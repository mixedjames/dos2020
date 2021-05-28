# SRC SRC_DIRS TARGET

COMPLETE_SRC = $(SRC) $(SRC_16BIT)
OBJ = $(COMPLETE_SRC:.C=.OBJ)
OBJ = $(OBJ:.ASM=.OBJ)

CFLAGS=-0 -d0 -ms -wx -zq -bt=DOS
.EXTENSIONS: .asm

.c: ../../$(SRC_DIRS:;=;../../)
.asm: ../../$(SRC_DIRS:;=;../../)

$(TARGET): $(OBJ)
	WLINK \
	OPTION QUIET SYSTEM DOS \
	NAME $(TARGET) FILE { $(OBJ) }

.c.obj: .AUTODEPEND
	@ECHO $[@
	WCC $(CFLAGS) $(WCC_DEFS) -i=..\INCLUDE -fo=$^& $[@

.asm.obj:
	NASM -f OBJ -o $^&.OBJ $[@

clean: .SYMBOLIC
	IF EXIST *.EXE DEL /Q *.EXE
	IF EXIST *.OBJ DEL /Q *.OBJ
	IF EXIST *.MAP DEL /Q *.MAP
	IF EXIST *.ERR DEL /Q *.ERR