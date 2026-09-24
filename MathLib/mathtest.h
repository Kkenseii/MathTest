#pragma once


struct Task {
	int num_1;
	int num_2;
	char _operation;
	int _answer;

	Task();
	Task(int min, int max, char operation = '\0');
	void print() const noexcept;
};

class MathTest {

    Task* tasks;
    int count;
    int* user_answers;
    int correct_count;

public:
    MathTest(int count);
    MathTest(int count, int min, int max);
    MathTest(int count, int min, int max, char op);
    ~MathTest();

    void run();               
    void show_statistics() const noexcept;
    void submit_answer(int i, int a);  
    char get_mark() const noexcept;

    int get_count() const noexcept { 
        return count; 
    }
    int get_correct() const noexcept { 
        return correct_count; 
    }
    int get_user_answer(int i) const noexcept { 
        return user_answers[i]; 
    }
    const Task& get_task(int i) const { 
        return tasks[i]; 
    }


};