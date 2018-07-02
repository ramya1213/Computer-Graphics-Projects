#include <windows.h>
#include <stdio.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <string>
#include <sudoku.h>
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;
Sudoku::Sudoku()
{
  playing = false;
  birth = 0;
  Highlight.SetCenter(-4.0f, 4.0f, -14.9999f);
  Highlight.SetBorderSize(.05f);
  eventdelay = 0;
  Darklines.SetSize(3.0f, 3.0f);
  NumbersPossibleTitle.SetSize(3.0f, 2.0f);
  NumbersPossibleTitle.SetCenter(7.0f, 5.0f, - 14.9999f);
  highlightr = 0;
  highlightc = 0;
  NumberPossible.SetSize(1.0f, 1.0f);
  NumbersToGen = 28; // default numbers to start with
  difficulty = 0;
  failed = false;
  textureindex = 25; // default background is black
  Smovingbackground.ChangeBehavior(0, 0); // set a default moving BG
  LoadSettings();
}

Sudoku::~Sudoku()
{
}

void Sudoku::LoadSettings()
{
  ifstream inp;
  string myFileName;
  string line;
  char temp, tempa;
  int timesran = 0; // keeps track so we don't store anything the last time
  myFileName = "settings.txt";
  inp.open(myFileName.c_str(), ifstream::in);
  inp.close();
  if(!inp.fail())
  {
    inp.clear(ios::goodbit);
    inp.open(myFileName.c_str(), ifstream::in);
    if(inp.is_open())
    {
      //MessageBox(NULL, "made it", "ok", MB_OK | MB_ICONEXCLAMATION);
      for(int timesran = 0; timesran < 6; timesran++)
      {
          getline(inp, line);
          if(timesran == 0)
          {
            temp = line[0];
            difficulty = temp - '0';
          }
          else if(timesran == 1)
          {
            temp = line[0];
            tempa = line[1];
            if((temp - '0') > 0)
              Smovingbackground.ChangeBehavior(0 , (tempa - '0'));
          }
          else if(timesran == 2)
          {
            temp = line[0];
            tempa = line[1];
            if((temp - '0') > 0)
              Smovingbackground.ChangeBehavior(1 , (tempa - '0'));
          }
          else if(timesran == 3)
          {
            temp = line[0];
            tempa = line[1];
            if((temp - '0') > 0)
              Smovingbackground.ChangeBehavior(2 , (tempa - '0'));
          }
          else if(timesran == 4)
          {
            temp = line[0];
            tempa = line[1];
            if((temp - '0') > 0)
              Smovingbackground.ChangeBehavior(3 , (tempa - '0'));
          }
          else if(timesran == 5)
          {
            temp = line[0];
            tempa = line[1];
            int tens = temp - '0';
            int ones = tempa - '0';
            textureindex = (tens*10)+ones;
          }
      }
      inp.close();
    } 
  }
}

void Sudoku::SaveSettings()
{
  ofstream myfile("settings.txt");
  if(myfile.is_open())
  {
    myfile<<difficulty<<endl;
    if(Smovingbackground.BehaviorSettings(0))
      myfile<<"1";
    else
      myfile<<"0";
    if(Smovingbackground.BehaviorDirection(0))
      myfile<<"1"<<endl;
    else
      myfile<<"0"<<endl;
    if(Smovingbackground.BehaviorSettings(1))
      myfile<<"1";
    else
      myfile<<"0";
    if(Smovingbackground.BehaviorDirection(1))
      myfile<<"1"<<endl;
    else
      myfile<<"0"<<endl;
    if(Smovingbackground.BehaviorSettings(2))
      myfile<<"1";
    else
      myfile<<"0";
    if(Smovingbackground.BehaviorDirection(2))
      myfile<<"1"<<endl;
    else
      myfile<<"0"<<endl;
    if(Smovingbackground.BehaviorSettings(3))
      myfile<<"1";
    else
      myfile<<"0";
    if(Smovingbackground.BehaviorDirection(3))
      myfile<<"1"<<endl;
    else
      myfile<<"0"<<endl;
    myfile<<textureindex<<endl;  
    myfile.close();
  }
}

void Sudoku::MarkSpace(int number)
{
  if(difficulty != 0)// not allowed in beginner mode
  {
    if(eventdelay == 0)
    {
      FindHighlight();
      GameBoard[8].MakePossible(number, highlightr, highlightc);
      eventdelay = 50;
    }
  }
}

void Sudoku::InitiateUserMark()
{
  // clear all possibles in Board 8's spaces
  for(int r = 0; r < 9; r++)
  {
    for(int c = 0; c < 9; c++)
    {
      for(int number = 1; number < 10; number++)
      {
        GameBoard[8].MakeNotPossible(number, r, c);
      } 
    }
  }
}

bool Sudoku::MenuOptionActive()
{
  return Menu.OptionActive();
}

void Sudoku::MenuMoveChosen(int direction)
{
  Menu.MoveChosen(direction);
}

void Sudoku::Events(bool keys[])
{
  if(keys[VK_F2])
      {
        MChangeActive();
      }
      if(MenuActive()) // if the sudoku menu is active
      {
        if(MenuOptionActive())
        {
          if(keys[VK_LEFT])
          {
            MenuMoveChosen(0);
            keys[VK_LEFT] = false;
          }
          if(keys[VK_UP])
          {
            MenuMoveChosen(1);
            keys[VK_UP] = false;
          }
          if(keys[VK_RIGHT])
          {
            MenuMoveChosen(2);
            keys[VK_RIGHT] = false;
          }
          if(keys[VK_DOWN])
          {
            MenuMoveChosen(3);
            keys[VK_DOWN] = false;
          }
          if(keys[VK_RETURN])
          {
            MenuSelection();
            keys[VK_RETURN] = false;
          }
        }
        else
        {
          if(keys[VK_RIGHT])
          {
            MenuRotate(0); 
          }
          if(keys[VK_LEFT])
          {
            MenuRotate(1);
          }
          if(keys[VK_RETURN])
          {
            MenuSelection();
            keys[VK_RETURN] = false;
          }
        }
      }
      else
      {
        if(keys[VK_LEFT])
        {
          MoveHighlight(0);
        }
        if(keys[VK_UP])
        {
          MoveHighlight(1);
        }
        if(keys[VK_RIGHT])
        {
          MoveHighlight(2);
        }
        if(keys[VK_DOWN])
        {
          MoveHighlight(3);
        }
        if(keys['1'])
        {
          if(keys[VK_SHIFT])
          {
            MarkSpace(1);
           // keys[VK_SHIFT] = false;
          }
          else
          {
            CheckMove(1);
            keys['1'] = false;
          }
        }
        if(keys['2'])
        {
          if(keys[VK_SHIFT])
          {
            MarkSpace(2);
           // keys[VK_SHIFT] = false;
          }
          else
          {
            CheckMove(2);
            keys['2'] = false;
          }
        }
        if(keys['3'])
        {
          if(keys[VK_SHIFT])
          {
            MarkSpace(3);
            //keys[VK_SHIFT] = false;
          }
          else
          {  
            CheckMove(3);
            keys['3'] = false;
          }
        }
        if(keys['4'])
        {
          if(keys[VK_SHIFT])
          {
            MarkSpace(4);
            //keys[VK_SHIFT] = false;
          }
          else
          {
            CheckMove(4);
            keys['4'] = false;
          }
        }
        if(keys['5'])
        {
          if(keys[VK_SHIFT])
          {
            MarkSpace(5);
            //keys[VK_SHIFT] = false;
          }
          else
          {
            CheckMove(5);
            keys['5'] = false;
          }
        }
        if(keys['6'])
        {
          if(keys[VK_SHIFT])
          {
            MarkSpace(6);
            //keys[VK_SHIFT] = false;
          }
          else
          {
            CheckMove(6);
            keys['6'] = false;
          }
        }
        if(keys['7'])
        {
          if(keys[VK_SHIFT])
          {
            MarkSpace(7);
            //keys[VK_SHIFT] = false;
          }
          else
          {
            CheckMove(7);
            keys['7'] = false;
          }
        }
        if(keys['8'])
        {
          if(keys[VK_SHIFT])
          {
            MarkSpace(8);
            //keys[VK_SHIFT] = false;
          }
          else
          {
            CheckMove(8);
            keys['8'] = false;
          }
        }
        if(keys['9'])
        {
          if(keys[VK_SHIFT])
          {
            MarkSpace(9);
            //keys[VK_SHIFT] = false;
          }
          else
          {
            CheckMove(9);
            keys['9'] = false;
          }
        }
        if(keys['0'])
        {
          CheckMove(0);
          keys['0'] = false;
        }
      }
      if(keys['Z'])
      {
        Reset();
        keys['Z'] = false;
      }
}

void Sudoku::LoadGame(string Filename)
{
  // saves the current line in the file 
  string line;
  // a int to track what line we are on.. file is known to have 19 lines 9lines..blank link... 9 lines
  int linenumber = 0;  // call it 0 instead of one to be compatible with array index
  ifstream myfile (Filename.c_str());
  // so we can change both boards with one loop
  int boardindex = 9;
  if(myfile.is_open())
  {
      // while its not the end of the file
      while(!myfile.eof())
      {
        getline(myfile,line);
          // change the board to 8 and make rows compatible again
          if(linenumber == 9 && boardindex != 8)
          {
            linenumber = 0;
            boardindex = 8;
          }
        if(linenumber != 9)
        {
          for(int c = 0; c < 9; c++)
          {
            int temp = -1; // becomes the integar read saved as -1 in case of error
            char ctemp; // a character of the current point in the string
            ctemp = line[c];
            temp = ctemp - '0';
            GameBoard[boardindex].Fill(temp, linenumber, c); 
          }
        }
          linenumber++;        
      }
      myfile.close();
  }
}

void Sudoku::MenuSelection()
{
  int selection = Menu.MakeSelection();
  
  if(selection == 0)
    MessageBox(NULL, "Make a choice please or press F_2 to Exit Menu", "Duh", MB_OK | MB_ICONEXCLAMATION);
  if(selection == 1)
    LoadGame("test.txt");
  if(selection == 2)
    SaveGame("test.txt");
  if(selection == 3)
    Menu.ChangeActive();           
  for(int x = 37; x < 43; x++)
  {
    if(selection == x)
    {
      difficulty = 2;
      NumbersToGen = x - 14;
      birth = 0;
    }
  }       
  if(selection == 7)
    difficulty = 0;
  if(selection == 11)
  {
    difficulty = 1;
    InitiateUserMark();
  }
  if(selection == 15)
  {
    difficulty = 2;
    InitiateUserMark();
  }
  if(selection == 8)
    Smovingbackground.ChangeBehavior(0, 1);
  if(selection == 12)
    Smovingbackground.ChangeBehavior(0, 0);
  if(selection == 16)
    Smovingbackground.ChangeBehavior(1, 0);
  if(selection == 20)
    Smovingbackground.ChangeBehavior(1, 1);
  if(selection == 31 && (Menu.Rotation() == 0))
    Smovingbackground.ChangeBehavior(2, 1);
  if(selection == 31 && (Menu.Rotation() == 1))
    Smovingbackground.ChangeBehavior(3, 1);
  if(selection == 32 && (Menu.Rotation() == 0))
    Smovingbackground.ChangeBehavior(2, 0);
  if(selection == 32 && (Menu.Rotation() == 1))
    Smovingbackground.ChangeBehavior(3, 0);   
  if(selection == 22)
    textureindex = 14;
  if(selection == 26)
    textureindex = 21;
  if(selection == 27)
    textureindex = 25;
  if(selection == 30)
    textureindex = 23;
  SaveSettings();
}

void Sudoku::SaveGame(string Filename)
{ 
  int a, b; 
  ofstream myfile (Filename.c_str());
  if (myfile.is_open())
  {
    // save the solution
    for(a = 0; a < 9; a++)
    {
      for(b = 0; b < 9; b++)
      {
        myfile << GameBoard[9].Read(a, b);
      }
      myfile <<endl;
    }   
    // save the user's game
    for(a = 0; a < 9; a++)
    {
      for(b = 0; b < 9; b++)
      {
        myfile<< GameBoard[8].Read(a, b);
      }
      myfile << endl;
    }
    myfile.close();
  }
}

void Sudoku::MenuRotate(int direction)
{
  if(eventdelay == 0)
  {
    Menu.Rotate(direction);
    eventdelay = 25;
  }
}

