

OFILES = \
		 base/ImgProc.o \
		 base/Stencil.o \
		 base/Fractal.o \
	 	 base/StarterViewer.o

ROOTDIR = .
LIB = $(ROOTDIR)/lib/libstarter.a

GLLDFLAGS     = -L /opt/homebrew/lib -lglut -lGL -lm -lGLU -lOpenImageIO -lOpenImageIO_Util

CXX = clang++ -Wall -g -O1 -fPIC $(DEFINES) -fopenmp -std=c++17

INCLUDES =  -I /opt/homebrew/include/ -I$(ROOTDIR)/include/ -I/usr/local/include/ -I/usr/include/

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
	rm -rf bin/simple_viewer bin/test bin/*dSYM *.o base/*.o base/*~ include/*~ $(LIB)  *~ 



