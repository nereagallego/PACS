__kernel void histogram(__global uchar4* inputImage,
                        __global uint *redHistogram,
                        __global uint *greenHistogram,
                        __global uint *blueHistogram,
                        const int width,
                        const int height) {

    const int2 gid = (int2)(get_global_id(0), get_global_id(1));

    if (gid.x < width && gid.y < height) {
        uchar4 pixel = inputImage[gid.y * width + gid.x];
        
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