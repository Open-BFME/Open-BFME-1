// cl: /O2 /MD

struct BfmeStringData3AF0
{
    unsigned short m_refCount;
    unsigned short m_length;
    unsigned m_capacity;
    char m_text[1];
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;

class Rva00891B00String
{
    BfmeStringData3AF0 *m_data;

public:
    bool isDefaultRva00891B00() const;
    char *dataRva00891B10() const;
};

bool Rva00891B00String::isDefaultRva00891B00() const
{
    return m_data == &g_bfmeDefaultString1284;
}

char *Rva00891B00String::dataRva00891B10() const
{
    return m_data->m_text;
}
