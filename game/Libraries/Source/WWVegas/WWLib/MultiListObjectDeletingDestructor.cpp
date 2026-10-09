// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep

#include "multilist.h"

// Keep the retail complete destructor beside its deleting wrapper.
// Retail's wrapper calls the complete destructor through RVA 0x00945970.
__declspec(noinline) MultiListObjectClass::~MultiListObjectClass()
{
	while (ListNode)
		ListNode->List->Internal_Remove(this);
}

void Force_MultiListObject_Deleting_Destructor(MultiListObjectClass *object)
{
	delete object;
}
