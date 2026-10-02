// ?method@Rva0049C2E0@@QAEXH_N@Z
// cl: /DNDEBUG /MD /EHsc

// Retail RVA 0x0049C2E0 ends with ret 8 at +0x7C, so this body spans 127 bytes.
// No caller or vtable proves the owner, so this file keeps the address in
// Rva0049C2E0::method.
// Retail accesses fields at +0x10, +0x18, +0x70, +0x74, +0x78, and +0x148.
// ILT 0x00006938 pins the call to Rva0049BA80::call(Object*, bool).
// ILT 0x0001F253 pins GameLogic::findObjectByID(int).

typedef int Int;
typedef unsigned int UnsignedInt;

class Object;

struct Rva00367E30Logic
{
	char m_prefix[0x0c];
};

class Rva0049BA80
{
public:
	void call(Object *object, bool flag) const;
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

extern GameLogic *TheGameLogic;   // 0x012F0898

class Rva0049C2E0
{
public:
	void method(Int p1, bool p2);

private:
	char m_prefix10[0x10];
	Int m_10;
	char m_prefix18[0x18 - 0x14];
	Int m_18;
	char m_prefix70[0x70 - 0x1c];
	Int m_70;
	Int m_74;
	Int m_78;
	char m_prefix148[0x148 - 0x7c];
	Int m_148;
};

void Rva0049C2E0::method(Int p1, bool p2)
{
	if (m_18 & 0x800000)
	{
		switch (m_10)
		{
		case 0x22:
		{
			if (p1 == m_70)
			{
				p1 = m_74;
				if (p1 == 3)
					p1 = m_70;
			}
			else if (p1 == m_74)
			{
				p1 = m_78;
				if (p1 == 3)
					p1 = m_70;
			}
			else if (p1 == m_78)
			{
				p1 = m_70;
			}
			m_148 = p1;
			return;
		}
		case 0x2e:
			((const Rva0049BA80 *)this)->call(
				((GameLogic *)TheGameLogic)->findObjectByID(p1), p2);
			return;
		default:
			return;
		}
	}
	else if (!(m_18 & 0x3000000))
	{
		return;
	}

	((const Rva0049BA80 *)this)->call(
		((GameLogic *)TheGameLogic)->findObjectByID(p1), p2);
}
