CC					= cc
CFLAGS			= -Wall -Wextra -Werror

SERVER_SRCS = server.c minitalk_utils.c
CLIENT_SRCS = client.c minitalk_utils.c

SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

NAME				= minitalk
SERVER 			= server
CLIENT			= client

all:				$(NAME)

$(NAME):		$(SERVER) $(CLIENT)

$(SERVER): 	$(SERVER_OBJS)
						$(CC) $(CFLAGS) $(SERVER_SRCS) -o $(SERVER)

$(CLIENT): 	$(CLIENT_OBJS)
						$(CC) $(CFLAGS) $(CLIENT_SRCS) -o $(CLIENT)

%.o:				%.c
						$(CC) $(CFLAGS) -c $< -o $@

clean:
						rm -f $(SERVER_OBJS) $(CLIENT_OBJS)

fclean:			clean
						rm -f $(SERVER) $(CLIENT)

re:					fclean all

.PHONY:			all clean fclean re