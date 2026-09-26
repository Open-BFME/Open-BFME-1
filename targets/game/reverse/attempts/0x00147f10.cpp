// ?initForLTA@ThingTemplate@@QAEXABVAsciiString@@@Z
// partial score=0.62 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/ini_bfme /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include "PreRTS.h"
#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"
#include "Common/GameCommon.h"
#include "Common/GlobalData.h"
#include "Common/ModuleFactory.h"
#include "Common/ThingTemplate.h"
#include "GameClient/Shadow.h"

class BfmeThingTemplateString
{
public:
	void set(const AsciiString &source)
	{
		((StringBase<char> *)this)->set(*(const StringBase<char> *)&source);
	}

	const char *str() const
	{
		return ((const StringBase<char> *)this)->str();
	}
};

static BfmeThingTemplateString &bfmeLtaName(ThingTemplate *self)
{
	return *(BfmeThingTemplateString *)((char *)self + 0x5c);
}

static BfmeThingTemplateString &bfmeTemplateName(ThingTemplate *self)
{
	return *(BfmeThingTemplateString *)((char *)self + 0x20);
}

static UnicodeString &bfmeDisplayName(ThingTemplate *self)
{
	return *(UnicodeString *)((char *)self + 0x0c);
}

static GeometryInfo &bfmeGeometry(ThingTemplate *self)
{
	return *(GeometryInfo *)((char *)self + 0x60);
}

static ModuleInfo &bfmeModuleInfo(ThingTemplate *self, unsigned int offset)
{
	return *(ModuleInfo *)((char *)self + offset);
}

class BFMEThingTemplateInitCarrier
{
public:
	void init(const AsciiString &name);
};

void BFMEThingTemplateInitCarrier::init(const AsciiString &name)
{
	ThingTemplate *self = (ThingTemplate *)this;
	bfmeTemplateName(self).set(name);

	char buffer[1024];
	strncpy(buffer, name.str(), sizeof(buffer));
	int i;
	for (i = 0; buffer[i]; ++i)
	{
		if (buffer[i] == '/')
		{
			++i;
			break;
		}
	}

	AsciiString ltaName(buffer + i);
	bfmeLtaName(self).set(ltaName);
	bfmeModuleInfo(self, 0x294).clear();
	bfmeModuleInfo(self, 0x2a0).clear();
	bfmeModuleInfo(self, 0x2ac).clear();

	AsciiString moduleTag;
	moduleTag.format("LTA_%sDestroyDie", bfmeLtaName(self).str());
	bfmeModuleInfo(self, 0x294).addModuleInfo(
		self, "DestroyDie", moduleTag,
		TheModuleFactory->newModuleDataFromINI(NULL, "DestroyDie", MODULETYPE_BEHAVIOR, moduleTag),
		MODULEINTERFACE_DIE, false);

	moduleTag.format("LTA_%sInactiveBody", bfmeLtaName(self).str());
	bfmeModuleInfo(self, 0x294).addModuleInfo(
		self, "InactiveBody", moduleTag,
		TheModuleFactory->newModuleDataFromINI(NULL, "InactiveBody", MODULETYPE_BEHAVIOR, moduleTag),
		MODULEINTERFACE_BODY, false);

	moduleTag.format("LTA_%sW3DDefaultDraw", bfmeLtaName(self).str());
	bfmeModuleInfo(self, 0x2a0).addModuleInfo(
		self, "W3DDefaultDraw", moduleTag,
		TheModuleFactory->newModuleDataFromINI(NULL, "W3DDefaultDraw", MODULETYPE_DRAW, moduleTag),
		MODULEINTERFACE_DRAW, false);

	*(unsigned char *)((char *)self + 0x489) = 0;
	*(unsigned char *)((char *)self + 0x48a) = 0;
	*(KindOfMaskType *)((char *)self + 0xc8) = KINDOFMASK_NONE;
	*(Real *)((char *)self + 0x3c0) = 1.0f;
	*(Real *)((char *)self + 0x3c4) = 0.0f;
	*(unsigned char *)((char *)self + 0x497) = 0;
	bfmeDisplayName(self).translate(name);
	*(unsigned short *)((char *)self + 0x482) = SHADOW_VOLUME;
	bfmeGeometry(self).set(GEOMETRY_SPHERE, false, 10.0f, 10.0f, 10.0f);
}
