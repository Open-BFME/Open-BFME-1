// ?bfmeEmit1236@BfmeB1236@@QAEXPAXH0@Z
// partial score=0.88 date=2026-09-28
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?bfmeEmit1236@BfmeB1236@@QAEXPAXH0@Z  (retail 0x008ADBD0, 1452 bytes, ret 12)
// Rewrite (opus-5.5, 2026-09-28): 1452/1452 bytes, 173 non-reloc diffs.
// Identity: matched callers bfmeGo1236 (0x008BDA00) and bfmeTransform1236
// (0x008BDA70) plus the existing symbols.csv pin.  Apt render-emit body:
// kind 0x0d/0x12 string callback, 0x0e bounds add, 0x0f callback, 0x10
// glyph-run loop (lastX/lastY start at -1e8, advance*0.05), isKind11 alpha
// pair, isKind0C single shape.  Frame table (/FAsc) now equals retail:
// lastX 0x10 lastY 0x14 j 0x18 scale 0x1c i 0x20 font 0x24 tmp 0x28 matrix
// 0x2c data 0x44; advance in dead a slot, name string in dead c slot.
// Levers that moved it: full predicate per test (no shared kind local, else
// MSVC jump-threads 0xd straight to isKind11); callbacks are the function
// pointer globals g_bfmeSlot16/27/28/29VB (call [mem] each time, not a
// cached dllimport); shape test is a one-case switch (mov/dec/jne);
// __forceinline string operator=; lastX != rec.x operand order; ternary
// left/right; matrix stores tx,ty,a,d; (unsigned char) on the int
// isKind11/isKind0C results because the caller tests al.
// Remaining: found must be ebp (the zero register) and context ebx -- ours
// swaps them and adds xor ebx,ebx at +0xca; the find result compare at +0x8a
// is cmp eax,ebp in retail; the left/right type tests narrow to and al/cmp al
// here (retail dword and eax,0x3f/cmp eax,1) which also stops the early
// context->m_tail load at +0x17b.  An int-typed type local un-narrows them
// but flips found back to ebx.

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
};

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *storage);
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

class Rva8CD130String
{
public:
	Rva8CD130String()
	{
		++g_bfmeDefaultString1284.m_refCount;
		m_data = &g_bfmeDefaultString1284;
	}

	~Rva8CD130String()
	{
		BfmeStringData3AF0 *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	__forceinline Rva8CD130String &operator=(const Rva8CD130String &other)
	{
		++other.m_data->m_refCount;
		BfmeStringData3AF0 *old = m_data;
		if (--old->m_refCount == 0)
			g_bfmeStringPool1284->free(old);
		m_data = other.m_data;
		return *this;
	}

	const char *text() const { return (const char *)m_data + 8; }

	BfmeStringData3AF0 *m_data;
};

class Fields00898F60
{
public:
	Rva8CD130String underscoreFields00898F60();
};

class Rva00899770
{
public:
	virtual void addRef(void);
	virtual void release(void);
	enum Type { type1 = 1 };
	int type() const { return m_flags & 0x3f; }
	Type etype() const { return (Type)(m_flags & 0x3f); }

