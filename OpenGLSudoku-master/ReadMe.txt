also note the OpenGL code was taught to me by Nehe tutorials... so credit must be given
nehe can be found by typing nehe into a google search.



Updates Version 1.1
1.  The logic of the solver was updated causing a great increase in speed on the generator.
2.  Reseting the solution was changed to pressing the Z key, bacause it was easy
    to accidently reset the solution if a windows popup message came up.
3.  Highlighted box was made bolder
4.  Background added 
5.  More complex puzzles are possible if you change the code in the random generator
    specificly change the loop control of numbersgenerated.  It is important to note,
    since the logic doesn't allow guesses the program cannot find a puzzle with 22 
    hints (numbers generated), and 23 hints takes between 2-5minutes depending on the 
    computer.  If you put 22 in you will end up with a never ending loop so be careful.
    A user input of this will be added later.
6.  Menu prototype was added if you hit F_2 you will see it pop up to the left all 
    events will affect the menu while it is engaged and not the sudoku board.  It can
    be disengaged by pressing F_2 again.

Updates Version 1.2
1.  Menu is 95% functional
2.  User can chose 3 difficulty modes
3.  Under expert level user can chose the number of hints that will be generated
4.  Save Game added
5.  Load Game added
6.  The moving background is now customizeable
7.  Settings are saved after user makes a change
8.  settings are loaded on boot so it saves user chosen difficulty level 
    and background from the last time the game was played.
9.  In any mode other than beginner holding a shift key while pressing 1-9 will 
    "mark" the square as possible or not possible depending on its current boolean.  
     This makes it easier to track your own logic while playing the game.

                            User Controls
Directions (left, right, up, down)   to move the highlighted square and navigate menus
F2:                                  Initiate the menu
Enter:                               Make a menu choice
1-9:                                 Input that number into the square that is highlighted
Shift + 1-9:                         Mark that square as possible or not possible (all modes but beginner)
Z:                                   At any time this will generate a new puzzle
F1:                                  To leave fullscreen mode at any time
ESC:                                 To quit the game

All code was developed my Lesshardtofind/John Rodney with the exception of the information
that was provided by Nehe tutorials (no code was copy-pasted even from web sources). 