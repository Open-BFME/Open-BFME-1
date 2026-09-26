// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
// ?cleanup@ExperienceLevelSystem@@QAEXXZ

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>

class BfmeRefAB
{
public:
    BfmeRefAB *bfmeReleaseThunk();
};

#pragma comment(linker, "/alternatename:?bfmeReleaseThunk@BfmeRefAB@@QAEPAV1@XZ=?j_00032d1c@@YAXXZ")

class BfmeOwnedReference
{
public:
    virtual ~BfmeOwnedReference();
    BfmeRefAB *m_reference;
    bool m_owned;
};

typedef _STL::list<BfmeOwnedReference> ExperienceList;
typedef _STL::pair<const int, ExperienceList> ExperienceMapPair;
typedef _STL::hash_map<int, ExperienceList, _STL::hash<int>,
    _STL::equal_to<int>, _STL::allocator<ExperienceMapPair> > ExperienceMap;

class ExperienceLevelSystem
{
public:
	void cleanup();

private:
	char m_pad[8];
	ExperienceMap m_levelMap;
};

// ?cleanup@ExperienceLevelSystem@@QAEXXZ
void ExperienceLevelSystem::cleanup()
{
    ExperienceMap::iterator it;
    it = m_levelMap.begin();
    while (it != m_levelMap.end())
    {
        ExperienceList &list = (*it).second;
        ExperienceList::iterator entry = list.begin();
        while (entry != list.end())
        {
            BfmeOwnedReference *value = &*entry;
            if (value->m_owned)
            {
                delete value;
            }
            else if (value->m_reference)
            {
                value->m_reference = value->m_reference->bfmeReleaseThunk();
            }
            ++entry;
        }
        ++it;
    }
}
