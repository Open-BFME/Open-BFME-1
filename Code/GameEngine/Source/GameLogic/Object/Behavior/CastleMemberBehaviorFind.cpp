// cl: /DNDEBUG /MD /EHsc

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

Module *rva0036BB10FindCastleMemberBehavior( const Object *object );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
protected:
	Module *findModule( NameKeyType key ) const;

	friend Module *rva0036BB10FindCastleMemberBehavior( const Object *object );
};

Module *rva0036BB10FindCastleMemberBehavior( const Object *object )
{
	static NameKeyType key =
		TheNameKeyGenerator->nameToKey( "CastleMemberBehavior" );
	return object->findModule( key );
}
