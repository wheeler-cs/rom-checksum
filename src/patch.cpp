#include "patch.hpp"

#include "ups.hpp"


void do_patch(Arguments * args)
{
    UPS patcher;
    if(patcher.validate_patch(args->get_patch_file()))
    {
        patcher.load_patch(args->get_patch_file());
        patcher.apply_patch("");
    }
}
