#include <iostream>

int DFSlauncher(int** lake, int** visited, int m, int n);
void DFS(int** lake, int** visited, int m, int n, int& fish, int i, int j);

int main()
{
    int m, n;
    std::cin >> m >> n;

    int** lake = new int* [m];
    for (int i = 0; i < m; i++)
    {
        lake[i] = new int[n];
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            std::cin >> lake[i][j];
    }

    int** visited = new int* [m];
    for (int i = 0; i < m; i++)
    {
        visited[i] = new int[n] {0};  // Initialize to zero while allocating
    }

    std::cout << DFSlauncher(lake, visited, m, n) << std::endl;

    // Release memory
    for (int i = 0; i < m; i++)
    {
        delete[] lake[i];
        delete[] visited[i];
    }
    delete[] lake;    // Release the array of pointers
    delete[] visited; // Release the array of pointers

    return 0;
}

int DFSlauncher(int** lake, int** visited, int m, int n)
{
    int maxfish = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (lake[i][j] > 0 && visited[i][j] == 0) // Check if water and not visited
            {
                int fish = 0;
                DFS(lake, visited, m, n, fish, i, j);
                if (fish > maxfish)
                {
                    maxfish = fish;
                }
            }
        }
    }
    return maxfish;
}

void DFS(int** lake, int** visited, int m, int n, int& fish, int i, int j)
{
    visited[i][j] = 1;
    fish += lake[i][j];
    static const int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} }; // Directions array

    for (int d = 0; d < 4; d++) // Iterate over all 4 possible directions
    {
        int ni = i + dir[d][0], nj = j + dir[d][1];
        if (ni >= 0 && ni < m && nj >= 0 && nj < n && lake[ni][nj] > 0 && visited[ni][nj] == 0)
        {
            DFS(lake, visited, m, n, fish, ni, nj);
        }
    }
}
