cmake_minimum_required(VERSION 3.15)
project(wet1)


set(GCC_COVERAGE_COMPILE_FLAGS "-Wall")
# need to check which exact compiler flags will be used (PDF only states DNDEBUG and Wall
#set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror -pedantic-errors")
set(CMAKE_CXX_STANDARD 11)
# might need these
#set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

add_executable(wet1 main1.cpp library1.h library1.cpp MusicManager.cpp MusicManager.h Artist.cpp Artist.h Song.cpp Song.h ArtistPlays.cpp ArtistPlays.h MostPlayedListNode.cpp MostPlayedListNode.h SongPlays.cpp SongPlays.h Tree.h)
add_executable(test Artist.cpp Artist.h test.cpp Tree.h)