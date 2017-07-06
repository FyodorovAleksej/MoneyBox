#include <stdio.h>
#include <stdlib.h>

#define N 7												     		 // count of coins

struct Coin															 // every coin
{
	int count;														 // count of this coin
	int capacity;													 // capacity of coin
};

char out(int count, struct Coin *mon, int*result, int start);        // usual algoritm
char more(int count, struct Coin *mon, int*result);                  // find more

int main()
{
	struct Coin *copilka;											 // copilka
	copilka = (struct Coin*)malloc(sizeof(struct Coin) * (N+1));     // memory for copilka
	copilka[0].count = 5;											 // count of 1 cent
	copilka[0].capacity = 0.01 * 100;								 // capacity of cent

	copilka[1].count = 0;											 // count of 2 cents
	copilka[1].capacity = 0.02 * 100;								 // capacity of 2 cents

	copilka[2].count = 0;											 // count of 5 cents
	copilka[2].capacity = 0.05 * 100;								 // capacity of 5 cents

	copilka[3].count = 0;											 // count of 10 cents
	copilka[3].capacity = 0.1 * 100;								 // capacity of 10 cents

	copilka[4].count = 1;											 // count of 20 cents
	copilka[4].capacity = 0.2 * 100;								 // capacity of 20 cents

	copilka[5].count = 5;											 // count of 50 cents
	copilka[5].capacity = 0.5 * 100;							     // capacity of 50 cents

	copilka[6].count = 5;											 // count of 100 cents
	copilka[6].capacity = 1.0 * 100;								 // capacity of 100 cents

	copilka[7].count = 5;											 // count of 200 cents
	copilka[7].capacity = 2.0 * 100;								 // capacity of 200 cents

	int* res = (int*) malloc (sizeof(int) * (N + 1));				 // the array with count of all coins
	for (int i = 0; i <= N; i++)
	{
		res[i] = 0;													 // fill result by zeros
	}

	int output = 14;												 // the summ for output

	if (out(output, copilka, res, N))								 // try out this summ
	{
		int sum = 0;												 // summ of the all used coins for checked
		printf("%d -- YES:\n",output);								 // the output of result
		for (int i = 0; i <= N; i++)
		{
			printf("%d cent - %d\n", copilka[i].capacity, res[i]);
			sum += (copilka[i].capacity * res[i]);
		}
		printf("result sum - %d\n", sum);
	}
	else
	{
		for (int i = 0; i <= N; i++) res[i] = 0;					 // clear result array
		if (more(output, copilka, res))								 // try used in more destination
		{
			int sum = 0;
			printf("%d -- YES:\n", output);							 // the result
			for (int i = 0; i <= N; i++)
			{
				printf("%d cent - %d\n", copilka[i].capacity, res[i]);
				sum += (copilka[i].capacity * res[i]);
			}
			printf("result sum - %d\n", sum);
		}
		else
		{
			printf("%d -- NO:\n", output);							 // if not usual alghoritm and no more alghoritm
		}
	}
	system("pause");

	free(copilka);													 // free memory
	free(res);
	return 0;
}

char out(int count, struct Coin *mon, int*result, int start)
{
	if (count == 0) return 1;										 // if count -> 0
	for (int i = start; i >= 0; i--)								 // check all coins
	{
		if (mon[i].capacity <= count)								 // if coin <= count 
		{
			if (mon[i].count - result[i] > 0)						 // if count of unused coin with this capacity > 0
			{
				result[i]++;										 // using this coin
				return (out(count - mon[i].capacity, mon, result, i)); // try return the other count
			}
			else
			{
				if (out(mon[i].capacity, mon, result, i - 1))		 // try using this capacity by other coins
				{
					return (out(count - mon[i].capacity, mon, result, i)); // if good -> using other coins
				}
				else
				{
					return 0;										 // if can't
				}
			}
		}
	}
	return 0;
}

char more(int count, struct Coin *mon, int* result)
{
	for (int i = 0; i <= N; i++)									 // for all coins
	{
		if (mon[i].capacity > count && mon[i].count - result[i] > 0) // if coin > count
		{
			result[i]++;											 // using big coin
			return 1;												 // is can
		}
	}
	return 0;														 // can't
}