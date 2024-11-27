NAME = libft.a

BUILD_DIR = ./.build
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
AR = ar crs
RM = rm -f
Lib_H = libft.h

SRCS_LIBFT =	ft_memset.c		\
				ft_strlen.c		\
				ft_calloc.c		\
				ft_strdup.c		\
				ft_memcpy.c		\
				ft_strncmp.c 	\
				ft_realloc.c	\
				get_next_line.c

OBJS_LIBFT = $(SRCS_LIBFT:%.c=$(BUILD_DIR)/%.o)

# Rule to create the library
$(NAME): $(OBJS_LIBFT)
	@$(AR) $(NAME) $(OBJS_LIBFT)

all: $(NAME)

# Rule to compile .c files into .o files with the correct path
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files
clean:
	@$(RM) $(OBJS_LIBFT)

# Clean up object files and the library
fclean: clean
	@$(RM) $(NAME)
	@$(RM) -r $(BUILD_DIR)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
