__kernel void image_flip(
  __read_only image2d_t inputImage,
  __write_only image2d_t outputImage){


  const int2 gid = (int2)(get_global_id(0), get_global_id(1));
  // printf("gid.x = %d, gid.y = %d\n", gid.x, gid.y);
  
  // Read the pixel from the original image
  uint4 pixel = read_imageui(inputImage, gid);
  // printf("pixel.r = %d, pixel.g = %d, pixel.b = %d, pixel.a = %d\n", pixel.x, pixel.y, pixel.z, pixel.w);
  // printf("pixel.x = %d, pixel.y = %d, pixel.z = %d, pixel.w = %d\n", pixel.x, pixel.y, pixel.z, pixel.w);

  // Calculate the corresponding index for the vertically flipped pixel
  int flippedX = get_image_width(inputImage) - gid.x - 1;
  // printf("get_image_width(inputImage) = %d\n", get_image_width(inputImage));
  // printf("flippedX = %d\n", flippedX);

  // Write the pixel to the flipped position in the image
  write_imageui(outputImage, (int2)(flippedX, gid.y), pixel);
  // printf("write_imageui\n");
}
