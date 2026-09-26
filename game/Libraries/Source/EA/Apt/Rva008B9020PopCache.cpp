// 0x008B9020: pop a tagged cache entry, falling back to the Apt null value.

class AptValue;
extern AptValue *g_bfmeFallbackDB;

struct Rva008B9020Owner
{
	unsigned char m_pad0[4];
	unsigned int m_flags;
	unsigned char m_pad1[0x20 - 8];
	void **m_arr;
	unsigned char m_pad2[4];
	int m_count;
};

void *rva008B9020PopCache(Rva008B9020Owner *obj)
{
	void *result = g_bfmeFallbackDB;
	unsigned int flags = obj->m_flags;
	if ((flags & 0x3f) == 0x16)
	{
		unsigned char bit = (unsigned char)(flags >> 15);
		bit = ~bit;
		if (bit & 1)
			return result;

		int count = obj->m_count;
		if (count <= 0)
			return result;

		int lastIndex = count - 1;
		if (lastIndex >= 0 && lastIndex < count)
		{
			void *elem = obj->m_arr[lastIndex];
			unsigned int masked = (unsigned int)elem & ~1u;
			if (masked == 0)
				masked = (unsigned int)result;
			result = (void *)masked;
		}

		obj->m_count = lastIndex;
		obj->m_arr[lastIndex] = 0;
	}
	return result;
}
