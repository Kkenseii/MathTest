#include "mathtest.h"
#include <iostream>
#include <ctime>

static int rnd(int min, int max) {
    static bool seeded = false;
    if (!seeded) { std::srand((unsigned)std::time(nullptr)); seeded = true; }
    if (min > max) { int t = min; min = max; max = t; }
    return min + std::rand() % (max - min + 1);
}

static char rnd_op() {
    const char ops[4] = { '+', '-', '*', '/' };
    return ops[rnd(0, 3)];
}

Task::Task() : Task(1, 20, '\0') {}

Task::Task(int min, int max, char op) {
    _operation = (op == '\0') ? rnd_op() : op;

    if (min > max) {
        int t = max;
        max = min;
        min = t;
    }

    if (_operation == '/') {
        num_2 = rnd(1, max);
        int res = rnd(min, max);
        num_1 = num_2 * res;
        _answer = res;
    }
    else {
        num_1 = rnd(min, max);
        num_2 = rnd(min, max);
        if (_operation == '+') _answer = num_1 + num_2;
        else if (_operation == '-') _answer = num_1 - num_2;
        else _answer = num_1 * num_2; 
    }
}

void Task::print() const {
    std::cout << num_1 << " " << _operation << " " << num_2;
}

static void pad(int value, int width)
{
    int len = 0;
    int tmp = value;
    if (tmp == 0) len = 1;
    else
    {
        if (tmp < 0) { len++; tmp = -tmp; }
        while (tmp > 0) { len++; tmp /= 10; }
    }
    for (int i = len; i < width; ++i) std::cout << ' ';
    std::cout << value;
}

static void pad(const char* s, int width)
{
    int len = 0;
    while (s[len] != '\0') ++len;
    for (int i = len; i < width; ++i) std::cout << ' ';
    std::cout << s;
}


MathTest::MathTest(int count)   {
    this->count = count;
    correct_count = 0;
    tasks = new Task[count];
    user_answers = new int[count]();
}

MathTest::MathTest(int count, int min, int max) : MathTest(count) {
    for (int i = 0; i < count; ++i) tasks[i] = Task(min, max);
}

MathTest::MathTest(int count, int min, int max, char op)
    : MathTest(count)
{
    for (int i = 0; i < count; ++i) tasks[i] = Task(min, max, op);
}

MathTest::~MathTest()
{
    delete[] tasks;
    delete[] user_answers;
}

void MathTest::submit_answer(int i, int a)
{
    if (i < 0 || i >= count) return;
    user_answers[i] = a;
    if (a == tasks[i]._answer) ++correct_count;
}

char MathTest::get_mark() const
{
    if (count == 0) return 'F';
    double r = (double)correct_count / count;
    if (r >= 0.9)  return 'A';
    if (r >= 0.75) return 'B';
    if (r >= 0.6)  return 'C';
    if (r >= 0.4)  return 'D';
    return 'F';
}

void MathTest::run()
{
    for (int i = 0; i < count; ++i)
    {
        std::cout << "Question " << (i + 1) << ": ";
        tasks[i].print();
        std::cout << " = ? ";
        int a; std::cin >> a;
        submit_answer(i, a);
    }
    show_statistics();
}

void MathTest::show_statistics() const
{
    std::cout << "|";
    pad("No", 12);
    std::cout << " |";
    for (int i = 0; i < count; ++i)
    {
        std::cout << " ";
        pad(i + 1, 7);
        std::cout << " |";
    }
    std::cout << "\n+";
    for (int i = 0; i <= count; ++i) std::cout << "--------+";
    std::cout << "\n";

    std::cout << "|";
    pad("Question", 12);
    std::cout << " |";
    for (int i = 0; i < count; ++i)
    {
        char buf[32];
        int n = 0;
        {
            int v = tasks[i].num_1; char tmp[12]; int k = 0;
            if (v == 0) tmp[k++] = '0';
            else {
                if (v < 0) { tmp[k++] = '-'; v = -v; }
                char rev[12]; int r = 0;
                while (v > 0) { rev[r++] = char('0' + v % 10); v /= 10; }
                while (r > 0) tmp[k++] = rev[--r];
            }
            for (int j = 0; j < k; ++j) buf[n++] = tmp[j];
        }
        buf[n++] = ' ';
        buf[n++] = tasks[i]._operation;
        buf[n++] = ' ';
        {
            int v = tasks[i].num_2; char tmp[12]; int k = 0;
            if (v == 0) tmp[k++] = '0';
            else {
                if (v < 0) { tmp[k++] = '-'; v = -v; }
                char rev[12]; int r = 0;
                while (v > 0) { rev[r++] = char('0' + v % 10); v /= 10; }
                while (r > 0) tmp[k++] = rev[--r];
            }
            for (int j = 0; j < k; ++j) buf[n++] = tmp[j];
        }
        buf[n] = '\0';

        std::cout << " ";
        pad(buf, 7);
        std::cout << " |";
    }
    std::cout << "\n";

    std::cout << "|";
    pad("True Answer", 12);
    std::cout << " |";
    for (int i = 0; i < count; ++i)
    {
        std::cout << " ";
        pad(tasks[i]._answer, 7);
        std::cout << " |";
    }
    std::cout << "\n";

    std::cout << "|";
    pad("Your Answer", 12);
    std::cout << " |";
    for (int i = 0; i < count; ++i)
    {
        std::cout << " ";
        pad(user_answers[i], 7);
        std::cout << " |";
    }
    std::cout << "\n";

    std::cout << "|";
    pad("Result", 12);
    std::cout << " |";
    for (int i = 0; i < count; ++i)
    {
        const char* mark = (user_answers[i] == tasks[i]._answer) ? "+" : "-";
        std::cout << " ";
        pad(mark, 7);
        std::cout << " |";
    }
    std::cout << "\n\n";

    std::cout << "Total Result: " << correct_count << " / " << count
        << " (mark: " << get_mark() << ")\n";
}