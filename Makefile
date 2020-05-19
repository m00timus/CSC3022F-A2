#A2 makefile
 
CC=g++  
COMPILE=-c
LINK=-o
PROGRAM=volimage
PROGRAM2=driver

#      c++11     all warnings on            
#      |         |     debug info (allows debugging with gdb)
#      |         |     |  check for out-of-bounds errors
#      V         V     V  V                  /=extra info for runtime errors
FLAGS=-std=c++11 -Wall -g -fsanitize=address -fno-omit-frame-pointer
OPTIMIZE=-O3 -std=c++11 -Wall #but do not add error checking at runtime

#the default target is debug code
debug: 
	cppcheck --enable=all $(PROGRAM).cpp #source code analysis
	$(CC) $(FLAGS) $(COMPILE) $(PROGRAM).o $(PROGRAM).cpp #compile
	$(CC) $(FLAGS) $(LINK) $(PROGRAM) $(PROGRAM).o #link
	#echo "$(@:git-%=%)" #to debug the git commandline
	git commit -a -m "$m" #commit all changes 
	git push origin master #push to the repo
	./$(PROGRAM) #run the program

#and fast executable is an additional target
release:
	$(CC) $(OPTIMIZE) $(COMPILE) volimage_h.h $(PROGRAM).cpp $(PROGRAM2).cpp #compile for speed
	$(CC) $(OPTIMIZE) $(LINK) $(PROGRAM) $(PROGRAM).o $(PROGRAM2).o  #link

clean:
	rm -f *.o #clear out object files
	rm -f volimage_h.h.gch output.data output.raw
	rm -f $(PROGRAM) #and the final executable

