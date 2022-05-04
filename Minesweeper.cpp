#include <iostream>
#include <vector>
#include <queue>
#include <time.h>
#include <algorithm>

using namespace std;

bool lost;
bool won;

vector<vector<int>> mineBoard{
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {1, 9, 1, 2, 9, 2, 1, 9, 1, 0},
    {1, 1, 1, 2, 9, 2, 1, 1, 1, 0},
    {1, 1, 0, 1, 1, 1, 0, 0, 0, 0},
    {9, 2, 1, 1, 1, 1, 1, 0, 0, 0},
    {1, 2, 9, 1, 1, 9, 1, 0, 0, 0},
    {0, 1, 1, 1, 1, 2, 2, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 9, 2, 1, 1},
    {0, 0, 0, 1, 1, 2, 1, 2, 9, 1},
    {0, 0, 0, 1, 9, 1, 0, 1, 1, 1},
};

vector<vector<char>> myBoard{
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '2', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '1', '1', '1', '-', '-', '-', '-'},
    {'-', '-', '-', '1', '1', '1', '1', '-', '-', '-'},
    {'-', '-', '-', '1', '1', '-', '-', '-', '-', '-'},
    {'-', '1', '1', '1', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
};

bool isValid(int r, int c)
{
    return ((r >= 0) && (r < 10) && (c >= 0) && (c < 10));
}

bool isMine(int r, int c)
{
    if (mineBoard[r][c] == 9)
        return true;
    else
        return false;
}

void move(int *x, int *y)
{
    cout << "Enter your move, (row, column) -> ";
    cin >> *x >> *y;
    return;
}

void print()
{
    cout << "   ";
    for (int i = 0; i < 10; i++)
    {
        cout << i << " ";
    }
    cout << endl
         << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << i << "  ";
        for (int j = 0; j < 10; j++)
            cout << myBoard[i][j] << " ";
        cout << endl;
    }
    return;
}

bool hasEnded()
{
    int count = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (myBoard[i][j] == '-')
                count++;
        }
    }
    if (count == 10 || lost == true)
        return true;
}

// Stores all the cells that have been marked
vector<vector<int>> markedCells(10, vector<int>(10, 0));

// Stores all the cells that have been visited
vector<vector<int>> visited{
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

void print_marked()
{
    cout << "   ";
    for (int i = 0; i < 10; i++)
    {
        cout << i << " ";
    }
    cout << endl
         << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << i << "  ";
        for (int j = 0; j < 10; j++)
            cout << markedCells[i][j] << " ";
        cout << endl;
    }
    return;
}

bool isAFN(int r, int c)
{
    int count = 0;
    int dim[8][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
    for (int i = 0; i < 8; i++)
    {
        if (isValid(r + dim[i][0], c + dim[i][1]))
        {
            if (markedCells[r + dim[i][0]][c + dim[i][1]] == 1)
                count++;
        }
    }
    return (mineBoard[r][c] == count);
}

bool isAMN(int r, int c)
{
    int count = 0;
    int dim[8][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
    for (int i = 0; i < 8; i++)
    {
        if (isValid(r + dim[i][0], c + dim[i][1]))
        {
            if (markedCells[r + dim[i][0]][c + dim[i][1]] == 1)
                count++;
        }
    }
    return (mineBoard[r][c] - count == (9 - count));
}

void singlePointSolver()
{
    // int x = 5;
    do
    {

        int xr, xc;
        bool found = false;
        while (found != true)
        {
            srand(time(NULL));
            xr = rand() % 10;
            xc = rand() % 10;
            if (visited[xr][xc] == 0)
            {
                found = true;
            }
        }
        vector<vector<int>> Neighbours;

        cout << "\n"
             << xr << " " << xc << endl;
        visited[xr][xc] = 1;

        if (mineBoard[xr][xc] == 9)
        {
            lost = true;
            cout << "\nA mine was clicked game lost" << endl;
            break;
        }
        else
        {
            myBoard[xr][xc] = mineBoard[xr][xc] + '0';
        }

        int dim[8][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

        vector<vector<int>> unmarked;
        for (int k = 0; k < 8; k++)
        {
            if (isValid(xr + dim[k][0], xc + dim[k][1]))
            {
                if (markedCells[xr + dim[k][0]][xc + dim[k][1]] == 0)
                    unmarked.push_back({xr + dim[k][0], xc + dim[k][1]});
            }
        }

        if (isAFN(xr, xc))
        {
            for (int k = 0; k < unmarked.size(); k++)
            {
                for (int i = 0; i < unmarked.size(); i++)
                {
                    myBoard[unmarked[i][0]][unmarked[i][1]] = mineBoard[unmarked[i][0]][unmarked[i][1]] + '0';
                    Neighbours.push_back({unmarked[i][0], unmarked[i][1]});
                }
            }
        }

        else if (isAMN(xr, xc))
        {
            for (int k = 0; k < unmarked.size(); k++)
            {
                markedCells[unmarked[k][0]][unmarked[k][1]] = 1;
            }
        }

        // cout << "\n"
        //      << xr << " " << xc << endl;

        print();
        cout << endl
             << endl;
        // print_marked();
        // cout << endl
        //      << endl;

        if (lost == true)
            break;
        // x--;
    } while (!hasEnded());
    // while (x > 0);
}

int main()
{
    print();
    cout << endl
         << endl;
    // print_marked();
    // cout << endl
    //      << endl;
    singlePointSolver();
}