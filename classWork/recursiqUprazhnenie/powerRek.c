#include <stdio.h>

int power (int x, int n)
{
	if (n == 1)
	{
		return x;
	}
	return x * power(x, n - 1);

}

int main()
{
	int x = 2, n = 8;
	printf("%d\n", power(x, n));

	return 0;
}
