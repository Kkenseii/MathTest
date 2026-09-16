#pragma once


struct Task {
	int num_1;
	int num_2;
	char _operation;
	int _answer;

	Task();
	Task(int min, int max, char operation = '\0');
	void print() const;
};


class MathTest;