##
## EPITECH PROJECT, 2019
## Plazza
## File description:
## Plazza makefile
##

override CXXFLAGS	+=	-W -Wall -Wextra -I./include -std=c++2a
override LDFLAGS	+=

CXX_LOG		?=	[\033[32;1m✓\033[0m] $<$(END) \033[31;1m→\033[0m $@

DIR			=	./src/

SRC			=

OBJ_SRC		=	$(addprefix $(DIR), $(SRC:.cpp=.o))

SRC_MAIN	=	main.cpp

OBJ_MAIN	=	$(addprefix $(DIR), $(SRC_MAIN:.cpp=.o))

DIR_TEST	=	./tests/
SRC_TEST	=	catch2.cpp

OBJ_TEST	=	$(addprefix $(DIR_TEST), $(SRC_TEST:.cpp=.o))

BINARY_TEST	=	unit_tests
BINARY		=	plazza

all: $(BINARY)

SHD_PATH	=	./shd
SHD_MODULES	=	GUI THREADPOOL
include shd/shd.mk

$(BINARY_TEST):	CXXFLAGS	+= --coverage -I./tests/include
$(BINARY_TEST):	LDFLAGS		+= --coverage
$(BINARY_TEST):	$(OBJ_SRC) $(OBJ_TEST) $(SHD_OBJ) $(SHD_OBJ_TESTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BINARY):	$(OBJ_SRC) $(OBJ_MAIN) $(SHD_OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	@echo -e "\e[31;1mRemoving $(BINARY) temporary files\e[0m"
	@rm -f $(OBJ_SRC) $(OBJ_SRC:.o=.gcno) $(OBJ_SRC:.o=.gcda)
	@rm -f $(OBJ_TEST) $(OBJ_TEST:.o=.gcno) $(OBJ_TEST:.o=.gcda)
	@rm -f $(OBJ_MAIN) $(OBJ_MAIN:.o=.gcno) $(OBJ_MAIN:.o=.gcda)
	@rm -f $(SHD_OBJ) $(SHD_OBJ:.o=.gcno) $(SHD_OBJ:.o=.gcda)
	@rm -f $(SHD_OBJ_TESTS) $(SHD_OBJ_TESTS:.o=.gcno) $(SHD_OBJ_TESTS:.o=.gcda)
	@rm -rf gcovr

fclean:		clean
	@echo -e "\e[31;1mRemoving $(BINARY) file\e[0m"
	@rm -f $(BINARY)
	@rm -f $(BINARY_TEST)

tests_run:	clean $(BINARY_TEST)
	@echo -e "\e[34;1m\nUNIT TEST\n\e[0m"
	@./$(BINARY_TEST)

gcovr:	$(BINARY_TEST)
	@echo -e "\e[34;1m\nUNIT TEST\n\e[0m"
	@./$(BINARY_TEST)
	@echo -e "\e[34;1m\nCOVERAGE\n\e[0m"
	@mkdir -p gcovr; cd gcovr; gcovr -r ../ --exclude "../tests/" --exclude "../gcovr/" --exclude "../include/test/" --html --html-details --html-title $(BINARY) -o $(BINARY).html

re:		fclean all

%.o:	%.cpp
	@echo -e "${CXX_LOG}"
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

.PHONY:		all clean fclean re	tests_run	gcovr
