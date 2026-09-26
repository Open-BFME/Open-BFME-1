// cl: /O2 /Ob1 /DNDEBUG /MD
//
// Retail 0x00430330 (166B) clears one of GameClient's ten queued icon stages.
// W3DView::draw reaches it through the incremental-link thunk at 0x0000DBC0.

void __cdecl bfmeDeallocate(void *block, unsigned int bytes);
extern void j_000042a5();

class Display
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot1A(); virtual void slot1B();
	virtual void slot1C(); virtual void slot1D(); virtual void slot1E(); virtual void slot1F();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot2A(); virtual void slot2B();
	virtual void slot2C(); virtual void slot2D(); virtual void slot2E(); virtual void slot2F();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35(); virtual void slot36(); virtual void slot37();
	virtual void slot38(); virtual void slot39(); virtual void slot3A(); virtual void slot3B();
	virtual void slot3C(); virtual void slot3D(); virtual void slot3E(); virtual void slot3F();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot4A(); virtual void slot4B();
	virtual void slot4C(); virtual void slot4D(); virtual void slot4E(); virtual void slot4F();
	virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55();
};

extern Display *TheDisplay;

class Drawable
{
public:
	void drawIconUI(int stage);
};

typedef void (Drawable::*DrawIconUI)(int);

union DrawIconUIValue
{
	void (*function)();
	DrawIconUI member;
};

struct IconNode
{
	IconNode *m_next;
	IconNode *m_previous;
	Drawable *m_drawable;
};

class GameClient
{
public:
	void drawIconUIGroup(int stage);

private:
	unsigned char m_unreconstructed[0xF4];
	IconNode *m_iconLists[10];
};

void GameClient::drawIconUIGroup(int stage)
{
	if (stage < 0 || stage >= 10)
		return;

	IconNode *head = m_iconLists[stage];
	if (head->m_next == head)
		return;

	TheDisplay->slot2C();

	IconNode *node = m_iconLists[stage]->m_next;
	while (node != m_iconLists[stage])
	{
		DrawIconUIValue drawIconUI = { j_000042a5 };
		(node->m_drawable->*drawIconUI.member)(stage);
		node = node->m_next;
	}

	TheDisplay->slot37();

	IconNode *walk = m_iconLists[stage]->m_next;
	while (walk != m_iconLists[stage])
	{
		IconNode *current = walk;
		walk = walk->m_next;
		bfmeDeallocate(current, sizeof(IconNode));
	}

	m_iconLists[stage]->m_next = m_iconLists[stage];
	m_iconLists[stage]->m_previous = m_iconLists[stage];
}