bool Sudoku::MenuActive()
{
  return Menu.Active();
}

void Sudoku::FindHighlight()
{
  int temp = (int)Highlight.CenterX();
  switch(temp)
  {
    case -4: highlightc = 0; break;
    case -3: highlightc = 1; break;
    case -2: highlightc = 2; break;
    case -1: highlightc = 3; break;
    case 0: highlightc = 4; break;
    case 1: highlightc = 5; break;
    case 2: highlightc = 6; break;
    case 3: highlightc = 7; break;
    case 4: highlightc = 8; break;
  }
  temp = (int)Highlight.CenterY();
  switch(temp)
  {
    case 4: highlightr = 0; break;
    case 3: highlightr = 1; break;
    case 2: highlightr = 2; break;
    case 1: highlightr = 3; break;
    case 0: highlightr = 4; break;
    case -1: highlightr = 5; break;
    case -2: highlightr = 6; break;
    case -3: highlightr = 7; break;
    case -4: highlightr = 8; break;
  }    
}    

void Sudoku::MoveHighlight(int direction)
{
  // values of direction 
  // 0: left
  // 1: up
  // 2: right
  // 3: left
  if(eventdelay == 0)
  {
    switch(direction)
    {
      case 0: if(Highlight.CenterX() > -4.0f) 
                Highlight.SetCenter(Highlight.CenterX()-1.0f, Highlight.CenterY(), -14.9999f);
      break;
      case 1: if(Highlight.CenterY() < 4.0f)
                Highlight.SetCenter(Highlight.CenterX(), Highlight.CenterY()+1.0f, -14.9999f);
      break;
      case 2: if(Highlight.CenterX() < 4.0f)
                Highlight.SetCenter(Highlight.CenterX()+1, Highlight.CenterY(), -14.9999f);
      break;
      case 3: if(Highlight.CenterY() > -4.0f)
                Highlight.SetCenter(Highlight.CenterX(), Highlight.CenterY()-1, -14.9999f);
      break;
    }
    eventdelay = 50;
  } 
}

void Sudoku::CheckMove(int number)
{
  // two numbers to find the r and c that highlight is over
  FindHighlight();
  if(difficulty < 2)
  {
    if(eventdelay == 0)
    {
      if(GameBoard[9].Read(highlightr, highlightc) == number)
      {
        GameBoard[8].Fill(number, highlightr, highlightc);
      }
      else
        MessageBox(NULL, "Not a valid move", "sorry", MB_OK | MB_ICONEXCLAMATION);
      eventdelay = 50;
    }
  }
  else // if its on the hardest we let incorrect moves happen
  {
    if(eventdelay == 0)
    {
      if(!GameBoard[8].Permanent(highlightr, highlightc))
      {
        GameBoard[8].Fill(number, highlightr, highlightc);
        eventdelay = 50;
        failed = false; // so that you can check the board again if they failed once and went back
      }
      else
        MessageBox(NULL, "Whoa you can't write over the original hints.", "Mistake", MB_OK | MB_ICONEXCLAMATION);
    }
  }
}

// Changing this flag will cause the main scenerendering loop to handle Sudoku
void Sudoku::Play()
{
  playing = true;
}

/// check for if the flag has been triggered
bool Sudoku::Playing()
{
  return playing;
}
// clear the solutioin board
void Sudoku::ResetSolution()
{
  GameBoard[8].Clear();
  GameBoard[9].Clear();
}
// final check to validate that the sudoku is correct
bool Sudoku::ValidateSolution()
{
  // boolean to control if its valid.. assume it is and prove it wrong
  bool valid = true;
  // will be saved as the current value of the space the loop is on
  int temp;
  for(int r = 0; r < 9; r++)
  {
    for(int c = 0; c < 9; c++)
    {
      temp = GameBoard[9].Read(r, c);
      // check columns 
      for(int colcheck = 0; colcheck < 9; colcheck++)
      {
        // only look at the spaces at aren't our current space we are validating
        if(colcheck != c)
        {
          if(temp == GameBoard[9].Read(r, colcheck))
            valid = false;
        }
      }
      // check rows
      for(int rowcheck = 0; rowcheck < 9; rowcheck++)
      {
        // only look at the spaces at aren't our current space we are validating
        if(rowcheck != r)
        {
          if(temp == GameBoard[9].Read(rowcheck, c))
            valid = false;
        }
      }
    }
  }
  // since there wasn't a breakdown of logic on each 3x3 grid, but it was on col and row I didn't validate
  // grid it was on as well.
  return valid;
}

void Sudoku::GeneratePuzzle()
{
  int tempnumber;
  int tempr;
  int tempc;
  int currentgridrow[2];
  int currentgridcol[2];
  bool solved = false;
// when a puzzle is generated beat should be set to false because we know the user hasn't solved it yet
  beat = false;
  while(!solved)
  {
    ResetSolution();
    for(int numberstogenerate = 0; numberstogenerate < NumbersToGen; numberstogenerate++)
    { 
      bool spotfound = false;
      while(!spotfound)
      {
        tempnumber = (rand()%9)+1;  // number
        tempr = (rand()%8);  // row
        tempc = (rand()%8);  // column
        MarkSpaces(9);
          if(GameBoard[9].Read(tempr, tempc) == 0 && GameBoard[9].IsPossible(tempnumber, tempr, tempc)) // if the random position is empty
          {
            GameBoard[9].Fill(tempnumber, tempr, tempc); // number, row, column
            spotfound = true;
          }
        Copy(9, 8);     
      }
    }
    if(Solvable(9))
    {
      if(ValidateSolution()) // final check to see if its valid
        solved = true;
    }
  }
  for(int r = 0; r < 9; r++)
  {
    for(int c = 0; c < 9; c++)
    {
      if(GameBoard[8].Read(r, c) != 0)
        GameBoard[8].MakePermanent(r, c);
    }
  }
  if(difficulty != 0)// if its not beginner mode
    InitiateUserMark();
}

