#include "minitalk.h"

static volatile sig_atomic_t	g_pid;

static void	ft_handler(int sig, siginfo_t *siginfo, void *ucontext)
{
	static t_bit	t_bit;

  (void)ucontext;
  if (g_pid != siginfo->si_pid)
	{
		t_bit.c = 0;
		t_bit.count = 0;
	}
	t_bit.c <<= 1;
	if (sig == SIGUSR1)
		t_bit.c += 1;
	else if (sig == SIGUSR2)
		t_bit.c += 0;
  t_bit.count++;
	if (t_bit.count == 8)
	{
		if (t_bit.c != '\0')
			write(1, &t_bit.c, 1);
		t_bit.c = 0;
		t_bit.count = 0;
	}
	usleep(60);
	g_pid = siginfo->si_pid;
	if (kill(siginfo->si_pid, SIGUSR1) == -1)
		exit(EXIT_FAILURE);
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr_fd("Pid : ", 1);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	sa.sa_sigaction = &ft_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
  sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		exit(EXIT_FAILURE);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		exit(EXIT_FAILURE);
	while (1)
		pause();
	exit(EXIT_SUCCESS);
}
