#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <string.h>
#include <math.h>

using namespace std;

double module(pair<float, float> v1) {
  return sqrt(v1.first*v1.first + v1.second*v1.second);
}

pair<float, float> normalize(pair<float, float> v1) {
  pair<float, float> v;
  v.first = v1.first/module(v1);
  v.second = v1.second/module(v1);
  return v;
}

int scalar_product(pair<int, int> v1, pair<int, int> v2) {
  return v1.first*v2.first + v1.second*v2.second;
}

pair<int, int> product_by_factor(pair<int, int> v1, int factor) {
  pair<int, int> v;
  v.first = v1.first*factor;
  v.second = v1.second*factor;
  return v;
}

pair<int, int> substract(pair<int, int> v1, pair<int, int> v2) {
  pair<int, int> v;
  v.first = v1.first - v2.first;
  v.second = v1.second - v2.second;
  return v;
}

pair<int, int> reflect(pair<int, int> v1, pair<int, int> n) {
  return substract(v1, product_by_factor(n, 2*scalar_product(v1, n)));
}
