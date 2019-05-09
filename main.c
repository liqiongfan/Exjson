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
    EXJSON *v = decode_json("{\"hello world\":10 # hello world\n"
                            "}");

    char *str = encode_json(v);
    printf("%s", str);
    free(str);
    destroy_exjson(v);
    return 0;
}