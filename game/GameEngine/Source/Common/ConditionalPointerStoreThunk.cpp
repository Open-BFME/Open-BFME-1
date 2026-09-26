struct ConditionalPointerStoreThunk
{
    unsigned long first;
    void *second;
    void *stored;

    void *storeIfNotNull(void *value);
    void *storeSecondIfNotNull(void *value);
    void *takeStored();
    void assignSecond(void *value);
};

// ?d_0005bb30@@YAXXZ
void *ConditionalPointerStoreThunk::storeIfNotNull(void *value)
{
    if (value)
    {
        stored = value;
        return value;
    }

    return 0;
}

// ?d_0005bdb0@@YAXXZ
void ConditionalPointerStoreThunk::assignSecond(void *value)
{
    second = value;
}

// ?d_0005bda0@@YAXXZ
void *ConditionalPointerStoreThunk::takeStored()
{
    void *result = stored;
    stored = 0;
    return result;
}

// ?d_0005bb70@@YAXXZ
void *ConditionalPointerStoreThunk::storeSecondIfNotNull(void *value)
{
    if (value)
    {
        second = value;
        return value;
    }

    return 0;
}
