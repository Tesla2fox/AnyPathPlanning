
#最小版本的要求
cmake_minimum_required(VERSION 3.0)

#项目名称
project(AnyPathPro)

message("PROJECT_SOURCE_DIR" ${PROJECT_SOURCE_DIR})
#添加外部dll
#add_library(libGPS SHARED IMPORTED)
#set_target_properties(libGPS PROPERTIES
#	IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/libgps2local.dll 
#	IMPORTED_IMPLIB   ${PROJECT_SOURCE_DIR}/lib/libgps2local.lib 
#)
#测试主函数的文件夹
add_subdirectory(src test_pathPlanning)