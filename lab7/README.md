## Исправления

### 1. fftw_plan

Создание `fftw_plan` и `fftw_alloc` на каждый запуск - это дорого, лучше переиспользовать план при повторных вычислениях

В `CalcFFT` добавлены `m_buf/m_plan` и `EnsurePlan()` — аллокация и построение плана делаются один раз на размер, дальше только `fftw_execute`.

До:

```c++
void CalcFFT::CalcFourier(SampleComplex& oSample_p) {
    const int rows = oSample_p.GetSizeX();
    const int cols = oSample_p.GetSizeY();
    ShiftSample(oSample_p);
    fftw_complex* in = fftw_alloc_complex(static_cast<size_t>(rows) * static_cast<size_t>(cols));
    fftw_complex* out = fftw_alloc_complex(static_cast<size_t>(rows) * static_cast<size_t>(cols));
    // ...
    fftw_plan plan = fftw_plan_dft_2d(rows, cols, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan);
    // ...
    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);
    ShiftSample(oSample_p);
}
```

После:

```c++
void CalcFFT::EnsurePlan(int rows, int cols) {
    // ... 
}
void CalcFFT::CalcFourier(SampleComplex& oSample_p) {
    const int rows = oSample_p.GetSizeX();
    const int cols = oSample_p.GetSizeY();
    ShiftSample(oSample_p);
    EnsurePlan(rows, cols);
    
    ShiftSample(oSample_p);
}
```

### 2. Сдвиг спектра

Прежний `ShiftSample` делает 2 полных копии матрицы и делает `%` для каждого элемента. Для четных `N` можно упростить.

Для чётных размеров (512/1024/2048) сделан in-place swap квадрантов без `tmp` и без `%`

До:

```c++
void CalcFFT::ShiftSample(SampleComplex& oSample_p) {
    const int rows = oSample_p.GetSizeX();
    const int cols = oSample_p.GetSizeY();
    const int shiftY = rows / 2;
    const int shiftX = cols / 2;

    SampleComplex tmp(rows, cols);
    for (int y = 0; y < rows; ++y)
      for (int x = 0; x < cols; ++x)
        tmp((y + shiftY) % rows, (x + shiftX) % cols) = oSample_p(y, x);

    for (int y = 0; y < rows; ++y)
      for (int x = 0; x < cols; ++x)
        oSample_p(y, x) = tmp(y, x);
}
```

После:

```c++
void CalcFFT::ShiftSample(SampleComplex& oSample_p) {
    const int rows = oSample_p.GetSizeX();
    const int cols = oSample_p.GetSizeY();

    if ((rows % 2 == 0) && (cols % 2 == 0)) {
        const int halfY = rows / 2;
        const int halfX = cols / 2;
        for (int y = 0; y < halfY; ++y) {
            for (int x = 0; x < halfX; ++x) {
                using std::swap;
                swap(oSample_p(y, x), oSample_p(y + halfY, x + halfX));
                swap(oSample_p(y + halfY, x), oSample_p(y, x + halfX));
            }
        }
        return;
    }
}
```

### 3. Лишние накладные расходы на `operator()(y,x)`

`operator()` в `Sample` делает проверки границ: двойные циклы и вызовы `operator()` дают лишнюю нагрузку на больших N. 

Использованы GetDataPointer() и один линейный проход по памяти.

До:

```c++
for (int y = 0; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
        oRes_p(y, x) = std::abs(sc(y, x));
    }
}
```

После:

```c++
const std::complex<double>* scData = sc.GetDataPointer();
double* resData = oRes_p.GetDataPointer();
const int total = oRes_p.GetSize();
for (int i = 0; i < total; ++i) {
    resData[i] = std::abs(scData[i]);
}
```

## Сравнение производительности

Был создан бенчмарк скрипт, результат сравнения:

![Alt text](docs/bench.png)