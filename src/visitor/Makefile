# XOgastan makefile

include ../Makefile.incl 



all: $(VISITOR_OBJ)
	@echo "visitors classes *.o done."; echo;

visitor.o:visitor.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $< 

visit_declsInFnct.o:visit_declsInFnct.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $< 

visit_exprsInFnct.o:visit_exprsInFnct.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $< 

visit_varUsedByFnct.o:visit_varUsedByFnct.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $< 

visit_fnctsInNast.o:visit_fnctsInNast.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $< 

visit_fnctBodyGraph.o:visit_fnctBodyGraph.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $< 

visit_fnctCFG.o:visit_fnctCFG.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $< 

visit_stmtNumber.o:visit_stmtNumber.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $< 

visit_exprNumber.o:visit_exprNumber.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $< 

visit_nastNumber.o:visit_nastNumber.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $< 

visit_fnctCallGraph.o:visit_fnctCallGraph.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $< 

prepare_bin:
	@cp -vf *.o ../bin; echo "copied visitor *.o in bin directory";

clean:
	@rm -vf *.o; echo "factory classes *.o removed";





