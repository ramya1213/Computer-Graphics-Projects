#include <string>
using namespace std;

// space will hold a width, height, vertice coordinates and centerpoint and draw itself as a square
class BoardSpace{
      private: 
        GLfloat centerpoint[3], width, height, topleft[3], topright[3], bottomright[3], bottomleft[3];
        // this represents all the numbers the square could possibly be.
        bool possible[9];
        // this represents if this is one of the originally generated hints so it can't be written over on advanced mode
        bool permanent;
        // the amount of numbers this square can possibly be
        int numberofpossible;
        // the rotation controls
        GLfloat localzrotcontrol, globalzrotcontrol;
        // stores the given rotation point for the global rotation aka x, y, z coords
        GLfloat globalrotationaxis[3];
        // flag for a menu item
        bool menu;
        // bool flag that sets if a menu item is active. chosen is for optionsmenu
        bool active, chosen;
        // floats that track the texture coordinates of this object
        GLfloat textopleft[2], texbottomright[2]; // assumes its a rectange  [0] = x coord [1] = y coord
        GLfloat texwidth, texheight; //texture's width and height
      public:
        //set the default width and height.
        BoardSpace();
        // deconstruct
        ~BoardSpace();
        // allow to turn the possible flag for a number false
        void MakeNotPossible(int number);
        // allow to turn the possible flag for a number true
        void MakePossible(int number);
        // render the square
        void Render(GLuint spacetexture);
        // set the square's centerpoint
        void SetCenter(GLfloat x, GLfloat y, GLfloat z);
        // send the numberofpossible choices back to the parent Board
        int NumberOfPossible();
        // send if any given number is possible to parent board
        bool IsPossible(int numbercheck);
        // reset the boolean holders and number possible
        void Reset();
        // resize the space to allow the quad texture to be used for other purposes
        void SetSize(GLfloat w, GLfloat h);
        // return center x value
        GLfloat CenterX();
        // return center y value
        GLfloat CenterY();
        // return center z value
        GLfloat CenterZ();
        // rotation added for menu usage  
        // one rotation is for around a center point that is not the object
        void GlobalRotateZ(GLfloat angle);
        // one rotation is for rotating around itself so the menu items can stay facing upright
        void LocalRotateZ(GLfloat angle);
        // allow global rotation axis coordinates to be passed into the space
        void GiveGlobalAxis(GLfloat x, GLfloat y, GLfloat z);
        // tell the square its used for a menu
        void SetMenu();
        // change the active either true to false or false to true
        void ChangeActive();
        // returns if its active or not
        bool Active();
        // changes texture coordinates
        void ChangeTexCoords(GLfloat topleftx, GLfloat toplefty, GLfloat width, GLfloat height);
        // change the square to the opposite of "chosen"
        void ChangeChosen();
        // return if a box is chosen
        bool Chosen();
        // return if the space permanent
        bool Permanent();
        // Make it permanent
        void MakePermanent();
};

// since I couldn't find a truly transparent code for OpenGL I made this class 4 really thin connected quads that has 
// no center texture. This is the red box that surrounds the box the user is currently "over" or about to input a value for
class SeeThroughSquare{
  private:
    // Border size will make the border changable to be thicker or thinner
    GLfloat bordersize;
    // represents the centerpoint that the four quads will be drawn around, width and height should be obvious
    // they hold the values of the square's current size.
    GLfloat centerpoint[3], width, height;
    // Since BoardSpace is a single Quadclass that can hold a texture and will render itself around a centerpoint
    // there is no point in redefining any new rendering functions here.
    BoardSpace TopEdge, BottomEdge, LeftEdge, RightEdge;
  public:
    // constructor for seethrough square.. Becuause this square will be a constant all the values of the Edges will be set here
    SeeThroughSquare();
    // deconstructor
    ~SeeThroughSquare();
    // Since everytime the centerpoint of this object is moved each of its 4 edges need to be moved based off its centerpoint
    void SetEdgeCenters();
    // return so you can see what its x and y coordinates are
    GLfloat CenterX();
    GLfloat CenterY();
    // all the center to be changed so the highlight square can be moved based off input
    void SetCenter(GLfloat x, GLfloat y, GLfloat z);
    // this just passes a request to use BoardSpace's built in render function
    void Render(GLuint bordertexture);
    // this allows the size of this object to be set and resizes the edges based off its value
    void SetSize(GLfloat w, GLfloat h);
    // allow the border size to be changed to the user's choice
    void SetBorderSize(GLfloat newsize);
};

