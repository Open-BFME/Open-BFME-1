struct OneWordCopyThunk
{
    unsigned long value;

    OneWordCopyThunk *copyFrom(const OneWordCopyThunk *other);
};

OneWordCopyThunk *OneWordCopyThunk::copyFrom(const OneWordCopyThunk *other)
{
    value = other->value;
    return this;
}
