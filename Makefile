SRCS = src/main.cpp src/board_state.cpp src/frontier.cpp src/puzzle_solver.cpp
DEPS = include/board_state.h include/frontier.h include/puzzle_solver.h
INCLUDE_DIR = include
FLAGS = -O3

15_puzzle: $(SRCS) $(DEPS)
	g++ $(SRCS) $(DEPS) -I${INCLUDE_DIR} -o run ${FLAGS}

clean:
	rm -f ./run ./output.txt