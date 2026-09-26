// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWDebug
#include "Common/AsciiString.h"
#include "rendobj.h"
extern RenderObjClass *Create_Render_Obj(const char *name);
struct BfmeR1025;
extern char bfmeGo1025F(BfmeR1025 *);
class GameLODManager
{
	unsigned char m_pad[0x16c4];
public:
	int m_rva16c4;
};
extern GameLODManager *TheGameLODManager;

struct Rva006DE5A0Input
{
	unsigned char m_pad[8];
	AsciiString m_name;
	unsigned char m_flag;
};
struct Rva006DE5A0Entry
{
	RenderObjClass *m_obj;
	AsciiString m_name;
	unsigned char m_flag;
	unsigned char m_pad[3];
};
class Rva006DE5A0LodRenderSlot
{
	unsigned char m_pad[0x18];
	Rva006DE5A0Entry m_entries[10];
	int m_count;
public:
	int rva006DE5A0(AsciiString *name, Rva006DE5A0Input *record);
};
int Rva006DE5A0LodRenderSlot::rva006DE5A0(AsciiString *name, Rva006DE5A0Input *record)
{
	if (m_count >= 10)
		return 0;
	m_entries[m_count].m_obj = 0;
	AsciiString suffix;
	AsciiString chosen;
	switch (TheGameLODManager->m_rva16c4)
	{
	case 0:
	case 1: suffix = "L"; break;
	case 2: suffix = "M"; break;
	case 3:
	case 4: suffix.clear(); break;
	}
	chosen.set(*name);
	void *suffixData = *reinterpret_cast<void **>(&suffix);
	const char *suffixText;
	int suffixLength;
	if (suffixData) {
		suffixLength = *reinterpret_cast<unsigned short *>(static_cast<unsigned char *>(suffixData) + 4);
		suffixText = static_cast<const char *>(suffixData) + 8;
	} else {
		suffixLength = 0;
		suffixText = "";
	}
	reinterpret_cast<StringBase<char> *>(&chosen)->concat(suffixText, suffixLength);
	if (!bfmeGo1025F(reinterpret_cast<BfmeR1025 *>(&chosen)))
		chosen.set(*name);
	RenderObjClass *obj = Create_Render_Obj(chosen.str());
	if (!obj)
		return 0;
	if (obj->Class_ID() == RenderObjClass::CLASSID_HLOD
		|| obj->Class_ID() == RenderObjClass::CLASSID_MESH)
		m_entries[m_count].m_obj = obj;
	m_entries[m_count].m_name.set(record->m_name);
	m_entries[m_count].m_flag = record->m_flag;
	++m_count;
	return m_count - 1;
}
