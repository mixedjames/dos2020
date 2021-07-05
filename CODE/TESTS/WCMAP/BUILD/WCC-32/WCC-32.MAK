# SRC SRC_DIRS TARGET

COMPLETE_SRC = $(SRC) $(SRC_32BIT) $(SRC_WATCOM)
OBJ = $(COMPLETE_SRC:.C=.OBJ)
OBJ = $(OBJ:.ASM=.OBJ)

CFLAGS= -l=dos4g 
.EXTENSIONS: .asm

.c: ../../$(SRC_DIRS:;=;../../)
.asm: ../../$(SRC_DIRS:;=;../../)

$(TARGET): $(OBJ)
	WLINK \
	OPTION QUIET SYSTEM DOS4G \
	OPTION MAP=..\..\SRC\MAPS\MAP-W32.MAP\
	NAME $(TARGET) FILE { $(OBJ) }

.c.obj: .AUTODEPEND
	@ECHO $[@
	WCL386 -c -fo=$^& $[@

.asm.obj:
	NASM -f OBJ -o $^&.OBJ $[@

clean: .SYMBOLIC
	IF EXIST *.EXE DEL /Q *.EXE
	IF EXIST *.OBJ DEL /Q *.OBJ
	IF EXIST *.MAP DEL /Q *.MAP
	IF EXIST *.ERR DEL /Q *.ERR