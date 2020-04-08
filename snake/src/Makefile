file_test: file.c file_test.c
	gcc file.c file_test.c game.c -o file_test.out -std=c99
game_test: game.c game_test.c
	gcc game.c game_test.c -o game_test.out -std=c99
game: file.c ai.c view.c game.c main.c
	gcc file.c ai.c view.c game.c main.c -o game.out -std=c99 
clean_file_test: 
	rm file_test.out
clean_game_test:
	rm game_test.out
clean_game:
	rm game.out
clean_all:
	rm file_test.out game_test.out game.out 
