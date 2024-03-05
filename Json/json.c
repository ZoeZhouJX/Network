#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include <json-c/json_object.h>

#if 1
/*
typedef enum json_type
{
    json_type_null,
    json_type_boolean,
    json_type_double,
    json_type_int,
    json_type_object,
    json_type_array,
    json_type_string,
} json_type;
*/

/* 创建一个object类型的Jason对象，返回地址 */
struct json_object *json_object_new_object(void);

/*
    往json对象中添加键值对
    key为C字符串
    value为C转换后对应的Jason类型对象
 */
void json_object_object_add(struct json_object *obj, const char *key, struct json_object *value);

/* 获取Jason对象中指定键的值 */
json_object *json_object_object_get(json_object *obj, const char *key);

/* 创建一个整数类型的Jason类型对象，并返回地址，i为C类型的整数 */
struct json_object *json_object_new_int(int32_t i);

/* 获取整数型Jason类型对象的C整数，以返回值返回 */
int32_t json_object_get_int(struct json_object *obj);

/* 创建一个字符串类型的Jason类型对象， 并返回地址，s为C类型的字符串 */
struct json_object *json_object_new_string(const char *s);

/* 获取字符串类型Jason类型对象的C字符串，以返回值返回 */
const char *json_object_get_string(struct json_object *obj);

/* 创建一个数组类型的Jason类型对象，返回地址 */
struct json_object *json_object_new_array(void);

/* 将Jason类型对象val添加到Jason数组类型对象obj中 */
int json_object_array_add(struct json_object *obj, struct json_object *val);

/* 返回JSON对象的数组值。 */
struct array_list *json_object_get_array(json_object *obj);

/* 返回JSON数组中的元素个数 */
int json_object_array_length(json_object *array);

/* 将符合json格式的str字符串构造成一个json对象。 */
struct json_object *json_tokener_parse(const char *str);
/*
用例：注意字符串中"前要加\转义, 通过是否加""来区分字符串中的数是整数型还是字符型
    struct json_object *json_obj = json_tokener_parse("{\"name\":\"John\",\"age\":30,\"city\":\"New York\"}");
    printf("%s\n", json_object_to_json_string(json_obj));
    // 释放 JSON 对象
    json_object_put(json_obj);
*/

/* 传入地址获取对应键key的值val地址，返回值为是否查询到对应的值（int） */
json_bool json_object_object_get_ex(struct json_object *obj, const char *key, struct json_object **value);
// obj:json_object对象
// key:要获取的字段名称
// val:与key关联的json_object对象

/* 从文件中读取JSON数据并返回一个JSON对象 */
json_object *json_object_from_file(char *filename);

/* 将json对象内容，转成json格式对应的的C字符串格式。 */
const char *json_object_to_json_string(struct json_object *obj);

/* 将JSON对象写入文件中。 */
int json_object_to_file(char *filename, json_object *obj);

/* 从文件中读取JSON数据并返回一个JSON对象。 */
json_object *json_object_from_file(char *filename);

/* 获取JSON对象的类型。 */
enum json_type json_object_get_type(struct json_object *obj);
// 返回类型：
// json_type_null
// json_type_boolean
// json_type_double
// json_type_int
// json_type_object
// json_type_array
// json_type_string

/* 用于获取JSON对象的引用计数，每当引用计数增加一次时，
需要调用该函数。它的作用是将JSON对象的引用计数加1，
表示有一个新的指针指向该对象。 */
struct json_object *json_object_get(struct json_object *obj);

/* 用于释放JSON对象占用的内存。每当引用计数减少到0时，
需要调用该函数。它的作用是将JSON对象的引用计数减1，
如果引用计数为0，则释放该对象的内存。 */
void json_object_put(struct json_object *obj);

/* 注意：在使用json_object_get函数增加引用计数后，
必须要对相应的JSON对象使用json_object_put函数释放引用计数，
否则会造成内存泄漏。 */
#endif



#if 1
int main(void)
{
    // 一、创建JSON
    //  1、创建空json对象
    struct json_object *obj = json_object_new_object();

    // 2、往json对象里添加键值对
    json_object_object_add(obj, "name", json_object_new_string("xiaoming"));
    json_object_object_add(obj, "age", json_object_new_int(20));

    // 3、打印json对象的内容和长度
    printf("%s\n", json_object_to_json_string(obj));
    printf("%ld\n", strlen(json_object_to_json_string(obj)));

    // 二、解析JSON
    //  1：根据键名解析出对应的json对象
    struct json_object *json;
    json_object_object_get_ex(obj, "name", &json);

    // 2：根据json对象类型转换成对应的数据
    json_type type = json_object_get_type(json); // 先获取json对象类型
    if (json_type_string == type)
    {
        printf("name: %s\n", json_object_get_string(json));
    }

    json_object_object_get_ex(obj, "age", &json);
    printf("age: %d\n", json_object_get_int(json));

    return 0;
}
#endif



#if 1
int main(void)
{
    struct json_object *obj = json_object_new_object();

    json_object_object_add(obj, "name", json_object_new_string("xiaoming"));

    // 创建json数组对象
    struct json_object *array = json_object_new_array();
    json_object_array_add(array, json_object_new_int(99));
    json_object_array_add(array, json_object_new_int(100));

    // 把数组对象添加到json对象中
    json_object_object_add(obj, "score", array);

    printf("%s\n", json_object_to_json_string(obj));

    struct json_object *json;
    json_object_object_get_ex(obj, "score", &json);
    if (json_object_get_type(json) == json_type_array)
    {
        int i;
        // 获取json_type_array类型json对象长度
        int size = json_object_array_length(json);
        for (i = 0; i < size; i++)
        {
            // 根据下标提取json对象
            struct json_object *j = json_object_array_get_idx(json, i);
            if (json_type_int == json_object_get_type(j))
            {
                printf("%d\n", json_object_get_int(j));
            }
        }
    }
    return 0;
}
#endif