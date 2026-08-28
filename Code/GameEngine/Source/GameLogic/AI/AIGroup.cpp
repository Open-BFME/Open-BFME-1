// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep

typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
	char m_layout[0x14];
	UnsignedInt m_id;

public:
	UnsignedInt getID( void );
};

UnsignedInt AIGroup::getID( void )
{
	return m_id;
}
