# Make use of the pru library
include_directories(include)
include_directories(../pru-as4/)
file(GLOB MY_SOURCES "src/*.c")
add_executable(find_dot_cmake ${MY_SOURCES})

# Make use of the HAL library
target_link_libraries(find_dot_cmake LINK_PRIVATE hal)


# ---------------- NEW! ----------------

# PTHREAD support
find_package(Threads REQUIRED)
target_link_libraries(find_dot_cmake LINK_PRIVATE Threads::Threads)

# Copy executable to final location (change `wave_player_cmake` to project name as needed)
add_custom_command(TARGET find_dot_cmake POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy 
     "$<TARGET_FILE:find_dot_cmake>"
     "$ENV{HOME}/cmpt433/public/myApps/find_dot_cmake" 
  COMMENT "Copying ARM executable to public NFS directory"
)
