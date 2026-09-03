// ?setMode@LookAtTranslator@@QAEHH@Z
// partial score=0.93 date=2026-09-02
// cl: /O2 /Ob0
// ?setMode@LookAtTranslator@@QAEHH@Z
// 60/60 instructions; residue is eax/edx swap on TheMouse vslot 14:
// retail mov edx,[esi+0x1ec]; mov eax,[ecx]; push edx; call [eax+0x38]
// ours   mov eax,[esi+0x1ec]; mov edx,[ecx]; push eax; call [edx+0x38]

class BfmeC977
{
public:
	char bfmeGo977C();
};

extern BfmeC977 *g_theWindowManager;

class Mouse
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void setVisibility(int visible);
};

extern Mouse *TheMouse;

class LookAtTranslator
{
public:
	int setMode(int value);

private:
	char m_pad[0x1EC];
	int m_mode;
};

int LookAtTranslator::setMode(int value)
{
	int old = m_mode;
	m_mode = value;
	if (g_theWindowManager->bfmeGo977C())
		TheMouse->setVisibility(m_mode);
	return old;
}
