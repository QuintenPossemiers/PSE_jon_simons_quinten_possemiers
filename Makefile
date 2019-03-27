#--- the location of the test includes; YOU MIGHT NEED TO MODIFY THESE
INCL =		gtest/include
#--- the location of the test libraries; YOU MIGHT NEED TO MODIFY THESE
TLIBPATH =	-Lgtest/lib
TLIBS =		-lgtest -lgtest_main


CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -I$(INCL)

OBJS =		src/SimulationModel.o\
			 		src/Road.o\
					src/Vehicle.o\
					src/Parser.o\
					src/Exceptions.o
SRCS =		src/Parser.cpp \
					src/Road.cpp \
					src/Vehicle.cpp\
					src/SimulationModel.cpp\
					src/main.cpp\
					src/Exceptions.cpp
TSTSRCS =	src/Parser.cpp \
            					src/Road.cpp \
            					src/Vehicle.cpp\
            					src/SimulationModel.cpp\
            					src/mainTests.cpp\
            					src/Exceptions.cpp
TINYOBJS =	TinyXml/tinystr.o \
					TinyXml/tinyxml.o \
					TinyXml/tinyxmlerror.o \
					TinyXml/tinyxmlparser.o
TINYSRCS =	TinyXml/tinystr.h \
					TinyXml/tinyxml.cpp \
					TinyXml/tinyxmlerror.cpp \
					TinyXml/tinyxmlparser.cpp
TARGET =	main mainTests

#--- primary target
.PHONY : all
all : $(TARGET)


#--- compiler targets
main : $(OBJS) $(TINYOBJS) TinyXml/tinyxml.h src/main.o
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(TINYOBJS) src/main.o

mainTests : $(OBJS) $(TSTSRCS) $(TINYOBJS) TinyXml/tinyxml.h src/mainTests.o
	$(CXX) $(CXXFLAGS) $(TLIBPATH) $(TLIBS) -o $@ $(OBJS) $(TINYOBJS) src/mainTests.o

mainTests.o : $(TSTSRCS)
	$(CXX) $(CXXFLAGS) -c -o $@ src/mainTests.cpp

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
	tar -cvf PSE.tar *.h *.cpp Makefile testOutput testInput

.PHONY : sourceszip
sourceszip :
	zip -q -r PSE.zip *.h *.cpp Makefile testOutput testInput
#--zip quietly and recursively
