2750-a1
=======
Known Issues:
Only case where parse may fail is if line is (name=value;name2=value;namex=value)
Expects lines to be separated by a space, will only take a single parameter after;
ie: Will parse
b1=true
;b2
=false;

Other than that issue, parsing should be fine.

Compiling:
  To compile the program use make, or make ParameterManager

Executing:
    To Execute the program use: %programName% < %file%


Description of files:

ParameterManager.h  - Contains all of the headers I used for functions + needed function definitions
ParameterManager.c  - Contains all of the functions in the .h file. 
