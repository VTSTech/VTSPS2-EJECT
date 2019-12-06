EE_BIN = eject.elf
EE_OBJS = eject.o pad.o
EE_LIBS = -ldebug -lc -lcdvd -lpad

all: $(EE_BIN)

clean:
	rm -f $(EE_BIN) $(EE_OBJS)

run: $(EE_BIN)
	ps2client execee host:$(EE_BIN)

reset:
	ps2client reset

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal