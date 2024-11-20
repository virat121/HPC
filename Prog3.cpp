#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
  long num_intervals = 1e8; // Number of intervals for the integration
  double pi_serial = 0.0, pi_parallel = 0.0;
  double step = 1.0 / num_intervals;

  // Serial execution to compute pi
  double start_serial = omp_get_wtime();
  for (long i = 0; i < num_intervals; ++i)
  {
    double x = (i + 0.5) * step;
    pi_serial += 4.0 / (1.0 + x * x);
  }
  pi_serial *= step;
  double end_serial = omp_get_wtime();

  // Parallel execution to compute pi
  double start_parallel = omp_get_wtime();
#pragma omp parallel
  {
    double local_sum = 0.0;

#pragma omp for
    for (long i = 0; i < num_intervals; ++i)
    {
      double x = (i + 0.5) * step;
      local_sum += 4.0 / (1.0 + x * x);
    }

#pragma omp atomic
    pi_parallel += local_sum;
  }
  pi_parallel *= step;
  double end_parallel = omp_get_wtime();

  // Output results
  cout << "Computed value of Pi (Serial): " << pi_serial << endl;
  cout << "Serial Time: " << (end_serial - start_serial) << " seconds" << endl;

  cout << "Computed value of Pi (Parallel): " << pi_parallel << endl;
  cout << "Parallel Time: " << (end_parallel - start_parallel) << " seconds" << endl;

  return 0;
}
