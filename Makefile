
CMP= g++
CLASS1 = player
CLASS2= target
CLASS3= shot
MAIN= project
EXEC= game

$(EXEC): $(CLASS1).o $(CLASS2).o $(CLASS3).o  $(MAIN).o
	$(CMP)  gfx.o -lX11 $(CLASS1).o $(CLASS2).o $(CLASS3).o $(MAIN).o -o $(EXEC) -std=c++11

$(CLASS1).o: $(CLASS1).cpp $(CLASS1).h
	$(CMP) -c $(CLASS1).cpp -o $(CLASS1).o 

$(CLASS2).o: $(CLASS2).cpp $(CLASS2).h
	$(CMP) -c $(CLASS2).cpp -o $(CLASS2).o 

$(CLASS3).o: $(CLASS3).cpp $(CLASS3).h
	$(CMP) -c $(CLASS3).cpp -o $(CLASS3).o

$(MAIN).o: $(MAIN).cpp $(CLASS1).h $(CLASS2).h $(CLASS3).h
	$(CMP) -c $(MAIN).cpp -o $(MAIN).o -std=c++11 
	
clean:
	rm *.o
	rm $(EXEC)
