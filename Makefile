SOURCES := $(wildcard src/*.cpp tests/main.cpp)
HEADERS := $(wildcard **/*.h)
OBJECTS := ${SOURCES:.cpp=.o}

TEST_SOURCES := $(wildcard src/*.cpp tests/test.cpp)
TEST_OBJECTS := ${TEST_SOURCES:.cpp=.o}


all: style life test 
  
life: $(OBJECTS)
	g++ $(OBJECTS) -lboost_program_options -o life

test: $(TEST_OBJECTS)
	g++ $(TEST_OBJECTS) -lboost_unit_test_framework -o test
	./test

%.o: **/%.cpp  $(HEADERS)
	g++ $@ -o $< 

style:
	bash -c "diff -u <(cat $(SOURCES)) <(clang-format $(SOURCES))"
	clang-tidy -header-filter=none '-warnings-as-errors=*' '-checks=*,-readability-magic-numbers,-altera-id-dependent-backward-branch,-cert-err34-c,-cppcoreguidelines-avoid-non-const-global-variables,-readability-function-cognitive-complexity,-misc-no-recursion,-llvm-header-guard,-cppcoreguidelines-init-variables,-altera-unroll-loops,-clang-analyzer-valist.Uninitialized,-llvmlibc-callee-namespace,-cppcoreguidelines-no-malloc,-hicpp-no-malloc,-llvmlibc-implementation-in-namespace,-bugprone-easily-swappable-parameters,-llvmlibc-restrict-system-libc-headers,-llvm-include-order,-modernize-use-trailing-return-type,-cppcoreguidelines-special-member-functions,-hicpp-special-member-functions,-cppcoreguidelines-owning-memory,-cppcoreguidelines-pro-type-vararg,-hicpp-vararg,-fuchsia-default-arguments-calls' $(SOURCES)

fix:
	clang-format -i --style=file $(SOURCES) tests/test.cpp $(HEADERS)

clean:
	rm -f src/*.o
	rm -f tests/*.o
	rm -f life		
	rm -f test
