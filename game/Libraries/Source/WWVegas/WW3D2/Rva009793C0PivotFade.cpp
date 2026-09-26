// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
#define Matrix4x4 Matrix4
#include "htree.h"

// The retail HTreeClass layout has Pivot at +0x14; this subclass adds no fields.
class Rva009793C0Tree : public HTreeClass
{
public:
	float pivotFade(int index) const;
};

float Rva009793C0Tree::pivotFade(int index) const
{
	const PivotClass *pivots = *(PivotClass *const *)((const char *)this + 0x14);
	return pivots[index].PivotFade;
}
