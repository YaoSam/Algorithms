#include "bag.h"

void bag_1d::Onebag(const object_1d &one)
{
	for (int i = Max_weight; i >= one.weight;i--)
		if (ValueOfBag[i-one.weight]>=0//要求恰好装满的时候用的。
			&&ValueOfBag[i] < ValueOfBag[i - one.weight] + one.value)
		{
			ValueOfBag[i] = ValueOfBag[i - one.weight] + one.value;
			//更新解
			solution[i - one.weight]=solution[i];
			solution[i - one.weight].push(one);
		}
}
void bag_1d::Twobag(const object_1d &one)
{
	for (int i = one.weight; i <= Max_weight;i++)
		if (ValueOfBag[i-one.weight]>=0
			&& ValueOfBag[i]<ValueOfBag[i-one.weight]+one.value)
		{
			ValueOfBag[i] = ValueOfBag[i - one.weight] + one.value;
			solution[i].push(one);
		}
}

void bag_1d::Threebag(const object_1d &one)
{
	int i = 0;
	while ((1 << (i + 1) <= one.num))
	{
		Onebag(object_1d(one.value*(1 << i), one.weight*(1 << i), 1 << i));
		i++;
	}
	int left = one.num - (1 << i) + 1;
	Onebag(object_1d(one.value*left, one.weight*left, left));
}


float bag_1d::push(const object_1d& one)
{
	if (one.num == 1)
		Onebag(one);
	else if (one.num == 0)
		Twobag(one);
	else 
		Threebag(one);
	return ValueOfBag[Max_weight];
}


array<object_1d> bag_1d::Solution(unsigned int n)
{
	if (n == 0)
		return solution[Max_weight];
	return 
		solution[n];
}



