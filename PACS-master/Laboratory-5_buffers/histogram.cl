__kernel void histogram(__global unsigned char* inputImage,
                        __global unsigned int *redHistogram,
                        __global unsigned int *greenHistogram,
                        __global unsigned int *blueHistogram,
                        const int width,
                        const int height) {

    const int2 gid = (int2)(get_global_id(0), get_global_id(1));

    if (gid.x < width && gid.y < height) {
        
        // Extracting individual color channels
        const unsigned char red = inputImage[(gid.y * width + gid.x)];
        const unsigned char green = inputImage[(gid.y * width + gid.x) + width * height];
        const unsigned char blue = inputImage[(gid.y * width + gid.x) + 2 * width * height];

        // Incrementing histogram bins
        atomic_inc(&redHistogram[red]);
        atomic_inc(&greenHistogram[green]);
        atomic_inc(&blueHistogram[blue]);
    }
}