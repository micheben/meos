SRCDIR   := src
BUILDDIR := build
SRCEXT   := c

SOURCES := $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))



runbin: bin
	qemu-system-i386 -kernel build/meos.bin

runiso: iso
	qemu-system-i386 -cdrom build/meos.iso

iso: bin
	rm -rf build/isodir/boot/grub
	mkdir -p build/isodir/boot/grub
	cp build/meos.bin build/isodir/boot/meos.bin
	cp grub.cfg build/isodir/boot/grub/grub.cfg
	grub-mkrescue -o build/meos.iso build/isodir

bin: boot.o $(OBJECTS)
	i686-elf-gcc -T linker.ld -o build/meos.bin -ffreestanding -O2 -nostdlib build/boot.o $(OBJECTS) -lgcc
	grub-file --is-x86-multiboot build/meos.bin

boot.o:
	mkdir -p build
	i686-elf-as src/boot.s -o build/boot.o

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(shell dirname $@)
	i686-elf-gcc -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

clean:
	rm -rf build

clear:
	rm -rf build
