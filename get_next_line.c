#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

static char	*ft_setstr(char *buffer, char *str, int tempint)
{
	char	*tempstr;

	tempstr = ft_strdup(str);
	free(str);
	str = malloc(sizeof(*str) * tempint);
	ft_strlcpy(str, tempstr, (ft_strlen(tempstr) + 1));
	ft_strlcat(str, buffer, tempint);
	free(tempstr);
	return (str);
}

static char	*get_next_line2(int fd, size_t *index, char *buffer, char *str)
{
	int		tempint;

	while (1)
	{
		tempint = read(fd, buffer, BUFFER_SIZE);
		buffer[tempint] = '\0';
		*index = ft_check(buffer);
		if (tempint != BUFFER_SIZE && !*index)
		{
			free(str);
			return (0);
		}
		if (!*index)
			tempint += ft_strlen(str) + 1;
		else
			tempint = ft_strlen(str) + *index + 1;
		str = ft_setstr(buffer, str, tempint);
		if (*index)
			return (str);
	}
}

char	*get_next_line(int fd)
{
	static size_t	index;
	static char		buffer[BUFFER_SIZE + 1];
	char			*str;
	int				tempint;

	tempint = ft_check(buffer + index);
	if (tempint)
	{		
		str = malloc(sizeof(*str) * (tempint + 1));
		ft_strlcpy(str, buffer + index, tempint + 1);
		index += tempint;
	}
	else
	{
		if (index <= BUFFER_SIZE)
		{
			tempint = ft_strlen(buffer + index);
			str = malloc(sizeof(*str) + (tempint + 1));
			ft_strlcpy(str, buffer + index, tempint + 1);
		}
		else
			str = ft_strdup("\0");
		return (get_next_line2(fd, &index, buffer, str));
	}
	return (str);
}
/* 
int main()
{
	int fd = open("testrtext.txt", O_RDONLY);

	char *testr;

	testr = get_next_line(fd);
	printf("Main output: %s",  testr);
	printf("---main newline test---\n");
	free(testr);

	testr = get_next_line(fd);
	printf("Main output: %s",  testr);
	printf("---main newline test---\n");
	free(testr);

	testr = get_next_line(fd);
	printf("Main output: %s",  testr);
	printf("---main newline test---\n");
	free(testr);

	testr = get_next_line(fd);
	printf("Main output: %s",  testr);
	printf("---main newline test---\n");
	free(testr);

	testr = get_next_line(fd);
	printf("Main output: %s",  testr);
	printf("---main newline test---\n");
	free(testr);
} */