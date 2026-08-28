// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?getObjectExitInterface@Object@@QBEPAVExitInterface@@XZ: Code/GameEngine/Source/GameLogic/Object/Object.cpp
// Object::getObjectExitInterface, retail 0x001BEAF0.
//
// Zero Hour's body verbatim. The behavior-module array is at this+0x1F0 and is
// walked to its null terminator; getUpdateExitInterface is slot 0x4C of a
// second base whose subobject sits at module+0x0C, so the call adjusts this by
// twelve. The contain module at this+0x1FC is tail-jumped through slot 0x60.

class ExitInterface;

class ModuleBase
{
public:
	virtual ~ModuleBase();								///< the first vtable pointer occupies +0x00

private:
	unsigned char m_unreconstructed_04[ 0x0C - 0x04 ];
};

class UpdateExitProvider
{
public:
	virtual void vslot_00( void ) = 0;
	virtual void vslot_04( void ) = 0;
	virtual void vslot_08( void ) = 0;
	virtual void vslot_0C( void ) = 0;
	virtual void vslot_10( void ) = 0;
	virtual void vslot_14( void ) = 0;
	virtual void vslot_18( void ) = 0;
	virtual void vslot_1C( void ) = 0;
	virtual void vslot_20( void ) = 0;
	virtual void vslot_24( void ) = 0;
	virtual void vslot_28( void ) = 0;
	virtual void vslot_2C( void ) = 0;
	virtual void vslot_30( void ) = 0;
	virtual void vslot_34( void ) = 0;
	virtual void vslot_38( void ) = 0;
	virtual void vslot_3C( void ) = 0;
	virtual void vslot_40( void ) = 0;
	virtual void vslot_44( void ) = 0;
	virtual void vslot_48( void ) = 0;
	virtual ExitInterface *getUpdateExitInterface( void ) = 0;	///< vtable slot +0x4C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ModuleBase, public UpdateExitProvider
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class ContainModuleInterface
{
public:
	virtual void vslot_00( void ) = 0;
	virtual void vslot_04( void ) = 0;
	virtual void vslot_08( void ) = 0;
	virtual void vslot_0C( void ) = 0;
	virtual void vslot_10( void ) = 0;
	virtual void vslot_14( void ) = 0;
	virtual void vslot_18( void ) = 0;
	virtual void vslot_1C( void ) = 0;
	virtual void vslot_20( void ) = 0;
	virtual void vslot_24( void ) = 0;
	virtual void vslot_28( void ) = 0;
	virtual void vslot_2C( void ) = 0;
	virtual void vslot_30( void ) = 0;
	virtual void vslot_34( void ) = 0;
	virtual void vslot_38( void ) = 0;
	virtual void vslot_3C( void ) = 0;
	virtual void vslot_40( void ) = 0;
	virtual void vslot_44( void ) = 0;
	virtual void vslot_48( void ) = 0;
	virtual void vslot_4C( void ) = 0;
	virtual void vslot_50( void ) = 0;
	virtual void vslot_54( void ) = 0;
	virtual void vslot_58( void ) = 0;
	virtual void vslot_5C( void ) = 0;
	virtual ExitInterface *getContainExitInterface( void ) = 0;	///< vtable slot +0x60
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	ExitInterface *getObjectExitInterface( void ) const;

	ContainModuleInterface *getContain( void ) const { return m_contain; }

private:
	unsigned char m_unreconstructed_00[ 0x1F0 ];
	BehaviorModule **m_behaviors;						///< retail this+0x1F0
	unsigned char m_unreconstructed_1F4[ 0x1FC - 0x1F4 ];
	ContainModuleInterface *m_contain;					///< retail this+0x1FC
};

ExitInterface *Object::getObjectExitInterface() const
{
	ExitInterface *exitInterface = 0;

	for( BehaviorModule **umod = m_behaviors; *umod; ++umod )
	{
		if( ( exitInterface = ( *umod )->getUpdateExitInterface() ) != 0 )
			break;
	}

	// If you don't have a fancy one, you may have one from your contain module,
	// since if you can contain something, they will need to get out.
	if( exitInterface == 0 )
	{
		ContainModuleInterface *cmod = getContain();
		if( cmod )
		{
			exitInterface = cmod->getContainExitInterface();
		}
	}

	return exitInterface;
}
