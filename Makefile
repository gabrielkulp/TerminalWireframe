CC = gcc
EXE = test
SOURCES = math_3d.c buffer.c graphics.c wireframe.c main.c
FLAGS = -g -Wall -lm -O3

$(EXE): $(SOURCES)
	$(CC) $(FLAGS) $(SOURCES) -o $(EXE)

.PHONY: run
run: $(EXE)
	./$(EXE)

.PHONY: clean
clean:
	rm -rf $(EXE) *.o a.out

.PHONY: mem
mem: $(EXE)
	valgrind -v --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(EXE)

.PHONY: stats
stats:
	@echo Line counts:
	@wc -l *.c *.h
