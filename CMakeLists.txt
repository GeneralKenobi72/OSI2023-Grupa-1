cmake_minimum_required(VERSION 3.10)
project(Softver-za-registraciju-vozila)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "inc/*.h")

# Postavite izlazni putanju za izvršni fajl unutar bin/ foldera u glavnom direktorijumu
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Dodajte izvore i zaglavlja u izvršni fajl
add_executable(Softver-za-registraciju-vozila ${SOURCES} ${HEADERS})
