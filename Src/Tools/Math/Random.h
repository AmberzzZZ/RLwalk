/**
 * @file Math/Random.h
 * This contains some functions for creating random numbers.
 * @author <a href="mailto:martin.kallnik@gmx.de">Martin Kallnik</a>
 * @author Max Risler
 */

#pragma once

//#include <cstdlib>
#include <random>
#include <cstdlib>
#include <random>
#include <chrono>

static std::default_random_engine randomGenerator(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));


class Random
{
public:
  /**
   * Returns true with a probabillity of p.
   */
  static bool bernoulli(double p = 0.5);

  /**
   * Returns a normally distributed value of type T with a mean and a sigma.
   * Undefined behaviour if T is not a real type.
   */
  template<typename T = float>
  static T normal(T mean, T sigma);

  /**
   * Returns a normally distributed value of type T with zero mean and a sigma.
   * Undefined behaviour if T is not a real type.
   */
  template<typename T = float>
  static T normal(T sigma = T(1)) { return normal(T(0), sigma); }

  /**
   * Returns an uniformly distributed random floating point number in [min, max).
   */
  template<typename T = float>
  static T uniform(T min = T(0), T max = T(1));

  /**
   * Returns an uniformly distributed random integral number in [min, max].
   */
  template<typename T = int>
  static T uniformInt(T min, T max);

  /**
   * Returns an uniformly distributed random integral number in [0, max].
   */
  template<typename T = int>
  static T uniformInt(T max = T(1)) { return uniformInt(T(0), max); }

  template<typename T = float>
  static T triangular(T mean, T sigma);

  template<typename T = float>
  static T triangular(T sigma = T(1)) { return triangular(T(0), sigma); }

  template<typename T = float>
  static T triangular(T low, T mean, T high);

private:
  static std::mt19937& getGenerator();
};

inline bool Random::bernoulli(double p)
{
  std::bernoulli_distribution dist(p);
  return dist(getGenerator());
}

template<typename T>
T Random::normal(T min, T max)
{
  std::normal_distribution<T> dist(min, max);
  return dist(getGenerator());
}

template<typename T>
T Random::uniform(T min, T max)
{
  std::uniform_real_distribution<T> dist(min, max);
  return dist(getGenerator());
}

template<typename T>
T Random::uniformInt(T min, T max)
{
  std::uniform_int_distribution<T> dist(min, max);
  return dist(getGenerator());
}

template<typename T>
T Random::triangular(T mean, T sigma)
{
  const T sqrt6_2 = std::sqrt(T(6)) / T(2);
  std::uniform_real_distribution<T> dist(-sigma, sigma);
  const T randVal = dist(getGenerator()) * dist(getGenerator());
  return mean + sqrt6_2 * randVal;
}

template<typename T>
T Random::triangular(T low, T mean, T high)
{
  // See: https://en.wikipedia.org/wiki/Triangular_distribution

  const T fmean = (mean - low) / (high - low);
  const std::uniform_real_distribution<T> dist(T(0), T(1));
  const T randVal = dist(getGenerator());
  if(randVal < fmean)
    return low + std::sqrt(randVal * (high - low) * (mean - low));
  else
    return high - std::sqrt((T(1) - randVal) * (high - low) * (high - mean));
}

/**
 * The function returns a random integer number in the range of [0..n-1].
 * @param n the number of possible return values (0 ... n-1)
 * @return The random number.
 */
template<typename T, typename = std::enable_if<std::is_integral<T>::value>>
static inline T random(T n)
{
  std::uniform_int_distribution<T> rnd(0, n - 1);
  return rnd(randomGenerator);
}