// used to store data and textures of the different "states" of the current Game
class Board{
      private:
// this is where actual data of a filled board will be stored 0 = blank, 1= 1, 2= 3, ect;
        int datamap[9][9];
// this is the class that handles rendering width and height of spaces the dataanalyzation will be done within the board, but
// the rendering will be done within the Space
        BoardSpace Space[9][9];
      public:
// Initialize the board and set all Spaces to blank;
        Board();
// deconstruct the board
        ~Board();
// pass if a given space is possible to parent Sudoku from child Space[r][c]
        bool IsPossible(int numbercheck, int r, int c);
// pass a request from sudoku generator to make a space not possible to the space
        void MakeNotPossible(int number, int row, int col);
// pass a request from sudoku to make a number in a given space possible
        void MakePossible(int number, int row, int col);
// clear the entire boards datamap back to 0;
        void Clear();
// fill one space in the datamap[r][c] with int number;
        void Fill(int number, int row, int column);
// return true if the number given matches the number in this datamap[r][c]
        bool Match(int number, int row, int column);
// return the current value of datamap[r][c]
        int Read(int row, int column);
// render all the board's susequent spaces
        void Render(int row, int column, GLuint spacetexture);
// send numberofpossible value of child space to parent Sudoku
        int NumberOfPossible(int r, int c);
// return if this board is full aka no space is blank
        bool Full();
// tell the child space to make its permanent boolean true
        void MakePermanent(int r, int c);
// bool request passed to child space to see if it is permanent
        bool Permanent(int r, int c);
};

//----------------------------------------------------------------------------------
//----------------------Beginning of the moving background class -------------------

class MovingBackground{
   private:
      // int that stores conditions for what behavior the background objects will have
      int BehaviorChoice;
      // again the background that stays still can be drawn on a quad the same as a boardspace
      BoardSpace StationaryBG; // background that doesn't move;
      // multiple quads that will scroll through the screen;
      BoardSpace MovingObjects[50];
      // booleans to control customizeable movement the first position in each array
      // [0] refers to if this is on or off 
      // [1] refers to the direction left and up [0]  right and down [1]
      bool horizontal[2], vertical[2], localrot[2], globalrot[2];
   public:
      MovingBackground();
      ~MovingBackground();
      // controls the behavior of the moving objects in the background
      void ObjectBehavior();
      // change the behavior changes the behavior to a different index
      void ChangeBehavior(int behavortochange, int direction);
      // Renders and processes the Background and all its parts
      void Handle(GLuint stationarytexture, GLuint movingtexture);
      // returns the booleans so that settings can be saved
      bool BehaviorSettings(int behaviorchoice);
      bool BehaviorDirection(int behaviorchoice);
};
      
      
//  ---------------------------------END OF MOVING BACKGROUND ----------------------

//-----------------------------------------------------------------------------------
// -------------------------Beginning of Menu Declaration ---------------------------
// smenu = sudoku menu
class Smenu{
      private:
        // to control the middle of all five menu items... pentagon
        GLfloat centerpoint[3];
        // to control if the menu is active
        bool active;
        // to render the menu items 
        BoardSpace MenuItems[5];
        BoardSpace OptionMenuItems[38];
        int test;
        // to control if the option menu is active
        bool optionactive;
        // to control if the rotation is global or local
        int rotation; // 0 = local 1 = global
      public:
        //construct
        Smenu();
        // destruct
        ~Smenu();
        // returns Optionactive
        bool OptionActive();
        // returns active
        bool Active();
        // handles the menu
        void Handle(GLuint menutexture,
                    GLuint loadtexture,
                    GLuint savetexture,
                    GLuint continuetexture,
                    GLuint optiontexture,
                    GLuint suboptiontexture);
        // make a selection
        int MakeSelection();
        // change active to on or off depending on whaty it is
        void ChangeActive();
        // rotate its parts in direction 0 = right  1 = left
        void Rotate(int direction);
        // reset all the option menu items to inactive
        void ResetOptionMenu();
        // handle option menu events direction 0 = left 1 = up 2 = right 3 = down
        void MoveChosen(int direction);
        // return the current rotation selection local or global
        int Rotation();
};

