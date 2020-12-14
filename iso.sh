#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/meos.kernel isodir/boot/meos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "meos" {
	multiboot /boot/meos.kernel
}
EOF
grub-mkrescue -o meos.iso isodir
