# XOgastan makefile

include ../Makefile.incl



all: $(NAST_OBJ)
	@echo "nast classes *.o done."; echo;

nast_node.o:nast_node.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<
type_n.o:type_n.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<
decl_n.o: decl_n.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<
cst_n.o:cst_n.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<
stmt_n.o:stmt_n.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<
othr_n.o:othr_n.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<
expr_n.o:expr_n.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

prepare_bin:
	@cp -vf *.o ../bin; echo "copied nast *.o in bin directory";


clean: 
	@rm -vf *.o; \
	echo "nast classes *.o removed"; 

