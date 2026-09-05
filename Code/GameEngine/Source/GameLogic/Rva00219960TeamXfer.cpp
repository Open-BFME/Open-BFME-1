// cl: /DNDEBUG /MD /EHsc
// Address-derived owner: retail 0x00219960. Snapshot xfer with TheTeamFactory
// at VA 0x012ED810. Base thunk 0x000489DC reaches 0x002298B0.
// The owner is address-derived; older Gen_0022CD40 pin label was misleading.

typedef unsigned int UnsignedInt;
typedef bool Bool;

struct XferVersion
{
	unsigned char m_version;
	unsigned char m_currentVersion;
};

struct XferException
{
	char *text;
	int tag;
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

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);
extern int g_guardTargetTypeThrowInfo;

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
	friend class Rva00219960;
	void xferBase2298B0(Xfer *target);
};

class Rva00219960 : public BfmeBase002298B0
{
public:
	void xfer(Xfer *xfer);

private:
	unsigned char m_pad[0xD8];
	Bool m_flag;
	int m_value;
	Team *m_team;
};

// ?xfer@Rva00219960@@QAEXPAVXfer@@@Z
void Rva00219960::xfer(Xfer *xfer)
{
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
				XferException error;
				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
			}
		}
		else
			m_team = 0;
	}
}
