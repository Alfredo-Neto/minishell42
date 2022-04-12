/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:26:28 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/04/12 00:07:40 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	new_prompt(int signal)
{
	write(1, "\n", 1);
	exit(131);
	(void)signal;
}

void	redirect(char *file, int flags, int in_or_out)
{
	int	fd;

	if (!in_or_out)
		fd = open(file, flags);
	else
		fd = open(file, flags, 0777);
	if (fd == -1)
		perror("Redirect Failed...\n");
	else
	{
		dup2(fd, in_or_out);
		close(fd);
	}
}

void	heredoc(char *eof)
{
	char	*input;
	int		status;

	signal(SIGINT, SIG_IGN);
	if (!fork())
	{
		signal(SIGINT, new_prompt);
		while (1)
		{
			input = readline("> ");
			if (!input)
			{
				printf("bash: warning: here-document at line 13 delimited by end-of-file (wanted `%s')", eof);
				exit(1);
			}
			if (!strcmp(input, eof))
			{
				free(input);
				exit(0);
			}
			ft_putendl_fd(input, 1);
			free(input);
		}
	}
	wait(&status);
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		if (status)
			printf("Error with code %d\n", status);
	}
}

void	check_redirections(char **redirect_mode)
{
	int	i;

	i = 0;
	while (redirect_mode[i])
	{
		if (redirect_mode[i] == GREAT)
			redirect(redirect_mode[i + 1], O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
		else if (redirect_mode[i] == GREATGREAT)
			redirect(redirect_mode[i + 1], O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO);
		else if (redirect_mode[i] == LESS)
			redirect(redirect_mode[i + 1], O_RDONLY | O_CREAT, STDIN_FILENO);
		else if (redirect_mode[i] == LESSLESS)
			heredoc(redirect_mode[i + 1]);
		i++;
	}
}
// bash: syntax error near unexpected token `newline'
