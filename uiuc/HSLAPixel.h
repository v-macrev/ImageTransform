/**
 * @file HSLAPixel.h
 *
 * @author University of Illinois CS 225 Course Staff
 * @version 2018r1-lab1 - Updated for CS 400
 */

#pragma once

#include <iostream>
#include <sstream>

namespace uiuc {

  class HSLAPixel {
  public:
    double h; // Hue, degrees between 0 and 360
    double s; // Saturation, decimal value between 0.0 and 1.0
    double l; // Luminance, decimal value between 0.0 and 1.0
    double a; // Alpha channel (blending opacity), decimal value between 0.0 and 1.0

    // Default constructor
    HSLAPixel() : h(0), s(0), l(0), a(1) {}

    // Custom constructor
    HSLAPixel(double hue, double saturation, double luminance, double alpha)
        : h(hue), s(saturation), l(luminance), a(alpha) {}
  };

} // namespace uiuc

