#include "pipex.h"
#include "utils.h"
#include <fcntl.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int	executable(char *cmd, char *path[], char **cmd_path)
{
	int		i;
	char	*temp;

	if (!access(*cmd, X_OK))
		temp = ft_strdup(cmd);
	else
	{
		i = 0;
		while (path && path[i])
		{
			temp = ft_joinpath(path[i++], cmd);
			if (!temp)
				return (-1);
			if (!access(temp, X_OK))
				break ;
			free(temp);
		}
		if (!path)
			return (1);
	}
	if (cmd_path)
		*cmd_path = temp;
	return (0);
}


//	致命的エラーの場合エラー出力をして終了する関数
pid_t	eval(char *cmd, t_eval *config)
{
	pid_t	ret;
	size_t	i;
	char	*path;
	char	**args;

	args = cmdline_split(cmd);
	if (!args)
		return (-1);
	path = executable(args[0], config->path);
	if (!path)
		ret = -1;
	else
		ret = execute(path, args, config->envp);
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
	free(path);
	return (ret);
}

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	pid;
	t_eval	config;

	(void)argc;
	(void)argv;
	(void)envp;
	config.envp = envp;
	config.path = get_path(envp);
	config.stdin = 0;
	config.stdout = 1;
	pid = eval("ls ~", &config);
	waitpid(pid, NULL, 0);
}
