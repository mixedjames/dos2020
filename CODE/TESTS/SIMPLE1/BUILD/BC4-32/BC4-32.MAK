!IF !$d(SRC)
!  ERROR You must define a variable named SRC in your PARTS file
!ENDIF

!IF !$d(SRC_DIRS)
!  ERROR You must define a variable named SRC_DIRS in your PARTS file
!ENDIF

!IF !$d(TARGET)
!  ERROR You must define a variable named TARGET in your PARTS file
!ENDIF

COMPLETE_SRC = $(SRC) $(SRC_32BIT)
OBJ_PASS1 = $(COMPLETE_SRC:.C=.OBJ)
OBJ = $(OBJ_PASS1:.ASM=.OBJ)

CC = BCC32

.autodepend
.path.c = ../../$(SRC_DIRS:;=;../../);.
.path.asm = ../../$(SRC_DIRS:;=;../../)

CFLAGS = -I../../$(SRC_DIRS:;=;../../) -ID:\INCLUDE
LDFLAGS = -LC:\BC5\LIB

$(TARGET): $(OBJ)
	@ECHO $(OBJ) > OBJFILES.RSP
	TLINK32 -Tpe -ax -LD:\LIB C0X32 @OBJFILES.RSP, $(TARGET), , CW32 DPMI32

.c.obj:
	$(CC) -WX $(CFLAGS) -c -o$&.OBJ $*.C

.asm.obj:
	NASM -f obj -o $&.OBJ $*.ASM

clean:
	DEL *.OBJ
	DEL *.EXE
	DEL *.MAP
	DEL *.RSP
