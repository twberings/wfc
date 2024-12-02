CXX := g++
EMXX := em++
CXXFLAGS := --debug -Wall -Werror -Wextra -pedantic -Iinclude -std=c++17
EMXXFLAGS := -s EXPORTED_RUNTIME_METHODS=[FS] -lembind --embed-file ./web/tilesets/circuit

SRC_DIR := src
TEST_DIR := test
BUILD_DIR := build
WASM_EXTRA_DIR := web
WASM_DIR := web/build
PUML_FILE := diagrams/class_diagram.puml
SVG_FILE := diagrams/class_diagram.svg
CLANG_UML := .clang-uml

MAIN_FILE := $(SRC_DIR)/main.cpp
COMMON_FILES := $(filter-out $(MAIN_FILE), $(wildcard $(SRC_DIR)/*.cpp))
WASM_FILES := $(wildcard $(WASM_EXTRA_DIR)/*.cpp)
TEST_FILES := $(wildcard $(TEST_DIR)/*.cpp)

COMMON_OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(COMMON_FILES))
MAIN_OBJ_FILE := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(MAIN_FILE))
TEST_OBJ_FILES := $(patsubst $(TEST_DIR)/%.cpp,$(BUILD_DIR)/test_%.o,$(TEST_FILES))
WASM_OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(WASM_DIR)/%.o,$(COMMON_FILES))
WASM_EXTRA_OBJ_FILES := $(patsubst $(WASM_EXTRA_DIR)/%.cpp,$(WASM_DIR)/%.o,$(WASM_FILES))

GTEST_LIB := -lgtest -lgtest_main -lgmock -lgmock_main -lpthread
TEST_INCLUDE := -Itest

TARGET := $(BUILD_DIR)/app
TEST_TARGET := $(BUILD_DIR)/test
WEB_TARGET := $(WASM_DIR)/app.js

all: $(TARGET) $(TEST_TARGET) $(WEB_TARGET)

$(TARGET): $(COMMON_OBJ_FILES) $(MAIN_OBJ_FILE)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(COMMON_OBJ_FILES) $(MAIN_OBJ_FILE) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(WASM_OBJ_FILES): $(WASM_DIR)/%.o : $(SRC_DIR)/%.cpp $(COMMON_FILES)
	@mkdir -p $(WASM_DIR)
	$(EMXX) $(CXXFLAGS) -c $< -o $@

$(WASM_EXTRA_OBJ_FILES): $(WASM_FILES)
	@mkdir -p $(WASM_DIR)
	$(EMXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

web: $(WEB_TARGET)
	@node $(WEB_TARGET)

$(WEB_TARGET): $(WASM_OBJ_FILES) $(WASM_EXTRA_OBJ_FILES)
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(WASM_DIR)
	$(EMXX) $(EMXXFLAGS) $(WASM_OBJ_FILES) $(WASM_EXTRA_OBJ_FILES) -o $(WEB_TARGET)

$(TEST_TARGET): $(COMMON_OBJ_FILES) $(TEST_OBJ_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(COMMON_OBJ_FILES) $(TEST_OBJ_FILES) -o $(TEST_TARGET) $(GTEST_LIB)

$(BUILD_DIR)/test_%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_INCLUDE) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(WASM_DIR)

diagram: $(SVG_FILE)

$(SVG_FILE): $(PUML_FILE)
	@plantuml -tsvg $<

$(PUML_FILE): $(COMMON_FILES) $(CLANG_UML)
	@clang-uml

.PHONY: all clean test run diagram web
