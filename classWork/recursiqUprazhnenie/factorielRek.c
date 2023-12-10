#include <stdio.h>

int factoriel(int n)
{
	if (n > 1)
	{
		return n * factoriel(n - 1);
	}
	return 1;
}

int main()
{

	int n = 5;
	printf("%d\n", factoriel(n));

	 return 0;
}
