struct Rva007F6B10Element
{
    void *first;
    void *second;
};

class Rva007F6B10Array
{
public:
    Rva007F6B10Element *get(int index);
private:
    Rva007F6B10Element *m_data;
    int m_count;
};

Rva007F6B10Element *Rva007F6B10Array::get(int index)
{
    if (index >= m_count)
        return 0;
    return &m_data[index];
}

class Rva007F6CC0Array
{
public:
    Rva007F6B10Element *get(int index);
private:
    Rva007F6B10Element *m_data;
    int m_count;
};

Rva007F6B10Element *Rva007F6CC0Array::get(int index)
{
    if (index >= m_count)
        return 0;
    return &m_data[index];
}
