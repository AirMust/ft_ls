# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: air_must <air_must@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/25 14:04:51 by slynell           #+#    #+#              #
#    Updated: 2020/09/03 00:41:31 by air_must         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC = gcc

FLAGS = -Wall -Werror -Wextra -O2
# -Wall -Werror -Wextra -O2

# /*
# ** ========================== HEADER ==============================
# */
INCS = ft_ls.h
IDIR = header
INCS += $(addprefix $(LDIR)/,$(addprefix $(IDIR)/,$(libft.h)))
INCLUDES = $(addprefix $(IDIR)/,$(INCS))

LDIR = libft
LIBFT = $(addprefix $(LDIR)/,libft.a)


# /*
# ** ====================== SOURCE LS MAIN ==========================
# */
SDIR = src
ODIR = obj

SRCS = main.c
SRCS += ls_error.c
SRCS += ls_read.c
SRCS += ls_print_lst_file.c


SOURCES = $(addprefix $(SDIR)/,$(SRCS))
OBJECTS = $(addprefix $(ODIR)/,$(SRCS:.c=.o))


# /*
# ** ====================== SOURCE LST FILE ==========================
# */
SDIR_LST_FILE = src/ls_lst_file
ODIR_LST_FILE = obj/ls_lst_file

SRC_LST_FILE = ls_lst_add.c
SRC_LST_FILE += ls_lst_create.c
SRC_LST_FILE += ls_lst_free.c
SRC_LST_FILE += ls_lst_get_start.c
SRC_LST_FILE += ls_lst_reverse.c
SRC_LST_FILE += ls_lst_swap.c
SRC_LST_FILE += ls_lst_length.c
SRC_LST_FILE += ls_lst_sort_by_atime.c
SRC_LST_FILE += ls_lst_sort_by_ctime.c
SRC_LST_FILE += ls_lst_sort_by_mtime.c
SRC_LST_FILE += ls_lst_sort_by_name.c
SRC_LST_FILE += ls_lst_is_root.c
SRC_LST_FILE += ls_lst_sort.c
SRC_LST_FILE += ls_lst_print_lst.c
SRC_LST_FILE += ls_lst_insert.c
SRC_LST_FILE += ls_lst_get_by_ind.c
SRC_LST_FILE += ls_lst_name_max_length.c



SOURCES_LST_FILE = $(addprefix $(SDIR_LST_FILE)/,$(SRC_LST_FILE))
OBJECTS_LST_FILE = $(addprefix $(ODIR_LST_FILE)/,$(SRC_LST_FILE:.c=.o))

# /*
# ** ====================== SOURCE FILE ==========================
# */
SDIR_FILE = src/ls_file
ODIR_FILE = obj/ls_file

SRC_FILE = ls_file_concat_path_dir.c
SRC_FILE += ls_file_get_type.c
SRC_FILE += ls_file_get_permision.c
SRC_FILE += ls_file_get_blocks.c
SRC_FILE += ls_file_readlink.c
SRC_FILE += ls_file_get_xattr.c



SOURCES_FILE = $(addprefix $(SDIR_FILE)/,$(SRC_FILE))
OBJECTS_FILE = $(addprefix $(ODIR_FILE)/,$(SRC_FILE:.c=.o))


.PHONY: clean fclean all re

all :  $(LIBFT) $(NAME)
	@make -C $(LDIR) 2> tmp.log
	@2> tmp.log
	@@echo "Project $(NAME) build successfully \c" >> tmp.log

$(NAME) :  $(LIBFT) $(OBJECTS) $(OBJECTS_LST_FILE) $(OBJECTS_FILE) $(INCLUDES) Makefile
	@$(CC) $(FLAGS) -o $(NAME) $(OBJECTS) $(OBJECTS_LST_FILE) $(OBJECTS_FILE) -I $(IDIR) $(LIBFT)
	@echo "\nProject $(NAME) build successfully \033[32m[OK]\033[0m\n"

# /*
# ** ====================== MAKE LIBFT ==========================
# */
$(LIBFT) :
	@make -C $(LDIR) 2> tmp.log

# /*
# ** ====================== MAKE LST FILE ==========================
# */
$(ODIR_LST_FILE)/%.o : $(SDIR_LST_FILE)/%.c $(INCLUDES) Makefile
	@if [[ $< == src/ls_lst_file/ls_lst_add.c ]]; then \
		echo "\n > Make \033[33mlst_file\033[0mfunctions:\c"; \
	fi
	@mkdir -p $(ODIR_LST_FILE) 2> tmp.log
	@$(CC) $(FLAGS) -I $(IDIR) -c $< -o $@ 2> tmp.log
	@echo "\033[32m.\033[0m\c"

# /*
# ** ====================== MAKE FILE ==========================
# */
$(ODIR_FILE)/%.o : $(SDIR_FILE)/%.c $(INCLUDES) Makefile
	@if [[ $< == src/ls_file/ls_file_concat_path_dir.c ]]; then \
		echo "\n > Make \033[33mfile\033[0m\tfunctions:\c"; \
	fi
	@mkdir -p $(ODIR_FILE) 2> tmp.log
	@$(CC) $(FLAGS) -I $(IDIR) -c $< -o $@ 2> tmp.log
	@echo "\033[32m.\033[0m\c"

# /*
# ** ====================== SOURCE LS MAIN  ==========================
# */
$(ODIR)/%.o : $(SDIR)/%.c $(INCLUDES) Makefile
	@if [[ $< == src/main.c ]]; then \
		echo "Make \033[33m$(NAME)\033[0m\tfunctions:\c"; \
	fi
	@mkdir -p $(ODIR) 2> tmp.log
	@$(CC) $(FLAGS) -I $(IDIR) -c $< -o $@ 2> tmp.log
	@echo "\033[32m.\033[0m\c"


clean:
	@make clean -C $(LDIR) 2> tmp.log
	@rm -rf $(OBJS) 2> tmp.log
	@rm -rf $(ODIR) 2> tmp.log

fclean: clean
	@make fclean -C $(LDIR) 2> tmp.log
	@rm -rf $(NAME) 2> tmp.log
	@echo "\033[31m> Clear $(NAME)\033[0m"

re: fclean all
