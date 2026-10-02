

OFILES = \
         base/Matrix.o \
         base/LinearAlgebra.o \
		 base/ImgProc.o \
		 base/Stencil.o \
	 	 base/StarterViewer.o

ROOTDIR = .
LIB = $(ROOTDIR)/lib/libstarter.a

GLLDFLAGS     = -lglut -lGL -lm -lGLU -lOpenImageIO -lOpenImageIO_Util

CXX = g++ -Wall -g -O1 -fPIC $(DEFINES) -fopenmp -std=c++17

INCLUDES =  -I$(ROOTDIR)/include/ -I/usr/local/include/ -I/usr/include/

.C.o:
	$(CXX) -c $(INCLUDES) $< -o $@

base: $(OFILES)
	ar rv $(LIB) $?
	$(CXX) base/simple_viewer.C $(INCLUDES) \
    -L./lib -lstarter $(GLLDFLAGS) \
    -o bin/simple_viewer

test: $(OFILES)
	ar rv $(LIB) $?
	$(CXX) base/test.C $(INCLUDES) \
    -L./lib -lstarter $(GLLDFLAGS) \
    -o bin/test

clean:
	rm -rf bin/simple_viewer bin/test *.o base/*.o base/*~ include/*~ $(LIB)  *~ 



