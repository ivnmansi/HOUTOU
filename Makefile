CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -lallegro -lallegro_font -lallegro_ttf -lallegro_image -lallegro_primitives -lallegro_audio -lallegro_acodec -lallegro_dialog
EXEC=HOUTOU.exe

SRC_DIR=src
OBJ_DIR=obj
SRC_FILES=$(wildcard $(SRC_DIR)/*.c)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
INCLUDE=-I./incs/

all: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o build/$(EXEC) $(OBJ_FILES) $(INCLUDE) $(LIBS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $^ $(INCLUDE)

.PHONY: clean folders
clean:
	@del /Q /F $(subst /,\,$(OBJ_FILES))
	@del /Q /F $(subst /,\,$(BUILD_DIR)/$(EXEC))

folders:
	@if not exist $(SRC_DIR) mkdir $(SRC_DIR)
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	@if not exist $(INCS_DIR) mkdir $(INCS_DIR)
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
