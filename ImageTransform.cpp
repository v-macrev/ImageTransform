#include <iostream>
#include <cmath>
#include <cstdlib>

#include "uiuc/PNG.h"
#include "uiuc/HSLAPixel.h"
#include "ImageTransform.h"

/* ******************
(Begin multi-line comment...)

Write your name and email address in the comment space here:

Name: Victor Rodrigues (Macrev)
Email: victorcruzrodrigues2003@gmail.com

(...end multi-line comment.)
******************** */

using uiuc::PNG;
using uiuc::HSLAPixel;

/**
 * Returns an image that has been transformed to grayscale.
 *
 * The saturation of every pixel is set to 0, removing any color.
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image) {
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);

      // `pixel` is a reference to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly. No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }

  return image;
}

/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its luminance is decreased by 2.5% (0.975x its original value).  At a
 * distance over 160 pixels away, the luminance will always decreased by 80%.
 * 
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, int centerX, int centerY) {
  // Calculate the distance from the center for each pixel and adjust luminance accordingly
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel &pixel = image.getPixel(x, y);
      
      // Calculate the distance from the center using Euclidean distance formula
      double distance = sqrt(pow((int)x - centerX, 2) + pow((int)y - centerY, 2));
      
      // Calculate the decrease in luminance based on the distance from the center
      double decrease = std::min(distance * 0.005, 0.8); // Decrease at most 80%
      
      // Adjust luminance
      pixel.l *= (1 - decrease);
    }
  }
  
  return image;
}

/**
 * Returns a image transformed to Illini colors.
 *
 * The hue of every pixel is set to the a hue value of either orange or
 * blue, based on if the pixel's hue value is closer to orange than blue.
 *
 * @param image A PNG object which holds the image data to be modified.
 *
 * @return The illinify'd image.
**/
PNG illinify(PNG image) {
  // Define Illini Orange and Illini Blue hue values
  double orange_hue = 11; // Illini Orange
  double blue_hue = 216;  // Illini Blue
  
  // Iterate through every pixel in the image
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel &pixel = image.getPixel(x, y);
      
      // Calculate the difference in hue from Illini Orange and Illini Blue
      double orange_diff = std::abs(pixel.h - orange_hue);
      double blue_diff = std::abs(pixel.h - blue_hue);
      
      // Choose the closer hue (Illini Orange or Illini Blue)
      if (orange_diff < blue_diff) {
        pixel.h = orange_hue;
      } else {
        pixel.h = blue_hue;
      }
    }
  }
  
  return image;
}

/**
* Returns an image that has been watermarked by another image.
*
* The luminance of every pixel of the second image is checked, if that
* pixel's luminance is 1 (100%), then the pixel at the same location on
* the first image has its luminance increased by 0.2.
*
* @param firstImage  The first of the two PNGs, which is the base image.
* @param secondImage The second of the two PNGs, which acts as the stencil.
*
* @return The watermarked image.
*/
PNG watermark(PNG firstImage, PNG secondImage) {
  // Iterate through every pixel in the overlapping region of the images
  unsigned commonWidth = std::min(firstImage.width(), secondImage.width());
  unsigned commonHeight = std::min(firstImage.height(), secondImage.height());
  for (unsigned x = 0; x < commonWidth; x++) {
    for (unsigned y = 0; y < commonHeight; y++) {
      HSLAPixel &pixel_first = firstImage.getPixel(x, y);
      HSLAPixel &pixel_second = secondImage.getPixel(x, y);
      
      // Check if the luminance of the pixel in the second image is at maximum (1.0)
      if (pixel_second.l == 1.0) {
        // Increase the luminance of the pixel in the first image by 0.2
        pixel_first.l = std::min(pixel_first.l + 0.2, 1.0); // Cap at 1.0
      }
    }
  }
  
  return firstImage;
}