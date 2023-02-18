APP := test

DIR_BIN=bin

CFLAGS += -Wall -pedantic -fPIC -std=c++17 -MMD
LDFLAGS += -lstdc++ -lncurses

OBJ_APP = $(patsubst %.cpp,$(DIR_BIN)/%.o,$(wildcard *.cpp))
DEPS = $(OBJ_APP:.o=.d)
OBJ_APP_MAIN = $(patsubst %_test.cpp,../../bin/%.o,$(wildcard *_test.cpp))
APP_FILE=$(DIR_BIN)/$(APP)


-include $(DEPS)

all: $(APP_FILE)

bin_dir:
	@mkdir -p $(DIR_BIN)

$(DIR_BIN)/%.o: %.cpp | bin_dir
	@echo "Compiling $@"
	@$(CXX) -c $(CFLAGS) $< -o $@

$(APP_FILE): $(OBJ_APP) $(OBJ_APP_MAIN)
	@echo "Linking $@"
	@$(CXX) $^ -o $@ -lboost_unit_test_framework $(LDFLAGS) 

clean:
	@rm -rf $(DIR_BIN)/

check: $(APP_FILE)
	@./$(APP_FILE)

show:
	@echo "OBJ_APP: $(OBJ_APP)"
	@echo "DEPS: $(DEPS)"
	@echo "OBJ_APP_MAIN: $(OBJ_APP_MAIN)"

.PHONY: show clean all check bin_dir
