/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:39:39 by blebas            #+#    #+#             */
/*   Updated: 2024/03/28 13:39:43 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*LIBRARY*/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "Libft/libft.h"

/*COLORS*/

#define NC		"\e[0m"
#define YELLOW	"\e[1;33m"
#define RED		"\e[1;31m"
#define GREEN	"\e[1;32m"
#define PURPLE	"\e[1;35m"
#define CYAN	"\e[1;36m"
#define BLUE	"\e[1;34m"

/*STRUCTURES*/


/*FONCTIONS*/

//main.c
int	main(int argc, char **argv);

//parse.c

//exec.c

//echo.c
int		echo_cmd(char **argv);

#endif
