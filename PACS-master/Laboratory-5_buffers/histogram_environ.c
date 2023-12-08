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

  const cl_uint num_platforms_ids = 10;				// max of allocatable platforms
  cl_platform_id platforms_ids[num_platforms_ids];		// array of platforms
  cl_uint n_platforms = 0;						// effective number of platforms in use
  const cl_uint num_devices_ids = 10;				// max of allocatable devices
  cl_device_id devices_ids[num_platforms_ids][num_devices_ids];	// array of devices
  cl_uint n_devices[num_platforms_ids];				// effective number of devices in use for each platform
	
  cl_device_id device_id;             				// compute device id 
  cl_context context;                 				// compute context
  cl_command_queue command_queue;     				// compute command queue
  
  
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

  // Select a platform with version at least 2.0
  int platform_selected = -1;
  int platform_12 = -1;
  bool found = false;
  for (int i = 0; i < n_platforms; i++){
    err = clGetPlatformInfo(platforms_ids[i], CL_PLATFORM_VERSION, t_buf*sizeof(char), str_buffer, &e_buf);
    cl_error (err, "Error: Failed to get info of the platform\n");
    if (str_buffer[7] == '1'){
      platform_12= i;
    }
    else if (str_buffer[7] >= '2'){
      platform_selected = i;
      found = true;
      printf("Platform with OpenCL >= 2.0 selected!\n");
      break;
    }
  }

  // 3. Create a context, with a device
  cl_context_properties properties[] = { CL_CONTEXT_PLATFORM, (cl_context_properties)platforms_ids[platform_selected], 0 };
  context = clCreateContext(properties, 1, devices_ids[platform_selected], NULL, NULL, &err);
  cl_error(err, "Failed to create a compute context\n");
  printf("Context created\n");

  // 4. Create a command queue
  cl_command_queue_properties proprt[] = { CL_QUEUE_PROPERTIES, CL_QUEUE_PROFILING_ENABLE, 0 };
  command_queue = clCreateCommandQueueWithProperties(context, devices_ids[platform_selected][0], proprt, &err);
  cl_error(err, "Failed to create a command queue\n");
  printf("Command queue created\n");

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

  // Create program from buffer
  cl_program program = clCreateProgramWithSource(context, 1, (const char**)&sourceCode, &fileSize, &err);
  cl_error(err, "Failed to create program with source\n");
  free(sourceCode);

  // Build the executable and check errors
  err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
  if (err != CL_SUCCESS){
    size_t len;
    char buffer[2048];

    printf("Error: Some error at building process.\n");
    clGetProgramBuildInfo(program, devices_ids[0][0], CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
    printf("%s\n", buffer);
    exit(-1);
  }

  // Create a compute kernel with the program we want to run
  cl_kernel kernel = clCreateKernel(program, "histogram", &err);
  cl_error(err, "Failed to create kernel from the program\n");
  printf("Kernel created\n");

  // Create and initialize the input and output arrays at the host memory
  CImg<unsigned char> image("lenna.jpeg");

  int width = image.width();
  int height = image.height();

  // Create OpenCL buffer memory objects
  size_t img_size = image.size(); // 4 for RGBA channels

  cl_mem in_device_object;
  in_device_object = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(unsigned char)*img_size, NULL, &err);
  cl_error(err, "Failed to create memory buffer at device 3.0\n");

  // Create OpenCL buffers for histograms
  const int histogramSize = 256;
  std::vector<unsigned int> redHistogram(histogramSize, 0);
  std::vector<unsigned int> greenHistogram(histogramSize, 0);
  std::vector<unsigned int> blueHistogram(histogramSize, 0);

  cl_mem redBuffer= clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(unsigned int) * histogramSize, redHistogram.data(), &err);
  cl_error(err, "Failed to create red histogram buffer\n");
  cl_mem greenBuffer= clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(unsigned int) * histogramSize, greenHistogram.data(), &err);
  cl_error(err, "Failed to create green histogram buffer\n");
  cl_mem blueBuffer=clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(unsigned int) * histogramSize, blueHistogram.data(), &err);
  cl_error(err, "Failed to create blue histogram buffer\n");

  // Write data into the memory object
  err = clEnqueueWriteBuffer(command_queue, in_device_object, CL_TRUE, 0, sizeof(unsigned char)*img_size, image.data(), 0, NULL, NULL);
  cl_error(err, "Failed to enqueue a write command\n");

  // Set the arguments to our compute kernel
  err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &in_device_object);
  cl_error(err, "Failed to set kernel arguments\n");
  err = clSetKernelArg(kernel, 1, sizeof(cl_mem), &redBuffer);
  cl_error(err, "Failed to set kernel arguments\n");
  err = clSetKernelArg(kernel, 2, sizeof(cl_mem), &greenBuffer);
  cl_error(err, "Failed to set kernel arguments\n");
  err = clSetKernelArg(kernel, 3, sizeof(cl_mem), &blueBuffer);
  cl_error(err, "Failed to set kernel arguments\n");
  err = clSetKernelArg(kernel, 4, sizeof(int), &width);
  cl_error(err, "Failed to set kernel arguments\n");
  err = clSetKernelArg(kernel, 5, sizeof(int), &height);
  cl_error(err, "Failed to set kernel arguments\n");

  // Launch kernel
  const size_t global_size[2] = {static_cast<size_t>(image.width()), static_cast<size_t>(image.height())};

  start_k = clock();

  err = clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL, global_size, NULL, 0, NULL, NULL);
  cl_error(err, "Failed to launch kernel to the device\n");
  printf("Kernel launched\n");

  // clFinish(command_queue);

  err = clEnqueueReadBuffer(command_queue, redBuffer, CL_TRUE, 0, sizeof(unsigned int) *
                            histogramSize, redHistogram.data(), 0, NULL, NULL);
  cl_error(err, "Failed to read red histogram from the device\n");
  err = clEnqueueReadBuffer(command_queue, greenBuffer, CL_TRUE, 0, sizeof(unsigned int) 
                            * histogramSize, greenHistogram.data(), 0, NULL, NULL);
  cl_error(err, "Failed to read green histogram from the device\n");
  err = clEnqueueReadBuffer(command_queue, blueBuffer, CL_TRUE, 0, sizeof(unsigned int) *
                            histogramSize, blueHistogram.data(), 0, NULL, NULL);
  cl_error(err, "Failed to read blue histogram from the device\n");
  printf("Data read from device\n");

  end_k = clock();
  double time_kernel = ((double) (end_k - start_k)) / CLOCKS_PER_SEC;

  // Bandwidth to/from memory to/from kernel. Amount data interchanged with memory for every second
  double bandwidth = (double) (image.width() * image.height() * 4 * sizeof(unsigned char)*2) / time_kernel;

  // Trhoughput of the kernel in terms of number of pixels processed per second
  double throughput = (double) (image.width() * image.height()) / time_kernel;

  // Memory footprint
  // Local memory footprint
  size_t local_memory_footprint = (size_t) image.width() * image.height() * 4 * sizeof(unsigned char) + histogramSize*3*sizeof(unsigned int) + 2 * sizeof(int) + sizeof(size_t); // image + histogram buffers
  size_t kernel_memory_footprint_in = 0.0;
  size_t kernel_memory_footprint_hist = 0.0;
  err = clGetMemObjectInfo(in_device_object, CL_MEM_SIZE, sizeof(kernel_memory_footprint_in), &kernel_memory_footprint_in, NULL);
  cl_error(err, "Failed to get memory object info\n");
  err = clGetMemObjectInfo(redBuffer, CL_MEM_SIZE, sizeof(kernel_memory_footprint_hist), &kernel_memory_footprint_hist, NULL);
  cl_error(err, "Failed to get memory object info\n");
  size_t kernel_memory_footprint_out = kernel_memory_footprint_hist * 3;

  size_t memory_footprint = local_memory_footprint + kernel_memory_footprint_in + kernel_memory_footprint_out;

  // Print histograms
  // for (int i = 0; i < histogramSize; i++){
  //   printf("Red[%d]: %d\n", i, redHistogram[i]);
  //   printf("Green[%d]: %d\n", i, greenHistogram[i]);
  //   printf("Blue[%d]: %d\n", i, blueHistogram[i]);
  // }

  // Plot histograms
  plotHistogram(redHistogram, greenHistogram, blueHistogram);

  // Release OpenCL resources

  clReleaseProgram(program);
  clReleaseKernel(kernel);
  clReleaseCommandQueue(command_queue);
  clReleaseContext(context);

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

