// cl: /DNDEBUG /MD /EHsc
// readable body of ??1W3DPropBuffer@@QAE@XZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DPropBuffer.cpp
// Open-BFME: W3DPropBuffer::~W3DPropBuffer, retail 0x00702E50, 268 bytes.

typedef int Int;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Tools/Launcher/Toolkit/Support/RefCounted.h
class RefCounted
{
public:
	virtual void deleteThis() = 0;

	void releaseRef()
	{
		if (--m_refCount == 0)
			deleteThis();
	}

private:
	UnsignedInt m_refCount;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	~Snapshot() {}
	virtual void crc(void *) = 0;
	virtual void xfer(void *) = 0;
	virtual void loadPostProcess() = 0;
};

struct TProp
{
	~TProp() {}

	RefCounted *m_renderObject;
	char m_fields[0x2C];
};

struct TPropType
{
	RefCounted *m_renderObject;
	AsciiString m_renderObjectName;
	char m_bounds[0x10];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DPropBuffer.h
class W3DPropBuffer : Snapshot
{
public:
	~W3DPropBuffer();
	virtual void crc(void *);
	virtual void xfer(void *);
	virtual void loadPostProcess();

private:
	TProp m_props[4000];
	Int m_numProps;
	bool m_anythingChanged;
	bool m_initialized;
	bool m_doCull;
	TPropType m_propTypes[96];
	Int m_numPropTypes;
	RefCounted *m_propShroudMaterialPass;
	void *m_bfmeExtraField;
	RefCounted *m_light;
};

static void release(RefCounted *&object)
{
	if (object)
	{
		object->releaseRef();
		object = 0;
	}
}

W3DPropBuffer::~W3DPropBuffer()
{
	for (Int i = 0; i < m_numProps; ++i)
		release(m_props[i].m_renderObject);

	for (Int i = 0; i < 96; ++i)
		release(m_propTypes[i].m_renderObject);

	release(m_light);
	release(m_propShroudMaterialPass);
}
