// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Apt render-emit body, retail 0x008ADBD0 (1452 bytes); identity from the matched
// callers bfmeGo1236 and bfmeTransform1236 in BfmeConv1236.cpp.

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
	Rva8CD130String &string()
	{
		int type = m_flags & 0x3f;
		return *(Rva8CD130String *)&((type == 1 ? this : m_indirect)->m_string);
	}

	unsigned m_flags;
	BfmeStringData3AF0 *m_string;
	char m_gap0c[0x14];
	Rva00899770 *m_indirect;
};

class BfmeStrVKI;

typedef Rva00899770 AptValue;

// Retail's object at 0x01338748 is `struct Rva008AE770Stack` (Rva00C6DCC0StaticInit.cpp
// defines it), and MSVC 7.1 mangles a global's class type 3V for `class` but 3U for
// `struct`, so this must be spelled `struct` to reference ?Rva008AE770TheStack@@3U...
struct Rva008AE770Stack
{
public:
	Rva00899770 *createString(void *value, int unused, BfmeStrVKI *name,
		int one, int another, int zero);
};

extern Rva008AE770Stack Rva008AE770TheStack;

extern int key013384C0, key013384C8;

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

// retail 0x013377D8; defining spelling (BfmePicker1284.cpp), declared
// incomplete here because only the pointer value is cast and passed on.
struct BfmePickWorld1284;
extern BfmePickWorld1284 *g_bfmeHolderBU;

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

	AptValue *getValue(void)
	{
		return m_table != 0 ? (AptValue *)m_table->bfmeFind1024((int)&key013384C8) : 0;
	}
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
			if (state->getValue() != 0)
				state->m_bits = (state->m_bits & 0xf7ffffff) | 0x04000000;
			else
				state->m_bits = (state->m_bits & 0xfbffffff) | 0x08000000;
		}
		if ((state->m_bits & 0x0c000000) == 0x04000000)
		{
			AptValue *found = state->getValue();
			RvaEmitContext1236 *context =
				((RvaEmitOwnerTable1236 *)*(void **)state->m_bfme24.m_owner)->m_context;
			if (context == 0)
				return;
			Rva00899770 *created = Rva008AE770TheStack.createString(
				this, 0, (BfmeStrVKI *)&key013384C0, 1, 1, 0);
			created->addRef();
			Rva8CD130String name;
			name = ((Fields00898F60 *)this)->underscoreFields00898F60();
			RvaEmitTail1236 *tail = context->m_tail;
			((RvaEmitSink1236)g_bfmeSlot29VB)(found->string().text(), created->string().text(),
				tail->m_ref0c->m_value, name.text());
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
		((BfmeThingLI *)(void *)g_bfmeHolderBU)->bfmeAddLI((BfmeItemLI *)this, (const BfmeDataLI *)&data);
		m_bfme50->m_bfme20.bfmeAdd1038((int)a, (int)c);
		return;
	}

	if ((m_flags & 0x3f) == 0x0f && !((unsigned char)~(m_flags >> 15) & 1))
	{
		RvaEmitState1236 *state = m_bfme50;
		if (state->m_bfme20.m_owner != 0 && state->m_bfme20.m_owner != &g_bfmeSpecialBlock1286)
			((RvaEmitNotify1236)g_bfmeSlot16VB)(state->m_bfme20.m_owner, c);
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
