__kernel void histogram(__read_only image2d_t inputImage,
                                 __global uint *redHistogram,
                                 __global uint *greenHistogram,
                                 __global uint *blueHistogram) {

    const int2 gid = (int2)(get_global_id(0), get_global_id(1));
    int width = get_image_width(inputImage);
    int height = get_image_height(inputImage);

    if (gid[0] < width && gid[1] < height) {
        uint4 pixel = read_imageui(inputImage, gid);
        if(pixel.x == 0 && pixel.y == 0 && pixel.z == 0)
            printf("black pixel at %d %d\n", gid[0], gid[1]);
        
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