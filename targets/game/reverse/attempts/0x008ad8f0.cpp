// ?bfmeApply1236@BfmeB1236@@QAEXPAX@Z
// partial score=0.2812 date=2026-09-23
// ?bfmeApply1236@BfmeB1236@@QAEXPAX@Z
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva8CD130Value;

class Rva008AD750StringBinding
{
public:
	void refresh(Rva8CD130Value *scope);
	char m_pad00[0x0c];
	void *m_source0c;
	char m_pad10[8];
	void *m_string18;
	void *m_key1c;
	void *m_value20;
	int m_fallback24;
	int m_value28;
	int m_value2c;
	int m_value30;
	int m_value34;
	int m_mode38;
	int m_value3c;
	int m_value40;
	int m_value44;
	int m_value48;
	int m_value4c;
	float m_value50;
	float m_value54;
	float m_value58;
	float m_value5c;
	int m_value60;
	int m_index64;
	void *m_owner68;
	unsigned m_flags6c;
	int m_value70;
	unsigned m_flags74;
	int m_value78;
	int m_value7c;
};

struct BfmeApplyRecord1236
{
	void *m_value00;
	float m_value04;
	float m_value08;
	float m_value0c;
	float m_value10;
	int m_value14;
	int m_value18;
	int m_value1c;
	int m_value20;
	int m_value24;
	int m_value28;
	int m_value2c;
	int m_value30;
	int m_value34;
	int m_value38;
	int m_value3c;
	int m_value40;
	int m_value44;
	int m_value48;
	int m_value4c;
	int m_value50;
	int m_value54;
	int m_value58;
	int m_value5c;
	int m_value60;
	int m_value64;
	int m_value68;
	int m_value6c;
};

struct BfmeApplyMap1236
{
	char m_pad00[4];
	void *m_base04;
	char m_pad08[8];
	void **m_entries;
};

struct BfmeApplyNode1236
{
	char m_pad00[0x0c];
	BfmeApplyMap1236 *m_map;
};

struct BfmeApplyArgument1236
{
	char m_pad00[0x50];
	BfmeApplyNode1236 *m_node;
};

class Rva00899770
{
public:
	virtual void addRef(void);
	virtual void release(void);
	unsigned m_flags;
	union
	{
		bool m_boolean;
		int m_integer;
		float m_float;
		void *m_string;
	};
	char m_gap0c[0x14];
	float m_bfme20;
};

class BfmeB1236 : public Rva00899770
{
public:
	void bfmeApply1236(void *argument);
	char m_bfmePad24[0x24];
	float *m_bfme48;
	void *m_bfme4c;
	Rva008AD750StringBinding *m_bfme50;
};

class BfmeSlotState1289
{
public:
	void bfmeSetAxis1289(int axis, float value, int enabled);
};

typedef void (__cdecl *BfmeUpdate1236)(void *, int);
typedef void *(__cdecl *BfmeCreate1236)(BfmeApplyRecord1236 *);

void BfmeB1236::bfmeApply1236(void *argument)
{
	BfmeB1236 *self = this;
	Rva008AD750StringBinding *binding = self->m_bfme50;
	void *bindingSource = binding->m_source0c;
	BfmeApplyArgument1236 *source = (BfmeApplyArgument1236 *)argument;
	binding->refresh((Rva8CD130Value *)argument);
	unsigned flags = binding->m_flags6c;
	if (flags & 1)
		goto finish;

	void *old = binding->m_value20;
	if (old != 0 && old != (void *)0x012D5598)
		(*(BfmeUpdate1236 *)0x01337874)(old, flags);

	BfmeApplyRecord1236 record;
	BfmeApplyNode1236 *node = source->m_node;
	BfmeApplyMap1236 *map = (BfmeApplyMap1236 *)((char *)node->m_map);
	void *entry = (void *)((char *)map->m_base04 + 8);
	void *string = binding->m_string18;
	if (string == (void *)0x012D5298) {
		binding->m_value20 = (void *)0x012D5598;
		if (binding->m_mode38 != 3) {
			binding->m_value58 = binding->m_value50 + *(const float *)0x01075340;
		binding->m_value5c = binding->m_value54 + *(const float *)0x01075340;
		}
		binding->m_value44 = 0;
		binding->m_value48 = 0;
		binding->m_flags6c = 1;
		goto finish;
	} else {
		if (*(int *)((char *)bindingSource + 0x18) >= 0)
			entry = *(void **)((char *)map->m_entries + binding->m_index64 * 4);
		if (binding->m_owner68 != 0)
			record.m_value00 = *(void **)((char *)binding->m_owner68 + 8);
		else
			record.m_value00 = entry;
	}

	record.m_value04 = binding->m_value50;
	record.m_value08 = binding->m_value54;
	record.m_value0c = binding->m_value58;
	record.m_value10 = binding->m_value5c;
	record.m_value14 = binding->m_value60;
	record.m_value18 = binding->m_mode38;
	unsigned typeFlags = binding->m_flags74;
	record.m_value38 = (typeFlags >> 2) & 1;
	record.m_value3c = (typeFlags >> 1) & 1;
	record.m_value28 = binding->m_mode38;
	record.m_value34 = binding->m_value34;
	record.m_value30 = binding->m_value30;
	record.m_value24 = binding->m_fallback24;
	record.m_value2c = binding->m_value2c;
	record.m_value40 = (int)((char *)string + 8);
	record.m_value48 = binding->m_value60;
	record.m_value4c = binding->m_value2c;
	record.m_value54 = (int)((char *)string + 8);
	record.m_value58 = binding->m_flags6c;
	record.m_value5c = (int)binding->m_value20;

		if (binding->m_owner68 != 0) {
			record.m_value60 = *(int *)((char *)binding->m_owner68 + 0x10);
			record.m_value64 = *(int *)((char *)binding->m_owner68 + 0x14);
			record.m_value68 = *(int *)((char *)binding->m_owner68 + 0x18);
			record.m_value6c = *(int *)((char *)binding->m_owner68 + 0x1c);
		} else {
			record.m_value60 = -1;
			record.m_value64 = -1;
			record.m_value68 = -1;
			record.m_value6c = -1;
		}
		record.m_value50 = binding->m_value44;
		record.m_value44 = binding->m_value48;
		record.m_value20 = binding->m_value4c;
	binding->m_value20 = (*(BfmeCreate1236 *)0x01337870)(&record);

	if (binding->m_mode38 == 2) {
		float delta = binding->m_value58 - binding->m_value50;
		float oldDelta = record.m_value0c - record.m_value04;
		if (delta != oldDelta) {
			((BfmeSlotState1289 *)self)->bfmeSetAxis1289(1, self->m_bfme20 - delta * *(const float *)0x0107533c, 0);
		}
	} else if (binding->m_mode38 == 1) {
		float delta = binding->m_value58 - binding->m_value50;
		float oldDelta = record.m_value0c - record.m_value04;
		if (delta != oldDelta) {
			((BfmeSlotState1289 *)self)->bfmeSetAxis1289(0, self->m_bfme20 + delta - oldDelta, 0);
		}
	}

	binding->m_value50 = record.m_value04;
	binding->m_value58 = record.m_value0c;
	binding->m_value54 = record.m_value08;
	binding->m_value5c = record.m_value10;
	binding->m_value28 = record.m_value1c;
	if (binding->m_value2c > record.m_value1c)
		binding->m_value2c = record.m_value1c;
	binding->m_value44 = record.m_value50;
	binding->m_value48 = record.m_value54;
	binding->m_value4c = record.m_value20;
	binding->m_flags6c = 1;

finish:
	return;
}
