NAME		=	philo_bonus

SRC_DIR		=	./srcs/

OBJ_DIR		=	./objs/

HEADER_DIR	=	./includes/

SRC			=	./srcs/end.c \
				./srcs/init.c \
				./srcs/parse.c \
				./srcs/main.c \
				./srcs/ph_actions.c \
				./srcs/print.c \
				./srcs/ph.c \
				./srcs/time.c

HEADER		=	./includes/error.h \
				./includes/philosophers.h

OBJ			=	$(addprefix $(OBJ_DIR), $(notdir $(SRC:.c=.o)))

DEP			=	$(OBJ:%.o=%.d)

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -MMD -pthread -O2

LDFLAGS		=	-pthread -O2

RM			=	rm -f


all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(HEADER_DIR) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)
	@echo ""
	@echo "\x1b[1;36m \x1b[0;36m DONE ☆*:.｡.o(≧▽≦)o.｡.:*☆\033[0m"
	@echo ""
-include $(DEP)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

re: fclean $(OBJ_DIR) all

.PHONY: all clean fclean re
