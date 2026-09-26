// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// BFME's neighboring composite counter dispatches the post-polygon slot.

#include "rendobj.h"

class Rva00982FD0Composite : public RenderObjClass
{
public:
	int Get_Num_Polys(void) const;
};

int Rva00982FD0Composite::Get_Num_Polys(void) const
{
	int count = 0;
	for (int index = 0; index < Get_Num_Sub_Objects(); index++) {
		RenderObjClass *robj = Get_Sub_Object(index);
		count += robj->_bfme_ro_v9();
		robj->Release_Ref();
	}
	return count;
}
