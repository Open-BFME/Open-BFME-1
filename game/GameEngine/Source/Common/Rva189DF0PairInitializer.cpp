extern int g_Rva0109B558StateSecondaryVTable;

struct Rva189DF0PairInitializer
{
    unsigned int type;
    unsigned int value;

    Rva189DF0PairInitializer *initialize();
};

// ?d_00189df0@@YAXXZ
Rva189DF0PairInitializer *Rva189DF0PairInitializer::initialize()
{
    type = (unsigned int)&g_Rva0109B558StateSecondaryVTable;
    value = 0;
    return this;
}
