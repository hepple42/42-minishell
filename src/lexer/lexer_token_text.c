#include "lexer.h"

static int	lexer_text_len(char *str);
static int	lexer_quote_len(char *str);
static int	lexer_other_len(char *chr);

int	lexer_token_text(char *str, int *i, t_list **l_token)
{
	int		len;
	t_list	*token;

	len = lexer_text_len(&str[*i]);
	if (len < 0)
		return (ERROR);
	if (len > 0)
	{
		token = token_get(ft_substr(str, *i, len), TOK_TEXT);
		ft_lstadd_back(l_token, token);
		*i += len;
		if (!ft_strchr(WHITESPACES, str[*i]) && lexer_other_len(&str[*i]) == 0)
			token_content(token)->flags |= TOK_CONNECTED;
	}
	return (0);
}

int	lexer_token_quote(char *str, int *i, t_list **l_token)
{
	int		len;
	t_list	*token;

	len = lexer_quote_len(&str[*i]);
	if (len < 0)
		return (ERROR);
	if (len > 0)
	{
		if (str[*i] == '\'')
			token = token_get(ft_substr(str, *i + 1, len - 2),
					TOK_TEXT | TOK_S_QUOTE);
		else
			token = token_get(ft_substr(str, *i + 1, len - 2),
					TOK_TEXT | TOK_D_QUOTE);
		ft_lstadd_back(l_token, token);
		*i += len;
		if (ft_strchr(WHITESPACES, str[*i]) == NULL
			&& lexer_other_len(&str[*i]) == 0)
			token_content(token)->flags |= TOK_CONNECTED;
	}
	return (0);
}

static int	lexer_text_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(WHITESPACES, str[i]))
			break ;
		else if (lexer_other_len(&str[i]) > 0)
			break ;
		else if (ft_strchr(QUOT_MARKS, str[i]))
			break ;
		i++;
	}
	return (i);
}

static int	lexer_quote_len(char *str)
{
	int		i;
	char	mark;

	if (str == NULL || *str == '\0')
		return (0);
	if (ft_strchr(QUOT_MARKS, str[0]) == NULL)
		return (0);
	mark = str[0];
	i = 1;
	while (str[i])
	{
		if (str[i] == mark)
			break ;
		i++;
	}
	if (str[i] != mark)
	{
		print_error(ERR_QUOTE);
		return (ERROR);
	}
	return (i + 1);
}

static int	lexer_other_len(char *chr)
{
	if (*chr == '(' || *chr == ')')
		return (1);
	else if (*chr == '<' && *(chr + 1) != '<')
		return (1);
	else if (*chr == '<' && *(chr + 1) == '<')
		return (2);
	else if (*chr == '>' && *(chr + 1) != '>')
		return (1);
	else if (*chr == '>' && *(chr + 1) == '>')
		return (2);
	else if (*chr == '|' && *(chr + 1) != '|')
		return (1);
	else if (*chr == '|' && *(chr + 1) == '|')
		return (2);
	else if (*chr == '&' && *(chr + 1) == '&')
		return (2);
	return (0);
}