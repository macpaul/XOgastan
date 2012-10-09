# XOgastan makefile

include ../Makefile.incl


all: $(XMLMANAGER_OBJ)
	@echo "xmlManager classes *.o done."; echo;

XMLWriter.o:XMLWriter.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

XMLDOM_str_exception.o:XMLDOM_str_exception.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

build_xmlFunctionDOM.o:build_xmlFunctionDOM.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

build_xmlDeclarationDOM.o:build_xmlDeclarationDOM.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

build_xmlVarUsedDOM.o:build_xmlVarUsedDOM.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

build_xmlParameterDOM.o:build_xmlParameterDOM.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

build_xmlStatisticDOM.o:build_xmlStatisticDOM.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

build_xmlStmtStatDOM.o:build_xmlStmtStatDOM.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

build_xmlExprStatDOM.o:build_xmlExprStatDOM.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

build_xmlReachStatDOM.o:build_xmlReachStatDOM.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

build_xmlNastStatDOM.o:build_xmlNastStatDOM.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

prepare_bin:
	@cp -vf *.o ../bin; echo "copied xmlManager *.o in bin directory";

clean: 
	@rm -vf *.o; \
	echo "xmlManager classes *.o removed"; 

