////////////////////////////////////////////////////////////////////
//File: histogram_environ.c
//
//Description: histogram using OpenCL
//
// 
////////////////////////////////////////////////////////////////////
#define cimg_use_jpeg
#include "CImg.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <vector>
#ifdef __APPLE__
  #include <OpenCL/opencl.h>
#else
  #include <CL/cl.h>
#endif

using namespace cimg_library;
  
// check error, in such a case, it exits

void cl_error(cl_int code, const char *string){
	if (code != CL_SUCCESS){
		printf("%d - %s\n", code, string);
	    exit(-1);
	}
}

void plotHistogram(const std::vector<unsigned int>& redHistogram,
                   const std::vector<unsigned int>& greenHistogram,
                   const std::vector<unsigned int>& blueHistogram) {

    const int histogramSize = redHistogram.size();
    const int histWidth = 2; // Width of each histogram bar
    const int histHeight = 400; // Height of histogram image
    const int margin = 40; // Margin between histograms and window edge
    const int imageSize = histogramSize * histWidth + 2 * margin;

    // Create a new image to display histograms
    CImg<unsigned char> histImage(imageSize, histHeight + 2 * margin, 1, 3, 255);

    // Define colors
    const unsigned char red[] = {255, 0, 0};
    const unsigned char green[] = {0, 255, 0};
    const unsigned char blue[] = {0, 0, 255};

    // Plot red histogram
    for (int i = 0; i < histogramSize; ++i) {
        const int redHeight = histHeight * redHistogram[i] / (*std::max_element(redHistogram.begin(), redHistogram.end()));
        histImage.draw_rectangle(margin + i * histWidth, histHeight + margin - redHeight, margin + (i + 1) * histWidth - 1, histHeight + margin - 1, red);
    }

    // Plot green histogram
    for (int i = 0; i < histogramSize; ++i) {
        const int greenHeight = histHeight * greenHistogram[i] / (*std::max_element(greenHistogram.begin(), greenHistogram.end()));
        histImage.draw_rectangle(margin + i * histWidth, histHeight + margin - greenHeight, margin + (i + 1) * histWidth - 1, histHeight + margin - 1, green);
    }
    
    // Plot blue histogram
    for (int i = 0; i < histogramSize; ++i) {
        const int blueHeight = histHeight * blueHistogram[i] / (*std::max_element(blueHistogram.begin(), blueHistogram.end()));
        histImage.draw_rectangle(margin + i * histWidth, histHeight + margin - blueHeight, margin + (i + 1) * histWidth - 1, histHeight + margin - 1, blue);
    }

    histImage.save("histogram.jpeg");

    // Display histogram image
    CImgDisplay disp(histImage, "RGB Histograms");
    while (!disp.is_closed()) {
        disp.wait();
    }
}
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{

  clock_t start, end;
  clock_t start_k, end_k;
  double cpu_time_used, cpu_time_used_k;
  start = clock();

  int err;                            	// error code returned from api calls
  size_t t_buf = 1000;			// size of str_buffer
  char str_buffer[t_buf];		// auxiliary buffer	
  size_t e_buf;				// effective size of str_buffer in use
	    
  size_t local_size;                       	// local domain size for our calculation

  const int number_platforms_used = 2;			// number of platforms to use
  const int number_images = 5000;				// number of images to process

  double time_kernel = 0;					// time to execute the kernel

  const cl_uint num_platforms_ids = 10;				// max of allocatable platforms
  cl_platform_id platforms_ids[num_platforms_ids];		// array of platforms
  cl_uint n_platforms = 0;						// effective number of platforms in use
  const cl_uint num_devices_ids = 10;				// max of allocatable devices
  cl_device_id devices_ids[num_platforms_ids][num_devices_ids];	// array of devices
  cl_uint n_devices[num_platforms_ids];				// effective number of devices in use for each platform
	
  cl_device_id device_id;             				// compute device id 
  cl_context context[number_platforms_used];                 				// compute context
  cl_command_queue command_queue[number_platforms_used];     				// compute command queue
  
  
  cl_ulong host_timer_resolution;					// host timer resolution

  // 1. Scan the available platforms:
  err = clGetPlatformIDs (num_platforms_ids, platforms_ids, &n_platforms);
  cl_error(err, "Error: Failed to Scan for Platforms IDs");
  printf("Number of available platforms: %d\n\n", n_platforms);

  for (int i = 0; i < n_platforms; i++){
    err= clGetPlatformInfo(platforms_ids[i], CL_PLATFORM_NAME, t_buf*sizeof(char), str_buffer, &e_buf);
    cl_error (err, "Error: Failed to get info of the platform\n");
    printf( "\t[%d]-Platform Name: %s\n", i, str_buffer);
    // print host_timer_resolution
    err = clGetPlatformInfo(platforms_ids[i], CL_PLATFORM_VENDOR, t_buf*sizeof(char), str_buffer, &e_buf);
    cl_error (err, "Error: Failed to get info of the platform\n");
    printf("\t[%d]-Platform Vendor: %s\n", i, str_buffer);
    // print vendor
    // err = clGetPlatformInfo(platforms_ids[i], CL_PLATFORM_HOST_TIMER_RESOLUTION, sizeof(cl_ulong), &host_timer_resolution, NULL);
    // cl_error (err, "Error: Failed to get info of the platform\n");
    // printf("\t[%d]-Platform Host Timer Resolution: %d\n", i, host_timer_resolution);
    // // print version
    err = clGetPlatformInfo(platforms_ids[i], CL_PLATFORM_VERSION, t_buf*sizeof(char), str_buffer, &e_buf);
    cl_error (err, "Error: Failed to get info of the platform\n");
    printf("\t[%d]-Platform Version: %s\n", i, str_buffer);
  }
  printf("\n");
  // ***Task***: print on the screen the name, host_timer_resolution, vendor, versionm, ...

  // 2. Scan for devices in each platform
  for (int i = 0; i < n_platforms; i++){
    err = clGetDeviceIDs( platforms_ids[i], CL_DEVICE_TYPE_ALL , num_devices_ids, devices_ids[i], &(n_devices[i]));
    cl_error(err, "Error: Failed to Scan for Devices IDs");
    printf("\t[%d]-Platform. Number of available devices: %d\n", i, n_devices[i]);

    for(int j = 0; j < n_devices[i]; j++){
      err = clGetDeviceInfo(devices_ids[i][j], CL_DEVICE_NAME, sizeof(str_buffer), &str_buffer, NULL);
      cl_error(err, "clGetDeviceInfo: Getting device name");
      printf("\t\t [%d]-Platform [%d]-Device CL_DEVICE_NAME: %s\n", i, j,str_buffer);

      cl_uint max_compute_units_available;
      err = clGetDeviceInfo(devices_ids[i][j], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(max_compute_units_available), &max_compute_units_available, NULL);
      cl_error(err, "clGetDeviceInfo: Getting device max compute units available");
      printf("\t\t [%d]-Platform [%d]-Device CL_DEVICE_MAX_COMPUTE_UNITS: %d\n\n", i, j, max_compute_units_available);

      // print the cache size
      cl_ulong cache_size;
      err = clGetDeviceInfo(devices_ids[i][j], CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, sizeof(cache_size), &cache_size, NULL);
      cl_error(err, "clGetDeviceInfo: Getting device cache size");
      printf("\t\t [%d]-Platform [%d]-Device CL_DEVICE_GLOBAL_MEM_CACHE_SIZE: %lu\n", i, 0, cache_size);

      // print the global mem size
      cl_ulong global_mem_size;
      err = clGetDeviceInfo(devices_ids[i][j], CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(global_mem_size), &global_mem_size, NULL);
      cl_error(err, "clGetDeviceInfo: Getting device global mem size");
      printf("\t\t [%d]-Platform [%d]-Device CL_DEVICE_GLOBAL_MEM_SIZE: %lu\n", i, 0, global_mem_size);

      // print the local mem size
      cl_ulong local_mem_size;
      err = clGetDeviceInfo(devices_ids[i][j], CL_DEVICE_LOCAL_MEM_SIZE, sizeof(local_mem_size), &local_mem_size, NULL);
      cl_error(err, "clGetDeviceInfo: Getting device local mem size");
      printf("\t\t [%d]-Platform [%d]-Device CL_DEVICE_LOCAL_MEM_SIZE: %lu\n", i, 0, local_mem_size);

      // print the max work group size
      size_t max_work_group_size;
      err = clGetDeviceInfo(devices_ids[i][j], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(max_work_group_size), &max_work_group_size, NULL);
      cl_error(err, "clGetDeviceInfo: Getting device max work group size");
      printf("\t\t [%d]-Platform [%d]-Device CL_DEVICE_MAX_WORK_GROUP_SIZE: %d\n", i, 0, max_work_group_size);

      // print the profiling timer resolution
      size_t profiling_timer_resolution;
      err = clGetDeviceInfo(devices_ids[i][j], CL_DEVICE_PROFILING_TIMER_RESOLUTION, sizeof(profiling_timer_resolution), &profiling_timer_resolution, NULL);
      cl_error(err, "clGetDeviceInfo: Getting device profiling timer resolution");
      printf("\t\t [%d]-Platform [%d]-Device CL_DEVICE_PROFILING_TIMER_RESOLUTION: %d\n", i, 0, profiling_timer_resolution);
    }
  }	
  // ***Task***: print on the screen the cache size, global mem size, local memsize, max work group size, profiling timer resolution and ... of each device

  // Select two platforms with version at least 2.0
  int platforms_selected[number_platforms_used] = {-1, -1};
  int found = 0;
  for (int i = 0; i < n_platforms; i++){
    err = clGetPlatformInfo(platforms_ids[i], CL_PLATFORM_VERSION, t_buf*sizeof(char), str_buffer, &e_buf);
    cl_error (err, "Error: Failed to get info of the platform\n");
    if (str_buffer[7] >= '2'){
      platforms_selected[found] = i;
      found++;
      printf("Platform with OpenCL >= 2.0 selected!\n");
      if (found == number_platforms_used) {
        break;
      }
    }
  }

  if (found < number_platforms_used){
    printf("Two platforms with OpenCL >= 2.0 not found.\n");
    exit(-1);
  }

  // Select the first device of each platform
  int devices_selected[number_platforms_used] = {-1, -1};
  for (int i = 0; i < number_platforms_used; i++){
    devices_selected[i] = 0;
  }

  // Create two contexts and command queues, one for each platform and device
  cl_command_queue_properties proprt[] = { CL_QUEUE_PROPERTIES, CL_QUEUE_PROFILING_ENABLE, 0 };
  for (int i = 0; i < number_platforms_used; i++) {
    // Create a context for the platform
    cl_context_properties properties[] = { CL_CONTEXT_PLATFORM, (cl_context_properties)platforms_ids[platforms_selected[i]], 0 };
    context[i] = clCreateContext(properties, 1, devices_ids[platforms_selected[i]], NULL, NULL, &err);
    cl_error(err, "Failed to create a compute context\n");
    printf("Context for platform %d created\n", i);

    // Create a command queue for the device
    command_queue[i] = clCreateCommandQueueWithProperties(context[i], devices_ids[platforms_selected[i]][devices_selected[i]], proprt, &err);
    cl_error(err, "Failed to create a command queue\n");
    printf("Command queue for platform %d created\n", i);
  }

  // Calculate size of the file
  FILE *fileHandler = fopen("histogram.cl", "r");
  if (fileHandler == NULL){
    printf("Failed to open kernel file\n");
    exit(-1);
  }
  fseek(fileHandler, 0, SEEK_END);
  size_t fileSize = ftell(fileHandler);
  rewind(fileHandler);

  // Read kernel source into buffer
  char * sourceCode = (char*) malloc(fileSize + 1);
  sourceCode[fileSize] = '\0';
  fread(sourceCode, sizeof(char), fileSize, fileHandler);
  fclose(fileHandler);

  cl_program program[number_platforms_used];

  for (int i = 0; i < number_platforms_used; i++) {
      // Create program from buffer for each context
      program[i] = clCreateProgramWithSource(context[i], 1, (const char**)&sourceCode, &fileSize, &err);
      if (err != CL_SUCCESS) {
          fprintf(stderr, "Failed to create program with source for context %d\n", i);
          exit(1);
      }
  }

  free(sourceCode);

  for (int i = 0; i < number_platforms_used; i++) {
    // Build the executable for each program and check errors
    err = clBuildProgram(program[i], 0, NULL, NULL, NULL, NULL);
    if (err != CL_SUCCESS){
        size_t len;
        char buffer[2048];

        printf("Error: Some error at building process for program %d.\n", i);
        clGetProgramBuildInfo(program[i], devices_ids[i][devices_selected[i]], CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
        printf("%s\n", buffer);
        exit(-1);
    }
  }

  // Create a compute kernel with the program we want to run
  cl_kernel kernel[number_platforms_used];
  for (int i = 0; i < number_platforms_used; i++) {
      kernel[i] = clCreateKernel(program[i], "histogram", &err);
      cl_error(err, "Failed to create kernel from the program\n");
      printf("Kernel %d created\n", i);
  }

  // Allocate memory for 5000 pointers to images
  CImg<unsigned char>** images = (CImg<unsigned char>**)malloc(number_images * sizeof(CImg<unsigned char>*));
  // Check if memory allocation was successful
  if (images == NULL) {
      fprintf(stderr, "Failed to allocate memory for image pointers\n");
      exit(1);
  }

  CImg<unsigned char> img("lenna.jpeg");
  // Initialize each pointer with a new image
  for (int i = 0; i < number_images; i++) {
    // images[i] = new_image("lenna.jpeg");
    images[i] = new CImg<unsigned char>(img);
    if (images[i] == NULL) {
        fprintf(stderr, "Failed to create new image for pointer %d\n", i);
        exit(1);
    }
  }

  // Get the properties from the first image
  int width = images[0]->width();
  int height = images[0]->height();
  int spectrum = images[0]->spectrum();

  // Create OpenCL buffer memory objects
  size_t img_size = width * height * spectrum;

  const int histogramSize = 256;
 
  std::vector<std::vector<unsigned int>> redHistograms(number_images, std::vector<unsigned int>(histogramSize, 0));
  std::vector<std::vector<unsigned int>> greenHistograms(number_images, std::vector<unsigned int>(histogramSize, 0));
  std::vector<std::vector<unsigned int>> blueHistograms(number_images, std::vector<unsigned int>(histogramSize, 0));

  // Create ONE memory buffers for each context
  cl_mem in_device_object[number_images];
  cl_mem redBuffer[number_images];
  cl_mem greenBuffer[number_images];
  cl_mem blueBuffer[number_images];
  for (int i = 0; i < number_images; i++) {
      int device_index = i % number_platforms_used; // Use this to alternate between the two devices 

      in_device_object[i] = clCreateBuffer(context[device_index], CL_MEM_READ_ONLY, sizeof(unsigned char)*img_size, NULL, &err);
      cl_error(err, "Failed to create memory buffer at device\n");

      redBuffer[i] = clCreateBuffer(context[device_index], CL_MEM_READ_WRITE, sizeof(unsigned int) * histogramSize, NULL, &err);
      cl_error(err, "Failed to create red histogram buffer\n");
      greenBuffer[i] = clCreateBuffer(context[device_index], CL_MEM_READ_WRITE, sizeof(unsigned int) * histogramSize, NULL, &err);
      cl_error(err, "Failed to create green histogram buffer\n");
      blueBuffer[i] = clCreateBuffer(context[device_index], CL_MEM_READ_WRITE, sizeof(unsigned int) * histogramSize, NULL, &err);
      cl_error(err, "Failed to create blue histogram buffer\n");

      // Write data into the memory object
      err = clEnqueueWriteBuffer(command_queue[device_index], in_device_object[i], CL_TRUE, 0, sizeof(unsigned char)*img_size, images[i]->data(), 0, NULL, NULL);
      cl_error(err, "Failed to enqueue a write command\n");

      // Set the arguments to our compute kernel
      err = clSetKernelArg(kernel[device_index], 0, sizeof(cl_mem), &in_device_object[i]);
      cl_error(err, "Failed to set kernel arguments\n");
      err = clSetKernelArg(kernel[device_index], 1, sizeof(cl_mem), &redBuffer[i]);
      cl_error(err, "Failed to set kernel arguments\n");
      err = clSetKernelArg(kernel[device_index], 2, sizeof(cl_mem), &greenBuffer[i]);
      cl_error(err, "Failed to set kernel arguments\n");
      err = clSetKernelArg(kernel[device_index], 3, sizeof(cl_mem), &blueBuffer[i]);
      cl_error(err, "Failed to set kernel arguments\n");
      err = clSetKernelArg(kernel[device_index], 4, sizeof(int), &width);
      cl_error(err, "Failed to set kernel arguments\n");
      err = clSetKernelArg(kernel[device_index], 5, sizeof(int), &height);
      cl_error(err, "Failed to set kernel arguments\n");

      // Launch kernel
      const size_t global_size[2] = {static_cast<size_t>(width), static_cast<size_t>(height)};

      start_k = clock();

      err = clEnqueueNDRangeKernel(command_queue[device_index], kernel[device_index], 2, NULL, global_size, NULL, 0, NULL, NULL);
      cl_error(err, "Failed to launch kernel to the device\n");
      printf("Kernel launched\n");  

      err = clEnqueueReadBuffer(command_queue[device_index], redBuffer[i], CL_TRUE, 0, sizeof(unsigned int) * histogramSize, redHistograms[i].data(), 0, NULL, NULL);
      cl_error(err, "Failed to read red histogram from the device\n");
      err = clEnqueueReadBuffer(command_queue[device_index], greenBuffer[i], CL_TRUE, 0, sizeof(unsigned int) * histogramSize, greenHistograms[i].data(), 0, NULL, NULL);
      cl_error(err, "Failed to read green histogram from the device\n");
      err = clEnqueueReadBuffer(command_queue[device_index], blueBuffer[i], CL_TRUE, 0, sizeof(unsigned int) *            histogramSize, blueHistograms[i].data(), 0, NULL, NULL);
      cl_error(err, "Failed to read blue histogram from the device\n");
      printf("Data read from device\n");

      end_k = clock();  
      time_kernel += ((double) (end_k - start_k)) / CLOCKS_PER_SEC;                                          
  }
  

  // Plot histograms
  plotHistogram(redHistograms[1234], greenHistograms[1234], blueHistograms[1234]);

  // double time_kernel = ((double) (end_k - start_k)) / CLOCKS_PER_SEC;

  // Bandwidth to/from memory to/from kernel. Amount data interchanged with memory for every second
  double bandwidth = (double) (sizeof(unsigned char)*img_size) + (sizeof(unsigned int) * histogramSize * 3) + 2 * sizeof(int) / time_kernel;

  // Trhoughput of the kernel in terms of number of pixels processed per second
  double throughput = (double) (width*height) / time_kernel;

  // Memory footprint
  // Local memory footprint
  size_t local_memory_footprint = (size_t) (sizeof(unsigned char)*img_size) + histogramSize*3*sizeof(unsigned int) + 2 * sizeof(int); // image + histogram buffers
  size_t kernel_memory_footprint_in = 0.0;
  size_t kernel_memory_footprint_hist = 0.0;
  err = clGetMemObjectInfo(in_device_object[0], CL_MEM_SIZE, sizeof(kernel_memory_footprint_in), &kernel_memory_footprint_in, NULL);
  cl_error(err, "Failed to get memory object info\n");
  err = clGetMemObjectInfo(redBuffer[0], CL_MEM_SIZE, sizeof(kernel_memory_footprint_hist), &kernel_memory_footprint_hist, NULL);
  cl_error(err, "Failed to get memory object info\n");
  size_t kernel_memory_footprint_out = kernel_memory_footprint_hist * 3 * number_images;

  size_t memory_footprint = local_memory_footprint + kernel_memory_footprint_in * number_images+ kernel_memory_footprint_out + 2 * sizeof(int);

  // Print histograms
  // for (int i = 0; i < histogramSize; i++){
  //   printf("Red[%d]: %d\n", i, redHistogram[i]);
  //   printf("Green[%d]: %d\n", i, greenHistogram[i]);
  //   printf("Blue[%d]: %d\n", i, blueHistogram[i]);
  // }

  // Release OpenCL resources

  for (int i = 0; i < number_platforms_used; i++) {
      clReleaseProgram(program[i]);
      clReleaseKernel(kernel[i]);
      clReleaseCommandQueue(command_queue[i]);
      clReleaseContext(context[i]);
  }

  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  cpu_time_used_k = ((double) (end_k - start_k)) / CLOCKS_PER_SEC;

  printf("Kernel time: %f\n", cpu_time_used_k);
  printf("Overall time: %f\n", cpu_time_used);
  printf("Bandwidth: %f\n", bandwidth);
  printf("Throughput: %f\n", throughput);
  printf("Memory footprint: %zu\n", memory_footprint);

  return 0;
}

