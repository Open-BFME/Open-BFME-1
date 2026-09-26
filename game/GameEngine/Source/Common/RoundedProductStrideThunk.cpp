long roundedProductStride(long first, long second)
{
    return ((first * second + 31) / 32) * 4;
}
