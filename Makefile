all:
	cd bin && nasm ../src/boot.s -o boot
	cd bin && x86_64-elf-gcc -m32 -c -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector ../src/*.c
	x86_64-elf-ld bin/*.o -e main -m elf_i386 -T kernel.ld -o ./bin/kernel
	dd if=/dev/zero of=bin/img bs=512 count=255
	dd if=bin/kernel of=bin/img conv=notrunc
clean:
	rm bin/*