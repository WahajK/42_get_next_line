/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 00:15:54 by muhakhan          #+#    #+#             */
/*   Updated: 2024/12/20 17:32:08 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/**
 * @brief Copies up to n - 1 characters from the string src to dest, 
 *        null-terminating the result if n is not 0.
 * 
 * @param dest The destination buffer where the content is to be copied.
 * @param src The source string to be copied.
 * @param n The maximum number of characters to be copied from src.
 * 
 * @return A pointer to the destination string dest.
 */
static char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * @brief Duplicates up to n characters from the given string.
 *
 * This function allocates memory and duplicates up to n characters from the
 * input string 's' into the newly allocated memory. The duplicated string
 * is null-terminated.
 *
 * @param s The input string to duplicate.
 * @param n The maximum number of characters to duplicate.
 * @return A pointer to the newly allocated string, or NULL if allocation fails.
 */
static char	*ft_strndup(const char *s, size_t n)
{
	char	*ptr;

	ptr = malloc(n + 1);
	if (!ptr)
		return (NULL);
	ft_strncpy(ptr, s, n);
	return (ptr);
}

/**
 * ft_substr - Allocates and returns a substring from the string 's'.
 * @s: The string from which to create the substring.
 * @start: The start index of the substring in the string 's'.
 * @len: The maximum length of the substring.
 *
 * Return: The substring. NULL if the allocation fails or if 's' is NULL.
 *
 * Description: This function allocates memory for a substring of 's' starting
 * from index 'start' and of maximum length 'len'. If 'start' is greater than
 * the length of 's' or 'len' is 0, it returns an empty string. If memory
 * allocation fails, it returns NULL.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s) || len == 0)
		return (NULL);
	else
	{
		s += start;
		if (len > ft_strlen(s))
			len = ft_strlen(s);
		ptr = ft_strndup(s, len);
	}
	return (ptr);
}

/**
 * ft_strlen - Calculates the length of a string.
 * @s: The string whose length is to be calculated.
 *
 * Return: The number of characters in the string, excluding the null byte.
 */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/**
 * ft_strchr - Locate character in string
 * @s: The string to be searched
 * @c: The character to be located
 *
 * This function locates the first occurrence of the character @c (converted to
 * an unsigned char) in the string pointed to by @s. The terminating null byte
 * is considered part of the string, so that if @c is '\0', the function will
 * return a pointer to the terminator.
 *
 * Return: A pointer to the first occurrence of the character @c in the string
 * @s, or NULL if the character is not found.
 */
char	*ft_strchr(const char *s, int c)
{
	while (*s != (unsigned char)c)
		if (!*s++)
			return (0);
	return ((char *)s);
}
