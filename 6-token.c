#include "shell.h"

/**
 * strtow - splits a string into words. Repeat delimiters are ignored.
 * @str: the input string
 * @d: the delimiter string
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);

	/* If no delimiter is provided, use a space as the default delimiter */
	if (!d)
		d = " ";

	/* Count the number of words in the input string */
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	/* If no words are found, return NULL */
	if (numwords == 0)
		return (NULL);

	/* Allocate memory for the array of strings */
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);

	/* Split the input string into words */
	for (i = 0, j = 0; j < numwords; j++)
	{
		/* Skip leading delimiters */
		while (is_delim(str[i], d))
			i++;

		/* Find the length of the current word */
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;

		/* Allocate memory for the current word */
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			/* Free previously allocated memory and return NULL if allocation fails */
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		/* Copy the characters of the current word to the allocated memory */
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0; /* Null-terminate the current word */
	}

	s[j] = NULL; /* Null-terminate the array of strings */
	return (s);
}


char **split_string(char *str, char *delimiter, int *num_words) {
    char **words = NULL;
    int word_count = 0;
    char *token;

    if (str == NULL || delimiter == NULL || num_words == NULL) {
        return NULL;
    }

    /* Count the number of words in the string */
    char *str_copy = strdup(str);
    if (str_copy == NULL) {
        return NULL;
    }

    token = strtok(str_copy, delimiter);
    while (token != NULL) {
        word_count++;
        token = strtok(NULL, delimiter);
    }

    /* Allocate memory for the array of pointers to words */
    words = (char **)malloc((word_count + 1) * sizeof(char *));
    if (words == NULL) {
        free(str_copy);
        return NULL;
    }

    /* Split the string and store words in the array */
    token = strtok(str, delimiter);
    for (int i = 0; i < word_count; i++) {
        words[i] = strdup(token);
        if (words[i] == NULL) {
            /* Free memory and return NULL if memory allocation fails */
            for (int j = 0; j < i; j++) {
                free(words[j]);
            }
            free(words);
            free(str_copy);
            return NULL;
        }
        token = strtok(NULL, delimiter);
    }

    words[word_count] = NULL;  /* Mark the end of the array */
    *num_words = word_count;
    free(str_copy);
    return words;
}

int main() {
    char input[] = "Hello, world! This is a test.";
    char delimiter[] = " ,.!";  /* Delimiters are space, comma, and period */
    int num_words;

    char **words = split_string(input, delimiter, &num_words);
    if (words != NULL) {
        for (int i = 0; i < num_words; i++) {
            printf("Word %d: %s\n", i + 1, words[i]);
            free(words[i]);
        }
        free(words);
    } else {
        printf("Failed to split the string.\n");
    }

    return 0;
}

