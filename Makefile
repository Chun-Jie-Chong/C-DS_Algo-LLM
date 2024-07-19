CC = clang
CFLAGS = -Wall -I/opt/homebrew/Cellar/cunit/2.1-3/include
LDFLAGS = -L/opt/homebrew/Cellar/cunit/2.1-3/lib -lcunit

SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build
RESULT_FILE = test_results.txt

TEST_FILES = $(wildcard $(TEST_DIR)/*_test.c)

all: $(BUILD_DIR) run_tests

$(BUILD_DIR):
	@mkdir -p $@

$(BUILD_DIR)/%_test: $(TEST_DIR)/%_test.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

run_tests: $(patsubst $(TEST_DIR)/%_test.c, $(BUILD_DIR)/%_test, $(TEST_FILES))
	@echo "Running tests..." > $(RESULT_FILE)
	@for test in $^; do \
		echo "--------------------------------------------------------------------------------------" >> $(RESULT_FILE); \
		echo "Running $$test" >> $(RESULT_FILE); \
		./$$test >> $(RESULT_FILE) 2>&1; \
	done

clean:
	@rm -rf $(BUILD_DIR) $(RESULT_FILE)

