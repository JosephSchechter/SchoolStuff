JFLAGS = -g
JC = javac
.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
	cli.java \
	serv.java 

default: classes

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class
	$(RM) *_ce
	$(RM) *_sd
	$(RM) *_se