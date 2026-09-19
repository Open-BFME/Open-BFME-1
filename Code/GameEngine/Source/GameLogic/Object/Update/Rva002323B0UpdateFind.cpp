// Fuzzy twin (tools/fuzzy_twin_scan.py) of WallUpgradeUpdateFind.cpp: same static-key
// findModule body for "BannerCarrierUpdate", but retail 0x002323B0 ends in ret 4, so this one is
// __stdcall. Identity unproven beyond the key; address-derived name.
// cl: /DNDEBUG /MD /EHsc
//
// Near-twin of CastleMemberBehaviorFind.cpp's
// ?rva0036BB10FindCastleMemberBehavior@@YAPAVModule@@PBVObject@@@Z
// (0x0036BB10): same static-local-NameKeyType-cache-then-findModule shape.
// The cached key string here is "BannerCarrierUpdate" (read at retail rdata
// 0x00C90090), matching the WallUpgradeUpdate module landed alongside this
// row (WallUpgradeUpdateCtorThunk.cpp, 0x002B2270). Real function name not
// recovered; this is address-derived.

enum NameKeyType { };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Module;
class Object;

Module *__stdcall rva002323B0FindBannerCarrierUpdate( const Object *object );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
protected:
	Module *findModule( NameKeyType key ) const;

	friend Module *__stdcall rva002323B0FindBannerCarrierUpdate( const Object *object );
};

Module *__stdcall rva002323B0FindBannerCarrierUpdate( const Object *object )
{
	static NameKeyType key =
		TheNameKeyGenerator->nameToKey( "BannerCarrierUpdate" );
	return object->findModule( key );
}
