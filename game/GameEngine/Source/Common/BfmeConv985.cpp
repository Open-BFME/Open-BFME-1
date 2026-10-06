// Open-BFME5 conversions.

struct BfmeObj985
{
	char m_bfmePad[0x254];
	char m_bfmeFlag;
	char m_bfmePad2[7];
	int m_bfmeMode;
};

// Retail global 0x012F4B58 is EA's shell singleton, defined under the canonical
// spelling (Shell *TheShell); this TU's view of the pointee keeps that class
// name so the reference resolves to the definition.
class Shell
{
public:
	char m_bfmePad[0x50];
	char m_bfmeFlag;
};

class BfmeAptScreenQuitMenu;
extern BfmeAptScreenQuitMenu *g_obj12F4B40;
extern Shell *TheShell;
// retail 0x012F19E8: the canonical spelling is
// ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A, defined once in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

// ILT 0x000290D2 -> 0x00465B80, matched ?apply@Rva00465B80@@QAEXXZ (sets the
// byte at +0x1AC to 1), called on the window manager at 0x012F19E8.
class Rva00465B80
{
public:
	void apply();
};

class BfmeA985
{
public:
	void bfmeGo985A(int unused);

	char m_bfmePad[0x258];
	char m_bfmeOwn;
};

void BfmeA985::bfmeGo985A(int unused)
{
	m_bfmeOwn = 1;

	BfmeObj985 *p = reinterpret_cast<BfmeObj985 * &>(g_obj12F4B40);

	if (!p)
		return;
	if (p->m_bfmeFlag)
		return;

	p->m_bfmeFlag = 1;
	reinterpret_cast<BfmeObj985 * &>(g_obj12F4B40)->m_bfmeMode = 2;
	TheShell->m_bfmeFlag = 1;
	((Rva00465B80 *)g_rva012F19E8WindowManager)->apply();
}

void __stdcall bfmeGo985B(int unused)
{
	BfmeObj985 *p = reinterpret_cast<BfmeObj985 * &>(g_obj12F4B40);

	if (!p)
		return;
	if (p->m_bfmeFlag)
		return;

	p->m_bfmeFlag = 1;
	reinterpret_cast<BfmeObj985 * &>(g_obj12F4B40)->m_bfmeMode = 0;
	TheShell->m_bfmeFlag = 1;
	((Rva00465B80 *)g_rva012F19E8WindowManager)->apply();
}

class UpgradeTemplate;

class Object
{
public:
	bool affectedByUpgrade(const UpgradeTemplate *upgradeTemplate) const;	// retail ILT 0x000077B6 -> 0x001C5A30
	bool hasUpgrade(const UpgradeTemplate *upgradeTemplate) const;			// retail ILT 0x0000BA37 -> 0x001C9F50
};

// The row spells its argument BfmeArg985; the two calls on it are Object's.
class BfmeArg985;

class BfmeC985
{
public:
	char bfmeGo985C(BfmeArg985 *a);

	char m_bfmePad[8];
	const UpgradeTemplate *m_bfmeVal;
};

char BfmeC985::bfmeGo985C(BfmeArg985 *a)
{
	const Object *object = (const Object *)a;

	if (object->affectedByUpgrade(m_bfmeVal) && !object->hasUpgrade(m_bfmeVal))
		return 1;

	return 0;
}