void Sudoku::MarkSpaces(int boardindex)
{
  int currentgridrow[2];
  int currentgridcol[2];
  // look through the entire board
      for(int r = 0; r < 9 ; r++)
      {
        for(int c = 0; c < 9; c++)
        {
          if(GameBoard[boardindex].Read(r, c) == 0)
          {
            // this will look through all the rows and eliminate possible numbers that share the column with it.
            for(int rowcheck = 0; rowcheck < 9; rowcheck++)
            {
              // if the col of the first loop aka the col of the space that is being populated with a boolean map
              // of possibilities and the current variable row isn't 0;
              if(GameBoard[boardindex].Read(rowcheck, c) != 0) // if the number space isn't empty
              {
                // copy the value of this space into the boolean array index value and make it false
                // aka Since the number ALREADY exhists on this col then no other row in this column 
                // can have that number in it.
                //  { 1}{!1}{!1}{!1}{!1}{!1}{!1}{!1}{!1}
                //  {!1}{--}{--}{--}{--}{--}{--}{--}{--}
                //  {!1}{--}{--}{--}{--}{--}{--}{--}{--}
                //  {!1}{--}{--}{--}{--}{--}{--}{--}{--}
                //  {!1}{--}{--}{--}{--}{--}{--}{--}{--}  <<<-- When finished redraw logic based on this
                //  {!1}{--}{--}{--}{--}{--}{--}{--}{--}  <<<-- One loop can populate all squres not filled
                //  {!1}{--}{--}{--}{--}{--}{--}{--}{--}  <<<-- with their possibilities.  Then when it fills
                //  {!1}{--}{--}{--}{--}{--}{--}{--}{--}  <<<-- a space it can check only the row.. col.. and 3x3 
                //  {!1}{--}{--}{--}{--}{--}{--}{--}{--}  <<<-- of the space  (observer method?)
                GameBoard[boardindex].MakeNotPossible(GameBoard[boardindex].Read(rowcheck, c), r, c);  
              }
            }
            // this will look through all the columns and eliminate possible numbers that share the row with it.
            // not explained as much does exact duplicate of loop above except for the columns
            for(int colcheck = 0; colcheck < 9; colcheck++)
            {
              if(GameBoard[boardindex].Read(r , colcheck) != 0)
                GameBoard[boardindex].MakeNotPossible(GameBoard[boardindex].Read(r, colcheck), r, c);
            }
            // check its 3x3 grid and eliminate any number already here
            //  { 1}{!1}{!1}
            //  {!1}{!1}{!1}
            //  {!1}{!1}{!1} 
            // find out what grid we are in and set loop controls
            if(r >= 0 && r < 3) // first 3 rows
            {
              currentgridrow[0] = 0;
              currentgridrow[1] = 3; 
              if(c >= 0 && c < 3) // first 3 cols
              {// top-left 3x3 grid
                currentgridcol[0] = 0;
                currentgridcol[1] = 3;
              }
              else if(c >= 3 && c < 6) // second 3 cols
              {// top-middle 3x3 grid
                currentgridcol[0] = 3;
                currentgridcol[1] = 6;
              }
              else if(c >= 6 && c < 9) // first 3 cols
              {// top-right 3x3 grid
                currentgridcol[0] = 6;
                currentgridcol[1] = 9;
              }
            }
            else if(r >= 3 && r < 6) // second 3 rows
            {
              currentgridrow[0] = 3;
              currentgridrow[1] = 6; 
              if(c >= 0 && c < 3) // first 3 cols
              {// middle-left 3x3 grid
                currentgridcol[0] = 0;
                currentgridcol[1] = 3;
              }
              else if(c >= 3 && c < 6) // second 3 cols
              {// middle-middle 3x3 grid
                currentgridcol[0] = 3;
                currentgridcol[1] = 6;
              }
              else if(c >= 6 && c < 9) // first 3 cols
              {// middle-right 3x3 grid
                currentgridcol[0] = 6;
                currentgridcol[1] = 9;
              }
            }
            else if(r >= 6 && r < 9) // bottom 3 rows
            {
              currentgridrow[0] = 6;
              currentgridrow[1] = 9; 
              if(c >= 0 && c < 3) // first 3 cols
              {// middle-left 3x3 grid
                currentgridcol[0] = 0;
                currentgridcol[1] = 3;
              }
              else if(c >= 3 && c < 6) // second 3 cols
              {// middle-middle 3x3 grid
                currentgridcol[0] = 3;
                currentgridcol[1] = 6;
              }
              else if(c >= 6 && c < 9) // first 3 cols
              {// middle-right 3x3 grid
                currentgridcol[0] = 6;
                currentgridcol[1] = 9;
              }
            }    
            // now that we know what grid we are in and it is set for this loop run the loop
            for(int rowcheck = currentgridrow[0]; rowcheck < currentgridrow[1] ; rowcheck++)
            {
              for(int colcheck = currentgridcol[0]; colcheck < currentgridcol[1]; colcheck++)
              {
                if(rowcheck != r || colcheck != c)
                {
                  // if this space has a number 
                  if(GameBoard[boardindex].Read(rowcheck, colcheck) != 0)
                    GameBoard[boardindex].MakeNotPossible(GameBoard[boardindex].Read(rowcheck, colcheck), r, c);
                }
              }
            }
            ///------------------------------------------------------------------------------------------
            
            //----------------------------------------------------
          }// if the space isn't empty
          else
          {  // make all the numbers not "possible" becuase its already a number
            for(int num = 1; num < 10; num++)
            {
              GameBoard[boardindex].MakeNotPossible(num, r, c);
            }
          }    
        }
      }
      for(int gridr = 0; gridr < 3; gridr++)
      {
        for(int gridc = 0; gridc < 3; gridc++)
        {
          // convert currentgridrow
          switch(gridr)
          {
            case 0: currentgridrow[0] = 0;
                    currentgridrow[1] = 3;
            break;
            case 1: currentgridrow[0] = 3;
                    currentgridrow[1] = 6;
            break;
            case 2: currentgridrow[0] = 6;
                    currentgridrow[1] = 9;
            break;
          }
          switch(gridc)
          {
            case 0: currentgridcol[0] = 0;
                    currentgridcol[1] = 3;
            break;
            case 1: currentgridcol[0] = 3;
                    currentgridcol[1] = 6;
            break;
            case 2: currentgridcol[0] = 6;
                    currentgridcol[1] = 9;
            break;
          }
          // changed to hold a minimum of 3 rows and columns
          int spacespossible[7];
          if(birth == 2) // only use this while generating a number
          {
            for(int numberchecking = 1; numberchecking < 10; numberchecking++)
            {
              spacespossible[0] = 0; 
              // added logic to eliminate solve faster 
              // if a number is restriced to a row or column in a 3x3 grid then the 
              // affected 3x3 grids can eliminate that number on the row or column they share
              for(int r = currentgridrow[0]; r < currentgridrow[1]; r++)
              {
                for(int c = currentgridcol[0]; c < currentgridcol[1]; c++)
                {
                  // if any space in this current grid is possible on the number we are checking 
                  if(GameBoard[boardindex].IsPossible(numberchecking, r, c))
                  {
                    // save the last spot that was true in so if its only one the variable row and col are already saved
                    if(spacespossible[0] == 0)
                    {
                      spacespossible[1] = r;
                      spacespossible[2] = c;
                    }
                    else if(spacespossible[0] == 1)
                    {
                      spacespossible[3] = r;
                      spacespossible[4] = c;
                    }
                    else if(spacespossible[0] == 2)
                    {
                      spacespossible[5] = r;
                      spacespossible[6] = c;
                    }
                    spacespossible[0]++;
                  }
                }
              }
              if(spacespossible[0] == 1)
              {
                // if this is the only space this number can be
                // mark all other numbers not possible
                for(int numberstoeliminate = 1; numberstoeliminate < 10; numberstoeliminate++)
                {
                  // if its not the number we were checking for it can be eliminated 
                  if(numberstoeliminate != numberchecking)
                  {
                    GameBoard[boardindex].MakeNotPossible(numberstoeliminate, spacespossible[1], spacespossible[2]);
                  }
                }
                // then run a loop to eliminate all that number from all other spaces in the row and col
                for(int rowcheck = 0; rowcheck < 9; rowcheck++)
                {
                  // if this isn't the space we are on
                  if(rowcheck != spacespossible[1])
                    GameBoard[boardindex].MakeNotPossible(numberchecking, rowcheck, spacespossible[2]);
                }
                for(int colcheck = 0; colcheck < 9; colcheck++)
                {
                  if(colcheck != spacespossible[2])
                    GameBoard[boardindex].MakeNotPossible(numberchecking, spacespossible[1], colcheck);
                }
              }
              else if(spacespossible[0] == 3 || spacespossible[0] == 2)
              {// if they are on the same row
                if(spacespossible[1] == spacespossible[3])
                {
                  if((spacespossible[0] == 3 && spacespossible[3] == spacespossible[5]) || spacespossible[0] == 2)
                  {
                    // you can eliminate this number from the same row in the other 2 grids
                    switch(gridc)
                    {// top
                      case 0: for(int colcheck = 3; colcheck < 9; colcheck++)
                                GameBoard[boardindex].MakeNotPossible(numberchecking, spacespossible[1], colcheck);
                      break;
                      case 1: for(int colcheck = 0; colcheck < 3; colcheck++)  // middle
                                GameBoard[boardindex].MakeNotPossible(numberchecking, spacespossible[1], colcheck);
                              for(int colcheck = 6; colcheck < 9; colcheck++)
                                GameBoard[boardindex].MakeNotPossible(numberchecking, spacespossible[1], colcheck);
                      break;
                      case 2: for(int colcheck = 0; colcheck < 6; colcheck++) // bottom
                                GameBoard[boardindex].MakeNotPossible(numberchecking, spacespossible[1], colcheck);
                      break;     
                    }
                  }
                }
                if(spacespossible[2] == spacespossible[4])
                {
                  if((spacespossible[0] == 3  && spacespossible[4] == spacespossible[6]) || spacespossible[0] == 2)
                  {
                    // you can eliminate this number from the same row in the other 2 grids
                    switch(gridr)
                    {// top
                      case 0: for(int rowcheck = 3; rowcheck < 9; rowcheck++)
                                GameBoard[boardindex].MakeNotPossible(numberchecking, rowcheck, spacespossible[2]);
                      break;
                      case 1: for(int rowcheck = 0; rowcheck < 3; rowcheck++)  // middle
                                GameBoard[boardindex].MakeNotPossible(numberchecking, rowcheck, spacespossible[2]);
                              for(int rowcheck = 6; rowcheck < 9; rowcheck++)
                                GameBoard[boardindex].MakeNotPossible(numberchecking, rowcheck, spacespossible[2]);
                      break;
                      case 2: for(int rowcheck = 0; rowcheck < 6; rowcheck++) // bottom
                                GameBoard[boardindex].MakeNotPossible(numberchecking, rowcheck, spacespossible[2]);
                      break;     
                    }
                  }
                }
              }
            }
          }
          /// check to see if any two squares in the grid share ONLY two of the same numbes 
          // ie both squares contain only 1 and 5 then one and 5 can be eliminated from all other squares
          // in the row in the column and in the grid
          if(birth == 2) // only run this while generating a puzzle
          {
            for(int r = currentgridrow[0]; r < currentgridrow[1]; r++)
            {
              for(int c = currentgridcol[0]; c < currentgridcol[1]; c++)
              {
                // look to see if the space only has two candidates
                // [0] = the number of numbers possible in the first square at location r, c
                // [1] = the first number it found possible
                // [2] = the second number it found possible
                // [3] = the number of numbers possible in the second square looked for location rowcheck, colcheck
                // [4] = the first number it found possible
                // [5] = the second number it found possible
                int numberfound[6];
                numberfound[0] = 0;
                numberfound[3] = 0;
                for(int a = 1; a < 10; a++)
                {
                  if(GameBoard[boardindex].IsPossible(a, r, c))
                  {
                    if(numberfound[0] == 0)
                      numberfound[1] = a;
                    else if(numberfound[0] == 1)
                      numberfound[2] = a;
                    numberfound[0]++;
                  }
                }
                // if this square only had 2 possible
                /*if(numberfound[0] == 2)
                {
                  //look for another space that only has those two
                  for(int rowcheck = currentgridrow[0]; rowcheck < currentgridrow[1]; rowcheck++)
                  {
                    for(int colcheck = currentgridcol[0]; colcheck < currentgridcol[1]; colcheck++)
                    {
                      // if this isn't the space we already checked
                      if(rowcheck != r || colcheck!= c)
                      {
                        for(int a = 1; a < 10; a++)
                        {
                          if(GameBoard[boardindex].IsPossible(a, rowcheck, colcheck))
                          {
                            if(numberfound[3] == 0)
                              numberfound[4] = a;
                            else if(numberfound[3] == 1)
                              numberfound[5] = a;
                            numberfound[3]++;
                          }
                        }
                        if(numberfound[3] == numberfound[0]) // if they both only have two numbers
                        {
                          // if the numbers they share are the same
                          if(numberfound[1] == numberfound[4] && numberfound[2] == numberfound[5])
                          {
                            // all other squares in this grid can have both those numbers eliminated
                            // another loop to look through the squares
                            for(int rr = currentgridrow[0]; rr < currentgridrow[1]; rr++)
                            {
                              for(int cc = currentgridcol[0]; cc < currentgridcol[1]; cc++)
                              {
                                // if this space isn't either the starting square or the square
                                // that matched these conditions mark both numbers false
                                if((rr != r || cc != c) && (rr != rowcheck || cc != colcheck))
                                {
                                  GameBoard[boardindex].MakeNotPossible(numberfound[4], rr, cc);
                                  GameBoard[boardindex].MakeNotPossible(numberfound[5], rr, cc);
                                }
                              }
                            }
                            // further if these two are on the same row or column you can eliminate the rest
                            // of the row / column
                            if(rowcheck == r)
                            {
                              for(int cc = 0; cc < 9; cc++)
                              {
                                // if this space isn't either of the ones we're using to eliminate mark the numbers false
                                if(cc != c && cc != colcheck)
                                {
                                  GameBoard[boardindex].MakeNotPossible(numberfound[4], r, cc);
                                  GameBoard[boardindex].MakeNotPossible(numberfound[5], r, cc);
                                }
                              }
                            }
                            if(colcheck == c)
                            {
                              for(int rr = 0; rr < 9; rr++)
                              {
                                if(rr != r && rr != rowcheck)
                                {
                                  GameBoard[boardindex].MakeNotPossible(numberfound[4], rr, c);
                                  GameBoard[boardindex].MakeNotPossible(numberfound[5], rr, c);
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }*/
              }
            }
          }
        }
      }
}

bool Sudoku::Solvable(int boardindex)
{
  // declare a int array to set the grid min[0] and max[1] row and col
  // this will be converted based off loop controls to know what grid is being analyzed 
  // and giving these values based off the start and end column and row of that grid
  int currentgridrow[2], currentgridcol[2];
  bool solved = false;
 /// test to see if it can solve a known sudoku
 /*GameBoard[9].Fill(5, 0, 0);
  GameBoard[9].Fill(2, 0, 1);
  GameBoard[9].Fill(6, 0, 4);
  GameBoard[9].Fill(8, 0, 6);
  GameBoard[9].Fill(1, 0, 8);
  GameBoard[9].Fill(1, 1, 0);
  GameBoard[9].Fill(5, 1, 5);
  GameBoard[9].Fill(2, 1, 7);
  GameBoard[9].Fill(9, 2, 4);
  GameBoard[9].Fill(5, 2, 6);
  GameBoard[9].Fill(3, 2, 8);
  GameBoard[9].Fill(8, 3, 3);
  GameBoard[9].Fill(5, 3, 7);
  GameBoard[9].Fill(3, 4, 0);
  GameBoard[9].Fill(1, 4, 2);
  GameBoard[9].Fill(6, 4, 6);
  GameBoard[9].Fill(4, 4, 8);
  GameBoard[9].Fill(8, 5, 1);
  GameBoard[9].Fill(4, 5, 5);
  GameBoard[9].Fill(9, 6, 0);
  GameBoard[9].Fill(7, 6, 2);
  GameBoard[9].Fill(1, 6, 4);
  GameBoard[9].Fill(1, 7, 1);
  GameBoard[9].Fill(7, 7, 3);
  GameBoard[9].Fill(5, 7, 8);
  GameBoard[9].Fill(8, 8, 0);
  GameBoard[9].Fill(5, 8, 2);
  GameBoard[9].Fill(2, 8, 4);
  GameBoard[9].Fill(4, 8, 7);
  GameBoard[9].Fill(7, 8, 8);*/
    for(int timesran = 0; timesran < 100; timesran++)
    {
      MarkSpaces(boardindex);
      int spacespossible[3]; 
      for(int numberchecking = 1; numberchecking < 10; numberchecking++)
      { 
        for(int gridr = 0; gridr < 3; gridr++)
        {
          for(int gridc = 0; gridc < 3; gridc++)
          {         
            //------------Set Loop controls based on grid-------------
            if(gridr == 0) // first 3 rows
            {
              currentgridrow[0] = 0;
              currentgridrow[1] = 3; 
              if(gridc == 0) // first 3 cols
              {// middle-left 3x3 grid
                currentgridcol[0] = 0;
                currentgridcol[1] = 3;
              }
              else if(gridc == 1) // second 3 cols
              {// middle-middle 3x3 grid
                currentgridcol[0] = 3;
                currentgridcol[1] = 6;
              }
              else if(gridc == 2) // first 3 cols
              {// middle-right 3x3 grid
                currentgridcol[0] = 6;
                currentgridcol[1] = 9;
              }
            }
            else if(gridr == 1) // second 3 rows
            {
              currentgridrow[0] = 3;
              currentgridrow[1] = 6; 
              if(gridc == 0) // first 3 cols
              {// middle-left 3x3 grid
                currentgridcol[0] = 0;
                currentgridcol[1] = 3;
              }
              else if(gridc == 1) // second 3 cols
              {// middle-middle 3x3 grid
                currentgridcol[0] = 3;
                currentgridcol[1] = 6;
              }
              else if(gridc == 2) // first 3 cols
              {// middle-right 3x3 grid
                currentgridcol[0] = 6;
                currentgridcol[1] = 9;
              }
            }
            else if(gridr == 2) // bottom 3 rows
            {
              currentgridrow[0] = 6;
              currentgridrow[1] = 9; 
              if(gridc == 0) // first 3 cols
              {// middle-left 3x3 grid
                currentgridcol[0] = 0;
                currentgridcol[1] = 3;
              }
              else if(gridc == 1) // second 3 cols
              {// middle-middle 3x3 grid
                currentgridcol[0] = 3;
                currentgridcol[1] = 6;
              }
              else if(gridc == 2) // first 3 cols
              {// middle-right 3x3 grid
                currentgridcol[0] = 6;
                currentgridcol[1] = 9;
              }
            }
  //-----------------------------------------------------------------------
            spacespossible[0] = 0;
            // loop to controls set to be within the current grid 
            for(int r = currentgridrow[0]; r < currentgridrow[1]; r++)
            {
              for(int c = currentgridcol[0]; c < currentgridcol[1]; c++)
              {
                // if any space in this current grid is possible on the number we are checking 
                if(GameBoard[boardindex].IsPossible(numberchecking, r, c))
                {
                  spacespossible[0]++;
                  spacespossible[1] = r;
                  spacespossible[2] = c;
                }
              }
            }
            if(spacespossible[0] == 1)
              GameBoard[boardindex].Fill(numberchecking, spacespossible[1], spacespossible[2]);
          }
        } 
      }    
      // check to see if it is solved
      solved = true;
      for(int r = 0; r < 9; r++)
      {
        for(int c = 0; c < 9; c++)
        {
          if(GameBoard[boardindex].Read(r, c) == 0)
            solved = false;
        }
      }
      if(solved)
      {
        return true;
      }
    }
    //Next Check to see if any number is only possible in one space the loop will quit after the first number it
    // finds with only one possible space
    // run a loop for every possible number 1 - 9

    
    /// built in debugger for tracking numbers... the code didn't go so well first time I compiled 
    /*char *Rowchar;
      char *Colchar;
      char *Possible;
      switch(6)
      {
        case 3: Rowchar = "row 4"; break;
        case 4: Rowchar = "row 5"; break;
        case 6: Rowchar = "row 7"; break;
      }
      switch(2)
      {
        case 0: Colchar = "col 1"; break;
        case 1: Colchar = "col 2"; break;
        case 2: Colchar = "col 3"; break;
      }
      switch(GameBoard[9].NumberOfPossible(6, 2))
      {
        case 0: Possible = "has 0 possible"; break;
        case 1: Possible = "has 1 possible"; break;
        case 2: Possible = "has 2 possible"; break;
        case 3: Possible = "has 3 possible"; break;
        case 4: Possible = "has 4 possible"; break;
        case 5: Possible = "has 5 possible"; break;
        case 6: Possible = "has 6 possible"; break;
        case 7: Possible = "has 7 possible"; break;
        case 8: Possible = "has 8 possible"; break;
        case 9: Possible = "has 9 possible"; break;    
      }
      MessageBox(NULL, Rowchar, Colchar, MB_OK | MB_ICONEXCLAMATION);
      MessageBox(NULL, Possible, "yea", MB_OK | MB_ICONEXCLAMATION);*/
   return false;       
}

