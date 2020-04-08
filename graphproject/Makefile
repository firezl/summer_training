object = main.o stats.o search.o
search-cli: $(object)
	gcc -o search-cli $(object) -std=c99

main.o: main.c stats.h search.h
	gcc -c main.c -std=c99

stats.o: stats.c search.h
	gcc -c stats.c -std=c99

search.o: search.h
	gcc -c search.c -std=c99
clean:
	rm $(object)
