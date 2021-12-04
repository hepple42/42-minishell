#include "exec.h"

int	close_pipes(int	pipes[2][2], int i, bool last)
{
	if (i == 0)
		close_pipe_end(pipes[0][1]);
	else if (last)
		close_pipe_end(pipes[(i + 1) % 2][0]);
	else if (i % 2 == 1)
	{
		close_pipe_end(pipes[0][0]);
		close_pipe_end(pipes[1][1]);
	}
	else if (i % 2 == 0)
	{
		close_pipe_end(pipes[1][0]);
		close_pipe_end(pipes[0][1]);
	}
	else if (i == -1)
	{
		close_pipe_end(pipes[0][0]);
		close_pipe_end(pipes[0][1]);
		close_pipe_end(pipes[1][0]);
		close_pipe_end(pipes[1][1]);
	}
	return (0);
}

void	child_set_pipes(int fd[2], int pipes[2][2], int i, bool last)
{
	if (i == 0)
	{
		fd[0] = STDIN_FILENO;
		fd[1] = pipes[0][1];
	}
	else if (last)
	{
		fd[0] = pipes[(i + 1) % 2][0];
		fd[1] = STDOUT_FILENO;
	}
	else if (i % 2 == 1)
	{
		fd[0] = pipes[0][0];
		fd[1] = pipes[1][1];
	}
	else if (i % 2 == 0)
	{
		fd[0] = pipes[1][0];
		fd[1] = pipes[0][1];
	}
}

void	pipes_init(int pipes[2][2])
{
	pipes[0][0] = -1;
	pipes[0][1] = -1;
	pipes[1][0] = -1;
	pipes[1][1] = -1;
}

int	close_pipe_end(int pipe_end)
{
	if (pipe_end == -1)
		return (0);
	return (close(pipe_end));
}