AUX_RGBImageRec *Sudoku::LoadBMP(char *Filename)
{
  FILE *File = NULL;
  if(!Filename)
    return NULL;
  File = fopen(Filename, "r");
  if(File)
  {
    fclose(File);
    return auxDIBImageLoad(Filename);
  }
  return NULL;
}

void Sudoku::Copy(int Copyfromindex, int Copytoindex)
{
  // clear the target
  GameBoard[Copytoindex].Clear();
  for(int r = 0; r < 9; r++)
  {
    for(int c = 0; c < 9; c++)
    {
      GameBoard[Copytoindex].Fill(GameBoard[Copyfromindex].Read(r, c), r, c);
    }
  }
}

int Sudoku::LoadTextures()
{
  int Status = false;
  char *filename;
  AUX_RGBImageRec *TextureImage[numtextures];
  memset(TextureImage, 0, sizeof(void *)*1);
  for(int a = 0; a < numtextures; a++)
  {
    switch(a)
    {
      case 0: filename = "images/blank.bmp"; break;
      case 1: filename = "images/one.bmp"; break;
      case 2: filename = "images/two.bmp"; break;
      case 3: filename = "images/three.bmp"; break;
      case 4: filename = "images/four.bmp"; break;
      case 5: filename = "images/five.bmp"; break;
      case 6: filename = "images/six.bmp"; break;
      case 7: filename = "images/seven.bmp"; break;
      case 8: filename = "images/eight.bmp"; break;
      case 9: filename = "images/nine.bmp"; break;
      case 10: filename = "images/computer.bmp"; break;
      case 11: filename = "images/highlight.bmp"; break;
      case 12: filename = "images/bborder.bmp"; break;
      case 13: filename = "images/numposs.bmp"; break;
      case 14: filename = "images/darkblue.bmp"; break;
      case 15: filename = "images/bluesquiggly.bmp"; break;
      case 16: filename = "images/menua.bmp"; break;
      case 17: filename = "images/load.bmp"; break;
      case 18: filename = "images/save.bmp"; break;
      case 19: filename = "images/continue.bmp"; break;
      case 20: filename = "images/options.bmp"; break;
      case 21: filename = "images/lightblue.bmp"; break;
      case 22: filename = "images/lbluesquiggly.bmp"; break;
      case 23: filename = "images/lightgreen.bmp"; break;
      case 24: filename = "images/lgreensquiggly.bmp"; break;
      case 25: filename = "images/black.bmp"; break;
      case 26: filename = "images/starthing.bmp"; break;
      case 27: filename = "images/prototype.bmp"; break;
    }
    if(TextureImage[a] = LoadBMP(filename))
    {
      Status = TRUE;
    
      glGenTextures(1, &texture[a]);
      glBindTexture(GL_TEXTURE_2D, texture[a]);
      glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[a]->sizeX, TextureImage[a] -> sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[a] ->data); 
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
      gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[a]->sizeX, TextureImage[a]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[a]->data); // ( NEW )
    }
    if(TextureImage[a])
    {
      if(TextureImage[a] -> data)
      free(TextureImage[a] -> data);
      free(TextureImage[a]);
    }
  }
  return Status;
}

void Sudoku::MChangeActive()
{
  if(eventdelay == 0)
  {
    Menu.ChangeActive();
    eventdelay = 50;
  }
}
// sets up a loading texture before the puzzle is generated
void Sudoku::Loading()
{
  Load.SetCenter(0.0f, 0.0f, -3.0f);
  Load.SetSize(2.0f, 2.0f);
  Load.Render(texture[10]);
}

void Sudoku::Reset()
{
  if(eventdelay == 0)
  {
    birth = 0;
    eventdelay = 50;
  }
}

void Sudoku::Handle()
{
 // check it this is the first time sudoku has been handled.. if so load textures and display loading screen
  if(birth == 0)
  {
    if(!LoadTextures())
      MessageBox(NULL, "Failed to load Textures", "load error", MB_OK | MB_ICONEXCLAMATION);
    birth++;
  }
  else if(birth == 1)
  {
    Loading();
    birth++;
  }
  // if this is the second time and Loading screen has been displayed 
  else if(birth == 2)
  {
    for(int a = 0; a < 10; a++)
      GameBoard[a].Clear();
    GeneratePuzzle();
    birth++;
  }
  else
  {
    // draw the moving background first
    Smovingbackground.Handle(texture[textureindex], texture[textureindex+1]);
    if(!Menu.OptionActive())
    {
      for(int r = 0; r < 9; r++)
      {
        for(int c = 0; c < 9; c++)
        {
          GameBoard[8].Render(r, c, (texture[GameBoard[8].Read(r, c)]));
        }
      }
      // render's the highlight onto the board
      Highlight.Render(texture[11]);
      // start a loop to run through all numbers
      if(difficulty == 0)// beginner
      {
        MarkSpaces(8); // only mark for the user in beginner mode
      }
      // finds the row and column of the currend highlight square
      // control what location on the screen the number is rendered too.. allowing for all 9 to be viewed and 
      // not in a straight line down
      int Xcontrol, Ycontrol;
      Xcontrol = 7; 
      Ycontrol = 3;
      FindHighlight();
      
      // render's the numbers possible title on the board
      NumbersPossibleTitle.Render(texture[13]);
      for(int a = 1; a < 10; a++)
      {
        // make sure the spaces have been marked.
        if(GameBoard[8].IsPossible(a, highlightr, highlightc))
        {
          NumberPossible.SetCenter(Xcontrol, Ycontrol, -14.9999f);
          NumberPossible.Render(texture[a]);
          Ycontrol -= 1;
          if(Ycontrol < -1)
          {
            Ycontrol = 3;
            Xcontrol = 8;
          }
        }
      }
      for(int gridr = 0; gridr < 3; gridr++)
      {
        for(int gridc = 0; gridc < 3; gridc ++)
        {
          // even though these values are floats they are currently all whole numbers so the temps are ints
          int tempx, tempy;
          switch(gridr)
          {
            case 0: tempy = 3; break;
            case 1: tempy = 0; break;
            case 2: tempy = -3; break;
          }
          switch(gridc)
          {
            case 0: tempx = -3; break;
            case 1: tempx = 0; break;
            case 2: tempx = 3; break;
          }
          Darklines.SetCenter((GLfloat)tempx, (GLfloat)tempy, -14.9999f);
          Darklines.Render(texture[12]);
        }
      }
    }
  }
  // handle the menu
  Menu.Handle(texture[16], texture[17], texture[18], texture[19], texture[20], texture[27]);
  if(eventdelay > 0)
    eventdelay--;
  bool correct = true;
  for(int r = 0; r < 9; r++)
  {
    for(int c = 0; c < 9; c++)
    {
      if(GameBoard[9].Read(r, c) != GameBoard[8].Read(r, c))
        correct = false;
    }
  }
  if(GameBoard[8].Full() && !beat && !failed)
  {
    if(correct)
    {
      MessageBox(NULL, "Congratulations!! You must be super smart. Press Z after you close this box to start a new puzzle", "Solved", MB_OK | MB_ICONEXCLAMATION);
      beat = true;
    }
    else
    {
      MessageBox(NULL, "Sorry you missed something.  You might want to go back or start a new puzzle.", "Invalid", MB_OK | MB_ICONEXCLAMATION);
      failed = true;
    }
  }
}

//----------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//----------------------------Beginning of Board Definitions ----------------------
Board::Board()
{
  GLfloat xpos = -4.0f;
  GLfloat ypos = 4.0f;
  GLfloat zpos = - 15.0f;
  for(int r = 0; r < 9; r++)
  {
    for(int c = 0; c < 9; c++)
    {
      Space[r][c].SetCenter(xpos, ypos, zpos);
      xpos += 1.0f;
    }
    xpos = -4.0f;
    ypos -= 1.0f;
  }
}

Board::~Board()
{
}

bool Board::Permanent(int r, int c)
{
  return Space[r][c].Permanent();
}

void Board::MakePermanent(int r, int c)
{
  Space[r][c].MakePermanent();
}
// fill the entire datamap with 0s
void Board::Clear()
{
  for(int r = 0; r < 9; r++)
  {
    for(int c = 0; c < 9; c++)
    {
      datamap[r][c] = 0;
      Space[r][c].Reset();
    }
  }
}
bool Board::Full()
{
  // assume its full and prove it wrong
  bool full = true;
  // run a loop to check the entire board
  for(int r = 0; r < 9; r++)
  {
    for(int c = 0; c < 9; c++)
    {
      if(datamap[r][c] == 0)
        full = false;
    }
  }
  // if it was proven wrong return false .. otherwise it returns true
  return full;
}

// the definition of the function to pass Suduko Generators request to make a Space number not possible
void Board::MakeNotPossible(int number, int row, int col)
{
  Space[row][col].MakeNotPossible(number);
}
// definition of the function to make a number possble... used for user mark mode
void Board::MakePossible(int number, int row, int col)
{
  Space[row][col].MakePossible(number);
}

// fill board with a given number at row, column
void Board::Fill(int number, int row, int column)
{
  datamap[row][column] = number;
  // if the number isn't 0 then this space is a concrete number
  if(number != 0)
  {
    // loop to make take all possible boolean away when the number has been made concrete or "absolute"
    for(int turnfalse = 1; turnfalse < 10; turnfalse++)
    {
      Space[row][column].MakeNotPossible(turnfalse);
    }
  }
}
// return int value of datamap[r][c];
int Board::Read(int row, int column)
{
  return datamap[row][column];
}

