#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

class MyStack
{
public:
	int get_max()
	{
		if (max_stack.empty())
			return 0;
		else
			return max_stack.top();
	}

	void push(int element)
	{
		s.push(element);
		if (element > get_max())
			max_stack.push(element);
		else
			max_stack.push(get_max());
	}

	void pop()
	{
		if (!max_stack.empty() && !s.empty())
		{
			max_stack.pop();
			s.pop();
		}
	}

	int top()
	{
		return s.top();
	}

	bool empty()
	{
		return s.empty();
	}

	int size()
	{
		return s.size();
	}

private:
	stack<int> max_stack;
	stack<int> s;
};

class MyQueue
{
public :
	void push(int element)
	{
		stackIn.push(element);
	}

	int pop()
	{
		if (stackOut.empty())
		{
			while (!stackIn.empty())
			{
				stackOut.push(stackIn.top());
				stackIn.pop();
			}
		}
		int value = stackOut.top();
		stackOut.pop();
		return value;
	}

	int get_max()
	{
		return max(stackIn.get_max(), stackOut.get_max());
	}

private:
	MyStack stackIn;
	MyStack stackOut;
};

int main()
{
	
}
