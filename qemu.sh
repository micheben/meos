#!/bin/sh
set -e
. ./iso.sh

qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom meos.iso  -no-reboot -no-shutdown #-gdb 
