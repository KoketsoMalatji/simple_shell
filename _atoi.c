#include "shell.h"

int findtensplaces(int i, char *s)
{
	double tens = 1;

	while (s[i] >= '0' && s[i] <= '9')
	{
		tens *= 10;
		i++;
	}
	tens /= 10;
	return ((int) tens);
}

/**
 * _atoi - converts str into int
 * @s: str to convert to int
 * Rrturn: converted int.
 */

int _atoi(char *s)
{
	int i = 0, j = 0;
	int tens = 1;
	unsigned int integer = 0;
	int isnegative = 0;
	int numnegs = 0;
	int numpos = 0;

	while (s[j] != '\0')
	{
		if (s[j] > '9' || s[j] < '0')
			return (-1);
		j++;
	}
	while ((s[i] > '9' || s[i] < '0') && s[i] != '\0')
	{
		if (s[i] == '-')
			numnegs++;
		if (s[i] == '+')
			numpos++;
		i++;
	}
	if (s[i] == '\0')
		return (0);

	if ((numnegs % 2) != 0)
		isnegative = 1;

	tens = findtensplaces(i, s);
	while (s[i] >= '0' && s[i] <= '9')
	{
		integer += ((s[i] - '0') * tens);
		tens /= 10;
		i++;
	}
	if (isnegative == 1)
		integer *= -1;

	return ((int) integer);
}
