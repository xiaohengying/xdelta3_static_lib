## 编译Xdelta3的静态库

### 编译
1. 进去[https://github.com/ably-forks/xdelta](https://github.com/ably-forks/xdelta)这里下载源码然运行
```
sh ./buildXDelta.sh
```
即可生成相关头文件和`libxdelta3.a`

### 使用注意点
需要拷贝`xdelta3.h`,`config.h`这两个头文件到你的工程目录中,**使用的时候这两个头文件都要包含，c++项目需要加上`extern`**:
```cpp
extern "C" {
#include "include/config.h"
#include "include/xdelta3.h"
}

```
