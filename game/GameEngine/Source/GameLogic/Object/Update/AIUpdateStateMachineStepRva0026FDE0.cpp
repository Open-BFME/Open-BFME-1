// cl: /DNDEBUG /MD /EHsc
//
// BfmeThingEW::bfmeConv1940194, retail 0x0026FDE0 (66 B).
//
// The name is the one the matched caller Object::bfmeConv001C6E00
// (Rva001C6E00.cpp, 0x001C6E00) calls right after BfmeThingEW::bfmeSwapEW on
// the same receiver; the method name itself stays address-derived. The
// receiver's slot 134 (+0x218) is AIUpdateInterface::makeStateMachine
// (0x00271D30) in the vtable 0x010BA8A8 installed by the AIUpdateInterface
// constructor 0x0027F4B0, and +0x30 is the witnessed m_stateMachine. The
// machine's +0x1C is the witnessed StateMachine::m_currentState, and its
// slot 8 (+0x20) sits after the isIdle slot 7 the matched
// AIFollowPathAsTeamState::isAttack (0x0016C2B0) calls. The null-means-true
// test is the Zero Hour StateMachine inline shape
// (m_currentState ? m_currentState->isX() : true); written as that bool inline
// accessor it puts both vtable temporaries in retail's registers.
class BfmeCurCB;

class BfmeItemCB
{
public:
	virtual void bfmeSlot000I();
	virtual void bfmeSlot001I();
	virtual void bfmeSlot002I();
	virtual void bfmeSlot003I();
	virtual void bfmeSlot004I();
	virtual void bfmeSlot005I();
	virtual void bfmeSlot006I();
	virtual void bfmeSlot007I();
	virtual bool bfmeReadyCB() const;
};

class BfmeCurCB
{
public:
	virtual void bfmeSlot000C();
	virtual void bfmeSlot001C();
	virtual void bfmeSlot002C();
	virtual void bfmeSlot003C();
	virtual void bfmeSlot004C();
	virtual void bfmeSlot005C();
	virtual void bfmeSlot006C();
	virtual void bfmeEnterCB();
	virtual void bfmeSlot008C();
	virtual void bfmeSlot009C();
	virtual void bfmeSlot010C();
	virtual void bfmeSlot011C();
	virtual void bfmeSlot012C();
	virtual void bfmeLeaveCB();

	bool bfmeGateReadyCB() const
	{
		return m_bfmeGateCB ? m_bfmeGateCB->bfmeReadyCB() : true;
	}

