__kernel void image_rotation(
  __global uchar4* inputImage,
  __global uchar4* outputImage,
  const int imageWidth,
  const int imageHeight,
  const float angle) {

  const int2 gid = (int2)(get_global_id(0), get_global_id(1));

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
    uchar4 pixel = inputImage[rotatedCoords.y * imageWidth + rotatedCoords.x];
    outputImage[gid.y * imageWidth + gid.x] = pixel;
  }
}

// kernel void image_rotation(global unsigned char* input, __global unsigned char* output, 
//   const int width, const int height, const float angle) {
//   int x = get_global_id(0);
//   int y = get_global_id(1);
//   float centerX = width / 2.0f;
//   float centerY = height / 2.0f;
//   float s = sin(angle);
//   float c = cos(angle);
//   int newX = (int)((x - centerX) * c - (y - centerY) * s + centerX);
//   int newY = (int)((x - centerX) * s + (y - centerY) * c + centerY);
//   if(newX >= 0 && newX < width && newY >= 0 && newY < height) {
//       output[(newY * width + newX) * 3] = input[(y * width + x) * 3];
//       output[(newY * width + newX) * 3 + 1] = input[(y * width + x) * 3 + 1];
//       output[(newY * width + newX) * 3 + 2] = input[(y * width + x) * 3 + 2];
//   }
// }