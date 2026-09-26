// cl: /DNDEBUG /MD /EHsc /Ob1 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep

#include "wwstring.h"
#define MUTEX_H
#include "../../../../../inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/mempool.h"
#include "hanim.h"

template HAnimComboDataClass *
ObjectPoolClass<HAnimComboDataClass, 256>::Allocate_Object_Memory(void);
