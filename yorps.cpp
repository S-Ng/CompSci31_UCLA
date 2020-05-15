// yorps.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the utterly trivial
// functions (marked TRIVIAL).  Then get Arena::display going.  That gives
// you more flexibility in the order that you choose to tackle the rest of
// the functionality.  As you finish implementing each TODO: item, remove
// its TODO: comment; that makes it easier to find what you have left to do.

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
#include <cassert>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;            // max number of rows in the arena
const int MAXCOLS = 20;            // max number of columns in the arena
const int MAXYORPS = 100;          // max number of yorps allowed
const int MAXCOLORS = 3;           // max number of colors
const double WALL_DENSITY = 0.14;  // density of walls

const int NORTH = 0;
const int EAST = 1;
const int SOUTH = 2;
const int WEST = 3;
const int NUMDIRS = 4;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Arena;  // This is needed to let the compiler know that Arena is a
			  // type name, since it's mentioned in the Yorp declaration.

class Yorp // ADDED PRIVATE HEALTH VARIABLE -SN
{
public:
	// Constructor
	Yorp(Arena* ap, int r, int c, char color);

	// Accessors
	int  row() const;
	int  col() const;
	char color() const;
	bool isDead() const;

	// Mutators
	void forceMove(int dir);
	void move();

private:
	Arena* m_arena;
	int    m_row;
	int    m_col;
	char   m_color;
	int m_health; // ADD HEALTH VARIABLE -SN
};

class Player // UNCHANGED -SN
{
public:
	// Constructor
	Player(Arena* ap, int r, int c);

	// Accessors
	int  row() const;
	int  col() const;
	bool isDead() const;

	// Mutators
	string stand();
	string move(int dir);
	void   setDead();

private:
	Arena* m_arena;
	int    m_row;
	int    m_col;
	bool   m_dead;
};

class Arena // UNCHANGED - SN
{
public:
	// Constructor/destructor
	Arena(int nRows, int nCols);
	~Arena();

	// Accessors
	int     rows() const;
	int     cols() const;
	Player* player() const;
	int     yorpCount() const;
	bool    hasWallAt(int r, int c) const;
	int     numberOfYorpsAt(int r, int c) const;
	void    display(string msg) const;

	// Mutators
	void   placeWallAt(int r, int c);
	bool   addYorp(int r, int c, char color);
	bool   addPlayer(int r, int c);
	string moveYorps(char color, int dir);

private:
	bool    m_wallGrid[MAXROWS][MAXCOLS];
	int     m_rows;
	int     m_cols;
	Player* m_player;
	Yorp*   m_yorps[MAXYORPS]; //ARRAY OF POINTERS TO YORP OBJECTS -SN
	int     m_nYorps;

	// Helper functions
	void checkPos(int r, int c, string functionName) const;
};

class Game // UNCHANGED
{
public:
	// Constructor/destructor
	Game(int rows, int cols, int nYorps);
	~Game();

	// Mutators
	void play();

private:
	Arena* m_arena;

	// Helper functions
	string takePlayerTurn();
	string takeYorpsTurn();
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char ch);
int randInt(int lowest, int highest);
bool attemptMove(const Arena& a, int dir, int& r, int& c);
bool recommendMove(const Arena& a, int r, int c, int& bestDir);
void clearScreen();
int evaluateMove(const Arena& a, int r, int c); // ADDED THIS FUNCTION -SN

///////////////////////////////////////////////////////////////////////////
//  Yorp implementation
///////////////////////////////////////////////////////////////////////////

Yorp::Yorp(Arena* ap, int r, int c, char color) // ADDED HEALTH INITIALIZATION
{
	if (ap == nullptr)
	{
		cout << "***** A yorp must be created in some Arena!" << endl;
		exit(1);
	}
	if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols())
	{
		cout << "***** Yorp created with invalid coordinates (" << r << ","
			<< c << ")!" << endl;
		exit(1);
	}
	if (color != 'R'  &&  color != 'Y'  &&  color != 'B')
	{
		cout << "***** Yorp created with invalid color " << color << endl;
		exit(1);
	}
	m_arena = ap;
	m_row = r;
	m_col = c;
	m_color = color;
	m_health = 3; // INITIALIZE HEALTH TO 3 -SN
}

int Yorp::row() const // UNCHANGED -SN
{
	return m_row;
}

int Yorp::col() const // DONE -SN
{
	// Return what column the yorp is at.
	return m_col;  
}

char Yorp::color() const // DONE -SN
{
	// Return what color the yorp follows.
	return m_color; 
}

