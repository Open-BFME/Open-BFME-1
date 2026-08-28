// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: TerrainLogic::updateBridgeDamageStates, retail 0x001AAD70.
//
// The Zero Hour body unchanged. One offset is BFME's:
// m_bridgeDamageStatesChanged at TerrainLogic+0x38, where TerrainLogic.cpp
// lands it at +0x30. getFirstBridge as virtual slot 37 and Bridge::m_next at
// +0x04 were both already right there.
//
// Kept out of TerrainLogic.cpp because pinning the offset inline renumbers
// that compiland's $L labels and breaks its EH funclet row uw_00c08460 -- the
// same thing that moved Shell::isAnimReversed and
// BattlePlanUpdate::recenterTurret into their own TUs.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Bridge
{
public:
	void updateDamageState(void);					///< ILT 0x000232D6
	Bridge *getNext(void) { return m_next; }

private:
	char m_unreconstructed_00[4];
	Bridge *m_next;									///< retail this+0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual Bridge *getFirstBridge(void);			///< retail vtable slot 37

	virtual void updateBridgeDamageStates(void);

private:
	char m_unreconstructed_04[0x38 - 4];			///< the vtable pointer occupies +0x00
	bool m_bridgeDamageStatesChanged;				///< retail this+0x38
};

// ?updateBridgeDamageStates@TerrainLogic@@UAEXXZ
void TerrainLogic::updateBridgeDamageStates( void )
{
	Bridge *pBridge = getFirstBridge();
	while (pBridge) {
		pBridge->updateDamageState();
		pBridge = pBridge->getNext();
	}
	m_bridgeDamageStatesChanged = true;
}
