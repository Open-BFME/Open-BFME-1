// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline
// Open-BFME5: byte-exact C++ reconstruction of W3DBridgeBuffer::addBridge.

#include "StringInline.h"

class Vector3
{
	public:
	float X;
	float Y;
	float Z;

	Vector3() {}
	Vector3(const Vector3 &v)
	{
		X = v.X;
		Y = v.Y;
		Z = v.Z;
	}
};

class Dict;

enum BodyDamageType
{
	BODY_PRISTINE
};

class BridgeInfo
{
	public:
	BridgeInfo();

	public:
	char pad000[0x4c];
	int bridgeIndex;
	char pad050[0x18];
	unsigned char damageStateChanged;
};

class W3DBridge
{
public:
	void init(Vector3 fromLoc, Vector3 toLoc, AsciiString name);
	bool load(BodyDamageType curDamageState);
	void getBridgeInfo(BridgeInfo *info);

	char pad000[0x114];
};

class W3DTerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
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
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void addBridgeToLogic(BridgeInfo *info, Dict *props, AsciiString name);
};

class W3DBridgeBuffer
{
protected:
	void addBridge(Vector3 fromLoc, Vector3 toLoc, AsciiString name,
		W3DTerrainLogic *pTerrainLogic, Dict *props);

	char pad000[0x18];
	W3DBridge m_bridges[200];
	int m_numBridges;
	unsigned char m_initialized;
};

// ?addBridge@W3DBridgeBuffer@@IAEXVVector3@@0VAsciiString@@PAVW3DTerrainLogic@@PAVDict@@@Z
void W3DBridgeBuffer::addBridge(Vector3 fromLoc, Vector3 toLoc, AsciiString name,
	W3DTerrainLogic *pTerrainLogic, Dict *props)
{
	if (m_numBridges >= 200)
		return;

	if (!m_initialized)
		return;

	m_bridges[m_numBridges].init(fromLoc, toLoc, name);
	if (m_bridges[m_numBridges].load(BODY_PRISTINE))
	{
		W3DBridge *pBridge = m_bridges + m_numBridges;
		if (pTerrainLogic)
		{
			BridgeInfo info;
			pBridge->getBridgeInfo(&info);
			info.bridgeIndex = m_numBridges;
			pTerrainLogic->addBridgeToLogic(&info, props, name);
		}
		m_numBridges++;
	}
}
