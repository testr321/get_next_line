#include "get_next_line_bonus.h"

static char	**copy(char **str1, int size, int choice)
{
	char	**str2;
	int		tempint;

	tempint = 1;
	if (choice != 2)
	{
		str2 = malloc(sizeof(*str2) * (size + 2));
		str2[size + 1] = 0;
		str2[0] = ft_strljoin(str1[0], "", 0);
		while (tempint <= ft_atoi(str1[0]) + 1)
		{
			if (str1[tempint])
			{
				str2[tempint] = ft_strljoin(str1[tempint], "", 0);
				free(str1[tempint++]);
			}
			else
				str2[tempint++] = 0;
		}
	}
	while (tempint <= size && (choice == 1 || choice == 2))
		str1[tempint++] = 0;
	if (choice == 2)
		return (0);
	return (str2);
}

static char	*readloop(int fd, char **buffer, char *str, char *tempbuffer)
{
	int		tempint;

	buffer[fd] = ft_strljoin(tempbuffer, "", 0);
	while (1)
	{
		str = ft_setstr(fd, buffer, str, 0);
		if (multi(str, 1))
			return (str);
		tempint = read(fd - 1, tempbuffer, BUFFER_SIZE);
		tempbuffer[tempint] = '\0';
		free(buffer[fd]);
		buffer[fd] = ft_strljoin(tempbuffer, "", 0);
		if (tempint == 0)
		{
			str = ft_setstr(fd, buffer, str, multi(str, 0));
			if (!*str)
			{
				free(str);
				str = 0;
			}
			free(buffer[fd]);
			buffer[fd] = 0;
			return (str);
		}
	}
}

static char	*exist(char **buffer, int fd, int tempint)
{
	char	**tempstr;
	char	*str;

	str = ft_strljoin("", buffer[fd], tempint);
	tempstr = malloc(sizeof(*tempstr) * 2);
	tempstr[1] = 0;
	tempstr[0] = ft_strljoin(buffer[fd] + tempint, "", 0);
	free(buffer[fd]);
	buffer[fd] = ft_strljoin(tempstr[0], "", 0);
	free(tempstr[0]);
	free(tempstr);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	**buffer;
	char		**tempstr;
	char		*str;
	char		tempbuffer[BUFFER_SIZE + 1];
	int			tempint;

	if (fd++ < 0)
		return (0);
	if (!buffer)
	{
		tempint = read(fd - 1, tempbuffer, BUFFER_SIZE);
		if (tempint == -1)
			return (0);
		multi2(buffer, fd, tempint, 0);
		buffer = malloc(sizeof(*buffer) * (fd + 2));
		buffer[fd + 1] = 0;
		buffer[0] = ft_itoa(fd);
	}
	else if (ft_atoi(buffer[0]) >= fd)
	{
		tempint = multi(buffer[fd], 1);
		if (tempint)
			return (exist(buffer, fd, tempint);
		tempint = read(fd - 1, tempbuffer, BUFFER_SIZE);
		if (tempint == -1)
			return (0);
	}
	else
	{
		tempint = read(fd - 1, tempbuffer, BUFFER_SIZE);
		if (tempint == -1)
			return (0);
		tempstr = copy(buffer, fd, 0);
		free(buffer);
		buffer = copy(tempstr, fd, 1);
		free(tempstr);
		buffer[0] = ft_itoa(fd);
	}
	tempbuffer[tempint] = '\0';
	if (buffer[fd])
		str = ft_strljoin(buffer[fd], "", 0);
	else
		str = ft_strljoin("\0", "", 0);
	free(buffer[fd]);
	return (readloop(fd, buffer, str, tempbuffer));
}

/* #include <stdio.h>
int main()
{
	int fd[4];
	fd[0] = open("files/empty", O_RDWR);
	char *testr;

	testr = get_next_line(fd[0]);
	printf("Main output: %s",  testr);
	printf("---main newline test---\n");
	free(testr);

	testr = get_next_line(fd[0]);
	printf("Main output: %s",  testr);
	printf("---main newline test---\n");
	free(testr);
} */