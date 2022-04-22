HEADERS := stats.h
SRC := stats.c wtbb.c
CFLAGS := -Os -std=c11

all: wtbb

strip: wtbb
	$(STRIP) wtbb

wtbb: $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(SRC) -o wtbb
