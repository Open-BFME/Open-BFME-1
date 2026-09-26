// cl: /DNDEBUG /MD /EHsc
// TBuff::xfer at retail 0x006DBD00. Vtable 0x0111E134 slot 3 selects this
// body, and slot 2 at 0x006DAC30 returns the identifying name "TBuff".

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

__declspec(noreturn) void __stdcall _CxxThrowException(void *, void *);

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual Bool isLightCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void xferUser(void *, int);
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
	virtual void xferCoord3D(float *);
	virtual void slot25();
	virtual void slot26();
	virtual void xferReal(float *);
	virtual void slot28();
	virtual void slot29();
	virtual void xferUnsignedInt(UnsignedInt *);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(Bool *);
};

class TBuff
{
public:
	virtual void xfer(Xfer *);

private:
	UnsignedInt m_04;
	UnsignedInt m_08;
	float m_0c;
	UnsignedByte m_pad10[0x34];
	Bool m_44;
	float m_48[3];
	float m_54;
};

// ?xfer@TBuff@@UAEXPAVXfer@@@Z
void TBuff::xfer(Xfer *xfer)
{
	if (xfer->isLightCRC())
		return;

	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 5;
	xfer->xferVersion(&version);
	if (version.m_currentVersion < 5)
	{
		int error = 2;
		_CxxThrowException(&error, (void *)0x01239ce0);
	}

	UnsignedInt value = m_04;
	xfer->xferUnsignedInt(&value);
	xfer->xferUser(&m_08, 4);
	xfer->xferReal(&m_0c);
	xfer->xferBool(&m_44);
	xfer->xferCoord3D(m_48);
	xfer->xferReal(&m_54);
}
