// ?addProp@BaseHeightMapRenderObjClass@@QAEXHVCoord3D@@MMABVAsciiString@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?addProp@BaseHeightMapRenderObjClass@@QAEXHUCoord3D@@MMABVAsciiString@@@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp
// Open-BFME5: clean C++ terrain prop-buffer forwarding body.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
public:
	Coord3D(const Coord3D &that) : x(that.x), y(that.y), z(that.z) {}
	~Coord3D(void) {}
	float x, y, z;
};
class AsciiString;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DPropBuffer.h
class W3DPropBuffer
{
public:
	void addProp(int id, Coord3D location, float angle, float scale,
		const AsciiString &modelName);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/BaseHeightMap.h
class BaseHeightMapRenderObjClass
{
public:
	void addProp(int id, Coord3D location, float angle, float scale,
		const AsciiString &modelName);
private:
	char m_pad[0x309c];
	W3DPropBuffer *m_propBuffer;
};

void BaseHeightMapRenderObjClass::addProp(int id, Coord3D location,
	float angle, float scale, const AsciiString &modelName)
{
	if (m_propBuffer)
		m_propBuffer->addProp(id, location, angle, scale, modelName);
}
