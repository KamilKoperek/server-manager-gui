cmake_minimum_required(VERSION 3.10)

project(ServersManagerGUI)
set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})

add_definitions(${GTK4_CFLAGS_OTHER})

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)




add_library(serversHeader STATIC src/servers.cpp)


#add_library(server_proftpd STATIC servers/proftpd.cpp)

target_include_directories(serversHeader PUBLIC src)


add_executable(ServersManagerGUI src/main.cpp)

#target_link_libraries(ServersManagerGUI Threads::Threads)


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/theme DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/icons DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/bash_scripts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/servers DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/config DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/*
 #    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/src)

#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/theme.css
#     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})



#find_package(PkgConfig)
#if (PKG_CONFIG_FOUND)
 # pkg_check_modules(GTK "gtk4")
  #if (GTK_FOUND)
   # target_link_libraries(ServersManagerGUI ${GTK_LIBRARIES} serversHeader)
    #target_link_libraries(serversHeader ${GTK_LIBRARIES})
    #add_definitions(${GTK_CFLAGS} ${GTK_CFLAGS_OTHER})
 ## endif()
#endif()



target_link_libraries(ServersManagerGUI ${GTK4_LIBRARIES})
#target_link_libraries(serversHeader server_proftpd)
