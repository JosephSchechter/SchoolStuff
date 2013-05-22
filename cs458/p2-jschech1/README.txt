Name:	Joseph Schechter
email:	jschech1@binghamton.edu
Tested on Bingsuns: Yes, read notes on output files
execution:	This is a c file that compiles with gcc, use make to compile it. To encrypt in.txt into out.txt and then decrypt out into out2.txt, follow these steps

make
./des 0123456789abcdef in.txt out.txt 1
./des 0123456789abcdef out.txt out2.txt 0


Notes:	Sometimes the output files contain garbage data at the end from the padding that is unable to be read by gedit, but they are still readable in pico and vi. In OSX, the files are read perfectly by textedit.
