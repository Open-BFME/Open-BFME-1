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
	bool operator==(const Gen_t_0039e9d0_p128pod &other) const;

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

void _Construct(FlightDeckBehavior::RunwayInfo *destination,
	const FlightDeckBehavior::RunwayInfo &source);
}

class BfmeAttributePool : public _STL::vector<FlightDeckBehavior::RunwayInfo>
{
};

extern BfmeAttributePool TheBfmeAttributePool;

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
		if (*(Gen_t_0039e9d0_p128pod *)cursor ==
			*(Gen_t_0039e9d0_p128pod *)entry)
		{
			++*(UnsignedInt *)((char *)TheBfmeAttributePool.m_start
				+ index * 0x88 + 0x84);
			return index;
		}
	}

	entry->m_useCount = 1;
	if (TheBfmeAttributePool.m_finish != TheBfmeAttributePool.m_end)
	{
		_STL::_Construct(
			(FlightDeckBehavior::RunwayInfo *)TheBfmeAttributePool.m_finish,
			*(FlightDeckBehavior::RunwayInfo *)entry);
		TheBfmeAttributePool.m_finish += 1;
	}
	else
	{
		((_STL::vector<FlightDeckBehavior::RunwayInfo> *)&TheBfmeAttributePool)->
			_M_insert_overflow(
				(FlightDeckBehavior::RunwayInfo *)TheBfmeAttributePool.m_finish,
				*(FlightDeckBehavior::RunwayInfo *)entry, tag, 1, true);
	}

	return (TheBfmeAttributePool.m_finish - TheBfmeAttributePool.m_start) - 1;
}
