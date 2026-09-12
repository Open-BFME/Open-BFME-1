// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <stack>
// MapObject::fastAssignAllUniqueIDs, retail RVA 0x00089DC0, full 765B body.
// Ported from GeneralsMD WorldHeightMap.cpp. The reverse traversal preserves
// map-order IDs while assigning each object a path-free template/waypoint name.
// BFME uses a holder for the object list and StringBase's 16-bit length at +4.
// Keep the original recursive Overridable getter visible for retail CSE.
#include <stdlib.h>

template<class T> struct StringData { unsigned short refs, capacity, length, pad; T text[1]; };
template<class T> class StringBase {
    friend class AsciiString;
protected:
    StringData<T> *data;
private:
    StringBase():data(0) {}
    StringBase(const T*);
    StringBase(const StringBase &);
    ~StringBase();
};
class AsciiString : private StringBase<char> {
public:
    AsciiString() {}
    AsciiString(const char *p):StringBase<char>(p) {}
    AsciiString(const AsciiString &p):StringBase<char>(p) {}
    ~AsciiString() {}
    const char *str() const { return data ? data->text : ""; }
    int getLength() const { return data ? data->length : 0; }
    const char *reverseFind(char ch) const {
        const char *s = str();
        const char *p = s + getLength();
        while (p != s) { --p; if (*p == ch) return p; }
        return 0;
    }
    void __cdecl format(AsciiString, ...);
};
enum NameKeyType { NAMEKEY_INVALID=0 };
class StaticNameKey { public: NameKeyType key() const; };
extern const StaticNameKey TheKey_uniqueID;
class Dict { public:
    AsciiString getAsciiString(NameKeyType, bool *exists=0) const;
    void setAsciiString(NameKeyType,const AsciiString &);
    void *data;
};
class Overridable {
public:
    void *vtable;
    Overridable *nextOverride;
    const Overridable *getFinalOverride() const { if(nextOverride) return nextOverride->getFinalOverride(); return this; }
};
class ThingTemplate : public Overridable {
public:
    char pad1[0x20-8];
    AsciiString name;
};
class MapObject;
struct MapObjectList { MapObject *first; };
extern MapObjectList *BfmeTheMapObjectListHolder;
class MapObject {
public:
    void *vtable;
    MapObject *next;
    char pad0[0x14-8];
    AsciiString name;
    ThingTemplate *thing;
    char pad1[0x24-0x1c];
    Dict properties;
    char pad2[0x44-0x28];
    int runtimeFlags;
    bool isWaypoint() const { return (runtimeFlags & 4) != 0; }
    const ThingTemplate *getThingTemplate() const { return thing ? static_cast<const ThingTemplate *>(thing->getFinalOverride()) : 0; }
    AsciiString getWaypointName();
    static void fastAssignAllUniqueIDs();
};

// Distinguish this proven four-byte POD instantiation from the legacy ledger's
// incorrect MapObject-pointer name at RVA 0x008FA2B0 (a 20-byte-element deque).
// The tag is reconstruction bookkeeping; each element still stores one pointer.
struct MapObjectIDPointer {
    MapObject *object;
    operator MapObject *() const { return object; }
};
// This aggregate has the same trivial default/copy/assignment/destruction and
// POD properties as the pointer it contains; STLport cannot infer these traits.
namespace _STL { template<> struct __type_traits<MapObjectIDPointer> : __type_traits<MapObject *> {}; }
void MapObject::fastAssignAllUniqueIDs()
{
    MapObject *pMapObj = BfmeTheMapObjectListHolder->first;
    std::stack<MapObjectIDPointer> objStack;
    int actualNumObjects = 0;
    while (pMapObj) {
        ++actualNumObjects;
        MapObjectIDPointer entry = {pMapObj};
        objStack.push(entry);
        pMapObj = pMapObj->next;
    }
    int indexOfThisObject = 0;
    while (actualNumObjects) {
        MapObject *obj = objStack.top();
        const char* thingName;
        if (obj->getThingTemplate()) thingName = obj->getThingTemplate()->name.str();
        else if (obj->isWaypoint()) thingName = obj->getWaypointName().str();
        else thingName = obj->name.str();
        const char *pName = thingName;
        while (*thingName) { if (*thingName == '/') pName = thingName + 1; ++thingName; }
        AsciiString newID;
        if (obj->isWaypoint()) newID.format("%s", pName);
        else newID.format("%s %d", pName, indexOfThisObject);
        obj->properties.setAsciiString(TheKey_uniqueID.key(), newID);
        objStack.pop();
        ++indexOfThisObject;
        --actualNumObjects;
    }
}
