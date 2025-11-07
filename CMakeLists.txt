cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main src/main.cpp)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE
    SFML::Graphics
    SFML::Audio
)


# --- Copy non-C++ files from src/ to target directory ---

# Gather all files recursively in src/
file(GLOB_RECURSE ASSETS
    "${CMAKE_SOURCE_DIR}/src/*"
)

# Filter out .cpp and .hpp files
set(FILES_TO_COPY "")
foreach(f ${ASSETS})
    if(NOT f MATCHES "\\.cpp$" AND NOT f MATCHES "\\.hpp$")
        list(APPEND FILES_TO_COPY ${f})
    endif()
endforeach()

# Copy each file to the output directory, preserving folder structure relative to src/
foreach(f ${FILES_TO_COPY})
    file(RELATIVE_PATH REL_PATH "${CMAKE_SOURCE_DIR}/src" "${f}")  # relative path inside src
    get_filename_component(DIR ${REL_PATH} DIRECTORY)
    add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:main>/${DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${f}"
            "$<TARGET_FILE_DIR:main>/${REL_PATH}"
    )
endforeach()
