!IF !$d(SRC)
!  ERROR You must define a variable named SRC in your PARTS file
!ENDIF

!IF !$d(SRC_DIRS)
!  ERROR You must define a variable named SRC_DIRS in your PARTS file
!ENDIF

!IF !$d(TARGET)
!  ERROR You must define a variable named TARGET in your PARTS file
!ENDIF

COMPLETE_SRC = $(SRC) $(SRC_32BIT) BC5-32.C
OBJ_PASS1 = $(COMPLETE_SRC:.C=.OBJ)
OBJ = $(OBJ_PASS1:.ASM=.OBJ)

CC = BCC32

.autodepend
.path.c = ../../$(SRC_DIRS:;=;../../);../../../BUILD/BORLAND
.path.asm = ../../$(SRC_DIRS:;=;../../)

CFLAGS = -I../../$(SRC_DIRS:;=;../../) -IC:\BC5\INCLUDE
LDFLAGS = -LC:\BC5\LIB

$(TARGET): $(OBJ)
	@ECHO $(OBJ) > OBJFILES.RSP
	TLINK32 -LC:\BC5\LIB C0X32 @OBJFILES.RSP, $(TARGET), , CW32 DPMI32

BC5-32.OBJ: BC5-32.C
	$(CC) -WX $(CFLAGS) -c -oBC5-32.OBJ ../../../BUILD/BORLAND/BC5-32.C

.c.obj:
	$(CC) -WX $(CFLAGS) -c -o$&.OBJ $*.C

.asm.obj:
	NASM -f obj -o $&.OBJ $*.ASM

clean:
	DEL *.OBJ
	DEL *.EXE
	DEL *.MAP
