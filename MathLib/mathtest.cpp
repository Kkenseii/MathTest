#include "mathtest.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

static int rnd(int min, int max)
{
    static bool seeded = false;
    if (!seeded) { std::srand((unsigned)std::time(nullptr)); seeded = true; }
    if (min > max) { int t = min; min = max; max = t; }
    return min + std::rand() % (max - min + 1);
}

static char rnd_op()
{
    const char ops[4] = { '+', '-', '*', '/' };
    return ops[rnd(0, 3)];
}

Task::Task() : Task(1, 20, '\0') {}

Task::Task(int min, int max, char op)
{
    _operation = (op == '\0') ? rnd_op() : op;

    if (_operation == '/')
    {
        num_2 = rnd(1, max);
        int res = rnd(min, max);
        num_1 = num_2 * res;
        _answer = res;
    }
    else
    {
        num_1 = rnd(min, max);
        num_2 = rnd(min, max);
        if (_operation == '+') _answer = num_1 + num_2;
        else if (_operation == '-') _answer = num_1 - num_2;
        else _answer = num_1 * num_2; 
    }
}

void Task::print() const
{
    std::cout << num_1 << " " << _operation << " " << num_2;
}