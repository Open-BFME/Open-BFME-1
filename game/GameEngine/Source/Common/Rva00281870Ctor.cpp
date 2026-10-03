// cl: /O2 /Ob0

// Retail's constructor calls the ILT entry 0x0003747A, the empty, ICF-folded
// member-constructor body several pins share. The tree holds that entry as the
// five-byte thunk ?j_0003747a@@YAXXZ (game/gen_small/thunks_026.cpp), the only
// defined spelling of it, so the call is spelled that way: the folded body
// writes nothing, which is why the base needs no constructor of its own here.
extern void __cdecl j_0003747a();

class RespawnPolicyMember
{
private:
	int m_00;
};

class Rva00281870 : public RespawnPolicyMember
{
	int m_04;
	float m_08;

public:
	Rva00281870();
};

Rva00281870::Rva00281870()
{
	j_0003747a();
	m_04 = 0;
	m_08 = 1.0f;
}
