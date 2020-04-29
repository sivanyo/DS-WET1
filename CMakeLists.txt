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

add_executable(wet1 test.cpp library1.cpp MusicManager.cpp MusicManager.h TreeNode/TreeNode.cpp TreeNode/TreeNode.h Artist/Artist.cpp Artist/Artist.h Song/Song.cpp Song/Song.h MostPlayedList/MostPlayedListNode.cpp MostPlayedList/MostPlayedListNode.h ArtistTree/ArtistNode.cpp ArtistTree/ArtistNode.h test.cpp MostPlayedList/ArtistPlaysNode.cpp MostPlayedList/ArtistPlaysNode.h MostPlayedList/SongPlaysNode.cpp MostPlayedList/SongPlaysNode.h)
add_executable(test TreeNode/TreeNode.cpp TreeNode/TreeNode.h Artist/Artist.cpp Artist/Artist.h ArtistTree/ArtistNode.cpp ArtistTree/ArtistNode.h test.cpp)