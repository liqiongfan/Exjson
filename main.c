/**
 * File:main.c for project exjson.
 * Author: Josin
 * Email: xeapplee@gmail.com
 * Website: https://www.supjos.cn
 */

#include <stdio.h>
#include "exjson.h"


int main(int argc, char *argv[])
{
    EXJSON *v = decode_json("{\n"
                            "    \"b\": 100, # 这个是注释\n"
                            "    \"a\":{\n"
                            "        \"a\": \"您好\"\n"
                            "    }\n"
                            "}");
    // 找到a对象里面a的值
    char *value = exjson_get_val_from_key(exjson_get_val_from_key(v, "a"), "a");
    printf("a:%s", value);

    destroy_exjson(v);
    return 0;
}