#include "rt.hpp"
#include <iostream>

/*

Object:
    @cast String METHOD (Object self) -> String
    $repr METHOD (Object self) -> String
    $new METHOD () -> Object
    $del METHOD () -> Void
*/

_object *_main_cfunc(_object **args) {

    for (_object *typeinfo : _types) {
        typeinfo->debug_print();
    }
    return 0;
}

/*
 * GlobalScope _init_rt();
 *     initialize primitive classes and prepare global scope
 */
_object *_init_rt() {
    DEBUG("    Initializing runtime");
    _object *gs = new _object();
    // create `Object` type
    _types.push_back(just_named_type("Object"));
    // create `Int` type
    _types.push_back(just_named_type("Int"));
    // create `Float` type
    _types.push_back(just_named_type("Float"));
    // create `Bool` type
    _types.push_back(just_named_type("Bool"));
    // create `String` type
    _types.push_back(just_named_type("String"));
    // create `Func` type
    _types.push_back(just_named_type("Func"));
    DEBUG("    Done!");
    gs->kind = KIND_DEFAULT;
    DEBUG("    Listing types list")
    for (_object *typo : _types)
        typo->debug_print();
    DEBUG("    Setting up main function");
    _object *main_func = FUNC_OBJECT(_main_cfunc);
    main_func->debug_print();
    gs->set_attr("main", main_func);
    DEBUG("    Done!");
    return gs;
}
