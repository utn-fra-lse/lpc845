cmake_minimum_required(VERSION 3.12)
project(freertos)

set(CORE LPC845)

# Add FreeRTOS source files
add_library(freertos STATIC
    event_groups.c
    list.c
    queue.c
    stream_buffer.c
    tasks.c
    timers.c
    portable/MemMang/heap_2.c
    portable/GCC/${CORE}/port.c
)

# Include FreeRTOS header files
target_include_directories(freertos PUBLIC
    include
    portable/GCC/${CORE}/include
)