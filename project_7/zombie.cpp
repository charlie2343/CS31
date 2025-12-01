// zombies.cpp

// Portions that you are to complete are marked with a TODO: comment.
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
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;     // max number of rows in the arena
const int MAXCOLS = 24;     // max number of columns in the arena
const int MAXZOMBIES = 100; // max number of zombies allowed

const int NORTH = 0;
const int EAST = 1;
const int SOUTH = 2;
const int WEST = 3;
const int NUMDIRS = 4;

const int EMPTY = 0;
const int HAS_POISON = 1;
const int HAS_ZOMBIE = 2;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Arena; // This is needed to let the compiler know that Arena is a
             // type name, since it's mentioned in the Zombie declaration.

class Zombie
{
public:
    // Constructor
    Zombie(Arena *ap, int r, int c);

    // Accessors
    int row() const;
    int col() const;
    bool isDead() const;

    // Mutators
    void move();

private:
    Arena *m_arena;
    int m_row;
    int m_col;
    bool m_dead;
    bool m_poisoned;
    bool m_isStalled;
};

class Player
{
public:
    // Constructor
    Player(Arena *ap, int r, int c);

    // Accessors
    int row() const;
    int col() const;
    bool isDead() const;

    // Mutators
    string dropPoisonedBrain();
    string move(int dir);
    void setDead();

private:
    Arena *m_arena;
    int m_row;
    int m_col;
    bool m_dead;
};

class Arena
{
public:
    // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();

    // Accessors
    int rows() const;
    int cols() const;
    Player *player() const;
    int zombieCount() const;
    int getCellStatus(int r, int c) const;
    int numberOfZombiesAt(int r, int c) const;
    void display(string msg) const;

    // Mutators
    void setCellStatus(int r, int c, int status);
    bool addZombie(int r, int c);
    bool addPlayer(int r, int c);
    void moveZombies();

private:
    int m_grid[MAXROWS][MAXCOLS];
    int m_rows;
    int m_cols;
    Player *m_player;
    Zombie *m_zombies[MAXZOMBIES];
    int m_nZombies;

    // Helper functions
    void checkPos(int r, int c, string functionName) const;
    void deallocate(Zombie *m_zombies[], int i);
    bool isPosInBounds(int r, int c) const;
};

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nZombies);
    ~Game();

    // Mutators
    void play();

private:
    Arena *m_arena;
    int m_turns;

    // Helper functions
    string takePlayerTurn();
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int randInt(int lowest, int highest);
bool decodeDirection(char ch, int &dir);
bool attemptMove(const Arena &a, int dir, int &r, int &c);
bool recommendMove(const Arena &a, int r, int c, int &bestDir);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Zombie implementation
///////////////////////////////////////////////////////////////////////////

Zombie::Zombie(Arena *ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** A zombie must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols())
    {
        cout << "***** Zombie created with invalid coordinates (" << r << ","
             << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
}

int Zombie::row() const
{
    return m_row;
}

int Zombie::col() const
{

    // Delete the following line and replace it with the correct code.
    return m_col; // This implementation compiles, but is incorrect.
}

bool Zombie::isDead() const
{
    // Delete the following line and replace it with the correct code.
    return m_dead; // This implementation compiles, but is incorrect.
}

