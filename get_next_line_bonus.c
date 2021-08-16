#include "get_next_line_bonus.h"

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

	free(buffer[fd]);
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
			str = ft_strljoin(buffer[fd], "", 0);
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
			tempstr[0] = ft_strljoin(buffer[0], "", 0);
			while (tempint <= ft_atoi(buffer[0]) + 1)
			{
				if (buffer[tempint])
				{
					tempstr[tempint] = ft_strljoin(buffer[tempint], "", 0);
					free(buffer[tempint]);
				}
				else
					tempstr[tempint] = 0;
				tempint++;
			}
			free(buffer);
			buffer = malloc(sizeof(*buffer) * (fd + 2));
			buffer[fd + 1] = 0;
			buffer[0] = ft_strljoin(tempstr[0], "", 0);
			tempint = 1;
			while (tempint <= (ft_atoi(buffer[0])))
			{
				if (tempstr[tempint])
				{
					buffer[tempint] = ft_strljoin(tempstr[tempint], "", 0);
					free(tempstr[tempint]);
				}
				else
					buffer[tempint] = 0;
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
	if (!str)
		str = ft_strljoin("\0", "", 0);
	tempbuffer[readlen] = '\0';
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