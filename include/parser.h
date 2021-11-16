#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdbool.h>

# include "libft.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

# define ERROR				-1

# define ERR_UNO_BRACKET	"minishell: Syntax error: Unopened brackets"
# define ERR_UNC_BRACKET	"minishell: Syntax error: Unclosed brackets"
# define ERR_EMPTY_BRACKET	"minishell: Syntax error: Empty brackets"
# define ERR_REDIR			"minishell: Syntax error: Invalid redirection"
# define ERR_QUOTE			"minishell: Syntax error: Unclosed quotation mark"
# define ERR_LIST			"minishell: Syntax error: Incomplete command list"

# define ERR_PIPE			"minishell: Syntax error: Incomplete pipe"

# define TOK_TEXT			(1<<1)
# define TOK_S_QUOTE		(1<<10)
# define TOK_D_QUOTE		(1<<11)
# define TOK_REDIR_FILE		(1<<12)
# define TOK_CONNECTED		(1<<13)

# define TOK_BIN_OP			(1<<2)
# define TOK_PIPE			(1<<3)
# define TOK_O_BRACKET		(1<<4)
# define TOK_C_BRACKET		(1<<5)
# define TOK_REDIR			(1<<6)

# define PAR_SCMD			10
# define PAR_AND			11
# define PAR_OR				12
# define PAR_PIPE			13
# define PAR_O_BRACKET		14
# define PAR_C_BRACKET		15
# define PAR_PIPELINE		16
# define PAR_GROUP			17

# define PAR_L_SCMD			18
# define PAR_L_PG			19

# define WHITESPACES		" \t\n"
# define QUOT_MARKS			"\'\""

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

typedef struct s_token_content
{
	int		flags;
	char	*string;
}	t_c_token;

typedef struct s_scmd_content
{
	int		type;
	t_list	*l_argv;
	t_list	*l_redir;
}	t_c_scmd;

typedef struct s_pg_content
{
	int		type;
	t_list	*l_element;
}	t_c_pg;


/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// PARSER
t_list		*parser(t_list *l_token);

int			parser_scmd_set(t_c_scmd *c_element, t_list **l_token);
bool		parser_token_is_cmd(t_list *token);

t_c_scmd	*parser_c_scmd_get(t_list **l_token);
void		parser_c_scmd_destroy(void *c_element);
t_c_scmd	*scmd_content(t_list *element);

int			parser_list_group(t_list **l_pipeline);
t_list		*parser_list_group_merge(t_list *open);

int			parser_list_pipeline_pg(t_list **l_pg);
t_list		*parser_list_pipeline_merge(t_list *start);

t_list		*parser_list_pipeline(t_list *l_scmd);
t_c_pg		*pg_content(t_list *pg);
t_c_pg		*parser_c_pipeline_get(t_list **l_scmd);
int			parser_pipeline_set(t_c_pg *c_pipeline, t_list **l_scmd);

int			parser_get_scmd_type(t_list *token);
char		**parser_get_redirs(t_list *l_token, int i_redir);
char		**parser_get_redir_files(t_list *l_token, int i_redir);
int			parser_get_list_type(t_list *lst);

void		parser_printer_l_scmd_structure(t_list *l_scmd);
void		parser_printer_l_scmd(t_list *l_scmd, bool newline);
void		parser_printer_l_pipeline(t_list *l_pipeline);
void		parser_printer_l_pg(t_list *l_pg);
// void		parser_printer_l_pipeline(t_list *l_pipeline);
// void		parser_printer_l_pipeline_structure(t_list *l_pipeline);
void		parser_printer_l_pg_structure(t_list *l_pg);

void		parser_c_pg_destroy(void *c_pg);

// LEXER
void		lexer_token_bin_op(char *str, int *i, t_list **l_token);
void		lexer_token_redir(char *str, int *i, t_list **l_token);
void		lexer_token_pipe(char *str, int *i, t_list **l_token);
void		lexer_token_bracket(char *str, int *i, t_list **l_token);
int			lexer_token_text(char *str, int *i, t_list **l_token);
int			lexer_token_quote(char *str, int *i, t_list **l_token);

int			lexer_text_len(char *str);
int			lexer_quote_len(char *str);
int			lexer_special_len(char *chr);

t_list		*lexer_get_token(char *string, int type);
void		lexer_c_token_destroy(void *content);
t_c_token	*token_content(t_list *token);

void		lexer_printer(t_list *l_token);

#endif