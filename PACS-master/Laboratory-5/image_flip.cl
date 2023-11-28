__kernel void image_flip(
  __read_write image2d_t img){

  const int2 gid = (int2)(get_global_id(0), get_global_id(1));
  
  // Read the pixel from the original image
  uchar4 pixel = read_imageui(image, gid);

  // Calculate the corresponding index for the vertically flipped pixel
  int flippedX = get_image_width(image) - gid.x - 1;

  // Write the pixel to the flipped position in the image
  write_imageui(image, (int2)(flippedX, gid.y), pixel);
}