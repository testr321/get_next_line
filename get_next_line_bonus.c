#include "get_next_line_bonus.h"

static char	**copy(char **str1, int size, int choice)
{
	char	**str2;
	int		tempint;

	tempint = 1;
	if (choice != 3)
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
	while (tempint <= size && (choice == 1 || choice == 3))
		str1[tempint++] = 0;
	if (choice == 3)
		return (0);
	return (str2);
}

static char	*ft_setstr(int fd, char **buffer, char *str, int tempint)
{
	char	*tempstr;

	tempint += ft_strlen(str) + ft_strlen(buffer[fd]);
	if (ft_check(buffer[fd]))
		tempint = ft_strlen(str) + ft_check(buffer[fd]);
	tempstr = ft_strljoin(str, "", 0);
	free(str);
	if (ft_check(buffer[fd]))
		str = ft_strljoin(tempstr, buffer[fd], ft_check(buffer[fd]));
	else
		str = ft_strljoin(tempstr, buffer[fd], tempint);
	free(tempstr);
	if (ft_check(buffer[fd]))
	{
		tempstr = ft_strljoin(buffer[fd] + ft_check(buffer[fd]), "", 0);
		free(buffer[fd]);
		if (ft_strlen(tempstr))
			buffer[fd] = ft_strljoin(tempstr, "", 0);
		else
			buffer[fd] = 0;
		free(tempstr);
	}
	return (str);
}

static char	*readloop(int fd, char **buffer, char *str, char *tempbuffer)
{
	int		tempint;

	buffer[fd] = ft_strljoin(tempbuffer, "", 0);
	while (1)
	{
		str = ft_setstr(fd, buffer, str, 0);
		if (ft_check(str))
			return (str);
		tempint = read(fd - 1, tempbuffer, BUFFER_SIZE);
		tempbuffer[tempint] = '\0';
		free(buffer[fd]);
		buffer[fd] = ft_strljoin(tempbuffer, "", 0);
		if (tempint == 0)
		{
			str = ft_setstr(fd, buffer, str, ft_strlen(str));
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

char	*get_next_line(int fd)
{
	static char	**buffer;
	char		**tempstr;
	char		tempbuffer[BUFFER_SIZE + 1];
	char		*str;
	int			tempint;
	int			readlen;

	if (fd < 0)
		return (0);
	fd++;
	if (!buffer)
	{
		readlen = read(fd - 1, tempbuffer, BUFFER_SIZE);
		if (readlen == -1)
			return (0);
		buffer = malloc(sizeof(*buffer) * (fd + 2));
		buffer[fd + 1] = 0;
		buffer[0] = ft_itoa(fd);
		copy(buffer, fd, 3);
		// tempint = 1;
		// while (tempint <= fd)
		// {
		// 	buffer[tempint] = 0;
		// 	tempint++;
		// }
	}
	else
	{
		if (ft_atoi(buffer[0]) >= fd)
		{
			tempint = ft_check(buffer[fd]);
			if (tempint)
			{
				str = ft_strljoin("", buffer[fd], tempint);
				// tempstr = copy(buffer, fd, 0);
				// free(buffer);
				// buffer = copy(tempstr, fd, 1);
				// free(tempstr);
				tempstr = malloc(sizeof(*tempstr) * 2);
				tempstr[1] = 0;
				tempstr[0] = ft_strljoin(buffer[fd] + tempint, "", 0);
				free(buffer[fd]);
				buffer[fd] = ft_strljoin(tempstr[0], "", 0);
				free(tempstr[0]);
				free(tempstr);
				return (str);
			}
			readlen = read(fd - 1, tempbuffer, BUFFER_SIZE);
			if (readlen == -1)
				return (0);
		}
		else
		{
			readlen = read(fd - 1, tempbuffer, BUFFER_SIZE);
			if (readlen == -1)
				return (0);
			tempstr = copy(buffer, fd, 0);
			free(buffer);
			buffer = copy(tempstr, fd, 1);
			free(tempstr);
			buffer[0] = ft_itoa(fd);
		}
	}
	tempbuffer[readlen] = '\0';
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