#ifndef GLOBAL_H
# define GLOBAL_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>

# include "libft.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

# define ERROR				-1

# define SHELL_NAME			"minishell"
# define ERR_NO_MEM			"out of virtual memory"

# define UNUSED				__attribute__((unused))

/* ************************************************************************** */
/* GLOBAL VARIABLES															  */
/* ************************************************************************** */

extern char	**g_env;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

int		print_error(char *s1, char *s2, char *s3, char *message);
int		split_count(char **argv);

int		lst_node_remove(t_list **lst, t_list *node, void (*del)(void *));
t_list	*lst_node_prev(t_list *lst, t_list *node);
int		lst_relink(t_list **lst, t_list *node, t_list *start, t_list *end);

int		split_append_str(char ***split, char *str);

int		split_remove_str(char ***split, char *remove_str);
int		split_replace_str(char ***split, char *old_str, char *new_str);
int		split_contains_str(char **split, char *str);

#endif
