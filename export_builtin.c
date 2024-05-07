/* ************************************************************************** */
/*	*/
/*	:::	  ::::::::   */
/*   export_builtin.c	   :+:	  :+:	:+:   */
/*	+:+ +:+	 +:+	 */
/*   By: atyurina <marvin@42.fr>	+#+  +:+	   +#+	*/
/*	+#+#+#+#+#+   +#+	   */
/*   Created: 2024/04/01 17:12:44 by atyurina	  #+#	#+#	 */
/*   Updated: 2024/04/01 17:12:46 by atyurina	 ###   ########.fr	   */
/*	*/
/* ************************************************************************** */

/*
you can export multiple variables:
export VAR1=value1 VAR2=value2 VAR3=value3 
(it does not have to be capslock. can be any) 
между ними могут быть рандомные стринги и они просто проигнортся. 
а везде где есть равно - становится в env
also is you pass just a string without = it just doesnt impact
*/

#include "minishell.h"

void	add_str_arr(char *var, char ***env)
{
	int		len;
	int		i;
	char	**dup_env;

	len = 0;
	i = 0;
	while ((*env)[len] != NULL)
		len++;
	dup_env = (char **)ft_malloc((len + 2) * sizeof(char *));
	while (i < len)
	{
		dup_env[i] = ft_strdup_ex((*env)[i]);
		i++;
	}
	dup_env[i] = ft_strdup_ex(var);
	dup_env[i + 1] = NULL;
	free_dup_env(*env);
	*env = dup_env;
}

void	export_arg(char *arg, char ***env)
{
	int		i;
	int		j;
	char	*var;
	int		exist;

	if (ft_strchr(arg, '=') == NULL)
		return ;
	else
		i = ft_strchr(arg, '=') - arg;
	exist = 0;
	var = (char *)ft_malloc((i + 1) * sizeof(char));
	var = ft_mystrncpy(var, arg, i);
	j = 0;
	while ((*env)[j] != NULL)
	{
		if (change_env_var(*env, var, i, arg + i) == 0)
		{
			exist = 1;
			break ;
		}
		j++;
	}
	if (exist == 0)
		add_str_arr(arg, env);
	free(var);
}

int	ft_export(char **argv, char ***env)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		export_arg(argv[i], env);
		i++;
	}
	return (0);
}
