#include "get_next_line_bonus.h"

static char	**copy(char **str1, int size, int choice, int tempint)
{
	char	**str2;

	if (choice != 2)
	{
		str2 = malloc(sizeof(*str2) * (size + 2));
		str2[size + 1] = 0;
		str2[0] = ft_strljoin(str1[0], "", 0);
		free(str1[0]);
		while (tempint <= ft_atoi(str2[0]) + 1)
		{
			if (str1[tempint])
			{
				str2[tempint] = ft_strljoin(str1[tempint], "", 0);
				free(str1[tempint++]);
			}
			else
				str2[tempint++] = 0;
		}
		free(str1);
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

static char	*exist(char **buffer, int fd, int tempint, int choice)
{
	char	**tempstr;
	char	*str;

	if (choice == 1)
	{
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
	buffer[fd + 1] = 0;
	buffer[0] = ft_itoa(fd);
	copy(buffer, fd, 2, 1);
	return (0);
}

static void	get_next_line2(int fd, char ***buffer, int choice)
{
	char	**tempstr;

	if (choice == 1)
	{
		tempstr = copy(*buffer, fd, 0, 1);
		*buffer = copy(tempstr, fd, 1, 1);
		free(*buffer[0]);
		*buffer[0] = ft_itoa(fd);
	}
}

char	*get_next_line(int fd)
{
	static char	**buffer;
	char		tempbuffer[BUFFER_SIZE + 1];
	int			tempint;
	char		*str;

	if (buffer && ft_atoi(buffer[0]) >= fd && multi(buffer[fd], 1))
		return (exist(buffer, fd, multi(buffer[fd], 1), 1));
	tempint = read(fd, tempbuffer, BUFFER_SIZE);
	if (fd++ < 0 || tempint == -1)
		return (0);
	if (buffer && ft_atoi(buffer[0]) < fd)
		get_next_line2(fd, &buffer, 1);
	if (!buffer)
	{
		buffer = malloc(sizeof(*buffer) * (fd + 2));
		exist(buffer, fd, tempint, 0);
	}
	tempbuffer[tempint] = '\0';
	if ((buffer)[fd])
		str = ft_strljoin((buffer)[fd], "", 0);
	else
		str = ft_strljoin("\0", "", 0);
	free((buffer)[fd]);
	// get_next_line2(fd, &buffer, &str, 0);
	return (readloop(fd, buffer, str, tempbuffer));
}

/* #include <stdio.h>
int main()
{
	int fd[4];
	char *testr;

	fd[0] = open("files/41_with_nl", O_RDWR);
	testr = get_next_line(1000);
	printf("Main output: %s",  testr);
	printf("---main newline test---\n");
	free(testr);

	testr = get_next_line(fd[0]);
	printf("Main output: %s",  testr);
	printf("---main newline test---\n");
	free(testr);

	fd[1] = open("files/42_with_nl", O_RDWR);
	testr = get_next_line(1001);
	printf("Main output: %s",  testr);
	printf("---main newline test---\n");
	free(testr);

	testr = get_next_line(fd[1]);
	printf("Main output: %s",  testr);
	printf("---main newline test---\n");
	free(testr);

	fd[2] = open("files/43_with_nl", O_RDWR);
	testr = get_next_line(1002);
	printf("Main output: %s",  testr);
	printf("---main newline test---\n");
	free(testr);

	testr = get_next_line(fd[2]);
	printf("Main output: %s",  testr);
	printf("---main newline test---\n");
	free(testr);

	testr = get_next_line(1003);
	printf("Main output: %s",  testr);
	printf("---main newline test---\n");
	free(testr);

	testr = get_next_line(fd[0]);
	printf("Main output: %s",  testr);
	printf("---main newline test---\n");
	free(testr);
} */