bool Yorp::isDead() const // DONE -SN
{
	// Return whether the yorp is dead.
	return (m_health == 0);  // RETURNS TRUE IS YORP IS DEAD -SN
}

void Yorp::forceMove(int dir) // DONE -SN
{
	// Move the yorp in the indicated direction, if possible.
	// Suffer one unit of damage if moving fails
	bool moveSuccessful = attemptMove(*m_arena, dir, m_row, m_col);
	if (!moveSuccessful) // hit something
		m_health--; // sustain 1 hp damage
}

void Yorp::move() // UNCHAGNED -SN
{
	// Attempt to move in a random direction; if can't move, don't move
	if (!isDead())
		attemptMove(*m_arena, randInt(0, NUMDIRS - 1), m_row, m_col);
}

///////////////////////////////////////////////////////////////////////////
//  Player implementation
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena* ap, int r, int c) // UNCHANGED
{
	if (ap == nullptr)
	{
		cout << "***** The player must be created in some Arena!" << endl;
		exit(1);
	}
	if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols())
	{
		cout << "**** Player created with invalid coordinates (" << r
			<< "," << c << ")!" << endl;
		exit(1);
	}
	m_arena = ap;
	m_row = r;
	m_col = c;
	m_dead = false;
}

int Player::row() const // DONE -SN
{
	// Return what row the player is at.
	return m_row;  
}

int Player::col() const //	DONE -SN
{
	//  Return what column the player is at.
	return m_col;  
}

string Player::stand() // UNCHAGNED -SN
{
	return "Player stands.";
}

string Player::move(int dir) //	DONE -SN
{
	//		  Attempt to move the player one step in the indicated
	//        direction.  If this fails,
	//        return "Player couldn't move; player stands."
	//        A player who moves onto a yorp dies, and this
	//        returns "Player walked into a yorp and died."
	//        Otherwise, return one of "Player moved north.",
	//        "Player moved east.", "Player moved south.", or
	//        "Player moved west."
	bool moveSuccessful = attemptMove(*m_arena, dir, m_row, m_col); // see if player can make that move
	cout << "m_arena is " << m_arena << endl;
	if (!moveSuccessful)
		return "Player couldn't move; player stands.";
	if (m_arena->numberOfYorpsAt(m_row, m_col) > 0) { // if there are any yorps on player position, player dies
		m_dead = true; // set player dead
		return "Player walked into a yorp and died.";
	}
	switch (dir) { // find which direction message to return
	case NORTH:
		return "Player moved north.";
	case EAST:
		return "Player moved east.";
	case SOUTH:
		return "Player moved south." ;
	case WEST:
		return "Player moved west.";
	default:
		cout << "This should never happen in Player::move" << endl;
	}
}

bool Player::isDead() const //DONE -SN
{
	// Return whether the player is dead.
	return m_dead;  // RETURNS TRUE IF PLAYER WAS PREVIOUSLY SET DEAD
}

void Player::setDead() // UNCHANGED -SN
{
	m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Arena implementation
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols) // UNCHANGED
{
	if (nRows <= 0 || nCols <= 0 || nRows > MAXROWS || nCols > MAXCOLS)
	{
		cout << "***** Arena created with invalid size " << nRows << " by "
			<< nCols << "!" << endl;
		exit(1);
	}
	m_rows = nRows;
	m_cols = nCols;
	m_player = nullptr;
	m_nYorps = 0;
	for (int r = 1; r <= m_rows; r++)
		for (int c = 1; c <= m_cols; c++)
			m_wallGrid[r - 1][c - 1] = false;
}

Arena::~Arena() // DONE -SN
{
	//  Release the player and all remaining dynamically allocated yorps.
	delete m_player; // delete dynamically allocated player
	m_player = nullptr;
	for (int i = 0; i < m_nYorps; i++) { // iterate through all remaining yorps
		delete m_yorps[i]; // delete dynamically allocated yorps
		m_yorps[i] = nullptr;
	}
}

int Arena::rows() const // DONE -SN
{
	//return the number of rows in the arena.
	return m_rows;
}

int Arena::cols() const // DONE -SN
{
	// return the number of columns in the arena
	return m_cols; 
}

Player* Arena::player() const // UNCHAGNED -SN
{
	return m_player;
}

int Arena::yorpCount() const // DONE -SN
{
	// return the number of yorps in the arena
	return m_nYorps; 
}

bool Arena::hasWallAt(int r, int c) const // UNCHANGED -SN
{
	checkPos(r, c, "Arena::hasWallAt");
	return m_wallGrid[r - 1][c - 1];
}

