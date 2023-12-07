__kernel void image_rotation(
  __read_only image2d_t inputImage,
  __write_only image2d_t outputImage,
  float angle) {

  const int2 gid = (int2)(get_global_id(0), get_global_id(1));

  int imageWidth = get_image_width(inputImage);
  int imageHeight = get_image_height(inputImage);

  // Calculate the center of the input image
  float centerX = 0.5f * imageWidth;
  float centerY = 0.5f * imageHeight;

  // Calculate relative coordinates from center
  float relativeX = gid.x - centerX;
  float relativeY = gid.y - centerY;

  // Calculate rotated coordinates using the provided rotation equations
  float cosA = cos(angle);
  float sinA = sin(angle);
  float rotatedX = cosA * relativeX - sinA * relativeY + centerX;
  float rotatedY = sinA * relativeX + cosA * relativeY + centerY;

  // Calculate output pixel
  int2 rotatedCoords = (int2)(rotatedX, rotatedY);

  if (rotatedCoords.x >= 0 && rotatedCoords.x < imageWidth &&
      rotatedCoords.y >= 0 && rotatedCoords.y < imageHeight) {
    // Read the pixel from the input image and write it to the output image
    uint4 pixel = read_imageui(inputImage, rotatedCoords);
    write_imageui(outputImage, gid, pixel);
  }
}
