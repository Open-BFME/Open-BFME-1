// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// BFME retail RVA 0x00137E80, 284 bytes. The one-argument factory lookup is
// named by matched ScriptActions callers. The test-asset path agrees with
// ThingFactory::findTemplateInternal in the vendored Generals source.
// Previous HorseHordeContain/ObjectCreationUpgrade/SpecialDisguiseUpdate
// destructor claims at this address were raw-byte lifts with wrong identities.
#include "StringInline.h"

// Retail IAT RVA 0x00F594BC is MSVCR71 strncmp (case-sensitive).
extern "C" __declspec(dllimport) int __cdecl strncmp(
    const char *, const char *, unsigned int);

class ThingTemplate
{
public:
    void initForLTA(const AsciiString &);
};

// Read-only views of the already existing factory and its string-key table.
// No objects or vtables are constructed from these partial declarations.
struct Rva001366A0Node
{
    void *next;
    AsciiString key;
    ThingTemplate *value;
};
class Rva00137E80Map
{
public:
    Rva001366A0Node *find(const AsciiString &);
    unsigned int erase(const AsciiString &);
    ThingTemplate *&operator[](const AsciiString &);
};
class BfmeThingFactory
{
public:
    const ThingTemplate *findTemplate(const AsciiString &);
    ThingTemplate *newTemplate(const AsciiString &);
private:
    unsigned char prefix[16];
    Rva00137E80Map map;
};

const ThingTemplate *BfmeThingFactory::findTemplate(const AsciiString &name)
{
    Rva001366A0Node *node = map.find(name);
    if (node)
        return node->value;

    if (!strncmp(name.str(), "***TESTING", 10))
    {
        ThingTemplate *tmplate = newTemplate(AsciiString("Un-namedTemplate"));
        tmplate->initForLTA(name);
        map.erase(AsciiString("Un-namedTemplate"));
        map[name] = tmplate;
        return findTemplate(name);
    }
    return 0;
}
