# Your program must compile with 'make'
# You must not change this file.

CC = gcc
FLAGS = -std=c99 -O0 -Wall -Werror -g -pedantic 

rgrep:
	$(CC) $(FLAGS) rgrep.c -o rgrep

clean:
	rm -rf rgrep *.dSYM

check: clean rgrep
	test "`echo "a\nb\nc" | ./rgrep 'a'`" = "a"
	test "`echo "a\n" | ./rgrep 'a'`" = "a"
	test "`echo "a" | ./rgrep '...'`" = ""
	test "`echo "abc" | ./rgrep '.b.'`" = "abc"
	test "`echo "h\naaaaah" | ./rgrep 'a+h'`" = "aaaaah"
	test "`echo "h\naaaaahhhhh" | ./rgrep 'aa+hh+'`" = "aaaaahhhhh"
	test "`echo "h\naaaaahhhhh\n" | ./rgrep 'aa+hh+'`" = "aaaaahhhhh"
	test "`echo "a" | ./rgrep 'a?a'`" = "a"
	test "`echo "woot\nwot\nwat\n" | ./rgrep 'wo?t'`" = "wot"
	test "`echo "CCCCCCC\nC+\nC++" | ./rgrep '.\+\+'`" = "C++"
	test "`echo "GG" | ./rgrep '.+'`" = "GG"
	test "`echo "woooooo_CSE31.jpg" | ./rgrep 'w.+_...31\.jpg'`" = "woooooo_CSE31.jpg"
	test "`echo "aab" | ./rgrep 'bb?'`" = "aab"
	test "`echo "aaab" | ./rgrep 'a+b'`" = "aaab"
	test "`echo "aaab" | ./rgrep 'a+ab'`" = "aaab"
	test "`echo "aah" | ./rgrep 'aa+h+'`" = "aah"
	test "`echo "aaab\naa\n" | ./rgrep '...'`" = "aaab"
	test "`echo "aaab+\naa" | ./rgrep '\+'`" = "aaab+"
	test "`echo "aaab\naa" | ./rgrep '...'`" = "aaab"
	test "`echo "a" | ./rgrep '.+'`" = "a"
	test "`echo "ab\naa" | ./rgrep 'a?b+'`" = "ab"
	test "`echo "b\naa" | ./rgrep 'a?b+'`" = "b"
	test "`echo "abbb\naa" | ./rgrep 'a?b+'`" = "abbb"
	test "`echo "there\naa" | ./rgrep 'they?re'`" = "there"
	test "`echo "theyre\ntheir" | ./rgrep 'they?re'`" = "theyre"
	test "`echo "hidden\ntheir" | ./rgrep 'h.d..?n'`" = "hidden"
	test "`echo "hiden\ntheir" | ./rgrep 'h.d..?n'`" = "hiden"
	test "`echo "cut\ncult" | ./rgrep 'cu\.?t'`" = "cut"
	test "`echo "cu.t\ncult" | ./rgrep 'cu\.?t'`" = "cu.t"
	test "`echo "?\ncu\\t" | ./rgrep '\?+'`" = "?"
	test "`echo "ccc+aa\ncu\\t" | ./rgrep '\+?aa'`" = "ccc+aa"
	test "`echo "cccaa\ncu\\t" | ./rgrep '\+?aa'`" = "cccaa"
	@echo "Passed sanity check."
