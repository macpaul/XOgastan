# XOgastan makefile

include ../Makefile.incl


all: $(HTMLWRITER_OBJ)
	@echo "htmlWriter classes *.o done."; echo;

HTMLfilesRegister.o:HTMLfilesRegister.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

HTMLofstream.o:HTMLofstream.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

HTMLwriter.o:HTMLwriter.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

write_htmlHomePage.o:write_htmlHomePage.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

write_htmlFnctFilter.o:write_htmlFnctFilter.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

write_htmlFnctPages.o:write_htmlFnctPages.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

write_htmlNastStat.o:write_htmlNastStat.cpp
	${CXX} ${CMP} $(INCLUDE) -o $@ $<

prepare_bin:
	@cp -vf *.o ../bin; echo "copied htmlWriter *.o in bin directory";


clean: 
	@rm -vf *.o; \
	echo "htmlWriter classes *.o removed"; 

