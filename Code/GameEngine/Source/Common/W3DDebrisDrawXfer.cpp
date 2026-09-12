// cl: /DNDEBUG /MD /EHsc
// readable body of ?xfer@W3DDebrisDraw@@MAEXPAVXfer@@@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DDebrisDraw.cpp
// Open-BFME5: convert the W3DDebrisDraw snapshot transfer to clean C++.

typedef unsigned char XferVersion;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;
typedef int Color;

enum ShadowType
{
	SHADOW_NONE = 0
};

class FXList;

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

class Xfer
{
public:
	virtual void slot0();
	virtual bool getXferMode();
	virtual void slot2();
	virtual void slot3();
	virtual bool isDraft();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void xferVersion(XferVersion *version);
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
	virtual void xferAsciiString(AsciiString *value);
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void xferInt(Int *value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(Bool *value);
};

class W3DDebrisDrawRootBase
{
public:
	virtual ~W3DDebrisDrawRootBase();

private:
	unsigned char m_pad[8];
};

class W3DDebrisDrawDrawModule : public W3DDebrisDrawRootBase
{
public:
	virtual ~W3DDebrisDrawDrawModule() {}

protected:
	virtual void xfer(Xfer *xfer);
};

class DebrisDrawInterface
{
public:
	virtual void setModelName(AsciiString name, Color color, ShadowType type) = 0;
	virtual void setAnimNames(AsciiString initial, AsciiString flying,
		AsciiString final, const FXList *finalFX) = 0;
};

class W3DDebrisDraw : public W3DDebrisDrawDrawModule, public DebrisDrawInterface
{
public:
	virtual ~W3DDebrisDraw();
	virtual void doDrawModule(const void *transform);
	virtual void setShadowsEnabled(Bool enable);
	virtual void releaseShadows();
	virtual void allocateShadows();
	virtual void setFullyObscuredByShroud(Bool fullyObscured);
	virtual void reactToTransformChange(const void *oldMtx, const void *oldPos, float oldAngle);
	virtual void reactToGeometryChange();
	virtual void setModelName(AsciiString name, Color color, ShadowType type);
	virtual void setAnimNames(AsciiString initial, AsciiString flying,
		AsciiString final, const FXList *finalFX);

protected:
	virtual void xfer(Xfer *xfer);

private:
	AsciiString m_modelName;
	Color m_modelColor;
	AsciiString m_animInitial;
	AsciiString m_animFlying;
	AsciiString m_animFinal;
	void *m_renderObject;
	void *m_anims[3];
	const FXList *m_fxFinal;
	Int m_state;
	Int m_frames;
	Bool m_finalStop;
	void *m_shadow;
};

// ?xfer@W3DDebrisDraw@@MAEXPAVXfer@@@Z
void W3DDebrisDraw::xfer(Xfer *xfer)
{
	W3DDebrisDrawDrawModule::xfer(xfer);

	if (!xfer->isDraft())
	{
		XferVersion version[2] = {1, 1};
		xfer->xferVersion(version);

		xfer->xferAsciiString(&m_modelName);
		xfer->xferInt(&m_modelColor);
		if (xfer->getXferMode())
			setModelName(m_modelName, m_modelColor, SHADOW_NONE);

		xfer->xferAsciiString(&m_animInitial);
		xfer->xferAsciiString(&m_animFlying);
		xfer->xferAsciiString(&m_animFinal);
		if (xfer->getXferMode())
			setAnimNames(m_animInitial, m_animFlying, m_animFinal, 0);

		xfer->xferInt(&m_state);
		xfer->xferInt(&m_frames);
		xfer->xferBool(&m_finalStop);
	}
}