void Board::Render(int row, int column, GLuint spacetexture)
{
  Space[row][column].Render(spacetexture);
}
// definition of pass of numberofpossible from child space to parent sudoku
int Board::NumberOfPossible(int r, int c)
{
  return Space[r][c].NumberOfPossible();
}
// definition of passing if a given number is possible from child space to parent sudoku
bool Board::IsPossible(int numbercheck, int r, int c)
{
  return Space[r][c].IsPossible(numbercheck);
}


//----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
//-----------------------------Beginning of Boardspace definitions ------------------------------------------

BoardSpace::BoardSpace()
{
  centerpoint[0] = 0.0f;
  centerpoint[1] = 0.0f;
  centerpoint[2] = 0.0f;
  width = 1.0f;
  height = 1.0f;
  bottomleft[0] = -(width/2);
  bottomleft[1] = -(height/2);
  bottomright[0] = width/2;
  bottomright[1] = -(height/2);
  topright[0] = width/2;
  topright[1] = height/2;
  topleft[0] = -(width/2);
  topleft[1] = height/2;
  for(int a = 0; a < 9; a++)
    possible[a] = true;
  numberofpossible = 9;
  globalzrotcontrol = 0.0f;
  localzrotcontrol = 0.0f;
  globalrotationaxis[0] = centerpoint[0];
  globalrotationaxis[1] = centerpoint[1];
  globalrotationaxis[2] = centerpoint[2];
  menu = false;
  active = false;
  textopleft[0] = 0.0f;
  textopleft[1] = 1.0f;
  texbottomright[0] = 1.0f;
  texbottomright[1] = 0.0f;
  texwidth = 1.0f;
  texheight = 1.0f;
  chosen = false;
  permanent = false;
}

BoardSpace::~BoardSpace()
{
}

void BoardSpace::MakePermanent()
{
  permanent = true;
}

bool BoardSpace::Permanent()
{
  return permanent;
}

bool BoardSpace::Chosen()
{
  return chosen;
}

void BoardSpace::ChangeChosen()
{
  chosen = !chosen;
}

void BoardSpace::ChangeTexCoords(GLfloat topleftx, GLfloat toplefty, GLfloat width, GLfloat height)
{
  textopleft[0] = topleftx;
  textopleft[1] = toplefty;
  texwidth = width;
  texheight = height;
  texbottomright[0] = topleftx + width;
  texbottomright[1] = toplefty - height;
}

bool BoardSpace::Active()
{
  return active;
}

void BoardSpace::ChangeActive()
{
  active = !active;
}

void BoardSpace::SetMenu()
{
  menu = true;
}

void BoardSpace::GlobalRotateZ(GLfloat angle)
{
  globalzrotcontrol += angle;
}

void BoardSpace::LocalRotateZ(GLfloat angle)
{
  localzrotcontrol -= angle;
}

void BoardSpace::GiveGlobalAxis(GLfloat x, GLfloat y, GLfloat z)
{
  globalrotationaxis[0] = x;
  globalrotationaxis[1] = y;
  globalrotationaxis[2] = z;
}

void BoardSpace::SetSize(GLfloat w, GLfloat h)
{
  width = w;
  height = h;
  bottomleft[0] = -(width/2);
  bottomleft[1] = -(height/2);
  bottomright[0] = width/2;
  bottomright[1] = -(height/2);
  topright[0] = width/2;
  topright[1] = height/2;
  topleft[0] = -(width/2);
  topleft[1] = height/2;
}
// define the pass from child space to parent board .... of how many numbers it can possibly be
int BoardSpace::NumberOfPossible()
{
  return numberofpossible;
}

void BoardSpace::MakePossible(int number)
{
  number -= 1; // make it compatible w/ boolean
  possible[number] = !possible[number]; // changed to work opposite so you can unmark a number too
}

void BoardSpace::MakeNotPossible(int number)
{
  // this makes the number compatible with the boolean index 0- 8 and the actual number 1- 9;
  number -= 1;
  // if that position is true make it false
  if(possible[number])
  {
    possible[number] = false;
    numberofpossible -= 1;
  }
}
 
