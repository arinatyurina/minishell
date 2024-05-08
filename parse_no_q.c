/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_no_q.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:17:51 by rtavabil          #+#    #+#             */
/*   Updated: 2024/05/08 19:47:24 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_no_q(char *str, char **env, int *exit_code)
{
	char	**res;
	int		num;
	char	*final;

	res = ft_split_str(str);
	res = replace_env(res, env, exit_code);
	num = get_len_tokens(res);
	final = merge_tokens(num, res);
	free_double_array(res);
	return (final);
}
