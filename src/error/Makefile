# XOgastan makefile

include ../Makefile.incl



all: $(ERROR_OBJ)
	@echo "error classes *.o done."; echo;

bad_XOgastan.o:bad_XOgastan.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

prepare_bin:
	@cp -vf *.o ../bin; echo "copied error *.o in bin directory";

clean: 
	@rm -vf *.o; \
	echo "error classes *.o removed"; 
