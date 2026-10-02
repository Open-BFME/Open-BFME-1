// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/Common /Igame/Libraries/Source/WWVegas/WWMath
// stlport
// Retail RVA 0x000A1510, 640 bytes, RET 4 at +0x27D followed by INT3.
// StateMachine-family transfer: source donor behavior and 20 matched callers
// establish the operation, but EA's BFME2 DoXfer label does not prove its BFME1
// method spelling. The owner/method identity therefore retains the address.
// Canonical Xfer operators return Xfer&, including the nested ObjectID/Coord3D
// tail; see identity_evidence/000a1510.md for all direct-call and layout proof.
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include "System/xfer.h"
#include "coord3d.h"
#include "Thing/GameLogicObjectLookup.h"

class Rva000A1510Version : public Xfer::Version { public:
    Rva000A1510Version() { data[0] = 1; data[1] = 2; }
};
struct XferException { char *text; int tag; };
extern "C" XferException *__cdecl bfmeFormatText(XferException *, int, const char *, ...);
extern "C" char g_rva005c5100ThrowInfo;
__declspec(noreturn) void __stdcall _CxxThrowException(void *, void *);
extern GameLogic *TheGameLogic;
class MidVirtualSlot90Receiver;
void __cdecl Rva0010C3C0(MidVirtualSlot90Receiver *, void *);
// The existing address-derived slot-0x90 forwarder was declared void. Retail
// consumes the virtual writer's unchanged EAX; this return-ABI cast preserves
// the exact provider identity, as VersionedRecord37A610.cpp already does.
typedef Xfer &(__cdecl *Rva000A1510Writer)(Xfer *, void *);

struct BfmeNodeABB;
struct BfmeIterABB { BfmeNodeABB *node; };
class BfmeHostABB { public: void *bfmeFrontABB(BfmeIterABB); };

struct Rva000A1510State { void *vptr; unsigned id04; };
// The matched provider uses an opaque single-DWORD record and void* result.
// Both callers here supply an unsigned state ID and consume the returned node
// payload as State*. The constant member-pointer cast changes that source ABI
// view while retaining the same proven provider symbol and thiscall cleanup.
typedef Rva000A1510State *(BfmeHostABB::*Rva000A1510Lookup)(unsigned);
struct Rva000A1510Node : _STL::_Rb_tree_node_base {
    unsigned key10;
    Rva000A1510State *state14;
};
struct Rva000A1510ObjectView { char gap00[0x74]; unsigned id74; };

class Rva000A1510Owner {
public:
    void transfer(Xfer *);
    unsigned currentID() const { if (current1C) return current1C->id04; return 999999; }
    void *vptr;
    Rva000A1510Node *header04;
    char gap08[8];
    Object *owner10;
    unsigned sleep14;
    unsigned default18;
    Rva000A1510State *current1C;
    unsigned field20;
    Coord3DBase coord24;
    unsigned field30;
    Coord3DBase coord34;
    bool flag40, flag41, flag42;
};

void Rva000A1510Owner::transfer(Xfer *xfer)
{
    if (xfer->IsLightCRC()) return;
    unsigned ownerID;
    Rva000A1510Version version;
    ((*xfer == version) == sleep14) == default18;
    unsigned currentID = this->currentID();
    *xfer == currentID;
    if (version.data[1] >= 2 && currentID == 999999) return;
    if (xfer->IsLoading()) {
        current1C = (reinterpret_cast<BfmeHostABB *>(this)->*
            reinterpret_cast<Rva000A1510Lookup>(&BfmeHostABB::bfmeFrontABB))(currentID);
    }
    bool all = false;
    *xfer == all;
    if (all) {
        int count = 0;
        Rva000A1510Node *node;
        for (node = static_cast<Rva000A1510Node *>(header04->_M_left); node != header04;
            node = static_cast<Rva000A1510Node *>(_STL::_Rb_global<bool>::_M_increment(node))) ++count;
        int saveCount = count;
        *xfer == saveCount;
        if (saveCount != count) {
            XferException error;
            bfmeFormatText(&error, 5, 0);
            _CxxThrowException(&error, &g_rva005c5100ThrowInfo);
        }
        for (node = static_cast<Rva000A1510Node *>(header04->_M_left); node != header04;
            node = static_cast<Rva000A1510Node *>(_STL::_Rb_global<bool>::_M_increment(node))) {
            Rva000A1510State *state = node->state14;
            unsigned id = state->id04;
            *xfer == id;
            if (id != state->id04) {
                XferException error;
                bfmeFormatText(&error, 5, 0);
                _CxxThrowException(&error, &g_rva005c5100ThrowInfo);
            }
            *xfer == *reinterpret_cast<Snapshot *>(state);
        }
    } else {
        if (!current1C) {
            current1C = (reinterpret_cast<BfmeHostABB *>(this)->*
                reinterpret_cast<Rva000A1510Lookup>(&BfmeHostABB::bfmeFrontABB))(default18);
            if (!current1C) {
                XferException error;
                bfmeFormatText(&error, 5, 0);
                _CxxThrowException(&error, &g_rva005c5100ThrowInfo);
            }
        }
        *xfer == *reinterpret_cast<Snapshot *>(current1C);
    }
    ((((Rva000A1510Writer)Rva0010C3C0)(
       &(((Rva000A1510Writer)Rva0010C3C0)(xfer, &field20) == coord24), &field30)
       == coord34) == flag40) == flag41;
    *xfer == flag42;
    ownerID = 0;
    if (xfer->IsLoading()) {
        ((Rva000A1510Writer)Rva0010C3C0)(xfer, &ownerID);
        if (TheGameLogic) owner10 = TheGameLogic->findObjectByID(ownerID);
    } else {
        if (owner10) ownerID = reinterpret_cast<Rva000A1510ObjectView *>(owner10)->id74;
        ((Rva000A1510Writer)Rva0010C3C0)(xfer, &ownerID);
    }
}
