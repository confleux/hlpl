main:
	g++ -std=c++17 -o bin/main main.cpp sample.cpp matrix.cpp sample_complex.cpp
matrix_mul_boost:
	g++ -std=c++17 -I/opt/homebrew/Cellar/boost/1.90.0_1/include -o bin/mm_boost boost_benchmark.cpp sample_complex.cpp sample.cpp
matrix_mul_custom:
	g++ -std=c++17 -o bin/mm_custom matrix_benchmark.cpp sample_complex.cpp sample.cpp matrix.cpp