void Zombie::move()
{

    //   Return without moving if the zombie has eaten one poisoned
    //   brain (so is supposed to move only every other turn) and
    //   this is a turn it does not move.

    //   Otherwise, attempt to move in a random direction; if can't
    //   move, don't move.  If it lands on a poisoned brain, eat the
    //   brain and remove it from the game (so it is no longer on that
    //   grid point).
    bool isPoison_thisMove;
    if (m_poisoned)
    {
        if (m_isStalled)
        {
            m_isStalled = !m_isStalled;
            return;
        }
    }

    //   This illustrates how you can select a random direction:
    int dir = randInt(0, NUMDIRS - 1); // dir is now UP, DOWN, LEFT, or RIGHT

    int maxRows = m_arena->rows();
    int maxCols = m_arena->cols();
    if (dir == NORTH)
    {
        if (m_row <= 1)
            ;
        else if (m_arena->getCellStatus(m_row - 1, m_col) == HAS_POISON)
        {
            m_arena->setCellStatus(m_row - 1, m_col, EMPTY);
            isPoison_thisMove = true;
        }
        else
        {
            m_row--;
        }
    }
    if (dir == SOUTH)
    {
        if (m_row >= maxRows)
            ;
        else if (m_arena->getCellStatus(m_row + 1, m_col) == HAS_POISON)
        {
            m_arena->setCellStatus(m_row - 1, m_col, EMPTY);
            isPoison_thisMove = true;
        }
        else
        {
            m_row++;
        }
    }
    if (dir == EAST)
    {
        if (m_col >= maxCols)
            ;
        else if (m_arena->getCellStatus(m_row, m_col + 1) == HAS_POISON)
        {
            m_arena->setCellStatus(m_row - 1, m_col, EMPTY);
            isPoison_thisMove = true;
        }
        else
        {
            m_col++;
        }
    }
    if (dir == WEST)
    {
        if (m_col <= 1)
            ;
        else if (m_arena->getCellStatus(m_row, m_col - 1) == HAS_POISON)
        {
            m_arena->setCellStatus(m_row - 1, m_col, EMPTY);
            isPoison_thisMove = true;
        }
        else
        {
            m_col--;
        }
    }
    if (m_poisoned && isPoison_thisMove)
    {
        m_dead = true;
    }
    else
    {
        m_poisoned = isPoison_thisMove;
    }
}

///////////////////////////////////////////////////////////////////////////
//  Player implementation
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena *ap, int r, int c)
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

int Player::row() const
{

    // Delete the following line and replace it with the correct code.
    return m_row; // This implementation compiles, but is incorrect.
}

int Player::col() const
{
    // Delete the following line and replace it with the correct code.
    return m_col; // This implementation compiles, but is incorrect.
}

string Player::dropPoisonedBrain()
{
    if (m_arena->getCellStatus(m_row, m_col) == HAS_POISON)
        return "There's already a poisoned brain at this spot.";
    m_arena->setCellStatus(m_row, m_col, HAS_POISON);
    return "A poisoned brain has been dropped.";
}

string Player::move(int dir)
{

    //        direction.  If this fails,
    //        return "Player couldn't move; player stands."
    //        If the player moves onto a zombie, the player dies and this
    //        returns "Player walked into a zombie and died."
    //        Otherwise, return one of "Player moved north.",
    //        "Player moved east.", "Player moved south.", or
    //        "Player moved west."
    int maxRows = m_arena->rows();
    int maxCols = m_arena->cols();
    if (dir == NORTH)
    {
        if (m_row <= 1)
            return "Player couldn't move; player stands.";
        else if (m_arena->numberOfZombiesAt(m_row - 1, m_col) != 0)
        {
            m_dead = true;
            return "Player walked into a zombie and died.";
        }
        else
        {
            m_row--;
            return "Player moved north.";
        }
    }
    if (dir == SOUTH)
    {
        if (m_row >= maxRows)
            return "Player couldn't move; player stands.";
        else if (m_arena->numberOfZombiesAt(m_row + 1, m_col) != 0)
        {
            m_dead = true;
            return "Player walked into a zombie and died.";
        }
        else
        {
            m_row++;
            return "Player moved south.";
        }
    }
    if (dir == EAST)
    {
        if (m_col >= maxCols)
            return "Player couldn't move; player stands.";
        else if (m_arena->numberOfZombiesAt(m_row, m_col + 1) != 0)
        {
            m_dead = true;
            return "Player walked into a zombie and died.";
        }
        else
        {
            m_col++;
            return "Player moved east.";
        }
    }
    if (dir == WEST)
    {
        if (m_col <= 1)
            return "Player couldn't move; player stands.";
        else if (m_arena->numberOfZombiesAt(m_row, m_col - 1) != 0)
        {
            m_dead = true;
            return "Player walked into a zombie and died.";
        }
        else
        {
            m_col--;
            return "Player moved west.";
        }
    }

    return "Player couldn't move; player stands.";

    // This implementation compiles, but is incorrect.
}

