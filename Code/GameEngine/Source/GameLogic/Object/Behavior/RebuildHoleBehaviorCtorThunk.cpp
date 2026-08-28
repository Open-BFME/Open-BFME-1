// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift RebuildHoleBehavior's ICF-identical retail constructor to C++.

#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _ReadWriteBarrier(void);

class Thing;
class ModuleData;

class QueueProductionExitUpdateBase
{
public:
	void construct(Thing *, const ModuleData *);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RebuildHoleBehavior.h
class RebuildHoleBehavior
{
public:
	RebuildHoleBehavior(Thing *, const ModuleData *);

private:
	unsigned char m_tail[0x40];
};

// ??0RebuildHoleBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
RebuildHoleBehavior::RebuildHoleBehavior(Thing *thing, const ModuleData *moduleData)
{
	unsigned char *bytes = reinterpret_cast<unsigned char *>(this);
	reinterpret_cast<QueueProductionExitUpdateBase *>(this)->construct(thing, moduleData);

	volatile unsigned int *words = reinterpret_cast<volatile unsigned int *>(bytes);
	words[0x1c / 4] = 0x010a257c;
	words[0x20 / 4] = 0x010a372c;

	_ReadWriteBarrier();
	unsigned int zero = 0;
	*reinterpret_cast<volatile unsigned char *>(bytes + 0x3c) = static_cast<unsigned char>(zero);
	*reinterpret_cast<volatile unsigned char *>(bytes + 0x3d) = static_cast<unsigned char>(zero);
	words[0x00 / 4] = 0x010a397c;
	words[0x0c / 4] = 0x010a38b8;
	words[0x10 / 4] = 0x010a3868;
	words[0x18 / 4] = 0x010a3858;
	words[0x1c / 4] = 0x010a3854;
	words[0x20 / 4] = 0x010a3844;
	words[0x24 / 4] = zero;
	words[0x28 / 4] = zero;
	words[0x2c / 4] = zero;
	words[0x30 / 4] = zero;
	words[0x34 / 4] = zero;
	words[0x38 / 4] = zero;
}
