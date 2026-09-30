// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/bfmeobjectlayout /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame
// stlport
#include "Lib/BaseType.h"
#include "Common/GameMemory.h"
#include "Common/Overridable.h"
#include "Common/KindOf.h"
#define OBJECT_TU_MEMBERS unsigned char getCrusherLevel() const;
#define THING_TU_MEMBERS bool isKindOf(KindOfType) const;
#include "GameEngine/Source/GameLogic/Object/object.h"
#undef THING_TU_MEMBERS
#undef OBJECT_TU_MEMBERS


// Retail 0x001AF550, 146 bytes: RET 4 at 0x001AF5DF ends at
// 0x001AF5E2, followed by INT3. The owner and method names retain addresses.
// The receiver is passed unchanged to the independently matched six-slot
// TerrainRecordScan001AEFF0::apply. Its action argument is a one-pointer
// local; separate that local from the input parameter to preserve retail's
// initial saved Object pointer and later dead-parameter-slot reuse.
// Template tests at +0xC8 bit 2 and +0xD8 bit 22 remain opaque. The signed
// comparison after getCrusherLevel follows retail's CMP AL,1 / JG.

struct Point001AEFF0;
class GeometryInfo;
class BfmeT1035;

class TerrainRecordScan001AEFF0
{
public:
	void apply(const Point001AEFF0 *, int, GeometryInfo *, BfmeT1035 *, bool, int);
	void rva001AF550(Object *object);
};

class Rva001AF550TerrainVisual
{
public:
#define RVA001AF550_SLOT(n) virtual void slot##n();
	RVA001AF550_SLOT(00) RVA001AF550_SLOT(01) RVA001AF550_SLOT(02) RVA001AF550_SLOT(03)
	RVA001AF550_SLOT(04) RVA001AF550_SLOT(05) RVA001AF550_SLOT(06) RVA001AF550_SLOT(07)
	RVA001AF550_SLOT(08) RVA001AF550_SLOT(09) RVA001AF550_SLOT(10) RVA001AF550_SLOT(11)
	RVA001AF550_SLOT(12) RVA001AF550_SLOT(13) RVA001AF550_SLOT(14) RVA001AF550_SLOT(15)
	RVA001AF550_SLOT(16) RVA001AF550_SLOT(17) RVA001AF550_SLOT(18) RVA001AF550_SLOT(19)
	RVA001AF550_SLOT(20) RVA001AF550_SLOT(21) RVA001AF550_SLOT(22) RVA001AF550_SLOT(23)
	RVA001AF550_SLOT(24) RVA001AF550_SLOT(25) RVA001AF550_SLOT(26) RVA001AF550_SLOT(27)
	RVA001AF550_SLOT(28) RVA001AF550_SLOT(29) RVA001AF550_SLOT(30) RVA001AF550_SLOT(31)
	RVA001AF550_SLOT(32) RVA001AF550_SLOT(33) RVA001AF550_SLOT(34) RVA001AF550_SLOT(35)
	RVA001AF550_SLOT(36) RVA001AF550_SLOT(37) RVA001AF550_SLOT(38)
#undef RVA001AF550_SLOT
	virtual void slot39(Object *object);
};

extern "C" Rva001AF550TerrainVisual *g_012F7014;

void TerrainRecordScan001AEFF0::rva001AF550(Object *parameter)
{
	Object *object = parameter;
	g_012F7014->slot39(object);

	const Overridable *data =
		reinterpret_cast<const Overridable *>(object->m_template);
	const Overridable *finalData = data;
	if (data)
		finalData = data->getFinalOverride();

	if ((*(reinterpret_cast<const unsigned char *>(finalData) + 0xC8) & 4) == 0)
	{
		if ((signed char)object->getCrusherLevel() > 1 ||
			object->isKindOf(static_cast<KindOfType>(11)))
		{
			data = reinterpret_cast<const Overridable *>(object->m_template);
			finalData = data;
			if (data)
				finalData = data->getFinalOverride();

			if ((*reinterpret_cast<const unsigned int *>(
				reinterpret_cast<const unsigned char *>(finalData) + 0xD8)
				& 0x400000) == 0)
			{
				Object *action = object;
				apply(reinterpret_cast<const Point001AEFF0 *>(object->m_cachedPos),
					*reinterpret_cast<int *>(&object->m_cachedAngle),
					reinterpret_cast<GeometryInfo *>(object->m_geometryInfo),
					reinterpret_cast<BfmeT1035 *>(&action), true, 0);
			}
		}
	}
}
