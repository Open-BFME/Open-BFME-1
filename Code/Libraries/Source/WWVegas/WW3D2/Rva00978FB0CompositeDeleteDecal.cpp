// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
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
