all:
	cd bin && nasm ../src/boot.s -o boot
	nasm -f elf -g -F stabs src/utils.s -o bin/utils.o
	nasm -f elf -g -F stabs src/interrupt.s -o bin/interrupt.o
	nasm -f elf -g -F stabs src/switch_task.s -o bin/switch_task.o
	cd bin && x86_64-elf-gcc -m32 -c -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector ../src/*.c
	x86_64-elf-ld bin/*.o -e main -m elf_i386 -T kernel.ld -o ./bin/kernel
	dd if=/dev/zero of=bin/img bs=512 count=255
	dd if=bin/kernel of=bin/img conv=notrunc
debug:
	x86_64-elf-objdump -x bin/kernel
clean:
	rm bin/*