// ?rva0024e990@Rva0024E990Owner@@QAEXPAVObject@@@Z
// partial score=0.88 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// retail RVA 0x0024E990. Called through the dispatch thunk at 0x0024EA60
// (Rva0024EA60Dispatch.cpp). this->m_9bc is an object count, this->m_9c0
// an AsciiString template name. If the count is positive, the name's buffer
// is non-null and its buffer+4 word is non-zero, and the explicit Object
// argument is non-null: look up both this->m_08's and the argument's
// controlling players (Object::getControllingPlayer, already landed), find
// the named ThingTemplate through TheThingFactory (already landed), and if
// the two players differ and the template resolved, add the count to the
// first player's ScoreKeeper object count and the second player's
// ScoreKeeper destroyed-by count (both already landed, ScoreKeeper at
// +0x348 of Player). The count field is reset to 0 and the name string
// released. The primary-vtable caller at 0x0024ED40 is SlaughterHordeContain and
// passes this through unchanged in ECX, with the Object* as its stack argument.
// The helper's exact method name remains address-derived.

class Player;
class ThingTemplate;

class Object
{
public:
	Player *getControllingPlayer(void) const;
};

class BfmeThingFactory;
extern BfmeThingFactory *TheThingFactory;

class BFMERetailAsciiString
{
public:
	char *m_buffer;
	void releaseBuffer();
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const BFMERetailAsciiString &name);
};

class ScoreKeeper
{
public:
	void addObjectCount(const ThingTemplate *tmpl, int count);
	void addObjectDestroyedCount(const ThingTemplate *tmpl, const Player *byPlayer, int count);
};


struct Rva0024E990Owner
{
	void rva0024e990(Object *other);

	unsigned char m_head08[8];
	Object *m_creatorObj;			// +0x08
	unsigned char m_gap[0x9bc - 8 - 4];
	int m_count;				// +0x9bc
	BFMERetailAsciiString m_name;		// +0x9c0
};

// retail RVA 0x0024E990
void Rva0024E990Owner::rva0024e990(Object *other)
{
	if ((unsigned int)m_count <= 0)
		return;

	BFMERetailAsciiString *namePtr = &m_name;
	char *buf = namePtr->m_buffer;
	if (!buf)
		return;

	if (*(short *)(buf + 4) == 0)
		return;

	if (!other)
		return;

	Player *player1 = m_creatorObj->getControllingPlayer();
	Player *player2 = other->getControllingPlayer();

	const ThingTemplate *tmpl = TheThingFactory->findTemplate(*namePtr);

	if (player1 == player2)
		return;
	if (!tmpl)
		return;

	((ScoreKeeper *)((char *)player1 + 0x348))->addObjectCount(tmpl, m_count);
	((ScoreKeeper *)((char *)player2 + 0x348))->addObjectDestroyedCount(tmpl, player1, m_count);

	m_count = 0;
	namePtr->releaseBuffer();
}
