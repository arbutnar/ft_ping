NAME = ft_ping
HEADER = ft_ping.h
FLAGS = -Wall -Wextra -Werror -g

SOURCES_DIR = src
OBJECTS_DIR = obj

SOURCES = $(wildcard $(SOURCES_DIR)/*.c)
OBJECTS = $(addprefix $(OBJECTS_DIR)/, $(notdir $(SOURCES:.c=.o)))


all: $(NAME)

$(NAME): $(OBJECTS) $(HEADER)
	gcc -I. $(OBJECTS) -o $@

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c $(HEADER)
	mkdir -p $(OBJECTS_DIR)
	gcc $(FLAGS) -I. -c $< -o $@

clean:
	rm -rf $(OBJECTS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re