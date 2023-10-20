#include "minitalk.h"

static t_list	g_list;

static void	ft_send_byte(char c, pid_t pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		while (g_list.flag == 0)
			pause();
		g_list.flag = 0;
		usleep(60);
		if (c >> i & 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(EXIT_FAILURE);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(EXIT_FAILURE);
		}
		i--;
	}
}

static void	ft_send_message(char *str, pid_t pid)
{
	size_t	i;

	g_list.flag = 1;
	i = 0;
	while (str[i])
	{
		ft_send_byte(str[i], pid);
		i++;
	}
}

static void	ft_handler(int sig, siginfo_t *siginfo, void *ucontext)
{
	(void)sig;
	(void)ucontext;
	if (siginfo->si_pid == g_list.pid)
		g_list.flag = 1;
}

int	main(int argc, char **argv)
{
  struct sigaction	sa;

	if (argc != 3)
	{
		ft_putstr_fd("Usage: ./client [pid] [message]\n", 2);
		exit(EXIT_FAILURE);
	}
	g_list.pid = ft_atoi_pid(argv[1]);
	if (g_list.pid < 100 || g_list.pid > 99998)
	{
		ft_putstr_fd("Pid should be between 100 and 99998.\n", 2);
		exit(EXIT_FAILURE);
	}
	if (*argv[2] == '\0')
	{
		ft_putstr_fd("Insert a non-empty message.\n", 2);
		exit(EXIT_FAILURE);
	}
	sa.sa_sigaction = &ft_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		exit(EXIT_FAILURE);
	ft_send_message(argv[2], (pid_t)g_list.pid);
	exit(EXIT_SUCCESS);
}
