APP := qsort

CFLAGS += -Wall -pedantic -fPIC -std=c++17 -MMD
LDFLAGS += -lstdc++

OBJ_APP = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
DEPS = $(OBJ_APP:.o=.d)

-include $(DEPS)

all: $(APP)

%.o: %.cpp
	@echo "Compiling $@"
	@$(CXX) -c $(CFLAGS) $< -o $@

$(APP): $(OBJ_APP)
	@echo "Linking $@"
	@$(CXX) $^ -o $@  $(LDFLAGS)

clean:
	@rm -f *.o *.d $(APP)
	@$(MAKE) -C tests/ clean --no-print-directory 

check: $(APP)
	@$(MAKE) -C tests/ check --no-print-directory 

show:
	@echo "OBJ_APP: $(OBJ_APP)"
	@echo "DEPS: $(DEPS)"

.PHONY: show clean all check
