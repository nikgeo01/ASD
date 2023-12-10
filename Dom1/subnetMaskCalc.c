#include <stdio.h>


unsigned int get_net_size(char *arr)
{
	unsigned int power = 0;
	for(int i = 3; i >= 0; i--)
	{
		for(int shifts = 0; shifts < 8; shifts++)
		{
			if((arr[i] & 1) == 0)
			{
				++power;
			}
			arr[i] >>= 1;
		}
	}
	unsigned int size = 1;
	for(int i = 0; i < power; i++)
	{
		size *= 2;
	}
	return (size - 2);
}

int main()
{
	unsigned char arr[4] = {255, 255, 255, 224};
	printf("%d\n", get_net_size(arr));

	return 0;
}