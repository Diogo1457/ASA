#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>

using namespace std;

int readNumber() {
  string input{};
  cin >> input;
  return stoi(input);
}

string reconstruct(vector<vector<int>> &matrix, vector<vector<vector<vector<int>>>> &res_matrix, vector<int> &vec, int x, int y) {
  if (x == y) return to_string(vec[0]); // caso terminal

  int p = vec[1];
  vector<int> l_vec, r_vec;

  l_vec = res_matrix[x][y-p-1][vec[2]];

  r_vec = res_matrix[y-p][y][vec[3]];

  return "(" + reconstruct(matrix,res_matrix,l_vec, x, y-p-1) + " " + reconstruct(matrix,res_matrix,r_vec,y-p,y) +  ")";
}

string func(vector<vector<int>> matrix, vector<int> operation, int res) {
  int m = operation.size();
  int n = matrix.size();
  vector<vector<vector<vector<int>>>> res_matrix(m, vector<vector<vector<int>>>(m, vector<vector<int>>(n, vector<int>{})));

  // -- RESULT SEARCHING --
  
  for (int i = 0; i < m; i++) {
    for (int ii = 0; ii < m-i; ii++) {
      int x = ii, y = ii+i;
      vector<vector<int>> &Vec = res_matrix[x][y];
      
      if (i == 0) {
	Vec[0] = vector<int>{operation[ii]};
	continue;
      }

      int count = 0;
      vector<bool> used(n, false);
      
      for (int p = 0; p < i; p++) {
	vector<vector<int>> &Vec_l = res_matrix[x][y-p-1], &Vec_r = res_matrix[x+i-p][y];
	bool stop = false;

	for (int l_index = 0; l_index < n; l_index++) {
	  vector<int> &vec_l = Vec_l[l_index];

	  if (vec_l.empty()) break;
	  
	  for (int r_index = 0; r_index < n; r_index++) {
	    vector<int> &vec_r = Vec_r[r_index];

	    if (vec_r.empty()) break;
	    
	    int op_res = matrix[vec_l[0]-1][vec_r[0]-1];
	    
	    if (used[op_res-1]) continue;
	    
	    Vec[count] = vector<int> {op_res, p, l_index, r_index};
	    used[op_res-1] = true;
	    count++;
	    
	    if (count >= n || (i == m-1 && op_res == res)) {
	      stop = true;
	      break;
	    }
	  }
	  if (stop) {break;}
	}
	if (stop) {break;}
      }
    }
  }


  // -- RESULT CHECKING --

  vector<int> res_vec;
  bool solvable = false;

  for (vector<int> vec : res_matrix[0][m-1]) {
    if (vec.empty())
      break;
    else if (vec[0] == res) {
      res_vec = vec;
      solvable = true;
      break;
    }
  }

  if (!solvable) return "0\n";

  // -- RECONSTRUCTION --
  return "1\n" + reconstruct(matrix, res_matrix, res_vec, 0, m-1) + "\n";
}

int main() {
  int n, m, result;

  ios::sync_with_stdio(0);
  cin.tie(0);

  // Ler n e m ficheiro
  n = readNumber();
  m = readNumber();

  // Ler a matriz
  vector<vector<int>> matrix(n,vector<int>(n));

  for (int i {0}; i < n; i++)
    for (int ii {0}; ii < n; ii++)
      matrix[i][ii] = readNumber();

  // Ler operação

  vector<int> operation(m);

  for (int i{0}; i<m; i++)
    operation[i] = readNumber();

  result = readNumber();
  
  cout << func(matrix, operation, result);
  
  return 0;
}
