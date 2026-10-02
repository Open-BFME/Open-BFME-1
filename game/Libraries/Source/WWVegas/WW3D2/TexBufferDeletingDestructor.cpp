// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug
// stlport

// The inline constructor emits this TU's scalar-deleting wrapper; keep the
// class declaration and out-of-line destructor from the real game header.
#include "meshmatdesc.h"

void Force_TexBuffer_Deleting_Destructor(TexBufferClass *buffer)
{
	TexBufferClass value(0, NULL);
	delete buffer;
}
