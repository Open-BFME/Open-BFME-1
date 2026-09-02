// ?addProp@BaseHeightMapRenderObjClass@@QAEXHVCoord3D@@MMABVAsciiString@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: clean C++ terrain prop-buffer forwarding body.

struct Coord3D
{
public:
	Coord3D(const Coord3D &that) : x(that.x), y(that.y), z(that.z) {}
	~Coord3D(void) {}
	float x, y, z;
};
class AsciiString;

class W3DPropBuffer
{
public:
	void addProp(int id, Coord3D location, float angle, float scale,
		const AsciiString &modelName);
};

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
