#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main()
{
  vector<string> sections = {"Clothing", "Gaming", "Grocery", "Stationery"};
  vector<int> serial_prices(sections.size(), 0);
  vector<int> parallel_prices(sections.size(), 0);
  vector<vector<int>> item_prices(sections.size());

  // Input collection
  cout << "Enter items and prices for each section:\n";
  for (int i = 0; i < sections.size(); ++i)
  {
    int num_items;
    cout << sections[i] << " - Number of items: ";
    cin >> num_items;

    cout << "Enter prices: ";
    item_prices[i].resize(num_items); // Resize to store prices
    for (int j = 0; j < num_items; ++j)
    {
      cin >> item_prices[i][j];
    }
  }

  // Serial execution
  cout << "\nSerial Execution:\n";
  double start_serial = omp_get_wtime();
  for (int i = 0; i < sections.size(); ++i)
  {
    for (int price : item_prices[i])
    {
      serial_prices[i] += price;
    }
  }
  double end_serial = omp_get_wtime();

  // Parallel execution
  cout << "\nParallel Execution:\n";
  double start_parallel = omp_get_wtime();
#pragma omp parallel for
  for (int i = 0; i < sections.size(); ++i)
  {
    int total = 0;
    for (int price : item_prices[i])
    {
      total += price;
    }
    parallel_prices[i] = total;
  }
  double end_parallel = omp_get_wtime();

  // Final summary
  cout << "\nResults:\n";

  int overall_serial = 0, overall_parallel = 0;

  cout << "\nSerial Prices:\n";
  for (int i = 0; i < sections.size(); ++i)
  {
    cout << sections[i] << ": " << serial_prices[i] << "\n";
    overall_serial += serial_prices[i];
  }
  cout << "Total (Serial): " << overall_serial << "\n";
  cout << "Serial Time: " << (end_serial - start_serial) << " seconds\n";

  cout << "\nParallel Prices:\n";
  for (int i = 0; i < sections.size(); ++i)
  {
    cout << sections[i] << ": " << parallel_prices[i] << "\n";
    overall_parallel += parallel_prices[i];
  }
  cout << "Total (Parallel): " << overall_parallel << "\n";
  cout << "Parallel Time: " << (end_parallel - start_parallel) << " seconds\n";

  return 0;
}
