// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x0021B960: ContestableContain's map at complete-object +0x9C4.
// Node +0x10 is its unsigned pointer key, +0x14 is the target pointer,
// and +0x18 is the reference count. The method spelling is unproven.
#include <map>

struct Rva0021B960Entry
{
    unsigned int value;
    unsigned char count;
};

class Rva0021B960Owner
{
public:
    void rva0021b960();

private:
    char padding[0x9c4];
    _STL::map<unsigned int, Rva0021B960Entry> entries;
};

void Rva0021B960Owner::rva0021b960()
{
    typedef _STL::map<unsigned int, Rva0021B960Entry> Map;
    for (Map::iterator it = entries.begin(); it != entries.end(); ++it)
        it->second.count = 0;

    for (Map::iterator it = entries.begin(); it != entries.end(); ++it)
    {
        unsigned int key = it->second.value;
        if (key)
        {
            Map::iterator found = entries.find(key);
            if (found != entries.end())
                ++found->second.count;
        }
    }
}
