/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:18:13 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/04/27 20:42:47 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


#define TMP_FILE	"/tmp/minishell_here_document"
#define NO_DELIMITER "minishell: warning: here-document at \
		line 13 delimited by end-of-file (wanted `%s')"

static void	clear_tmp_file(void)
{
	int		tmp_fd;

	tmp_fd = open(TMP_FILE, O_WRONLY | O_TRUNC, 0600);
	close(tmp_fd);
}

static int	create_tmp_file(void)
{
	int	fd;

	fd = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		perror("Minishell: Could not create temp file: %s");
	return (fd);
}

static void	redirect_tmp_file_input(void)
{
	int		tmp_fd;

	tmp_fd = open(TMP_FILE, O_RDONLY);
	unlink(TMP_FILE);
	dup2(tmp_fd, STDIN);
	close(tmp_fd);
}

void	write_input(char *eof, int tmp_file)
{
	char	*input;

	signal(SIGINT, interrupt_input_writing);
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			ft_printf(STDERR, NO_DELIMITER, eof);
			exit(0);
		}
		if (!ft_strcmp(input, eof))
		{
			free(input);
			exit(0);
		}
		ft_putendl_fd(input, tmp_file);
		free(input);
	}
}

int	heredoc(char *eof, int *fd)
{
	int		save_fd;
	int		tmp_file;
	int		status;

	tmp_file = create_tmp_file();
	if (tmp_file < 0)
		return (FAILURE);
	save_fd = dup(STDOUT_FILENO);
	dup2(fd[STDOUT], STDOUT_FILENO);
	signal(SIGINT, SIG_IGN);
	printf("OK\n");
	if (!fork())
		write_input(eof, tmp_file);
	wait(&status);
	dup2(save_fd, STDOUT_FILENO);
	close(save_fd);
	if (status == 130)
	{
		clear_tmp_file();
		return (FAILURE);
	}
	redirect_tmp_file_input();
	return (SUCCESS);
}
