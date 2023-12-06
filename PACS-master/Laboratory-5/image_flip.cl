__kernel void image_flip(
  __read_only image2d_t inputImage,
  __write_only image2d_t outputImage){


  const int2 gid = (int2)(get_global_id(0), get_global_id(1));
  
  // Read the pixel from the original image
  uint4 pixel = read_imageui(inputImage, gid);
  if(pixel.x == 0 && pixel.y == 0 && pixel.z == 0)
    printf("pixel is 0\n");
  
  // Calculate the corresponding index for the vertically axis flipped pixel
  int flippedX = get_image_width(inputImage) - gid.x - 1;
  if (flippedX < 0) {
    flippedX = 0; // Modify this based on your specific image dimension conditions
  }

  // Write the pixel to the flipped position in the image
  write_imageui(outputImage, (int2)(flippedX, gid.y), pixel);
}
