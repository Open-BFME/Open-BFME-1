// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
//
// Open-BFME5: GenericList scalar-deleting destructor at retail
// 0x009E3030 (30 bytes).  The matched GenericList constructor at 0x009E2EC0
// and complete virtual destructor at 0x009E2F30 establish the identity.

// Use the real list layout and constructor, as the retail-proven copies in
// ini.cpp and INISectionListDeletingDestructor.cpp do.
#include "listnode.h"

void forceGenericListDeletingDestructor()
{
	GenericList value;
}
