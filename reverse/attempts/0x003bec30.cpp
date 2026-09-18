// ?finish@Rva003BEED0@@QAEXXZ
// partial score=0.8 date=2026-09-18
// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc
//
// Rva003BEED0::finish, retail 0x003BEC30, 167 bytes.
// The ILT at 0x0000A754 and the seven callers identify this as the shared
// pointer-vector refresh used by the living-world gate objects.  The first
// callee returns the entry name through the existing StringBase copy ABI.

extern void j_0004958a(void);
extern void j_00044391(void);
extern void j_0002437a(void);
extern void j_000394e6(void);

class Rva003BEC30Owner;

template <typename T>
class StringBase
{
public:
	StringBase(void) {}
	StringBase(const StringBase &other) : m_data(other.m_data) {}
	~StringBase() { releaseBuffer(); }

	void *m_data;

private:
	void releaseBuffer(void);
	friend class Rva003BEC30Owner;
};

struct Rva003BEC30Entry
{
	char m_pad00[0x1d];
	unsigned char m_flag1d;
};

struct Rva003BEC30NameView
{
	StringBase<char> *copyName(StringBase<char> *out);
};
typedef StringBase<char> *(Rva003BEC30NameView::*Rva003BEC30Name)(StringBase<char> *out);

struct Rva003BEC30LogicView
{
	int invoke(StringBase<char> *name);
};
typedef int (Rva003BEC30LogicView::*Rva003BEC30Invoke)(StringBase<char> *name);

struct Rva003BEC30TierView
{
	int tier(int value);
};
typedef int (Rva003BEC30TierView::*Rva003BEC30Tier)(int value);

struct Rva003BEC30FinishView
{
	void finish(int value);
};
typedef void (Rva003BEC30FinishView::*Rva003BEC30Finish)(int value);

struct Rva003BEC30Range
{
	Rva003BEC30Entry **m_begin;
	Rva003BEC30Entry **m_end;

	unsigned int size(void) const
	{
		return (unsigned int)(m_end - m_begin);
	}
};

class Rva003BEED0
{
public:
	void finish(void);

	char m_pad00[0x0c];
	Rva003BEC30Range m_entries;
	char m_pad14[0x14];
	Rva003BEC30TierView *m_tierOwner;
};

void Rva003BEED0::finish(void)
{
	Rva003BEED0 *owner = this;
	Rva003BEED0 *tierBase = this;
	int value;
	int index = 0;
	if (owner->m_entries.size() > 0)
	{
		union { void (*raw)(void); Rva003BEC30Invoke member; } invokeCast;
		union { void (*raw)(void); Rva003BEC30Tier member; } tierCast;
		union { void (*raw)(void); Rva003BEC30Finish member; } finishCast;
		invokeCast.raw = j_00044391;
		tierCast.raw = j_0002437a;
		finishCast.raw = j_000394e6;
			do
		{
			Rva003BEC30Entry *entry = owner->m_entries.m_begin[index];
			if (entry->m_flag1d != 0)
			{
				{
					StringBase<char> entryName;
					union { void (*raw)(void); Rva003BEC30Name member; } nameCast;
					nameCast.raw = j_0004958a;
					StringBase<char> *name =
						(reinterpret_cast<Rva003BEC30NameView *>(entry)->*nameCast.member)(&entryName);
					Rva003BEC30LogicView *logic =
						*reinterpret_cast<Rva003BEC30LogicView **>(0x012F0898);
					value = (logic->*invokeCast.member)(name);
				}
				if (value != -1)
				{
					int tier = (tierBase->m_tierOwner->*tierCast.member)(value);
					(reinterpret_cast<Rva003BEC30FinishView *>(entry)->*finishCast.member)(tier);
				}
			}
			++index;
		} while ((unsigned int)index < owner->m_entries.size());
	}
}