int Arena::numberOfYorpsAt(int r, int c) const //DONE -SN
{
	// Return the number of yorps at row r, column c.
	int n_yorpsAtLoc = 0;
	for (int i = 0; i < m_nYorps; i++) { //	ITERATE THROUGH ALL YORPS -SN
		if ((m_yorps[i]->row()) == r && (m_yorps[i]->col()) == c) // IF YORP IS AT POSITION, ADD TO LIST -SN
			n_yorpsAtLoc++;
	}
	return n_yorpsAtLoc; 
}

void Arena::display(string msg) const //DONE -SN
{
	char displayGrid[MAXROWS][MAXCOLS];
	int r, c;

	// Fill displayGrid with dots (empty) and stars (wall)
	for (r = 1; r <= rows(); r++)
		for (c = 1; c <= cols(); c++)
			displayGrid[r - 1][c - 1] = (hasWallAt(r, c) ? '*' : '.');

	// Indicate yorp positions by their colors.  If more than one yorp
	// occupies a cell, show just one (any one will do).

	// For each yorp, set the grid cell to that yorp's color character.
	for (int i = 0; i < m_nYorps; i++) { //	iterate through each yorp and put it's corresponding color at its row and column
		displayGrid[(m_yorps[i]->row() - 1)][(m_yorps[i]->col() - 1)] = m_yorps[i]->color();
	}

	// Indicate player's position
	if (m_player != nullptr)
		displayGrid[m_player->row() - 1][m_player->col() - 1] = (m_player->isDead() ? 'X' : '@');

	// Draw the grid
	clearScreen();
	for (r = 1; r <= rows(); r++)
	{
		for (c = 1; c <= cols(); c++)
			cout << displayGrid[r - 1][c - 1];
		cout << endl;
	}
	cout << endl;

	// Write message, yorp, and player info
	if (msg != "")
		cout << msg << endl;
	cout << "There are " << yorpCount() << " yorps remaining." << endl;
	if (m_player == nullptr)
		cout << "There is no player!" << endl;
	else if (m_player->isDead())
		cout << "The player is dead." << endl;
}

void Arena::placeWallAt(int r, int c) // UNCHANGED -SN
{
	checkPos(r, c, "Arena::placeWallAt");
	m_wallGrid[r - 1][c - 1] = true;
}

bool Arena::addYorp(int r, int c, char color) // UNCHANGED -SN
{
	if (hasWallAt(r, c))
		return false;
	if (m_player != nullptr  &&  m_player->row() == r && m_player->col() == c)
		return false;
	if (color != 'R'  &&  color != 'Y'  &&  color != 'B')
		return false;
	if (m_nYorps == MAXYORPS)
		return false;
	m_yorps[m_nYorps] = new Yorp(this, r, c, color);
	m_nYorps++;
	return true;
}

bool Arena::addPlayer(int r, int c) // UNCHANGED -SN
{
	if (m_player != nullptr || hasWallAt(r, c))
		return false;
	if (numberOfYorpsAt(r, c) > 0)
		return false;
	m_player = new Player(this, r, c);
	return true;
}

string Arena::moveYorps(char color, int dir) // DONE -SN
{
	// Yorps of the indicated color will follow that color with probability 1/2
	bool willFollow = (randInt(0, 1) == 0);

	// Move all yorps
	int nYorpsOriginally = m_nYorps;

	//		  Move each yorp.  Force yorps of the indicated color to move
	//        in the indicated direction if willFollow is true.  If
	//        willFollow is false, or if the yorp is of a different color,
	//        it just moves.  Mark the player as dead necessary.  Release
	//        any dead dynamically allocated yorps.
	if (willFollow) {
		for (int i = 0; i < m_nYorps; i++) {// iterate through yorps
			if ((m_yorps[i]->color()) == color) {// yorp is correct color
				m_yorps[i]->forceMove(dir); // force move in direction and sustain damage if invalid move
				if (m_yorps[i]->isDead()) {// is yorp dead
					delete m_yorps[i]; // delete yorp
					for (int j = i + 1; j < m_nYorps; j++) // iterate through remaining yorps
						m_yorps[j-1] = m_yorps[j]; // remove dangling pointer to deleted yorp
					m_nYorps--; // one fewer yorps
				}
			}
			else
				m_yorps[i]->move(); //move yorp randomly

			if (m_yorps[i]->row() == m_player->row() && m_yorps[i]->col() == m_player->col()) // yorp on player space
				m_player->setDead(); // kill player
		}
	}
	else { // yorps won't follow fruit
		for (int i = 0; i < m_nYorps; i++) {
			m_yorps[i]->move();//move all yorps random

			if (m_yorps[i]->row() == m_player->row() && m_yorps[i]->col() == m_player->col()) // yorp on player space
				m_player->setDead(); // kill player
		}
	}

	if (m_nYorps < nYorpsOriginally)
		return "Some yorps have been destroyed.";
	else
		return "No yorps were destroyed.";
}

