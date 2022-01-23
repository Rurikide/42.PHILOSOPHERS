# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/19 19:22:46 by tshimoda          #+#    #+#              #
#    Updated: 2022/01/23 17:30:26 by tshimoda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo

AR= ar rc
RM= rm -rf

CC= gcc
CFLAGS= -Wall -Werror -Wextra -pthread -c

SDIR= sources

ODIR= objects

SRCS= main.c \
		time.c \
		utils.c \

OBJS= $(SRCS:.c=.o)

SFIX= $(addprefix $(SDIR)/, $(SRCS))
OFIX= $(addprefix $(ODIR)/, $(OBJS))

VPATH= $(SDIR)

$(ODIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(NAME): $(ODIR) $(OFIX)
	$(CC) $(OFIX) -o $(NAME)
	@echo "\033[1;32m 下田、徳太郎のPHILO\033[0;39m"

all:    $(NAME)

$(ODIR):
		mkdir -p $(ODIR)

clean:
	$(RM) $(ODIR)

fclean: clean
	$(RM) $(NAME)
	@echo "\033[1;34m make fclean done!\033[0;39m"

re:     clean all

.PHONY: all clean flcean re