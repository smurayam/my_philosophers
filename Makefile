NAME        = philo

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -pthread

# 今後作成するソースファイル名をここに追加していきます
SRCS        = main.c \
              # utils.c init.c routine.c monitor.c など

OBJS        = $(SRCS:.c=.o)

# デフォルトのターゲット
all: $(NAME)

# 実行ファイルの生成
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# オブジェクトファイルの削除
clean:
	rm -f $(OBJS)

# 実行ファイルとオブジェクトファイルの削除
fclean: clean
	rm -f $(NAME)

# 全て削除して再コンパイル
re: fclean all

# 同名のファイルが存在してもターゲットとして実行するための宣言
.PHONY: all clean fclean re
