include ../makefile.vars

NUM=1

all: cuda$(NUM)

%.o: %.cu
	nvcc -g -c $<

cuda$(NUM): main$(NUM).cpp cuda$(NUM).o $(wildcard *.h) 
	g++ -g $(filter %.cpp %.o, $^) $(OPENCVHDRS) $(CUDALIBS) $(OPENCVLIBS) -o cuda$(NUM)

clean:
	rm -f *.o cuda$(NUM)


