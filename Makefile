
CXX = g++
CXXFLAGS = -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11
EXE = program.exe

$(EXE): program.o funciones.o Pri.o Procesador.o Proceso.o
	$(CXX) $(CXXFLAGS) program.o funciones.o Pri.o Procesador.o Proceso.o -o $(EXE)

program.o: program.cc funciones.hh Procesador.hh Proceso.hh Pri.hh
	$(CXX) $(CXXFLAGS) -c program.cc

funciones.o: funciones.cc funciones.hh Procesador.hh Proceso.hh Pri.hh
	$(CXX) $(CXXFLAGS) -c funciones.cc

Pri.o: Pri.cc Pri.hh Proceso.hh
	$(CXX) $(CXXFLAGS) -c Pri.cc

Procesador.o: Procesador.cc Procesador.hh Proceso.hh
	$(CXX) $(CXXFLAGS) -c Procesador.cc

Proceso.o: Proceso.cc Proceso.hh
	$(CXX) $(CXXFLAGS) -c Proceso.cc

clean:
	rm -f *.o $(EXE)

run: $(EXE)
	./$(EXE)
