// cl: /O2 /Ob2 /DNDEBUG /MD /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
//
// Rva0076EDA0Holder::getBlend, retail 0x0076EDA0 (456 B, ret 0Ch). It reports the playing
// animation's frame range pair for track i. The structure follows the BFME 2 donor; the
// name and member roles stay address-derived. Handoff:
// targets/game/reverse/attempt_support/20261107-0076eda0-donor-slot-view.md
// Retail 0x0076EDA0, 456 B, ret 0xC; secondary-interface receiver (primary +0xC).
// Structure follows Open BFME 2 (dbde7dbe) Code/GameEngine/Source/Common/Rva000B8F5A.cpp
// W3DScriptedModelDraw::getPlayingAnimationFrameRanges: early-return invalid path,
// null/mode/direction read through the indexed array, other fields through a
// per-index slot view (this + i*0x1C). Name and member roles remain address-derived.
#include "hanim.h"

typedef HAnimClass Rva0076EDA0Item;
static inline int getValue(Rva0076EDA0Item *item) { return item->Get_Num_Frames(); }
extern unsigned int g_rva0075b2e0_value;
class Rva0076C080 { public: void advanceAnimation(); };
class Rva0076CAF0ConditionalDispatch
{
public:
    unsigned char padding[0x9c];
    int stamp;
    void synchronize()
    {
        if (g_rva0075b2e0_value != (unsigned int)stamp)
            ((Rva0076C080 *)this)->advanceAnimation();
    }
};

struct Rva0076EDA0Output { float first, second; };
struct Rva0076EDA0Entry
{
    Rva0076EDA0Item *item;
    float lower, upper;
    unsigned char entryPadding[4];
    int type;
    int at14;
    bool enabled, at19;
};
class Rva0076EDA0Holder
{
public:
    void getBlend(int index, Rva0076EDA0Output *first, Rva0076EDA0Output *second);
    unsigned char padding[0x90];
    int stamp;
    unsigned char at94[0x3c];
    Rva0076EDA0Entry entries[3];
};

void Rva0076EDA0Holder::getBlend(int i, Rva0076EDA0Output *first, Rva0076EDA0Output *second)
{
    ((Rva0076CAF0ConditionalDispatch *)((char *)this - 0xc))->synchronize();
    if (i < 0 || (unsigned int)i >= 3 || !entries[i].item)
    {
        first->first = 0.0f; first->second = 0.0f;
        *second = *first;
        return;
    }
    Rva0076EDA0Holder *slot = (Rva0076EDA0Holder *)((char *)this + i * 0x1c);
    if (slot->entries[0].enabled)
    {
        switch (entries[i].type)
        {
        case 1:
            first->first = slot->entries[0].upper;
            first->second = (float)getValue(slot->entries[0].item);
            second->first = -0.00001f; second->second = slot->entries[0].lower;
            return;
        case 3:
            if (entries[i].at14 == 1)
            {
                if (slot->entries[0].upper > slot->entries[0].lower) { first->first = slot->entries[0].upper; first->second = 0.0f; }
                else { first->first = -0.00001f; first->second = slot->entries[0].lower; }
            }
            else
            {
                if (slot->entries[0].upper < slot->entries[0].lower)
                {
                    first->first = slot->entries[0].upper;
                    first->second = (float)getValue(slot->entries[0].item) - 1.0f;
                }
                else
                {
                    first->first = (float)getValue(slot->entries[0].item) - 0.99999f;
                    first->second = slot->entries[0].lower;
                }
            }
            second->first = 0.0f; second->second = 0.0f;
            return;
        case 5:
            first->first = slot->entries[0].upper; first->second = 0.0f;
            second->first = (float)getValue(slot->entries[0].item);
            second->second = slot->entries[0].lower;
            return;
        }
    }
    first->first = slot->entries[0].upper; first->second = slot->entries[0].lower;
    second->first = 0.0f; second->second = 0.0f;
}