bool Player::isDead() const
{
    return m_dead;
    // Delete the following line and replace it with the correct code.
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Arena implementation
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols)
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
    m_nZombies = 0;
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            setCellStatus(r, c, EMPTY);
}

Arena::~Arena()
{
    cerr << "Entering Arena destructor" << endl;
    delete m_player;
    m_player = nullptr;
    for (int i = 0; i < m_nZombies; i++)
    {
        deallocate(m_zombies, i);
    }
    cerr << "Leaving Arena destructor" << endl;
}

int Arena::rows() const
{
    // Delete the following line and replace it with the correct code.
    return m_rows; // This implementation compiles, but is incorrect.
}

int Arena::cols() const
{

    // Delete the following line and replace it with the correct code.
    return m_cols; // This implementation compiles, but is incorrect.
}

Player *Arena::player() const
{
    return m_player;
}

int Arena::zombieCount() const
{
    // Delete the following line and replace it with the correct code.
    return m_nZombies; // This implementation compiles, but is incorrect.
}

int Arena::getCellStatus(int r, int c) const
{
    checkPos(r, c, "Arena::getCellStatus");
    return m_grid[r - 1][c - 1];
}

int Arena::numberOfZombiesAt(int r, int c) const
{
    // cerr << "GRID value: " << m_grid[r - 1][c - 1] << endl;
    //  if (m_grid[r - 1][c - 1] == 'Z')
    //      return 1;
    //  else if (isdigit(m_grid[r - 1][c - 1]))
    //      return m_grid[r - 1][c - 1] - '0';
    //  if (m_grid[r - 1][c - 1] >= 2)
    //  {
    //      return m_grid[r - 1][c - 1] - 1;
    //  }
    //! little confused if I should update m_grid with zombie number or not
    int count = 0;
    for (int i = 0; i < m_nZombies; i++)
    {
        if (m_zombies[i]->row() == r && m_zombies[i]->col() == c)
        {
            count++;
            // cerr << "FUKCINGS PENISOD" << endl;
        }
    }
    // cerr << "ZOMBIE count: " << count << endl;
    return count; // This implementation compiles, but is incorrect.
}
void Arena::display(string msg) const
{
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;

    // Fill displayGrid with dots (empty) and stars (poisoned brains)
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
            displayGrid[r - 1][c - 1] = (getCellStatus(r, c) == EMPTY ? '.' : '*');

    // Indicate each zombie's position
    int count = 0;
    cerr << "Number of zombies " << m_nZombies << endl;
    for (int i = 0; i < m_nZombies; i++)
    {
        int row = m_zombies[i]->row();
        int col = m_zombies[i]->col();
        char displayC = displayGrid[row - 1][col - 1];
        // cerr << "ZOMBIE @ i = " << i << ", row: " << row << ", col: " << col << endl;
        //  if (displayC == '.' || displayC == '*')
        //  {
        //      displayGrid[row - 1][col - 1] = 'Z';
        //  }
        //  if (displayC == 'Z')
        //  {
        //      displayGrid[row - 1][col - 1] = '2';
        //  }else if(displayC - '0' <= 9){
        //      displayGrid[row - 1][col - 1] = displayC++;
        //  }\]
        //  cerr << "Num Zombies @ 4,3: " << numberOfZombiesAt(4, 3) << endl;
        if (numberOfZombiesAt(row, col) == 1)
        {
            displayGrid[row - 1][col - 1] = 'Z';
        }
        else if (numberOfZombiesAt(row, col) <= 8)
        {
            displayGrid[row - 1][col - 1] = '0' + numberOfZombiesAt(row, col);
        }
        else
        {
            displayGrid[row - 1][col - 1] = '9';
        }
    }

    // Indicate the player's position
    if (m_player != nullptr)
        displayGrid[m_player->row() - 1][m_player->col() - 1] = (m_player->isDead() ? '#' : '@');

    // Draw the grid
    clearScreen();
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
            cout << displayGrid[r - 1][c - 1];
        cout << endl;
    }
    cout << endl;
    // for (r = 1; r <= rows(); r++)
    // {
    //     for (c = 1; c <= cols(); c++)
    //         cout << m_grid[r - 1][c - 1];
    //     cout << endl;
    // }

    // Write message, zombie, and player info
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << zombieCount() << " zombies remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player!" << endl;
    else if (m_player->isDead())
        cout << "The player is dead." << endl;
}

