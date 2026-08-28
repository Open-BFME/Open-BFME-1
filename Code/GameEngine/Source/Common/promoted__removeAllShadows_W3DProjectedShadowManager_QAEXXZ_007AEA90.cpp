// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?removeAllShadows@W3DProjectedShadowManager@@QAEXXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadow.cpp

// Three lists, walked the same way: take the head, null it, then mark every
// entry unused and follow the link at +0xd4. Nothing is freed here -- the flag
// at +4 is what defers that.
//
// The walk is a helper rather than three copies of a loop. Written out three
// times the compiler materialises the constants afresh in each; shared, the
// values 0 and 1 are live across all three bodies and earn registers, which is
// what retail holds them in -- edx and bl, with ebx pushed to afford the second.
//
// The reference declares two lists, m_shadowList and m_decalList. Retail walks
// three and takes the one at +0xc first, so BFME added a list ahead of the pair
// in processing order but behind them in the layout.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DProjectedShadow.h
class W3DProjectedShadow
{
public:
	unsigned char m_head[4];
	bool m_unused;
	unsigned char m_body[0xCF];
	W3DProjectedShadow *m_next;
};

static void markListUnused(W3DProjectedShadow *shadow)
{
	while (shadow) {
		shadow->m_unused = true;
		shadow = shadow->m_next;
	}
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shadow.h
class ProjectedShadowManager
{
public:
	virtual ~ProjectedShadowManager();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DProjectedShadow.h
class W3DProjectedShadowManager : public ProjectedShadowManager
{
public:
	void removeAllShadows(void);

private:
	W3DProjectedShadow *m_shadowList;
	W3DProjectedShadow *m_decalList;
	W3DProjectedShadow *m_simpleDecalList;
};

// ?removeAllShadows@W3DProjectedShadowManager@@QAEXXZ
void W3DProjectedShadowManager::removeAllShadows(void)
{
	W3DProjectedShadow *shadow;

	shadow = m_simpleDecalList;
	m_simpleDecalList = 0;
	markListUnused(shadow);

	shadow = m_shadowList;
	m_shadowList = 0;
	markListUnused(shadow);

	shadow = m_decalList;
	m_decalList = 0;
	markListUnused(shadow);
}
