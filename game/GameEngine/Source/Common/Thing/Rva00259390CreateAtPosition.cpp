// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWLib
// stlport

class AsciiString;
class ThingTemplate;
class Team;
struct Coord3D;
class Thing { public: void setPosition(const Coord3D *); };
class Object;
#include <bitset>

template<int N> class BitFlags { public: std::bitset<N> m_bits; };
struct BfmeObjectStatusMask { unsigned int m_words[3]; };
typedef bool Bool;
#include "../System/game_engine_subsystems.h"

class BfmeThingFactory {
public:
    const ThingTemplate *findTemplate(const AsciiString &);
    Object *newObject(const ThingTemplate *, Team *, const BfmeObjectStatusMask &, unsigned int);
};

extern ThingFactory *TheThingFactory;

void __stdcall Rva00259390(const Coord3D *position, const AsciiString &name)
{
    const ThingTemplate *thing = ((BfmeThingFactory *)TheThingFactory)->findTemplate(name);
    if (thing) {
        BitFlags<86> status;
        Object *created = ((BfmeThingFactory *)TheThingFactory)->newObject(thing, 0, *(const BfmeObjectStatusMask *)&status, 0);
        if (created)
            ((Thing *)created)->setPosition(position);
    }
}
