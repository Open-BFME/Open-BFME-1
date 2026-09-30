// ?rva0010EA60@Rva0010EA60Owner@@QAEXPAXI@Z
// partial score=0.2951 date=2026-09-30
// cl: /DNDEBUG /MD /EHsc
// stlport
#include <list>
#include <utility>
class Rva0010EA60Owner
{
public:
    void rva0010EA60(void *unused, unsigned key);
    unsigned char m_prefix[0x48];
    std::list<void *> m_48;
    std::list<std::pair<void *, unsigned> > m_4c;
};
void Rva0010EA60Owner::rva0010EA60(void *, unsigned key)
{
    typedef std::list<std::pair<void *, unsigned> > Entries;
    Entries::iterator it = m_4c.begin();
    while (it != m_4c.end())
    {
        if (it->second >= key)
        {
            Entries::iterator removed = it++;
            std::pair<void *, unsigned> *entry = &*removed;
            m_4c.erase(removed);
            m_48.remove(entry->first);
        }
        else
            ++it;
    }
}