	unsigned m_flags;
	BfmeStringData3AF0 *m_string;
	char m_gap0c[0x14];
	Rva00899770 *m_indirect;
};

class BfmeStrVKI;

typedef Rva00899770 AptValue;

class Rva008AE770Stack
{
public:
	Rva00899770 *createString(void *value, int unused, BfmeStrVKI *name,
		int one, int another, int zero);
};

extern Rva008AE770Stack Rva008AE770TheStack;

class BfmeTab1024
{
public:
	int bfmeFind1024(int key);
};

class BfmeSubF1038
{
public:
	void *m_owner;
	void bfmeAdd1038(int a, int b);
};

struct BfmeQ1206
{
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
};

extern "C" BfmeQ1206 g_bfmeD1206;

class BfmeA1206
{
public:
	void bfmeGet1206(BfmeQ1206 *out);
};

struct BfmeDataLI
{
	int m_bfmeWords[6];
};

class BfmeItemLI
{
public:
	virtual void bfmeDoLI(void) = 0;
};

class BfmeThingLI
{
public:
	void bfmeAddLI(BfmeItemLI *item, const BfmeDataLI *data);
};

extern char *Rva008A5380Holder;

class Gen_008D2B50 { public: void bfmePush(void); };
class Gen_008D2B80 { public: void bfmePop(void); };
class Gen_008D2C80 { public: void bfmePush(void); };
class BfmeA1210 { public: void bfmePop1210(void); };

struct BfmeS1209
{
	float m_bfme00[8];
};

class BfmeA1209 { public: void bfmeOp1209(const BfmeS1209 *a); };
class BfmeThingDXH { public: void bfmeGoDXH(void *a); };

class Rva008A0F20Header
{
public:
	int isKind0C(void) const;
	int isKind11(void) const;
};

extern void (*g_bfmeSlot27VB)(void);
extern void (*g_bfmeSlot28VB)(void);
typedef void (__cdecl *RvaEmitAlpha1236)(void *);
typedef void (__cdecl *RvaEmitRender1236)(void *, void *);

extern void (*g_bfmeSlot16VB)(void);
extern void (*g_bfmeSlot29VB)(void);
extern char g_bfmeSpecialBlock1286;

struct RvaEmitShape1236
{
	int m_kind;
	char m_gap04[0x14];
	void *m_value;
};

static __forceinline void renderShape(RvaEmitShape1236 *shape, void *c)
{
	switch (shape->m_kind)
	{
	case 1:
		((RvaEmitRender1236)g_bfmeSlot28VB)(shape->m_value, c);
		break;
	}
}

struct RvaEmitFont1236
{
	char m_gap00[0x10];
	RvaEmitShape1236 **m_shapes;
};

struct RvaEmitFontTable1236
{
	char m_gap00[0x18];
	RvaEmitFont1236 **m_fonts;
};

struct RvaEmitGlyph1236
{
	short m_index;
	short m_advance;
};

struct RvaEmitRecord1236
{
	int m_font;
	BfmeS1209 m_color;
	float m_x;
	float m_y;
	float m_scale;
	int m_count;
	RvaEmitGlyph1236 *m_glyphs;
};

struct RvaEmitSequence1236
{
	char m_gap00[4];
	RvaEmitFontTable1236 *m_fontTable;
	RvaEmitShape1236 *m_ref08;
	RvaEmitShape1236 *m_ref0c;
	char m_gap10[8];
	BfmeQ1206 m_matrix;
	int m_count;
	RvaEmitRecord1236 *m_records;
};

struct RvaEmitTail1236
{
	char m_gap00[0x0c];
	RvaEmitShape1236 *m_ref0c;
};

struct RvaEmitContext1236
{
	char m_gap00[0x50];
	RvaEmitTail1236 *m_tail;
};

struct RvaEmitOwnerTable1236
{
	char m_gap00[0x58];
	RvaEmitContext1236 *m_context;
};

struct RvaEmitState1236
{
	char m_gap00[0x0c];
	RvaEmitSequence1236 *m_sequence;
	BfmeTab1024 *m_table;
	int m_bfme14;
	float m_alpha;
	unsigned m_bits;
	BfmeSubF1038 m_bfme20;
	BfmeSubF1038 m_bfme24;
};

struct RvaEmitLerp1236
{
	char m_gap00[0x2c];
	float m_factor;
};

class BfmeB1236 : public Rva00899770
{
public:
	void bfmeEmit1236(void *a, int unused, void *c);

