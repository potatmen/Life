SOURCE := $(wildcard **/*.cpp)
HEADERS := $(wildcard **/*.h)
OBJECTS := ${SOURCE:.cpp=.o}

# This section is customisable, so you can configure by yourself

INCLUDE := ~/../usr/local/include/ #library headers 
LINKER := ~/../usr/lib/x86_64-linux-gnu/libboost_program_options.a # .a file to link library 
 
all: install Life

install:
	sudo apt install g++
	sudo apt-get install libboost-all-dev
	sudo apt-get install -y clang-tidy
	sudo apt install clang-format
	
Life: $(OBJECTS)
	g++ -L $(INCLUDE) $(OBJECTS) $(LINKER) -o Life
	bash -c "diff -u <(cat $(SOURCE)) <(clang-format $(SOURCE))"
	clang-tidy -header-filter=none '-warnings-as-errors=*' '-checks=*,-readability-magic-numbers,-altera-id-dependent-backward-branch,-cert-err34-c,-cppcoreguidelines-avoid-non-const-global-variables,-readability-function-cognitive-complexity,-misc-no-recursion,-llvm-header-guard,-cppcoreguidelines-init-variables,-altera-unroll-loops,-clang-analyzer-valist.Uninitialized,-llvmlibc-callee-namespace,-cppcoreguidelines-no-malloc,-hicpp-no-malloc,-llvmlibc-implementation-in-namespace,-bugprone-easily-swappable-parameters,-llvmlibc-restrict-system-libc-headers,-llvm-include-order,-modernize-use-trailing-return-type,-cppcoreguidelines-special-member-functions,-hicpp-special-member-functions,-cppcoreguidelines-owning-memory,-cppcoreguidelines-pro-type-vararg,-hicpp-vararg,-fuchsia-default-arguments-calls' $(SOURCE)

%.o: %.cpp tests/%.cpp $(HEADERS)
	g++ $@ -o $<	

fix:
	clang-format -i $(SOURCE) $(HEADERS)

clean:
	rm src/*.o
	rm tests/*.o
	rm Life	