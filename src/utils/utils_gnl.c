#include "global.h"

static char	*gnl_free_line(char *line);

char	*get_next_line(int fd)
{
	int		check;
	char	buffer;
	char	*line;

	line = ft_strdup("");
	if (line == NULL)
		return (NULL);
	check = read(fd, &buffer, 1);
	if (check == -1 || check == 0)
		return (gnl_free_line(line));
	while (check > 0)
	{
		line = str_append_chr(line, buffer);
		if (line == NULL)
			return (NULL);
		if (buffer == '\n')
			return (line);
		check = read(fd, &buffer, 1);
	}
	if (check == -1)
		return (gnl_free_line(line));
	return (line);
}

static char	*gnl_free_line(char *line)
{
	free(line);
	return (NULL);
}