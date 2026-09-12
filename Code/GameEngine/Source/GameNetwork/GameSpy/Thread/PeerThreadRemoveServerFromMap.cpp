// ?removeServerFromMap@PeerThreadClass@@QAEHPAU_SBServer@@@Z
// Retail RVA 0x00647F90; PeerThreadClass callback target through ILT 0x0000252C.
// Exact BFME body: 519 bytes, 13 relocations, verified by the limited fleet probe.
// This TU is intentionally focused: PeerThread.cpp's broader STL configuration
// selects different incremental-link helper routes for the same source shape.
// The 4-byte pointer queue view preserves the retail j_00036c82 helper route;
// the integer key remains an lvalue at the call site, so no conversion code is
// emitted.  The map value facade is one pointer slot with the production
// SBServer comparison; its existing Gen_t_00644050_p4pod erase body is the
// verified 146-byte ICF twin at retail 0x00644BB0, reached via j_0004a8db.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <queue>
#include <map>
typedef int Int;
struct _SBServer;
typedef _SBServer *SBServer;
struct Gen_t_00644050_p4pod
{
    SBServer value;
    bool operator==(SBServer other) const { return value == other; }
};
namespace Rva00647F90
{
class PeerThreadClass
{
public:
    Int removeServerFromMap(SBServer server);
private:
    char m_beforeStagingMap[0x20c];
    std::map<Int, Gen_t_00644050_p4pod> m_stagingServers;
};
Int PeerThreadClass::removeServerFromMap(SBServer server)
{
    std::queue<void *> handles;
    for (std::map<Int, Gen_t_00644050_p4pod>::iterator it = m_stagingServers.begin();
        it != m_stagingServers.end(); ++it)
    {
        if (it->second == server)
            handles.push(*(void **)&it->first);
    }
    Int result = 0;
    while (!handles.empty())
    {
        result = (Int)handles.front();
        m_stagingServers.erase(result);
        handles.pop();
    }
    return result;
}
}
