/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:41:41 by muhakhan          #+#    #+#             */
/*   Updated: 2024/12/20 18:23:23 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/**
 * ft_strjoin - Allocates and returns a new string, which is the result of 
 * the concatenation of 's1' and 's2'.
 * @s1: The prefix string.
 * @s2: The suffix string.
 *
 * Return: The new string. NULL if the allocation fails.
 */
static char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		ptr[j++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		ptr[j++] = s2[i];
		i++;
	}
	ptr[j] = 0;
	return (ptr);
}

/**
 * set_line - Reads from a file descriptor and appends to the line until a 
 *            newline character is found or end of file is reached.
 * @fd: The file descriptor to read from.
 * @buffer: The buffer to store read data.
 * @line: The line to append read data to.
 *
 * This function reads from the given file descriptor into the buffer and 
 * appends the buffer content to the line until a newline character is found 
 * or the end of the file is reached. If the line already contains a newline 
 * character, the function returns immediately. The buffer is freed before 
 * returning.
 */
static void	set_line(int fd, char *buffer, char **line)
{
	int		i;
	char	*temp;

	if (!line[fd] || !ft_strchr(line[fd], '\n'))
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i <= 0)
			return (free(buffer));
		while (i > 0)
		{
			buffer[i] = '\0';
			if (!line[fd])
				line[fd] = ft_substr(buffer, 0, i);
			else
			{
				temp = line[fd];
				line[fd] = ft_strjoin(line[fd], buffer);
				free(temp);
			}
			if (ft_strchr(line[fd], '\n'))
				break ;
			i = read(fd, buffer, BUFFER_SIZE);
		}
	}
	free(buffer);
}

/**
 * get_line - Extracts a line from the given string and updates the string.
 * @line: Double pointer to the string from which the line is extracted.
 *
 * This function extracts a line from the given string up to and including
 * the first newline character. If there is no newline character, it returns
 * the entire string. The extracted line is returned, and the original string
 * is updated to remove the extracted part. If the input string is NULL, the
 * function returns NULL.
 *
 * Return: A pointer to the extracted line, or NULL if the input string is NULL.
 */
static char	*get_line(int fd, char **line)
{
	int		i;
	int		j;
	char	*ret;
	char	*temp;

	if (!line[fd])
		return (0);
	if (!ft_strchr(line[fd], '\n'))
	{
		ret = ft_substr(line[fd], 0, ft_strlen(line[fd]));
		free (line[fd]);
		line[fd] = 0;
		return (ret);
	}
	i = ft_strlen(line[fd]);
	j = ft_strlen(ft_strchr(line[fd], '\n'));
	ret = ft_substr(line[fd], 0, i - j + 1);
	temp = line[fd];
	line[fd] = ft_substr(ft_strchr(line[fd], '\n'), 1, j - 1);
	free(temp);
	return (ret);
}

/**
 * get_next_line - Reads a line from a file descriptor.
 * @fd: The file descriptor to read from.
 *
 * This function reads a line from the given file descriptor and returns it as
 * a string. It uses a static variable to store the remaining part of the line
 * between function calls. The function allocates memory for the buffer and
 * checks for errors such as invalid file descriptor or read errors.
 *
 * Return: A string containing the next line from the file descriptor, or NULL
 * if an error occurs or if the end of the file is reached.
 */
char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*line[OPEN_MAX];

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (BUFFER_SIZE < 1 || fd == -1 || read(fd, buffer, 0) == -1)
	{
		free(buffer);
		return (0);
	}
	set_line(fd, buffer, line);
	return (get_line(fd, line));
}
// #include <stdio.h>
// #include <fcntl.h>
// int	main()
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	char *str;
// 	while (str = get_next_line(fd))
// 	{
// 		printf("%s\n", str);
// 		free(str);
// 	}
// 	printf("%s\n", str);
// 	close(fd);
// }