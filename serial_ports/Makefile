CFLAGS= -g

HEADER_FILES = c_src
SOURCE_FILES = c_src/serial.c

OBJECT_FILES = $(SOURCE_FILES:.c=.o)

priv_dir/serial: clean priv_dir $(OBJECT_FILES)
	mkdir -p priv_dir
	$(CC) -I $(HEADER_FILES) -o $@ $(LDFLAGS) $(OBJECT_FILES) $(LDLIBS)

priv_dir:
	mkdir -p priv_dir

clean:
	rm -f priv_dir/serial $(OBJECT_FILES) $(BEAM_FILES)