	unsigned char m_bfmeHeadCB[0x18];
	BfmeItemCB *m_bfmeGateCB;
};
class BfmeThingEW
{
public:
	virtual void bfmeSlot000H();
	virtual void bfmeSlot001H();
	virtual void bfmeSlot002H();
	virtual void bfmeSlot003H();
	virtual void bfmeSlot004H();
	virtual void bfmeSlot005H();
	virtual void bfmeSlot006H();
	virtual void bfmeSlot007H();
	virtual void bfmeSlot008H();
	virtual void bfmeSlot009H();
	virtual void bfmeSlot010H();
	virtual void bfmeSlot011H();
	virtual void bfmeSlot012H();
	virtual void bfmeSlot013H();
	virtual void bfmeSlot014H();
	virtual void bfmeSlot015H();
	virtual void bfmeSlot016H();
	virtual void bfmeSlot017H();
	virtual void bfmeSlot018H();
	virtual void bfmeSlot019H();
	virtual void bfmeSlot020H();
	virtual void bfmeSlot021H();
	virtual void bfmeSlot022H();
	virtual void bfmeSlot023H();
	virtual void bfmeSlot024H();
	virtual void bfmeSlot025H();
	virtual void bfmeSlot026H();
	virtual void bfmeSlot027H();
	virtual void bfmeSlot028H();
	virtual void bfmeSlot029H();
	virtual void bfmeSlot030H();
	virtual void bfmeSlot031H();
	virtual void bfmeSlot032H();
	virtual void bfmeSlot033H();
	virtual void bfmeSlot034H();
	virtual void bfmeSlot035H();
	virtual void bfmeSlot036H();
	virtual void bfmeSlot037H();
	virtual void bfmeSlot038H();
	virtual void bfmeSlot039H();
	virtual void bfmeSlot040H();
	virtual void bfmeSlot041H();
	virtual void bfmeSlot042H();
	virtual void bfmeSlot043H();
	virtual void bfmeSlot044H();
	virtual void bfmeSlot045H();
	virtual void bfmeSlot046H();
	virtual void bfmeSlot047H();
	virtual void bfmeSlot048H();
	virtual void bfmeSlot049H();
	virtual void bfmeSlot050H();
	virtual void bfmeSlot051H();
	virtual void bfmeSlot052H();
	virtual void bfmeSlot053H();
	virtual void bfmeSlot054H();
	virtual void bfmeSlot055H();
	virtual void bfmeSlot056H();
	virtual void bfmeSlot057H();
	virtual void bfmeSlot058H();
	virtual void bfmeSlot059H();
	virtual void bfmeSlot060H();
	virtual void bfmeSlot061H();
	virtual void bfmeSlot062H();
	virtual void bfmeSlot063H();
	virtual void bfmeSlot064H();
	virtual void bfmeSlot065H();
	virtual void bfmeSlot066H();
	virtual void bfmeSlot067H();
	virtual void bfmeSlot068H();
	virtual void bfmeSlot069H();
	virtual void bfmeSlot070H();
	virtual void bfmeSlot071H();
	virtual void bfmeSlot072H();
	virtual void bfmeSlot073H();
	virtual void bfmeSlot074H();
	virtual void bfmeSlot075H();
	virtual void bfmeSlot076H();
	virtual void bfmeSlot077H();
	virtual void bfmeSlot078H();
	virtual void bfmeSlot079H();
	virtual void bfmeSlot080H();
	virtual void bfmeSlot081H();
	virtual void bfmeSlot082H();
	virtual void bfmeSlot083H();
	virtual void bfmeSlot084H();
	virtual void bfmeSlot085H();
	virtual void bfmeSlot086H();
	virtual void bfmeSlot087H();
	virtual void bfmeSlot088H();
	virtual void bfmeSlot089H();
	virtual void bfmeSlot090H();
	virtual void bfmeSlot091H();
	virtual void bfmeSlot092H();
	virtual void bfmeSlot093H();
	virtual void bfmeSlot094H();
	virtual void bfmeSlot095H();
	virtual void bfmeSlot096H();
	virtual void bfmeSlot097H();
	virtual void bfmeSlot098H();
	virtual void bfmeSlot099H();
	virtual void bfmeSlot100H();
	virtual void bfmeSlot101H();
	virtual void bfmeSlot102H();
	virtual void bfmeSlot103H();
	virtual void bfmeSlot104H();
	virtual void bfmeSlot105H();
	virtual void bfmeSlot106H();
	virtual void bfmeSlot107H();
	virtual void bfmeSlot108H();
	virtual void bfmeSlot109H();
	virtual void bfmeSlot110H();
	virtual void bfmeSlot111H();
	virtual void bfmeSlot112H();
	virtual void bfmeSlot113H();
	virtual void bfmeSlot114H();
	virtual void bfmeSlot115H();
	virtual void bfmeSlot116H();
	virtual void bfmeSlot117H();
	virtual void bfmeSlot118H();
	virtual void bfmeSlot119H();
	virtual void bfmeSlot120H();
	virtual void bfmeSlot121H();
	virtual void bfmeSlot122H();
	virtual void bfmeSlot123H();
	virtual void bfmeSlot124H();
	virtual void bfmeSlot125H();
	virtual void bfmeSlot126H();
	virtual void bfmeSlot127H();
	virtual void bfmeSlot128H();
	virtual void bfmeSlot129H();
	virtual void bfmeSlot130H();
	virtual void bfmeSlot131H();
	virtual void bfmeSlot132H();
	virtual void bfmeSlot133H();
	virtual BfmeCurCB *bfmeNextCB();

	void bfmeConv1940194();

	unsigned char m_bfmeHeadCB[0x2c];
	BfmeCurCB *m_bfmeCurCB;
	unsigned char m_bfmePadCB[4];
	BfmeCurCB *m_bfmePrevCB;
};

void BfmeThingEW::bfmeConv1940194()
{
	if (m_bfmePrevCB != 0)
		return;

	if (m_bfmeCurCB->bfmeGateReadyCB())
		m_bfmeCurCB->bfmeLeaveCB();

	m_bfmePrevCB = m_bfmeCurCB;
	m_bfmeCurCB = bfmeNextCB();
	m_bfmeCurCB->bfmeEnterCB();
}
