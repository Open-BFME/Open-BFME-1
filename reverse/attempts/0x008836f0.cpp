// ?rva008836F0@Rva008838F0Owner@@QAEXPAXPADI@Z
// partial score=0.22 date=2026-09-20
// ?rva008836F0@Rva008838F0Owner@@QAEXPAXPADI@Z
// cl: /O2 /DNDEBUG /MD

extern "C" __declspec(dllimport) int __cdecl sprintf(
	char *buffer, const char *format, ...);
extern "C" void *__cdecl memcpy(void *destination, const void *source,
	unsigned int count);
#pragma intrinsic(memcpy)
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *lock);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *lock);

class DebugStackwalk
{
public:
	class Signature
	{
	public:
		static void GetSymbol(unsigned address, char *buffer, unsigned size);
	};
};

struct Rva008838F0Node
{
	Rva008838F0Node *m_next;
	int m_type;
	unsigned int m_key;
	unsigned int m_pad0c[2];
	void *m_value;
	unsigned int m_count;
	void *m_values[1];
	unsigned char m_pad20[0x9c - 0x20];
	int m_freeCheckpoint;
};

class Rva008838F0Owner
{
public:
	void rva008836F0(void *block, char *diagnostic, unsigned int limit);

private:
	void *m_owner;
	void **m_table;
	unsigned int m_tableIndex;
	Rva008838F0Node *m_buckets[0x2b7b];
	Rva008838F0Node *m_slots[0x7530];
	unsigned int m_slotIndex;
	Rva008838F0Node *m_current;
	unsigned char m_disabled;
	char m_pad282c1[3];
	void *m_previousOwner;
	void *m_lock;
};

void Rva008838F0Owner::rva008836F0(void *block, char *diagnostic, unsigned int limit)
{
	unsigned int key = reinterpret_cast<unsigned int>(block);
	register Rva008838F0Owner *tracker = this;
	if (*reinterpret_cast<volatile unsigned int *>(&limit) < 0x64)
	{
		diagnostic[0] = 0;
		return;
	}

	if (tracker->m_disabled != 0)
	{
		memcpy(diagnostic, reinterpret_cast<const void *>(0x01132E28), 0x1a);
		return;
	}

	if (tracker->m_lock != 0)
		EnterCriticalSection(tracker->m_lock);

	Rva008838F0Node **link = &tracker->m_buckets[key % 0x2b7b];
	while (*link != 0 && (*link)->m_key != key)
		link = &(*link)->m_next;

	Rva008838F0Node *node = *link;
	if (node == 0)
	{
		diagnostic[0] = 0;
		goto leave;
	}

	int written;
	if (node->m_freeCheckpoint >= 0)
	{
		const char *name;
		if (node->m_type < 0)
			name = reinterpret_cast<const char *>(0x010EB03C);
		else
			name = reinterpret_cast<const char *>(tracker->m_table[node->m_type]);
		written = sprintf(diagnostic,
			reinterpret_cast<const char *>(0x01132DEC), key, name);
	}
	else if (node->m_value != 0)
	{
		written = sprintf(diagnostic,
			reinterpret_cast<const char *>(0x0109106C), node->m_value);
	}
	else
	{
		diagnostic[0] = 0;
		written = 0;
	}

	char *output = diagnostic + written;
	unsigned int remaining = limit - written;
	unsigned int index = 0;
	while (index < node->m_count)
	{
		char symbol[0x1f8];
		DebugStackwalk::Signature::GetSymbol(
			reinterpret_cast<unsigned int>(node->m_values[index]), symbol, 0x1ff);

		char *end = symbol + 0x0c;
		while (*end != 0)
			++end;
		*reinterpret_cast<unsigned short *>(end) =
			*reinterpret_cast<const unsigned short *>(0x01080294);

		unsigned int length = 0;
		while (symbol[length] != 0)
			++length;
		if (length > remaining)
			break;

		unsigned int copy = length + 1;
		char *source = symbol;
		while (copy != 0)
		{
			*output++ = *source++;
			--copy;
		}
		remaining -= length;
		++index;
	}

leave:
	if (tracker->m_lock != 0)
		LeaveCriticalSection(tracker->m_lock);
}
