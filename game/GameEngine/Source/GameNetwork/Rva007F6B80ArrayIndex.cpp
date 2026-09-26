// cl: /O2
// Array indexing keeps the retail upper-bound-only test, including negative indices.
struct Rva007F6B80Array
{
    char *m_data;
    int m_count;
    char *element(int index);
};

char *Rva007F6B80Array::element(int index)
{
    if (index >= m_count)
        return 0;
    return m_data + index * 28;
}

struct Rva007F6C40Array
{
    char *m_data;
    int m_count;
    char *element(int index);
};

char *Rva007F6C40Array::element(int index)
{
    if (index >= m_count)
        return 0;
    return m_data + index * 64;
}
