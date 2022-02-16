##
## EPITECH PROJECT, 2022
## LIB_CONVERSION
## File description:
## make the conversion lib
##

# ----------------------------------------------------------------------------
# TARGET
NAME		=	libbgs.a
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# COLOUR
CYAN		=	'\033[1;36m'
BLUE		=	'\033[1;34m'
GREEN 		= 	'\033[1;32m'

RESET		=	'\033[0m'
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# IN-MAKEFILE SETTINGS
CURR_RULE	=	all
# ----------------------------------------------------------------------------

SRCDIR		=	src/

# ----------------------------------------------------------------------------
# SRC
SRC		:=	add.c								\
			cast.c								\
			create_object.c						\
			create_scene.c						\
			event.c								\
			loop.c								\
			remove.c							\
			object_add_components.c				\
			object_add_set_sprite_components.c	\
			preset_display.c					\
			start.c
SRC		:=	$(addprefix $(SRCDIR),$(SRC))

OBJ		=	$(SRC:%.c=%.o)
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# FLAGS
CFLAGS		=	-I../include
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# DEPENDANCES
LIBS_DEP	=	
# ----------------------------------------------------------------------------

%.o:	%.c
	@$(CC) $(CFLAGS) $^ -c -o $@
	@echo -e $(BLUE)'[compil]: $(notdir $^) -> $(notdir $@)'$(RESET)

all: 	CURR_RULE = all
all: 	init
	@$(MAKE) $(NAME) -s

$(NAME): CURR_RULE = $(NAME)
$(NAME): init $(LIBS_DEP) $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@echo -e $(GREEN)'[finished]: $(NAME): $(CURR_RULE)'$(RESET)

$(LIBS_DEP):
	$(foreach LIB,$(LIBS_DEP),$(MAKE) -C $(dir $(LIB)) $(RULE);)

debug: RULE = debug
debug: CFLAGS += -g3
debug: fclean $(NAME)

clean:	CURR_RULE = clean
clean:	init
	@$(RM) $(OBJ)
	@echo -e $(GREEN)'[finished]: $(NAME): $(CURR_RULE)'$(RESET)

fclean:	CURR_RULE = fclean
fclean:	init
	@$(MAKE) clean -s
	@$(RM) $(NAME)
	@echo -e $(GREEN)'[finished]: $(NAME): $(CURR_RULE)'$(RESET)

re:	CURR_RULE = re
re:	init
	@$(MAKE) fclean -s
	@$(MAKE) all -s
	@echo -e $(GREEN)'[finished]: $(NAME): $(CURR_RULE)'$(RESET)

.PHONY: init
init:
	@echo -e $(CYAN)'[starting]: $(NAME): $(CURR_RULE)'$(RESET)
