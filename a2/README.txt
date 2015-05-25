A2 Readme

Known Bugs:
Classpath/Compiler options are just stubs, it will only execute with no arguments in the current directory.
ie "nreymer/a2/%name%.java"

How to use:
Running make will compile the C and H files from A1, along with the Java files and launch the gui.
After its ran it will clean all .class files from the src/ directory

Issues you may encounter:
The created GUI window is only 600x600, for the example. It can hold up to 10 paramaters, and 8 buttons before it will start overlapping.
A space in the title name will be converted to a _ so the the name will remain a single word