void Arena::setCellStatus(int r, int c, int status)
{
    checkPos(r, c, "Arena::setCellStatus");
    m_grid[r - 1][c - 1] = status;
}

bool Arena::addZombie(int r, int c)
{
    if (!isPosInBounds(r, c))
        return false;

    // Don't add a zombie on a spot with a poisoned brain
    if (getCellStatus(r, c) != EMPTY)
        return false;

    // Don't add a zombie on a spot with a player
    if (m_player != nullptr && m_player->row() == r && m_player->col() == c)
        return false;

    // If there are MAXZOMBIES existing zombies, return false.  Otherwise,
    // dynamically allocate a new zombie at coordinates (r,c).  Save the
    // pointer to newly allocated zombie and return true.
    if (m_nZombies >= MAXZOMBIES)
    {
        return false;
    }
    m_zombies[m_nZombies] = new Zombie(this, r, c);
    // int status = getCellStatus(r, c);
    // cerr << "Status: " << status << endl;
    //  if zombies already there increment count there
    //  if (status >= HAS_ZOMBIE)
    //      setCellStatus(r, c, status + 1);
    //  // otherwise set the initial zombie flag (value 2 )
    //  else
    // setCellStatus(r, c, HAS_ZOMBIE);
    m_nZombies++;
    return true; // This implementation compiles, but is incorrect.
}

bool Arena::addPlayer(int r, int c)
{
    if (!isPosInBounds(r, c))
        return false;

    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

    // Don't add a player on a spot with a zombie
    if (numberOfZombiesAt(r, c) > 0)
        return false;

    m_player = new Player(this, r, c);
    return true;
}

void Arena::moveZombies()
{
    // Move all zombies

    for (int i = 0; i < m_nZombies; i++)
    {
        m_zombies[i]->move();
        if (m_zombies[i]->row() == m_player->row() && m_zombies[i]->col() == m_player->col())
        {
            m_player->setDead();
        }
        if (m_zombies[i]->isDead())
        {
            deallocate(m_zombies, i);
            // m_zombies[i] = nullptr;
        }
    }
}

void Arena::deallocate(Zombie *m_zombies[], int i)
{
    delete m_zombies[i];
    for (int j = i; j < m_nZombies - 1; j++)
    {
        m_zombies[j] = m_zombies[j + 1];
    }
    m_zombies[m_nZombies - 1] = nullptr;
    m_nZombies--;
}

bool Arena::isPosInBounds(int r, int c) const
{
    return (r >= 1 && r <= m_rows && c >= 1 && c <= m_cols);
}

void Arena::checkPos(int r, int c, string functionName) const
{
    if (!isPosInBounds(r, c))
    {
        cout << "***** " << "Invalid arena position (" << r << ","
             << c << ") in call to " << functionName << endl;
        exit(1);
    }
}

