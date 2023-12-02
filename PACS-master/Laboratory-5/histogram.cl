__kernel void calculateHistogram(__read_only image2d_t inputImage,
                                 __global uint *redHistogram,
                                 __global uint *greenHistogram,
                                 __global uint *blueHistogram) {

    const int x = get_global_id(0);
    const int y = get_global_id(1);
    int width = get_image_width(inputImage);
    int height = get_image_height(inputImage);

    if (x < width && y < height) {
        int4 pixel = read_imagei(inputImage, CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP_TO_EDGE, (int2)(x, y));

        // Extracting individual color channels
        uint red = pixel.x;
        uint green = pixel.y;
        uint blue = pixel.z;

        // Incrementing histogram bins
        atomic_inc(&redHistogram[red]);
        atomic_inc(&greenHistogram[green]);
        atomic_inc(&blueHistogram[blue]);
    }
}