// ?bfmeApplySlot1281@BfmeSlotDispatcher1281@@QAEXPAXH0@Z
// partial score=0.86 date=2026-08-30
class BfmeSlotDispatcher1281
{
public:
	void bfmeApplySlot1281(void *entry, int mode, void *tail);
	void bfmeDispatchSlots1281(int enabled, int mode, void *tail);

private:
	char m_padding000[0x820];
	int m_count;
	void *m_slots[64];
};

extern void *(*WideAllocPtr)(unsigned int bytes);
void Gen00897300(void *block);

struct BfmeRouteMask1281
{
	int mask;
	int index;
};

extern BfmeRouteMask1281 g_bfmeRouteMasks1281[6];
extern void *g_bfmeRouteKeys1281[1];

struct BfmeRouteDetail1281
{
	int m_unused00;
	int m_value04;
};

struct BfmeTailFields1281
{
	unsigned int m_unused02 : 2;
	unsigned int m_type08 : 8;
	unsigned int m_flags07 : 7;
};

class BfmeResolvedSlot1281
{
public:
	virtual void reserved00() = 0;
	virtual void reserved01() = 0;
	virtual void reserved02() = 0;
	virtual void reserved03() = 0;
	virtual void reserved04() = 0;
	virtual void reserved05() = 0;
	virtual void reserved06() = 0;
	virtual void reserved07() = 0;
	virtual void reserved08() = 0;
	virtual void reserved09() = 0;
	virtual void reserved10() = 0;
	virtual void reserved11() = 0;
	virtual void reserved12() = 0;
	virtual void reserved13() = 0;
	virtual void reserved14() = 0;
	virtual void reserved15() = 0;
	virtual void reserved16() = 0;
	virtual void reserved17() = 0;
	virtual void reserved18() = 0;
	virtual int bfmeRouteKind1281() = 0;

	unsigned int m_flags;
	char m_padding08[0x20 - 0x08];
	int m_value20;
	int m_value24;
	void *m_owner28;
	char m_padding2c[4];
	BfmeRouteDetail1281 *m_detail30;
};

class BfmeSlotSource1281
{
public:
	BfmeResolvedSlot1281 *bfmeResolveRoute1281(void *key, int zero);
};

class BfmeRoutedObject1281
{
public:
	__forceinline void *operator new(unsigned int bytes)
	{
		char *raw = (char *)WideAllocPtr(bytes + 8);
		char *block = raw + 8;
		Gen00897300(block);
		return block;
	}

	unsigned int m_vtable;
	unsigned int m_flags;
};

class BfmeRoutedA1281 : public BfmeRoutedObject1281
{
public:
	BfmeRoutedA1281(BfmeRouteDetail1281 *detail, int value20, int value24, void *owner);
	char m_padding08[0x34 - 0x08];
};

class BfmeRoutedB1281 : public BfmeRoutedObject1281
{
public:
	BfmeRoutedB1281(BfmeRouteDetail1281 *detail, int value20, int value24, void *owner);
	char m_padding08[0x34 - 0x08];
};

class BfmeRouteManager1281
{
public:
	void bfmeSubmitRoute1281(void *source, BfmeRoutedObject1281 *object,
		int routeValue, void *tail);
};

extern BfmeRouteManager1281 *g_bfmeHolderBU;

void BfmeSlotDispatcher1281::bfmeDispatchSlots1281(int enabled, int mode, void *tail)
{
	int visited = 0;
	for (int index = 0; index < 64; ++index) {
		if (visited == m_count)
			break;
		void *entry = m_slots[index];
		if (entry != 0) {
			switch (mode) {
			case 0:
				if (enabled != 0)
					bfmeApplySlot1281(entry, 0x40, tail);
				break;
			case 1:
				if (enabled != 0)
					bfmeApplySlot1281(entry, 0x80, tail);
				break;
			}
			++visited;
		}
	}
}

void BfmeSlotDispatcher1281::bfmeApplySlot1281(void *entry, int mode, void *tail)
{
	int *routeIndex = &g_bfmeRouteMasks1281[0].index;
	for (; routeIndex < &g_bfmeRouteMasks1281[6].index; routeIndex += 2) {
		if ((routeIndex[-1] & mode) == 0)
			continue;

		BfmeResolvedSlot1281 *node = ((BfmeSlotSource1281 *)entry)->bfmeResolveRoute1281(
			&g_bfmeRouteKeys1281[*routeIndex], 0);
		if (node == 0 || (node->m_flags & 0x8000) == 0 ||
			(node->m_flags & 0x3f) != 10 ||
			((unsigned char)(~(node->m_flags >> 15)) & 1) != 0)
			continue;

		int routeValue = 0;
		BfmeTailFields1281 *tailFields = (BfmeTailFields1281 *)&tail;
		if (tailFields->m_type08 == 1 && (tailFields->m_flags07 & 7) != 0)
			routeValue = node->m_detail30->m_value04;

		if (node->m_owner28 == entry) {
			g_bfmeHolderBU->bfmeSubmitRoute1281(
				entry, (BfmeRoutedObject1281 *)node, 0, tail);
			continue;
		}

		int routeKind = node->bfmeRouteKind1281();
		BfmeRouteDetail1281 *detail = node->m_detail30;
		BfmeRoutedObject1281 *object;
		if (routeKind == 1)
			object = new BfmeRoutedA1281(detail, node->m_value20, node->m_value24, entry);
		else
			object = new BfmeRoutedB1281(detail, node->m_value20, node->m_value24, entry);

		object->m_flags = (object->m_flags & 0xffffc07f) | 0x40;
		g_bfmeHolderBU->bfmeSubmitRoute1281(entry, object, routeValue, tail);
	}
}
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
