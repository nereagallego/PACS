#define cimg_use_jpeg
#include <iostream>
#include "CImg.h"
using namespace cimg_library;


int main(){
  CImg<unsigned char> img("image.jpg");  // Load image file "image.jpg" at object img

  std::cout << "Image width: " << img.width() << "Image height: " << img.height() << "Number of slices: " << img.depth() << "Number of channels: " << img.spectrum() << std::endl;  //dump some characteristics of the loaded image

  // Draw a blue line in the middle of the image
  unsigned char blue[] = { 0, 0, 255 };  // Blue color
  int y = img.height() / 2;  // Middle of the image
  img.draw_line(0, y, img.width(), y, blue);
  
  int i = 100;
  int j = 100;
  std::cout << std::hex << (int) img(i, j, 0, 0) << std::endl;  //print pixel value for channel 0 (red) 
  std::cout << std::hex << (int) img(i, j, 0, 1) << std::endl;  //print pixel value for channel 1 (green) 
  std::cout << std::hex << (int) img(i, j, 0, 2) << std::endl;  //print pixel value for channel 2 (blue) 
  
  img.display("My first CImg code");             // Display the image in a display window

  return 0;

}
