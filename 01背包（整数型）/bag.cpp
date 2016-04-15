#include "bag.h"

float bag::Onebag(const object &one)
{
	for (unsigned int i = Max_weight; i >= one.weight;i--)
		if (ValueOfBag[i-one.weight]>=0//要求恰好装满的时候用的。
			&&ValueOfBag[i] < ValueOfBag[i - one.weight] + one.value)
		{
			ValueOfBag[i] = ValueOfBag[i - one.weight] + one.value;
			//更新解
			solution[i]=solution[i-one.weight];
			solution[i].push(one);
		}
	return ValueOfBag[Max_weight];
}

float bag::Twobag(const object &one)
{
	for (unsigned int i = one.weight; i <= Max_weight;i++)
		if (ValueOfBag[i-one.weight]>=0
			&& ValueOfBag[i]<ValueOfBag[i-one.weight]+one.value)
		{
			ValueOfBag[i] = ValueOfBag[i - one.weight] + one.value;
			solution[i] = solution[i - one.weight];
			solution[i].push(one);
		}
	return ValueOfBag[Max_weight];
}

float bag::Threebag(const object &one)
{
	int i = 0;
	while ((1 << (i + 1) <= one.num))
	{
		Onebag(object(one.value*(1 << i), one.weight*(1 << i), 1 << i));
		i++;
	}
	int left = one.num - (1 << i) + 1;
	Onebag(object(one.value*left, one.weight*left, left));
	return ValueOfBag[Max_weight];
}

float bag::groupbag(const object one[], unsigned int n)
{
	for (int i = Max_weight; i >= 0; i--)
		re(j,n)
		if (i>=one[j].weight&&ValueOfBag[i-one[j].weight]>=0
			&& ValueOfBag[i]<ValueOfBag[i-one[j].weight]+one[j].value)
		{
			ValueOfBag[i] = ValueOfBag[i - one[j].weight] + one[j].value;
			solution[i] = solution[i - one[j].weight];
			solution[i].push(one[j]);
		}
	return ValueOfBag[Max_weight];
}



float bag::push(const object& one)
{
	if (one.num == 1)
		Onebag(one);
	else if (one.num == 0)
		Twobag(one);
	else 
		Threebag(one);
	return ValueOfBag[Max_weight];
}


array<object> bag::Solution(unsigned int n)
{
	if (n == 0)
		return solution[Max_weight];
	return 
		solution[n];
}



