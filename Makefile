OBJECTS := labwork3.o 
CC := clang

all: labwork3

labwork3: $(OBJECTS)
	$(CC) $(OBJECTS) -lpthread -o labwork3

%.o: %.c
	$(CC) -c -g $< -o $@

clean:
	rm -f *.o
