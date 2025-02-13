/**
 * @file BallPhysics.h
 *
 * Some functions that help computations that involve the motion of a rolling ball.
 *
 * All functions assume a linear model for ball deceleration:
 *
 *   s = v * t + 0.5 * a * t^2  with v = ball velocity, a = ball friction, s = rolled distance
 *
 * @author <A href="mailto:tlaue@uni-bremen.de">Tim Laue</A>
 */

#pragma once

#include "Platform/BHAssert.h"
#include <limits>

/**
 * @class BallPhysics
 *
 * Collection of static functions
 */
class BallPhysics
{
public:
  /**
   * Computes the position where a rolling ball is expected to stop rolling.
   * @param p The ball position (in mm)
   * @param v The ball velocity (in mm/s)
   * @param ballFriction The ball friction (negative force) (in m/s^2)
   * @return The position relative to the robot (in mm)
   */
  static Vector2f getEndPosition(const Vector2f& p, const Vector2f& v, float ballFriction)
  {
    ASSERT(ballFriction < 0.f);
    const Vector2f velInMetersPerSecond = v / 1000.f;                       // unit: meter / second
    const float tStop = (velInMetersPerSecond.norm() * -1.f) / ballFriction;  // unit: seconds
    return propagateBallPosition(p, v, tStop, ballFriction);
  }

  /**
   * Computes the position of a rolling ball in t seconds.
   * @param p The ball position (in mm)
   * @param v The ball velocity (in mm/s)
   * @t Time in seconds
   * @ballFriction The ball friction (negative force)  (in m/s^2)
   * @return The new position (in mm)
   */
  static Vector2f propagateBallPosition(const Vector2f& p, const Vector2f& v, float t, float ballFriction)
  {
    ASSERT(ballFriction < 0.f);
    if(v.norm() == 0.f)
      return p;
    const Vector2f a = computeNegativeAccelerationVector(v, ballFriction); // unit: millimeter / second^2
    return p + v * t + a * 0.5f * t * t;                                    // unit: millimeter
  }

  /**
   * Computes the position and velocity of a rolling ball in t seconds.
   * @param p The ball position (in mm)   -> updated by this method
   * @param v The ball velocity (in mm/s) -> updated by this method
   * @t Time in seconds
   * @ballFriction The ball friction (negative force)  (in m/s^2)
   */
  static void propagateBallPositionAndVelocity(Vector2f& p, Vector2f& v, float t, float ballFriction)
  {
    ASSERT(ballFriction < 0.f);
    if(v.norm() == 0.f)
      return;
    const Vector2f a = computeNegativeAccelerationVector(v, ballFriction); // unit: millimeter / second^2
    p += v * t + a * 0.5f * t * t;                                          // unit: millimeter
    v += a * t;                                                             // unit: millimeter / s
  }

  /**
   * Applies friction to position and velocity of a rolling ball in t seconds.
   * THIS METHOD DOES NOT APPLY THE VELOCITY TO THE POSITION! USE propagateBallPositionAndVelocity INSTEAD!
   * (this might appear freaky but fits the structure of the current BallLocator;
   *  the purpose of this function is to have all code that makes an assumption about
   *  the current model for rolling friction in one file)
   * @paarm p The ball position (in mm), set by this method
   * @param v The ball velocity (in mm/s), set by this method
   * @t Time in seconds
   * @ballFriction The ball friction (negative force)  (in m/s^2)
   * @return The new velocity (in mm / s)
   */
  static void applyFrictionToPositionAndVelocity(Vector2f& p, Vector2f& v, float t, float ballFriction)
  {
    ASSERT(ballFriction < 0.f);
    if(v.norm() == 0.f)
      return;
    const Vector2f a = computeNegativeAccelerationVector(v, ballFriction); // unit: millimeter / second^2
    v += a * t;                                                             // unit: millimeter / s
    p += a * t * t * 0.5f;                                                  // unit: millimeter
  }

  /**
   * Computes the time (in seconds) the ball needs to pass distance.
   * @param v The ball velocity (in mm/s)
   * @distance The distance (in mm)
   * @ballFriction The ball friction (negative force)  (in m/s^2)
   * @return std::numeric_limits<float>::max(), if ball won't make the distance with its current velocity, time otherwise
   */
  static float timeForDistance(const Vector2f& v, float distance, float ballFriction)
  {
    ASSERT(ballFriction < 0.f);
    if(getEndPosition(Vector2f::Zero(), v, ballFriction).norm() < distance)
    {
      return std::numeric_limits<float>::max();
    }
    else
    {
      // Compute time by solving the standard equation:
      // s = v * t + 0.5 * a * t^2  with v = velocity, a = ballFriction, s = distance
      const float s = distance / 1000.f;                       // unit: meter
      const Vector2f velmps = v / 1000.f;                     // unit: meter / second
      const float vb = velmps.norm() / ballFriction;            // unit: seconds
      const float radicand = vb * vb + 2.f * s / ballFriction; // unit: seconds^2
      if(radicand < 0.f)
        return std::numeric_limits<float>::max();
      else
        return (-std::sqrt(radicand) - vb);                    // unit: seconds
    }
  }

  /**
   * Calculates the velocity needed to kick the ball a certain distance
   * @param distance the distance in mm
   * @param ballFriction The ball friction (negative force)  (in m/s^2)
   * @return the velocity in mm/s
   */
  static float velocityForDistance(const float distance, const float ballFriction)
  {
    ASSERT(ballFriction < 0.0f);
    ASSERT(distance > 0.0f);
    const float sqrt2 = 1.4142135623f; //sqrt(2)
    const float b = ballFriction * 1000.0f; //unit: millimeter/second^2
    return sqrt2 * std::sqrt(-b * distance);
  }
  
  //BEGIN Added by Dortmund because the
  
  /**
   * @brief Computes a vector describing the ball acceleration (in reverse direction of the velocity).
   *
   * This method is required by the module \c BallModelProvider which needs the acceleration value without
   * adding it directly to the velocity as the method \c applyFrictionToPositionAndVelocity() does it.
   * @param v The ball velocity (in mm/s)
   * @param t Time in seconds
   * @param ballFriction The ball friction (negative force)  (in m/s^2)
   * @return The acceleration vector (in millimeter / second^2)
   * @see applyFrictionToPositionAndVelocity()
   */
  static Vector2f computeNegativeAccelerationVectorPerTimestep(const Vector2f& v, float t, float ballFriction)
  {
    ASSERT(ballFriction < 0.f);
    if (v.norm() == 0.f)
      return Vector2f::Zero();
    Vector2f acc = computeNegativeAccelerationVector(v, ballFriction) * t;
    // If the friction would accelerate the ball in the opposite direction
    // (acceleration is larger than remaining velocity), stop the ball by
    // acceleration exactly the inverse velocity.
    if (acc.norm() > v.norm())
    {
      acc = v * -1.f;
    }
    return acc;
  }
  
  //END
  
private:
  /**
   * Computes a vector describing the ball acceleration (in reverse direction of the velocity)
   * @param v The ball velocity (in mm/s)
   * @ballFriction The ball friction (negative force)  (in m/s^2)
   * @return The acceleration vector (in millimeter / second^2)
   */
  static Vector2f computeNegativeAccelerationVector(const Vector2f& v, float ballFriction)
  {
    Vector2f negVel(v * -1.f);                   // unit: millimeter / second
    negVel.normalize(std::abs(ballFriction));     // unit: meter / second^2
    negVel *= 1000.f;                             // unit: millimeter / second^2
    return negVel;
  }
};
