NAME = minishell
INCLUDES = include
SRCS_DIR = src
OBJS_DIR = objs
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf
LIBFT = libft

# Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

SOURCES = main.c

SRCS = $(addprefix $(SRCS_DIR)/,$(SOURCES))
OBJS = $(addprefix $(OBJS_DIR)/,$(SOURCES:.c=.o))

all: lib tmp $(NAME)

lib:
	@echo "$(GREEN)Creating lib files$(BLUE)"
	@make -C $(LIBFT)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -L $(LIBFT) -o $(NAME) $(OBJS)
	@echo "$(GREEN)Project successfully compiled$(DEF_COLOR)"

tmp:
	@mkdir -p objs

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(INCLUDES)/$(NAME).h
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf "$(BLUE)Compiling $(WHITE)%-30s$(BLUE)[%3d%%]$(RED)\r" $(notdir $@) $$(expr $$(expr $$(ls $(OBJS_DIR)/*.o 2>/dev/null | wc -l) \* 100) / $$(ls $(SRCS_DIR)/*.c | wc -l))
	@sleep 0.1

clean:
	@echo "$(RED)Deleting object files$(BLUE)"
	@make clean -C $(LIBFT)
	@$(RM) $(OBJS_DIR)

fclean:
	@$(RM) $(OBJS_DIR)
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)
	@echo "$(RED)All files cleaned with fclean"

re: fclean
	@$(MAKE) all

.PHONY: tmp, re, fclean, clean

