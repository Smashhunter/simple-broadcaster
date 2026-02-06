# Компилятор и флаги
CC = gcc
CFLAGS = -I./include -Wall -Wextra -g
LDFLAGS = 

# Флаги для клиента (ncurses)
CLIENT_LIBS = -lncurses

# Директории
SRV_DIR = server
CLT_DIR = client
INC_DIR = include
BUILD_DIR = bin

# Цели сборки
SERVER_TARGET = $(BUILD_DIR)/broadcast-host
CLIENT_TARGET = $(BUILD_DIR)/broadcast-client

# Исходные файлы сервера
SRV_SOURCES = $(wildcard $(SRV_DIR)/*.c)
# Объектные файлы сервера
SRV_OBJECTS = $(patsubst $(SRV_DIR)/%.c, $(BUILD_DIR)/$(SRV_DIR)/%.o, $(SRV_SOURCES))

# Исходные файлы клиента
CLT_SOURCES = $(wildcard $(CLT_DIR)/*.c)
# Объектные файлы клиента
CLT_OBJECTS = $(patsubst $(CLT_DIR)/%.c, $(BUILD_DIR)/$(CLT_DIR)/%.o, $(CLT_SOURCES))

# Заголовочные файлы
HEADERS = $(wildcard $(INC_DIR)/*.h)

# Основная цель
all: $(SERVER_TARGET) $(CLIENT_TARGET)

# Сборка сервера
$(SERVER_TARGET): $(SRV_OBJECTS)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(LDFLAGS)

# Сборка клиента
$(CLIENT_TARGET): $(CLT_OBJECTS)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(LDFLAGS) $(CLIENT_LIBS)

# Компиляция объектных файлов сервера
$(BUILD_DIR)/$(SRV_DIR)/%.o: $(SRV_DIR)/%.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Компиляция объектных файлов клиента
$(BUILD_DIR)/$(CLT_DIR)/%.o: $(CLT_DIR)/%.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка
clean:
	rm -rf $(BUILD_DIR)

# Флаг для предотвращения конфликтов с файлами
.PHONY: all clean
