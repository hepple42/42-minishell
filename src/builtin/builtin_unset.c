#include "builtin.h"
#include "env.h"

int	builtin_unset(int argc __attribute((unused)), char **argv)
{
	int	i;
	int	status;

	status = 0;
	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '\0' || ft_strchr(argv[i], '=')
			|| ft_strchr(argv[i], '?') || ft_strchr(argv[i], '$')
			|| ft_strchr(argv[i], '/'))
		{
			print_error(SHELL_NAME, "unset", argv[i], "not a valid identifier");
			status = EXIT_FAILURE;
		}
		else
			env_unset_var(argv[i]);
		i++;
	}
	return (status);
}
