#MakeFile example

#target: dependency1 dependency2 ...
#	<tab> command

#NOTE: remember to add the TAB character before the command part

#Typing 'make' will invoke the first target entry in the file


encode: encode.cpp	
	g++ -std=c++11 -o encode encode.cpp
	
decode: decode.cpp	
	g++ -std=c++11 -o decode decode.cpp
	
clean:
	$(RM) encode

#Example of compiling multiple files

example.o: example.cpp
	g++ -c example.cpp

file1.o: file1.cpp
	g++ -c file1.cpp

file2.o: file2.cpp
	g++ -c file2.cpp

multiFile: example.o file1.o file2.o
	g++ -o multiFile example.o file1.o file2.o
