#include <iostream>
using namespace std;

int mod_inv(int a,int m) {
  return a <= 1 ? a : m - (long long)(m/a) * mod_inv(m % a, m) % m;
}