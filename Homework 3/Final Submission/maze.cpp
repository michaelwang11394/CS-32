#include <iostream>
#include <string>
using namespace std;



bool pathExists(string maze[], int sr, int sc, int er, int ec)
{
    if (sr == er && sc == er)
        return true;
    maze[sr][sc] = 'X';
    if (maze[sr - 1][sc] == '.') // north
    {
        if (pathExists(maze, sr - 1, sc, er, ec))
            return true;
    }
    if (maze[sr][sc + 1] == '.') // east
    {
        if (pathExists(maze, sr, sc + 1, er, ec))
            return true;
    }
    if (maze[sr + 1][sc] == '.')//south
    {
        if (pathExists(maze, sr + 1, sc, er, ec))
            return true;
    }
    if (maze[sr][sc - 1] == '.')// west
    {
        if (pathExists(maze, sr, sc - 1, er, ec))
            return true;
    }
    return false;
}

int main()
{
	string maze[10] = {
		"XXXXXXXXXX",
		"X........X",
		"XX.X.XXXXX",
		"X..X.X...X",
		"X..X...X.X",
		"XXXX.XXX.X",
		"X.X....XXX",
		"X..XX.XX.X",
		"X...X....X",
		"XXXXXXXXXX"
	};

	if (pathExists(maze, 6, 4, 1, 1))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}