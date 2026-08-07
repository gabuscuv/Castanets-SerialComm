## ASIO - SERIAL COMM
add_subdirectory(asio)

## JSON - nlohmann/json parser
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(json)

set(CMAKE_EXPORT_COMPILE_COMMANDS OFF CACHE INTERNAL "")

set(NANO_BUILD_TESTS OFF CACHE INTERNAL "Build unit tests")
add_subdirectory(nano-signal-slot)