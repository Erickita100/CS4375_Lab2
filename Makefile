run: main.c tokenizer.c bash.c
	gcc main.c  tokenizer.c bash.c -o run
clean:
	rm run
