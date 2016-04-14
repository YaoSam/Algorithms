#include "Arrange.h"
int AllSolution(int m, int n)//相当于对完全n插树的前序遍历
{
	stack<int> Stack;
	int temp = 0, count = 0;
	while (temp < n || !Stack.isEmpty())//到了最顶层然后然后栈为空（也就是最后一列都被pop了）
	{
		while (Stack.Top() < m&&temp < n)//后一个条件指 非空位置。
		{
			Stack.push(temp);
			temp = 0;
		}
		if (Stack.Top() == m - 1)
		{
			std::cout << Stack;
			count++;
		}
		if (!Stack.isEmpty())//返回上一层取旁边一个节点。
			temp = Stack.pop() + 1;
	}
	return count;//其实直接return n^m也是可以的……
}

int Combination(int m, int n)
{
	stack<int> Stack;
	int count = 0, temp = 0;
	int flag[100] = { 0 }; 
	while (temp < n||!Stack.isEmpty())
	{
		while (Stack.Number() < m&&temp<n)
		{
			if (flag[temp] == 0)
			{
				Stack.push(temp);
				flag[temp] = 1;
			}
			temp++;
		}
		if (Stack.Number() == m)
		{
			std::cout << Stack;
			count++;
		}
		if (!Stack.isEmpty())
		{
			temp = Stack.pop() + 1;
			flag[temp - 1] --;
		}
	}
	return count;
}

int Permutation(int m, int n)
{
	stack<int> Stack;
	int count = 0, temp = 0, ok = 0;
	bool flag[100] = { 0 }; 
	while (temp < n || !Stack.isEmpty())
	{
		while (Stack.Number() < m&&temp<n)
		{
			if (flag[temp] == 0)
			{
				Stack.push(temp);
				flag[temp] = 1;
				if (ok > 1)temp = -1;//代表连续两次pop()而没有push所以要重新来
				ok = 0;
			}
			++temp;
		}
		if (Stack.Number() == m)
		{
			std::cout << Stack;
			count++;
		}
		if(!Stack.isEmpty())
		{
			temp = Stack.pop() + 1;
			flag[temp - 1] = 0;
			ok++;
		}
	}
	return count;
}