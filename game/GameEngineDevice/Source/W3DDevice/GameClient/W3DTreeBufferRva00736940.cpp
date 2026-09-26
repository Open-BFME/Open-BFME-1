// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// W3DTreeBuffer method at retail 0x00736940: finds or adds the tree type for a template's tree draw
// module data and returns its index, or -2; a template without that module reports it and fails.

#include "ascii_string.h"

template<> inline bool StringBase<char>::isEmpty() const { return m_data == 0 || m_data->length == 0; }
template<> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }

typedef int Int;
typedef unsigned int UnsignedInt;

struct Rva00736940TreeDrawData
{
	unsigned char moduleDataBase[8];
	AsciiString m_modelName;
	AsciiString m_nameC;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
	virtual void slot00() const;
	virtual void slot01() const;
	virtual void slot02() const;
	virtual void slot03() const;
	virtual void slot04() const;
	virtual void slot05() const;
	virtual void slot06() const;
	virtual void slot07() const;
	virtual void slot08() const;
	virtual const Rva00736940TreeDrawData *getAsW3DTreeDrawModuleData() const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleInfo
{
public:
	struct Nugget
	{
		unsigned char m_names[8];
		const ModuleData *second;
		unsigned char m_rest[8];
	};

	Int getCount() const
	{
		return (Int)(m_end - m_begin);
	}

	const ModuleData *getNthData(Int i) const
	{
		if ((UnsignedInt)i < (UnsignedInt)getCount())
			return m_begin[i].second;
		return 0;
	}

private:
	Nugget *m_begin;
	Nugget *m_end;
	Nugget *m_capacity;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	const ModuleInfo &getDrawModuleInfo() const { return m_drawModuleInfo; }

	unsigned char m_pad00[0x20];
	AsciiString m_name;
	unsigned char m_pad24[0x2a0 - 0x24];
	ModuleInfo m_drawModuleInfo;
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern BfmeThingFactory *TheThingFactory;

class BfmeAwakenLog
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual BfmeAwakenLog *v38(const char *message);
	virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
	virtual void v4c(int value);
};

class BfmeAwakenDebug
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
	virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
	virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
	virtual void v60();
	virtual void v64(); virtual void v68();
	virtual BfmeAwakenLog *v6c(int first, int second);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern bool _bfme_debugReportingEnabled(void);
extern void _bfme_debugRecordCallsite(int kind);

struct Rva00736940TreeType
{
	unsigned char prefix[0x4c];
	AsciiString m_modelName;
	AsciiString m_nameC;
	unsigned char suffix[0x5c - 0x54];
};

class W3DTreeBuffer
{
public:
	Int addTreeType(const AsciiString &modelName, const AsciiString &nameC, const void *data, Int shadowKind,
		const AsciiString &textureName, const AsciiString &templateName);
	Int rva00736940(const AsciiString &templateName, Int shadowKind, const AsciiString &textureName);

private:
	unsigned char prefix[0x2a7cb9];
	bool m_needUpdate;
	unsigned char alignment[2];
	Rva00736940TreeType m_treeTypes[64];
	Int m_numTreeTypes;
};

// ?rva00736940@W3DTreeBuffer@@QAEHABVAsciiString@@H0@Z
Int W3DTreeBuffer::rva00736940(const AsciiString &templateName, Int shadowKind, const AsciiString &textureName)
{
	if (templateName.isEmpty())
		return -2;
	const ThingTemplate *tmpl = TheThingFactory->findTemplate(templateName);
	if (tmpl == 0)
		return -2;
	const ModuleData *module = tmpl->getDrawModuleInfo().getNthData(0);
	if (module == 0)
		return -2;
	const Rva00736940TreeDrawData *data = module->getAsW3DTreeDrawModuleData();
	if (data == 0) {
		if (_bfme_debugReportingEnabled()) {
			_bfme_debugRecordCallsite(1);
			TheBfmeAwakenDebug->v60();
			TheBfmeAwakenDebug->v6c(0, 0)->v38("Tree ")->v38(tmpl->m_name.str())
				->v38(" requires a W3DTreeDrawModule.\n")->v4c(2);
		}
		return -2;
	}

	Int index = -2;
	for (Int i = 0; i < m_numTreeTypes; ++i) {
		if (m_treeTypes[i].m_modelName.compareNoCase(data->m_modelName) == 0 &&
			m_treeTypes[i].m_nameC.compareNoCase(data->m_nameC) == 0) {
			index = i;
			break;
		}
	}
	if (index < 0) {
		index = addTreeType(data->m_modelName, data->m_nameC, data, shadowKind, textureName, templateName);
		if (index >= 0)
			m_needUpdate = true;
	}
	return index;
}
