#include <stdio.h> 
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#define MY_CHAR_MAX 255
#define MY_CHAR_MIN 0

int OneMoreIsspace(int ch)
{
	assert(ch <= MY_CHAR_MAX);
	assert(ch >= MY_CHAR_MIN);
	int Spaces[6] = { '\n', ' ', '\t', '\v', '\r', '\v' };
	int i, a;
	a = 1;
	for (i = 0; i < 6; i++)
	{
		if (!(ch - Spaces[i])) a = 0;
	}
	return (!a);
}

int OneMoreUpcase(int ch)
{
	assert((MY_CHAR_MIN <= ch) && (ch <= MY_CHAR_MAX));
	if (('a' <= ch) && (ch <= 'z')) ch += 'A' - 'a';
	return ch;
}

size_t OneMoreStrlen(const char *str)
{
	assert(str != NULL);
	size_t res = 0;
	while (*str++)
	{
		++res;
	}
	return res;
}

char *OneMoreStrcat(char *dest, const char *src)
{
	assert(dest != NULL);
	assert(src != NULL);
	char *curr = dest + OneMoreStrlen(dest);
	while (*curr++ = *src++);
	return dest;
}

char *OneMoreStrstr(const char *haystack, const char *needle)
{
	assert(haystack != NULL);
	assert(needle != NULL);
	char *curr, *curr_n;
	if (!(*needle)) return haystack;
	if (!(*haystack)) return needle;
	while (*haystack)
	{
		curr = haystack;
		curr_n = needle;
		while (*curr == *curr_n)
		{
			if (!*curr_n) return haystack;
			if (!*curr) return NULL;
			curr++;
			curr_n++;
		}
		if (!*curr_n) return haystack;
		haystack++;
	}
	return NULL;
}

unsigned long int OneMoreStrtoul(const char *string, char **endptr, int basis)
{
	assert(string != NULL);
	assert((basis >= 0) || ((basis >= 2) && (basis <= 36)));
	while (OneMoreIsspace(*string) && (*string)) string++;
	unsigned long int res = 0;
	if (!basis)
	{
		basis = 10;
		if (*string == '0')
		{
			basis = 8;
			string++;
		}
		if (OneMoreUpcase(*(string)) == 'X')
		{
			basis = 16;
			string++;
		}
	}
	unsigned long int maximum = ULONG_MAX / basis;
	unsigned long int cut_maximum = ULONG_MAX % basis;
	int basis_ch = basis - 11;
	int basis_d = basis - 1;
	if (basis > 10) basis_d = 9;
	int IsDigit = 1;
	int DIGIT = 0;
	assert(basis_d < 10);
	assert(basis_ch < 26);
	while (*string)
	{
		int IsDigit = 0;
		if ((*string >= '0') && (*string <= '0' + basis_d))
		{
			IsDigit = 1;
			DIGIT = *string - '0';
		}
		if ((OneMoreUpcase(*string) >= 'A') && (OneMoreUpcase(*string) <= 'A' + basis_ch))
		{
			IsDigit = 1;
			DIGIT = *string - 'A' + 10;
		}
		string++;
		if (!IsDigit) break;
		if ((res > maximum) || ((res == maximum) && (DIGIT > cut_maximum)))
		{
			res = ULONG_MAX;
			errno = ERANGE;
			return res;
		}
		else
		{
			res = res * basis + DIGIT;
		}
	}
	if (*endptr != NULL) *endptr = string;
	return res;
}

int main()
{
	return 0;
}