// ?bfmeReactCK@BfmeHostCK@Rva0024CE60@@UAEXPAVBfmeSrcCK@2@@Z
// partial score=0.9803921569 date=2026-09-22
// ?bfmeReactCK@BfmeHostCK@Rva0024CE60@@UAEXPAVBfmeSrcCK@2@@Z
// Native secondary-base view; diagnostic constructor omitted from this bank.
namespace Rva0024CE60 {
// Scratch-only native multiple-inheritance probe for retail RVA 0x0024CE60.
// The names and branch/control-flow model are retained from the banked body.

class BfmeThingCK;
class BfmeSrcCK;

class BfmeThingCK
{
public:
#define BFME_THING_SLOT(N) virtual void bfmeSlot##N##T();
	BFME_THING_SLOT(000) BFME_THING_SLOT(001) BFME_THING_SLOT(002)
	BFME_THING_SLOT(003) BFME_THING_SLOT(004) BFME_THING_SLOT(005)
	BFME_THING_SLOT(006) BFME_THING_SLOT(007) BFME_THING_SLOT(008)
	BFME_THING_SLOT(009) BFME_THING_SLOT(010) BFME_THING_SLOT(011)
	BFME_THING_SLOT(012) BFME_THING_SLOT(013) BFME_THING_SLOT(014)
	BFME_THING_SLOT(015) BFME_THING_SLOT(016) BFME_THING_SLOT(017)
	BFME_THING_SLOT(018) BFME_THING_SLOT(019) BFME_THING_SLOT(020)
	BFME_THING_SLOT(021) BFME_THING_SLOT(022) BFME_THING_SLOT(023)
	BFME_THING_SLOT(024) BFME_THING_SLOT(025) BFME_THING_SLOT(026)
	BFME_THING_SLOT(027) BFME_THING_SLOT(028) BFME_THING_SLOT(029)
	BFME_THING_SLOT(030) BFME_THING_SLOT(031) BFME_THING_SLOT(032)
	BFME_THING_SLOT(033) BFME_THING_SLOT(034) BFME_THING_SLOT(035)
	BFME_THING_SLOT(036) BFME_THING_SLOT(037) BFME_THING_SLOT(038)
	BFME_THING_SLOT(039) BFME_THING_SLOT(040) BFME_THING_SLOT(041)
	BFME_THING_SLOT(042) BFME_THING_SLOT(043) BFME_THING_SLOT(044)
	BFME_THING_SLOT(045) BFME_THING_SLOT(046) BFME_THING_SLOT(047)
	BFME_THING_SLOT(048) BFME_THING_SLOT(049) BFME_THING_SLOT(050)
	BFME_THING_SLOT(051) BFME_THING_SLOT(052) BFME_THING_SLOT(053)
	BFME_THING_SLOT(054) BFME_THING_SLOT(055) BFME_THING_SLOT(056)
	BFME_THING_SLOT(057) BFME_THING_SLOT(058) BFME_THING_SLOT(059)
	BFME_THING_SLOT(060) BFME_THING_SLOT(061) BFME_THING_SLOT(062)
	BFME_THING_SLOT(063)
	virtual void bfmeMarkCK();
#undef BFME_THING_SLOT
};

class BfmeOwnerCK
{
public:
#define BFME_OWNER_SLOT(N) virtual void bfmeSlot##N##O();
	BFME_OWNER_SLOT(000) BFME_OWNER_SLOT(001) BFME_OWNER_SLOT(002)
	BFME_OWNER_SLOT(003) BFME_OWNER_SLOT(004) BFME_OWNER_SLOT(005)
	BFME_OWNER_SLOT(006) BFME_OWNER_SLOT(007) BFME_OWNER_SLOT(008)
	BFME_OWNER_SLOT(009) BFME_OWNER_SLOT(010) BFME_OWNER_SLOT(011)
	BFME_OWNER_SLOT(012) BFME_OWNER_SLOT(013) BFME_OWNER_SLOT(014)
	BFME_OWNER_SLOT(015) BFME_OWNER_SLOT(016) BFME_OWNER_SLOT(017)
	BFME_OWNER_SLOT(018) BFME_OWNER_SLOT(019) BFME_OWNER_SLOT(020)
	BFME_OWNER_SLOT(021) BFME_OWNER_SLOT(022) BFME_OWNER_SLOT(023)
	BFME_OWNER_SLOT(024) BFME_OWNER_SLOT(025)
	virtual BfmeThingCK *bfmeGetCK();
#undef BFME_OWNER_SLOT
};

// The witnessed primary subobject is exactly vptr + 0x1c bytes of padding.
class BfmeSubCK
{
public:
#define BFME_SUB_SLOT(N) virtual void bfmeSlot##N##S();
	BFME_SUB_SLOT(000) BFME_SUB_SLOT(001) BFME_SUB_SLOT(002)
	BFME_SUB_SLOT(003) BFME_SUB_SLOT(004) BFME_SUB_SLOT(005)
	BFME_SUB_SLOT(006) BFME_SUB_SLOT(007) BFME_SUB_SLOT(008)
	BFME_SUB_SLOT(009) BFME_SUB_SLOT(010) BFME_SUB_SLOT(011)
	BFME_SUB_SLOT(012) BFME_SUB_SLOT(013) BFME_SUB_SLOT(014)
	BFME_SUB_SLOT(015) BFME_SUB_SLOT(016)
	virtual void bfmeFinishCK();

