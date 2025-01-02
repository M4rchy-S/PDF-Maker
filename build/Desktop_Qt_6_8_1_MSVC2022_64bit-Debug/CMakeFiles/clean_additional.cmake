# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\testpdf_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\testpdf_autogen.dir\\ParseCache.txt"
  "testpdf_autogen"
  )
endif()
