# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
DEBUG_FLAGS = -g
RELEASE_FLAGS = -O2

# Директории
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build

# Цели
TARGET = graph_lib.a
TEST_TARGET = graph_test

# Исходные файлы
SRCS = $(SRC_DIR)/graph.c
TEST_SRCS = $(SRC_DIR)/graph.c $(TEST_DIR)/test_graph.c

# Объектные файлы
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)
TEST_OBJS = $(TEST_SRCS:%.c=$(BUILD_DIR)/%.o)

# Основная цель по умолчанию - статическая библиотека
all: $(TARGET)

# Создание статической библиотеки
$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	ar rcs $@ $^
	@echo "Статическая библиотека создана: $(TARGET)"

# Сборка и запуск тестов
test: $(TEST_TARGET)
	@echo "Запуск тестов..."
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $@ $^

# Компиляция объектных файлов
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c -o $@ $<

# Очистка
clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TEST_TARGET)

# Отладочная сборка
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

# Пересборка
rebuild: clean all

# Создание примера использования (опционально)
example: $(TARGET)
	@echo "Создание примера использования..."
	$(CC) $(CFLAGS) -o graph_example test/test_graph.c -L. -lgraph_lib
	@echo "Пример создан: graph_example"

# Помощь
help:
	@echo "Доступные команды:"
	@echo "  make all     - сборка статической библиотеки"
	@echo "  make test    - сборка и запуск тестов"
	@echo "  make debug   - отладочная сборка библиотеки"
	@echo "  make example - создание примера использования"
	@echo "  make clean   - очистка"
	@echo "  make rebuild - пересборка"
	@echo "  make help    - эта справка"

.PHONY: all test clean debug rebuild example help
