prog: prog.c
	clang $$(pkg-config --libs libgit2 --cflags --static) -o prog prog.c
