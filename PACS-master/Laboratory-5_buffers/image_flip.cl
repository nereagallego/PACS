__kernel void image_flip(
  __global uchar4* inputImage,
  __global uchar4* outputImage,
  const int width,
  const int height){

  const int2 gid = (int2)(get_global_id(0), get_global_id(1));
  
  // Read the pixel from the original image
  uchar4 pixel = inputImage[gid.y * width + gid.x];
  
  // Calculate the corresponding index for the vertically flipped pixel
  int flippedX = width - gid.x - 1;

  // Write the pixel to the flipped position in the image
  outputImage[gid.y * width + flippedX] = pixel;
}