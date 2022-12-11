CXX = g++

EXECUTABLE = main

SOURCES = $(wildcrad *.cpp)

OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $^ -o $@ $(LDLIBS)

.cpp.o:

-include $(OBJECTS:.o=.d)