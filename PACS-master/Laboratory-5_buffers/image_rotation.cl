__kernel void image_rotation(__global unsigned char* input, __global unsigned char* output, 
    const int width, const int height, const float angle) {
    int x = get_global_id(0);
    int y = get_global_id(1);
    float centerX = width / 2.0f;
    float centerY = height / 2.0f;
    float s = sin(angle);
    float c = cos(angle);
    float newX = (x - centerX) * c - (y - centerY) * s + centerX;
    float newY = (x - centerX) * s + (y - centerY) * c + centerY;
    // bilinear interpolation based on nearest neighbors
    int x1 = floor(newX);
    int y1 = floor(newY);
    int x2 = x1 + 1;
    int y2 = y1 + 1;
    float dx = newX - x1;
    float dy = newY - y1;
    for(int i = 0; i < 3; i++) {
        int index1 = (y1 * width + x1) + i * width * height;
        int index2 = (y1 * width + x2) + i * width * height;
        int index3 = (y2 * width + x1) + i * width * height;
        int index4 = (y2 * width + x2) + i * width * height;
        float value1 = (x1 < width && y1 < height) ? input[index1] : 0;
        float value2 = (x2 < width && y1 < height) ? input[index2] : 0;
        float value3 = (x1 < width && y2 < height) ? input[index3] : 0;
        float value4 = (x2 < width && y2 < height) ? input[index4] : 0;
        float value = value1 * (1 - dx) * (1 - dy) + value2 * dx * (1 - dy) + value3 * (1 - dx) * dy + value4 * dx * dy;
        int index = (y * width + x) + i * width * height;
        if(newX >= 0 && newX < width && newY >= 0 && newY < height)
            output[index] = (unsigned char)value;
        else
            output[index] = 0;
    }
}