// cl: /DNDEBUG /MD /EHsc
// readable body of ?privateGoProne@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// Open-BFME5: AIUpdateInterface::privateGoProne, retail 0x0026F840,
// zh_sweep packet 0026f840.
//
// The Zero Hour body unchanged, function-local static and all -- the guard byte
// and the cached key are the two globals at 0x012EFDF8 and 0x012EFDF4, and the
// SEH frame exists only to unregister the static initialiser if nameToKey
// throws.
//
// One byte separated it from retail inside AIUpdate.cpp: getObject() reads
// [this+0x08], where the vendored module base puts m_object at +0x0C. Its own
// TU rather than moving that member under AIUpdate.cpp's 34 other rows.
//
// Callees are all direct: nameToKey at ILT 0x0003ADD7; Object::findModule at
// 0x0002AE23, which findUpdateModule inlines into, exactly as the reference
// header has it; and ProneUpdate::goProne at 0x00015456, fronting the 76-byte
// body at 0x002A0120.

class DamageInfo;
class UpdateModule;

enum NameKeyType { NAMEKEY_INVALID = 0 };

enum CommandSourceType { CMD_FROM_PLAYER = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );				///< ILT 0x0003ADD7
};

extern NameKeyGenerator *TheNameKeyGenerator;				///< retail 0x012ED600

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ProneUpdate.h
class ProneUpdate
{
public:
	void goProne( const DamageInfo *damageInfo );			///< ILT 0x00015456 -> 0x002A0120
};

class Module;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	// findUpdateModule is inline in the reference and forwards to findModule,
	// which is the protected const member retail actually calls.
	UpdateModule *findUpdateModule( NameKeyType key ) const
	{
		return (UpdateModule *)findModule( key );
	}

protected:
	Module *findModule( NameKeyType key ) const;			///< ILT 0x0002AE23 -> 0x001BEE60
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
protected:
	virtual void privateGoProne( const DamageInfo *damageInfo, CommandSourceType );

	Object *getObject( void ) { return m_object; }

private:
	unsigned char m_unreconstructed_04[0x08 - 4];			///< vptr at +0x00
	Object *m_object;										///< +0x08
};

// ?privateGoProne@AIUpdateInterface@@MAEXPBVDamageInfo@@W4CommandSourceType@@@Z
void AIUpdateInterface::privateGoProne( const DamageInfo *damageInfo, CommandSourceType )
{
	static NameKeyType proneModuleKey = TheNameKeyGenerator->nameToKey( "ProneUpdate" );
	ProneUpdate *proneModule = (ProneUpdate *)getObject()->findUpdateModule( proneModuleKey );
	if (proneModule)
		proneModule->goProne(damageInfo);
}
