// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?findModuleInterfaceMask@ModuleFactory@@QAEHABVAsciiString@@W4ModuleType@@@Z: Code/GameEngine/Source/Common/Thing/ModuleFactory.cpp
// Lift the ModuleFactory::findModuleInterfaceMask naked dump to clean C++.
//
// Zero Hour's body, with findModuleTemplate inlined into it -- retail has no
// call to that helper, only the two things it does: decorate the name into a
// NameKeyType and look that up in m_moduleTemplateMap.
//
// The decorating helper at ILT 0x0044B439 is reached with cdecl argument order
// and an eight-byte stack cleanup, so it is a static member. Its body at
// 0x00526260 reserves a 256-byte buffer, writes '0' + type into the first byte,
// strcpy's the name after it and hands the result to TheNameKeyGenerator -- ZH's
// makeDecoratedNameKey exactly.
//
// The map lookup at ILT 0x0040C054 is a red-black tree walk that returns its
// iterator through a hidden pointer, so the iterator has to be a class MSVC
// cannot return in eax; declaring a copy constructor is enough to force the
// memory return and reproduce the push-key-then-push-result order.
//
// Retail pins the layout: the map is at this+0x0C and its first word is the
// header node that end() compares against, the mapped ModuleTemplate begins at
// node+0x14, and the interface mask sits at template+0x0C. isEmpty() inlines to
// "m_data == 0 || m_data->m_len == 0" against the word at data+0x04.
//
// The three rejections share one `xor eax,eax` tail while the hit has its own
// pop/ret, so the body is a nested if with a single trailing return 0.

typedef int Int;
typedef int NameKeyType;

enum ModuleType { MODULETYPE_FIRST = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiStringData
{
public:
	unsigned char m_unreconstructed_00[4];
	unsigned short m_len;								///< retail this+0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	bool isEmpty(void) const { return m_data == 0 || m_data->m_len == 0; }

private:
	AsciiStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ModuleFactory.h
class ModuleTemplate
{
public:
	unsigned char m_unreconstructed_00[0x0C];
	Int m_whichInterfaces;								///< retail this+0x0C
};

struct ModuleTemplateNode
{
	unsigned char m_unreconstructed_00[0x14];
	ModuleTemplate second;								///< retail node+0x14
};

// A bare pointer would come back in eax; the declared copy constructor is what
// forces the hidden-return-pointer form retail calls with.
struct ModuleTemplateMapIterator
{
	ModuleTemplateMapIterator(const ModuleTemplateMapIterator &);

	ModuleTemplateNode *node;
};

class ModuleTemplateMap
{
public:
	ModuleTemplateMapIterator find(const NameKeyType &key) const;	///< ILT thunk at 0x0000C054

	ModuleTemplateNode *end(void) const { return m_header; }

private:
	ModuleTemplateNode *m_header;						///< retail this+0x00
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ModuleFactory.h
class ModuleFactory
{
public:
	Int findModuleInterfaceMask(const AsciiString &name, ModuleType type);

	static NameKeyType makeDecoratedNameKey(const AsciiString &name, ModuleType type);	///< ILT thunk at 0x0004B439

private:
	const ModuleTemplate *findModuleTemplate(const AsciiString &name, ModuleType type)
	{
		NameKeyType namekey = makeDecoratedNameKey(name, type);

		ModuleTemplateMapIterator it = m_moduleTemplateMap.find(namekey);
		if (it.node == m_moduleTemplateMap.end())
		{
			return 0;
		}
		return &it.node->second;
	}

	unsigned char m_unreconstructed_00[0x0C];
	ModuleTemplateMap m_moduleTemplateMap;				///< retail this+0x0C
};

// ?findModuleInterfaceMask@ModuleFactory@@QAEHABVAsciiString@@W4ModuleType@@@Z
Int ModuleFactory::findModuleInterfaceMask(const AsciiString &name, ModuleType type)
{
	if (!name.isEmpty())
	{
		const ModuleTemplate *moduleTemplate = findModuleTemplate(name, type);
		if (moduleTemplate)
		{
			return moduleTemplate->m_whichInterfaces;
		}
	}

	return 0;
}
