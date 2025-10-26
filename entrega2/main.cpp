#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
#include <fstream>

using namespace std;

typedef struct vertice{
  unordered_set<int> connections{};
  int state = 0;
  int depth = 0;
} line;

inline int readNumber() {
  int input;
  cin >> input;
  return input;
}

inline int bfs(vector<vertice> vertices, int vec, int *count) {
  queue<int> vQueue{};
  int longest = 0;
  *count = 0;
  vQueue.push(vec);

  while (!vQueue.empty()) {
    int currVec = vQueue.front();
    vQueue.pop();

    for (int adj : vertices[currVec].connections) {
      if (vertices[adj].state == 0) {
	int depth = vertices[currVec].depth + 1;
	
        vertices[adj].state++;
	vQueue.push(adj);
	vertices[adj].depth = depth;
	
	if(depth > longest) longest = adj;
      }
    }

    vertices[currVec].state = 2;
    (*count)++;
  }

  return longest;
}

inline int diameter(vector<vertice> vertices, int n) {
  int count, longestVec;
  
  longestVec = bfs(vertices,0,&count);

  if (count != n) return -1;

  return vertices[bfs(vertices, longestVec, &count)].depth;
}

int main() {
  int n, m, l;
  int count = 0;
  int currLine = -1;

  ios::sync_with_stdio(0);
  cin.tie(0);

  n = readNumber();
  m = readNumber();
  l = readNumber();

  vector<vertice> vertices(n);
  vector<vertice> lines(l);

  for (int i = 0;i < m; i++) {
    int v1 = readNumber()-1, v2 = readNumber()-1, connection = readNumber()-1;

    if (currLine == -2) currLine = connection;
    else if (connection != currLine) currLine = -1;

    if (!vertices[v1].state) {
      vertices[v1].state++;
      count++;
    }

    if (!vertices[v2].state) {
      vertices[v2].state++;
      count++;
    }
    
    for (int line : vertices[v1].connections)
      if (line != connection) lines[line].connections.insert(connection);
    
    for (int line : vertices[v2].connections)
      if (line != connection) lines[line].connections.insert(connection);
    
    vertices[v1].connections.insert(connection);
    vertices[v2].connections.insert(connection);
  }

  if (currLine != -1 || count != n) {
    cout << "-1\n";
    return 0;
  }

  cout << diameter(lines, l) << '\n';
  
  return 0;
}
