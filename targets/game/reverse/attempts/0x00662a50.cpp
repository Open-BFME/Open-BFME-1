// ?query@Rva00662A50Owner@@QAE_NH@Z
// partial score=0.9855 date=2026-09-30
// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB
// stlport
#define private protected
#include "../../../../game/GameEngine/Source/GameNetwork/native_connection_timing.cpp"
#undef private
extern unsigned int g_dword010EAD50;
class Rva00662A50Owner : public BFMEConnectionManager {
public:
    bool query(int playerID);
};
bool Rva00662A50Owner::query(int playerID) {
    if (playerID == m_localSlot) return true;
    Connection *connection=m_connections[playerID];
    if (!connection) return true;
    if (!connection->m_lastHeardFrom) {
        connection->m_lastHeardFrom=timeGetTime();
        return true;
    }
    unsigned int now=timeGetTime();
    if (TheGameLogic->frame >= g_dword010EAD50) {
        unsigned int last=static_cast<volatile Connection *>(connection)->m_lastHeardFrom;
        unsigned int limit=*reinterpret_cast<volatile unsigned int *>(reinterpret_cast<char *>(TheWritableGlobalData)+0xCBC);
        now -= last;
        return limit >= now ? true:false;
    }
    unsigned int limit=*reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(TheWritableGlobalData)+0xCBC)*4;
    now -= connection->m_lastHeardFrom;
    return limit >= now ? true:false;
}
