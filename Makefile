# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 22:03:08 by tjensen           #+#    #+#              #
#    Updated: 2021/11/22 16:37:06 by tjensen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#	Project specific														   #
# **************************************************************************** #

NAME		:= minishell

SRCS		:= minishell.c utils.c
SRCS		+= token.c cmd/cmd.c cmd/scmd.c

SRCS_LEXER	:= lexer.c lexer_syntax.c lexer_token_other.c lexer_token_text.c
SRCS_PARSER	:= parser.c parser_scmd.c parser_scmd_pipeline.c parser_cmd_pipeline.c parser_cmd_group.c
SRCS_EXEC	:= execution.c
SRCS_BUILTIN:= echo.c
SRCS_PRINTER:= printer_token.c printer_scmd.c printer_cmd.c

SRCS		+= $(addprefix lexer/, $(SRCS_LEXER)) $(addprefix parser/, $(SRCS_PARSER)) \
			   $(addprefix execution/, $(SRCS_EXEC)) $(addprefix printer/, $(SRCS_PRINTER)) \
			   $(addprefix builtin/, $(SRCS_BUILTIN))

LDLIBS		:= -lft -lreadline

# **************************************************************************** #
#	GENERAL VARIABLES														   #
# **************************************************************************** #

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror

SDIR		:= src
ODIR		:= obj
OBJS		:= $(addprefix $(ODIR)/, $(SRCS:.c=.o))

LIBDIRS		:= $(wildcard lib/*)
LDLIBS		:= $(addprefix -L./, $(LIBDIRS)) $(LDLIBS)
INCLUDES	:= -I./inc/ $(addprefix -I./, $(LIBDIRS)) \
			   $(addprefix -I./, $(addsuffix /inc, $(LIBDIRS)))

# COLORS
LB   		= \033[0;36m
B			= \033[0;34m
Y  			= \033[0;33m
G		    = \033[0;32m
R 			= \033[0;31m
X		    = \033[m

# **************************************************************************** #
#	SYSTEM SPECIFIC SETTINGS							   					   #
# **************************************************************************** #

ifeq ($(shell uname -s), Linux)
	CFLAGS += -D LINUX -Wno-unused-result
endif

# **************************************************************************** #
#	FUNCTIONS									   							   #
# **************************************************************************** #

define MAKE_LIBS
	for DIR in $(LIBDIRS); do \
		$(MAKE) -C $$DIR $(1) --silent; \
	done
endef

# **************************************************************************** #
#	RULES																	   #
# **************************************************************************** #

.PHONY: all $(NAME) header clean fclean re bonus debug release libs test

all: $(NAME)

$(NAME): libs header $(OBJDIRS) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDLIBS)
	@printf "$(G)======= $(NAME)$(X)\n"

$(ODIR)/%.o: $(SDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "%-57b %b" "$(B)compile $(LB)$@" "$(G)[✓]$(X)\n"

header:
	@printf "###############################################\n"
	@printf "$(Y)####### $(shell echo "$(NAME)" | tr '[:lower:]' '[:upper:]')$(X)\n"

clean: libs header
	@$(RM) -r $(ODIR)
	@$(RM) -r *.dSYM $(SDIR)/*.dSYM $(SDIR)/$(NAME)
	@printf "%-50b %b" "$(R)clean" "$(G)[✓]$(X)\n"

fclean: libs header clean
	@$(RM) $(NAME)
	@printf "%-50b %b" "$(R)fclean" "$(G)[✓]$(X)\n"

re: fclean all

bonus: all

debug: CFLAGS += -O0 -DDEBUG -g
debug: all

release: fclean
release: CFLAGS	+= -O2 -DNDEBUG
release: all clean

libs:
ifeq ($(MAKECMDGOALS), $(filter $(MAKECMDGOALS), clean fclean re debug release))
	@$(call MAKE_LIBS,$(MAKECMDGOALS))
else
	@$(call MAKE_LIBS,all)
endif

test:
	@cd tests && bash tester.sh
