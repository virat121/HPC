#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main()
{
  int n;
  cout << "Enter matrix size: ";
  cin >> n;

  vector<vector<int>> A(n, vector<int>(n));
  vector<int> x(n), y_serial(n, 0), y_parallel(n, 0);

  cout << "Enter matrix A elements:\n";
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cin >> A[i][j];
    }
  }

  cout << "Enter vector x elements:\n";
  for (int i = 0; i < n; i++)
  {
    cin >> x[i];
  }

  double start = omp_get_wtime();
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      y_serial[i] += A[i][j] * x[j];
    }
  }
  double end = omp_get_wtime();

  cout << "Serial Result y = ";
  for (int i = 0; i < n; i++)
  {
    cout << y_serial[i] << " ";
  }
  cout << "\nSerial Time: " << (end - start) << " seconds\n";

  start = omp_get_wtime();

  // parallel execution
#pragma omp parallel for
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
#pragma omp atomic
      y_parallel[i] += A[i][j] * x[j];
    }
  }
  end = omp_get_wtime();

  cout << "Parallel Result y = ";
  for (int i = 0; i < n; i++)
  {
    cout << y_parallel[i] << " ";
  }
  cout << "\nParallel Time: " << (end - start) << " seconds\n";

  return 0;
}
