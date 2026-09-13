// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#include "PreRTS.h"
#include "Common/INI.h"
#include "string_base.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)


class ParticleSystemInfo
{
	public:
		virtual ~ParticleSystemInfo();

	private:
		unsigned char m_pad[0x94];
};

class ParticleSystemTemplate : public ParticleSystemInfo
{
	public:
		ParticleSystemTemplate(const AsciiString &name);
		virtual ~ParticleSystemTemplate();
};

namespace FXParticleSystem
{
	class TemplateMap
	{
	public:
		struct Node
		{
			void *unused0;
			void *unused1;
			ParticleSystemTemplate *value;
		};

		Node *find(const AsciiString *name);
	};
}

class ParticleSystemManager
{
public:
	ParticleSystemTemplate *newTemplate(const AsciiString &name);
	ParticleSystemTemplate *findTemplate(const AsciiString &name)
	{
		// The local order reproduces the retail map lookup register layout.
		ParticleSystemTemplate *sysTemplate = 0;
		FXParticleSystem::TemplateMap *templates = &m_templates;
		FXParticleSystem::TemplateMap::Node *node =
			templates->find(&name);
		if (node != 0)
			sysTemplate = node->value;
		return sysTemplate;
	}

private:
	unsigned char m_pad[0x9c];

public:
	FXParticleSystem::TemplateMap m_templates;
};

extern ParticleSystemManager *TheParticleSystemManager;

struct BfmeCategoryHead1054;
extern void j_0001f7c6(void) throw();
extern void j_0002aba3(void);

static ParticleSystemTemplate *newParticleSystemTemplate(
	ParticleSystemManager *manager, const AsciiString &name)
{
	typedef ParticleSystemTemplate *(ParticleSystemManager::*Function)(
		const AsciiString &);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0002aba3;
	return (manager->*fn.member)(name);
}

static void initParticleSystemFields(BfmeCategoryHead1054 *categories)
{
	typedef void (*Function)(BfmeCategoryHead1054 *);
	union { void (*raw)(void); Function typed; } fn;
	fn.raw = j_0001f7c6;
	fn.typed(categories);
}

struct ParticleSystemFieldTable
{
	unsigned int words[8];
};

void INI::parseParticleSystemDefinition(INI *ini)
{
	AsciiString name;
	const char *token = ini->getNextToken();
	((StringBase<char> *)&name)->set(token, token ? (int)strlen(token) : 0);

	ParticleSystemTemplate *sysTemplate =
		TheParticleSystemManager->findTemplate(name);
	if (sysTemplate == 0)
	{
		sysTemplate = newParticleSystemTemplate(
			TheParticleSystemManager, name);
	}
	else
	{
		sysTemplate->~ParticleSystemTemplate();
		new (sysTemplate) ParticleSystemTemplate(name);
	}

	if (!*reinterpret_cast<volatile unsigned char *>(0x012F6923))
	{
		// The retail System field table starts at 0x0110F92C.
		initParticleSystemFields(
			reinterpret_cast<BfmeCategoryHead1054 *>(0x012F6850));
		*(ParticleSystemFieldTable *)0x012F68E0 =
			*(const ParticleSystemFieldTable *)0x0110F92C;
		// This intrinsic emits no instruction and fixes the retail copy order.
		_ReadWriteBarrier();
		*reinterpret_cast<volatile unsigned char *>(0x012F6923) = 1;
	}

	ini->initFromINI(sysTemplate,
		reinterpret_cast<const FieldParse *>(0x012F6850));
}