void Arena::checkPos(int r, int c, string functionName) const // UNCHANGD -SN
{
	if (r < 1 || r > m_rows || c < 1 || c > m_cols)
	{
		cout << "***** " << "Invalid arena position (" << r << ","
			<< c << ") in call to " << functionName << endl;
		exit(1);
	}
}

///////////////////////////////////////////////////////////////////////////
//  Game implementation
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nYorps) // UNCHANGED
{
	if (nYorps < 0 || nYorps > MAXYORPS)
	{
		cout << "***** Game created with invalid number of yorps:  "
			<< nYorps << endl;
		exit(1);
	}
	int nEmpty = rows * cols - nYorps - 1;  // 1 for Player
	if (nEmpty < 0)
	{
		cout << "***** Game created with a " << rows << " by "
			<< cols << " arena, which is too small too hold a player and "
			<< nYorps << " yorps!" << endl;
		exit(1);
	}

	// Create arena
	m_arena = new Arena(rows, cols);

	// Add some walls in WALL_DENSITY of the empty spots
	assert(WALL_DENSITY >= 0 && WALL_DENSITY <= 1);
	int nWalls = static_cast<int>(WALL_DENSITY * nEmpty);
	while (nWalls > 0)
	{
		int r = randInt(1, rows);
		int c = randInt(1, cols);
		if (m_arena->hasWallAt(r, c))
			continue;
		m_arena->placeWallAt(r, c);
		nWalls--;
	}

	// Add player
	int rPlayer;
	int cPlayer;
	do
	{
		rPlayer = randInt(1, rows);
		cPlayer = randInt(1, cols);
	} while (m_arena->hasWallAt(rPlayer, cPlayer));
	m_arena->addPlayer(rPlayer, cPlayer);

	// Populate with yorps
	while (nYorps > 0)
	{
		int r = randInt(1, rows);
		int c = randInt(1, cols);
		if (m_arena->hasWallAt(r, c) || (r == rPlayer && c == cPlayer))
			continue;
		const char colors[MAXCOLORS] = { 'R', 'Y', 'B' };
		m_arena->addYorp(r, c, colors[randInt(1, MAXCOLORS) - 1]);
		nYorps--;
	}
}

Game::~Game() // UNCHANGED
{
	delete m_arena;
}

string Game::takePlayerTurn() // UNCHANGED
{
	for (;;)
	{
		cout << "Your move (n/e/s/w/x or nothing): ";
		string playerMove;
		getline(cin, playerMove);

		Player* player = m_arena->player(); // create a pointer to the player -SN
		int dir;

		if (playerMove.size() == 0) // no move given, make random move
		{
			if (recommendMove(*m_arena, player->row(), player->col(), dir))
				return player->move(dir);
			else
				return player->stand();
		}
		else if (playerMove.size() == 1) // move given
		{
			if (tolower(playerMove[0]) == 'x')
				return player->stand();
			else
			{
				dir = decodeDirection(tolower(playerMove[0]));
				if (dir != -1)
					return player->move(dir);
			}
		}
		cout << "Player move must be nothing, or 1 character n/e/s/w/x." << endl;
	}
}

string Game::takeYorpsTurn() // UNCHANGED
{
	for (;;)
	{
		cout << "Color thrown and direction (e.g., Rn or bw): ";
		string colorAndDir;
		getline(cin, colorAndDir);
		if (colorAndDir.size() != 2)
		{
			cout << "You must specify a color followed by a direction." << endl;
			continue;
		}
		char color = toupper(colorAndDir[0]);
		if (color != 'R'  &&  color != 'Y'  &&  color != 'B')
		{
			cout << "Color must be upper or lower R, Y, or B." << endl;
			continue;
		}
		int dir = decodeDirection(tolower(colorAndDir[1]));
		if (dir != -1)
			return m_arena->moveYorps(color, dir);
		cout << "Direction must be n, e, s, or w." << endl;
	}
}

void Game::play() // UNCHANGED
{
	m_arena->display("");
	Player* player = m_arena->player();
	if (player == nullptr)
		return;
	while (!player->isDead() && m_arena->yorpCount() > 0)
	{
		string msg = takePlayerTurn();

		m_arena->display(msg);
		if (player->isDead())
			break;
		msg = takeYorpsTurn();
		m_arena->display(msg);
	}
	if (player->isDead())
		cout << "You lose." << endl;
	else
		cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir) // UNCHANGED
{
	switch (dir)
	{
	case 'n':  return NORTH;
	case 'e':  return EAST;
	case 's':  return SOUTH;
	case 'w':  return WEST;
	}
	return -1;  // bad argument passed in!
}

