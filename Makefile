# Copyright (c) 2022 Anton Shatokhin

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.


FAST_SOURCES := $(wildcard Fast/src/*.cpp)
FAST_HEADERS := $(wildcard Fast/**/*.h)
FAST_OBJECTS := ${FAST_SOURCES:.cpp=.o}

FAST_TEST_SOURCES := $(filter-out Fast/src/main.cpp, $(shell find Fast/  -type f -name *.cpp))

FAST_TEST_OBJECTS := ${FAST_TEST_SOURCES:.cpp=.o}

all: style slow fast

slow: slow_life slow_test

fast:  fast_life fast_test 
  
fast_life: $(FAST_OBJECTS)
	g++ $(FAST_OBJECTS) -lboost_program_options -o fast_life

fast_test: $(FAST_TEST_OBJECTS)
	g++ $(FAST_TEST_OBJECTS) -lboost_unit_test_framework -o fast_test 
	./fast_test --log_level=all

%.o: Fast/**/%.cpp  $(FAST_HEADERS)
	g++ $@ -o $< 

SLOW_SOURCES := $(wildcard slow/src/*.cpp)
SLOW_HEADERS := $(wildcard slow/**/*.h)
SLOW_OBJECTS := ${SLOW_SOURCES:.cpp=.o}


print:
	find slow/tests/ -type f -name *.cpp

SLOW_TEST_SOURCES := $(filter-out slow/src/main.cpp, $(shell find slow/  -type f -name *.cpp))


SLOW_TEST_OBJECTS := ${SLOW_TEST_SOURCES:.cpp=.o}

slow_life: $(SLOW_OBJECTS)
	g++ $(SLOW_OBJECTS) -lboost_program_options -o slow_life

slow_test: $(SLOW_TEST_OBJECTS)
	g++ $(SLOW_TEST_OBJECTS) -lboost_unit_test_framework -lboost_program_options -o slow_test
	./slow_test --log_level=all

%.o:  slow/**/%.cpp  $(SLOW_HEADERS)
	g++ $@ -o $< 



ALL_SOURCES := $(SLOW_SOURCES) $(FAST_SOURCES)
ALL_HEADERS := $(FAST_HEADERS) $(SLOW_HEADERS)
style:
	bash -c "diff -u <(cat $(ALL_SOURCES)) <(clang-format --style=file $(ALL_SOURCES))"
	clang-tidy -header-filter=none '-warnings-as-errors=*' '-checks=*,-readability-magic-numbers,-altera-id-dependent-backward-branch,-cert-err34-c,-cppcoreguidelines-avoid-non-const-global-variables,-readability-function-cognitive-complexity,-misc-no-recursion,-llvm-header-guard,-cppcoreguidelines-init-variables,-altera-unroll-loops,-clang-analyzer-valist.Uninitialized,-llvmlibc-callee-namespace,-cppcoreguidelines-no-malloc,-hicpp-no-malloc,-llvmlibc-implementation-in-namespace,-bugprone-easily-swappable-parameters,-llvmlibc-restrict-system-libc-headers,-llvm-include-order,-modernize-use-trailing-return-type,-cppcoreguidelines-special-member-functions,-hicpp-special-member-functions,-cppcoreguidelines-owning-memory,-cppcoreguidelines-pro-type-vararg,-hicpp-vararg,-fuchsia-default-arguments-calls' $(ALL_SOURCES) 

fix:
	clang-format -i --style=file $(ALL_SOURCES) $(ALL_HEADERS)
	clang-tidy -fix -header-filter=none '-warnings-as-errors=*' '-checks=*,-readability-magic-numbers,-altera-id-dependent-backward-branch,-cert-err34-c,-cppcoreguidelines-avoid-non-const-global-variables,-readability-function-cognitive-complexity,-misc-no-recursion,-llvm-header-guard,-cppcoreguidelines-init-variables,-altera-unroll-loops,-clang-analyzer-valist.Uninitialized,-llvmlibc-callee-namespace,-cppcoreguidelines-no-malloc,-hicpp-no-malloc,-llvmlibc-implementation-in-namespace,-bugprone-easily-swappable-parameters,-llvmlibc-restrict-system-libc-headers,-llvm-include-order,-modernize-use-trailing-return-type,-cppcoreguidelines-special-member-functions,-hicpp-special-member-functions,-cppcoreguidelines-owning-memory,-cppcoreguidelines-pro-type-vararg,-hicpp-vararg,-fuchsia-default-arguments-calls' $(ALL_SOURCES) 


clean:
	rm -f **/src/*.o
	rm -f **/tests/**/*.o
	rm -f *_life		
	rm -f *_test