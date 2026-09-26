// cl: /O2
// Search a counted 28-byte record block for a key at element offset eight.
struct Rva007F6B30Record
{
    int m_reserved0;
    int m_reserved4;
    int m_key;
    char m_remainder[0x10];
};

struct Rva007F6B30Array
{
    Rva007F6B30Record *m_data;
    int m_count;
    Rva007F6B30Record *find(int key);
};

Rva007F6B30Record *Rva007F6B30Array::find(int key)
{
    Rva007F6B30Record *current = m_data;
    Rva007F6B30Record *end = m_data + m_count;
    for (; current < end; ++current)
        if (current->m_key == key)
            return current;
    return 0;
}
