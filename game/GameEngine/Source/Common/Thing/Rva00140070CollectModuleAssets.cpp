// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// ThingTemplate::GetAssetList calls this module asset collector at RVA 0x00140070.

#include <vector>
#include "ascii_string.h"

typedef int Int;

class ModuleData;

class BFMERetailAsciiString
{
private:
	void releaseBuffer();
	char *m_data;

public:
	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

	operator const AsciiString &() const
	{
		return *(const AsciiString *)this;
	}
};

class ModuleInfo
{
private:
	struct Nugget
	{
		BFMERetailAsciiString first;
		BFMERetailAsciiString second;
		const ModuleData *data;
		char padding[8];
	};

	std::vector<Nugget> m_info;

public:
	Int getCount() const
	{
		return m_info.size();
	}

	BFMERetailAsciiString getNthName(Int i) const;

	const ModuleData *getNthData(Int i) const
	{
		if (i >= 0 && i < m_info.size())
			return m_info[i].data;
		return 0;
	}
};

enum ModuleType
{
};

class ModuleFactory
{
public:
	void *rva00127e80(const AsciiString &name, void *data, ModuleType type,
		void *context, void *assets);
};

extern ModuleFactory *TheModuleFactory;

class Rva00140070
{
public:
	static void collectModuleAssets(ModuleInfo *moduleInfo, Int type,
		void *assets, void *context);
};

void Rva00140070::collectModuleAssets(ModuleInfo *moduleInfo, Int type,
	void *assets, void *context)
{
	for (Int i = 0; i < moduleInfo->getCount(); ++i)
	{
		TheModuleFactory->rva00127e80(moduleInfo->getNthName(i),
			(void *)moduleInfo->getNthData(i), (ModuleType)type, context, assets);
	}
}