	void bfmeFirstCK(BfmeSrcCK *src);
	void bfmeSecondCK(BfmeSrcCK *src);

private:
	unsigned char m_witnessedPrimaryPaddingCK[0x1c];
};

typedef char BfmeSubCK_must_be_0x20[sizeof(BfmeSubCK) == 0x20 ? 1 : -1];

// The retail constructor/vtable witness places this interface at +0x20.
class Rva0024CE60SecondaryCK
{
public:
#define BFME_REACT_SLOT(N) virtual void bfmeReactSlot##N##CK();
	BFME_REACT_SLOT(00) BFME_REACT_SLOT(01) BFME_REACT_SLOT(02)
	BFME_REACT_SLOT(03) BFME_REACT_SLOT(04) BFME_REACT_SLOT(05)
	BFME_REACT_SLOT(06) BFME_REACT_SLOT(07) BFME_REACT_SLOT(08)
	BFME_REACT_SLOT(09) BFME_REACT_SLOT(10) BFME_REACT_SLOT(11)
	BFME_REACT_SLOT(12) BFME_REACT_SLOT(13) BFME_REACT_SLOT(14)
	BFME_REACT_SLOT(15) BFME_REACT_SLOT(16) BFME_REACT_SLOT(17)
	BFME_REACT_SLOT(18) BFME_REACT_SLOT(19) BFME_REACT_SLOT(20)
	BFME_REACT_SLOT(21) BFME_REACT_SLOT(22) BFME_REACT_SLOT(23)
	BFME_REACT_SLOT(24) BFME_REACT_SLOT(25) BFME_REACT_SLOT(26)
	BFME_REACT_SLOT(27) BFME_REACT_SLOT(28) BFME_REACT_SLOT(29)
	BFME_REACT_SLOT(30) BFME_REACT_SLOT(31) BFME_REACT_SLOT(32)
	BFME_REACT_SLOT(33)
	virtual void bfmeReactCK(BfmeSrcCK *src);
#undef BFME_REACT_SLOT
};

typedef char Rva0024CE60SecondaryCK_must_be_0x4
	[(sizeof(Rva0024CE60SecondaryCK) == 0x4 ? 1 : -1)];

class BfmeSrcCK
{
public:
	unsigned char m_bfmeHeadCK[0x94];
	unsigned char m_bfmeFlagsCK;
	unsigned char m_bfmeMidCK[0x167];
	BfmeOwnerCK *m_bfmeOwnerCK;
	unsigned char m_bfmeTailCK[0x14];
	int m_bfmeGuardCK;
};

typedef char BfmeSrcCK_must_be_0x218[sizeof(BfmeSrcCK) == 0x218 ? 1 : -1];

// Native MI makes the secondary interface the receiver representation of the
// virtual override.  The primary base remains at complete-object +0x00.
class BfmeHostCK : public BfmeSubCK, public Rva0024CE60SecondaryCK
{
public:
	void bfmeReactCK(BfmeSrcCK *src);
};

typedef char BfmeHostCK_must_be_0x24
	[(sizeof(BfmeHostCK) == 0x24 ? 1 : -1)];

void BfmeHostCK::bfmeReactCK(BfmeSrcCK *src)
{
	if (src->m_bfmeGuardCK != 0)
		return;

	BfmeOwnerCK *owner = src->m_bfmeOwnerCK;
	BfmeThingCK *thing;

	if (owner != 0 && (thing = owner->bfmeGetCK()) != 0)
	{
		thing->bfmeMarkCK();
		bfmeFirstCK(src);
		bfmeFinishCK();
	}
	else if ((src->m_bfmeFlagsCK & 0x20) != 0)
	{
		bfmeSecondCK(src);
		bfmeFinishCK();
	}
}

}
