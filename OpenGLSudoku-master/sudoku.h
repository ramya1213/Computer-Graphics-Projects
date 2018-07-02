// This should handle all functions needed within the game of sudoku
// the goal is to allow for a game selection eventually
class Sudoku{
  private:
// Board is a class array that will be used to check instances
// of the board.  9 will be the solution 8 will be the displayed
// screen, and counting down from there will be previous turns allowing
// for undo's when playing intermediate where the computer allows inncorect moves
    Board GameBoard[10];
// playing will be the loop control to keep the player in the sudoku game aka Sudoku.Handle()
// will only prcess when Sudoku.Playing() is true.
    bool playing; 
  public:
// initiate all the boards and variables
    Sudoku();
// deconstructor
    ~Sudoku();
// return the private boolean so its readable, but not writeable
    bool Playing();
// will clear the current solution aka GameBoard[9]  allowing for a new game in the middle of an old one
    void ResetSolution();
// This will randomly generate numbers and check with the rules to see if the number is allowed before placing it
    void GenerateSolution();
// This will Permanently place a new move in the board
    void SetMove(int number, int row, int column);
// This will check if the move is valid before passing it to SetMove()
    void CheckMove(int number, int row, int column);
// This will copy the current board to 8 and 8 to 7 ect.  allowing for undo or previous turn viewing
    void StartNewTurn();
// This will handle all rendering
    void Handle();
};

// used to store data and textures of the different "states" of the current Game
class Board{
      private:
// this is where actual data of a filled board will be stored 0 = blank, 1= 1, 2= 3, ect;
        int datamap[9][9];
// this will be the storage for all 10 Textures of a board space numbers 1-9 and blank space
        GLuint texture[10];
// this is the class that handles rendering width and height of spaces the dataanalyzation will be done within the board, but
// the rendering will be done within the Space
        BoardSpace Space[9][9];
      public:
// Initialize the board and set all Spaces to blank;
        Board();
// deconstruct the board
        ~Board();
// load textures used to pass to spaces
        void LoadTextures();
// clear the entire boards datamap back to 0;
        void Clear();
// fill one space in the datamap[r][c] with int number;
        void Fill(int number, int row, int column);
// return true if the number given matches the number in this datamap[r][c]
        bool Match(int number, int row, int column);
// return the current value of datamap[r][c]
        int Read(int row, int column);
// render all the board's susequent spaces
        void Render();
};

// space will hold a width, height, and centerpoint and draw itself as a square
class BoardSpace{
      private: 
        GLfloat centerpoint[3], width, height;
      public:
        //set the default width and height.
        BoardSpace();
        // deconstruct
        ~BoardSpace();
        // render the square
        void Render(GLuint spacetexture);
        // set the square's centerpoint
        void SetCenter(GLfloat x, GLfloat y, GLfloat z)
};
