// cl: /DNDEBUG /MD /EHsc

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class AsciiString;
class Player;
class AttributeModifierPoolUpdate;

class Object
{
public:
	Player *getControllingPlayer() const;
	bool applyAttributeModifier(const AsciiString &name, int duration);

	unsigned char m_pad[0x88];
	Object *m_nextObject;

private:
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
	friend class BfmeObjectReferenceStore;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *getFirstObject();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h

// Retail inlines this wrapper into StringBase<char> directly; declare just the
// StringBase<char> members it reaches (see build/whatif/wrapfix.py).
template <class T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;
public:
	void set(const StringBase<T> &other);
private:
	void releaseBuffer();
};
class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other) { ((StringBase<char> *)this)->set(*(const StringBase<char> *)&other); return *this; }
	void set(const char *text, int length);
private:
	friend class BfmeObjectReferenceStore;
	char *m_data;
};

extern GameLogic *TheGameLogic;
extern const char g_Rva0107301CEmptyString[];

class PlayerTemplate
{
public:
	bool getFlag118() const { return m_flag118; }

	unsigned char m_pad[0x118];
	bool m_flag118;				// +0x118, unnamed
};

class Player
{
public:
	const PlayerTemplate *getPlayerTemplate() const { return m_playerTemplate; }

	unsigned char m_pad[4];
	PlayerTemplate *m_playerTemplate;
};

class PlayerList
{
public:
	Player *getPlayerFromMask(unsigned short mask);
};

extern PlayerList *ThePlayerList;

class Rva2225E0Filter
{
public:
	bool accepts(Object *object, Player *player);

	int m_value;
};

class BfmeMsgXI;

class BfmeOwnerXI
{
public:
	void bfmeSendXI(BfmeMsgXI *msg);
};

class Rva003679B0
{
public:
	void set(int index, unsigned value);
};

class BfmeObjectReferenceStore
{
public:
	void configure(int mode, const int &value, const Object *player,
		const AsciiString &name, int trailingValue);
	void updateObjectReference(Object *object, bool adding);
	void clearObjectEntries();

private:
	unsigned char m_pad[0x14];
	int m_mode;
	Rva2225E0Filter m_filter;
	AsciiString m_name;
	int m_value;
	unsigned short m_mask;
};

// ?updateObjectReference@BfmeObjectReferenceStore@@QAEXPAVObject@@_N@Z
// Retail 0x0039B160, 264 bytes (ret 8 at +0xF1/+0x105, INT3 from +0x108);
// identity from the matched callers clearObjectEntries and configure above.
// Callees are the ledger's bodies behind the retail ILT stubs: 0x20824
// getControllingPlayer, 0x1DDE5 getPlayerFromMask, 0x1DA34 the +0x18 filter's
// accepts, 0x1EF9C bfmeSendXI, 0x37A56 applyAttributeModifier, 0x202ED
// findAttributeModifierPoolUpdate and 0x1C0DA Rva003679B0::set.  The inline
// getPlayerTemplate/getFlag118 accessors are what put the Object in ESI
// and the store in EDI as retail does; direct field reads swap the two.
void BfmeObjectReferenceStore::updateObjectReference(Object *object, bool adding)
{
	if (object == 0)
		return;
	if (m_mode == 0)
		return;
	if (m_mode == 2 && object->getControllingPlayer())
	{
		const PlayerTemplate *pt = object->getControllingPlayer()->getPlayerTemplate();
		if (!pt || !pt->getFlag118())
			return;
	}
	if (m_mode == 3 && object->getControllingPlayer())
	{
		const PlayerTemplate *pt = object->getControllingPlayer()->getPlayerTemplate();
		if (pt && pt->getFlag118())
			return;
	}
	Player *player = m_mask == 0 ? 0 : ThePlayerList->getPlayerFromMask(m_mask);
	if (!m_filter.accepts(object, player))
		return;
	if (m_name.m_data != 0 && *(unsigned short *)(m_name.m_data + 4) != 0)
	{
		if (adding)
			((BfmeOwnerXI *)object)->bfmeSendXI((BfmeMsgXI *)&m_name);
		else
			object->applyAttributeModifier(m_name, -1);
	}
	if (m_value != 0)
	{
		Rva003679B0 *pool = (Rva003679B0 *)object->findAttributeModifierPoolUpdate();
		if (pool == 0)
			return;
		if (adding)
			pool->set(m_value, 0);
		else
			pool->set(m_value, 0x3b9ac9ff);
	}
}

void BfmeObjectReferenceStore::clearObjectEntries()
{
	Object *object = TheGameLogic->getFirstObject();
	while (object != 0) {
		updateObjectReference(object, true);
		object = object->m_nextObject;
	}
	m_mode = 0;
	m_name.set(g_Rva0107301CEmptyString, 0);
	m_value = 0;
	m_mask = 0;
}

void BfmeObjectReferenceStore::configure(int mode, const int &value,
		const Object *player, const AsciiString &name, int trailingValue)
{
	clearObjectEntries();
	m_mode = mode;
	m_filter.m_value = value;
	m_name = name;
	m_value = trailingValue;
	m_mask = (unsigned short)(1 << *(const int *)((const unsigned char *)player + 0x24));

	Object *object = TheGameLogic->getFirstObject();
	while (object != 0) {
		updateObjectReference(object, false);
		object = object->m_nextObject;
	}
}
