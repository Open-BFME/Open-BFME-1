// Retail at 0x00545CA0 returns 1 and callee-cleans four four-byte arguments.
// The semantic owner and argument meanings were not recovered.
int __stdcall rva_00545ca0_constant_one(
    unsigned int,
    unsigned int,
    unsigned int,
    unsigned int)
{
    return 1;
}

// cl: /DNDEBUG /MD /O2 /Ob2
