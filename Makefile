##
## EPITECH PROJECT, 2021
## defender
## File description:
## make the defender
##

# ----------------------------------------------------------------------------
# TARGET
NAME		=	my_defender
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# COLOUR
CYAN		=	'\033[1;36m'
BLUE		=	'\033[1;34m'
GREEN 		= 	'\033[1;32m'
RED			=	'\033[1;31m'

RESET		=	'\033[0m'
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# IN-MAKEFILE SETTINGS
CURR_RULE	=	all
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# SRC
SRCINITDIR		:=  init/
SRCMAP			:=	map/
SRCUPDATEDIR	:=  update/
SRCLAUNCHDIR	:=	launch_game/
SRCDIR			:=	src/
SRCBUTTON		:= create_button/
SRCENNEMY		:= create_ennemy/

SRC_BUTTON		:=	create_button.c		\
					check_set_color.c
SRC_BUTTON		:=	$(addprefix $(SRCBUTTON),$(SRC_BUTTON))

SRC_ENNEMY		:=	create_ennemy.c
SRC_ENNEMY		:=	$(addprefix $(SRCENNEMY),$(SRC_ENNEMY))

SRC_INIT		:= 	init_defender.c		\
					init_side_menu.c	\
					init_game_data.c	\
					init_menu.c
SRC_INIT		:=	$(addprefix $(SRCINITDIR),$(SRC_INIT))

SRC_MAP			:= 	create_map.c
SRC_MAP			:=	$(addprefix $(SRCMAP),$(SRC_MAP))

SRC_UPDATE		:=	button_menu.c			\
					ennemy.c				\
					pause_button.c			\
					update_wave_launcher.c	\
					button_shop.c			\
					button_level.c
SRC_UPDATE		:=	$(addprefix $(SRCUPDATEDIR),$(SRC_UPDATE))

SRC_LAUNC		:=	launch_game.c		\
					destroy_load_list.c	\
					load_gestion.c
SRC_LAUNC		:=	$(addprefix $(SRCLAUNCHDIR),$(SRC_LAUNC))

SRC			:=	main.c $(SRC_INIT) $(SRC_UPDATE) $(SRC_LAUNC) $(SRC_MAP)	\
				$(SRC_ENNEMY) $(SRC_BUTTON)
SRC			:=	$(addprefix $(SRCDIR),$(SRC))

OBJ			:=	$(SRC:%.c=%.o)
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# LIB
LIB_TARGET	=	lib/libmy.a

LDFLAGS		=	-L$(dir $(LIB_TARGET)) -lmy -lcsfml-graphics -lcsfml-audio \
				-lcsfml-system -lcsfml-window
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# TEST
TNAME		:=	bin_test

TSRCDIR		:=	tests/

TSRC		:=	test_basic.c
TSRC		:=	$(addprefix $(TSRCDIR),$(TSRC))
TSRC		:= 	$(filter-out $(SRCDIR)main.c,$(SRC)) $(TSRC)

TOBJ		:=	$(TSRC:%.c=%.o)
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# FLAGS
CFLAGS		= 	-Iinclude/ -Ilib/include/ -Wall -Wextra -Wpedantic

TFLAGS		=	-fprofile-arcs -ftest-coverage -Ilib/libbgs/include/

CR_TEST_LDFLAGS	=	-lcriterion -lgcov

FN_TEST_LDFLAGS	=	-lgcov
# ----------------------------------------------------------------------------

%.o: %.c
	@$(CC) $(CFLAGS) $^ -c -o $@
	@echo -e $(BLUE)'compil : $(notdir $^) -> $(notdir $@)'$(RESET)

# ----------------------------------------------------------------------------
# Make the defender
.PHONY: 	all
all:		CURR_RULE = all
all:		init $(LIB_TARGET)
	@$(MAKE) $(NAME) -s
	@echo -e $(GREEN)'-> [finished]: $(NAME): all'$(RESET)

$(NAME):	CURR_RULE = $(NAME)
$(NAME): 	init $(OBJ)
	@$(CC) $(OBJ) $(MAIN_OBJ) -o $(NAME) $(LDFLAGS) $(CFLAGS)
	@echo -e $(GREEN)'-> [finished]: $(NAME): $(NAME)'$(RESET)

$(LIB_TARGET):
	@$(MAKE) -s -C $(dir $(LIB_TARGET)) $(RULE)

debug: RULE = debug
debug: CFLAGS += -g3
debug: fclean $(LIB_TARGET) $(NAME)
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# Mr. clean
.PHONY: 	clean
clean:
	@$(RM) $(OBJ) $(TOBJ)
	@$(RM) $(TOBJ:.o=.gcno) $(TOBJ:.o=.gcda) $(OBJ:.o=.gcno) $(OBJ:.o=.gcda)
	@$(RM) vgcore.*

.PHONY: 	fclean
fclean:		CURR_RULE = fclean
fclean:		init clean
	@$(MAKE) -C $(dir $(LIB_TARGET)) fclean -s
	@$(RM) $(NAME) $(TNAME)
	@echo -e $(GREEN)'-> [finished]: $(NAME): $(CURR_RULE)'$(RESET)
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# Re
.PHONY: 	re
re:		CURR_RULE = re
re:		init
	@$(MAKE) fclean -s
	@$(MAKE) all -s
	@echo -e $(GREEN)'-> [finished]: $(NAME): $(CURR_RULE)'$(RESET)
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# Test
.PHONY: tests_run
tests_run: cr_tests_run

.PHONY: cr_tests_run
cr_tests_run: LDFLAGS += $(CR_TEST_LDFLAGS)
cr_tests_run: CFLAGS += $(TFLAGS)
cr_tests_run: fclean $(LIB_TARGET) $(TOBJ)
	@$(CC) $(TOBJ) -o $(TNAME) $(LDFLAGS) $(CFLAGS)
	@./$(TNAME)
	@gcovr --exclude tests/
	@gcovr --exclude tests/ --branch

.PHONY: fn_tests_run
fn_tests_run: LDFLAGS += $(FN_TEST_LDFLAGS)
fn_tests_run: CFLAGS += $(TFLAGS)
fn_tests_run: fclean $(LIB_TARGET) $(OBJ)
	@$(CC) $(OBJ) -o $(TNAME) $(LDFLAGS) $(CFLAGS)
	@./tests/fn_tests.sh ./$(TNAME)
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# Prety Print
.PHONY: init
init:
	@echo -e $(CYAN)'-> [starting]: $(NAME): make $(CURR_RULE)'$(RESET)
# ----------------------------------------------------------------------------