// --------------------------END of Menu Declaration --------------------------------
// This should handle all functions needed within the game of sudoku
// the goal is to allow for a game selection eventually
// numbtextures is a constant to make it easier to add textures as the game evolves
// just change to the new number of textures and add a case to the switch in the load textures function
const int numtextures = 28;
class Sudoku{
  private:
// Board is a class array that will be used to check instances
// of the board.  9 will be the solution 8 will be the displayed
// screen, and counting down from there will be previous turns allowing
// for undo's when playing intermediate where the computer allows inncorect moves
    Board GameBoard[10];
// two ints that will hold the r, and c that the highlight is on
        int highlightr, highlightc;
// Use the built in abilities of a boardspace and utilize it to display a loading screen before the 
// New sudoku board is generated.
    BoardSpace Load;
// the class that sudoku uses to display where the user is currently positioned
   SeeThroughSquare Highlight;
// this is to make a darker boarder around the 3x3 grids just like a typical sudoku game 
// sudoku owns this because every board doesn't need it since only one board is displayed at a time
   SeeThroughSquare Darklines;
// onece again use Boardspace for a flat texturedisplay this one will display in the top right
   BoardSpace NumbersPossibleTitle;
// this is used to show each number that is possible
   BoardSpace NumberPossible;
// integer used when troublshooting the random generator with the solve function
   int NumbersToGen, eventdelay;
// playing will be the loop control to keep the player in the sudoku game aka Sudoku.Handle()
// will only prcess when Sudoku.Playing() is true. Birth will be 0 to load loading screen then 1 to load textures and generate 
// puzzle
    bool playing;
    int birth; 
    // this will be the storage for all 10 Textures of a board space numbers 1-9 and blank space
    GLuint texture[numtextures];
// boolean to declare if the game has been beat and if the user has alredy been congratulated.. failed if they
// messed up and have already been told about it
    bool beat, failed;
// moving background does what is sounds like... some features are there to allow changing behavior so that a menu function 
// can be added to allow versitility to this class
   MovingBackground Smovingbackground;  // sudoku moving background
// menu
   Smenu Menu;
// tracks difficulty 0 = beginner 1 = intermed 2 = adv
   int difficulty;  
// Moving background texture ... allows this to be chosen
   int textureindex;
  public:
// initiate all the boards and variables
    Sudoku();
// deconstructor
    ~Sudoku();
// move highlight position
   void MoveHighlight(int direction);
// used to load the textures
   AUX_RGBImageRec *LoadBMP(char *Filename);
// load textures used in the game
   int LoadTextures();
// set the loading texture up
   void Loading();
// allows copying of data from one board to the next
   void Copy(int Copyfromindex, int Copytoindex);
// will turn the playing flag on
   void Play();
// return the private boolean so its readable, but not writeable
    bool Playing();
// mark all spaces as possible or not possible (aka what numbers can possibly go there following sudoku logic
   void MarkSpaces(int boardindex);
// will clear the current solution aka GameBoard[9]  allowing for a new game in the middle of an old one
    void ResetSolution();
// This will randomly generate numbers and check with the rules to see if the number is allowed before placing it
    void GeneratePuzzle();
// Generate Puzzle will use this solving function to see if the numbers it generated can be solved in 100 moves
    bool Solvable(int boardindex);
// This will Permanently place a new move in the board
    void SetMove(int number, int row, int column);
// This will check if the move is valid before passing it to SetMove()
    void CheckMove(int number, int row, int column);
// This will copy the current board to 8 and 8 to 7 ect.  allowing for undo or previous turn viewing
    void StartNewTurn();
// This will handle all rendering
    void Handle();
// handle the events in the sudoku 
    void Events(bool keys[]);
// check if a move is valid and fill it
    void CheckMove(int number);
// reset birth to generate a new board
    void Reset();
//  this was added later because in some cases my generator logic broke down and accepted a sudoku against the rules
    bool ValidateSolution();
//  this will find out the row and column of the highlight space and save it to highlightr, and highlightc
    void FindHighlight();
//  this sets the menu to active or unactive depending on its current value
    void MChangeActive();
//  communicate if the menu is active to the event handler
    bool MenuActive();
// tell the menu to rotate value of direction 0 = right   1 = left
    void MenuRotate(int direction);
// load the game
    void LoadGame(string Filename);
// save the game
    void SaveGame(string Filename);
// make menu selections
    void MenuSelection();
// request information from menu if its option menu is active
    bool MenuOptionActive();
// tell the menu to change is chosen
    void MenuMoveChosen(int direction);
// user mark mode the initiation will clear any marks the CPU did
    void InitiateUserMark();
// sends the marked number to the boardspace as a possibility
    void MarkSpace(int number);
// saves the settings choices after every settings change
    void SaveSettings();
// loads the settings default from the last time the program was ran
    void LoadSettings();
};
