// ?parseBlock@BfmePlayerAITypeSet@@QAEXPAVINI@@@Z
// partial score=1.0 date=2026-10-09
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// PlayerAIType record layout follows the decoded LibraryMap constructor and copy.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "ascii_string.h"

class INI;

class LibraryMap
{
public:
    LibraryMap() {}
    LibraryMap(INI *ini);
    LibraryMap(const LibraryMap &other);
    void swap(LibraryMap &other)
    {
        m_name.swap(other.m_name);
        m_libraryMaps.swap(other.m_libraryMaps);
    }
    AsciiString m_name;
    std::vector<AsciiString> m_libraryMaps;
};

struct BfmeItemERE
{
    BfmeItemERE() {}
    AsciiString m_bfmeNameERE;
    std::vector<AsciiString> m_bfmeSubERE;
};

class BfmeVecERE
{
public:
    void bfmeResizeERE(unsigned int count, BfmeItemERE value);
};

class PlayerAITypeSet
{
public:
    int find(AsciiString *name);
};

class BfmePlayerAITypeSet
{
public:
    void parseBlock(INI *ini);
    void *m_at00;
    AsciiString m_at04;
    std::vector<LibraryMap> m_types;
};

// ?Rva000DEEC0AtCapacity@@YA_NII@Z absent-from-retail
static inline bool Rva000DEEC0AtCapacity(unsigned int size, unsigned int capacity)
{
    return size >= capacity;
}

// ?parseBlock@BfmePlayerAITypeSet@@QAEXPAVINI@@@Z
void BfmePlayerAITypeSet::parseBlock(INI *ini)
{
    LibraryMap parsed(ini);
    int index = ((PlayerAITypeSet *)this)->find(&parsed.m_name);
    if (index == -1)
    {
        if (Rva000DEEC0AtCapacity(m_types.size(), m_types.capacity()))
        {
            std::vector<LibraryMap> grown;
            grown.reserve(m_types.size() + m_types.size() / 2 + 8);
            unsigned int oldSize = m_types.size();
            ((BfmeVecERE *)&grown)->bfmeResizeERE(oldSize, BfmeItemERE());
            std::vector<LibraryMap>::iterator destination = grown.begin();
            std::vector<LibraryMap>::iterator end = m_types.end();
            for (std::vector<LibraryMap>::iterator source = m_types.begin(); source != end; ++source, ++destination)
                destination->swap(*source);
            m_types.swap(grown);
        }
        index = m_types.size();
        m_types.push_back(LibraryMap());
    }
    m_types[index].swap(parsed);
}
