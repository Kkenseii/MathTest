#pragma once
#include "pch.h"
#include "mathtest.h"


TEST(SampleTest, AlwaysPasses)
{
    EXPECT_EQ(1, 1);
}

TEST(TaskTest, DefaultCtorValid)
{
    for (int i = 0; i < 50; ++i)
    {
        Task t;
        switch (t._operation)
        {
        case '+':
            EXPECT_EQ(t._answer, t.num_1 + t.num_2);
            break;
        case '-':
            EXPECT_EQ(t._answer, t.num_1 - t.num_2);
            break;
        case '*':
            EXPECT_EQ(t._answer, t.num_1 * t.num_2);
            break;
        case '/':
            EXPECT_NE(t.num_2, 0);
            EXPECT_EQ(t._answer, t.num_1 / t.num_2);
            break;
        default:
            FAIL() << "Unknown operation: " << t._operation;
        }
    }
}

TEST(TaskTest, RangeCtorRespectsRange)
{
    const int min = 5;
    const int max = 10;

    for (int i = 0; i < 50; ++i)
    {
        Task t(min, max, '+');
        EXPECT_GE(t.num_1, min);
        EXPECT_LE(t.num_1, max);
        EXPECT_GE(t.num_2, min);
        EXPECT_LE(t.num_2, max);
        EXPECT_EQ(t._answer, t.num_1 + t.num_2);
    }
}

TEST(TaskTest, FixedOperation)
{
    for (int i = 0; i < 50; ++i)
    {
        Task t(1, 9, '*');
        EXPECT_EQ(t._operation, '*');
        EXPECT_EQ(t._answer, t.num_1 * t.num_2);
    }
}

TEST(TaskTest, DivisionNoZeroDivisor)
{
    for (int i = 0; i < 100; ++i)
    {
        Task t(1, 20, '/');
        EXPECT_EQ(t._operation, '/');
        EXPECT_NE(t.num_2, 0);
        EXPECT_EQ(t._answer, t.num_1 / t.num_2);
    }
}

TEST(MathTestTest, CtorBySize)
{
    MathTest t(5);
    EXPECT_EQ(t.get_count(), 5);
    EXPECT_EQ(t.get_correct(), 0);
}

TEST(MathTestTest, CtorByRange)
{
    const int count = 10;
    const int min = 1;
    const int max = 9;

    MathTest t(count, min, max);

    EXPECT_EQ(t.get_count(), count);
    for (int i = 0; i < count; ++i)
    {
        EXPECT_GE(t.get_task(i).num_1, min);
        EXPECT_LE(t.get_task(i).num_1, max);
        EXPECT_GE(t.get_task(i).num_2, min);
        EXPECT_LE(t.get_task(i).num_2, max);
    }
}

TEST(MathTestTest, CtorByOperation)
{
    const int count = 10;
    MathTest t(count, 1, 9, '*');

    EXPECT_EQ(t.get_count(), count);
    for (int i = 0; i < count; ++i)
    {
        EXPECT_EQ(t.get_task(i)._operation, '*');
    }
}

TEST(MathTestTest, SubmitCorrectAnswer)
{
    MathTest t(3, 1, 9, '+');

    for (int i = 0; i < 3; ++i)
    {
        t.submit_answer(i, t.get_task(i)._answer);
    }

    EXPECT_EQ(t.get_correct(), 3);
    for (int i = 0; i < 3; ++i)
    {
        EXPECT_EQ(t.get_user_answer(i), t.get_task(i)._answer);
    }
}

TEST(MathTestTest, SubmitWrongAnswer)
{
    MathTest t(3, 1, 9, '+');

    t.submit_answer(0, t.get_task(0)._answer);
    t.submit_answer(1, t.get_task(1)._answer + 1000);
    t.submit_answer(2, t.get_task(2)._answer - 1000);

    EXPECT_EQ(t.get_correct(), 1);
    EXPECT_EQ(t.get_user_answer(0), t.get_task(0)._answer);
    EXPECT_EQ(t.get_user_answer(1), t.get_task(1)._answer + 1000);
    EXPECT_EQ(t.get_user_answer(2), t.get_task(2)._answer - 1000);
}

TEST(MathTestTest, SubmitInvalidIndexIgnored)
{
    MathTest t(2, 1, 9, '+');

    t.submit_answer(-1, 0);
    t.submit_answer(5, 0);

    EXPECT_EQ(t.get_correct(), 0);
}

TEST(MathTestTest, MarkAllCorrect)
{
    MathTest t(10, 1, 9, '+');
    for (int i = 0; i < 10; ++i)
    {
        t.submit_answer(i, t.get_task(i)._answer);
    }
    EXPECT_EQ(t.get_mark(), 'A');
}

TEST(MathTestTest, MarkNoneCorrect)
{
    MathTest t(10, 1, 9, '+');
    for (int i = 0; i < 10; ++i)
    {
        t.submit_answer(i, t.get_task(i)._answer + 1000);
    }
    EXPECT_EQ(t.get_mark(), 'F');
}

TEST(MathTestTest, MarkBoundaryC)
{
    MathTest t(10, 1, 9, '+');

    for (int i = 0; i < 6; ++i)
        t.submit_answer(i, t.get_task(i)._answer);
    for (int i = 6; i < 10; ++i)
        t.submit_answer(i, t.get_task(i)._answer + 1000);

    EXPECT_EQ(t.get_correct(), 6);
    EXPECT_EQ(t.get_mark(), 'C');
}