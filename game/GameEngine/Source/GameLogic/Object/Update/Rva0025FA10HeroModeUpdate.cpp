// cl: /DNDEBUG /MD /EHsc

// Callees (tools/callees.py 0x0025FA10): ILT 0x17D5F -> 0x002A8CE0
// SpecialAbilityUpdate::startUnpacking, ILT 0x4A74B -> 0x001C4920
// Thing::bfmeHasWeaponTemplateSet, ILT 0x348EC -> 0x001C9A10
// Gen001C9A10::handle.
enum WeaponSetType
{
	WEAPONSET_INVALID = 0
};

#define THING_TU_MEMBERS \
	bool bfmeHasWeaponTemplateSet( WeaponSetType type ) const;
#include "../../../Common/Thing/thing.h"
#undef THING_TU_MEMBERS

class Rva0025FA10Object;

class Gen001C9A10
{
public:
	void handle( int condition );
};

class SpecialAbilityUpdate
{
public:
	void startUnpacking();
};

struct Rva0025FA10ModuleData
{
	unsigned char m_lead[ 0x258 ];
	unsigned int m_duration;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
// TU-local view of the canonical GameLogic (GameLogic.cpp); the real class is
// only forward declared here, so every field read casts through this view.
struct GameLogicView
{
	unsigned char m_lead[ 0x3c ];
	unsigned int m_frame;
};

class GameLogic;

extern GameLogic *TheGameLogic;

class Rva0025FA10HeroModeUpdate
{
public:
	void update();

private:
	unsigned char m_lead[ 4 ];
	Rva0025FA10ModuleData *m_data;
	Rva0025FA10Object *m_object;
	unsigned char m_gap[ 0x20 ];
	unsigned int m_endFrame;
};

void Rva0025FA10HeroModeUpdate::update()
{
	((SpecialAbilityUpdate *)this)->startUnpacking();
	Rva0025FA10Object *object = m_object;
	Rva0025FA10ModuleData *data = m_data;
	if ( ((Thing *)object)->bfmeHasWeaponTemplateSet( (WeaponSetType)0x1b ) )
		((Gen001C9A10 *)object)->handle( 0x1b );
	m_endFrame = ((GameLogicView *)TheGameLogic)->m_frame + data->m_duration;
}
