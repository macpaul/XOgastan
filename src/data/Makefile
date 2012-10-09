# XOgastan makefile

include ../Makefile.incl

all: $(DATA_OBJ)
	@echo "data classes *.o done."; echo;

fnctData.o:fnctData.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

declData.o:declData.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

varUsedData.o:varUsedData.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

exprData.o:exprData.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

stmtNumData.o:stmtNumData.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

exprNumData.o:exprNumData.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

nastNumData.o:nastNumData.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

graphData.o:graphData.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

dataFilter.o:dataFilter.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

DATAfilesRegister.o:DATAfilesRegister.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

prepare_bin:
	@cp -vf *.o ../bin; echo "copied data *.o in bin directory";

clean: 
	@rm -vf *.o; \
	echo "data classes *.o removed"; 

