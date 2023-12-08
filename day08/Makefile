CXX := g++
CXXFLAGS := -std=c++17 -Wall -O2

SRCS := main.cpp

TARGET := main

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

.PHONY: all clean
