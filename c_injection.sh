# !/bin/bash
O_FILENAME=final # now you can change this i think PogChamp
BUILD_DIR=build/c_injection
LDFILE=$BUILD_DIR/c_injection.ld
QEMU_IRIX=/mnt/c/qemu-irix
OPT_FLAGS="-O2 -g3"

C_FILE=${1}

V_ADDR=${2}

mkdir -p $BUILD_DIR

$QEMU_IRIX -silent -L tools/ido5.3_compiler tools/ido5.3_compiler/usr/bin/cc \
	-c -Wab,-r4300_mul -non_shared -G 0 -Xcpluscomm -Xfullwarn -signed -g \
	-nostdinc -I include/libc -DTARGET_N64 -D_LANGUAGE_C \
	-I include -I build/us -I build/us/include -I src -I . \
	-DVERSION_US $OPT_FLAGS -mips2 -DF3D_OLD -32 -o $BUILD_DIR/$O_FILENAME.o $C_FILE

echo "SECTIONS" > $LDFILE
echo "{" >> $LDFILE
echo "    __romPos = 0x0;" >> $LDFILE
echo "    .name $V_ADDR : AT(__romPos){" >> $LDFILE
echo "        $BUILD_DIR/$O_FILENAME.o(.text*);" >> $LDFILE
echo "        $BUILD_DIR/$O_FILENAME.o(.data*);" >> $LDFILE
echo "        $BUILD_DIR/$O_FILENAME.o(.rodata*);" >> $LDFILE
echo "        $BUILD_DIR/$O_FILENAME.o(.bss*);" >> $LDFILE
echo "    }" >> $LDFILE
echo "    /DISCARD/ :" >> $LDFILE
echo "    {" >> $LDFILE
echo "        *(*);" >> $LDFILE
echo "    }" >> $LDFILE
echo "}" >> $LDFILE

mips-linux-gnu-ld -T syms.txt -T $LDFILE -Map $BUILD_DIR/c_injection.map -o $BUILD_DIR/$O_FILENAME.elf $BUILD_DIR/$O_FILENAME.o

mips-linux-gnu-objcopy $BUILD_DIR/$O_FILENAME.elf $BUILD_DIR/$O_FILENAME.bin -O binary

python3 c_injection.py $BUILD_DIR/c_injection.map $BUILD_DIR/$O_FILENAME.o
