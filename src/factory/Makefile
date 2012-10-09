# XOgastan makefile

include ../Makefile.incl 



all: $(FACTORY_OBJ)
	@echo "factory classes *.o done."; echo;

controlMachine.o:controlMachine.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $< 

operativeMachine.o:operativeMachine.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $< 

gxl_attr.o:gxl_attr.cpp 
	${CXX} ${CMP} $(INCLUDE) -o $@ $< 

gxl_edge.o:gxl_edge.cpp 
	${CXX} ${CMP} $(INCLUDE) -o $@ $< 

prepare_bin:
	@cp -vf *.o ../bin; echo "copied factory *.o in bin directory";

clean:
	@rm -vf *.o; echo "factory classes *.o removed";





