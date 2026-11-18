// cl: /DNDEBUG /MD /EHsc
// CaveContain::DoXfer at retail 0x00219960 (EA's name, ea_evidence.csv).
// Snapshot xfer with TheTeamFactory at VA 0x012ED810. Base thunk 0x000489DC
// reaches 0x002298B0. Retail's thunk table fits only the protected virtual
// Xfer& decoration ?DoXfer@CaveContain@@MAEXAAVXfer@@@Z.

#include "../../../../Include/Common/ScalarTypes.h"


struct XferVersion
{
	unsigned char m_version;
	unsigned char m_currentVersion;
};

class Team
{
public:
	UnsignedInt getID() const { return m_id; }

private:
	unsigned char m_beforeId[8];
	UnsignedInt m_id;
};

class TeamFactory
{
public:
	Team *findTeamByID(UnsignedInt id);
};

extern TeamFactory *TheTeamFactory;

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);
	char *text;
	int tag;
};

class Xfer
{
public:
	virtual void slot00();
	virtual Bool isLoading();
	virtual void slot02();
	virtual void slot03();
	virtual Bool isLightCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Xfer &xferVersion(XferVersion *version);
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
	virtual Xfer &xferUnsignedInt(UnsignedInt *value);
	virtual Xfer &xferInt(int *value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual Xfer &xferBool(Bool *value);
};



class BfmeBase002298B0
{
	friend class CaveContain;
	void xferBase2298B0(Xfer *target);

protected:
	virtual void DoXfer(Xfer &xfer);
};

class CaveContain : public BfmeBase002298B0
{
protected:
	virtual void DoXfer(Xfer &xfer);

private:
	unsigned char m_pad[0xD4];
	Bool m_flag;
	int m_value;
	Team *m_team;
};

// ?DoXfer@CaveContain@@MAEXAAVXfer@@@Z
void CaveContain::DoXfer(Xfer &xferRef)
{
	Xfer *xfer = &xferRef;
	xferBase2298B0(xfer);
	if (xfer->isLightCRC())
		return;

	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);
	xfer->xferBool(&m_flag);
	xfer->xferInt(&m_value);

	UnsignedInt teamID = m_team ? m_team->getID() : 0;
	xfer->xferUnsignedInt(&teamID);
	if (xfer->isLoading())
	{
		if (teamID)
		{
			m_team = TheTeamFactory->findTeamByID(teamID);
			if (m_team == 0)
			{
				throw XferException(5, 0);
			}
		}
		else
			m_team = 0;
	}
}

// Retail calls the shared snapshot routine (0x002298B0, still a gen_asm dump)
// through its ILT at 0x000489DC, where symbols.csv pins xferBase2298B0.
#pragma comment(linker, "/alternatename:?xferBase2298B0@BfmeBase002298B0@@AAEXPAVXfer@@@Z=?j_000489dc@@YAXXZ")
