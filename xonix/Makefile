APP := xonix

DIR_BIN=bin

CFLAGS += -Wall -pedantic -fPIC -std=c++17 -MMD -MP
LDFLAGS += -lstdc++ -lncurses

OBJ_APP = $(patsubst %.cpp,$(DIR_BIN)/%.o,$(wildcard *.cpp))
DEPS = $(OBJ_APP:.o=.d)
APP_FILE=$(DIR_BIN)/$(APP)

all: $(APP_FILE)

bin_dir:
	@mkdir -p $(DIR_BIN)

$(DIR_BIN)/%.o: %.cpp | bin_dir
	@echo "Compiling $@"
	@$(CXX) -c $(CFLAGS) $< -o $@

$(APP_FILE): $(OBJ_APP)
	@echo "Linking $@"
	@$(CXX) $^ -o $@  $(LDFLAGS)

-include $(DEPS)

clean:
	@rm -rf $(DIR_BIN)
	@#$(MAKE) -C tests/ clean --no-print-directory 

check: $(APP)
	@#$(MAKE) -C tests/ check --no-print-directory 

show:
	@echo "OBJ_APP: $(OBJ_APP)"
	@echo "DEPS: $(DEPS)"

.PHONY: show clean all check bin_dir
