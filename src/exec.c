/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blebas <blebas@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:52:27 by blebas            #+#    #+#             */
/*   Updated: 2024/04/23 20:09:53 by blebas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_if_invalid_cmd(char *cmd_path)
{
	struct stat	cmd_stat;

	stat(cmd_path, &cmd_stat);
	if (S_ISDIR(cmd_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_path, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		exit(126);
	}
	if (!(cmd_stat.st_mode & S_IXUSR))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_path, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		exit(126);
	}
}

void	exec_forked(t_token *tklst, t_cmd *cmd, t_env *env)
{
	char	*cmd_path;
	char	**envp;

	redir_open(tklst);
	cmd_path = ft_which(env, cmd->argv[0]);
	if (!cmd_path)
		exit(127);
	exit_if_invalid_cmd(cmd_path);
	envp = init_envp(env);
	execve(cmd_path, cmd->argv, envp);
	perror(cmd_path);
	free(cmd_path);
	free_str_tab(envp);
	exit(126);
}

int	exec(t_token *tklst, t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	int		stat_loc;
	int		retval;

	retval = exec_cmd(cmd, env);
	if (retval != -1)
		return (retval);
	pid = fork();
	if (pid == 0)
		exec_forked(tklst, cmd, env);
	waitpid(pid, &stat_loc, 0);
	if (WIFEXITED(stat_loc))
		return (WEXITSTATUS(stat_loc));
	else if (WIFSIGNALED(stat_loc))
		return (128 + WSTOPSIG(stat_loc));
	return (0);
}
