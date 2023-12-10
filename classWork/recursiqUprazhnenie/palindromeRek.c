#include <stdio.h>

int palindrome (char *str, int half, int left, int right)
{
	if (half == 0)
	{
		return 1;
	}

	return ((str[left] == str[right]) && palindrome(str, half - 1, left + 1, right - 1));
}

int main()
{

	char str[] = "abcfcba";
	int len = 7;
	int half = len/2;
	printf("%d\n", palindrome(str, half, 0, len - 1));

	return 0;
}
