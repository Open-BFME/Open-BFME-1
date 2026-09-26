// Retail at 0x002C4200 returns true and callee-cleans three four-byte arguments.
// The semantic owner and argument meanings were not recovered.
bool __stdcall rva_002c4200_true_result(
    unsigned int,
    unsigned int,
    unsigned int)
{
    return true;
}

// cl: /DNDEBUG /MD /O2 /Ob2
