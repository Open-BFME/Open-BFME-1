// cl: /O2 /MD

struct BfmeStringData3AF0
{
    unsigned short m_refCount;
    unsigned short m_length;
    unsigned m_capacity;
    char m_text[1];
};

// The shared empty string block at 0x012D5298 is defined once in
// game/GameEngine/Source/Common/Data/Rva012D5298.cpp as
// EAStringC::StringDataC g_rva012D5298Empty.  Only its address is compared
// against here.
class EAStringC
{
public:
	class StringDataC;
};

extern EAStringC::StringDataC g_rva012D5298Empty;

class Rva00891B00String
{
    BfmeStringData3AF0 *m_data;

public:
    bool isDefaultRva00891B00() const;
    char *dataRva00891B10() const;
};

bool Rva00891B00String::isDefaultRva00891B00() const
{
    return m_data == (BfmeStringData3AF0 *)&g_rva012D5298Empty;
}

char *Rva00891B00String::dataRva00891B10() const
{
    return m_data->m_text;
}
