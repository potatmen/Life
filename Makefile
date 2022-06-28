SOURCES := $(wildcard **/*.cpp)
HEADERS := $(wildcard **/*.h)
OBJECTS := ${SOURCES:.cpp=.o}

TEST_SORUCES := $(wildcard src/*.cpp tests/test.cpp)
TEST_OBJECTS := ${TEST_SORUCES:.cpp=.o}


all: style  Life
  
Life: $(OBJECTS)
	g++ $(OBJECTS) -lboost_program_options -o Life

%.o: src/%.cpp tests/%.cpp $(HEADERS)
	g++ $@ -o $<  

style:
	bash -c "diff -u <(cat $(SOURCES)) <(clang-format $(SOURCES))"
	clang-tidy -header-filter=none '-warnings-as-errors=*' '-checks=*,-readability-magic-numbers,-altera-id-dependent-backward-branch,-cert-err34-c,-cppcoreguidelines-avoid-non-const-global-variables,-readability-function-cognitive-complexity,-misc-no-recursion,-llvm-header-guard,-cppcoreguidelines-init-variables,-altera-unroll-loops,-clang-analyzer-valist.Uninitialized,-llvmlibc-callee-namespace,-cppcoreguidelines-no-malloc,-hicpp-no-malloc,-llvmlibc-implementation-in-namespace,-bugprone-easily-swappable-parameters,-llvmlibc-restrict-system-libc-headers,-llvm-include-order,-modernize-use-trailing-return-type,-cppcoreguidelines-special-member-functions,-hicpp-special-member-functions,-cppcoreguidelines-owning-memory,-cppcoreguidelines-pro-type-vararg,-hicpp-vararg,-fuchsia-default-arguments-calls' $(SOURCES)

fix:
	clang-format -i $(SOURCES) $(HEADERS)

clean:
	rm src/*.o
	rm tests/*.o
	rm Life		