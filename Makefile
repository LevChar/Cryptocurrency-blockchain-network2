CFLAGS=-Wall -g
LDFLAGS=-lm -lpthread -lz
CC=gcc -std=gnu11
ECHO=echo "going to compile for target $@"
SRCDIR=src
MAIN_FILE=bitcoin_driver
PROG=$(MAIN_FILE)
PROG_OBJS=bitcoin.o miner.o server.o utility.o linked_list.o driver.o

$(PROG): $(PROG_OBJS)
	@$(ECHO)
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o $(PROG)

%.o: $(SRCDIR)/%.c
	@$(ECHO)
	@$(CC) -c $< $(CFLAGS)

test:
	@echo going to run test...
	sudo ./$(PROG)

clean:
	rm -vf $(PROG)

clean_all: clean
	rm -vf *.o *.gch
