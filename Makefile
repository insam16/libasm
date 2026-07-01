NAME		= libasm.a

SRCS_DIR	= srcs
BONUS_DIR	= srcs_bonus
OBJS_DIR	= objs

SRCS		= \
				ft_strlen.s \
				ft_strcpy.s \
				ft_strcmp.s \
				ft_write.s \
				ft_read.s \
				ft_strdup.s
SRCS_BONUS	= \
				ft_atoi_base.s \
				ft_list_push_front.s \
				ft_list_size.s \
				ft_list_sort.s \
				ft_list_remove_if.s

OBJS		= $(SRCS:%.s=$(OBJS_DIR)/%.o)
OBJS_BONUS	= $(SRCS_BONUS:%.s=$(OBJS_DIR)/%.o)

ASM			= nasm
ASMFLAGS	= -f elf64

AR			= ar
ARFLAGS		= rcs

all: $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.s | $(OBJS_DIR)
	$(ASM) $(ASMFLAGS) $< -o $@

$(OBJS_DIR)/%.o: $(BONUS_DIR)/%.s | $(OBJS_DIR)
	$(ASM) $(ASMFLAGS) $< -o $@

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

bonus: (OBJS) $(OBJS_BONUS)
	$(AR) $(ARFLAGS) $@ $^

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: $(NAME)
	gcc -Wall -Wextra -Werror main.c $(NAME) -o test
	./test

.PHONY: all bonus clean fclean re test 