///////////////////////////////////////////////////////////////////////////
//  Game implementation
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nZombies)
{
    if (nZombies < 0)
    {
        cout << "***** Cannot create Game with negative number of zombies!" << endl;
        exit(1);
    }
    if (nZombies > MAXZOMBIES)
    {
        cout << "***** Trying to create Game with " << nZombies
             << " zombies; only " << MAXZOMBIES << " are allowed!" << endl;
        exit(1);
    }
    int nEmpty = rows * cols - nZombies - 1; // 1 for Player
    if (nEmpty < 0)
    {
        cout << "***** Game created with a " << rows << " by "
             << cols << " arena, which is too small to hold a player and "
             << nZombies << " zombies!" << endl;
        exit(1);
    }

    // Create arena
    m_arena = new Arena(rows, cols);

    // Add player
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(1, rows);
        cPlayer = randInt(1, cols);
    } while (m_arena->getCellStatus(rPlayer, cPlayer) != EMPTY);
    m_arena->addPlayer(rPlayer, cPlayer);

    // Populate with zombies
    while (nZombies > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (r == rPlayer && c == cPlayer)
            continue;
        m_arena->addZombie(r, c);
        nZombies--;
    }

    m_turns = 0;
}

Game::~Game()
{
    delete m_arena;
}

string Game::takePlayerTurn()
{
    for (;;)
    {
        cout << "Your move (n/e/s/w/x or nothing): ";
        string playerMove;
        getline(cin, playerMove);

        Player *player = m_arena->player();
        int dir;

        if (playerMove.size() == 0)
        {
            if (recommendMove(*m_arena, player->row(), player->col(), dir))
                return player->move(dir);
            else
                return player->dropPoisonedBrain();
        }
        else if (playerMove.size() == 1)
        {
            if (tolower(playerMove[0]) == 'x')
                return player->dropPoisonedBrain();
            else if (decodeDirection(playerMove[0], dir))
                return player->move(dir);
        }
        cout << "Player move must be nothing, or 1 character n/e/s/w/x." << endl;
    }
}

string translateDir(int dir)
{
    switch (dir)
    {
    case 0:
        return "NORTH";
        break;
    case 1:
        return "EAST";
        break;
    case 2:
        return "SOUTH";
        break;
    case 3:
        return "WEST";
        break;
    }
    return "I HATE CS";
}

