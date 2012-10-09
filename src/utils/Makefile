# XOgastan makefile

include ../Makefile.incl


all: $(UTILS_OBJ)
	@echo "utility functions and classes *.o done."; echo;

is_functions.o: is_functions.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

get_functions.o: get_functions.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

print_warning.o: print_warning.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

a2b.o: a2b.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

dot2gif.o: dot2gif.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

prepare_bin:
	@cp -vf *.o ../bin; echo "copied  utils *.o in bin directory";

clean: 
	@rm -vf *.o; \
	echo "utility functions and classes *.o removed"; 

