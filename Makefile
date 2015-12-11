# Declaration of variables
CC=g++
CC_FLAGS=-w -lSDL -lSDL_image -lSDL_ttf

# File names
EXEC=Adventurous
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(CC_FLAGS) -o $(EXEC)
# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(OBJECTS)
