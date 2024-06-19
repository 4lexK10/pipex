# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akloster <akloster@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/12 15:25:10 by akloster          #+#    #+#              #
#    Updated: 2024/06/19 18:28:02 by akloster         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM				= rm -rf

SRC				=	pipex.c free_functions.c error_handling.c file_handling.c \
					execs.c

LIBFT			=	libft/libft.a

OBJ_DIR			=	objs/

OBJ				=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror

NAME			=	pipex


$(NAME):		$(OBJ_DIR) $(OBJ)
				make -C./libft
				$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $@

all:			$(NAME)

$(OBJ_DIR)%.o:	%.c
				$(CC) $(CFLAGS) -c $< -o $@

%.o: 			%.c
				$(CC) $(CFLAGS) $< -o $@


$(OBJ_DIR):	
				@mkdir -p $(OBJ_DIR)

clean:
				make clean -C./libft
				$(RM) $(OBJ_DIR)

fclean:			clean
				make fclean -C./libft
				$(RM) $(OBJ) $(NAME) $(OBJ_DIR)

re:				fclean $(NAME)


.PHONY:			all clean fclean re
