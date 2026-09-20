// cl: /O2 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// The carved ILT at 0x000013E8 jumps to the matched Relationship hash insert
// body at 0x00787140.  This wrapper keeps the ILT's address-qualified name.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef int Int;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

namespace _STL
{
class RelationshipHashtableInsertShim
{
public:
	pair<const Int, Relationship> &insert(
		const pair<const Int, Relationship> &value);
};
}

#pragma comment(linker, "/alternatename:?insert@RelationshipHashtableInsertShim@_STL@@QAEAAU?$pair@$$CBHW4Relationship@@@2@ABU32@@Z=?_M_insert@?$hashtable@U?$pair@$$CBHW4Relationship@@@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair@$$CBHW4Relationship@@@_STL@@@2@U?$equal_to@H@2@V?$allocator@U?$pair@$$CBHW4Relationship@@@_STL@@@2@@_STL@@QAEAAU?$pair@$$CBHW4Relationship@@@2@ABU32@@Z")

class Rva000013E8RelationshipHashInsertThunk
{
public:
	__declspec(noinline) _STL::pair<const Int, Relationship> &forward(
		const _STL::pair<const Int, Relationship> &value)
	{
		return ((_STL::RelationshipHashtableInsertShim *)this)->insert(value);
	}
};

typedef _STL::pair<const Int, Relationship> &
	(Rva000013E8RelationshipHashInsertThunk::*Rva000013E8ForwardType)(
		const _STL::pair<const Int, Relationship> &);

Rva000013E8ForwardType g_rva000013e8_forward =
	&Rva000013E8RelationshipHashInsertThunk::forward;
