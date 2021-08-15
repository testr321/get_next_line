#include "get_next_line_bonus.h"
#include <stdio.h>

static char	*ft_setstr(int fd, char **buffer, char *str, int tempint)
{
	char	*tempstr;

	tempstr = ft_strdup(str);
	free(str);
	str = ft_strdup(tempstr);
	ft_strlcat(str, buffer[fd], tempint);
	free(tempstr);
	return (str);
}

static char	*readloop(int fd, char **buffer, char *str)
{
	int		tempint;
	char	tempbuffer[BUFFER_SIZE + 1];
	char	*tempstr;

	tempint = 0;
	while (1)
	{
		if (!ft_check(buffer[fd]))
			tempint += ft_strlen(str) + ft_strlen(buffer[fd]) + 1;
		else
			tempint = ft_strlen(str) + ft_check(buffer[fd]) + 1;
		str = ft_setstr(fd, buffer, str, tempint);
		if (ft_check(buffer[fd]))
		{
			tempint = ft_check(buffer[fd]);
			tempstr = ft_strdup(buffer[fd] + tempint);
			free(buffer[fd]);
			buffer[fd] = ft_strdup(tempstr);
			free(tempstr);
			return (str);
		}
		tempint = read(fd - 1, tempbuffer, BUFFER_SIZE);
		tempbuffer[tempint] = '\0';
		if (tempint == -1 || (tempint == 0 && !*str))
		{
			free(str);
			free(buffer[fd]);
			buffer[fd] = 0;
			return (0);
		}
		free(buffer[fd]);
		buffer[fd] = ft_strdup(tempbuffer);
		if (tempint == 0 && *str)
		{
			str = ft_setstr(fd, buffer, str, ft_strlen(str) + 1);
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

	// printf("fd: %d\n", fd);
	if (fd < 0)
		return (0);
	tempint = 0;
	if (!buffer)
	{
		// printf("enter no buffer\n");
		readlen = read(fd, tempbuffer, BUFFER_SIZE);
		if (readlen == -1)
		{
			// printf("exit read fail1\n");
			return (0);
		}
		buffer = malloc(sizeof(*buffer) * (fd + 3));
		buffer[0] = ft_itoa(fd);
		buffer[fd + 2] = 0;
		tempint = 1;
		while (tempint < (fd + 2))
		{
			buffer[tempint] = 0;
			tempint++;
		}
	}
	else
	{
		// printf("enter yes buffer\n");
		if (ft_atoi(buffer[0]) < fd)
		{
			// printf("fd no exist\n");
			readlen = read(fd, tempbuffer, BUFFER_SIZE);
			if (readlen == -1)
				return (0);
			tempstr = malloc(sizeof(*tempstr) * (ft_atoi(buffer[0]) + 2));
			tempint = 1;
			while (tempint < ft_atoi(buffer[0]) + 2)
			{
				if (buffer[tempint])
				{
					tempstr[tempint] = ft_strdup(buffer[tempint]);
					free(buffer[tempint]);
				}
				tempint++;
			}
			free(buffer);
			buffer = malloc(sizeof(*buffer) * fd + 3);
			while (tempint)
			{
				if (tempstr[tempint])
				{
					buffer[tempint] = ft_strdup(tempstr[tempint]);
					free(tempstr[tempint]);
				}
				else
					buffer[tempint] = 0;
				tempint--;
			}
			free(tempstr);
			buffer[0] = ft_itoa(fd);
		}
		else
		{
			tempint = ft_check(buffer[fd + 1]);
			if (tempint)
			{
				str = ft_strdup(buffer[fd + 1]);
				tempstr = malloc(sizeof(*tempstr) * 2);
				tempstr[1] = 0;
				tempstr[0] = ft_strdup(buffer[fd + 1] + tempint);
				free(buffer[fd + 1]);
				buffer[fd + 1] = ft_strdup(tempstr[0]);
				free(tempstr[0]);
				free(tempstr);
				return (str);
			}
			readlen = read(fd, tempbuffer, BUFFER_SIZE);
			if (readlen == -1)
				return (0);
		}
	}
	if (buffer[fd + 1])
	{
		tempint = ft_strlen(buffer[fd + 1]);
		str = ft_strdup(buffer[fd + 1]);
	}
	else
		str = ft_strdup("\0");
	tempbuffer[readlen] = '\0';
	free(buffer[fd + 1]);
	buffer[fd + 1] = ft_strdup(tempbuffer);
	return (readloop(fd + 1, buffer, str));
}

/* #include <stdio.h>
int main()
{
	int fd[4];
	fd[0] = open("files/multiple_nlx5", O_RDWR);
	fd[1] = open("files/42_no_nl", O_RDWR);
	char *testr;

	testr = get_next_line(fd[0]);
	printf("Main output1: %s",  testr);
	printf("---main newline test---\n");
	free(testr);

	testr = get_next_line(fd[0]);
	printf("Main output1: %s",  testr);
	printf("---main newline test---\n");
	free(testr);

	testr = get_next_line(fd[0]);
	printf("Main output1: %s",  testr);
	printf("---main newline test---\n");
	free(testr);

	testr = get_next_line(fd[0]);
	printf("Main output1: %s",  testr);
	printf("---main newline test---\n");
	free(testr);

	testr = get_next_line(fd[0]);
	printf("Main output1: %s",  testr);
	printf("---main newline test---\n");
	free(testr);

	// testr = get_next_line(1000);
	// printf("Main output2: %s",  testr);
	// printf("---main newline test---\n");
	// free(testr);

	// testr = get_next_line(fd[1]);
	// printf("Main output1: %s",  testr);
	// printf("---main newline test---\n");
	// free(testr);

	// testr = get_next_line(1001);
	// printf("Main output2: %s",  testr);
	// printf("---main newline test---\n");
	// free(testr);

 	// testr = get_next_line(fd);
	// printf("Main output1: %s",  testr);
	// printf("---main newline test---\n");
	// free(testr);

	// testr = get_next_line(fd);
	// printf("Main output1: %s",  testr);
	// printf("---main newline test---\n");
	// free(testr);

	// testr = get_next_line(fd);
	// printf("Main output1: %s",  testr);
	// printf("---main newline test---\n");
	// free(testr);

	// testr = get_next_line(fd);
	// printf("Main output1: %s",  testr);
	// printf("---main newline test---\n");
	// free(testr);

	// testr = get_next_line(fd);
	// printf("Main output1: %s",  testr);
	// printf("---main newline test---\n");
	// free(testr);

	// testr = get_next_line(fd);
	// printf("Main output1: %s",  testr);
	// printf("---main newline test---\n");
	// free(testr);
} */