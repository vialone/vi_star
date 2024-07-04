#pragma once

#include <cstdint>
#include <string>
#include <list>
#include <unordered_map>
#include <functional>
#include <memory>
#include <cstdarg>
#include <iostream>
#include <list>

#include "debug.hpp"

using namespace std;

#define VSTYPE(tpname) TYPE_BY_NAME(#tpname)

uint TYPE_BY_NAME(string name);

template <typename K, typename V>
using map = unordered_map<K, V>;

constexpr uint KIND_TEPLATE = 1;
constexpr uint KIND_TYPEDEF = 2;
constexpr uint KIND_FUNCTOR = 3;
constexpr uint KIND_DEFAULT = 4;
constexpr uint KIND_NOTHING = 5;

struct _object;

typedef _object *(*_function)(_object **);

// class can be used to represent any type of object
struct _universal_object {
    struct {
        bool boolean;
        int integer;
        unsigned integer_unsigned;
        string str;
        _function function;
        double floating;
    } unionize;
    _universal_object() {};
    ~_universal_object() {};
};

// class for object
struct _object : public _universal_object {
    uint kind;
    map<string, _object *> members;
    list<string> member_names;

    _object *get_attr(string name);
    void set_attr(string name, _object *value);
    void del_attr(string name);

    _object *operator()(_object **);

    void debug_print();
};

extern vector<_object*> _types; // type is object with 3 fields: id, name and initial class object (id, name, ico)

_object *just_named_type(string name);

_object *STRING_OBJECT(string str);

_object *INT_OBJECT(int num, bool stop = false);

_object *NULL_OBJECT();

_object *BOOL_OBJECT(bool b);

_object *FLOAT_OBJECT(float f);

_object *FUNC_OBJECT(_function func);

_object *TYPE_OBJECT();

uint TYPE_BY_NAME(string name);

_object *_init_rt();

_object **_convert_args(int argc, char **argv);
