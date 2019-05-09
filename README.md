## C语言JSON解析库：Exjson



#### 什么是Exjson?

**Exjson**是一款高性能的基于Flex & Bison的 **JSON** 解析器，**Xserver**引擎自带，其他需要使用的只需要引入几个头文件和源文件即可



#### Exjson适应场合

**Exjson**适合于在需要在底层C语言或者C++语言层面使用 **JSON** 功能的场景。目前大部分接口使用的都是 **JSON** 格式传输，后面增加 **xml解析库**



### APIs

```
// 生成一个EXJSON对象
EXJSON_API EXJSON * INIT_EXJSON();

// 生成一个 string: long int 的键值对
EXJSON_API int add_object_int(EXJSON *exjson, char *key, long val);

// 生成一个 string: double 的键值对
EXJSON_API int add_object_double(EXJSON *exjson, char *key, double val);

// 生成一个 string : string 的键值对
EXJSON_API int add_object_string(EXJSON *exjson, char *key, char *val);

// 生成一个 string: {} 的键值对
EXJSON_API int add_object_object(EXJSON *exjson, char *key, void *val);

// 生成一个 string: [] 的键值对
EXJSON_API int add_object_array(EXJSON *exjson, char *key, void *val);
// 上面添加方法的一个通用函数
EXJSON_API int add_object_ptr(EXJSON *exjson, char *key, void *val, unsigned char val_type);

// 生成一个 long int 的一个数组元素
EXJSON_API int add_array_int(EXJSON *exjson, long val);

// 生成一个 double 的一个数组元素
EXJSON_API int add_array_double(EXJSON *exjson, double val);

// 生成一个 string 的一个数组元素
EXJSON_API int add_array_string(EXJSON *exjson, char *val);

// 生成一个 对象{} 的一个数组元素
EXJSON_API int add_array_object(EXJSON *exjson, void *val);

// 生成一个 数组的 的一个数组元素
EXJSON_API int add_array_array(EXJSON *exjson, void *val);
// 上面方法的通用函数
EXJSON_API int add_array_ptr(EXJSON *exjson, void *val, unsigned char val_type);

// 打印 EXJSON 信息
PRINT_EXJSON(exjson);

// 从 EXJSON结构中获取数据
EXJSON_API void *exjson_get_val_from_key(EXJSON *exjson, char *key);
EXJSON_API void *exjson_get_val_from_index(EXJSON *exjson, int index);

// 编码JSON字符串为EXJSON结构
EXJSON_API extern EXJSON *decode_json(char *json_string);
// EXJSON结构解码为JSON字符串
EXJSON_API char *encode_json(EXJSON *exjson);
// 使用完毕后，需要释放内存
EXJSON_API void destroy_exjson(EXJSON *exjson);
```



#### 示例

```
#include <stdio.h>
#include "exjson.h"


int main(int argc, char *argv[])
{
    EXJSON *v = decode_json("{\n"
                            "    \"b\": 100,\n"
                            "    \"a\":{\n"
                            "        \"a\": \"b\"\n"
                            "    }\n"
                            "}");
	// 返回的字符串因为分配了内存，需要手动释放
    char *str = encode_json(v);
    printf("%s", str);
    free(str);
    destroy_exjson(v);
    return 0;
}
```

