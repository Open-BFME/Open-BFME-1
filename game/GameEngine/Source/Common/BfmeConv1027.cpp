// Open-BFME5 conversions.

// Matched callee rows, reached through their ILT thunks (callees.py):
// aiEvacuate 0x000D8AC0, aiIdle 0x000D87E0, leaveGroup 0x001BFBF0,
// bfmeGo916D 0x001C9B80, GameClientRandomVariable::getValue 0x00096F60.
enum CommandSourceType { CMD_FROM_SCRIPT_1027 = 1 };

class AICommandInterface
{
public:
	void aiEvacuate(bool exposeStealthUnits, CommandSourceType cmdSource);
	void aiIdle(CommandSourceType cmdSource);
};

class Object
{
public:
	void leaveGroup(void);
};

class BfmeThing916D
{
public:
	void bfmeGo916D(void *p);
};

class GameClientRandomVariable
{
public:
	float getValue(void) const;
};

class BfmeQ1027
{
public:
};

class BfmeY1027
{
public:
	char m_bfmePad[0x20];
	BfmeQ1027 m_bfmeQ;
};

class BfmeX1027
{
public:

	char m_bfmePad[0x204];
	BfmeY1027 *m_bfmeOwner;
};

class BfmeU1027
{
public:
	virtual void bfmeVU01027();
	virtual void bfmeVU11027();
	virtual void bfmeVU21027();
	virtual void bfmeVU31027();
	virtual void bfmeVU41027();
	virtual void bfmeVU51027();
	virtual void bfmeVU61027();
	virtual void bfmeVU71027();
	virtual void bfmeVU81027();
	virtual void bfmeVU91027();
	virtual void bfmeVU101027();
	virtual void bfmeVU111027();
	virtual void bfmeVU121027();
	virtual void bfmeVU131027();
	virtual void bfmeVU141027();
	virtual void bfmeVU151027();
	virtual void bfmeVU161027();
	virtual void bfmeVU171027();
	virtual void bfmeVU181027();
	virtual void bfmeVU191027();
	virtual void bfmeVU201027();
	virtual void bfmeVU211027();
	virtual void bfmeVU221027();
	virtual void bfmeVU231027();
	virtual void bfmeVU241027();
	virtual void bfmeVU251027();
	virtual BfmeX1027 *bfmeFind1027(int a);
};

// Retail's ScriptEngine global at 0x012F076C, spelled canonically so this TU
// links against game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine.cpp's
// definition; the reads go through this TU's own view of the object.
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

static inline BfmeU1027 *bfmeViewU1027(void)
{
	return (BfmeU1027 *)TheScriptEngine;
}

void __stdcall bfmeGo1027A(int a)
{
	BfmeX1027 *x = bfmeViewU1027()->bfmeFind1027(a);

	if (x == 0)
		return;

	BfmeY1027 *y = x->m_bfmeOwner;

	if (y == 0)
		return;

	((Object *)x)->leaveGroup();
	((AICommandInterface *)&y->m_bfmeQ)->aiEvacuate(false, (CommandSourceType)1);
}

void __stdcall bfmeGo1027B(int a)
{
	BfmeX1027 *x = bfmeViewU1027()->bfmeFind1027(a);

	if (x == 0)
		return;

	BfmeY1027 *y = x->m_bfmeOwner;

	if (y == 0)
		return;

	((BfmeThing916D *)x)->bfmeGo916D((void *)1);
	((AICommandInterface *)&y->m_bfmeQ)->aiIdle((CommandSourceType)1);
}

class BfmeVal1027
{
public:
};

struct BfmeZ1027
{
	char m_bfmePad[4];
	BfmeVal1027 m_bfmeSub;
	char m_bfmePad2[0x17];
	char m_bfmeFlag;
};

struct BfmeS1027
{
	char m_bfmePad[0x3c];
	int m_bfmeBase;
};

class GameLogic;
extern GameLogic *TheGameLogic;

// TU-local field view of the retail global at 0x012F0898; the global itself is
// declared with its real type (GameLogic *) so the linked build has one symbol.
static inline BfmeS1027 *g_bfmeS1027()
{
	return (BfmeS1027 *)TheGameLogic;
}

void __stdcall bfmeGo1027D(BfmeZ1027 *p, int *out)
{
	if (p->m_bfmeFlag != 0) {
		*out = -1;
		return;
	}

	int base = g_bfmeS1027()->m_bfmeBase;

	*out = base + (int)((GameClientRandomVariable *)&p->m_bfmeSub)->getValue();
}
