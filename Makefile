FAST_SOURCES := $(wildcard fast/src/*.cpp fast/tests/main.cpp)
FAST_HEADERS := $(wildcard fast/**/*.h)
FAST_OBJECTS := ${FAST_SOURCES:.cpp=.o}

FAST_TEST_SOURCES := $(wildcard fast/src/*.cpp fast/tests/test.cpp)
FAST_TEST_OBJECTS := ${FAST_TEST_SOURCES:.cpp=.o}

all: style slow fast

slow: slow_life

fast:  fast_life fast_test 
  
fast_life: $(FAST_OBJECTS)
	g++ $(FAST_OBJECTS) -lboost_program_options -o fast_life

fast_test: $(FAST_TEST_OBJECTS)
	g++ $(FAST_TEST_OBJECTS) -lboost_unit_test_framework -o fast_test
	./fast_test

%.o: fast/**/%.cpp  $(FAST_HEADERS)
	g++ $@ -o $< 

SLOW_SOURCES := $(wildcard slow/src/*.cpp)
SLOW_HEADERS := $(wildcard slow/**/*.h)
SLOW_OBJECTS := ${SLOW_SOURCES:.cpp=.o}


slow_life: $(SLOW_OBJECTS)
	g++ $(SLOW_OBJECTS) -lboost_program_options -o slow_life



ALL_SOURCES := $(FAST_SOURCES) $(SLOW_SOURCES)


style:
	bash -c "diff -u <(cat $(ALL_SOURCES)) <(clang-format --style=file $(ALL_SOURCES))"
	clang-tidy -header-filter=none '-warnings-as-errors=*' '-checks=*,-readability-magic-numbers,-altera-id-dependent-backward-branch,-cert-err34-c,-cppcoreguidelines-avoid-non-const-global-variables,-readability-function-cognitive-complexity,-misc-no-recursion,-llvm-header-guard,-cppcoreguidelines-init-variables,-altera-unroll-loops,-clang-analyzer-valist.Uninitialized,-llvmlibc-callee-namespace,-cppcoreguidelines-no-malloc,-hicpp-no-malloc,-llvmlibc-implementation-in-namespace,-bugprone-easily-swappable-parameters,-llvmlibc-restrict-system-libc-headers,-llvm-include-order,-modernize-use-trailing-return-type,-cppcoreguidelines-special-member-functions,-hicpp-special-member-functions,-cppcoreguidelines-owning-memory,-cppcoreguidelines-pro-type-vararg,-hicpp-vararg,-fuchsia-default-arguments-calls' $(ALL_SOURCES) 

fix:
	clang-format -i --style=file $(ALL_SOURCES)

clean:
	rm -f **/src/*.o
	rm -f **/tests/*.o
	rm -f *_life		
	rm -f *_test
