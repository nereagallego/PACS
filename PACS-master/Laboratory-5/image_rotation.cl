__kernel void image_rotation(
  __read_only image2d_t inputImage,
  __write_only image2d_t outputImage,
  float angle) {

  const int2 gid = (int2)(get_global_id(0), get_global_id(1));

  // Read the pixel from the original image
  uint4 pixel = read_imageui(inputImage, gid);

  // Image dimensions
  int imageWidth = get_image_width(inputImage);
  int imageHeight = get_image_height(inputImage);

  // Coordinates of the center of the image
  float centerX = 0.5f * imageWidth;
  float centerY = 0.5f * imageHeight;

  // Coordinates of the current pixel relative to the center
  float relativeX = gid.x - centerX;
  float relativeY = gid.y - centerY;

  // Calculate the rotated coordinates using the provided rotation equations
  float rotatedX = cos(angle) * relativeX - sin(angle) * relativeY + centerX;
  float rotatedY = sin(angle) * relativeX + cos(angle) * relativeY + centerY;

  // Ensure the rotated coordinates are within the image boundaries
  int2 rotatedCoords = (int2)(clamp(rotatedX, 0.0f, imageWidth - 1.0f),
                               clamp(rotatedY, 0.0f, imageHeight - 1.0f));

  // Write the pixel to the rotated position in the output image
  write_imageui(outputImage, rotatedCoords, pixel);
}