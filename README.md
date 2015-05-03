Othello AI
CS242 
Antonio Cardenas (hcardena)/ Colin Pronovost (cpronovo)/ Cesar De Hoyos (cdehoyos)

This package includes an Othello player based in minimax search. The input and output is formatted to work with H. Kautz's tournament interface.

Languages used: C/C++
	The choice of using C++ was done because it would help with multi-threading (not implemented due to lack fo time) and because it would be overall faster than other languages.
	We used a minimax search because we thought it would provide an effective way of optimizing moves in a time restricted environment.
	
Testing:
	Testing was done by playing against the Kautz player.

Data structures:
	The program uses a state class to represent state instances in vectors while holding a global reference to a best state. 
	AlphaBeta pruning is implemented for efficiency. 

Cost function
The evaluation of states is done through naive weighting of piece counts. A numeric value is assigned by adding the enumerated values of each board slot. The enumeration is:
			Black: -1
			White: 1
			Blank: 0

Description of files:

state.h:	
			This header file contains the State class definition for the player. The class includes a board representation and a move that defines the action that produced each instance.
			It also includes a node to the parent state. It contains the color enumeration definition.


playAntonio.cpp
			This defines the main class as well as the I/O methods and the search function. 
