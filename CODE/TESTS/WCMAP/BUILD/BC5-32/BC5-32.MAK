!IF !$d(SRC)
!  ERROR You must define a variable named SRC in your PARTS file
!ENDIF

!IF !$d(SRC_DIRS)
!  ERROR You must define a variable named SRC_DIRS in your PARTS file
!ENDIF

!IF !$d(TARGET)
!  ERROR You must define a variable named TARGET in your PARTS file
!ENDIF

COMPLETE_SRC = $(SRC) $(SRC_32BIT) $(SRC_BORLAND) BC5.C
OBJ_PASS1 = $(COMPLETE_SRC:.C=.OBJ)
OBJ = $(OBJ_PASS1:.ASM=.OBJ)

CC = BCC32

.autodepend
.path.c = ../../$(SRC_DIRS:;=;../../);.
.path.asm = ../../$(SRC_DIRS:;=;../../)

CFLAGS = -I../../$(SRC_DIRS:;=;../../) -IC:\BC5\INCLUDE
LDFLAGS = -LC:\BC5\LIB

$(TARGET): $(OBJ)
	@ECHO $(OBJ) > OBJFILES.RSP
	TLINK32 -Tpe -ax -m -LC:\BC5\LIB C0X32 @OBJFILES.RSP, $(TARGET), MAP-BC32, CW32 DPMI32
	@COPY MAP-BC32.MAP ..\..\SRC\MAPS

BC5.OBJ: BC5.C
	$(CC) -WX $(CFLAGS) -c -oBC5.OBJ BC5.C

SECTION2.OBJ: ../../SRC/SECTION2.C
	$(CC) -WX -zRLOCKDATA -zDLOCKDAT2 $(CFLAGS) -c -o$&.OBJ ../../SRC/$*.C

.c.obj:
	$(CC) -WX $(CFLAGS) -c -o$&.OBJ $*.C

.asm.obj:
	NASM -f obj -o $&.OBJ $*.ASM

clean:
	DEL *.OBJ
	DEL *.EXE
	DEL *.MAP
