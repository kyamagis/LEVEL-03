# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/08 09:35:52 by smuramat          #+#    #+#              #
#    Updated: 2022/10/25 20:02:21 by smuramat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc

CFLAGS = -Wall	-Wextra	-Werror

LINK_LIB := -lreadline

ifeq ($(shell uname), Darwin)
	CFLAGS += -I$(shell brew --prefix readline)/include
	LINK_LIB += -L$(shell brew --prefix readline)/lib
endif

LIBFT_PATH = libft
LIBFT_MAKE = $(MAKE) -C $(LIBFT_PATH)
LIBFT_LIB = -L./libft -lft

LDFLAGS = $(LIBFT_LIB) $(LINK_LIB)

HEADER_FILES = includes/minishell.h

SRCNAME = minishell.c\
		check_syntax/check_syntax.c\
		check_syntax/check_syntax2.c\
		check_syntax/check_syntax3.c\
		check_syntax/check_quote.c\
		init/importing_main_shell_env.c\
		init/init.c\
		replace_env/replace_env_to_command.c\
		replace_env/replace_env_to_cmd_util.c\
		replace_env/replace_env_to_cmd_util_2.c\
		replace_env/rm_quote.c\
		save_cmd/add_command_to_list.c\
		save_cmd/split_for_add_list.c\
		save_cmd/split_for_parser.c\
		save_redirect/make_new_cmd_without_redirect.c\
		save_redirect/make_redirect_arr.c\
		save_redirect/save_redirect.c\
		save_redirect/save_redirect_util.c\
		save_redirect/split_with_valid_pipe.c\
		util/util.c\
		util/util2.c\
		util/util3.c\
		util/util4.c\
		util/util5.c\
		util/free.c\
		util/rm_space.c\
		util/signal.c\
		exe_cmd/exe_cmd.c\
		exe_cmd/multiple_pipe.c\
		exe_cmd/not_pipe_and_builtin_cmd.c\
		exe_cmd/waitpid_and_set_g_status.c\
		exe_cmd/lib_shell/ft_strcmp.c\
		exe_cmd/lib_shell/ft_isspace.c\
		exe_cmd/lib_shell/ft_strstr_idx.c\
		exe_cmd/lib_shell/my_split.c\
		exe_cmd/lib_shell/my_strdup.c\
		exe_cmd/lib_shell/my_substr.c\
		exe_cmd/lib_shell/my_strjoin.c\
		exe_cmd/exe_cmd_utils/exit.c\
		exe_cmd/exe_cmd_utils/isbuiltin_cmd.c\
		exe_cmd/exe_cmd_utils/exe_a_builtin_cmd.c\
		exe_cmd/exe_cmd_utils/strerror_file_name.c\
		exe_cmd/exe_cmd_utils/delete_created_file.c\
		exe_cmd/make_absolute_path/make_absolute_path.c\
		exe_cmd/make_absolute_path/if_slash_exists_cmd.c\
		exe_cmd/make_absolute_path/path_envp_to_str.c\
		exe_cmd/make_absolute_path/envp_list_to_double_pointer.c\
		exe_cmd/redirections/stdin_redirect.c\
		exe_cmd/redirections/detect_redirection.c\
		exe_cmd/redirections/add_write_redirection.c\
		exe_cmd/redirections/over_write_redirection.c\
		exe_cmd/redirections/discriminate_accessible_file.c\
		exe_cmd/redirections/here_document/put_env.c\
		exe_cmd/redirections/here_document/here_document.c\
		exe_cmd/redirections/here_document/find_list_tail.c\
		exe_cmd/redirections/here_document/create_unique_file_name.c\
		exe_cmd/redirections/here_document/gnl/get_next_line.c\
		exe_cmd/redirections/here_document/gnl/get_next_line_utils.c\
		exe_cmd/builtin_cmd/cd.c\
		exe_cmd/builtin_cmd/env.c\
		exe_cmd/builtin_cmd/pwd.c\
		exe_cmd/builtin_cmd/echo.c\
		exe_cmd/builtin_cmd/unset.c\
		exe_cmd/builtin_cmd/builtin_exit.c\
		exe_cmd/builtin_cmd/builtin_export/builtin_export.c\
		exe_cmd/builtin_cmd/builtin_export/make_export_list.c\
		exe_cmd/builtin_cmd/builtin_export/add_export_cmdline_to_envp.c\
		exe_cmd/builtin_cmd/builtin_utils/builtin_puterror.c\
		exe_cmd/builtin_cmd/builtin_utils/isalnum_underscore.c\
		exe_cmd/builtin_cmd/builtin_utils/isalnum_underscore_str.c\
		exe_cmd/builtin_cmd/builtin_utils/find_env_name_and_return_the_env_pointer.c
		
SRCDIR = src/
SRCS	=	${addprefix ${SRCDIR}, ${SRCNAME}}
OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(OBJS): $(HEADER_FILES)

$(NAME): ${HEADER_FILES} ${OBJS}
	$(LIBFT_MAKE)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	$(LIBFT_MAKE) clean
	${RM} ${OBJS}

fclean: clean
	$(LIBFT_MAKE) fclean
	${RM} ${NAME}

re: fclean all

.PHONY: all fclean clean re
