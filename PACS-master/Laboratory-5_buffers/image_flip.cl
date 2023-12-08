__kernel void image_flip(
  __global unsigned char* inputImage,
  __global unsigned char* outputImage,
  const int width,
  const int height){

  const int3 gid = (int3)(get_global_id(0), get_global_id(1), get_global_id(2));
  
  // Read the pixel from the original image
  // unsigned char redPixel = inputImage[(gid.y * width + gid.x)];
  // unsigned char greenPixel = inputImage[(gid.y * width + gid.x) + width * height];
  // unsigned char bluePixel = inputImage[(gid.y * width + gid.x) + width * height * 2];
  unsigned char pixel = inputImage[(gid.y * width + gid.x) + width * height * gid.z];
  
  // Calculate the corresponding index for the vertically flipped pixel
  int flippedX = width - gid.x - 1;

  // Write the pixel to the flipped position in the image
  // outputImage[(gid.y * width + flippedX)] = redPixel;
  // outputImage[(gid.y * width + flippedX) + width * height] = greenPixel;
  // outputImage[(gid.y * width + flippedX) + width * height * 2] = bluePixel;
  outputImage[(gid.y * width + flippedX) + width * height * gid.z] = pixel;
}