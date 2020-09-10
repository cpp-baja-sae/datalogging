cmake_minimum_required(VERSION 3.10)

project(data_router C)

# Without this, file writing craps out after 2GB.
# See https://stackoverflow.com/questions/730709/2gb-limit-on-file-size-when-using-fwrite-in-c
add_definitions(-D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE)

add_executable(
  data_router 
  src/main.c 
  src/workers.c 
  src/command_worker.c 
  src/file_worker.c
  src/realtime_stream_worker.c
  src/sensor_read_worker.c
)

target_include_directories(data_router PRIVATE src/)
target_include_directories(data_router PRIVATE .)

# Default communication library for raspi chipset, has low-level functions
# allowing for super-fast reads / writes.
target_link_libraries(data_router pigpio)

# Include pthreads library
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(data_router Threads::Threads)