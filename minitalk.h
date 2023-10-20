#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <limits.h>

typedef struct s_bit {
	char	c;
	int		count;
}	t_bit;

typedef struct s_list {
	volatile sig_atomic_t	flag;
	int										pid;
}	t_list;

void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi_pid(char *str);

#endif
