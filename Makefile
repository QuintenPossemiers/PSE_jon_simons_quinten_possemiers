#--- the location of the test includes; YOU MIGHT NEED TO MODIFY THESE
INCL =		../gtest/include
#--- the location of the test libraries; YOU MIGHT NEED TO MODIFY THESE
TLIBPATH =	-L../gtest/lib
TLIBS =		-lgtest -lgtest_main


CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -I$(INCL)

OBJS =		SimulationModel.o
SRCS =		Parser.cpp \
			Road.cpp \
			Vehicle.cpp\
			SimulationModel.h


TINYOBJS =	tinystr.o \
			tinyxml.o \
			tinyxmlerror.o \
			tinyxmlparser.o
TINYSRCS =	XML_Files\tinystr.h \
			XML_Files\tinyxml.cpp \
			XML_Files\tinyxmlerror.cpp \
			XML_Files\tinyxmlparser.cpp
TARGET =	main.cpp

#--- primary target
.PHONY : all
all : $(TARGET)


#--- compiler targets
TicTacToeMain : $(OBJS) $(TINYOBJS) tinyxml.h TicTacToeMain.o
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(TINYOBJS) TicTacToeMain.o

TicTacToeTests : $(OBJS) $(TSTSRCS) $(TINYOBJS) tinyxml.h TicTacToeTests.o
	$(CXX) $(CXXFLAGS) $(TLIBPATH) $(TLIBS) -o $@ $(OBJS) $(TINYOBJS) TicTacToeTests.o

TicTacToeTests.o : $(TSTSRCS)
	$(CXX) $(CXXFLAGS) -c -o $@ main_test.cpp

%.o : %.cpp %.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<



#--- non-file targets
.PHONY : clean
clean :
	rm -f *.o $(TARGET)
	rm -f testOutput/file*.txt testOutput/happyDayOut.txt  testOutput/noWinnerOut.txt testOutput/zzz*.txt testOutput/zzz*.html
	rm -f testInput/zzz*.xml testInput/zzz*.txt

.PHONY : cleantests
cleantests :
	rm -f testOutput/file*.txt testOutput/happyDayOut.txt  testOutput/noWinnerOut.txt
	rm -f testInput/zzz*.xml testInput/zzz*.txt

.PHONY : depend
depend :
	g++ -MM -I $(INCL) $(SRCS)

.PHONY : echo
echo :
	@echo CXXFLAGS = $(CXXFLAGS)
	@echo CXX = $(CXX)
	@echo LDFLAGS = $(LDFLAGS)
	@echo INCL = $(INCL)
	@echo TLIBPATH = $(TLIBPATH)
	@echo TLIBS = $(TLIBS)


.PHONY : sourcestar
sourcestar :
	tar -cvf TicTacToe.tar *.h *.cpp Makefile testOutput testInput

.PHONY : sourceszip
sourceszip :
	zip -q -r TicTacToe.zip *.h *.cpp Makefile testOutput testInput
#--zip quietly and recursively
