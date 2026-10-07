// cl: /DNDEBUG /D_WINDOWS /MD /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep /EHsc
//
// Open-BFME5: List<INISection *> scalar-deleting destructor at retail RVA
// 0x009E3860.  The matched constructor at 0x009E3440 installs the single-slot
// vtable 0x011454A0, and INIClass::Initialize allocates this exact list type.
// listnode.h's List gives the forced constructor COMDAT retail's body too.
#include "listnode.h"

struct INISection;

void forceINISectionListDeletingDestructor()
{
	List<INISection *> value;
}
