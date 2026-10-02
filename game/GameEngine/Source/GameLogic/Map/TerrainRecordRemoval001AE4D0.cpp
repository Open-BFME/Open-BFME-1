// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Source/Common/System
// RVA 0x001AE4D0: first intersecting 0x30-byte terrain record removal.
// Owner and method remain address-qualified; three stack args and RET12.
// 92-byte BFME GeometryInfo scratch, not the 32-byte ZH geometry.h type.
// The 0x2C/0x38 vector fields and total 0x5C size are independently
// witnessed by GeometryInfoConstructor.cpp and this body cleanup.
// The canonical empty Snapshot base preserves its destructor EH state.
// Native frame local reproduces EAX load/store after the visual notification.
// Constructor and its two member vector destructor ABIs witnessed by retail.
enum GeometryType { GEOMETRY_CYLINDER = 1 };
class Gen_uwm_000187d2 { public: ~Gen_uwm_000187d2(); private: char bytes[12]; };
class Gen_uw_0000ac2c { public: ~Gen_uw_0000ac2c(); private: char bytes[12]; };
#include "snapshot.h"
class GeometryInfo : public Snapshot {
    char prefix[0x28];
    Gen_uw_0000ac2c shapes;
    Gen_uwm_000187d2 records;
    char suffix[0x18];
public:
    GeometryInfo(GeometryType,bool,float,float,float);
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &);
};
struct TerrainRecord001AE4D0 {
    unsigned int field00,field04,field08,field0c,field10,field14;
    bool field18; char gap19[15];
    int field28; bool field2c,field2d; char tail[2];
    void reset() {
        field00=0; field04=0; field08=0; field0c=0; field10=0; field14=0;
        field18=false; field28=1; field2c=true; field2d=true;
    }
};
class BfmeSubYR { public: char bfmeDoYR(void*,void*,void*,void*,int); };
class TerrainVisual001AE4D0 { public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4C();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5C();
    virtual void slot60();
    virtual void slot64();
    virtual void slot68();
    virtual void slot6C();
    virtual void slot70();
    virtual void slot74();
    virtual void slot78();
    virtual void slot7C();
    virtual void slot80();
    virtual void slot84();
    virtual void slot88(unsigned int);
};
// Retail 0x012F7014 is GameClient's TerrainVisual *TheTerrainVisual, defined
// once in game/GameEngine/Source/GameClient/Terrain/TerrainVisual.cpp.
// TerrainVisual001AE4D0 is a TU-local vftable view of that same object.
class TerrainVisual;
extern TerrainVisual *TheTerrainVisual;
static inline TerrainVisual001AE4D0 *theBfmeTerrainVisual(void)
{
    return (TerrainVisual001AE4D0 *)TheTerrainVisual;
}
struct Rva00367E30Logic { char prefix[0x3c]; unsigned int frame; };
// Retail 0x012F0898 is EA's GameLogic *TheGameLogic, defined once in
// game/GameEngine/Source/GameLogic/System/GameLogic.cpp.  Rva00367E30Logic is a
// TU-local view of that object, reached here through the canonical global.
class GameLogic;
extern GameLogic *TheGameLogic;
static inline Rva00367E30Logic *theBfmeGameLogic(void)
{
    return (Rva00367E30Logic *)TheGameLogic;
}
class TerrainRecordRemoval001AE4D0 {
    char prefix[0x55c];
    TerrainRecord001AE4D0 *begin55c,*end560;
    char gap564[0x18f0-0x564];
    unsigned int frame18f0;
public: void removeIntersecting(void *position,BfmeSubYR *collision,void *shape);
};
void TerrainRecordRemoval001AE4D0::removeIntersecting(void *position,BfmeSubYR *collision,void *shape)
{
    GeometryInfo geometry(GEOMETRY_CYLINDER,false,35.0f,14.0f,14.0f);
    for (TerrainRecord001AE4D0 *record=begin55c;record!=end560;++record) {
        if (record->field0c && collision->bfmeDoYR(position,shape,&geometry,record,0)) {
            unsigned int handle=record->field0c;
            record->reset();
            theBfmeTerrainVisual()->slot88(handle);
            unsigned int frame=theBfmeGameLogic()->frame;
            frame18f0=frame;
            break;
        }
    }
}
