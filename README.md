# What is this program?
This program is a lexical analyzer and parser. It takees words input into it. Separates them into tokens and places them into a binary tree.
It then creates 3 files for each possible traversal inorder, preorder, and postorder traversal.

# How to run
in the directory the makefile is in enter make. This should compile the program.
The executables name is P0. Use ./P0 and enter any arguments you'd like to make.
If you wish to pass your own file into the program be sure it has the .fs25s1 extension this is required if you intend for the program to use a file as it's input.

## Argument options
No arguments:
	Gives you space to write whatever you wish. You can even press enter to create a new line. When you're done press ctrl+d (sometimes you'll need to do it twice) it will use those words and the output file names will have the base name out
one argument:
	This program will only take in one argument and that is the basefile name not including the required .fs25s1 file extension the program will append that to the file name
# testing
A good way to test the No arguments option is to still use your input file with the .fs25s1 extension. Some thing like ./P0 < someFile.fs25s1 this just redirects the input to the programs stdin
