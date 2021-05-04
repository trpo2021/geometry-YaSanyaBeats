CXX=g++
CFLAGS= -c -Wall -Werror
CPPFLAGS_TEST = -Wall -Wextra -Werror -I thirdparty -I src -MP -MMD
LIBI = obj/src/libinput
LIBC = obj/src/libcalculate
GEO = obj/src/geometry


bin/geometry.exe: $(GEO)/main.o $(GEO)/structFunctions.o $(LIBC)/calculate.o $(LIBI)/input.o 
		$(CXX) -I src -Wall -Werror -o bin/geometry.exe $(GEO)/main.o $(GEO)/structFunctions.o $(LIBC)/calculate.o $(LIBI)/input.o

$(LIBC)/calculate.a: $(LIBC)/calculate.o
		ar rcs $@ $^

$(LIBI)/input.a: $(LIBI)/input.o
		ar rcs $@ $^

$(LIBC)/calculate.o: src/libcalculate/calculate.cpp
		$(CXX) -I src $(CFLAGS) -MMD -o $(LIBC)/calculate.o src/libcalculate/calculate.cpp

$(LIBI)/input.o: src/libinput/input.cpp
		$(CXX) -I src $(CFLAGS) -MMD -o $(LIBI)/input.o src/libinput/input.cpp

$(GEO)/structFunctions.o: src/geometry/structFunctions.cpp
		$(CXX) -I src $(CFLAGS) -MMD -o $(GEO)/structFunctions.o src/geometry/structFunctions.cpp

$(GEO)/main.o: src/geometry/main.cpp
		$(CXX) -I src $(CFLAGS) -MMD -o $(GEO)/main.o src/geometry/main.cpp

-include main.d input.d calculate.d structFunctions.d

.PHONY: test
test: bin/test

bin/test: $(LIBI)/input.a $(LIBC)/calculate.a obj/test/test.o
	$(CXX) -I src -Wall -Werror -o bin/test obj/test/main.o $(LIBI)/input.a $(LIBC)/calculate.a

obj/test/test.o: test/main.cpp
		$(CXX) -I src $(CFLAGS) -MMD -o obj/test/main.o test/main.cpp

.PHONY: clean

clean: 
	rm -rf $(GEO)/*.o $(GEO)/*.d $(LIBC)/*.o $(LIBC)/*.d $(LIBI)/*.o $(LIBI)/*.d bin/*.exe
