// cl: /DNDEBUG /MD /EHsc
// Retail [0x00264AF0,0x00264B0E): 30 bytes, followed by INT3 padding.
// RousingSpeechUpdate's primary slot15 body at0x00265510 passes this address
// to containment slot0xFC. ContainIterateFunc takes Object* and void* context;
// the unused second argument must not be mistaken for a one-argument ABI.
// Object+0x210 and the full102B gainExpForLevel body at0x001B2A10 establish
// this narrow view. The original callback's spelling remains unknown.

class ExperienceTracker
{
public:
    bool gainExpForLevel(int, bool, bool);
};

#include "../object.h"

void __cdecl rousingContainedLevelAt00264AF0(Object *object, void *)
{
    if (object && object->m_experienceTracker)
        object->m_experienceTracker->gainExpForLevel(1, true, false);
}
