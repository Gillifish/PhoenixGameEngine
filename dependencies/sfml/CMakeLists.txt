message(STATUS "Fetching SFML...")

set(SFML_BUILD_EXAMPLES FALSE)
set(SFML_BUILD_TESTS FALSE)
set(SFML_BUILD_DOCS FALSE)

FetchContent_MakeAvailable(sfml)

