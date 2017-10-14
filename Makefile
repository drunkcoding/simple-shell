mainshell: src/buildin.c src/error_handler.c src/file_handler.c src/line_handler.c  src/lsh_loop.c src/main.c src/msg_prompt.c src/signal_handler.c
	clang -Werror -pedantic -O2 -std=gnu99 -o mainshell -I./includes/ src/buildin.c src/error_handler.c src/file_handler.c src/line_handler.c  src/lsh_loop.c src/main.c src/msg_prompt.c src/signal_handler.c

clean:
	rm -f mainshell

.PHONY: clean
