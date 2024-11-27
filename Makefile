################################################################################
#                                 	CONFIG	                                   #
################################################################################

NAME						:= Cub3D
BUILD_DIR					:= ./.build
CC							:= gcc
FLAGS						:= -Wall -Wextra -Werror -g
INC							:= include/cub3d.h

LIBFT_DIR					:= lib/
LIBFT						:= $(LIBFT_DIR)libft.a

CLR_RMV						:= \033[0m
RED							:= \033[0;31m
GREEN						:= \033[0;32m
REDIRECT_ERROR 				:= >/dev/null 2>&1

################################################################################
#                                	MLX			                               #
################################################################################

MINILIBX_URL 				= https://github.com/42Paris/minilibx-linux.git
MINILIBX_DIR 				= minilibx-linux/
MINILIBX_HEADERS 			= $(MINILIBX_DIR)
MINILIBX 					= $(MINILIBX_DIR)libmlx.a
LIBS 						= -lm -L$(MINILIBX_DIR) -lmlx -lX11 -lXext

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS						:=	src/main.c					 		\
                				src/utils/close.c					\
                				src/utils/utils.c					\
                				src/utils/utils2.c					\
                				src/utils/key_hook.c				\
                				src/parsing/init.c					\
                				src/parsing/parsing.c				\
                				src/parsing/colors.c				\
                				src/parsing/map_parse.c				\
                				src/parsing/texture_parse.c			\
                				src/raycasting/draw.c				\
                				src/raycasting/wall_hit.c			\
                				src/raycasting/wall_ne.c			\
                				src/raycasting/wall_nw.c			\
                				src/raycasting/wall_se.c			\
                				src/raycasting/wall_sw.c			\
                				src/raycasting/raycaster.c			

                          
OBJS							:= $(SRCS:%.c=$(BUILD_DIR)/%.o)

################################################################################
#                               BUILDING OBJECTS                               #
################################################################################

$(BUILD_DIR)/%.o: %.c $(INC)
	@mkdir -p $(@D)
	@echo "\e[35mCompiling\e[0m $(*F)"
	@$(CC) $(FLAGS) -I $(LIBFT_DIR) -c $< -o $@

################################################################################
#                                 MAIN TARGETS                                 #
################################################################################

all: $(NAME) $(LIBFT)

$(NAME): $(MINILIBX) $(OBJS) $(LIBFT)
	@echo "\e[36mBuilding\e[0m $@"
	@$(CC) $(FLAGS) $(OBJS) $(LIBS) $(LIBFT) -Llibft -o $(NAME)
	@echo "$(GREEN)$(NAME) created ✔️${CLR_RMV}"
	@sleep 1
	@clear

$(LIBFT):
	@echo "\e[34mLinking\e[0m libft"
	@make --no-print-directory -C $(LIBFT_DIR)
	@cp $(LIBFT) $(NAME)

$(MINILIBX):
	@echo "${GREEN}~-~-~-~-~ COMPILING MINILIBX ~-~-~-~-~${CLR_RMV}"
	@echo "   ${GREEN}- Fetching sources...${CLR_RMV}"
	@if [ ! -d "$(MINILIBX_DIR)" ]; then \
		git clone $(MINILIBX_URL) $(MINILIBX_DIR); \
	else \
		cd $(MINILIBX_DIR) && git pull; \
	fi
	@echo "   ${GREEN}- Compiling sources...${CLR_RMV}"
	@make --no-print-directory -s -C $(MINILIBX_DIR) all $(REDIRECT_ERROR)
	@echo "${GREEN}~ DONE ~\n${CLR_RMV}"

clean_minilibx:
	@rm -rf $(MINILIBX_DIR)

bonus: all

clean:
	@$(RM) -r $(BUILD_DIR)/*.o
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@echo "$(RED)Deleting $(CYAN)$(NAME)'s $(CLR_RMV)object files ✔️"

fclean: clean clean_minilibx
	@$(RM) -r $(BUILD_DIR)/*.o
	@$(RM) -r $(BUILD_DIR)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@echo "$(RED)Deleting $(CYAN)$(NAME)'s $(CLR_RMV)binaries ✔️"


re: fclean all

.PHONY: all clean fclean re
