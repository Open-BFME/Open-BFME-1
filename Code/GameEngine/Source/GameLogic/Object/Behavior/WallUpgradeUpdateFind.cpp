// cl: /DNDEBUG /MD /EHsc
//
// Near-twin of CastleMemberBehaviorFind.cpp's
// ?rva0036BB10FindCastleMemberBehavior@@YAPAVModule@@PBVObject@@@Z
// (0x0036BB10): same static-local-NameKeyType-cache-then-findModule shape.
// The cached key string here is "WallUpgradeUpdate" (read at retail rdata
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

Module *rva002B21E0FindWallUpgradeUpdate( const Object *object );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
protected:
	Module *findModule( NameKeyType key ) const;

	friend Module *rva002B21E0FindWallUpgradeUpdate( const Object *object );
};

Module *rva002B21E0FindWallUpgradeUpdate( const Object *object )
{
	static NameKeyType key =
		TheNameKeyGenerator->nameToKey( "WallUpgradeUpdate" );
	return object->findModule( key );
}
