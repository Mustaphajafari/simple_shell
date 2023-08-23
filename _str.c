#include "shell.h"

/**
 * str_len - returns the length of a string.
 * @string: pointer to string.
 * Return: length of string.
 */
int str_len(const char *string)
{
int length = 0;
if (string == NULL)
return (0);


while (string[length] != '\0')
length++;
return (length);
}

/**
 * str_dup - duplicates a string.
 * @string: String to be copied
 * Return: pointer to the new string
 */
char *str_dup(const char *string)
{
int i = 0;
int length = str_len(string);
char *result;

if (string == NULL)
return (NULL);


result = malloc(sizeof(char) * (length + 1));

if (result == NULL)
{
errno = ENOMEM;
perror("Error");
return (NULL);
}

for (i = 0; i <= length; i++)
result[i] = string[i];

return (result);
}

/**
 * str_compare - Compare two strings
 * @string1: First string
 * @string2: Second string
 * @number: number of characters to be compared, 0 for full comparison
 * Return: 1 if the strings are equal, 0 if they are different
 */
int str_compare(const char *string1, const char *string2, int number)
{
int i = 0;
int length1 = str_len(string1);
int length2 = str_len(string2);



if (string1 == NULL && string2 == NULL)
return (1);

if (string1 == NULL || string2 == NULL)
return (0);



if (number == 0)
number = length1; /* Full comparison*/

if (length1 != length2 || length1 < number || length2 < number)
return (0);

for (i = 0; i < number; i++)
{
if (string1[i] != string2[i])
return (0);
}
return (1);
}

/**
 * str_concat - concatenates two strings.
 * @string1: First string
 * @string2: Second string
 * Return: pointer to the concatenated string
 */
char *str_concat(const char *string1, const char *string2)
{
int i, j;
char *result;


int length1 = str_len(string1);
int length2 = str_len(string2);

if (string1 == NULL)
string1 = "";

if (string2 == NULL)
string2 = "";



result = malloc(sizeof(char) * (length1 + length2 + 1));
if (result == NULL)
{
errno = ENOMEM;
perror("Error");
return (NULL);
}



for (i = 0; i < length1; i++)
result[i] = string1[i];

for (j = 0; j < length2; j++, i++)
result[i] = string2[j];

result[i] = '\0';
return (result);
}

/**
 * str_rev - reverses a string.
 * @string: pointer to string.
 * Return: void.
 */
void str_rev(char *string)
{
int i = 0, length = str_len(string) - 1;

while (i < length)
{
char hold = string[i];
string[i++] = string[length];
string[length--] = hold;
}
}

