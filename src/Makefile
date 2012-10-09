# XOgastan makefile

include Makefile.incl


all: $(XOgastan_OBJS)
	@echo "All objects files *.o done";
	@if [ -d bin ]; then \
	echo "Removing actual bin directory"; \
	rm -vfr bin; \
	fi; 
	@echo "Creating bin directory";	mkdir bin; 
	@echo 
	@echo "Preparing for linking"; 
	@echo
	@cd nast; gmake prepare_bin;
	@cd factory; gmake prepare_bin;
	@cd utils; gmake prepare_bin;
	@cd data;gmake prepare_bin;
	@cd visitor; gmake prepare_bin;
	@cd htmlWriter;gmake prepare_bin;
	@cd xmlManager;gmake prepare_bin;
	@cd error; gmake prepare_bin;
	@cp -v main.o bin; 
	@cp -v Makefile.bin bin/Makefile; 
	@echo; echo "Linking *.o files"; echo
	@- cd bin; gmake link; echo; rm -vf *.o; rm -vf Makefile
	@echo; echo "XOgastan done !!"; echo



main.o:main.cpp
	- ${CXX} ${CMP} $(INCLUDE) -o $@ $<; 


nast.o: 
	@cd nast;gmake all;

factory.o: 
	@cd factory;gmake all;

utils.o: 
	@cd utils;gmake all;

visitor.o:
	@cd visitor;gmake all;

data.o:
	@cd data;gmake all;

htmlWriter.o:
	@cd htmlWriter;gmake all;

xmlManager.o:
	@cd xmlManager;gmake all;

error.o: 
	@cd error;gmake all;

clean: 
	@cd nast; gmake clean;  
	@cd factory; gmake clean;  
	@cd utils; gmake clean; 
	@cd data;gmake clean;
	@cd visitor; gmake clean; 
	@cd htmlWriter;gmake clean;
	@cd xmlManager;gmake clean;
	@cd error; gmake clean;  
	@rm -vf *.o 
	@rm -vfr bin 
	@echo "All cleaned"; 
	@echo



doc: docclean
#create new images .gif of the classes
	@mkdir $(XOgastanROOT)/img/classes;
	@cp $(XOgastanROOT)/img/dot/map2dot.pl $(XOgastanROOT)/img/classes/;
	@cp $(XOgastanROOT)/gcc2gxl/g2x.map $(XOgastanROOT)/img/classes/;
	(cd $(XOgastanROOT)/img/classes; ./map2dot.pl --ifile g2x.map;)
	@rm -vf $(XOgastanROOT)/img/classes/g2x.map;
	@rm -vf $(XOgastanROOT)/img/classes/map2dot.pl;
#create images .gif of the dofile in dot/
	(cd $(XOgastanROOT)/img/dot; \
	 dot -Tgif -o stateMachine.gif stateMachine.dot; \
	 dot -Tgif -o unary_expr.gif unary_expr.dot; \
	 dot -Tgif -o binary_expr.gif binary_expr.dot; \
	 mv *.gif ../classes/;)
#generate new docs
	(cd $(XOgastanROOT); doxygen)
#copy logo image and style sheet
	cp $(XOgastanROOT)/doc/img/xogastan_logo.jpg $(XOgastanROOT)/doc/sources/;
	cp $(XOgastanROOT)/doc/img/xogastan_logo_small.jpg $(XOgastanROOT)/doc/sources/;
	cp $(XOgastanROOT)/doc/style.css $(XOgastanROOT)/doc/sources/;
	@echo;
	@echo "Documentation done.";

docclean:
#remove docs
	@if [ -d $(XOgastanROOT)/doc/sources ]; then 	\
	rm -vfr $(XOgastanROOT)/doc/sources; \
	fi;
#remove images .gif of the classes
	@if [ -d $(XOgastanROOT)/img/classes ]; then \
	rm -vfr $(XOgastanROOT)/img/classes; \
	fi;


help:
	@echo "Usage :";
	@echo;
	@echo "     gmake LABEL";
	@echo;
	@echo "where LABEL is one of : "
	@echo;
	@echo;
	@echo "all          compile the XOgastan sources";
	@echo "clean        clean all the objects and executable files";
	@echo "doc          create the html documentation";
	@echo "docclean     delete the html documentation";
	@echo;
	@echo;
	@echo "written by lucas75it";
