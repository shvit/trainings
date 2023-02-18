APP := xonix

DIR_BIN=bin
DIR_SRC=src
DIR_TST=$(DIR_SRC)/tests

CFLAGS += -Wall -pedantic -fPIC -std=c++17 -MMD -MP
LDFLAGS += -lstdc++ -lncurses


OBJ_APP = $(patsubst $(DIR_SRC)/%.cpp,$(DIR_BIN)/%.o,$(wildcard $(DIR_SRC)/*.cpp))
DEPS = $(OBJ_APP:.o=.d)
APP_FILE=$(DIR_BIN)/$(APP)

all: $(APP_FILE)

bin_dir:
	@mkdir -p $(DIR_BIN)

$(DIR_BIN)/%.o: $(DIR_SRC)/%.cpp | bin_dir
	@echo "Compiling $@"
	@$(CXX) -c $(CFLAGS) $< -o $@

$(APP_FILE): $(OBJ_APP)
	@echo "Linking $@"
	@$(CXX) $^ -o $@  $(LDFLAGS)

-include $(DEPS)

clean:
	@rm -rf $(DIR_BIN)/
	@$(MAKE) -C $(DIR_TST)/ clean --no-print-directory 

check: $(APP)
	@$(MAKE) -C $(DIR_TST)/ check --no-print-directory 

show:
	@echo "OBJ_APP: $(OBJ_APP)"
	@echo "DEPS: $(DEPS)"
	@echo "$(DIR_TST):"
	@$(MAKE) -C $(DIR_TST)/ show --no-print-directory 

.PHONY: show clean all check bin_dir
