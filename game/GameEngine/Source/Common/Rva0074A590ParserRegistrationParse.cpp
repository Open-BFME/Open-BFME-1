// Retail 0x0074D2D0 (474 B, ret 8): slot 1 of vtable 0x01121B24, which the
// NamedCameras registration constructor 0x0074A590
// (Rva0074A590ParserRegistrationCtor.cpp) installs; the vtable slot reaches
// it through ILT 0x0004B4CF, its only reference. The sibling registration
// 0x0074A680 has ParseLightingDataChunk in the same slot. It reads the camera
// count, then per camera a position, a name, nine-or-so reals (the second
// only from chunk version 2) into a 0x30-byte node pushed on the list at
// +0x0C. The catch(...) funclet at +0x191 frees the list and rethrows; it
// was rowed alone as ?d_0074d461 before. The member meanings are unproven,
// so the method and fields keep address or offset names.
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseascii/Common /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Include

#include "AsciiString.h"
#include "Lib/Coord3D.h"

inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

#include "../../Include/Common/ScalarTypes.h"

typedef unsigned short DataChunkVersionType;


class DataChunkInput
{
public:
	Int readInt();
	Real readReal();
	AsciiString readAsciiString();
};

struct DataChunkInfo
{
	AsciiString label;
	AsciiString parentLabel;
	DataChunkVersionType version;
	Int dataSize;
};

class UserParser;

struct Rva0074D2D0NamedCamera
{
	Rva0074D2D0NamedCamera(const AsciiString &name, const Coord3D &pos,
		Real f14, Real f18, Real f1c, Real f20, Real f24, Real f28)
		: m_next(0), m_name(name), m_x(pos.x), m_y(pos.y), m_z(pos.z), m_14(f14), m_18(f18),
		  m_1c(f1c), m_20(f20), m_24(f24), m_28(f28), m_2c(false) {}

	Rva0074D2D0NamedCamera *m_next;
	AsciiString m_name;
	Real m_x;
	Real m_y;
	Real m_z;
	Real m_14;
	Real m_18;
	Real m_1c;
	Real m_20;
	Real m_24;
	Real m_28;
	bool m_2c;
};

class Rva0074A590ParserRegistration
{
public:
	virtual ~Rva0074A590ParserRegistration();
	virtual bool rva0074D2D0(DataChunkInput &file, DataChunkInfo *info);

private:
	DataChunkInput *m_table;
	UserParser *m_parser;
	Rva0074D2D0NamedCamera **m_cameras;
};

bool Rva0074A590ParserRegistration::rva0074D2D0(DataChunkInput &file, DataChunkInfo *info)
{
	Int count = file.readInt();
	try
	{
		while (count)
		{
			--count;
			AsciiString name;
			Coord3D pos;
			pos.x = file.readReal();
			pos.y = file.readReal();
			pos.z = file.readReal();
			name = file.readAsciiString();
			Real f1c = file.readReal();
			Real f20;
			if (info->version >= 2)
				f20 = file.readReal();
			else
				f20 = 0.0f;
			Real f18 = file.readReal();
			Real f24 = file.readReal();
			Real f28 = file.readReal();
			Real f14 = file.readReal();
			Rva0074D2D0NamedCamera *camera = new Rva0074D2D0NamedCamera(name, pos,
				f14, f18, f1c, f20, f24, f28);
			camera->m_next = *m_cameras;
			*m_cameras = camera;
		}
	}
	catch (...)
	{
		Rva0074D2D0NamedCamera *camera;
		while ((camera = *m_cameras) != 0)
		{
			*m_cameras = camera->m_next;
			delete camera;
		}
		throw;
	}
	return true;
}
