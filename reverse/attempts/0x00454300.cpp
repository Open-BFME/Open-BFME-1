// ?d_00454300@@YAXXZ
// partial score=0.35 date=2026-09-16
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
struct Coord3D {
    float x;
    float y;
    float z;
};

class AsciiString {
public:
    bool operator<(const AsciiString &rhs) const;

private:
    char *m_data;
};

namespace _STL {
template <bool threads, int instance>
class __node_alloc {
public:
    static void _M_deallocate(void *block, unsigned int bytes);
};
}

struct RvaCoord3DListNode {
    RvaCoord3DListNode *m_next;
    RvaCoord3DListNode *m_prev;
    Coord3D m_data;
};

struct RvaCoord3DList {
    RvaCoord3DListNode *m_node;
};

// The retail call is the already matched STLport tree destructor for the
// proven <AsciiString, Coord3D> waypoint tree.  No tree member is touched in
// this body, so keep the owner opaque and retain only the thiscall ABI.
class Rva00454300WaypointMap {
public:
    ~Rva00454300WaypointMap();
};

#pragma comment(linker, "/alternatename:??1Rva00454300WaypointMap@@QAE@XZ=?j_00030bde@@YAXXZ")

void operator delete(void *block);

#define m_data (*(unsigned char **)0x012F1584)
#define m_waypoints (*(Rva00454300WaypointMap **)0x012F1588)
#define m_supplyHead (*(RvaCoord3DListNode **)0x012F15A8)
#define m_techHead (*(RvaCoord3DListNode **)0x012F15AC)
#define m_data_slot (*(volatile unsigned int *)0x012F1584)
#define m_waypoints_slot (*(volatile unsigned int *)0x012F1588)

__declspec(dllexport) void resetMap()
{
    if (m_data) {
        delete[] m_data;
        m_data_slot = 0;
    }
    if (m_waypoints) {
        m_waypoints->~Rva00454300WaypointMap();
        ::operator delete(m_waypoints);
        m_waypoints_slot = 0;
    }
    RvaCoord3DListNode *node = m_techHead->m_next;
    while (node != m_techHead) {
        RvaCoord3DListNode *old = node;
        node = node->m_next;
        _STL::__node_alloc<true, 0>::_M_deallocate(old, 0x14);
    }
    m_techHead->m_next = m_techHead;
    m_techHead->m_prev = m_techHead;

    node = m_supplyHead->m_next;
    while (node != m_supplyHead) {
        RvaCoord3DListNode *old = node;
        node = node->m_next;
        _STL::__node_alloc<true, 0>::_M_deallocate(old, 0x14);
    }
    m_supplyHead->m_next = m_supplyHead;
    m_supplyHead->m_prev = m_supplyHead;
}
