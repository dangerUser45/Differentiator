Compiler = g++
B        = build_diff/
Target   = diff
#-----------------------------------------------------------------------

$(Target):      $(B)Diff_Main.o $(B)Diff_Init.o $(B)Diff.o $(B)Diff_Dump.o $(B)Recursive_descent.o $(B)Eval.o $(B)LaTeX.o $(B)TXLib.o $(B)Print.o $(B)Processing.o
	$(Compiler) $(B)Diff_Main.o $(B)Diff_Init.o $(B)Diff.o $(B)Diff_Dump.o $(B)Recursive_descent.o $(B)Eval.o $(B)LaTeX.o $(B)TXLib.o $(B)Print.o $(B)Processing.o -o diff.exe
#-----------------------------------------------------------------------

$(B)Diff_Main.o : Diff_Main.cpp                                  \
				Diff_Common.h                                    \
				Recursive_descent.h                              \
				Diff_Init.h                                      \
				Eval.h                                           \
				Diff_Dump.h                                      \
				LaTeX.h
	$(Compiler) -c Diff_Main.cpp -o $(B)Diff_Main.o

$(B)Diff_Init.o : Diff_Init.cpp                                  \
                Diff_Init.h                                      \
				..\Processor\Onegin_for_proc\Onegin_processing.h \
				..\Processor\Onegin_for_proc\Onegin_General.h    \
				..\Processor\Onegin_for_proc\Print.h
	$(Compiler) -c Diff_Init.cpp -o $(B)Diff_Init.o

$(B)Diff.o : Diff.cpp                                            \
		   Diff_Common.h
	$(Compiler) -c Diff.cpp -o $(B)Diff.o
				 

$(B)Diff_Dump.o : Diff_Dump.cpp                                  \
				  Diff_Dump.h                                    \
				  Diff_init.h                                          
	$(Compiler) -c Diff_Dump.cpp -o $(B)Diff_Dump.o


$(B)Recursive_descent.o: Recursive_descent.cpp                   \
				Diff.h                                           \
				Recursive_descent.h
	$(Compiler) -c Recursive_descent.cpp -o $(B)Recursive_descent.o

$(B)Eval.o : Eval.cpp                                            \
			 Eval.h                                              \
			 Diff_Common.h 
	$(Compiler) -c Eval.cpp -o $(B)Eval.o

$(B)LaTeX.o : LaTeX.cpp                                          \
			  LaTeX.h                                            \
			  Diff_Init.h
	$(Compiler) -c LaTeX.cpp -o $(B)LaTeX.o

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
	