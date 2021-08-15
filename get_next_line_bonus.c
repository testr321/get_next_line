#include "get_next_line_bonus.h"
#include <stdio.h>

static char	*ft_setstr(int fd, char **buffer, char *str, int tempint)
{
	char	*tempstr;

	// printf("tmepint %d\n", tempint);
	tempstr = ft_strdup(str);
	free(str);
	str = malloc(sizeof(*str) * tempint);
	ft_strlcpy(str, tempstr, (ft_strlen(tempstr) + 1));
	// printf("2 %s\n", buffer[fd]);
	ft_strlcat(str, buffer[fd], tempint);
	free(tempstr);
	// printf("2 %s\n", str);
	return (str);
}

static char	*readloop(int fd, char **buffer, char *str)
{
	int		tempint;
	char	tempbuffer[BUFFER_SIZE + 1];

	// printf("1 %s\n", buffer[fd]);
	tempint = 0;
	while (1)
	{
		if (!ft_check(buffer[fd]))
			tempint += ft_strlen(str) + ft_strlen(buffer[fd]) + 1;
		else
			tempint = ft_strlen(str) + ft_check(buffer[fd]) + 1;
		str = ft_setstr(fd, buffer, str, tempint);
		// printf("string: %s\n", str);
		if (ft_check(buffer[fd]))
		{
			tempint = ft_check(buffer[fd]);
			// tempstr = ft_strdup(buffer[fd] + tempint);
			// free(buffer[fd]);
			// buffer[fd] = ft_strdup(tempstr);
			// free(tempstr);
			ft_strlcpy(buffer[fd], buffer[fd] + tempint,
				ft_strlen(buffer[fd] + tempint) + 1);
			// printf("leftover: %s\n", buffer[fd]);
			return (str);
		}
		tempint = read(fd, tempbuffer, BUFFER_SIZE);
		tempbuffer[tempint] = '\0';
		if (tempint == -1 || (tempint == 0 && !*str))
		{
			free(str);
			free(buffer[fd]);
			buffer[fd] = ft_strdup("\0");
			return (0);
		}
		free(buffer[fd]);
		buffer[fd] = ft_strdup(tempbuffer);
		if (tempint == 0 && *str)
		{
			str = ft_setstr(fd, buffer, str, ft_strlen(str) + 1);
			free(buffer[fd]);
			buffer[fd] = ft_strdup("\0");
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
		buffer = malloc(sizeof(*buffer) * (fd + 2));
		buffer[fd + 1] = 0;
		while (tempint < fd + 1)
		{
			buffer[tempint] = ft_strdup("\0");
			tempint++;
		}
	}
	else
	{
		// printf("enter yes buffer\n");
		while (buffer[tempint])
			tempint++;
		// printf("buffer len: %d\n", tempint);
		if (tempint >= (fd + 1))
		{
			// printf("fd exist\n");
			tempint = ft_check(buffer[fd]);
			if (tempint)
			{
				// printf("enter newline found\n");
				str = malloc(sizeof(*str) * (tempint + 1));
				ft_strlcpy(str, buffer[fd], tempint + 1);
				tempstr = malloc(sizeof(*tempstr) * 2);
				tempstr[1] = 0;
				tempstr[0] = ft_strdup(buffer[fd] + tempint);
				free(buffer[fd]);
				buffer[fd] = ft_strdup(tempstr[0]);
				free(tempstr[0]);
				free(tempstr);
				// printf("newline found\n");
				return (str);
			}
			readlen = read(fd, tempbuffer, BUFFER_SIZE);
			if (readlen == -1)
			{
				// printf("exit read fail2\n");
				return (0);
			}
		}
		else
		{
			// printf("fd no exist\n");
			readlen = read(fd, tempbuffer, BUFFER_SIZE);
			if (readlen == -1)
			{
				// printf("exit read fail3\n");
				return (0);
			}
			tempstr = malloc(sizeof(*tempstr) * (tempint + 1));
			tempstr[tempint] = 0;
			tempint--;
			while (tempint >= 0)
			{
				// printf("tempint %d\n", tempint);
				if (buffer[tempint][0])
				{
					// printf("buffer not empty\n");
					// printf("buffer: %s\n", buffer[tempint]);
					tempstr[tempint] = ft_strdup(buffer[tempint]);
				}
				else
				{
					// printf("buffer empty\n");
					tempstr[tempint] = ft_strdup("\0");
				}
				tempint--;
			}
			tempint = 0;
			while (buffer[tempint])
			{
				free(buffer[tempint]);
				tempint++;
			}
			free(buffer);
			tempint = 0;
			buffer = malloc(sizeof(*buffer) * (fd + 2));
			buffer[fd + 1] = 0;
			while (tempstr[tempint])
			{
				buffer[tempint] = ft_strdup(tempstr[tempint]);
				free(tempstr[tempint]);
				tempint++;
			}
			while (tempint < fd + 1)
			{
				buffer[tempint] = ft_strdup("\0");
				free(tempstr[tempint]);
				tempint++;
			}
			free(tempstr);
		}
	}
	if (buffer[fd])
	{
		tempint = ft_strlen(buffer[fd]);
		str = malloc(sizeof(*str) + (tempint + 1));
		ft_strlcpy(str, buffer[fd], tempint + 1);
	}
	else
		str = ft_strdup("\0");
	tempbuffer[readlen] = '\0';
	free(buffer[fd]);
	buffer[fd] = ft_strdup(tempbuffer);

/* 	printf("\n\nTESTR\n");
	tempint = 0;
	while (buffer[tempint])
	tempint++;
	tempint--;
	while (tempint >= 0)
	{
		printf("tempint %d\n", tempint);
		if (buffer[tempint][0])
		{
			printf("buffer not empty\n");
			printf("buffer: %s\n", buffer[tempint]);
		}
		else
		{
			printf("buffer empty\n");
		}
		tempint--;
	}
	printf("TESTR\n\n\n"); */

	// printf("%s\n", tempbuffer);
	// printf("%s\n", buffer[fd]);
	return (readloop(fd, buffer, str));
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