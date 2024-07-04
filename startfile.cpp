#include "rt.hpp"

int main(int argc, char **argv) {
    DEBUG("Program started");
    _object *_gs = _init_rt();
    DEBUG("Initialized runtime");
    _object *main = _gs->get_attr("main");
    DEBUG("Got main function");
    _object **args = _convert_args(argc, argv);
    DEBUG("Converted arguments, calling main");
    _object *status = main->operator()(args);
    DEBUG("Program ended");
    return status->unionize.integer;
}
