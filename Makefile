include CONFIG.cfg

CC = gcc
LD = gcc

TEST_OK = ok
TEST_FAIL = fail

EXE = $(BUILD_DIR)/$(NAME)
OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/functions.o
LOGS = $(patsubst $(TEST_DIR)/%.in, $(TEST_DIR)/%.log, $(wildcard $(TEST_DIR)/*.in))

.PHONY: all clean check

all: $(EXE)


$(EXE): $(OBJS)

	$(LD) $(LDFLAGS) $^ -o $@


$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c | $(BUILD_DIR)

	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@	


$(BUILD_DIR):
	
	mkdir -p $@


check: $(LOGS)

	@for log in $^ ; do \
        if [ "$$(cat $${log})" != "$(TEST_OK_STAT)" ]; then \
            	exit 1; \
        fi; \
    done


$(TEST_DIR)/%.log: $(TEST_DIR)/%.in $(TEST_DIR)/%.out $(EXE)

	@if [ "$$(./$(EXE) ./$<)" = "$$(cat $(word 2, $^))" ]; then \
	echo "Test $< - passed"; \
        echo "$(TEST_OK_STAT)" > $@; \
    else \
    	echo "Test $< - fail"; \
        echo "$(TEST_FL_STAT)" > $@; \
    fi

    
clean:
	$(RM) $(OBJS) $(LOGS)
