#include "env.h"

int	env_unset_var(char *name)
{
	char	*env_var;

	env_var = env_find_var(name);
	if (env_var == NULL)
		return (ERROR);
	split_remove_str(&g_env, env_var);
	return (0);
}

int	env_put_var(char *str)
{
	int		i;
	int		status;
	char	*new_var;
	char	*old_var;

	if (str == NULL || ft_strchr(str, '=') == NULL)
		return (ERROR);
	new_var = ft_strdup(str);
	if (new_var == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
	old_var = env_find_var(str);
	status = split_replace_str(&g_env, old_var, new_var);
	if (status == ERROR)
	{
		status = split_append_str(&g_env, new_var);
		if (status == ERROR)
			return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
	}
	return (0);
}

int		env_set_env(char *name, char *value)
{
	char	*tmp;
	char	*var_str;

	if (name == NULL || value == NULL)
		return (ERROR);
	tmp = ft_strjoin(name, "=");
	if (tmp == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
	var_str = ft_strjoin(tmp, value);
	free(tmp);
	if (var_str == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
	return (env_put_var(var_str));
}