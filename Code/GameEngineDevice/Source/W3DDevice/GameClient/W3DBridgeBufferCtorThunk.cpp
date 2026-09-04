// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift the W3DBridgeBuffer constructor MASM dump to clean C++.
//
// The 200-element array of 0x114-byte bridges at +0x18 is built through
// `eh vector constructor iterator' (??_L at 0x009F6EE4), which is what the
// pushed size/count/ctor/dtor quartet is; 0x18 + 200 * 0x114 lands exactly on
// +0xD7B8, so the two scalars behind it close the object.
//

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class W3DBridge
{
public:
	W3DBridge();					///< element ctor at 0x00437AF6
	~W3DBridge();				///< element dtor at 0x00418174

private:
	unsigned char m_unreconstructed_00[0x114];
};

// Retail tracks two unwind states -- 0 before the array call, 1 after -- so a
// destructible subobject precedes the array. The six words at +0 are that base:
// its constructor writes +0xC, which is the one store retail makes before the
// array is built, and its declared destructor is what earns the extra state.
class W3DBridgeBufferPrefix
{
public:
	W3DBridgeBufferPrefix() : m_bridgeTexture(0) {}
	~W3DBridgeBufferPrefix();

	unsigned int m_vertexBridge;
	unsigned int m_indexBridge;
	unsigned int m_vertexMaterial;
	unsigned int m_bridgeTexture;
	unsigned int m_curNumBridgeVertices;
	unsigned int m_curNumBridgeIndices;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DBridgeBuffer.h
class W3DBridgeBuffer : public W3DBridgeBufferPrefix
{
public:
	W3DBridgeBuffer();

private:
	void freeBridgeBuffers(void);		///< ILT 0x00003E59
	void allocateBridgeBuffers(void);	///< ILT 0x0002EF2D

	W3DBridge m_bridges[200];		///< retail this+0x18 .. +0xD7B8
	unsigned int m_numBridges;
	bool m_initialized;
};

// ??0W3DBridgeBuffer@@QAE@XZ
W3DBridgeBuffer::W3DBridgeBuffer()
{
	m_initialized = false;
	m_vertexMaterial = 0;
	m_vertexBridge = 0;
	m_indexBridge = 0;
	m_curNumBridgeVertices = 0;
	m_curNumBridgeIndices = 0;
	m_numBridges = 0;

	freeBridgeBuffers();
	allocateBridgeBuffers();

	m_initialized = true;
}
