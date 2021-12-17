clear
sudo docker run --rm -it -v "$(pwd)":/root/env myos-buildenv
qemu-system-x86_64 -cdrom dist/x86_64/kernel.iso
