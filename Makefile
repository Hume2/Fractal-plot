SOURCES = $(wildcard *.cpp) $(wildcard engine/*.cpp) $(wildcard math/*.cpp) $(wildcard plot/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
DEPS = $(SOURCES:%.cpp=%.d)
TARGET = fg

CFLAGS = -std=gnu++14
LFLAGS = -lm -lSDL2

all: $(TARGET)

clean:
	rm $(DEPS) $(OBJECTS) $(TARGET)

.cpp.o:
	g++ -ggdb -MMD -MP $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	g++ $(OBJECTS) -o $(TARGET) $(LFLAGS)

-include $(DEPS)
