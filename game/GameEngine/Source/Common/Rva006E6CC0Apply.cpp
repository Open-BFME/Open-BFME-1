// cl: /O2 /Ob0

// Retail's global at 0x012F12CC is EA's DisplayStringManager; defined once in
// GameClient/DisplayStringManager.cpp.  The local view below only exists to spell
// the slots this TU calls, so the use casts.
class DisplayStringManager;

class Rva006E6CC0Target
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual int slot24();
};

extern DisplayStringManager *TheDisplayStringManager;

class Rva006E6CC0
{
	char m_lead[0x2C];
	int m_at2C;

public:
	void apply();
};

void Rva006E6CC0::apply()
{
	m_at2C = ((Rva006E6CC0Target *)TheDisplayStringManager)->slot24();
}
