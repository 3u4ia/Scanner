# Which Option did I attempt
Option 3 the most difficult one which included creating an Finite State Automata Table to lookup each character being read a lookahead of 1 was used to determine tokens
# What is this program?
This is a scanner/lexical analyzer that is able to extract tokens one at a time from a file. It will return a token struct that has a tokenId the token isntance as well as the line number for said token
If there are any tokens that don't exist in the langauge this lexical analyzer will throw an error usually with the line number attatched.
To test this lexical analyzer P1.cpp runs a testScanner function that calls the scanner on loop and outputs the result for viewing purposes
# How to run
in the directory the makefile is in enter make. This should compile the program.
The executables name is P1. Use ./P1 and enter any arguments you'd like to make.
If you wish to pass your own file into the program be sure it has the .fs25s1 extension this is required if you intend for the program to use a file as it's input.
## Argument options
No arguments:
	Gives you space to write whatever you wish. You can even press enter to create a new line. When you're done press ctrl+d (sometimes you'll need to do it twice) it will use those words and the output file names will have the base name out
one argument:
	This program will only take in one argument and that is the basefile name not including the required .fs25s1 file extension the program will append that to the file name
# testing
A good way to test the No arguments option is to still use your input file with the .fs25s1 extension. Some thing like ./P1 < P1test.fs25s1 this just redirects the input to the programs stdin
