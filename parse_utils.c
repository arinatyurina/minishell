/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:45:31 by rtavabil          #+#    #+#             */
/*   Updated: 2024/05/08 19:41:49 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_alphanum(char c)
{
	if (((c >= 48) && (c <= 57)) || ((c >= 97 && c <= 122)) \
		|| (c == '_') || ((c >= 65) && (c <= 90)))
		return (1);
	return (0);
}

int	is_special_str(char *str)
{
	if (!ft_strcmp(str, ">"))
		return (1);
	if (!ft_strcmp(str, "<"))
		return (1);
	if (!ft_strcmp(str, ">>"))
		return (1);
	if (!ft_strcmp(str, "<<"))
		return (1);
	if (!ft_strcmp(str, "|"))
		return (1);
	if (!ft_strcmp(str, "$"))
		return (1);
	return (0);
}

int	is_empty_str(char *str)
{
	int	flag;

	flag = 0;
	if (str != NULL)
	{
		while (*str)
		{
			if (!is_space(*str))
				flag = 1;
			str++;
		}
	}
	if (!flag)
		return (1);
	return (0);
}

char	*remove_quotes(char *str)
{
	int		len;
	char	*ret;

	len = ft_strlen(str);
	ret = (char *)malloc((len - 1) * sizeof(char));
	ft_strlcpy(ret, str + 1, len - 1);
	return (ret);
}

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
