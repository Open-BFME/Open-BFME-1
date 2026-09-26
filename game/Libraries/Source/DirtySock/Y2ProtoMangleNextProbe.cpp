// cl: /DNDEBUG /MD /GX /Od /GZ /GS
// DirtySock ProtoMangle probe parser, RVA 0x00805A70, 484 bytes through RET.
// The matched Rva00805960 caller passes Probe*, ProtoMangleRef*, text as cdecl
// arguments and cleans 12 bytes. That proves the former NAT no-argument method
// identity was false. The inputs/reference/context argument is unused by this body.
//
// DirtySock uses MSVC /Od /GZ /GS here. The RTC descriptor immediately AFTER
// the 484-byte body describes strParm at ebp-0x4c with size 64. Its name is
// retained, and descriptor bytes are not counted as executable function bytes.
// CRT declarations omit dllimport because retail calls their direct stubs.

extern "C" char *strncpy(char *, const char *, unsigned);
extern "C" int atoi(const char *);

struct Rva00804150ProtoMangleRef;
struct Rva00805960Probe {
    int m_index;
    int m_count;
    unsigned m_peerAddr;
    int m_peerPort;
    int m_port;
    int m_serial;
    char m_tag[0x40];
};
int Rva00805710TagFieldGet(char *, int, const char *, const char *, int);
unsigned Rva007FFC10TextAddr(const char *);

int Rva00805A70NextProbe(Rva00805960Probe *probe,
    Rva00804150ProtoMangleRef *ref, const char *text)
{
    int fields = 0;
    char strParm[64];
    if (text == 0)
        return 0;

    probe->m_index = 0;
    probe->m_port = -1;
    probe->m_serial = -1;
    probe->m_serial = Rva00805710TagFieldGet(strParm, sizeof(strParm), text, "targetIP", 1);
    if (probe->m_serial >= 0) {
        probe->m_peerAddr = Rva007FFC10TextAddr(strParm);
        if (probe->m_peerAddr != 0)
            ++fields;
    }
    if (Rva00805710TagFieldGet(strParm, sizeof(strParm), text, "targetPort", 1) == probe->m_serial) {
        probe->m_peerPort = atoi(strParm);
        if (probe->m_peerPort > 0)
            ++fields;
    }
    if (Rva00805710TagFieldGet(strParm, sizeof(strParm), text, "tag", 1) == probe->m_serial) {
        strncpy(probe->m_tag, strParm, sizeof(probe->m_tag) - 1);
        probe->m_tag[sizeof(probe->m_tag) - 1] = 0;
        ++fields;
    }
    if (Rva00805710TagFieldGet(strParm, sizeof(strParm), text, "sendCount", 1) == probe->m_serial) {
        int count = atoi(strParm);
        if (count > 1 && count < 32) {
            probe->m_count = count;
            ++fields;
        }
    }
    // sourcePort is optional and does not contribute to the four required fields.
    if (Rva00805710TagFieldGet(strParm, sizeof(strParm), text, "sourcePort", 1) == probe->m_serial) {
        int port = atoi(strParm);
        if (port > 0)
            probe->m_port = port;
    }
    return fields == 4;
}
