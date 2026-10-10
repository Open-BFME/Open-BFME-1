extern int g_Va0109B558;

struct Rva189DF0PairInitializer
{
    unsigned int type;
    unsigned int value;

    Rva189DF0PairInitializer *initialize();
};

// ?d_00189df0@@YAXXZ
Rva189DF0PairInitializer *Rva189DF0PairInitializer::initialize()
{
    type = (unsigned int)&g_Va0109B558;
    value = 0;
    return this;
}
