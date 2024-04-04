#include "minishell.h"

void	print_tktlst(t_token *token)
{
	while (token != NULL)
	{
		printf("%s\n", token->str);
		token = token->next;
	}
}
