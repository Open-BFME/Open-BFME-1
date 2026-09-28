// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// TerrainLogic::addWaypoint -- retail RVA 0x001ABC90, 550 bytes.
// Identity: TerrainLogic_loadMap_Thunk.cpp calls ILT 0x00026940 using
// AddWaypointCall(MapObject*); that thunk reaches this body. The ZH addWaypoint
// source supplies the three label assignments and copied location. BFME passes
// two extra Dict values to its nine-word constructor and the ctor owns linking.
// MapObject+0x24 is m_properties in the layout witness (name_oracle).
// Keep the exact observed ILTs: j_0001325a returns a three-word location
// pointer; j_00010f05 returns an AsciiString through a hidden result pointer;
// j_0003ce2a returns the waypoint ID in eax.
// j_00009304 has no stack args. The already-pushed bool* belongs to the Dict
// lookup, not the static-key accessor. Direct typed calls preserve EH ordering.
#include "ascii_string.h"
#include <new>

void j_00009304();
void j_0001325a();
void j_00010f05();
void j_0003ce2a();
void j_00043a1d();
void j_0003a76a();

struct Position001ABC90 { float x,y,z;
 // Copy the coordinate payload without changing floating-point bits.
 Position001ABC90(const Position001ABC90 &p) {
  int a=((const int*)&p)[0], b=((const int*)&p)[1], c=((const int*)&p)[2];
  ((int*)this)[2]=c; ((int*)this)[0]=a; ((int*)this)[1]=b;
 }
};
struct Rva001AB600Arg { int m_values[3]; };
class Key001ABC90 {
public:
 int key() const {
  union {void (*raw)(); int (Key001ABC90::*typed)() const;} call;
  call.raw=j_00009304; return (this->*call.typed)();
 }
};
extern Key001ABC90 g_Key001ABC90_012A77B8,g_Key001ABC90_012A77C0,g_Key001ABC90_012A77C8,g_Key001ABC90_012A77D0,g_Key001ABC90_012A77D8,g_Key001ABC90_012A77E0;

class Rva0002FF6DStringPresenceThunk {
public: AsciiString forward(int key, bool *exists) const;
};
class Properties001ABC90 : public Rva0002FF6DStringPresenceThunk {};
class MapObject {
public:
 AsciiString getWaypointName();
 const Position001ABC90 *location001ABC90() const {
  union {void (*raw)(); const Position001ABC90 *(MapObject::*typed)()const;} call;
  call.raw=j_0001325a; return (this->*call.typed)();
 }
 Properties001ABC90 *properties001ABC90() { return (Properties001ABC90*)((char*)this+0x24); }

};
class Rva001A2D50Node {
public:
 Rva001A2D50Node(int,AsciiString,const Rva001AB600Arg&,AsciiString,AsciiString,AsciiString,bool,int,AsciiString);
 char storage[0xb0];
};
class TerrainLogic {public: void addWaypoint(MapObject*);};
void TerrainLogic::addWaypoint(MapObject *object) {
 union {void (*raw)(); bool (Properties001ABC90::*typed)(int,bool*) const;} boolCall;
 union {void (*raw)(); int (Properties001ABC90::*typed)(int,bool*) const;} intCall;
 boolCall.raw=j_00043a1d; intCall.raw=j_0003a76a;
 union {void (*raw)(); int (MapObject::*typed)();} idCall;
 idCall.raw=j_0003ce2a;
 Position001ABC90 loc=*object->location001ABC90();
 bool exists;
 AsciiString label1,label2,label3;
 label1=object->properties001ABC90()->forward(g_Key001ABC90_012A77B8.key(),&exists);
 label2=object->properties001ABC90()->forward(g_Key001ABC90_012A77C0.key(),&exists);
 label3=object->properties001ABC90()->forward(g_Key001ABC90_012A77C8.key(),&exists);
 bool bidirectional=(object->properties001ABC90()->*boolCall.typed)(g_Key001ABC90_012A77D0.key(),&exists);
 new Rva001A2D50Node((object->*idCall.typed)(),object->getWaypointName(),
  *(const Rva001AB600Arg*)&loc,label1,label2,label3,bidirectional,
  (object->properties001ABC90()->*intCall.typed)(g_Key001ABC90_012A77D8.key(),&exists),
  object->properties001ABC90()->forward(g_Key001ABC90_012A77E0.key(),&exists));
}