	char m_gap24[0x24];
	RvaEmitLerp1236 *m_bfme48;
	void *m_bfme4c;
	RvaEmitState1236 *m_bfme50;
};

typedef void (__cdecl *RvaEmitSink1236)(const char *, const char *, void *, const char *);
typedef void (__cdecl *RvaEmitNotify1236)(void *, void *);

void BfmeB1236::bfmeEmit1236(void *a, int unused, void *c)
{
	RvaEmitLerp1236 *lerp = m_bfme48;
	if (lerp != 0 && lerp->m_factor < 0.5f)
		return;

	if (((m_flags & 0x3f) == 0x0d && !((unsigned char)~(m_flags >> 15) & 1)) ||
		((m_flags & 0x3f) == 0x12 && !((unsigned char)~(m_flags >> 15) & 1)))
	{
		RvaEmitState1236 *state = m_bfme50;
		if ((state->m_bits & 0x0c000000) == 0)
		{
			if (state->m_table != 0 && (Rva00899770 *)state->m_table->bfmeFind1024(0x013384c8) != 0)
				state->m_bits = (state->m_bits & 0xf7ffffff) | 0x04000000;
			else
				state->m_bits = (state->m_bits & 0xfbffffff) | 0x08000000;
		}
		if ((state->m_bits & 0x0c000000) == 0x04000000)
		{
			AptValue *found = 0;
			if (state->m_table != 0)
				found = (AptValue *)state->m_table->bfmeFind1024(0x013384c8);
			RvaEmitContext1236 *context =
				((RvaEmitOwnerTable1236 *)*(void **)state->m_bfme24.m_owner)->m_context;
			if (context == 0)
				return;
			Rva00899770 *created = Rva008AE770TheStack.createString(
				this, 0, (BfmeStrVKI *)0x013384c0, 1, 1, 0);
			created->addRef();
			Rva8CD130String name;
			name = ((Fields00898F60 *)this)->underscoreFields00898F60();
			AptValue *left = (created->m_flags & 0x3f) == 1 ? created : created->m_indirect;
			AptValue *right = (found->m_flags & 0x3f) == 1 ? found : found->m_indirect;
			((RvaEmitSink1236)g_bfmeSlot29VB)((const char *)right->m_string + 8,
				(const char *)left->m_string + 8,
				context->m_tail->m_ref0c->m_value, name.text());
			created->release();
		}
		else
			state->m_bfme24.bfmeAdd1038((int)a, (int)c);
		return;
	}

	if ((m_flags & 0x3f) == 0x0e && !((unsigned char)~(m_flags >> 15) & 1))
	{
		BfmeQ1206 data;
		((BfmeA1206 *)a)->bfmeGet1206(&data);
		((BfmeThingLI *)Rva008A5380Holder)->bfmeAddLI((BfmeItemLI *)this, (const BfmeDataLI *)&data);
		m_bfme50->m_bfme20.bfmeAdd1038((int)a, (int)c);
		return;
	}

	if ((m_flags & 0x3f) == 0x0f && !((unsigned char)~(m_flags >> 15) & 1))
	{
		RvaEmitState1236 *state = m_bfme50;
		void *value = state->m_bfme20.m_owner;
		if (value != 0 && value != &g_bfmeSpecialBlock1286)
			((RvaEmitNotify1236)g_bfmeSlot16VB)(value, c);
		return;
	}

	if ((m_flags & 0x3f) == 0x10 && !((unsigned char)~(m_flags >> 15) & 1))
	{
		RvaEmitState1236 *state = m_bfme50;
		((Gen_008D2C80 *)a)->bfmePush();
		((BfmeThingDXH *)a)->bfmeGoDXH(&state->m_sequence->m_matrix);
		BfmeQ1206 matrix = g_bfmeD1206;
		float lastX = -100000000.0f;
		float lastY = -100000000.0f;
		float advance = 0.0f;
		for (int i = 0; i < state->m_sequence->m_count; ++i)
		{
			((Gen_008D2B50 *)a)->bfmePush();
			((BfmeA1209 *)a)->bfmeOp1209(&state->m_sequence->m_records[i].m_color);
			RvaEmitFont1236 *font =
				state->m_sequence->m_fontTable->m_fonts[state->m_sequence->m_records[i].m_font];
			if (lastX != state->m_sequence->m_records[i].m_x ||
				lastY != state->m_sequence->m_records[i].m_y)
				advance = 0.0f;
			lastX = state->m_sequence->m_records[i].m_x;
			lastY = state->m_sequence->m_records[i].m_y;
			float scale = state->m_sequence->m_records[i].m_scale;
			for (int j = 0; j < state->m_sequence->m_records[i].m_count; ++j)
			{
				*(float *)&matrix.m_bfme10 = advance + lastX;
				*(float *)&matrix.m_bfme14 = lastY;
				*(float *)&matrix.m_bfme00 = scale;
				*(float *)&matrix.m_bfme0c = scale;
				RvaEmitGlyph1236 *glyph = &state->m_sequence->m_records[i].m_glyphs[j];
				RvaEmitShape1236 *shape = font->m_shapes[glyph->m_index];
				((Gen_008D2C80 *)a)->bfmePush();
				((BfmeThingDXH *)a)->bfmeGoDXH(&matrix);
				renderShape(shape, c);
				((BfmeA1210 *)a)->bfmePop1210();
				advance += (float)glyph->m_advance * 0.05f;
			}
			((Gen_008D2B80 *)a)->bfmePop();
		}
		((BfmeA1210 *)a)->bfmePop1210();
		return;
	}

	if ((unsigned char)((Rva008A0F20Header *)this)->isKind11())
	{
		RvaEmitState1236 *state = m_bfme50;
		((Gen_008D2B50 *)a)->bfmePush();
		*(float *)a = 1.0f - state->m_alpha;
		((RvaEmitAlpha1236)g_bfmeSlot27VB)(a);
		RvaEmitShape1236 *first = state->m_sequence->m_ref08;
		renderShape(first, c);
		*(float *)a = state->m_alpha;
		((RvaEmitAlpha1236)g_bfmeSlot27VB)(a);
		RvaEmitShape1236 *second = state->m_sequence->m_ref0c;
		renderShape(second, c);
		((Gen_008D2B80 *)a)->bfmePop();
		return;
	}

	if ((unsigned char)((Rva008A0F20Header *)this)->isKind0C())
	{
		RvaEmitShape1236 *shape = (RvaEmitShape1236 *)m_bfme50->m_sequence;
		renderShape(shape, c);
	}
}
