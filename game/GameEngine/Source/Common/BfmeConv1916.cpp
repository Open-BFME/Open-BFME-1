// cl: /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
#define __PLACEMENT_VEC_NEW_INLINE
#include <hash_map>
#include "Common/PlayerList.h"

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual Bool isSaving();
	virtual void slot03();
	virtual Bool isLightCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion *);
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void xferInt(int *);
};

struct BfmePlayerBR
{
	unsigned char m_bfmeHeadBR[0x24];
	int m_playerIndex;
};

class BfmeHostBR
{
public:
	void xfer(Xfer *x);

	unsigned char m_bfmeHeadBR[0xc];
	Player *m_owner;
};

void BfmeHostBR::xfer(Xfer *x)
{
	if (x->isLightCRC())
		return;

	XferVersion version;

	version.m_version = 1;
	version.m_currentVersion = 1;
	x->xferVersion(&version);

	int id;

	if (x->isSaving())
		id = ((BfmePlayerBR *)m_owner)->m_playerIndex;

	x->xferInt(&id);

	m_owner = ThePlayerList->getNthPlayer(id);
}
