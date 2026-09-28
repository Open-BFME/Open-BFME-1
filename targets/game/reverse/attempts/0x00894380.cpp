// ?Rva00894380@@YAXXZ
// partial score=0.2995 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00894380 (728 B): per-frame playback of a recorded command stream.
// Opaque owner: no named caller; globals keep their address tokens.
#include <string.h>
typedef unsigned int UnsignedInt;

struct StringBlock00894380 { unsigned short refs, length, capacity, flags; char text[1]; };
struct StringPool00894380 { void *unused; void (__cdecl *free)(void *); };
extern StringPool00894380 *g_bfmeStringPool1284;
class BfmeStrVKI {
public:
	BfmeStrVKI(const char *text) { bfmeSetVKI(text); }
	void bfmeSetVKI(const char *);
	~BfmeStrVKI() { StringBlock00894380 *p = m_block; if (--p->refs == 0) g_bfmeStringPool1284->free(p); }
	StringBlock00894380 *m_block;
};

struct Item00894380 { UnsignedInt m_00; UnsignedInt kind; };
class List00894380
{
public:
	UnsignedInt count;
	UnsignedInt m_04;
	Item00894380 *items;
	void rva008941A0(const BfmeStrVKI &name);
	bool allSettled() const
	{
		for (const Item00894380 *p = items; p != items + count; ++p)
			if (p->kind != 4 && p->kind != 2)
				return false;
		return true;
	}
};

class BfmeJ1017 { public: void bfmeInsert(UnsignedInt word); };
class BfmeTracker4310 { public: void rva00896710(); };

struct Record00894380 { int value; int kind; };

extern char *Rva008A5380Holder;          // 0x013377D8
extern int g_bfme1017I;                  // 0x013377DC stream base
extern UnsignedInt *g_013377E0;          // stream cursor
extern int g_013377E4;                   // stream length
extern UnsignedInt g_013377EC;           // current frame
extern List00894380 *g_013377F0;
extern BfmeTracker4310 *g_013377F8;
extern "C" int g_rva00891FA0Ready;
extern "C" int g_rva00891FA0Value;
extern "C" __declspec(dllimport) void __cdecl Rva00891FA0SendText(const char *text);
extern "C" __declspec(dllimport) void __cdecl Rva00891FA0SendRecord(Record00894380 *record, int size);
extern "C" int __cdecl sprintf(char *, const char *, ...);
int Rva00892A70(int frames);

struct Value00894380
{
	void *m_vtbl;
	UnsignedInt m_04;
	bool isSettledKind() const { return (m_04 & 0x3f) == 0x12 && !((unsigned char)~(m_04 >> 15) & 1); }
};
struct Owner00894380 { char m_00[0x58]; Value00894380 *m_58; };

void Rva00894380()
{
	UnsignedInt stop = g_013377EC + 1;
	if (!g_bfme1017I)
		return;

	while (g_013377EC != stop)
	{
		if (g_013377F0->allSettled())
		{
			while (*g_013377E0 <= g_013377EC)
			{
				UnsignedInt *cursor = ++g_013377E0;
				switch (*(unsigned char *)cursor & 3)
				{
				case 0:
				case 1:
				{
					UnsignedInt word = *cursor;
					g_013377E0 = cursor + 1;
					((BfmeJ1017 *)Rva008A5380Holder)->bfmeInsert(word);
					break;
				}
				case 2:
				{
					char *text = (char *)cursor + 1;
					g_013377E0 = (UnsignedInt *)text;
					g_013377E0 = (UnsignedInt *)(text + strlen(text) + 1);
					BfmeStrVKI name(text);
					g_013377F0->rva008941A0(name);
					break;
				}
				case 3:
					g_013377E0 = (UnsignedInt *)((char *)cursor + 1);
					if (!g_rva00891FA0Ready)
					{
						char buffer[16];
						sprintf(buffer, "%06d", g_013377EC);
						Rva00891FA0SendText(buffer);
					}
					break;
				}
			}
		}

		if ((int)((char *)g_013377E0 - (char *)g_bfme1017I) >= g_013377E4)
		{
			g_bfme1017I = 0;
			g_013377E0 = 0;
			if (g_rva00891FA0Ready)
				g_rva00891FA0Ready = 0;
			return;
		}

		if (!g_013377F0->allSettled())
			goto flush;
		{
			Value00894380 *value = (*(Owner00894380 **)(Rva008A5380Holder + 0x122c))->m_58;
			if (!value || !value->isSettledKind())
				goto flush;
		}

		if (Rva00892A70(1) && g_rva00891FA0Ready)
		{
			char buffer[16];
			sprintf(buffer, "%06d", g_rva00891FA0Value);
			Rva00891FA0SendText(buffer);
			Record00894380 record;
			record.value = g_rva00891FA0Value;
			record.kind = 3;
			Rva00891FA0SendRecord(&record, 5);
		}

		++g_013377EC;
		if (!g_bfme1017I)
			return;
	}
	return;

flush:
	g_013377F8->rva00896710();
}
