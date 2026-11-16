// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Zero Hour twin: W3DBridge::init.

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

#include "../../../../Libraries/Source/WWVegas/WWMath/vector3.h"

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
