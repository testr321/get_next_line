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

char    *ft_strdup(const char *s)
{
    char    *str;
    int    len;

    len = ft_strlen(s);
    str = malloc(sizeof(*s) * (len + 1));
    if (!str)
        return (0);
    str[len] = '\0';
    while (len >= 0)
    {
        str[len] = s[len];
        len--;
    }
    return (str);
}

size_t    ft_strlen(const char *s)
{
    size_t    len;

    len = 0;
    while (s[len])
        len++;
    return (len);
}

size_t    ft_strlcat(char *dest, const char *src, size_t size)
{
    size_t    i;
    size_t    j;
    size_t    final;

    i = 0;
    j = 0;
    while (dest[i])
        i++;
    final = i;
    if (size < final)
        final = size;
    while (src[j] && i < (size - 1) && size != 0)
    {
        dest[i] = src[j];
        j++;
        i++;
    }
    dest[i] = '\0';
    i = 0;
    while (src[i])
        i++;
    return (final + i);
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
