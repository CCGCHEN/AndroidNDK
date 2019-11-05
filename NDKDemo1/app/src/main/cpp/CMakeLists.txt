# 设置cmake使用的最低版本，如果用到了高版本的特性，
#这里需要进行设置，如果没有，也可以忽略不写。
cmake_minimum_required(VERSION 3.4.1)

#第一个参数 创建一个名称为 native-lib 的动态库，会生成 native-lib.so 文件；
#第二个参数 SHARED 的意思是声明这个库为动态库，另外一种是静态库，STATIC 表示。
#第三个参数是指定这个库使用到的源代码文件
#另，可以使用多个 add_library，来构建更多的库文件。
add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        native-lib.cpp)
# 查找名字为log 的 NDK库，将这个库的路径存储在变量中。
# 这里的意思就是找到 NDK 中的 log 库，并将其路径存储在 “log-lib” 变量中，
# 在后面就可以通过 “${log-lib}” 命令取出变量中的值
find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

#将我们的so 库和 log 库链接起来
target_link_libraries( # Specifies the target library.
        native-lib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})