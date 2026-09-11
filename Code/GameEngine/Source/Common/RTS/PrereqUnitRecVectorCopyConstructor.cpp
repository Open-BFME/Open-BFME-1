// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "StringInline.h"

class ThingTemplate;

class ProductionPrerequisite
{
public:
	struct PrereqUnitRec
	{
		const ThingTemplate *unit;
		int flags;
		AsciiString name;
		~PrereqUnitRec();
	};
};

// ??0?$vector@UPrereqUnitRec@ProductionPrerequisite@@V?$allocator@UPrereqUnitRec@ProductionPrerequisite@@@_STL@@@_STL@@QAE@ABV01@@Z
template _STL::vector<ProductionPrerequisite::PrereqUnitRec,
	_STL::allocator<ProductionPrerequisite::PrereqUnitRec> >::vector(
	const _STL::vector<ProductionPrerequisite::PrereqUnitRec,
	_STL::allocator<ProductionPrerequisite::PrereqUnitRec> > &);
