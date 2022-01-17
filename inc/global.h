#ifndef GLOBAL_H
# define GLOBAL_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>
# include <errno.h>

# include "libft.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

# define ERROR		-1

# define SHELL_NAME	"minishell"
# define DEBUG_ENV	"DEBUG"

/* ************************************************************************** */
/* GLOBAL VARIABLES															  */
/* ************************************************************************** */

extern char	**g_env;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

int		print_error(char *s1, char *s2, char *s3, char *message);
int		print_error_errno(char *s1, char *s2, char *s3);

char	*str_append_str(char *str, char *append);
char	*str_append_chr(char *str, char append);
char	str_last_chr(char *str);

int		lst_node_remove(t_list **lst, t_list *node, void (*del)(void *));
t_list	*lst_node_prev(t_list *lst, t_list *node);
int		lst_relink(t_list **lst, t_list *node, t_list *start, t_list *end);

int		split_count(char **argv);
int		split_append_str(char ***split, char *str);
int		split_remove_str(char ***split, char *remove_str);
int		split_replace_str(char ***split, char *old_str, char *new_str);
void	split_sort(char **split);

char	*minishell_get_next_line(int fd);

#endif
