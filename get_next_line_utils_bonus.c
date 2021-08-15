#include "get_next_line_bonus.h"

size_t    ft_check(const char *s)
{
    size_t    i;

	if (!s)
		return (0);
    i = 0;
    while (s[i])
    {
        if (s[i] == '\n')
            return (i + 1);
        i++;
    }
    return (0);
}

size_t    ft_strlen(const char *s)
{
    size_t    len;

    len = 0;
    while (s[len])
        len++;
    return (len);
}

char	*ft_strljoin(char const *s1, char const *s2, size_t size)
{
	char	*str;
	size_t	len;
	size_t	i;
	size_t	j;

	len = ft_strlen(s1) + size + 1;
	if (ft_strlen(s2) < size)
		len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(sizeof(*s1) * len);
	if (!str)
		return (0);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] && j + i < (len - 1))
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

int    ft_atoi(const char *nptr)
{
    int        result;
    int        neg;
    size_t    sign;
    size_t    i;

    result = 0;
    sign = 0;
    neg = 1;
    i = 0;
    while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
        i++;
    while (nptr[i] == '-' || nptr[i] == '+')
    {
        if (nptr[i++] == '-')
            neg = -1;
        if (++sign > 1)
            return (0);
    }
    while (nptr[i] >= '0' && nptr[i] <= '9')
    {
        result *= 10;
        result += (nptr[i++] - 48);
    }
    return (result * neg);
}

char    *ft_itoa(int n)
{
    int save;
    size_t    len;
    char    *str;

    save = n;
    len = 0;
    while (save > 0)
    {
        save /= 10;
        len++;
    }
	str = malloc(sizeof(*str) * (len + 1));
    if (!str)
        return (0);
    str[len--] = '\0';
    while (n > 0)
    {
        str[len] = (n % 10) + 48;
        n /= 10;
        len--;
    }
    return (str);
}
