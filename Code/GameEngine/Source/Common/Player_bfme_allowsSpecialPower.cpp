// cl: /DNDEBUG /MD /EHsc

// Player::_bfme_allowsSpecialPower, retail 0x000C9890. The BFME-only question
// SpecialPowerStore::canUseSpecialPower ends on, written up in
// SpecialPowerStore_canUseSpecialPower_Thunk.cpp: a global at 0x012F0FF8 is
// asked about the template together with a subobject at player+0x274, and an
// absent global means yes.
//
// The store and its method stay _bfme_ named. Nothing here identifies them -
// the global is a masked relocation and the callee is an unnamed body at
// 0x0039BE50 - so the pin records the shape the call site proves and no more:
// thiscall on the global, two arguments, a byte back.

class SpecialPowerTemplate;

class BfmePlayerSpecialPowerState
{
private:
	unsigned int m_unmodelled_00;
};

class BfmeSpecialPowerAllowanceStore
{
public:
	unsigned char _bfme_allows( BfmePlayerSpecialPowerState *state, const SpecialPowerTemplate *tmpl );
};

extern BfmeSpecialPowerAllowanceStore *TheBfmeSpecialPowerAllowanceStore;	// 0x012F0FF8

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	unsigned char _bfme_allowsSpecialPower( const SpecialPowerTemplate *tmpl );

private:
	unsigned char m_unmodelled_000[ 0x274 ];
	BfmePlayerSpecialPowerState m_specialPowerState;	// +0x274
};

// ?_bfme_allowsSpecialPower@Player@@QAEEPBVSpecialPowerTemplate@@@Z
unsigned char Player::_bfme_allowsSpecialPower( const SpecialPowerTemplate *tmpl )
{
	if( TheBfmeSpecialPowerAllowanceStore )
		return TheBfmeSpecialPowerAllowanceStore->_bfme_allows( &m_specialPowerState, tmpl );

	return 1;
}
