## C语言JSON解析库：Exjson



#### 什么是Exjson?

**Exjson**是一款高性能的基于Flex & Bison的 **JSON** 解析器，**Exserver**引擎自带 **Exjson** 解析器，其他需要使用的只需要引入几个头文件和源文件即可

#### Exjson性能

测试代码案例如下：

```
printf("start_time: %ld\n", time(NULL));
for ( int i = 0; i < 1000000; ++i )
{
	EXJSON *v = decode_json("{\n"
                                "    \"a\": \"b\",\n"
                                "    \"b\": \"c\",\n"
                                "    \"c\": {\n"
                                "        \"d\": \"e\",\n"
                                "        \"e\": {\n"
                                "            \"f\": \"g\",\n"
                                "            \"g\": \"h\",\n"
                                "            \"h\": [ \"Linux\", \"Windows\", \"macOSX\"]\n"
                                "        }\n"
                                "    }\n"
                                "}");
    destroy_exjson(v);
}
printf("end_time: %ld\n", time(NULL));
```

解码与编码 JSON **1000000** 次测试结果均平衡稳定于：12~15s之间

```
start_time: 1557548671
end_time: 1557548683
```

测试机器：**MacBookPro 15寸 i7**

#### Exjson特殊符号解析规则

| 文本符号  | 符号含义       | Exjson解析结果 | 反序列化输出 |
| --------- | -------------- | -------------- | ------------ |
| **true**  | 布尔值：**真** | **1**          | 否           |
| **false** | 布尔值：**假** | **0**          | 否           |
| **null**  | **空**         | **0**          | 否           |

#### Exjson适应场合

**Exjson**适合于需要在底层C语言或者C++语言层面使用 **JSON** 功能的场景。目前大部分接口使用的都是 **JSON** 格式传输，后面增加 **XML解析库**

### 注意

**Exjson**支持注释，Exjson中注释以 `#` 或者`//` 开头，一直延续到行尾，如下是合格的 **Exjson**格式 

```
{
    "name": "Exjson", // 名字：Exjson
    "version": "1.0", # 版本号
    "platform": [ "MacOSX", "Linux", "Windows" ]
}
```

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
// EXJSON结构解码为JSON字符串(返回的字符串记得free释放内存)
EXJSON_API char *encode_json(EXJSON *exjson);
// 使用完毕后，需要释放内存
EXJSON_API void destroy_exjson(EXJSON *exjson);
```



#### 示例-编码Exjson

```
#include <stdio.h>
#include "exjson.h"


int main(int argc, char *argv[])
{
    EXJSON *exjson = INIT_EXJSON();
    
    EXJSON *array = INIT_EXJSON();
    add_array_string(array, "Exjson");
    add_array_string(array, "1.0.0");
    add_array_string(array, "Very fast");
    
    add_object_array(exjson, "exjson", array);
    
    char *str = encode_json(exjson);
    printf("%s", str);
    free(str);
    destroy_exjson(exjson);
    destroy_exjson(array);
    
    // 输出如下
    // {"exjson":["Exjson","1.0.0","Very fast"]}
    return 0;
}
```

#### 示例-解码Exjson

```
#include <stdio.h>
#include "exjson.h"


int main(int argc, char *argv[])
{
    EXJSON *v = decode_json("{\n"
                            "    \"b\": 100, # 这个是注释\n"
                            "    \"a\":{\n"
                            "        \"a\": \"b\"\n"
                            "    }\n"
                            "}");
	// 找到a对象里面a的值
	char *value = exjson_get_val_from_key(exjson_get_val_from_key(v, "a"), "a");
	printf("a:%s", value);
	
    destroy_exjson(v);
    return 0;
    // 输出如下：
    // a:b
}
```

