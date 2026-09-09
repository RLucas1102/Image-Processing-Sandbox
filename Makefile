

OFILES = \
         base/Matrix.o \
         base/LinearAlgebra.o \
		 base/ImgProc.o \
	 	 base/StarterViewer.o

ROOTDIR = .
LIB = $(ROOTDIR)/lib/libstarter.a

GLLDFLAGS     = -lglut -lGL -lm -lGLU -lOpenImageIO

CXX = g++ -Wall -g -O1 -fPIC $(DEFINES) -fopenmp -std=c++17

INCLUDES =  -I$(ROOTDIR)/include/ -I/usr/local/include/ -I/usr/include/

.C.o:
	$(CXX) -c $(INCLUDES) $< -o $@

base: $(OFILES)
	ar rv $(LIB) $?
	$(CXX) base/simple_viewer.C $(INCLUDES) \
    -L./lib -lstarter $(GLLDFLAGS) \
    -o bin/simple_viewer

clean:
	rm -rf bin/simple_viewer *.o base/*.o base/*~ include/*~ $(LIB)  *~ 



