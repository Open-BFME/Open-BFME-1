// cl: /DNDEBUG /MD /EHsc
// Twin of ?getRequiredScience@SpecialPowerModule@@UBE?AW4ScienceType@@XZ
// @0x00268A30 with module data at this-0x20 instead of this-0xc (same wider
// MI layout used by Rva0026AC60GetPowerName.cpp, its neighbour at 0x0026AC60).

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	Overridable *friend_getFinalOverride(void)
	{
		if (m_next)
			return m_next->m_next ? m_next->m_next->friend_getFinalOverride() : m_next;
		return this;
	}

private:
	void *m_vtable;
	Overridable *m_next;
};

typedef int ScienceType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate : public Overridable
{
public:
	ScienceType getRequiredScience(void) const
	{
		SpecialPowerTemplate *self = const_cast<SpecialPowerTemplate *>(this);
		return ((const SpecialPowerTemplate *)self->friend_getFinalOverride())->m_requiredScience;
	}

private:
	unsigned char m_unreconstructed_08[0x14];
	ScienceType m_requiredScience;		// +0x1c
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
struct Gen0026AC90ModuleData
{
	unsigned char m_unreconstructed_00[8];		// +0x00
	const SpecialPowerTemplate *m_specialPowerTemplate;	// +0x08
};

// Wider iface: module data pointer at this-0x20 (compact SpecialPowerModule
// keeps it at this-0xc; this sibling has more preceding MI bases/interfaces),
// matching Gen0026AC60Owner in Rva0026AC60GetPowerName.cpp.
class Gen0026AC90Owner
{
public:
	ScienceType getRequiredScience(void) const;

private:
	const Gen0026AC90ModuleData *getModuleData(void) const
	{
		return *(const Gen0026AC90ModuleData *const *)((const char *)this - 0x20);
	}
};

// ?getRequiredScience@Gen0026AC90Owner@@QBE?AW4ScienceType@@XZ
ScienceType Gen0026AC90Owner::getRequiredScience(void) const
{
	return getModuleData()->m_specialPowerTemplate->getRequiredScience();
}
