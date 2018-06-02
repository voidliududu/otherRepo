cmake_minimum_required(VERSION 3.8)
project(dataStructure)

set(CMAKE_CXX_STANDARD 98)

#set(SOURCE_FILES main.cpp LinkList.h city.h CityManager.cpp)
#set(SOURCE_FILES linkList/LinkList.h linkList/city.h linkList/CityManager.cpp linkList/yusefu.cpp stack/stack.h stack/test.cpp linkList/main.cpp)
set(SOURCE_FILES linkList/LinkList.h linkList/main.cpp)
#set(SOURCE_FILES LinkList.h city.h main.cpp)
#set(SOURCE_FILES LinkList.h city.cpp)
#栈的实现和测试
#set(SOURCE_FILES stack/stack.h stack/test.cpp)
#十进制转八进制
#set(SOURCE_FILES stack/stack.h stack/D2O.cpp)
#括号匹配
#set(SOURCE_FILES stack/stack.h stack/bracket.cpp)
#商品货架管理
#set(SOURCE_FILES stack/stack.h stack/item.cpp)
#张志宇的问题
#set(SOURCE_FILES  zhangzhiyu/Stack.h zhangzhiyu/main.cpp)
#队列的实现与测试
#set(SOURCE_FILES queue/queue.h queue/test.cpp)
#链式队列实现与测试
#set(SOURCE_FILES queue/queueList.h queue/testQueueList.cpp string/substr.cpp)
#set(SOURCE_FILES string/substr.cpp )
#显示工具
#set(SOURCE_FILES Graph/Graph.cpp Graph/Graph.h main.cpp)
#树的实现
#set(SOURCE_FILES tree/binary.h tree/test.cpp graph/Graph.h)



add_executable(dataStructure ${SOURCE_FILES})