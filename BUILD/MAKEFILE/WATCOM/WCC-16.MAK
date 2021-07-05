# SRC SRC_DIRS TARGET

COMPLETE_SRC = $(SRC) $(SRC_16BIT)
OBJ = $(COMPLETE_SRC:.C=.OBJ)
OBJ = $(OBJ:.ASM=.OBJ)

!ifdef MODEL 

!ifeq MODEL SMALL
MODEL_CFLAGS = -ms
!else ifeq MODEL MEDIUM
MODEL_CFLAGS = -ms
!else ifeq MODEL COMPACT
MODEL_CFLAGS = -mc
!else ifeq MODEL LARGE
MODEL_CFLAGS = -ml
!else ifeq MODEL HUGE
MODEL_CFLAGS = -mh
!else
!error Unsupported model specified
!endif

!else
MODEL_CFLAGS = -ms
!endif

CFLAGS=-0 -d0 -wx -zq -bt=DOS 
.EXTENSIONS: .asm

.c: ../../$(SRC_DIRS:;=;../../)
.asm: ../../$(SRC_DIRS:;=;../../)

$(TARGET): $(OBJ)
	WLINK \
	OPTION QUIET SYSTEM DOS \
	NAME $(TARGET) FILE { $(OBJ) }

.c.obj: .AUTODEPEND
	@ECHO $[@
	WCC $(CFLAGS) $(WCC_DEFS) $(MODEL_CFLAGS) -i=..\..\..\..\..\H -fo=$^& $[@

.asm.obj:
	NASM -f OBJ -o $^&.OBJ $[@

clean: .SYMBOLIC
	IF EXIST *.EXE DEL /Q *.EXE
	IF EXIST *.OBJ DEL /Q *.OBJ
	IF EXIST *.MAP DEL /Q *.MAP
	IF EXIST *.ERR DEL /Q *.ERR