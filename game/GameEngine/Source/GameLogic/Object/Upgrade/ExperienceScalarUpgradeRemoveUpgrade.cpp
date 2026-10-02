// cl: /O2 /Ob0
// ExperienceScalarUpgrade::removeUpgrade at retail 0x002D5120: slot 7 of the UpgradeMux table
// 0x010CC890, reached only through ILT 0x0000AC04. ExperienceScalarUpgrade's registered
// constructor 0x002D4FD0 stores that table. Evidence:
// targets/game/reverse/identity_evidence/upgrademux-slot7-owner-names.md
// Slot 7 is EA's removeUpgrade (BFME2/RotWK WorldBuilder labels, matching slot):
// targets/game/reverse/identity_evidence/upgrademux-slot7-removeupgrade.md

struct Rva002D5120Obj
{
	char m_lead[0x1C];
	float m_1c;
};

struct Rva002D5120Holder
{
	char m_lead[0x210];
	Rva002D5120Obj *m_obj;
};

struct Rva002D5120Other
{
	char m_lead[0x70];
	float m_70;
};

class ExperienceScalarUpgrade
{
protected:
	virtual void removeUpgrade();
};

void ExperienceScalarUpgrade::removeUpgrade()
{
	Rva002D5120Obj *obj = (*(Rva002D5120Holder **)((char *)this - 8))->m_obj;
	if (obj)
	{
		Rva002D5120Other *o = *(Rva002D5120Other **)((char *)this - 0x0C);
		obj->m_1c -= o->m_70;
	}
}
