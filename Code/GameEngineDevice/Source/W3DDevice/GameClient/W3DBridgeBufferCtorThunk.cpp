// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift the W3DBridgeBuffer constructor MASM dump to clean C++.
//
// The 200-element array of 0x114-byte bridges at +0x18 is built through
// `eh vector constructor iterator' (??_L at 0x009F6EE4), which is what the
// pushed size/count/ctor/dtor quartet is; 0x18 + 200 * 0x114 lands exactly on
// +0xD7B8, so the two scalars behind it close the object.
//

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class BridgeInfo
{
public:
	BridgeInfo();					///< element ctor at 0x00437AF6
	~BridgeInfo();				///< element dtor at 0x00418174

private:
	unsigned char m_unreconstructed_00[0x114];
};

// Retail tracks two unwind states -- 0 before the array call, 1 after -- so a
// destructible subobject precedes the array. The six words at +0 are that base:
// its constructor writes +0xC, which is the one store retail makes before the
// array is built, and its declared destructor is what earns the extra state.
class BridgeBufferBase
{
public:
	BridgeBufferBase() : m_0c(0) {}
	~BridgeBufferBase();

	unsigned int m_00;
	unsigned int m_04;
	unsigned int m_08;
	unsigned int m_0c;
	unsigned int m_10;
	unsigned int m_14;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DBridgeBuffer.h
class W3DBridgeBuffer : public BridgeBufferBase
{
public:
	W3DBridgeBuffer();

private:
	void freeBridgeBuffers(void);		///< ILT 0x00003E59
	void allocateBridgeBuffers(void);	///< ILT 0x0002EF2D

	BridgeInfo m_bridges[200];		///< retail this+0x18 .. +0xD7B8
	unsigned int m_d7b8;
	bool m_d7bc;
};

// ??0W3DBridgeBuffer@@QAE@XZ
W3DBridgeBuffer::W3DBridgeBuffer()
{
	m_d7bc = false;
	m_08 = 0;
	m_00 = 0;
	m_04 = 0;
	m_10 = 0;
	m_14 = 0;
	m_d7b8 = 0;

	freeBridgeBuffers();
	allocateBridgeBuffers();

	m_d7bc = true;
}
