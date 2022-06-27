source := $(wildcard **/*.cpp)
headers := $(wildcard include/*.h)
objects := ${source:.cpp=.o}

Life: $(objects)
	g++ -L ~/../boost_1_79_0/ $(objects) ~/../usr/local/lib/libboost_program_options.a -o Life
	bash -c "diff -u <(cat $(source)) <(clang-format $(source))"
	clang-tidy -header-filter=none '-warnings-as-errors=*' '-checks=*,-readability-magic-numbers,-altera-id-dependent-backward-branch,-cert-err34-c,-cppcoreguidelines-avoid-non-const-global-variables,-readability-function-cognitive-complexity,-misc-no-recursion,-llvm-header-guard,-cppcoreguidelines-init-variables,-altera-unroll-loops,-clang-analyzer-valist.Uninitialized,-llvmlibc-callee-namespace,-cppcoreguidelines-no-malloc,-hicpp-no-malloc,-llvmlibc-implementation-in-namespace,-bugprone-easily-swappable-parameters,-llvmlibc-restrict-system-libc-headers,-llvm-include-order,-modernize-use-trailing-return-type,-cppcoreguidelines-special-member-functions,-hicpp-special-member-functions,-cppcoreguidelines-owning-memory,-cppcoreguidelines-pro-type-vararg,-hicpp-vararg,-fuchsia-default-arguments-calls' $(source)

%.o: %.cpp tests/%.cpp $(headers)
	g++ $@ -o $<	

fix:
	clang-format -i $(source) $(headers)

clean:
	rm src/*.o
	rm tests/*.o
	rm Life	