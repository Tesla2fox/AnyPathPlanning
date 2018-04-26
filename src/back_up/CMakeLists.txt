#生成PathPlanning的lib

#添加定义
#add_definitions(-D__EXPORT_LIB)


#添加文件
set(file_list 
	#CenPathPlanning.h
	#gps2local.h
	#PointArray.h
	#CenPathPlanning.cpp
	  xml/tinystr.h
	  xml/tinyxml.h
	  tinyxml.cpp  
	  tinystr.cpp
	  tinyxmlerror.cpp tinyxmlparser.cpp
	Aplan.h Aplan.cpp
	bgeometry.h bgeometry.cpp
    ssconfig.hpp 
	#readmap.hpp
	obmap.h obmap.cpp
	#line.h	line.cpp
	#Point.h Point.cpp
	splan.h splan.cpp
	#polygonob.h polygonob.cpp
	stree.h stree.cpp
	#Obstacles.hpp Obstacles.cpp
	TestPathPlan.cpp
		cpp_CppPathPlanning.h
		cpp_CppPathPlanning.cpp
		dingTaskAllocation.h
		dingTaskAllocation.cpp
)

include_directories(../include)
find_package(Boost 1.65.0)

if(Boost_FOUND)


include_directories(${Boost_INCLUDE_DIRS})

message(${Boost_INCLUDE_DIRS})

endif()
#lib文件所存在的位置
set(PROJECT_LIB_DIR ${PROJECT_SOURCE_DIR}/src)

#输出包含文件信息
message(${file_list})
message(${PROJECT_BINARY_DIR})
message(${PROJECT_LIB_DIR})


#生成DLL
#add_executable(test_pathplan  ${PROJECT_LIB_DIR}/${file_list})
add_library(test_pathplan  SHARED ${PROJECT_LIB_DIR}/${file_list})

#链接外部DLL
#target_link_libraries(libPathPlanning libGPS)

#设置输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#设置输出名称
set_target_properties(test_pathplan PROPERTIES OUTPUT_NAME "libAnyPlanning")


# SHARE or STATIC
#add_library(pathplan SHARED  ${file_list})

#target_compile_definitions(pathplan PRIVATE __EXPORT_LIB)
#target_link_libraries(pathplan libgps2local)

#add_executable(test_pathplan TestPathPlan.cpp)

#target_link_libraries(test_pathplan pathplan libgps2local)

if (UNIX)
    target_compile_options(pathplan PRIVATE -std=c++11)
    target_compile_options(test_pathplan PRIVATE -std=c++11)
    message(STATUS "Using -std=c++11")
endif()
