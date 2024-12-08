CXX := g++
CXXFLAGS := -std=c++20 -Wall -O2

SRCS := main.cpp

TARGET := main.out

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

.PHONY: all clean
