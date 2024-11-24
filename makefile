
Compiler = g++
B        = build_diff/
Target   = diff

#-----------------------------------------------------------------------

$(Target):      $(B)Diff.o $(B)Diff_init.o $(B)TXLib.o $(B)Print.o $(B)Processing.o
	$(Compiler) $(B)Diff.o $(B)Diff_init.o $(B)TXLib.o $(B)Print.o $(B)Processing.o -o diff.exe
#-----------------------------------------------------------------------

$(B)Diff.o : Diff.cpp                                            \
				Diff.h                                           \
				..\Processor\Onegin_for_proc\Onegin_processing.h \
				..\Processor\Onegin_for_proc\Onegin_General.h    \
				..\Akinator\akinator.h
	$(Compiler) -c Diff.cpp -o $(B)Diff.o

$(B)Diff_init.o : diff_init.cpp                                  \
                Diff.h                                           \
				..\Processor\Onegin_for_proc\Onegin_processing.h \
				..\Processor\Onegin_for_proc\Onegin_General.h    \
				..\Processor\Onegin_for_proc\Print.h
	$(Compiler) -c diff_init.cpp -o $(B)diff_init.o

$(B)Print.o : ../Processor/Onegin_for_proc/Print.cpp             \
		      ../Processor/Onegin_for_proc/Onegin_General.h      \
			  ../Processor/Onegin_for_proc/Print.h
	$(Compiler) -c  ../Processor/Onegin_for_proc/print.cpp -o $(B)print.o

$(B)Processing.o : ../Processor/Onegin_for_proc/Processing.cpp      \
				   ../Processor/Onegin_for_proc/Onegin_General.h    \
				   ../Processor/Onegin_for_proc/Onegin_Processing.h \
				   ../Processor/Onegin_for_proc/Print.h
	$(Compiler) -c ../Processor/Onegin_for_proc/Processing.cpp -o $(B)Processing.o

$(B)TXLib.o : TXLib.cpp
	$(Compiler) -c TXLib.cpp -o $(B)TXLib.o

#---------------------------------------------------------------------------
clean :
	del build_diff\*.o
	