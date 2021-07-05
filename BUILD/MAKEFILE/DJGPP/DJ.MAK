COMPLETE_SRC = $(SRC) $(SRC_32BIT)

OBJ = $(patsubst %.C, %.O, \
        $(patsubst %.ASM, %.O, $(COMPLETE_SRC))\
      )

VPATH = ../../$(subst ;,;../../,$(SRC_DIRS))

CFLAGS = -MMD -x c -IC:/H

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

clean:
	DEL *.O
	DEL *.D
	DEL *.EXE

%.O : %.C
	$(CC) -c $(CFLAGS) $< -o $@

%.O : %.ASM
	NASM -MD $(basename $@).D -f coff -o $@ $<

-include $(subst .O,.D,$(OBJ))