SRCS = $(wildcard *.c)

PROGS = $(patsubst %.c,%,$(SRCS))

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ -lpthread -fopenmp -lm
	./$@

.PHONY: clean


clean: 
	rm -f $(PROGS)