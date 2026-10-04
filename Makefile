NAME = ft_ping
CC = gcc
FLAGS = -Wall -Wextra -Werror -g -std=gnu17

SOURCES_DIR = src
OBJECTS_DIR = build

HEADERS = $(wildcard $(SOURCES_DIR)/*.h)
SOURCES = $(wildcard $(SOURCES_DIR)/*.c)
OBJECTS = $(addprefix $(OBJECTS_DIR)/, $(notdir $(SOURCES:.c=.o)))

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c $(HEADERS) | $(OBJECTS_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJECTS_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJECTS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re