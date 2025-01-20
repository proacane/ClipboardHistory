# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\Clipboard_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Clipboard_autogen.dir\\ParseCache.txt"
  "Clipboard_autogen"
  "QHotkey\\CMakeFiles\\qhotkey_autogen.dir\\AutogenUsed.txt"
  "QHotkey\\CMakeFiles\\qhotkey_autogen.dir\\ParseCache.txt"
  "QHotkey\\qhotkey_autogen"
  )
endif()
