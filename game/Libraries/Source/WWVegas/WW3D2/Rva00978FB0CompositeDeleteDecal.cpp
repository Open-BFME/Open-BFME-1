// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// BFME's composite decal cleanup caches the child count before walking it.

#include "rendobj.h"

class Rva00978FB0Composite : public RenderObjClass
{
public:
	void Delete_Decal(unsigned int decal_id);
};

void Rva00978FB0Composite::Delete_Decal(unsigned int decal_id)
{
	int count = Get_Num_Sub_Objects();
	for (int index = 0; index < count; index++) {
		RenderObjClass *robj = Get_Sub_Object(index);
		robj->Delete_Decal(decal_id);
		robj->Release_Ref();
	}
}
