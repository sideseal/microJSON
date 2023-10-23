CC = c++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++98
LDFLAGS =
INCLUDE = -I.
RM = rm -rf

SRCDIR = .
OBJDIR = ./obj
SRCS = $(notdir $(wildcard $(SRCDIR)/*.cpp))
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)
OBJECTS = $(patsubst %.o,$(OBJDIR)/%.o,$(OBJS))

NAME = a.out

all: $(NAME)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p obj
	$(CC) $(CXXFLAGS) $(INCLUDE) -c $< -o $@ -MD $(LDFLAGS)

$(NAME): $(OBJECTS)
	$(CC) $(CXXFLAGS) $(OBJECTS) -o $(NAME) $(LDFLAGS)

.PHONY: all clean fclean re

clean:
	$(RM) $(OBJECTS) $(DEPS)
	$(RM) ./obj

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

-include $(DEPS)
