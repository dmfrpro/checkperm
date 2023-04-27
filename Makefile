SRC_DIR := src
BUILD_DIR := build
CFLAGS := -g -Wall

all: $(OBJS)
	$(shell mkdir -p ${BUILD_DIR})
	$(shell gcc ${SRC_DIR}/main.c ${SRC_DIR}/argresolver.c ${SRC_DIR}/argerror.c -o ${BUILD_DIR}/checkperm)

clean:
    $(shell rm -rf $(BUILD_DIR)/*)
