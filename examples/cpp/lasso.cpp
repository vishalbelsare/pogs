#include <random>
#include <vector>

#include "pogs.hpp"
#include "timer.hpp"

// Lasso
//   minimize    (1/2) ||Ax - b||_2^2 + \lambda ||x||_1
//
// See <pogs>/matlab/examples/lasso.m for detailed description.
template <typename T>
T Lasso(size_t m, size_t n) {
  std::vector<T> A(m * n);
  std::vector<T> b(m);
  std::vector<T> x(n);
  std::vector<T> y(m);

  std::default_random_engine generator;
  std::uniform_real_distribution<T> u_dist(static_cast<T>(0),
                                           static_cast<T>(1));
  std::normal_distribution<T> n_dist(static_cast<T>(0),
                                     static_cast<T>(1));

  for (unsigned int i = 0; i < m * n; ++i)
    A[i] = 1 / static_cast<T>(n) * n_dist(generator);

  std::vector<T> x_true(n);
  for (unsigned int i = 0; i < n; ++i)
    x_true[i] = u_dist(generator) < 0.8 ? 0 : n_dist(generator);

  for (unsigned int i = 0; i < m; ++i) {
    for (unsigned int j = 0; j < n; ++j)
      b[i] += A[i * n + j] * x_true[j];
    b[i] += static_cast<T>(0.5) * n_dist(generator);
  }

  PogsData<T, T*> pogs_data(A.data(), m, n);
  pogs_data.x = x.data();
  pogs_data.y = y.data();

  T lambda = static_cast<T>(2e-2 + 5e-6 * static_cast<T>(m));

  pogs_data.f.reserve(m);
  for (unsigned int i = 0; i < m; ++i)
    pogs_data.f.emplace_back(kSquare, static_cast<T>(1), b[i]);

  pogs_data.g.reserve(n);
  for (unsigned int i = 0; i < n; ++i)
    pogs_data.g.emplace_back(kAbs, lambda);
  
  T t = timer<T>();
  Pogs(&pogs_data);

  return timer<T>() - t;
}

template double Lasso<double>(size_t m, size_t n);
//template float Lasso<float>(size_t m, size_t n);

