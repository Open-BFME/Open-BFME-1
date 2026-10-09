// ??0Rva0035E030@@QAE@ABV0@@Z
// partial score=0.7068 date=2026-10-09
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Rva0035E030 copies the index range and deep-copies the string-record range.
#define _STLP_NO_EXCEPTIONS 1
#include "ascii_string.h"
#include <vector>

template <int N>
class Open2Gap
{
public:
    Open2Gap() {}
    Open2Gap(const Open2Gap<N> &) {}
    char m_bytes[N];
};
class Rva00354BC0;
struct Rva00359330Record
{
    int m_previous;
    int m_next;
    AsciiString m_name;
    unsigned char m_released;
    Open2Gap<1> m_pad;
    unsigned short m_references;
    Rva00354BC0 *m_nodes;
    Rva00359330Record() : m_nodes(0) {}
};
void Rva0035CEE0(Rva00359330Record *, const Rva00359330Record *);
void clearRva00359330Nodes(Rva00359330Record *);
class BfmeSecondZ;
void bfmeUnregister(BfmeSecondZ *);

class Rva0035E030
{
public:
    Rva0035E030(const Rva0035E030 &other);
private:
    _STL::vector<int> m_nameIndexes;
    _STL::vector<Rva00359330Record> m_records;
    int m_freeHead;
    int m_activeTail;
};

// ??0Rva0035E030@@QAE@ABV0@@Z
Rva0035E030::Rva0035E030(const Rva0035E030 &other)
    : m_nameIndexes(other.m_nameIndexes), m_freeHead(other.m_freeHead), m_activeTail(other.m_activeTail)
{
    m_records.reserve(other.m_records.size());
    try
    {
        _STL::vector<Rva00359330Record>::const_iterator end = other.m_records.end();
        for (_STL::vector<Rva00359330Record>::const_iterator p = other.m_records.begin(); p != end; ++p)
        {
            Rva00359330Record copy;
            Rva0035CEE0(&copy, p);
            try
            {
                m_records.push_back(copy);
            }
            catch (...)
            {
                clearRva00359330Nodes(&copy);
                throw;
            }
        }
    }
    catch (...)
    {
        bfmeUnregister((BfmeSecondZ *)&m_records);
        throw;
    }
}
