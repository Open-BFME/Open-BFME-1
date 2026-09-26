struct FirstWordZeroInitializerThunk
{
    unsigned long value;

    FirstWordZeroInitializerThunk *initialize();
    FirstWordZeroInitializerThunk *initializeAlternate();
};

// ?d_0005c650@@YAXXZ
FirstWordZeroInitializerThunk *FirstWordZeroInitializerThunk::initialize()
{
    value = 0;
    return this;
}

// ?d_0005c690@@YAXXZ
FirstWordZeroInitializerThunk *FirstWordZeroInitializerThunk::initializeAlternate()
{
    value = 0;
    return this;
}
