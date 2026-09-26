struct Rva007F6B80Element { char data[0x1c]; };
struct Rva007F6C40Element { char data[0x40]; };

class Rva007F6B80Array
{
public:
    Rva007F6B80Element *get(int index);
private:
    Rva007F6B80Element *m_data;
    int m_count;
};

Rva007F6B80Element *Rva007F6B80Array::get(int index)
{
    if (index >= m_count)
        return 0;
    return &m_data[index];
}

class Rva007F6C40Array
{
public:
    Rva007F6C40Element *get(int index);
private:
    Rva007F6C40Element *m_data;
    int m_count;
};

Rva007F6C40Element *Rva007F6C40Array::get(int index)
{
    if (index >= m_count)
        return 0;
    return &m_data[index];
}
