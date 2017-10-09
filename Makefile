all: compile execute

compile:
	@gcc main.c -o main_bin

execute:
	@./main_bin