// Return a random int from min to max, inclusive
int randInt(int min, int max) // UNCHANGED
{
	if (max < min)
		swap(max, min);
	static random_device rd;
	static default_random_engine generator(rd());
	uniform_int_distribution<> distro(min, max);
	return distro(generator);
}

bool attemptMove(const Arena& a, int dir, int& r, int& c) // DONE -SN (Arena& a passes an arena type by reference, so I can modify it)
{
	// Return false without changing anything if moving one step from (r,c)
	// in the indicated direction would hit a wall or run off the edge of the
	// arena.  Otherwise, update r and c to the position resulting from the
	// move and return true.

	int row = r; // copy r
	int col = c; // copy c
	switch (dir) {
	case NORTH:
		row--; break;
	case EAST:
		col++; break;
	case SOUTH:
		row++; break;
	case WEST:
		col--; break;
	}
	if (row < 1 || row > a.rows() || col < 1 || col > a.cols() || /*OUT OF BOUNDS*/
		a.hasWallAt(row, col)) { // WALL
		return false; 
	}
	r = row; // update row
	c = col; // update col
	return true;
}

bool recommendMove(const Arena& a, int r, int c, int& bestDir) // DONE -SN
{
	// Test possible moves
	int bestR = r; // look for best row
	int bestC = c; // look for best column
	int minYorps = MAXYORPS; // initialize best case move based on fewest number of yorps
	int numYorps; // variable for sum of yorps surrounding a given position

	// Evaluate each possible position
	for (int row = r - 1; row <= r + 1; row++) { // check north, current, and south positions
		if (row > 0 && row <= a.rows()) { // if within bounds
			numYorps = evaluateMove(a, row, c); // get number of yorps at adjacent positions
			if (numYorps != -1 && numYorps < minYorps) {// not a wall and best option so far
				bestR = row;
				minYorps = numYorps; // update best position based on number of adjacent yorps
			}
		}
	}
	for (int col = c - 1; col <= c + 1; col++) { // check east, current, and west positions
		if (col > 0 && col <= a.cols()) { // if within bounds
			numYorps = evaluateMove(a, r, col); // get number of yorps at adjacent positions
			if (numYorps != -1 && numYorps < minYorps) {
				bestC = col;
				bestR = r; // have to reset bestR to match column position
				minYorps = numYorps; // update best position based on number of adjacent yorps
			}
		}
	}
	// get direction of best move
	if (bestR == r - 1)
		bestDir = NORTH;
	else if (bestR == r + 1)
		bestDir = SOUTH;
	else if (bestC == c - 1)
		bestDir = WEST;
	else if (bestC == c + 1)
		bestDir = EAST;
	else // both r and c are unchanged
		return false; // best option is standing still

	// Recommend a move for a player at (r,c):  A false return means the
	// recommendation is that the player should stand; otherwise, bestDir is
	// set to the recommended direction to move.

	return true;  // if best direction is found, return true

	  // Your replacement implementation should do something intelligent.
	  // For example, if you're standing next to four zurts, and moving
	  // north would put you next to two zurts, but moving east would put
	  // you next to none, moving east is a safer choice than standing or
	  // moving north.
}

int evaluateMove(const Arena& a, int r, int c)  // ADDED FUNCTION TO AID recommendMove
{	// get number of yorps at adjacent positions
	if (a.hasWallAt(r, c) || a.numberOfYorpsAt(r, c) > 0) // has a wall, invalid move. or has yorp, move means game over
		return -1;
	int numYorps = 0; // initialize adjacent yorp count to 0
	for (int row = r - 1; row <= r + 1; row++)  // iterate through rows next to possible move
		numYorps += a.numberOfYorpsAt(row, c); // add number of yorps in adjacent rows
	for (int col = c - 1; col <= c + 1; col++)  // iterate through cols next to possible move
		numYorps += a.numberOfYorpsAt(r, col); // add number of yorps in adjacent columns
	return numYorps;
}
///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////
int main()
{
	// Create a game
	// Use this instead to create a mini-game:   
	//Game g(3, 5, 2);
	Game g(10, 12, 50);

	// Play the game
	g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	COORD upperLeft = { 0, 0 };
	DWORD dwCharsWritten;
	FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
		&dwCharsWritten);
	SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
	static const char* term = getenv("TERM");
	if (term == nullptr || strcmp(term, "dumb") == 0)
		cout << endl;
	else
	{
		static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
		cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
	}
}

#endif