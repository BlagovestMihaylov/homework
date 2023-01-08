cmake_minimum_required(VERSION 3.23)
project(homework)

set(CMAKE_CXX_STANDARD 23)

add_executable(homework main.cpp reading/NumbersReader.cpp reading/NumbersReader.h separate/Separator.cpp separate/Separator.h test/doctest.h test/Tests.h numerics/NumericChecker.cpp numerics/NumericChecker.h calculation/BinaryCalculator.cpp calculation/BinaryCalculator.h)
