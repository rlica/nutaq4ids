

# Makefile for nutaq4ids.C
# razvan.lica@cern.ch



    CC  = g++
CFLAGS  = `root-config --cflags`
LIBS    = `root-config --libs`    
INCLUDE = -I./include/
SOURCE  = ./src/nutaq4ids.cc
OBJECT  = ./bin/nutaq4ids.o
   EXE  = ./bin/n4i


$(EXE): $(OBJECT)
	$(CC) -o $(EXE)  $(OBJECT) $(LIBS)

$(OBJECT): $(SOURCE)
	$(CC) -c $(CFLAGS) -o $(OBJECT) $(INCLUDE) $(SOURCE) 

clean:
	rm -f $(OBJECT)



 
 
#  More details about compiling and linking c++ executables
#  http://www.hep.shef.ac.uk/teaching/phy6040/ROOT/ROOTseminars/Seminar_4.html
 
# Makefile taken from
# http://mrbook.org/tutorials/make/

