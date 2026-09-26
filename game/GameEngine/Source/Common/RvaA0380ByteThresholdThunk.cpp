struct RvaA0380ByteThresholdThunk
{
    unsigned char unused;
    unsigned char value;

    bool isAtLeast(int threshold) const;
};

// ?d_000a0380@@YAXXZ
bool RvaA0380ByteThresholdThunk::isAtLeast(int threshold) const
{
    return value >= threshold;
}
