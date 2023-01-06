APP := test

EXT_DEPENDS := ../VectorQSort.o

CFLAGS += -Wall -pedantic -fPIC -std=c++17 -MMD
LDFLAGS += -lstdc++

OBJ_APP = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
DEPS = $(OBJ_APP:.o=.d)

-include $(DEPS)

all: $(APP)

%.o: %.cpp
	@echo "Compiling $@"
	@$(CXX) -c $(CFLAGS) $< -o $@

$(APP): $(OBJ_APP) $(EXT_DEPENDS)
	@echo "Linking $@"
	@$(CXX) $^ -o $@ -lboost_unit_test_framework $(LDFLAGS) 

clean:
	@rm -f *.o *.d $(APP)

check: $(APP)
	@./$(APP)

show:
	@echo "OBJ_APP: $(OBJ_APP)"
	@echo "DEPS: $(DEPS)"

.PHONY: show clean all check
