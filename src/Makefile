CC = gcc
CFLAGS = -Wall -Werror -Wextra
BUILD_DIR = ../build
TARGET_QUEST_1 = $(BUILD_DIR)/graph
SRC_DIR = .
INCLUDE_DIR = .

SRC_FILES_QUEST_1 = $(SRC_DIR)/graph.c $(SRC_DIR)/queue.c $(SRC_DIR)/stack.c $(SRC_DIR)/render.c $(SRC_DIR)/polish_notation.c $(SRC_DIR)/parser.c
HEADERS_QUEST_1 = $(SRC_DIR)/queue.h $(SRC_DIR)/stack.h $(SRC_DIR)/render.h $(SRC_DIR)/polish_notation.c $(SRC_DIR)/parser.h

all: queue_stack_test

queue_stack_test: $(SRC_FILES_QUEST_1) $(HEADERS_QUEST_1)
	$(CC) $(CFLAGS) -o $(TARGET_QUEST_1) $(SRC_FILES_QUEST_1) -lm

clean:
	rm -f $(TARGET_QUEST_1)

rebuild: clean all
