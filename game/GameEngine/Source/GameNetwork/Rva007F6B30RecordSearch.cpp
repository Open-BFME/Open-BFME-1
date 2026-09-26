struct Rva007F6B30Record
{
    unsigned int m_unknown[2];
    void *m_key;
    char m_rest[0x10];
};

class Rva007F6B30Records
{
public:
    Rva007F6B30Record *find(void *key);
private:
    Rva007F6B30Record *m_data;
    int m_count;
};

Rva007F6B30Record *Rva007F6B30Records::find(void *key)
{
    Rva007F6B30Record *const end = m_data + m_count;
    for (Rva007F6B30Record *record = m_data; record < end; ++record)
        if (record->m_key == key)
            return record;
    return 0;
}
