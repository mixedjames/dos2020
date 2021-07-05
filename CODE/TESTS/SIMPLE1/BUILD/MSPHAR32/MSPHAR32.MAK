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

.autodepend
.path.c = ../../$(SRC_DIRS:;=;../../)
.path.asm = ../../$(SRC_DIRS:;=;../../)

CC = cl386
CFLAGS = -I../../$(SRC_DIRS:;=;../../) -ID:\INCLUDE -ID:\MSTOOLS\H
LDFLAGS = -LD:\LIB

$(TARGET): $(OBJ)
	386link -exe $(TARGET) @LINK.TXT $(OBJ)

.c.obj:
	$(CC) /c $(CFLAGS) /Fo$&.OBJ $*.C

.asm.obj:
	NASM -f OBJ -o $&.OBJ $*.ASM

clean:
	DEL *.OBJ
	DEL *.EXE
	DEL *.MAP
