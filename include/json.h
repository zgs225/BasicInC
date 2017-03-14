#ifndef JSON_H
#define JSON_H 1

typedef enum {
    json_string_t = 1;
    json_number_t = 2;
    json_object_t = 3;
    json_array_t = 4;
} json_type;

#endif
