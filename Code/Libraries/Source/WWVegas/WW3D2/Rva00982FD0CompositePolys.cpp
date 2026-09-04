// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
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
