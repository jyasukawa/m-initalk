#include "minitalk.h"

int	ft_atoi_pid(char *str)
{
	size_t		i;
	long long	pid;

	i = 0;
	pid = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			if ((INT_MAX - (str[i] - '0')) / 10 < pid)
				return (-1);
			pid = (pid * 10) + (str[i] - '0');
			i++;
		}
		else
			return (-1);
	}
	return ((int)pid);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (s == NULL)
		return ;
  i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;
	char	c;

	nbr = (long)n;
	if (nbr < 0)
	{
		write(fd, "-", 1);
    nbr = nbr * (-1);
	}
	if (nbr > 9)
		ft_putnbr_fd(nbr / 10, fd);
	c = nbr % 10 + '0';
	write(fd, &c, 1);
}
