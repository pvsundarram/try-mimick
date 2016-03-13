
SRCS := $(shell find . -name '*.c')

all: test runtest

.PHONY: runtest

%.o: %.c
	cc -c -o $@ $<

test: $(subst .c,.o,$(SRCS))
	cc -o test $^ -lmimick

runtest:
	./test

clean:
	rm -rf *.o test
