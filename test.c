#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (*s)
	{
		s++;
		len++;
	}
	return (len);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && (i < n))
	{
		if (s1[i] < s2[i])
			return (-1);
		if (s2[i] < s1[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strnstr(char *big, char *little, int len)
{
	int	i;

	if (*little == 0)
		return (big);
	i = ft_strlen(little);
	while (*big && i <= len)
	{
		if (*big == *little && ft_strncmp(big, little, i) == 0)
			return (big);
		big++;
		len--;
	}
	return ((void *)0);
}

// int	is_space(int c)
// {
// 	c = (unsigned char)c;
// 	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
// 		|| c == ' ')
// 		return (1);
// 	return (0);
// }

// int	is_next_string_space(char *token, char *user_input)
// {
// 	char	*ptr;
// 	char	*ch;

// 	ch = "\0";
// 	ptr = ft_strnstr(user_input, token, ft_strlen(user_input));
// 	printf("pointer is at %s   token len is %d\n", ptr, ft_strlen(user_input));
// 	if (ptr)
// 		ch = ptr + ft_strlen(token);
// 	if (is_space(*ch))
// 		return(1);
// 	return (0);
// }

int	ft_strchrin(char *s, int c)
{
	int		i;
	char	ch;

	ch = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == ch)
			return (i);
		i++;
	}
	if (s[i] == ch)
		return (i);
	return (-1);
}

int	is_alphanum(char c)
{
	if (((c >= 48) && (c <= 57)) || ((c >=97 && c <= 122)) \
		|| (c == '_') || ((c >= 65) && (c <= 90)))
		return (1);
	return (0);
}

int	find_end_exp(char *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (is_alphanum(*s))
		{
			i++;
			break;
		}
		s++;
	}
	return (i);
}

void	ft_bzero(void *dest, int byte_sizes)
{
	char	*temp_dest;

	temp_dest = (char *)dest;
	while (byte_sizes--)
		*(temp_dest++) = 0;
}

void	*ft_calloc(int num, int byte_sizes)
{
	void	*result;

	result = malloc(num * byte_sizes);
	if (!result)
		return (NULL);
	ft_bzero(result, num * byte_sizes);
	return (result);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*subs;
	int		i;

	if (start >= ft_strlen(s))
	{
		subs = ft_calloc(1, sizeof(char));
		if (!subs)
			return (NULL);
		return (subs);
	}
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	subs = (char *)malloc((len + 1) * sizeof(char));
	if (!subs)
		return ((void *)0);
	i = 0;
	while (i < len && s[start + i])
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}

static int	ft_count_words_str(char *s)
{
	int		words;
	int		flag;

	words = 0;
	flag = 1;
	while (*s)
	{
		if (((*s == '$') && (*(s + 1) == '?')) \
			|| ((*s == '$') && (is_alphanum(*(s + 1)))))
		{
			flag = 1;
			words++;
			s++;
		}
		if (*s == '$' && *(s + 1) == '$')
			return (-1);
		if((flag == 1) && ((!is_alphanum(*s)) && *s != '\0' && *s != '\"'))
		{
			flag = 0;
			words++;
			s++;
		}
		s++;
	}
	return (words);
}

char	**ft_split_str(char *s)
{
	char	**res;
	int		i;
	int		start;

	res = (char **)malloc((ft_count_words_str(s) + 1) * sizeof(char *));
	i = 0;
	while (s[i])
	{
		start = i;
		if (s[i] == '$' && is_alphanum(s[i + 1]))
		{
			i++;
			while (is_alphanum(s[i]) && s[i])
				i++;
		}
		else if (s[i] == '$' && s[i + 1] == '?')
			i += 2;
		else
			while (s[i] && !(s[i] == '$' && is_alphanum(s[i + 1])) \
					&& !((s[i] == '$') && (s[i + 1] == '?')))
				i++;
		*res++ = ft_substr(s, start, i - start);
	}
	*res = NULL;
	return (res - ft_count_words_str(s));
}

void	*ft_memcpy(void *dest, void *src, int n)
{
	char	*new_dest;
	char	*new_src;
	int	i;

	new_dest = (char *)dest;
	new_src = (char *)src;
	i = 0;
	while (i < n)
	{
		*(new_dest + i) = *(new_src + i);
		i++;
	}
	return (dest);
}

int	ft_strlcpy(char *dst, char *src, int size)
{
	int	src_len;

	src_len = ft_strlen(src);
	if (src_len + 1 < size)
	{
		ft_memcpy(dst, src, src_len + 1);
	}
	else if (size != 0)
	{
		ft_memcpy(dst, src, size - 1);
		dst[size - 1] = '\0';
	}
	return (src_len);
}

char	*remove_quotes(char *str)
{
	int		len;
	char	*ret;

	len = ft_strlen(str);
	ret = (char *)malloc((len - 1) * sizeof(char));
	ft_strlcpy(ret, str + 1, len - 1);
	//free(str);
	return (ret);
}

// int	get_env_value(char **token, char **env)
// {
	
// }

// int	replace_env(char **tokens, char **env)
// {
// 	int	res;

// 	res = 0;
// 	while (*tokens)
// 	{
// 		if (**tokens == '$')
// 			res += token_env(tokens, env);
// 		else 
// 			res += ft_strlen(*tokens);
// 		tokens++;
// 	}
// 	return (res);
// }

int	main()
{
	char	*str = {"\"$     $OLDPWD  lalalalal $OLDPWD$OL     $? $OLDPWD    a$\""};
	char	*token = {"$OLDPWD"};
	char	**res;

	printf("str = %s\n", str);
	printf("num of words %d\n", ft_count_words_str(str));
	str = remove_quotes(str);
	printf("str after removed quotes |%s|\n", str);
	res = ft_split_str(str);
	printf("res is %s\n", *res);
	while (*res)
	{
		printf("|%s|\n", *res);
		res++;
	}
}