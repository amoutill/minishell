/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutill <amoutill@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:15:00 by amoutill          #+#    #+#             */
/*   Updated: 2024/03/28 20:03:25 by amoutill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <readline/readline.h>

typedef enum	e_tktype
{
	word,
	in_redir,
	in_here_doc,
	out_redir,
	out_append,
	pipe
}		t_tktype;

typedef struct	s_token	t_token;

typedef struct	s_token
{
	char		*str;
	t_tktype	type;
	t_token		*next;
}		t_token;


void	tklst_addd(t_token **tklst, char *str, t_tktype type)
{
	if (!*tklst)
	{
		*tklst = malloc(sizeof(t_token));
		(*tklst)->str = strdup(str);
		(*tklst)->type = type;
		(*tklst)->next = NULL;
		return ;
	}
	while ((*tklst)->next)
		*tklst = (*tklst)->next;
	(*tklst)->next = malloc(sizeof(t_token));
	(*tklst)->next->str = strdup(str);
	(*tklst)->next->type = type;
	(*tklst)->next = NULL;
}

t_token	*magic_tokenizer(char *str)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*boeuf;
	t_token	*tklst;

	tklst = NULL;
	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		while (isspace(str[i]))
			++i;
		start = i;
		while (str[i] && !isspace(str[i]))
			++i;
		end = i;
		boeuf = malloc(sizeof(char) * (end - start + 1));
		strlcpy(boeuf, &str[start], end - start + 1);
		tklst_addd(&tklst, boeuf, word);
		++i;
	}
	return (tklst);
}

void	print_tktlst(t_token *token)
{
	printf("%s\n", token->str);
	while (token->next)
	{
		printf("%s\n", token->str);
		token = token->next;
	}
}


int	main(int argc, char const *argv[])
{
	char	*str;
	t_token	*tklst;

	while (1)
	{
		str = readline("minishell $ ");
		tklst = magic_tokenizer(str);
		print_tktlst(tklst);
		free(str);
	}
}
