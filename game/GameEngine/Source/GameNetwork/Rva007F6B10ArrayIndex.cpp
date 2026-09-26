// cl: /O2
// Both eight-byte element arrays check the upper bound; negative indices remain unchecked.
struct Rva007F6B10Array
{
    char *m_data;
    int m_count;
    char *element(int index);
};

char *Rva007F6B10Array::element(int index)
{
    if (index >= m_count)
        return 0;
    return m_data + index * 8;
}

struct Rva007F6CC0Array
{
    char *m_data;
    int m_count;
    char *element(int index);
};

char *Rva007F6CC0Array::element(int index)
{
    if (index >= m_count)
        return 0;
    return m_data + index * 8;
}
