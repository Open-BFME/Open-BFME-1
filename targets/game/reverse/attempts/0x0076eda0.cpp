// ?getBlend@Rva0076EDA0Holder@@QAEXHPAURva0076EDA0Output@@0@Z
// partial score=0.9781 date=2026-10-09
// cl: /O2 /Ob2 /DNDEBUG /MD /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
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
    void dispatchIfStale()
    {
        if (g_rva0075b2e0_value != (unsigned int)stamp)
            ((Rva0076C080 *)this)->advanceAnimation();
    }
};

struct Rva0076EDA0Output { float first, second; };
struct Rva0076EDA0Entry
{
    Rva0076EDA0Item * volatile item;
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

void Rva0076EDA0Holder::getBlend(int index, Rva0076EDA0Output *first, Rva0076EDA0Output *second)
{
    ((Rva0076CAF0ConditionalDispatch *)((char *)this - 0xc))->dispatchIfStale();
    if (index >= 0 && (unsigned int)index < 3 && entries[index].item)
    {
        if (entries[index].enabled)
        {
            switch (entries[index].type)
            {
            case 1:
                first->first = entries[index].upper;
                first->second = (float)getValue(entries[index].item);
                second->first = -0.00001f;
                second->second = entries[index].lower;
                return;
            case 3:
                if (entries[index].at14 == 1)
                {
                    if (entries[index].upper > entries[index].lower)
                    {
                        first->first = entries[index].upper;
                        first->second = 0.0f;
                    }
                    else
                    {
                        first->first = -0.00001f;
                        goto common;
                    }
                }
                else if (entries[index].upper < entries[index].lower)
                {
                    first->first = entries[index].upper;
                    first->second = (float)getValue(entries[index].item) - 1.0f;
                }
                else
                {
                    first->first = (float)getValue(entries[index].item) - 0.99999f;
                    goto common;
                }
                second->first = 0.0f;
                second->second = 0.0f;
                return;
            case 5:
                first->first = entries[index].upper;
                first->second = 0.0f;
                second->first = (float)getValue(entries[index].item);
                second->second = entries[index].lower;
                return;
            }
        }
        first->first = entries[index].upper;
common:
        first->second = entries[index].lower;
        second->first = 0.0f;
        second->second = 0.0f;
    }
    else
    {
        first->first = 0.0f;
        first->second = 0.0f;
        *second = *first;
    }
}
