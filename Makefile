CC = cc
CFLAGS = -O2 -Wall -Wextra -lm
TARGET = brodsky

all: $(TARGET)

$(TARGET): brodsky.c inhale/en.h inhale/ru.h inhale/he.h inhale/fr.h inhale/es.h
	$(CC) $(CFLAGS) -o $@ brodsky.c

clean:
	rm -f $(TARGET) brodsky.spore

test: $(TARGET)
	echo "exile" | ./$(TARGET) --seed 42

test-tensions: $(TARGET)
	./$(TARGET) --test-tensions

.PHONY: all clean test test-tensions
