CXX := g++
CFLAGS := -std=c++2a
LIBS := -lSDL2 -lSDL2_image

APP = bin/engine

SRCS := $(wildcard *.cpp */*.cpp */*/*.cpp)
SRCS := $(filter-out $(wildcard test/*), $(SRCS))
OBJS := $(SRCS:%.cpp=obj/%.o)
DEPS := $(SRCS:%.cpp=dep/%.d)

test/bin/%: obj/test/%.o $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) $^ -o $@ $(LIBS) -I.

obj/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) -c $< -o $@ -I.

dep/%.d: %.cpp 
	@mkdir -p $(@D)
	@$(CXX) $(CFLAGS) $< -MM -MT $(@:dep/%.d=obj/%.o) > $@ -I.

-include $(DEPS)

clean:
	rm -r obj dep
