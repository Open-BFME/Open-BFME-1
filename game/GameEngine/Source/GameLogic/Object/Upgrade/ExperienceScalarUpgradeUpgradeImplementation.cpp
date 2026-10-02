// cl: /O2 /Ob0
// ExperienceScalarUpgrade::upgradeImplementation at retail 0x002D5100: slot 9 of the UpgradeMux table
// 0x010CC890, reached only through ILT 0x0000C59F. ExperienceScalarUpgrade's registered
// constructor 0x002D4FD0 stores that table. Evidence:
// targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md

struct Rva002D5100Obj
{
	char m_lead[0x1C];
	float m_1c;
};

struct Rva002D5100Holder
{
	char m_lead[0x210];
	Rva002D5100Obj *m_obj;
};

struct Rva002D5100Other
{
	char m_lead[0x70];
	float m_70;
};

class ExperienceScalarUpgrade
{
protected:
	virtual void upgradeImplementation();
};

void ExperienceScalarUpgrade::upgradeImplementation()
{
	Rva002D5100Obj *obj = (*(Rva002D5100Holder **)((char *)this - 8))->m_obj;
	if (obj)
	{
		Rva002D5100Other *o = *(Rva002D5100Other **)((char *)this - 0x0C);
		obj->m_1c += o->m_70;
	}
}
