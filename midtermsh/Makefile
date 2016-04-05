SOURCES=midtermsh.cpp
OBJFILES=$(SOURCES:.cpp=.o)
TARGET=midtermsh

all: $(TARGET)

$(TARGET): $(OBJFILES)
	g++ $^ -o $(TARGET)

.c.o:
	g++ -c $< -o $@

clean:
	rm -f $(TARGET)
	rm -f $(OBJFILES)
