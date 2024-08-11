CC:=gcc
FLAGS:= -std=c17 -Wall -Wextra -Wpedantic -g -fstack-usage 
C_SRC:= $(wildcard ./src/*.c)
INCLUDE:= -I./include
TARGET:=prog
all:
	$(CC) $(FLAGS) $(C_SRC) $(INCLUDE) -o ./bin/$(TARGET) && ./bin/$(TARGET)