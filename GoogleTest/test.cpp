#pragma once
#include "pch.h"
#include "mathtest.h"

TEST(SampleTest, AlwaysPasses) { 
    EXPECT_EQ(1, 1); 
}

TEST(TaskTest, DefaultCtorValid)
{
    for (int i = 0; i < 50; ++i)
    {
        Task t;
        switch (t._operation)
        {
        case '+': EXPECT_EQ(t._answer, t.num_1 + t.num_2); break;
        case '-': EXPECT_EQ(t._answer, t.num_1 - t.num_2); break;
        case '*': EXPECT_EQ(t._answer, t.num_1 * t.num_2); break;
        case '/': EXPECT_NE(t.num_2, 0); EXPECT_EQ(t._answer, t.num_1 / t.num_2); break;
        default: FAIL();
        }
    }
}

TEST(TaskTest, RangeCtorRespectsRange)
{
    for (int i = 0; i < 50; ++i)
    {
        Task t(5, 10, '+');
        EXPECT_GE(t.num_1, 5); EXPECT_LE(t.num_1, 10);
        EXPECT_GE(t.num_2, 5); EXPECT_LE(t.num_2, 10);
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