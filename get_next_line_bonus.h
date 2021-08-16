#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*get_next_line(int fd);

size_t	multi(const char *s, int choice);
char	*ft_strljoin(char const *s1, char const *s2, size_t size);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);

#endif