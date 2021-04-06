CXX=g++
CFLAGS= -c -Wall -Werror
LIBI = obj/src/libinput
LIBC = obj/src/libcalculate
GEO = obj/src/geometry

bin/geometry.exe: $(GEO)/main.o $(LIBC)/calculate.o $(LIBI)/input.o 
		$(CXX) -I src -Wall -Werror -o bin/geometry.exe $(GEO)/main.o $(LIBC)/calculate.o $(LIBI)/input.o

$(LIBC)/calculate.o: src/libcalculate/calculate.cpp
		$(CXX) -I src $(CFLAGS) -MMD -o $(LIBC)/calculate.o src/libcalculate/calculate.cpp

$(LIBI)/input.o: src/libinput/input.cpp
		$(CXX) -I src $(CFLAGS) -MMD -o $(LIBI)/input.o src/libinput/input.cpp

$(GEO)/main.o: src/geometry/main.cpp
		$(CXX) -I src $(CFLAGS) -MMD -o $(GEO)/main.o src/geometry/main.cpp

.PHONY: clean

clean: 
	rm -rf $(GEO)/*.o $(GEO)/*.d $(LIBC)/*.o $(LIBC)/*.d $(LIBI)/*.o $(LIBI)/*.d bin/*.exe

-include main.d input.d calculate.d

