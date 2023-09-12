#include "pipex.h"
#include "utils.h"
#include "io.h"
#include <libft.h>
#include <stdio.h>
#include <fcntl.h>

#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

char	**cmdline_split(char *s);

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(void)envp;

	char **a = cmdline_split("cmd aa aa\"aa aa\"aa");
	while (*a)
		printf("%s\n", *a++);
	
	// t_strgen *strgen= ft_strgennew();
	// ft_strgenstr(strgen, "aaa");
	// ft_strgenchr(strgen, 'f');
	// ft_strgenstr(strgen, "ddd");
	// printf("%s\n", ft_strgencomp(strgen));
	// ft_strgendel(strgen);
	// pipex(&(t_pipex){(char *[]){"grep ppp", "cat -e", NULL}, 1, "file1", "file2"}, argv[0], envp);
	// int fd[2];

	// int fd2[2];
	// pipe(fd);
	// pipe(fd2);
	// write(fd[1], "abcde\n", 6);
	// write(fd[1], "abcde\n", 6);
	// write(fd[1], "abcde\n", 6);
	// write(fd[1], "abcde\n", 6);
	// close(fd[1]);
	// setstdio(fd[0], fd2[1]);
	// pid_t pid = fork();
	// setstdio(fd2[0], open("/dev/stdout", O_WRONLY));
	// if (!pid)
	// {
	// 	execve("/bin/cat", (char *[]){argv[0], NULL}, envp);
	// }	
	// execve("/bin/cat", (char *[]){argv[0], "-e", NULL}, envp);
	// close(fd2[1]);
	// wait(NULL);
}

// ダブルクォーテーションの場合\\を\、\"を"にする。
// シングルクォーテーションにはエスケープはない

