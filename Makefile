VERSION = 0.4

EE_BIN = PS2Eject.ELF
EE_BIN_PACKED = PS2Eject-packed.ELF
EE_BIN_STRIPPED = PS2Eject-stripped.ELF
EE_OBJS = eject.o pad.o
EE_LIBS = -lc -lcdvd -lpatches -ldebug -lpad

all:
	@echo "======================================="
	@echo "=== Building PS2Eject v$(VERSION) ==="
	@echo "======================================="
	$(MAKE) $(EE_BIN_PACKED)

clean:
	@echo "================"
	@echo "=== Cleaning ==="
	@echo "================"
	rm -fr *.ELF *.o *.bak

run: $(EE_BIN)
	ps2client execee host:$(EE_BIN)

reset:
	ps2client reset

$(EE_BIN_STRIPPED): $(EE_BIN)
	@echo "================="
	@echo "=== Stripping ==="
	@echo "================="
	$(EE_STRIP) -o $@ $<
	
$(EE_BIN_PACKED): $(EE_BIN_STRIPPED)
	@echo "==================="
	@echo "=== Compressing ==="
	@echo "==================="
	~/ps2homebrew/ps2-packer/ps2-packer -v $< $@
	
include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal