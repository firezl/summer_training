object = main.o stats.o search.o
search-cli: $(object)
	cc -o search-cli $(object)

main.o: main.c stats.h search.h
	cc -c main.c

stats.o: stats.c search.h
	cc -c stats.c

search.o: search.h
	cc -c search.c
clean:
	-rm $(object)