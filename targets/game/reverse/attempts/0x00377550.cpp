// ?rva00377550@CastleBehavior@@QAE_NXZ
// partial score=0.9311 date=2026-09-27
// Retail 0x00377550..0x003776D8. CastleBehavior ownership is supported by
// data04/object08 layout and calls into the landed CastleBehavior status helper.
// Original private method name unproved; address retained.
// Outstanding typed routes if the register residue is solved:
// Object::rva001BF300 -> ILT 0x00025806 -> body 0x001BF300
// Object::rva001C15F0 -> ILT 0x0001909C -> body 0x001C15F0
// CastleBehavior::rva00376590(bool) -> ILT 0x000084D6 -> 0x00376590
// CastleBehavior::rva00372FA0(ptr,int,bool) -> ILT 0x0000983B -> 0x00372FA0
// These prototypes come from the caller pushes and callees.py; no new pins claimed.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <utility>
#include "ascii_string.h"
class Player;
class PlayerList { public: Player *getNthPlayer(int); char pad00[0x10]; int count10; };
extern PlayerList *ThePlayerList;
struct Flags00377550 {
 unsigned bits[10];
 unsigned test(int i) const { return bits[i>>5] & (1u << (i&31)); }
 void set(int i) { bits[i>>5] |= 1u << (i&31); }
};
class Object {
public:
    virtual void unused00(); virtual void unused04(); virtual void unused08(); virtual void unused0c();
    virtual void unused10(); virtual void unused14(); virtual void unused18(); virtual void unused1c();
    virtual void unused20(); virtual void unused24(); virtual void unused28(); virtual void unused2c();
    virtual void unused30(); virtual void unused34(); virtual void unused38(); virtual void unused3c();
    virtual void unused40(); virtual void unused44(); virtual void unused48(); virtual void unused4c();
    virtual void slot50(void *);
    void rva001BF300();
    void rva001CA2E0();
    void rva001C15F0();
    void notifyModelConditionChanged();
    char pad04[0x10c]; Flags00377550 flags;
};
class Player { public: char pad00[0x1c]; AsciiString name1c; char pad20[0x210]; void *ptr230; };
typedef _STL::pair<AsciiString,int> StringInt00377550;
struct Data00377550 { char pad00[0x1c]; AsciiString name1c; char pad20[0x34]; _STL::vector<StringInt00377550> entries54; };
class ThingTemplate;
class BfmeThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &); };
extern BfmeThingFactory *TheThingFactory;
enum ObjectStatusTypes { Status78 = 78 };
class CastleBehavior {
public:
    bool rva00377550();
    void rva00376590(bool);
    Object *rva00372FA0(const ThingTemplate *, int, bool);
    void rva00371ee0(ObjectStatusTypes, bool);
    void *vtable; Data00377550 *data04; Object *object08; char pad0c[0x98]; bool pendingA4;
};
bool CastleBehavior::rva00377550()
{
    if (pendingA4) {
    Data00377550 *data = data04;
    Object *object = object08;
    for (int i=0; i<ThePlayerList->count10; ++i) {
        Player *player = ThePlayerList->getNthPlayer(i);
        if (player && player->name1c.StringBase<char>::compare(data->name1c)==0) {
            void *value = player->ptr230;
            if (value) {
                object->slot50(value);
                object->rva001BF300();
                object->rva001CA2E0();
                object->rva001C15F0();
                rva00376590(true);
                int count = data->entries54.size();
                for (int j=0; j<count; ++j) {
                    StringInt00377550 entry = data->entries54[j];
                    const ThingTemplate *type=TheThingFactory->findTemplate(entry.first);
                    if (type) rva00372FA0(type,entry.second,true);
                }
            }
            break;
        }
    }
    pendingA4=false;
    if (!(object->flags.test(207))) {
        object->flags.set(207);
        object->notifyModelConditionChanged();
    }
    rva00371ee0(Status78,false);
    return true;
    }
    return false;
}
