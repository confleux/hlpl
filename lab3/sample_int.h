#include <iostream>
#include <vector>

/*  i
    x ->
  jy[1 2 3 0
   | 4 5 6 0
   v 7 8 9 0]

   4 x 3

   2 3
*/
/*
 ^[1 2 3 0
 | 4 5 6 0
 y 7 8 9 0]
   x ->
*/



//-------------------------------------------------------------------------------------------------
// базовый класс для выборки (квадратной или прямоугольной)
class Sample_int
{
protected:
    // число элементов выборки по x и y
    int m_size_x = 0, m_size_y = 0;
    // массив данных
    std::vector<int> m_data;
	
public:
    // конструктор
    Sample_int() = default;
    // деструктор
    ~Sample_int() = default;

    
    // изменение размера для квадратной выборки
    void Resize(int size);
	// изменение размера для прямоугольной выборки
    void Resize(int size_x, int size_y);

    // размер выборки (для квадратной)
    int GetSize() const;
    // размер выборки по X и Y
    int GetSizeX() const;
    int GetSizeY() const;

    // оператор получения значения элемента с номером i,j
    int& operator()(int i, int j);
    // оператор получения const значения элемента с номером i,j
    const int& operator()(int i, int j) const;

    // проверка квадратная ли выборка
    bool IsSquare() const;
    // проверка что размер != 0
    bool IsZeroSize() const;
	// проверка равенства размеров с другой выборкой
    bool IsEqualSize(const Sample_int &temp) const;

    // инициализация всех элементов выборки одинаковым значением
    void SetValue(int value);
	// получение указателя на всю выборку
    int* GetPointer();
	// вычисление максимального значения
    int GetMax() const;

    // операции с выборкой и числом
    // сложение всех элементов выборки и числа
    Sample_int& operator+=(int value);
    // умножение всех элементов выборки на число
    Sample_int& operator*=(int value);
    // деление всех элементов выборки на число
    Sample_int& operator/=(int value);

    // операции с двумя выборками
    // присваивание
    Sample_int& operator= (const Sample_int& temp);
    // поэлементное сложение двух выборок
    Sample_int& operator+=(const Sample_int& temp);
    // поэлементное вычитание двух выборок
    Sample_int& operator-=(const Sample_int& temp);
    // поэлементное перемножение двух выборок
    virtual Sample_int& operator*=(const Sample_int& temp);

    // вывод выборки в поток (файл или экран)
    std::ostream& Save(std::ostream& out);
    // перегрузка оператора чтения выборки из файла 
    std::istream& Load(std::istream& out);

protected:
    // проверяет квадратная ли выборка, если нет - создает исключение
    void CheckSquare() const;
};
//-------------------------------------------------------------------------------------------------
