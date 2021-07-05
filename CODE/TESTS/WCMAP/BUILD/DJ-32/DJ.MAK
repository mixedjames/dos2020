COMPLETE_SRC = $(SRC) $(SRC_32BIT) $(SRC_DJGPP)

OBJ = $(patsubst %.C, %.O, \
        $(patsubst %.ASM, %.O, $(COMPLETE_SRC))\
      )

VPATH = ../../$(subst ;,;../../,$(SRC_DIRS))

$(TARGET): $(OBJ)
	$(CC) -Wl,-T,LINKER.TXT -Wl,-Map=../../SRC/MAPS/MAP-DJ.MAP -o $(TARGET) $(OBJ)

clean:
	DEL *.O
	DEL *.D
	DEL *.EXE

%.O : %.C
	$(CC) -MMD -c -x c $(CFLAGS) $< -o $@

%.O : %.ASM
	NASM -MD $(basename $@).D -f coff -o $@ $<

-include $(subst .O,.D,$(OBJ))