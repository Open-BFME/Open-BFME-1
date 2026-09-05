// ?bfmeRunEUAe@BfmeSpecialPowerAllowanceStore@@QAEXPAVBfmePlayerSpecialPowerState@@PAX@Z
// partial score=0.25 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc

// BfmeSpecialPowerAllowanceStore::bfmeRunEUAe, retail 0x0039C260, 287 bytes.
// The callback finds the allowance entry named by its context and removes that
// entry's index from the player's pending-index vector.

typedef int Int;
typedef unsigned short UnsignedShort;

extern "C" int __cdecl memcmp(const void *left, const void *right,
		unsigned int count);
extern "C" __declspec(dllimport) void *__cdecl BfmeMemMove(
		void *destination, const void *source, unsigned int bytes);

struct BfmeAsciiStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;
	UnsignedShort m_pad;
};

class BfmeAsciiString
{
public:
	Int getLength(void) const { return m_data ? m_data->m_len : 0; }
	const char *str(void) const
	{
		return m_data ? (const char *)(m_data + 1) : "";
	}
	Int compare(const BfmeAsciiString &other) const
	{
		Int otherLength = other.getLength();
		const char *otherData = other.str();
		Int thisLength = getLength();
		const char *thisData = str();
		Int shorter = thisLength < otherLength ? thisLength : otherLength;
		Int result = memcmp(thisData, otherData, shorter);
		if (result != 0)
			return result;
		return thisLength - otherLength;
	}

private:
	BfmeAsciiStringData *m_data;
};

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride(void);

private:
	char m_vftable[4];

public:
	BfmeOverridable *m_nextOverride;
	char m_overrideFlag[4];
};

class BfmeAllowanceEntry : public BfmeOverridable
{
public:
	BfmeAsciiString m_name;
};

class BfmePlayerSpecialPowerState
{
public:
	char m_head[8];
	Int *m_begin;
	Int *m_end;
};

class BfmeSpecialPowerAllowanceStore
{
public:
	void bfmeRunEUAe(BfmePlayerSpecialPowerState *state, void *context);

private:
	char m_head[8];
	BfmeAllowanceEntry **m_begin;
	BfmeAllowanceEntry **m_end;
};

// ?bfmeRunEUAe@BfmeSpecialPowerAllowanceStore@@QAEXPAVBfmePlayerSpecialPowerState@@PAX@Z
void BfmeSpecialPowerAllowanceStore::bfmeRunEUAe(
		BfmePlayerSpecialPowerState *state, void *context)
{
	unsigned int count = (unsigned int)(m_end - m_begin);
	if (count <= 0)
		return;

	const BfmeAsciiString *name = (const BfmeAsciiString *)context;
	BfmeAllowanceEntry **cursor = m_begin;
	unsigned int index = 0;
	while (index < count)
	{
		BfmeAllowanceEntry *entry = *cursor;
		if (entry->m_nextOverride)
			entry = (BfmeAllowanceEntry *)entry->m_nextOverride->friend_getFinalOverride();

		if (entry->m_name.compare(*name) == 0)
		{
			Int *position = state->m_begin;
			Int *end = state->m_end;
			while (position != end)
			{
				if (*position == (Int)index)
				{
					Int *nextPosition = position + 1;
					if (end != nextPosition)
						BfmeMemMove(position, nextPosition,
							(unsigned int)((char *)end - (char *)nextPosition));
					state->m_end--;
					return;
				}
				++position;
			}
			return;
		}

		++index;
		++cursor;
		count = (unsigned int)(m_end - m_begin);
	}
}