void BoardSpace::Render(GLuint spacetexture)
{
  if(globalzrotcontrol >= 360)
    globalzrotcontrol -= 360;
  else if(globalzrotcontrol < 0)
    globalzrotcontrol += 360;
  glLoadIdentity();
  glPushMatrix();
  glPushAttrib(GL_CURRENT_BIT);
  if(menu)// create a different color for the selected menu box
  {
    // conditions to tell a menu box it is selected so we change its color and set it to active
    // first box... aka top box    centerpoint (y) axis defines that it is the top menu item
    if((globalzrotcontrol < 25.0f || globalzrotcontrol > 340.0f) && centerpoint[1] > .8)   
    {
      glColor3f(0.0f, 0.0f, 1.0f);
      active = true;
    }
    // second box in clockwise order aka load box
    else if((globalzrotcontrol > 29.0f && globalzrotcontrol < 90.0f) && centerpoint[0] > -7.1f)
    {
      glColor3f(0.0f, 0.0f, 1.0f);
      active = true;
    }
    // third box in clockwise order aka save box
    else if((globalzrotcontrol > 92.0f && globalzrotcontrol < 160.0f) && centerpoint[0] > -8.0f && centerpoint[1] < 0.0f)
    {
      glColor3f(0.0f, 0.0f, 1.0f);
      active = true;
    }
    // fourth box in clockwise order aka continue box
    else if(globalzrotcontrol > 160.0f && globalzrotcontrol < 250.0f && centerpoint[0] < -8.0f && centerpoint[1] < 0.0f)
    {
      glColor3f(0.0f, 0.0f, 1.0f);
      active = true;
    }
    // fifth box in clockwise order aka options box
    else if(globalzrotcontrol > 250.0f && globalzrotcontrol < 340.0f && centerpoint[0] < -8.9)
    {
      glColor3f(0.0f, 0.0f, 1.0f);
      active = true;
    }
    else
      active = false;
  }
  //option menu items become "chosen" when user input is pressed up, down, left, or right
  if(chosen && !menu) // so if its an option menu item and its active
  {
    glColor3f(0.0f, 0.3f, 0.3f);
  }
  glTranslatef(globalrotationaxis[0], globalrotationaxis[1], globalrotationaxis[2]);
  glRotatef(globalzrotcontrol, 0.0f, 0.0f, 1.0f);
  glTranslatef(-globalrotationaxis[0], -globalrotationaxis[1], -globalrotationaxis[2]); // get back to point of origin
  glTranslatef(centerpoint[0], centerpoint[1], centerpoint[2]);
  glRotatef(localzrotcontrol, 0.0f, 0.0f, 1.0f);
  glBindTexture(GL_TEXTURE_2D, spacetexture);
  glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(textopleft[0], texbottomright[1]); glVertex3f(bottomleft[0], bottomleft[1], 0.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(texbottomright[0], texbottomright[1]); glVertex3f(bottomright[0], bottomright[1], 0.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(texbottomright[0], textopleft[1]); glVertex3f(topright[0], topright[1], 0.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(textopleft[0], textopleft[1]); glVertex3f(topleft[0], topleft[1], 0.0f);
  glEnd();
  glPopAttrib();
  glPopMatrix();
}
        // set the square's centerpoint
void BoardSpace::SetCenter(GLfloat x, GLfloat y, GLfloat z)
{
  centerpoint[0] = x;
  centerpoint[1] = y;
  centerpoint[2] = z;
}

// define pass of a given number possibility in a square to its parent board
bool BoardSpace::IsPossible(int numbercheck)
{
  // make numbercheck 1-9 compatible with booean 0- 8
  numbercheck -= 1;
  return possible[numbercheck];
}
// reset the space
void BoardSpace::Reset()
{
  for(int a = 0; a < 9; a++)
    possible[a] = true;
  numberofpossible = 9;
  permanent = false;
}

GLfloat BoardSpace::CenterX()
{
  return centerpoint[0];
}

GLfloat BoardSpace::CenterY()
{
  return centerpoint[1];
}

GLfloat BoardSpace::CenterZ()
{
  return centerpoint[2];
}

//----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
//-----------------------------Beginning of SeeThroughSquare definitions ------------------------------------------
SeeThroughSquare::SeeThroughSquare()
{
  // set default position as the top left of the board
  centerpoint[0] = -4.0f;
  centerpoint[1] = 4.0f;
  centerpoint[2] = 14.9999f;
  width = 1.0f;
  height = 1.0f;
  // default bordersize is .02
  bordersize = .02f;
}

SeeThroughSquare::~SeeThroughSquare()
{
}
// change the border size to a new value
void SeeThroughSquare::SetBorderSize(GLfloat newsize)
{
  width += (newsize - bordersize);
  height += (newsize - bordersize);
  bordersize = newsize;
  SetEdgeCenters();
}
// this is needed to process everytime the center of SeeThroughSquare is changed.
void SeeThroughSquare::SetEdgeCenters()
{
  // this is done based off seethroughsquare's centerpoint and its mathematical relation to its edges
  TopEdge.SetCenter(centerpoint[0], centerpoint[1] +((height/2)-bordersize), centerpoint[2]);
  BottomEdge.SetCenter(centerpoint[0], centerpoint[1] -((height/2)-bordersize), centerpoint[2]);
  RightEdge.SetCenter(centerpoint[0]+((width/2)-bordersize), centerpoint[1], centerpoint[2]);
  LeftEdge.SetCenter(centerpoint[0]-((width/2)-bordersize), centerpoint[1], centerpoint[2]);
  // also set the sizes in case the size of the class changed
  TopEdge.SetSize(width, bordersize);
  BottomEdge.SetSize(width, bordersize);
  RightEdge.SetSize(bordersize, height);
  LeftEdge.SetSize(bordersize, height);
}
// return center x coordinate 
GLfloat SeeThroughSquare::CenterX()
{
  return centerpoint[0];
}
// return center y coordinate
GLfloat SeeThroughSquare::CenterY()
{
  return centerpoint[1];
}
// set the values of the class's center and change the edges based off this new value;
void SeeThroughSquare::SetCenter(GLfloat x, GLfloat y, GLfloat z)
{
  centerpoint[0] = x;
  centerpoint[1] = y;
  centerpoint[2] = z;
  SetEdgeCenters();
}

void SeeThroughSquare::Render(GLuint bordertexture)
{
  TopEdge.Render(bordertexture);
  RightEdge.Render(bordertexture);
  BottomEdge.Render(bordertexture);
  LeftEdge.Render(bordertexture);
}

void SeeThroughSquare::SetSize(GLfloat w, GLfloat h)
{
  width = w;
  height = h;
    // set the size of each of this squares edges
  SetEdgeCenters();
}

/// --------------------------------------------------------------------------------------
// --------------------------- Beginning of Moving Backgrounds Defintions ----------------
MovingBackground::MovingBackground()
{
  // set the Stationary size and location
  StationaryBG.SetSize(30.0f, 20.0f);
  StationaryBG.SetCenter(0.0f, 0.0f, - 16.0f);
  // initiate the moving parts default value;
  for(int a = 0; a < 50; a++)
  {
    // int to generate random locations for the object  [0] = x coordinate [1] = y coordinate
    // using int here makes for a very finite number of positions because the centerpoint is a float
    int location[2];
    MovingObjects[a].SetSize(0.5f, 0.5f);
    // random number 0 - 20;
    location[0] = rand()%21;
    // random number 0 - 20;
    location[1] = rand()%21;
    // make the range -10 to 10
    location[0] -= 10;
    // make the range -10 to 10
    location[1] -= 10;
    // set the object to that random location and a tiny bit in front of the stationary background
    MovingObjects[a].SetCenter((GLfloat) location[0], (GLfloat) location[1], -15.9999f); 
  }
  // set default behavior choice to 1
  BehaviorChoice = 1;      
  for(int x = 0; x < 2; x++)
  {
    horizontal[x] = false;
    vertical[x] = false;
    localrot[x] = false;
    globalrot[x] = false;
  }
}

MovingBackground::~MovingBackground()
{
}

bool MovingBackground::BehaviorSettings(int behaviorchoice)
{
  switch(behaviorchoice)
  {
    case 0: return horizontal[0]; break;
    case 1: return vertical[0]; break;
    case 2: return localrot[0]; break;
    case 3: return globalrot[0]; break;
  }
}

bool MovingBackground::BehaviorDirection(int behaviorchoice)
{
  switch(behaviorchoice)
  {
    case 0: return horizontal[1]; break;
    case 1: return vertical[1]; break;
    case 2: return localrot[1]; break;
    case 3: return globalrot[1]; break;
  }
}

void MovingBackground::ObjectBehavior()
{
    if(vertical[0] && vertical[1])// true and down
    { 
      //apply behavior to all objects
      for(int a = 0; a < 50; a++)
      {
        if(MovingObjects[a].CenterY() > -20)
          MovingObjects[a].SetCenter(MovingObjects[a].CenterX(), (MovingObjects[a].CenterY()-.01), -15.9999f);
        else
          MovingObjects[a].SetCenter(MovingObjects[a].CenterX(), (MovingObjects[a].CenterY()+30), -15.9999f);    
      }
    }
    if(vertical[0] && !vertical[1]) // true and up
    { 
      //apply behavior to all objects
      for(int a = 0; a < 50; a++)
      {
        if(MovingObjects[a].CenterY() < 20)
          MovingObjects[a].SetCenter(MovingObjects[a].CenterX(), (MovingObjects[a].CenterY()+.01), -15.9999f);
        else
          MovingObjects[a].SetCenter(MovingObjects[a].CenterX(), (MovingObjects[a].CenterY()-30), -15.9999f);    
      }
    }
    if(horizontal[0] && !horizontal[1])
    { 
      //apply behavior to all objects
      for(int a = 0; a < 50; a++)
      {
        if(MovingObjects[a].CenterX() > -20)
          MovingObjects[a].SetCenter((MovingObjects[a].CenterX()-.01), MovingObjects[a].CenterY(), -15.9999f);
        else
          MovingObjects[a].SetCenter((MovingObjects[a].CenterX()+30), MovingObjects[a].CenterY(), -15.9999f);    
      }
    }
    if(horizontal[0] && horizontal[1])
    {
      //apply behavior to all objects
      for(int a = 0; a < 50; a++)
      {
        if(MovingObjects[a].CenterX() < 20)
          MovingObjects[a].SetCenter((MovingObjects[a].CenterX()+.01), MovingObjects[a].CenterY(), -15.9999f);
        else
          MovingObjects[a].SetCenter((MovingObjects[a].CenterX()-30), MovingObjects[a].CenterY(), -15.9999f);    
      }
    }
    if(globalrot[0] && globalrot[1])
    {
      for(int a = 0; a < 50; a++)
      {
        MovingObjects[a].GiveGlobalAxis(0.0f, 0.0f, MovingObjects[a].CenterZ());
        MovingObjects[a].GlobalRotateZ(-.1);
      }
    }
    if(globalrot[0] && !globalrot[1])
    {
      for(int a = 0; a < 50; a++)
      {
        MovingObjects[a].GiveGlobalAxis(0.0f, 0.0f, MovingObjects[a].CenterZ());
        MovingObjects[a].GlobalRotateZ(.1);
      }
    }
    if(localrot[0] && !localrot[1])
    {
      for(int a = 0; a < 50; a++)
      {
        MovingObjects[a].LocalRotateZ(-.1);
      }
    }
    if(localrot[0] && localrot[1])
    {
      for(int a = 0; a < 50; a++)
      {
        MovingObjects[a].LocalRotateZ(.1);
      }
    }       
}

void MovingBackground::ChangeBehavior(int behaviortochange, int direction)
{
  switch(behaviortochange)
  {
    case 0: horizontal[0] = true;  
            if(direction == 1)
              horizontal[1] = true;
            else
              horizontal[1] = false;
    break;
    case 1: vertical[0] = true; 
            if(direction == 1)
              vertical[1] = true;
            else
              vertical[1] = false;
    break;
    case 2: localrot[0] = true; 
            if(direction == 1)
              localrot[1] = true;
            else
              localrot[1] = false;
    break;
    case 3: globalrot[0] = true; 
            if(direction == 1)
              globalrot[1] = true;
            else
              globalrot[1] = false;
    break;
  }
}

void MovingBackground::Handle(GLuint stationarytexture, GLuint movingtexture)
{
  ObjectBehavior(); 
  StationaryBG.Render(stationarytexture);
  for(int a = 0; a < 50; a++)
  {
    MovingObjects[a].Render(movingtexture);
  }
}

/// ------------------------- END OF MOVING BACKGROUNDS DEFINITIONS ----------------------

// ---------------------------------------------------------------------------------------
// --------------------------Beginning of Menu Definitions -------------------------------
// constructor
Smenu::Smenu()
{
  optionactive = false;
  active = false;
  // going to try and handle all 5 seperately first
  centerpoint[0] = -8.0f;
  centerpoint[1] = 0.0f; 
  centerpoint[2] = -14.0f;
  // menu picture
  MenuItems[0].SetSize(1.0f, 1.0f);
  MenuItems[0].SetCenter(centerpoint[0], (centerpoint[1] + 1.0f), centerpoint[2]);
  MenuItems[0].SetMenu();
  // loadgame 
  MenuItems[1].SetSize(1.0f, 1.0f);
  MenuItems[1].SetCenter((centerpoint[0]+ 1.0f), centerpoint[1]+.3, centerpoint[2]);
  MenuItems[1].SetMenu();
  // savegame
  MenuItems[2].SetSize(1.0f, 1.0f);
  MenuItems[2].SetCenter((centerpoint[0]+ 0.7f), (centerpoint[1] - 1.0f), centerpoint[2]);
  MenuItems[2].SetMenu();
  // continue
  MenuItems[3].SetSize(1.0f, 1.0f);
  MenuItems[3].SetCenter((centerpoint[0]- 0.7f), (centerpoint[1] - 1.0f), centerpoint[2]);
  MenuItems[3].SetMenu();
  // options
  MenuItems[4].SetSize(1.0f, 1.0f);
  MenuItems[4].SetCenter((centerpoint[0]- 1.0f), centerpoint[1]+.3, centerpoint[2]);
  MenuItems[4].SetMenu();
  // set choice to default aka no choice made
  int timesran = 0;
  const GLfloat conversionratio = 0.00098f; // constant for pixel to texture coordinates conversion
                                            // ratio on a 1024x 1024 bmp
  GLfloat w = 210.0f * conversionratio;
  GLfloat h = 80.0f * conversionratio;
  for(int r = 0; r < 7; r++)
  {
    int roddoperator;
    switch(r)
    {
      case 0: roddoperator = 1; break;
      case 1: roddoperator = 3; break;
      case 2: roddoperator = 5; break;
      case 3: roddoperator = 7; break;
      case 4: roddoperator = 9; break;
      case 5: roddoperator = 11; break;
      case 6: roddoperator = 13; break;
    }
    for(int c = 0; c < 4; c++)
    {
      int coddoperator;
      switch(c)
      {
        case 0: coddoperator = 1; break;
        case 1: coddoperator = 3; break;
        case 2: coddoperator = 5; break;
        case 3: coddoperator = 7; break;
      }
      GLfloat topleftx = (((GLfloat)c*210.0f)+(GLfloat)coddoperator)*conversionratio;
      GLfloat toplefty = 1.0f-((((GLfloat)r*80.0f)+(GLfloat)roddoperator)*conversionratio);
      OptionMenuItems[timesran].ChangeTexCoords(topleftx, toplefty, w, h);
      OptionMenuItems[timesran].SetSize(2.625f, 1.0f);
      timesran++;
    }
  }
  // set the texture coords of the non uniform grid items
  // calibrate item
  w = 296.0f * conversionratio;   
  h = 163.0f * conversionratio;
  GLfloat topleftx = conversionratio;
  GLfloat toplefty = 1.0f-(575*conversionratio);
  OptionMenuItems[28].ChangeTexCoords(topleftx, toplefty, w, h);
  OptionMenuItems[28].SetSize(4.0f, 2.0f);
  // beginner description item width is the same so not redefined as is toplefty
  h = 198.0f * conversionratio;
  topleftx = 299.0f*conversionratio;
  OptionMenuItems[29].ChangeTexCoords(topleftx, toplefty, w, h);
  OptionMenuItems[29].SetSize(4.0f, 2.0f);
  //intermediate description 
  h = 146.0f * conversionratio;
  // width is the same as above
  topleftx = conversionratio;
  toplefty = 1.0f-(740.0f *conversionratio);
  OptionMenuItems[30].ChangeTexCoords(topleftx, toplefty, w, h);
  OptionMenuItems[30].SetSize(4.0f, 2.0f);
  // advanced description
  h = 130.0f* conversionratio;
  // width is the same
  topleftx = 299.0f*conversionratio;
  toplefty = 1.0f-(775*conversionratio);
  OptionMenuItems[31].ChangeTexCoords(topleftx, toplefty, w, h);
  OptionMenuItems[31].SetSize(4.0f, 2.0f);
  // numbers for x-pert search mode
  w = 93 *conversionratio;
  h = 80 *conversionratio;
  // h and w will be constant for this part
  // 23  
  topleftx = 597*conversionratio; // this will be consistent for the next 3 objects
  toplefty = 1.0f-(575.0f*conversionratio);
  OptionMenuItems[32].ChangeTexCoords(topleftx, toplefty, w, h);
  OptionMenuItems[32].SetSize(1.0f, 1.0f);
  // 24
  toplefty = 1.0f-(657.0f*conversionratio);
  OptionMenuItems[33].SetSize(1.0f, 1.0f);
  OptionMenuItems[33].ChangeTexCoords(topleftx, toplefty, w, h);
  // 25
  toplefty = 1.0f-(739.0f*conversionratio);
  OptionMenuItems[34].SetSize(1.0f, 1.0f);
  OptionMenuItems[34].ChangeTexCoords(topleftx, toplefty, w, h);
  //26
  topleftx = 692*conversionratio; // stays the same for the next 3 objects
  toplefty = 1.0f-(575.0f*conversionratio);
  OptionMenuItems[35].SetSize(1.0f, 1.0f);
  OptionMenuItems[35].ChangeTexCoords(topleftx, toplefty, w, h);
  //27
  toplefty = 1.0f-(657.0f*conversionratio);
  OptionMenuItems[36].SetSize(1.0f, 1.0f);
  OptionMenuItems[36].ChangeTexCoords(topleftx, toplefty, w, h);
  //28
  toplefty = 1.0f-(739.0f*conversionratio);
  OptionMenuItems[37].SetSize(1.0f, 1.0f);
  OptionMenuItems[37].ChangeTexCoords(topleftx, toplefty, w, h); 
  GLfloat start = -5.0f;
  OptionMenuItems[0].SetCenter(start, 3.0f, -10.0f); // options
  OptionMenuItems[4].SetCenter(start, 2.0f, -10.0f); // change difficulty
  OptionMenuItems[8].SetCenter(start, 1.0f, -10.0f); // change background
  OptionMenuItems[12].SetCenter(start, 0.0f, -10.0f); // calibrate speed
  OptionMenuItems[2].SetCenter((start+2.625f), 3.0f, -10.0f); // beginner
  OptionMenuItems[6].SetCenter((start+2.625f), 2.0f, -10.0f); // intermediate
  OptionMenuItems[10].SetCenter((start+2.625f), 1.0f, -10.0f); // advanced
  OptionMenuItems[14].SetCenter((start+2.625f), 0.0f, -10.0f); // x - pert
  OptionMenuItems[16].SetCenter((start+2.625f), 3.0f, -10.0f); // color
  OptionMenuItems[20].SetCenter((start+2.625f), 2.0f, -10.0f); // behavior
  OptionMenuItems[17].SetCenter((start+(2.625f*2)), 3.0f, -10.0f); // darkblue
  OptionMenuItems[21].SetCenter((start+(2.625f*2)), 2.0f, -10.0f); // lightblue
  OptionMenuItems[25].SetCenter((start+(2.625f*2)), 1.0f, -10.0f); // lightgreen
  OptionMenuItems[22].SetCenter((start+(2.625f*2)), 0.0f, -10.0f); // black
  OptionMenuItems[18].SetCenter((start+(2.625f*2)), 3.0f, -10.0f); // direction
  OptionMenuItems[24].SetCenter((start+(2.625f*2)), 2.0f, -10.0f); // rotation
  OptionMenuItems[3].SetCenter((start+(2.625f*3)), 3.0f, -10.0f);  // moveright
  OptionMenuItems[7].SetCenter((start+(2.625f*3)), 2.0f, -10.0f);  // moveleft
  OptionMenuItems[11].SetCenter((start+(2.625f*3)), 1.0f, -10.0f); // moveup
  OptionMenuItems[15].SetCenter((start+(2.625f*3)), 0.0f, -10.0f); // movedown
  OptionMenuItems[19].SetCenter((start+(2.625f*3)), 3.0f, -10.0f); // local
  OptionMenuItems[23].SetCenter((start+(2.625f*3)), 2.0f, -10.0f); // global
  OptionMenuItems[26].SetCenter((start+(2.625f*4)), 3.0f, -10.0f); // right
  OptionMenuItems[27].SetCenter((start+(2.625f*4)), 2.0f, -10.0f); // left                                                 
  OptionMenuItems[29].SetCenter((start+(2.625f*3)), 1.0f, -10.0f); // beginner description
  OptionMenuItems[30].SetCenter((start+(2.625f*3)), 1.0f, -10.0f); // intermediate description
  OptionMenuItems[31].SetCenter((start+(2.625f*3)), 1.0f, -10.0f); // advanced description
  OptionMenuItems[13].SetCenter((start+(2.625*2)), 0.0f, -10.0f);  // number of hints:
  OptionMenuItems[32].SetCenter((start+(2.625*2)+((2.625/2)+.5f)), 2.0f, -10.0f); // 23
  OptionMenuItems[33].SetCenter((start+(2.625*2)+((2.625/2)+.5f)), 1.0f, -10.0f); // 24
  OptionMenuItems[34].SetCenter((start+(2.625*2)+((2.625/2)+.5f)), 0.0f, -10.0f); // 25
  OptionMenuItems[35].SetCenter((start+(2.625*2)+((2.625/2)+1.5f)), 2.0f, -10.0f); // 26
  OptionMenuItems[36].SetCenter((start+(2.625*2)+((2.625/2)+1.5f)), 1.0f, -10.0f); // 27
  OptionMenuItems[37].SetCenter((start+(2.625*2)+((2.625/2)+1.5f)), 0.0f, -10.0f); // 28
} 

  
Smenu::~Smenu()
{
}

void Smenu::Rotate(int direction)
{
  for(int a = 0; a < 5; a++)
  {
    switch(direction)
    {
      case 0:       MenuItems[a].GiveGlobalAxis(centerpoint[0], centerpoint[1], centerpoint[2]);
                    MenuItems[a].GlobalRotateZ(-8.0f);
                    MenuItems[a].LocalRotateZ(-8.0f);
      break;
      case 1:       MenuItems[a].GiveGlobalAxis(centerpoint[0], centerpoint[1], centerpoint[2]);
                    MenuItems[a].GlobalRotateZ(8.0f);
                    MenuItems[a].LocalRotateZ(8.0f);
      break;
    }
  }  
}

bool Smenu::Active()
{
  return active;
}

void Smenu::Handle(GLuint menutexture,
                   GLuint loadtexture,
                   GLuint savetexture,
                   GLuint continuetexture,
                   GLuint optiontexture,
                   GLuint suboptiontexture)
{
  GLuint texturetouse;
  if(active && !optionactive)
  {
    for(int a = 0; a < 5; a++)
    {
      switch(a)
      {
        case 0: texturetouse = menutexture; break;
        case 1: texturetouse = loadtexture; break;
        case 2: texturetouse = savetexture; break;
        case 3: texturetouse = continuetexture; break;
        case 4: texturetouse = optiontexture; break;
      }
      MenuItems[a].Render(texturetouse);
    }
  }
  if(optionactive)
  {
    for(int a = 0; a < 38; a++)
    {
      if(OptionMenuItems[a].Active())
      {
        OptionMenuItems[a].Render(suboptiontexture);
      }
    }
  }
}

int Smenu::Rotation()
{
  return rotation;
}

void Smenu::ResetOptionMenu()
{
  // loop that will run 38 times
  for(int a = 0; a < 38; a++)
  {
    if(OptionMenuItems[a].Active())// if the current item is active
    {
      OptionMenuItems[a].ChangeActive(); // turn it false
      // otherwise its already false so no change
    }
    if(OptionMenuItems[a].Chosen())
    {
      OptionMenuItems[a].ChangeChosen();
    }
  }
}

int Smenu::MakeSelection()
{
  int selection = 0;
  // load game
  // check what menu item is highlighted
  // optionactive is going to go into a bigger menu with different event controls
  if(!optionactive)
  {
    if(MenuItems[0].Active())
      selection = 0;
    else if(MenuItems[1].Active())
      selection = 1;
    else if(MenuItems[2].Active())
      selection = 2;
    else if(MenuItems[3].Active())
      selection = 3;
    else if(MenuItems[4].Active())
    {
      selection = 4;
      optionactive = true;
      OptionMenuItems[0].ChangeActive();  
      OptionMenuItems[4].ChangeActive();
      OptionMenuItems[8].ChangeActive();
      OptionMenuItems[12].ChangeActive();
      OptionMenuItems[0].ChangeChosen(); // set top box as default chosen
    }
  }
  else
  { // probably a better way to do this
    for(int x = 0; x < 38; x++)
    {
      if(OptionMenuItems[x].Chosen())
      {
        selection = x+5; // since 0 - 4 are already used in main menu
        ResetOptionMenu();
        optionactive = false;
        active = false;
      }
    }
  }
  return selection;
}
// handles navigation through the options menu
void Smenu::MoveChosen(int direction)
{
  if(OptionMenuItems[0].Chosen()) // if its still at default
  {
    if(direction == 3) // if the movement was down
    {
      OptionMenuItems[0].ChangeChosen();
      OptionMenuItems[4].ChangeChosen();
    }
  }
  else if(OptionMenuItems[4].Chosen()) // second item change difficulty
  {
    switch(direction)
    {
      case 1: OptionMenuItems[4].ChangeChosen();
              OptionMenuItems[0].ChangeChosen();
      break;
      case 2: OptionMenuItems[4].ChangeChosen();
              OptionMenuItems[2].ChangeChosen();
              OptionMenuItems[2].ChangeActive();
              OptionMenuItems[29].ChangeActive();
              OptionMenuItems[6].ChangeActive();
              OptionMenuItems[10].ChangeActive();
              OptionMenuItems[14].ChangeActive();
      break;
      case 3: OptionMenuItems[4].ChangeChosen();
              OptionMenuItems[8].ChangeChosen();
      break;
    }
  }// sub menu of change difficulty --------------------------------------
  else if(OptionMenuItems[2].Chosen()) // 1st down beginner
  {
    switch(direction) 
    {
      case 0: OptionMenuItems[4].ChangeChosen();
              OptionMenuItems[2].ChangeChosen();
              OptionMenuItems[2].ChangeActive();
              OptionMenuItems[6].ChangeActive();
              OptionMenuItems[10].ChangeActive();
              OptionMenuItems[14].ChangeActive();
              OptionMenuItems[29].ChangeActive(); // beginner description
      break;
      case 3: OptionMenuItems[2].ChangeChosen();
              OptionMenuItems[6].ChangeChosen();
              OptionMenuItems[29].ChangeActive();
              OptionMenuItems[30].ChangeActive();
      break;
    }
  }
  else if(OptionMenuItems[6].Chosen()) // 2nd down intermediate
  {
    switch(direction) 
    {
      case 0: OptionMenuItems[4].ChangeChosen();
              OptionMenuItems[6].ChangeChosen();
              OptionMenuItems[2].ChangeActive();
              OptionMenuItems[6].ChangeActive();
              OptionMenuItems[10].ChangeActive();
              OptionMenuItems[14].ChangeActive();
              OptionMenuItems[30].ChangeActive();
      break;
      case 1: OptionMenuItems[6].ChangeChosen();
              OptionMenuItems[2].ChangeChosen();
              OptionMenuItems[29].ChangeActive();
              OptionMenuItems[30].ChangeActive();
      break;
      case 3: OptionMenuItems[6].ChangeChosen();
              OptionMenuItems[10].ChangeChosen();
              OptionMenuItems[30].ChangeActive();
              OptionMenuItems[31].ChangeActive();
      break;
    }
  }
  else if(OptionMenuItems[10].Chosen()) // 3rd down advanced
  {
    switch(direction) 
    {
      case 0: OptionMenuItems[4].ChangeChosen();
              OptionMenuItems[10].ChangeChosen();
              OptionMenuItems[2].ChangeActive();
              OptionMenuItems[6].ChangeActive();
              OptionMenuItems[10].ChangeActive();
              OptionMenuItems[14].ChangeActive();
              OptionMenuItems[31].ChangeActive();
      break;
      case 1: OptionMenuItems[10].ChangeChosen();
              OptionMenuItems[6].ChangeChosen();
              OptionMenuItems[30].ChangeActive();
              OptionMenuItems[31].ChangeActive();
      break;
      case 3: OptionMenuItems[14].ChangeChosen();
              OptionMenuItems[10].ChangeChosen();
              OptionMenuItems[31].ChangeActive(); // advanced description
              OptionMenuItems[13].ChangeActive();
      break;
    }
  }
  else if(OptionMenuItems[14].Chosen()) // 4th down x-pert
  {
    switch(direction) 
    {
      case 0: OptionMenuItems[4].ChangeChosen();
              OptionMenuItems[14].ChangeChosen();
              OptionMenuItems[2].ChangeActive();
              OptionMenuItems[6].ChangeActive();
              OptionMenuItems[10].ChangeActive();
              OptionMenuItems[14].ChangeActive();
              OptionMenuItems[13].ChangeActive();
      break;
      case 1: OptionMenuItems[10].ChangeChosen();
              OptionMenuItems[14].ChangeChosen();
              OptionMenuItems[31].ChangeActive();
              OptionMenuItems[13].ChangeActive();
      break;
      case 2: OptionMenuItems[14].ChangeChosen();
              OptionMenuItems[13].ChangeChosen();
              for(int x = 32; x < 38; x++)
                OptionMenuItems[x].ChangeActive();
      break;
    }
  }// beginning of submenu number of hints
  else if(OptionMenuItems[13].Chosen())
  {
    switch(direction)
    {
      case 0: OptionMenuItems[13].ChangeChosen();
              OptionMenuItems[14].ChangeChosen();
              for(int x = 32; x < 38; x++)
                OptionMenuItems[x].ChangeActive();
      break;
      case 2: OptionMenuItems[34].ChangeChosen();
              OptionMenuItems[13].ChangeChosen();
      break;
    }     
  }
  else if(OptionMenuItems[34].Chosen())
  {
    switch(direction)
    {
      case 0: OptionMenuItems[34].ChangeChosen();
              OptionMenuItems[13].ChangeChosen();
      break;
      case 1: OptionMenuItems[34].ChangeChosen();
              OptionMenuItems[33].ChangeChosen();
      break;
      case 2: OptionMenuItems[34].ChangeChosen();
              OptionMenuItems[37].ChangeChosen();
      break;
    }
  }
  else if(OptionMenuItems[33].Chosen())
  {
    switch(direction)
    {
      case 0: OptionMenuItems[33].ChangeChosen();
              OptionMenuItems[13].ChangeChosen();
      break;
      case 1: OptionMenuItems[33].ChangeChosen();
              OptionMenuItems[32].ChangeChosen();
      break;
      case 2: OptionMenuItems[33].ChangeChosen();
              OptionMenuItems[36].ChangeChosen();
      break;
      case 3: OptionMenuItems[33].ChangeChosen();
              OptionMenuItems[34].ChangeChosen();
      break;
    }
  }
  else if(OptionMenuItems[32].Chosen())
  {
    switch(direction)
    {
      case 0: OptionMenuItems[32].ChangeChosen();
              OptionMenuItems[13].ChangeChosen();
      break;
      case 2: OptionMenuItems[32].ChangeChosen();
              OptionMenuItems[35].ChangeChosen();
      break;
      case 3: OptionMenuItems[32].ChangeChosen();
              OptionMenuItems[33].ChangeChosen();
      break;
    }
  }
  else if(OptionMenuItems[35].Chosen())
  {
    switch(direction)
    {
      case 0: OptionMenuItems[35].ChangeChosen();
              OptionMenuItems[32].ChangeChosen();
      break;
      case 3: OptionMenuItems[35].ChangeChosen();
              OptionMenuItems[36].ChangeChosen();
      break;
    }
  }
  else if(OptionMenuItems[36].Chosen())
  {
    switch(direction)
    {
      case 0: OptionMenuItems[36].ChangeChosen();
              OptionMenuItems[33].ChangeChosen();
      break;
      case 1: OptionMenuItems[36].ChangeChosen();
              OptionMenuItems[35].ChangeChosen();
      break;
      case 3: OptionMenuItems[36].ChangeChosen();
              OptionMenuItems[37].ChangeChosen();
      break;
    }
  }
  else if(OptionMenuItems[37].Chosen())
  {
    switch(direction)
    {
      case 0: OptionMenuItems[37].ChangeChosen();
              OptionMenuItems[34].ChangeChosen();
      break;
      case 1: OptionMenuItems[37].ChangeChosen();
              OptionMenuItems[36].ChangeChosen();
      break;
    }
  }// end of Submenu difficulty ---------------------------------
  else if(OptionMenuItems[8].Chosen()) // 3rd down change background
  {
    switch(direction) 
    {
      case 1: OptionMenuItems[8].ChangeChosen();
              OptionMenuItems[4].ChangeChosen();
      break;
      case 2: OptionMenuItems[8].ChangeChosen();
              OptionMenuItems[16].ChangeChosen();
              OptionMenuItems[16].ChangeActive();
              OptionMenuItems[20].ChangeActive();
      break;
      case 3: OptionMenuItems[8].ChangeChosen();
              OptionMenuItems[12].ChangeChosen();
      break;
    }
  }// submenu background change ------------------
  else if(OptionMenuItems[16].Chosen()) // Color
  {
    switch(direction)
    {
      case 0: OptionMenuItems[16].ChangeChosen();
              OptionMenuItems[8].ChangeChosen();
              OptionMenuItems[16].ChangeActive();
              OptionMenuItems[20].ChangeActive();
      break;
      case 2: OptionMenuItems[16].ChangeChosen();
              OptionMenuItems[17].ChangeChosen();
              OptionMenuItems[17].ChangeActive();
              OptionMenuItems[21].ChangeActive();
              OptionMenuItems[22].ChangeActive();
              OptionMenuItems[25].ChangeActive();
      break;
      case 3: OptionMenuItems[16].ChangeChosen();
              OptionMenuItems[20].ChangeChosen();
      break;
    }
  }// submenu color --------------------------------
  else if(OptionMenuItems[17].Chosen())
  {
    switch(direction)
    {
      case 0: OptionMenuItems[17].ChangeChosen();
              OptionMenuItems[16].ChangeChosen();
              OptionMenuItems[17].ChangeActive();
              OptionMenuItems[21].ChangeActive();
              OptionMenuItems[22].ChangeActive();
              OptionMenuItems[25].ChangeActive();
      break;
      case 3: OptionMenuItems[17].ChangeChosen();
              OptionMenuItems[21].ChangeChosen();
      break;
    }
  }
  else if(OptionMenuItems[21].Chosen())
  {
    switch(direction)
    {
      case 0: OptionMenuItems[21].ChangeChosen();
              OptionMenuItems[16].ChangeChosen();
              OptionMenuItems[17].ChangeActive();
              OptionMenuItems[21].ChangeActive();
              OptionMenuItems[22].ChangeActive();
              OptionMenuItems[25].ChangeActive();
      break;
      case 1: OptionMenuItems[21].ChangeChosen();
              OptionMenuItems[17].ChangeChosen();
      break;
      case 3: OptionMenuItems[25].ChangeChosen();
              OptionMenuItems[21].ChangeChosen();
      break;
    }
  }
  else if(OptionMenuItems[25].Chosen())
  {
    switch(direction)
    {
      case 0: OptionMenuItems[25].ChangeChosen();
              OptionMenuItems[16].ChangeChosen();
              OptionMenuItems[17].ChangeActive();
              OptionMenuItems[21].ChangeActive();
              OptionMenuItems[22].ChangeActive();
              OptionMenuItems[25].ChangeActive();
      break;
      case 1: OptionMenuItems[21].ChangeChosen();
              OptionMenuItems[25].ChangeChosen();
      break;
      case 3: OptionMenuItems[25].ChangeChosen();
              OptionMenuItems[22].ChangeChosen();
      break;
    }
  }
  else if(OptionMenuItems[22].Chosen())
  {
    switch(direction)
    {
      case 0: OptionMenuItems[22].ChangeChosen();
              OptionMenuItems[16].ChangeChosen();
              OptionMenuItems[17].ChangeActive();
              OptionMenuItems[21].ChangeActive();
              OptionMenuItems[22].ChangeActive();
              OptionMenuItems[25].ChangeActive();
      break;
      case 1: OptionMenuItems[22].ChangeChosen();
              OptionMenuItems[25].ChangeChosen();
      break;
    }
  }// end of submenu color option ------------------------------
  else if(OptionMenuItems[20].Chosen()) // Behavior
  {
    switch(direction)
    {
      case 0: OptionMenuItems[20].ChangeChosen();
              OptionMenuItems[8].ChangeChosen();
              OptionMenuItems[16].ChangeActive();
              OptionMenuItems[20].ChangeActive();
      break;
      case 1: OptionMenuItems[16].ChangeChosen();
              OptionMenuItems[20].ChangeChosen();
      break;
      case 2: OptionMenuItems[20].ChangeChosen();
              OptionMenuItems[18].ChangeChosen();
              OptionMenuItems[18].ChangeActive();
              OptionMenuItems[24].ChangeActive();
    }
  }// beginning of submenu behavior
  else if(OptionMenuItems[18].Chosen())// direction
  {
    switch(direction)
    {
      case 0: OptionMenuItems[18].ChangeChosen();
              OptionMenuItems[20].ChangeChosen();
              OptionMenuItems[18].ChangeActive();
              OptionMenuItems[24].ChangeActive();
      break;
      case 2: OptionMenuItems[18].ChangeChosen();
              OptionMenuItems[3].ChangeChosen();
              OptionMenuItems[3].ChangeActive();
              OptionMenuItems[7].ChangeActive();
              OptionMenuItems[11].ChangeActive();
              OptionMenuItems[15].ChangeActive();
      break;
      case 3: OptionMenuItems[18].ChangeChosen();
              OptionMenuItems[24].ChangeChosen();
      break;
    }
  }//beginning of submenu direction
  else if(OptionMenuItems[3].Chosen())
  {
    switch(direction)
    {
      case 0: OptionMenuItems[3].ChangeChosen();
              OptionMenuItems[18].ChangeChosen();
              OptionMenuItems[3].ChangeActive();
              OptionMenuItems[7].ChangeActive();
              OptionMenuItems[11].ChangeActive();
              OptionMenuItems[15].ChangeActive();
      break;
      case 3: OptionMenuItems[3].ChangeChosen();
              OptionMenuItems[7].ChangeChosen();
      break;
    }
  }
  else if(OptionMenuItems[7].Chosen())
  {
    switch(direction)
    {
      case 0: OptionMenuItems[7].ChangeChosen();
              OptionMenuItems[18].ChangeChosen();
              OptionMenuItems[3].ChangeActive();
              OptionMenuItems[7].ChangeActive();
              OptionMenuItems[11].ChangeActive();
              OptionMenuItems[15].ChangeActive();
      break;
      case 1: OptionMenuItems[3].ChangeChosen();
              OptionMenuItems[7].ChangeChosen();
      break;
      case 3: OptionMenuItems[7].ChangeChosen();
              OptionMenuItems[11].ChangeChosen();
      break;
    }
  }
  else if(OptionMenuItems[11].Chosen())
  {
    switch(direction)
    {
      case 0: OptionMenuItems[11].ChangeChosen();
              OptionMenuItems[18].ChangeChosen();
              OptionMenuItems[3].ChangeActive();
              OptionMenuItems[7].ChangeActive();
              OptionMenuItems[11].ChangeActive();
              OptionMenuItems[15].ChangeActive();
      break;
      case 1: OptionMenuItems[11].ChangeChosen();
              OptionMenuItems[7].ChangeChosen();
      break;
      case 3: OptionMenuItems[15].ChangeChosen();
              OptionMenuItems[11].ChangeChosen();
      break;
    }
  }
  else if(OptionMenuItems[15].Chosen())
  {
    switch(direction)
    {
      case 0: OptionMenuItems[15].ChangeChosen();
              OptionMenuItems[18].ChangeChosen();
              OptionMenuItems[3].ChangeActive();
              OptionMenuItems[7].ChangeActive();
              OptionMenuItems[11].ChangeActive();
              OptionMenuItems[15].ChangeActive();
      break;
      case 1: OptionMenuItems[11].ChangeChosen();
              OptionMenuItems[15].ChangeChosen();
      break;
    }
  }// end of submenu direction -----------------
  else if(OptionMenuItems[24].Chosen())// rotation
  {
    switch(direction)
    {
      case 0: OptionMenuItems[24].ChangeChosen();
              OptionMenuItems[20].ChangeChosen();
              OptionMenuItems[18].ChangeActive();
              OptionMenuItems[24].ChangeActive();
      break;
      case 1: OptionMenuItems[18].ChangeChosen();
              OptionMenuItems[24].ChangeChosen();
      break;
      case 2: OptionMenuItems[24].ChangeChosen();
              OptionMenuItems[19].ChangeChosen();
              OptionMenuItems[19].ChangeActive();
              OptionMenuItems[23].ChangeActive();
      break;
    }
  }// beginning of rotation submenu
  else if(OptionMenuItems[19].Chosen())
  {
    switch(direction)
    {
      case 0: OptionMenuItems[19].ChangeChosen();
              OptionMenuItems[24].ChangeChosen();
              OptionMenuItems[19].ChangeActive();
              OptionMenuItems[23].ChangeActive();
      break;
      case 2: OptionMenuItems[19].ChangeChosen();
              OptionMenuItems[26].ChangeChosen();
              OptionMenuItems[26].ChangeActive();
              OptionMenuItems[27].ChangeActive();
              rotation = 0;
      break;
      case 3: OptionMenuItems[19].ChangeChosen();
              OptionMenuItems[23].ChangeChosen();
      break;
    }
  }
  else if(OptionMenuItems[23].Chosen())
  {
    switch(direction)
    {
      case 0: OptionMenuItems[23].ChangeChosen();
              OptionMenuItems[24].ChangeChosen();
              OptionMenuItems[19].ChangeActive();
              OptionMenuItems[23].ChangeActive();
      break;
      case 1: OptionMenuItems[19].ChangeChosen();
              OptionMenuItems[23].ChangeChosen();
      break;
      case 2: OptionMenuItems[23].ChangeChosen();
              OptionMenuItems[26].ChangeChosen();
              OptionMenuItems[26].ChangeActive();
              OptionMenuItems[27].ChangeActive();
              rotation = 1;
      break;
    }
  }
  else if(OptionMenuItems[26].Chosen())
  {
    switch(direction)
    {
      case 0: OptionMenuItems[19].ChangeChosen();
              OptionMenuItems[26].ChangeChosen();
              OptionMenuItems[26].ChangeActive();
              OptionMenuItems[27].ChangeActive();
      break;        
      case 3: OptionMenuItems[26].ChangeChosen();
              OptionMenuItems[27].ChangeChosen();
      break;
    }
  }
  else if(OptionMenuItems[27].Chosen())
  {
    switch(direction)
    {
      case 0: OptionMenuItems[19].ChangeChosen();
              OptionMenuItems[27].ChangeChosen();
              OptionMenuItems[26].ChangeActive();
              OptionMenuItems[27].ChangeActive();
      break;        
      case 1: OptionMenuItems[26].ChangeChosen();
              OptionMenuItems[27].ChangeChosen();
      break;
    }// end of submenu rotation
  }// end of submenu background change and submenu behavior --------------------
  else if(OptionMenuItems[12].Chosen()) // 4th down calibrate input
  {
    switch(direction)
    {
      case 1: OptionMenuItems[12].ChangeChosen();
              OptionMenuItems[8].ChangeChosen();
      break;
    }
  }
}

void Smenu::ChangeActive()
{
  // change it to the opposite
  active = !active;
  optionactive = false;
  ResetOptionMenu();
}

bool Smenu::OptionActive()
{
  return optionactive;
}

// ---------------------------- END OF MENU DEFINITIONS ----------------------------------
