// Retail at 0x006DAE90 returns true and callee-cleans four four-byte arguments.
// The semantic owner and argument meanings were not recovered.
bool __stdcall rva_006dae90_true_result(
    unsigned int,
    unsigned int,
    unsigned int,
    unsigned int)
{
    return true;
}

// cl: /DNDEBUG /MD /O2 /Ob2
