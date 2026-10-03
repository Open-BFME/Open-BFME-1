// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x006A83F0, 269 bytes. Under the mutex at +0x95C, lazily build
// a static vector from the 26 room-type records at VA 0x0111BAC8, excluding
// the record whose numeric type is zero. The table and its field identities
// are shared with MilesAudioRoomTypeLookupRva00694CA0.cpp. No method name
// is proven, so the receiver retains this body's address.
// Naming the wait result is significant for MSVC 7.1 register allocation.

#include <vector>
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *, unsigned long);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *);
struct Rva006A16B0Entry
{
    const char *m_name;
    int m_roomType;
};
extern Rva006A16B0Entry g_rva0111BAC8[];
class RoomNamesMutex006A83F0 {
    void *m_handle;
    unsigned char m_held;
public:
    __forceinline RoomNamesMutex006A83F0(void *h) {
        m_held = 0;
        m_handle = h;
        unsigned long result = WaitForSingleObject(m_handle,0xffffffffu);
        if (result!=0x102u) m_held=1;
    }
    __forceinline ~RoomNamesMutex006A83F0() {
        if (m_held) {
            ReleaseMutex(m_handle);
            m_held = 0;
        }
    }
};
class RoomTypeNames006A83F0 {
    char pad000[0x95c];
    void *mutex95c;
public:
    const _STL::vector<const char *>& get();
};
const _STL::vector<const char *>& RoomTypeNames006A83F0::get() {
    RoomNamesMutex006A83F0 guard(mutex95c);
    static _STL::vector<const char *> names;
    if(names.empty()) {
        names.reserve(25);
        for(unsigned i=0;i<26;++i) {
            if(g_rva0111BAC8[i].m_roomType) names.push_back(g_rva0111BAC8[i].m_name);
        }
    }
    return names;
}
