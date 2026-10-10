// cl: /DNDEBUG /MD /EHsc

// Open-BFME: intern a 0x88-byte Gen00043699 entry in the BFME attribute pool.
// The callers BfmeSecondPlainMember::setSecondPlain and Gen003A0410's
// constructor reach this body through the retail ILT at 0x00037FD8.

typedef unsigned int UnsignedInt;

class Gen00043699
{
public:
	unsigned char m_data[0x84];
	int m_useCount;
};

class Gen_t_0039e9d0_p128pod
{
public:
	unsigned char m_data[0x84];
};

class FlightDeckBehavior
{
public:
	struct RunwayInfo
	{
		unsigned char m_data[0x88];
	};
};

namespace _STL
{
class __false_type
{
};

template <class T>
class allocator
{
};

template <class T, class A = allocator<T> >
class vector
{
public:
	void _M_insert_overflow(T *position, const T &value,
		const __false_type &tag, UnsignedInt count, bool last);

	T *m_start;
	T *m_finish;
	T *m_end;
};


}

class BfmeAttributePool : public _STL::vector<FlightDeckBehavior::RunwayInfo>
{
};

// Rva00C6B2C0PoolInitialization.cpp owns the 12-byte pool cell at VA 012F1000.
struct Rva00EF1000Storage;
extern Rva00EF1000Storage Rva00EF1000Global;
#define TheBfmeAttributePool (reinterpret_cast<BfmeAttributePool &>(Rva00EF1000Global))

// Retail comparison returns one unsigned byte in AL (ECX/RET4);
// construction is cdecl/RET0, and overflow is ECX/RET20.
extern "C" void __cdecl __identifier("?j_000063f7@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_00008049@@YAXXZ")(
	FlightDeckBehavior::RunwayInfo *, const FlightDeckBehavior::RunwayInfo &);
extern "C" void __cdecl __identifier("?j_00025c89@@YAXXZ")();

// ?bfmeInternAttributeEntry@@YAIPAVGen00043699@@@Z
UnsignedInt bfmeInternAttributeEntry(Gen00043699 *entry)
{
	_STL::__false_type tag;
	int count = TheBfmeAttributePool.m_finish
		- TheBfmeAttributePool.m_start;
	register unsigned char *cursor =
		(unsigned char *)TheBfmeAttributePool.m_start;
	for (int index = 0; index < count; ++index, cursor += 0x88)
	{
		union
		{
			void (__cdecl *symbol)();
			unsigned char (Gen_t_0039e9d0_p128pod::*member)(const Gen_t_0039e9d0_p128pod &) const;
		} equal;
		equal.symbol = &__identifier("?j_000063f7@@YAXXZ");
		if ((((Gen_t_0039e9d0_p128pod *)cursor)->*equal.member)(
			*(Gen_t_0039e9d0_p128pod *)entry))
		{
			++*(UnsignedInt *)((char *)TheBfmeAttributePool.m_start
				+ index * 0x88 + 0x84);
			return index;
		}
	}

	entry->m_useCount = 1;
	if (TheBfmeAttributePool.m_finish != TheBfmeAttributePool.m_end)
	{
		__identifier("?j_00008049@@YAXXZ")(
			(FlightDeckBehavior::RunwayInfo *)TheBfmeAttributePool.m_finish,
			*(FlightDeckBehavior::RunwayInfo *)entry);
		TheBfmeAttributePool.m_finish += 1;
	}
	else
	{
		union
		{
			void (__cdecl *symbol)();
			void (_STL::vector<FlightDeckBehavior::RunwayInfo>::*member)(
				FlightDeckBehavior::RunwayInfo *, const FlightDeckBehavior::RunwayInfo &,
				const _STL::__false_type &, UnsignedInt, bool);
		} grow;
		grow.symbol = &__identifier("?j_00025c89@@YAXXZ");
		(TheBfmeAttributePool.*grow.member)(
				(FlightDeckBehavior::RunwayInfo *)TheBfmeAttributePool.m_finish,
				*(FlightDeckBehavior::RunwayInfo *)entry, tag, 1, true);
	}

	return (TheBfmeAttributePool.m_finish - TheBfmeAttributePool.m_start) - 1;
}
