run: main.c tokenizer.c
	gcc main.c  tokenizer.c -o run
clean:
	rm run
