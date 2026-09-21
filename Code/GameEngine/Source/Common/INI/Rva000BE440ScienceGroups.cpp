// ?Rva000BE440@@YAXPAVINI@@PAX1PBX@Z
// Retail000BE440,522B: nested native science-vector parser.
// None clears the current group; OR appends only after a nonempty group.
// An empty final group clears all groups. ILT4835B->000BE300 takes count
// plus a by-value12-byte ScienceVec and destroys that parameter (ret16).
// This corrected contract and native operations reproduce the full body.
// Owner identity is unproven; retain the bank's address-derived identity.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *left, const char *right);

enum ScienceType
{
    SCIENCE_INVALID = -1
};

class INI
{
  public:
    const char *getNextTokenOrNull(const char *delims = 0);
};

class ScienceStore
{
  public:
    ScienceType friend_lookupScience(const char *token) const;
};

extern ScienceStore *TheScienceStore;

typedef _STL::vector<ScienceType> ScienceVec;
typedef _STL::vector<ScienceVec> ScienceGroupVec;

class Rva000BE440Store
{
  public:
    void resizeGroups(unsigned count, ScienceVec value);
    ScienceGroupVec m_groups;
};

// ?Rva000BE440@@YAXPAVINI@@PAX1PBX@Z
void __cdecl Rva000BE440(INI *ini, void *, void *store, const void *)
{
    Rva000BE440Store *self = (Rva000BE440Store *)store;
    self->resizeGroups(1, ScienceVec());
    ScienceVec *current = &self->m_groups.back();
    for (const char *token = ini->getNextTokenOrNull(0); token; token = ini->getNextTokenOrNull(0))
    {
        if (_strcmpi(token, "None") == 0)
        {
            current->clear();
            break;
        }
        if (_strcmpi(token, "OR") == 0)
        {
            if (current->empty())
                break;
            self->m_groups.push_back(ScienceVec());
            current = &self->m_groups.back();
        }
        else
            current->push_back(TheScienceStore->friend_lookupScience(token));
    }
    if (current->empty())
        self->m_groups.clear();
}

// Retail000BE300,211B. The by-value argument is destroyed in this callee.
// Keep the native erase/insert branches explicit: calling vector::resize
// adds an out-of-line wrapper in this STLport version.
void Rva000BE440Store::resizeGroups(unsigned count, ScienceVec value)
{
    if (count < m_groups.size())
        m_groups.erase(m_groups.begin() + count, m_groups.end());
    else
        m_groups.insert(m_groups.end(), count - m_groups.size(), value);
}
