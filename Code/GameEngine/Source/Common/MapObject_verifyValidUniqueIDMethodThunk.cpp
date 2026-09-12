// cl: /DNDEBUG /MD /EHsc
// MapObject::verifyValidUniqueID, retail RVA 0x00089450, full 530-byte body.
// Ported from GeneralsMD WorldHeightMap.cpp with the BFME StringBase and
// MapObject-list-holder layouts. The original loop intentionally inspects
// only the first other non-waypoint object before choosing the next index.
// Keep Overridable::getFinalOverride visible: its original recursive body
// proves it cannot modify MapObject and preserves retail's cached pointer.
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
    void verifyValidUniqueID();
};
void MapObject::verifyValidUniqueID()
{
    bool exists;
    AsciiString uniqueID = properties.getAsciiString(TheKey_uniqueID.key(), &exists);
    MapObject *obj = BfmeTheMapObjectListHolder->first;
    int highestIndex = -1;
    while (obj) {
        if (obj == this) { obj = obj->next; continue; }
        if (obj->isWaypoint()) { obj = obj->next; continue; }
        bool iterateExists;
        AsciiString tempStr = obj->properties.getAsciiString(TheKey_uniqueID.key(), &iterateExists);
        const char *lastSpace = tempStr.reverseFind(' ');
        int testIndex = -1;
        if (lastSpace) testIndex = atoi(lastSpace);
        if (testIndex > highestIndex) highestIndex = testIndex;
        break;
    }
    int indexOfThisObject = highestIndex + 1;
    const char *thingName;
    if (getThingTemplate()) thingName = getThingTemplate()->name.str();
    else if (isWaypoint()) thingName = getWaypointName().str();
    else thingName = name.str();
    const char *pName = thingName;
    while (*thingName) { if (*thingName == '/') pName = thingName + 1; ++thingName; }
    AsciiString newID;
    if (isWaypoint()) newID.format("%s", pName);
    else newID.format("%s %d", pName, indexOfThisObject);
    properties.setAsciiString(TheKey_uniqueID.key(), newID);
}
