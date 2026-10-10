// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
// stlport
// Rebuilds the record vector from the first directed link of each input waypoint.

#include <vector>
#include "ascii_string.h"
#include "coord3d.h"

struct Rva003A3770Position
{
    float x, y, z;
};

struct Rva003A3770Input
{
    void *m_vptr;
    int m_id;
    AsciiString m_name;
    Rva003A3770Position m_position;
    Rva003A3770Input *m_prev;
    Rva003A3770Input *m_next;
    Rva003A3770Input *m_links[8];
    char m_pad40[0x0c];
    int m_count4c;

    // ?getLocation@Rva003A3770Input@@QBEPBURva003A3770Position@@XZ absent-from-retail
    const Rva003A3770Position *getLocation() const { return &m_position; }
    // ?getNumLinks@Rva003A3770Input@@QBEHXZ absent-from-retail
    int getNumLinks() const { return m_count4c; }
    // ?getLink@Rva003A3770Input@@QBEPAU1@H@Z absent-from-retail
    Rva003A3770Input *getLink(int index) const
    {
        if (index >= 0 && index <= 8)
            return m_links[index];
        return 0;
    }
};

class Waypoint;

struct Rva003A35A0Element
{
    int m_key;
    int m_prefix[10];
    Coord3D m_points[10];
    Rva003A3770Position m_location;
    AsciiString m_name;
    int m_tail;

    Rva003A35A0Element();
    Rva003A35A0Element(const Rva003A35A0Element &);
    ~Rva003A35A0Element();
    Rva003A35A0Element &operator=(const Rva003A35A0Element &);
    Rva003A35A0Element *rva003A25A0(const Waypoint *);
};

struct Rva003A3770Vec
{
    Rva003A35A0Element *m_begin;
    Rva003A35A0Element *m_end;
    Rva003A35A0Element *m_capEnd;

    // ?native@Rva003A3770Vec@@QAEAAV?$vector@URva003A35A0Element@@V?$allocator@URva003A35A0Element@@@_STL@@@_STL@@XZ absent-from-retail
    _STL::vector<Rva003A35A0Element> &native()
    {
        return *reinterpret_cast<_STL::vector<Rva003A35A0Element> *>(this);
    }
};

class Rva003A3770Obj
{
public:
    void method(void *arg);

private:
    char m_pad[0x2c];
    Rva003A3770Vec m_vec;
};

// ?method@Rva003A3770Obj@@QAEXPAX@Z
void Rva003A3770Obj::method(void *arg)
{
    m_vec.native().erase(m_vec.native().begin(), m_vec.native().end());
    Rva003A3770Input *node = static_cast<Rva003A3770Input *>(arg);
    if (node)
    {
        Rva003A35A0Element temporary;
        temporary.rva003A25A0(reinterpret_cast<const Waypoint *>(node));
        m_vec.native().push_back(temporary);
        for (;;)
        {
            Rva003A3770Position position;
            position.x = node->getLocation()->x;
            position.y = node->getLocation()->y;
            position.z = node->getLocation()->z;
            node = node->getNumLinks() > 0 ? node->getLink(0) : 0;
            if (!node)
                break;
            Rva003A3770Position delta;
            delta.x = position.x - node->getLocation()->x;
            delta.y = position.y - node->getLocation()->y;
            delta.z = position.z - node->getLocation()->z;
            if (delta.x * delta.x + delta.y * delta.y + delta.z * delta.z < 100.0f)
                m_vec.native()[m_vec.native().size() - 1] = *temporary.rva003A25A0(reinterpret_cast<const Waypoint *>(node));
            else
            {
                temporary.rva003A25A0(reinterpret_cast<const Waypoint *>(node));
                m_vec.native().push_back(temporary);
            }
        }
    }
}
