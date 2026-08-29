// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?isKindOf@Thing@@QBE_NW4KindOfType@@@Z: Code/GameEngine/Source/Common/Thing/Thing.cpp
// Thing::isKindOf, retail 0x000A2CF0.
//
// Zero Hour's one-liner `return getTemplate()->isKindOf(t);`, with BFME's
// getTemplate walking the override chain instead of returning the member
// straight: null template stays null, otherwise one level of the chain is
// unrolled and the rest reaches the walker at 0x00087A80 through its ILT.
// Same shape as Locomotor::getAppearance in Drawable_calcPhysicsXform_Thunk.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum KindOfType { KINDOF_INVALID = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	const Overridable *getFinalOverride(void) const;	///< ILT thunk at 0x000022BB

	Overridable *m_nextOverride;						///< retail this+0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	Bool isKindOf( KindOfType t ) const
	{
		return ( m_kindof[ (UnsignedInt)t >> 5 ] & ( 1 << ( (UnsignedInt)t & 31 ) ) ) != 0;
	}

private:
	unsigned char m_unreconstructed_08[ 0xC8 - 0x08 ];
	UnsignedInt m_kindof[ 3 ];							///< retail this+0xC8
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	const ThingTemplate *getTemplate( void ) const;
	Bool isKindOf( KindOfType t ) const;

private:
	virtual ~Thing();									///< the vtable pointer occupies +0x00

	const ThingTemplate *m_template;					///< retail this+0x04
};

inline const ThingTemplate *Thing::getTemplate( void ) const
{
	const ThingTemplate *tmpl = m_template;
	if( tmpl == 0 )
		return 0;
	if( tmpl->m_nextOverride )
		tmpl = (const ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
	return tmpl;
}

Bool Thing::isKindOf( KindOfType t ) const
{
	return getTemplate()->isKindOf( t );
}
