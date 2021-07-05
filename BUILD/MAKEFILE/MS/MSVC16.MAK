!IF !$d(SRC)
!  ERROR You must define a variable named SRC in your PARTS file
!ENDIF

!IF !$d(SRC_DIRS)
!  ERROR You must define a variable named SRC_DIRS in your PARTS file
!ENDIF

!IF !$d(TARGET)
!  ERROR You must define a variable named TARGET in your PARTS file
!ENDIF

COMPLETE_SRC = $(SRC) $(SRC_16BIT)
OBJ_PASS1 = $(COMPLETE_SRC:.C=.OBJ)
OBJ = $(OBJ_PASS1:.ASM=.OBJ)

.autodepend
.path.c = ../../$(SRC_DIRS:;=;../../)
.path.asm = ../../$(SRC_DIRS:;=;../../)

CC = cl
CFLAGS = -I../../$(SRC_DIRS:;=;../../) -ID:\INCLUDE
LDFLAGS = -LD:\LIB

$(TARGET): $(OBJ)
	LINK /STACK:5000 $(OBJ), $(TARGET), nul, , nul

.c.obj:
	$(CC) /c $(CFLAGS) /Fo$&.OBJ $*.C

.asm.obj:
	NASM -f OBJ -o $&.OBJ $*.ASM

clean:
	DEL *.OBJ
	DEL *.EXE
	DEL *.MAP
