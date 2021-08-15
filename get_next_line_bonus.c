#include "get_next_line_bonus.h"
#include <stdio.h>

static char	*ft_setstr(int fd, char **buffer, char *str, int tempint)
{
	char	*tempstr;

	tempstr = ft_strdup(str);
	free(str);
	str = malloc(sizeof(*str) * tempint);
	ft_strlcpy(str, tempstr, (ft_strlen(tempstr) + 1));
	ft_strlcat(str, buffer[fd], tempint);
	free(tempstr);
	return (str);
}

static char	*readloop(int fd, char **buffer, char *str)
{
	int		tempint;
	char	tempbuffer[BUFFER_SIZE + 1];

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
			ft_strlcpy(buffer[fd], buffer[fd] + tempint,
				ft_strlen(buffer[fd] + tempint) + 1);
			if (buffer[fd][0] == '\0')
			{
				printf("true\n");
				free(buffer[fd]);
				buffer[fd] = 0;
			}
			if (buffer[fd])
				printf("not blank\n");
			printf("return 1\n");
			return (str);
		}
		tempint = read(fd, tempbuffer, BUFFER_SIZE);
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
		tempint = 1;
		while (tempint <= fd)
		{
			buffer[tempint] = 0;
			tempint++;
		}
	}
	else
	{
		if (ft_atoi(buffer[0]) >= fd)
		{
			tempint = ft_check(buffer[fd]);
			if (tempint)
			{
				str = malloc(sizeof(*str) * (tempint + 1));
				ft_strlcpy(str, buffer[fd], tempint + 1);
				tempstr = malloc(sizeof(*tempstr) * 2);
				tempstr[1] = 0;
				tempstr[0] = ft_strdup(buffer[fd] + tempint);
				free(buffer[fd]);
				buffer[fd] = ft_strdup(tempstr[0]);
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
			
			tempint = 1;
			tempstr = malloc(sizeof(*tempstr) * (ft_atoi(buffer[0]) + 2));
			tempstr[ft_atoi(buffer[0]) + 1] = 0; 
			while (tempint <= ft_atoi(buffer[0]) + 1)
			{
				if (buffer[tempint])
				{
					tempstr[tempint] = ft_strdup(buffer[tempint]);
					free(buffer[tempint]);
				}
				tempint++;
			}
			free(buffer);
			buffer = malloc(sizeof(*buffer) * (fd + 2));
			buffer[fd + 1] = 0;
			tempint = 1;
			while (tempint <= ft_atoi(buffer[0]) + 1)
			{
				if (tempstr[tempint])
				{
					buffer[tempint] = ft_strdup(tempstr[tempint]);
					free(tempstr[tempint]);
				}
				tempint++;
			}
			while (tempint <= fd)
			{
				buffer[tempint] = 0;
				tempint++;
			}
			free(tempstr);
			buffer[0] = ft_itoa(fd);
		}
	}
	tempbuffer[readlen] = '\0';
	if (buffer[fd])
	{
		printf("not blank");
		str = ft_strdup(buffer[fd]);
	}
	else
		str = ft_strdup("\0");
	free(buffer[fd]);
	buffer[fd] = ft_strdup(tempbuffer);
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