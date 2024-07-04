#include "rt.hpp"


template <typename T>
uint list_find(list<T> vec, T value) {
    uint rv = 0;
    DEBUG("Looking for <" + value + ">")
    for (T val : vec) {
        DEBUG("Inspecting <" + val + ">")
        if (val == value) {
            DEBUG("Found <" + value + ">, it's ID is " << rv)
            return rv;
        }
        rv++;
    }
    return -1;
}

template <typename T>
T list_at(list<T> vec, uint at) {
    iterator iter = vec.begin();

    for (int i = 0; i <= at; i++)
        if (i == vec.end())
            THROW("not found");
    return iter;
}


_object *_object::operator()(_object **args) {
    _object *result;
    if (this->kind == KIND_FUNCTOR)
        result = this->unionize.function(reinterpret_cast<_object **>(args));
    else
        result = this->get_attr("$call")->unionize.function(reinterpret_cast<_object **>(args));
    return result;
}

_object *just_named_type(string name) {
    _object *type = new _object();
    type->kind = KIND_TYPEDEF;
    _object *class_name = new _object();
    class_name->kind = KIND_DEFAULT;
    class_name->unionize.str = name;
    class_name->set_attr("$class", TYPE_OBJECT());
    type->set_attr("name", class_name);
    return type;
}

_object *STRING_OBJECT(string str) {
    _object *obj = new _object();
    obj->kind = KIND_DEFAULT;
    obj->unionize.str = str;
    obj->set_attr("$class", INT_OBJECT(VSTYPE(String)));
    return obj;
}

_object *INT_OBJECT(int num, bool stop) {
    _object *obj = new _object();
    obj->kind = KIND_DEFAULT;
    obj->unionize.integer = num;
    obj->unionize.str = to_string(num);
    if (!stop)
        obj->set_attr("$class", INT_OBJECT(VSTYPE(Int)));
    else
        obj->set_attr("$class", NULL_OBJECT());
    return obj;
}

_object *NULL_OBJECT() {
    _object *obj = new _object();
    obj->kind = KIND_NOTHING;
    obj->unionize.str = "NULL";
    return obj;
}

_object *BOOL_OBJECT(bool b) {
    _object *obj = new _object();
    obj->kind = KIND_DEFAULT;
    obj->unionize.boolean = b;
    obj->unionize.str = b ? "true" : "false";
    obj->set_attr("$class", INT_OBJECT(VSTYPE(Bool)));
    return obj;
}

_object *FLOAT_OBJECT(float f) {
    _object *obj = new _object();
    obj->kind = KIND_DEFAULT;
    obj->unionize.floating = f;
    obj->unionize.str = to_string(f);
    obj->set_attr("$class", INT_OBJECT(VSTYPE(Float)));
    return obj;
}

_object *TYPE_OBJECT() {
    _object *obj = new _object();
    obj->kind = KIND_DEFAULT;
    obj->unionize.str = "type";
    obj->set_attr("$class", obj);
    return obj;
}

uint TYPE_BY_NAME(string name) {
    DEBUG("------  Looking up type <" + name + ">")
    for (int i = 0; i < _types.size(); i++) {
        _object *cur_type = _types[i];
        DEBUG("------  Found type <" + cur_type->unionize.str + ">")
        _object *cur_name_attr = cur_type->get_attr("name");
        DEBUG("------  Found type <" + cur_name_attr->unionize.str + ">")
        string cur_name = cur_name_attr->unionize.str;
        DEBUG("------  Found type <" + cur_name + ">")
        if (cur_name == name) {
            DEBUG("------  Found type <" + name + ">, success")
            return i;
        }
    }
    THROW("------ type <" + name + "> not found");
}

vector<_object*> _types;

_object *_object::get_attr(string name) {
    DEBUG("------  Looking for attribute <" + name + ">")
    if (list_find<string>(this->member_names, name) == -1)
        THROW("attribute not found");
    DEBUG("------ Success");
    return this->members[name];
}

void _object::set_attr(string name, _object *value) {
    this->members[name] = value;
    if (list_find<string>(this->member_names, name) == -1)
        this->member_names.push_back(name);
}

void _object::del_attr(string name) {
    this->members.erase(name);
    this->member_names.remove(name);
}

void _object::debug_print() {
    cerr << "Kind: ";
    switch (this->kind) {
        case (KIND_DEFAULT): {
            cerr << "default";
            break;
        };
        case (KIND_FUNCTOR): {
            cerr << "functor";
            break;
        };
        case (KIND_NOTHING): {
            cerr << "nothing";
            break;
        };
        case (KIND_TEPLATE): {
            cerr << "template";
            break;
        };
        case (KIND_TYPEDEF): {
            cerr << "typedef";
            break;
        };
        default: cerr << "<error>";
    }
    cerr << "\nMembers:\n    ";

    for (string key : this->member_names) {
        cerr << "    " << key << " = " << this->members[key]->unionize.str << "\n";
    }
}

_object *FUNC_OBJECT(_function func) {
    DEBUG("------  Creating functor")
    _object *obj = new _object();
    obj->kind = KIND_FUNCTOR;
    obj->unionize.function = func;
    obj->unionize.str = "<function at " + to_string(reinterpret_cast<uint64_t>(func)) + ">";
    obj->unionize.boolean = bool(func);
    obj->unionize.integer = reinterpret_cast<int64_t>(func);
    obj->unionize.floating = 0.0;
    obj->unionize.integer_unsigned = obj->unionize.integer;
    DEBUG("------  Setting $class")
    obj->set_attr("$class", INT_OBJECT(VSTYPE(Func)));
    return obj;
}

_object **_convert_args(int argc, char **argv) {
    _object **args = new _object*[argc];
    for (int i = 0; i < argc; i++)
        args[i] = STRING_OBJECT(argv[i]);
    return args;
}
