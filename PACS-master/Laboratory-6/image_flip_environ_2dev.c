 
////////////////////////////////////////////////////////////////////
//File: image_flip_environ.c
//
//Description: image flip using OpenCL
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
#include <time.h>
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
	    
                        	// global domain size for our calculation
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
    // print version
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

      size_t max_work_item_dimensions;
      err = clGetDeviceInfo(devices_ids[i][j], CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(max_work_item_dimensions), &max_work_item_dimensions, NULL);
      cl_error(err, "clGetDeviceInfo: Getting device max work item dimensions");
      printf("\t\t [%d]-Platform [%d]-Device CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS: %d\n", i, 0, max_work_item_dimensions);

      // print the profiling timer resolution
      size_t profiling_timer_resolution;
      err = clGetDeviceInfo(devices_ids[i][j], CL_DEVICE_PROFILING_TIMER_RESOLUTION, sizeof(profiling_timer_resolution), &profiling_timer_resolution, NULL);
      cl_error(err, "clGetDeviceInfo: Getting device profiling timer resolution");
      printf("\t\t [%d]-Platform [%d]-Device CL_DEVICE_PROFILING_TIMER_RESOLUTION: %d\n", i, 0, profiling_timer_resolution);
    }
  }	
  // ***Task***: print on the screen the cache size, global mem size, local memsize, max work group size, profiling timer resolution and ... of each device

  // Select two platforms with version at least 2.0
  int platforms_selected[2] = {-1, -1};
  int found = 0;
  for (int i = 0; i < n_platforms; i++){
    err = clGetPlatformInfo(platforms_ids[i], CL_PLATFORM_VERSION, t_buf*sizeof(char), str_buffer, &e_buf);
    cl_error (err, "Error: Failed to get info of the platform\n");
    if (str_buffer[7] >= '2'){
      platforms_selected[found] = i;
      found++;
      printf("Platform with OpenCL >= 2.0 selected!\n");
      if (found == 2) {
        break;
      }
    }
  }

  if (found < 2){
    printf("Two platforms with OpenCL >= 2.0 not found.\n");
    exit(-1);
  }

  // Select the first device of each platform
  int devices_selected[2] = {-1, -1};
  for (int i = 0; i < 2; i++){
    devices_selected[i] = 0;
  }
  

  // Create two contexts and command queues, one for each platform and device
  cl_context context[2];
  cl_command_queue command_queue[2];
  cl_command_queue_properties proprt[] = { CL_QUEUE_PROPERTIES, CL_QUEUE_PROFILING_ENABLE, 0 };

  for (int i = 0; i < 2; i++) {
    // Create a context for the platform
    cl_context_properties properties[] = { CL_CONTEXT_PLATFORM, (cl_context_properties)platforms_ids[platforms_selected[i]], 0 };
    context[i] = clCreateContext(properties, 1, &devices_ids[devices_selected[i]], NULL, NULL, &err);
    cl_error(err, "Failed to create a compute context\n");
    printf("Context for platform %d created\n", i);

    // Create a command queue for the device
    command_queue[i] = clCreateCommandQueueWithProperties(context[i], devices_ids[devices_selected[i]], proprt, &err);
    cl_error(err, "Failed to create a command queue\n");
    printf("Command queue for platform %d created\n", i);
}


  // Calculate size of the file
  FILE *fileHandler = fopen("image_flip.cl", "r");
  if (fileHandler ==   NULL){
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
  cl_kernel kernel = clCreateKernel(program, "image_flip", &err);
  cl_error(err, "Failed to create kernel from the program\n");
  printf("Kernel created\n");

  // Replicate the image 5000 times
  std::vector<CImg<unsigned char>> images(5000, CImg<unsigned char>("lenna.jpeg"));

  // Get the properties from the first image
  int width = images[0].width();
  int height = images[0].height();
  int spectrum = images[0].spectrum();

  // Create OpenCL buffer memory objects
  size_t img_size = width * height * spectrum;

  // Create two memory buffers for each context
  cl_mem in_device_object[2];
  cl_mem out_device_object[2];
  for (int i = 0; i < 2; i++) {
      in_device_object[i] = clCreateBuffer(context[i], CL_MEM_READ_ONLY, sizeof(unsigned char)*img_size, NULL, &err);
      cl_error(err, "Failed to create memory buffer at device\n");
      out_device_object[i] = clCreateBuffer(context[i], CL_MEM_WRITE_ONLY, sizeof(unsigned char)*img_size, NULL, &err);
      cl_error(err, "Failed to create memory buffer at device\n");
  }

  // Loop over the images and enqueue the kernel execution commands to the appropriate command queue
  for (int i = 0; i < 5000; i++) {
    int device_index = i % 2; // Use this to alternate between the two devices

    // Write data into the memory object
    err = clEnqueueWriteBuffer(command_queue[device_index], in_device_object[device_index], CL_TRUE, 0, sizeof(unsigned char)*img_size, images[i].data(), 0, NULL, NULL);
    cl_error(err, "Failed to enqueue a write command\n");

    // Set the arguments to the kernel
    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &in_device_object[device_index]);
    cl_error(err, "Failed to set kernel arguments\n");
    err = clSetKernelArg(kernel, 1, sizeof(cl_mem), &out_device_object[device_index]);
    cl_error(err, "Failed to set kernel arguments\n");
    err = clSetKernelArg(kernel, 2, sizeof(int), &width);
    cl_error(err, "Failed to set kernel arguments\n");
    err = clSetKernelArg(kernel, 3, sizeof(int), &height);
    cl_error(err, "Failed to set kernel arguments\n");

    // Launch kernel
    const size_t global_size[2] = {static_cast<size_t>(width) , static_cast<size_t>(height)};
    err = clEnqueueNDRangeKernel(command_queue[device_index], kernel, 2, NULL, global_size, NULL, 0, NULL, NULL);
    cl_error(err, "Failed to launch kernel to the device\n");
    printf("Kernel launched for image %d\n", i);

    // Read data from device memory to host memory
    err = clEnqueueReadBuffer(command_queue[device_index], out_device_object[device_index], CL_TRUE, 0,sizeof(unsigned char)*img_size, 
                              images[i].data(), 0, NULL, NULL);
    cl_error(err, "Failed to enqueue a read command\n\n");
    printf("Data read from device for image %d\n", i);
  }
  
  end_k = clock();

  // Display the first image
  images[0].display("Image flip");

  // Save the first image
  images[0].save("lenna_flip.jpeg");

  double time_kernel = ((double) (end_k - start_k)) / CLOCKS_PER_SEC;

  // Bandwidth to/from memory to/from kernel. Amount data interchanged with memory for every second
  double bandwidth = (double) (sizeof(unsigned char)*img_size*2) + (sizeof(int)*2) / time_kernel;

  // Trhoughput of the kernel in terms of pixels flipped per second
  double throughput = (double) (width*height) / time_kernel;

  // Memory footprint
  size_t local_memory_footprint = (size_t) ((sizeof(unsigned char)*img_size*2) + (sizeof(int)*2));
  size_t kernel_memory_footprint_in = 0.0;
  size_t kernel_memory_footprint_out = 0.0;
  err = clGetMemObjectInfo(in_device_object, CL_MEM_SIZE, sizeof(size_t), &kernel_memory_footprint_in, NULL);
  cl_error(err, "Failed to get memory object info\n");
  err = clGetMemObjectInfo(out_device_object, CL_MEM_SIZE, sizeof(size_t), &kernel_memory_footprint_out, NULL);
  cl_error(err, "Failed to get memory object info\n");

  size_t memory_footprint = local_memory_footprint + kernel_memory_footprint_in + kernel_memory_footprint_out + sizeof(int)*2;

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