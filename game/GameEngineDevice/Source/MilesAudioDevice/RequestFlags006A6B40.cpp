// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x006A6B40 (279 bytes) and 0x006A5320 (381 bytes) traverse the
// same request list at +0x4C and pointer-keyed hash set at +0x50. Hashing
// reads request+8; the event pointer is at +4 and flags at +0x12/+0x13.
// Event+0x28 is kept opaque: its use as an affect-mask index is witnessed,
// but the oracle does not establish a BFME field name. getSoundClass is
// the existing AudioEventRTS method at 0x000B2950.
// BfmeHostESG is the ledger name of the non-virtual request destructor at
// 0x006912A0. It is only an ABI view here, not an additional identity claim.

#include <hash_set>
#include <list>
class AudioEventRTS {
public:
    unsigned int getSoundClass() const;
    char pad00[0x28];
    unsigned int dword28;
};
class BfmeHostESG
{
public:
    ~BfmeHostESG();
};
struct AudioRequest006A6B40 {
    unsigned int dword00;
    AudioEventRTS *event04;
    unsigned int hash08;
    char pad0c[6];
    bool byte12, byte13;
};
struct RequestHash006A6B40 {
    unsigned int operator()(const AudioRequest006A6B40 *p) const {
        if(!p) return 0;
        return p->hash08;
    }
};
typedef _STL::hash_set<AudioRequest006A6B40 *,RequestHash006A6B40> RequestTable006A6B40;
typedef _STL::list<AudioRequest006A6B40 *> RequestList006A6B40;
class RequestFlags006A6B40 {
    char pad000[0x4c];
    RequestList006A6B40 list04c;
    RequestTable006A6B40 table050;
public:
    void apply(unsigned int classes,unsigned int types,bool value);
    void erase006A5320(unsigned int types);
};
void RequestFlags006A6B40::apply(unsigned int classes,unsigned int types,bool value) {
    RequestTable006A6B40::iterator i;
    for(i=table050.begin(); i!=table050.end(); ++i) {
        AudioRequest006A6B40 *request=*i;
        if (request && request->event04 &&
            (types & (1 << request->event04->dword28)) &&
            (classes & request->event04->getSoundClass())) {
            if(classes & 0x20) request->byte13=value;
            else request->byte12=value;
        }
    }
    for(RequestList006A6B40::iterator i=list04c.begin();i!=list04c.end();++i) {
        AudioRequest006A6B40 *request=*i;
        if (request && request->event04 &&
            (types & (1 << request->event04->dword28)) &&
            (classes & request->event04->getSoundClass())) {
            if(classes & 0x20) request->byte13=value;
            else request->byte12=value;
        }
    }
}

void RequestFlags006A6B40::erase006A5320(unsigned int types) {
    RequestList006A6B40::iterator i;
    for(i=list04c.begin();i!=list04c.end();) {
        AudioRequest006A6B40 *request=*i;
        unsigned int type=3;
        // Read through the iterator so deletion retains its null guard.
        AudioEventRTS *event=(*i)->event04;
        if(event) type=event->dword28;
        if(types==7 || (type!=3 && (types & (1<<type)))) {
            i=list04c.erase(i);
            delete (BfmeHostESG *)request;
        } else ++i;
    }
    RequestTable006A6B40::iterator j;
    for(j=table050.begin();j!=table050.end();) {
        AudioRequest006A6B40 *request=*j;
        unsigned int type=3;
        AudioEventRTS *event=request->event04;
        if(event) type=event->dword28;
        if(types==7 || (type!=3 && (types & (1<<type)))) {
            // Keep a separate deletion snapshot before advancing the iterator.
            AudioRequest006A6B40 *removed=*j;
            table050.erase(j++);
            delete (BfmeHostESG *)removed;
        } else ++j;
    }
}
