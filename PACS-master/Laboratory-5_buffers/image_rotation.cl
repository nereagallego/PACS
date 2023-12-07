__kernel void image_rotation(__global unsigned char* input, __global unsigned char* output, 
    const int width, const int height, const float angle) {
    int x = get_global_id(0);
    int y = get_global_id(1);
    float centerX = width / 2.0f;
    float centerY = height / 2.0f;
    float s = sin(angle);
    float c = cos(angle);
    int newX = (int)((x - centerX) * c - (y - centerY) * s + centerX);
    int newY = (int)((x - centerX) * s + (y - centerY) * c + centerY);
    if(newX >= 0 && newX < width && newY >= 0 && newY < height) {
        int index = (newY * width + newX) ;
        output[index] = input[(y * width + x)];
        output[index + width * height] = input[(y * width + x) + width * height];
        output[index + 2 * width * height] = input[(y * width + x) + width * height * 2];
    } else {
        int index = (y * width + x);
        output[index] = 0;
        output[index + width * height] = 0;
        output[index + 2 * width * height] = 0;
    }
}