void Game::play()
{
    m_arena->display("");
    Player *player = m_arena->player();
    if (player == nullptr)
        return;
    while (!player->isDead() && m_arena->zombieCount() > 0)
    {
        m_turns++;
        string msg = takePlayerTurn();
        if (!player->isDead())
            m_arena->moveZombies();
        m_arena->display(msg);
        int bestDir = 0;
        if (recommendMove(*m_arena, player->row(), player->col(), bestDir))
        {
            cout << "Best dir: " << translateDir(bestDir) << endl;
        }
        else
        {
            cout << "Recommended to drop brain" << endl;
        }
        cout << m_turns << " turns have been taken." << endl;
    }
    if (player->isDead())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementation
///////////////////////////////////////////////////////////////////////////

// Return a uniformly distributed random int from lowest to highest, inclusive
int randInt(int lowest, int highest)
{
    if (highest < lowest)
        swap(highest, lowest);
    static random_device ran;
    static default_random_engine generator(ran());
    uniform_int_distribution<> distro(lowest, highest);
    return distro(generator);
}

bool decodeDirection(char ch, int &dir)
{
    switch (tolower(ch))
    {
    default:
        return false;
    case 'n':
        dir = NORTH;
        break;
    case 'e':
        dir = EAST;
        break;
    case 's':
        dir = SOUTH;
        break;
    case 'w':
        dir = WEST;
        break;
    }
    return true;
}

// Return false without changing anything if moving one step from (r,c)
// in the indicated direction would run off the edge of the arena.
// Otherwise, update r and c to the position resulting from the move and
// return true.
bool attemptMove(const Arena &a, int dir, int &r, int &c)
{
    // TODO:  Implement this function
    // Delete the following line and replace it with the correct code.
    int step = 1;
    if (dir == NORTH || dir == WEST)
    {
        step = -1;
    }
    if (dir == NORTH)
    {
        if (r <= 1)
        {
            return false;
        }
        r += step;
        return true;
    }
    if (dir == SOUTH)
    {
        if (r >= a.rows())
        {
            return false;
        }
        r += step;
        return true;
    }
    if (dir == WEST)
    {
        if (c <= 1)
        {
            return false;
        }
        c += step;
        return true;
    }
    if (dir == EAST)
    {
        if (c >= a.cols())
        {
            return false;
        }
        c += step;
        return true;
    }
    return false; // This implementation compiles, but is incorrect.
}

// Recommend a move for a player at (r,c):  A false return means the
// recommendation is that the player should drop a poisoned brain and
// not move; otherwise, this function sets bestDir to the recommended
// direction to move and returns true.
bool recommendMove(const Arena &a, int r, int c, int &bestDir)
{
    // TODO:  Implement this function
    // Delete the following line and replace it with your code.
    int hazardGrid[a.rows()][a.cols()];
    for (int i = 1; i <= a.rows(); i++)
        for (int j = 1; j <= a.cols(); j++)
            hazardGrid[i - 1][j - 1] = 0;

    for (int i = 1; i <= a.rows(); i++)
    {
        for (int j = 1; j <= a.cols(); j++)
        {
            if (a.numberOfZombiesAt(i, j) != 0)
            {
                hazardGrid[i - 1][j - 1] = 1;
                for (int dir = 0; dir <= 3; dir++)
                {
                    int temp_i = i;
                    int temp_j = j;
                    // loop thorugh dir
                    if (attemptMove(a, dir, i, j))
                    {
                        hazardGrid[i - 1][j - 1] = 1;
                    }
                    i = temp_i;
                    j = temp_j;
                }
            }
        }
    }

    for (int i = 1; i <= a.rows(); i++)
    {
        for (int j = 1; j <= a.cols(); j++)
            cout << hazardGrid[i - 1][j - 1];
        cout << endl;
    }
    cout << endl;

    // if staying put is dangerous
    if (hazardGrid[r - 1][c - 1] == 1)
    {
        for (int dir = 0; dir <= 3; dir++)
        {
            int temp_r = r;
            int temp_c = c;
            // loop thorugh dir
            if (attemptMove(a, dir, r, c))
            {
                if (hazardGrid[r - 1][c - 1] == 1)
                {
                    ;
                }
                else
                {
                    bestDir = dir;
                    return true;
                }
            }
            r = temp_r;
            c = temp_c;
        }
    }
    // staying put is safe-> drop poison brain
    return false;

    // Your replacement implementation should do something intelligent.
    // You don't have to be any smarter than the following, although
    // you can if you want to be:  If staying put runs the risk of a
    // zombie possibly moving onto the player's location when the zombies
    // move, yet moving in a particular direction puts the player in a
    // position that is safe when the zombies move, then the chosen
    // action is to move to a safer location.  Similarly, if staying put
    // is safe, but moving in certain directions puts the player in
    // danger of dying when the zombies move, then the chosen action should
    // not be to move in one of the dangerous directions; instead, the player
    // should stay put or move to another safe position.  In general, a
    // position that may be moved to by many zombies is more dangerous than
    // one that may be moved to by few.
    //
    // Unless you want to, you do not have to take into account that a
    // zombie might be poisoned and thus sometimes less dangerous than one
    // that is not.  That requires a more sophisticated analysis that
    // we're not asking you to do.
}

///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////

int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 5, 2);
    Game g(10, 12, 40);

    // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANYTHING BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _WIN32

#pragma warning(disable : 4005) // redefined macro in <windows.h>
#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = {0, 0};
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                               &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else // not _WIN32

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen() // will just write a newline in an Xcode output window
{
    static const char *term = std::getenv("TERM");
    if (term == nullptr || std::strcmp(term, "dumb") == 0)
        std::cout << std::endl;
    else
    {
        static const char *ESC_SEQ = "\x1B["; // ANSI Terminal esc seq:  ESC [
        std::cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << std::flush;
    }
}

#endif