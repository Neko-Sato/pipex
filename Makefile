# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/20 00:51:30 by hshimizu          #+#    #+#              #
#    Updated: 2023/09/23 01:37:32 by hshimizu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= pipex

DIR				= .
FT				= $(DIR)/libft
FT_PRINTF		= $(DIR)/libftprintf
INCS_DIR		= $(DIR)/incs
OBJS_DIR		= $(DIR)/objs

MAIN			= $(DIR)/main.c

SRCS			= \
	$(addprefix $(DIR)/srcs/, \
		utils.c \
		cmdline_split.c \
		here_doc.c \
		eval.c \
		pipex.c \
	) \

OBJS			= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

CFLAGS			= -Wall -Wextra -Werror
CFLAGS			+= -g
LDFLAGS			+= -L$(FT)
IDFLAGS			+= -I$(FT)
LIBS			+= -lft
LDFLAGS			+= -L$(FT_PRINTF)
IDFLAGS			+= -I$(FT_PRINTF)
LIBS			+= -lftprintf
IDFLAGS			+= -I$(INCS_DIR)

.PHONY: all clean fclean re bonus

all: $(FT) $(FT_PRINTF) $(NAME)

$(NAME): $(MAIN) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(IDFLAGS) $^ -o $@ $(LIBS)

bonus: 
	@echo bonus

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(IDFLAGS) $< -o $@

clean:
	$(RM) -r $(OBJS_DIR)

fclean: clean
	@make -C $(FT) fclean
	@make -C $(FT_PRINTF) fclean
	$(RM) $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: test
test: test.c $(OBJS)
	$(CC) -g $(CFLAGS) $(LDFLAGS) $(IDFLAGS) $^ -o $@ $(LIBS)

.PHONY: norm
norm: $(MAIN) $(SRCS) $(INCS_DIR)
	@norminette $^

.PHONY: $(FT)
$(FT):
	# @git submodule update --init $@
	@make -C $@ all

.PHONY: $(FT_PRINTF)
$(FT_PRINTF):
	# @git submodule update --init $@
	@make -C $@
