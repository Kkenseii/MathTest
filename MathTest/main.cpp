#include <iostream>
#include "mathtest.h"

int main()
{
    std::cout << "Hello, MathTest!" << std::endl;

    MathTest test(5, 1, 20);   // 5 вопросов, числа от 1 до 20
    test.run();                // прогон теста + вывод статистики

    return 0;
}