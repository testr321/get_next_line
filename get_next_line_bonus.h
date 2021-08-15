#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*get_next_line(int fd);

size_t	ft_check(const char *s);

size_t	ft_strlen(const char *s);
char	*ft_strljoin(char const *s1, char const *s2, size_t size);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);

size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strdup(const char *s);

#endif