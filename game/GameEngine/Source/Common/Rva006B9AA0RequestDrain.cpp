// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
// Pointer-container drain; evidence: targets/game/reverse/identity_evidence/006b9aa0-request-drain.md
#include <hash_set>
#include <list>

// Prefix view of the existing request type; this body copies only its pointer.
struct AudioRequest006A6B40 {
    unsigned int dword00;
    void *event04;
    unsigned int hash08;
};
struct RequestHash006A6B40 {
    // ??RRequestHash006A6B40@@QBEIPBUAudioRequest006A6B40@@@Z absent-from-retail
    unsigned int operator()(const AudioRequest006A6B40 *p) const {
        if (!p) return 0;
        return p->hash08;
    }
};
typedef _STL::hash_set<AudioRequest006A6B40 *, RequestHash006A6B40> RequestTable006A6B40;
typedef _STL::list<AudioRequest006A6B40 *> RequestList006A6B40;
struct Rva006B9320Request;
class Rva006B9320Owner {
public:
    void process006B9320(Rva006B9320Request *, unsigned char *, int);
};
// Existing destructor ABI view at RVA 006912A0.
class BfmeHostESG { public: ~BfmeHostESG(); };
class Rva006B9AA0 {
    char pad000[0x4c];
    RequestList006A6B40 list04c;
    RequestTable006A6B40 table050;
public:
    void process();
};
// ?process@Rva006B9AA0@@QAEXXZ
void Rva006B9AA0::process() {
    RequestList006A6B40::iterator i;
    for (i = list04c.begin(); i != list04c.end();) {
        AudioRequest006A6B40 *request = *i;
        if (!request) {
            i = list04c.erase(i);
            continue;
        }
        unsigned char remove = 1;
        ((Rva006B9320Owner *)this)->process006B9320((Rva006B9320Request *)request, &remove, 1);
        if (remove) {
            delete (BfmeHostESG *)request;
            i = list04c.erase(i);
        } else ++i;
    }
    RequestTable006A6B40::iterator j;
    for (j = table050.begin(); j != table050.end();) {
        AudioRequest006A6B40 *request = *j;
        unsigned char remove = 1;
        if (request)
            ((Rva006B9320Owner *)this)->process006B9320((Rva006B9320Request *)request, &remove, 1);
        if (remove) {
            table050.erase(j++);
            delete (BfmeHostESG *)request;
        } else ++j;
    }
}
