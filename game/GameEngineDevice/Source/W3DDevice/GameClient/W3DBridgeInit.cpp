// cl: /DNDEBUG /MD /EHsc
// Zero Hour twin: W3DBridge::init.

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class Vector3
{
public:
	float X, Y, Z;
	Vector3 &operator=(const Vector3 &other)
	{
		X = other.X;
		Y = other.Y;
		Z = other.Z;
		return *this;
	}
};

class W3DBridge
{
public:
	void init(Vector3 fromLoc, Vector3 toLoc, AsciiString bridgeTemplateName);

private:
	Vector3 m_start;
	Vector3 m_end;
	unsigned char m_unmodelled_018[0x108 - 0x18];
	AsciiString m_templateName;
	unsigned char m_unmodelled_10C[0x110 - 0x10C];
	unsigned char m_enabled;
};

// @?init@W3DBridge@@QAEXVVector3@@0VAsciiString@@@Z 0x006D8920
void W3DBridge::init(Vector3 fromLoc, Vector3 toLoc, AsciiString bridgeTemplateName)
{
	m_start = fromLoc;
	m_end = toLoc;
	m_templateName = bridgeTemplateName;
	m_enabled = true;
}
