// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
struct Rva00699180Pair
{
	float m_value;
	unsigned int m_key;
};


// Product clamping and output-pair refresh share this receiver and translation unit.
// Keeping both helper bodies visible preserves retail's ECX call sequence at 0x006994C0.
class Rva00699430Owner {
public:
	void productClamp(int index);
	char m_bytes[0x60];
};
void Rva00699430Owner::productClamp(int index)
{
	char *slot = m_bytes + index * 12;
	float *begin = *(float **)(slot + 0x4c);
	float *end = *(float **)(slot + 0x50);
	float *out = (float *)(m_bytes + 0x34 + index * 4);
	*out = 1.0f;
	if (begin != end)
	{
		do
		{
			*out = *out * *begin;
			begin = (float *)((char *)begin + 8);
		} while (begin != end);
	}
	float v = *out;
	if (v < 0.0f)
	{
		static float s_zero = 0.0f;
		v = s_zero;
		*out = v;
		return;
	}
	if (v > 1.0f)
		v = 1.0f;
	*out = v;
}

extern float g_milesVolume012BA12C;
extern unsigned char g_012BA144;

class Rva00699180Owner
{
	friend class Rva0069F4D0Block;
public:
	void removeByKey(unsigned int key);
	void refreshPair(int a, int b);
	void refreshAll();
	void setVolumes(float volume, unsigned char flags);

	char m_pad0[4];
	float m_base[12];
	float m_product[6];
	_STL::vector<Rva00699180Pair> m_buckets[6];
	float m_atten;
	float m_vol;
	float m_scale;
	char m_padA0[0xC8 - 0xA0];
	float m_slot[12][4];
	unsigned char m_dirty[48];
};

void Rva00699180Owner::refreshPair(int a, int b)
{
	int idx = b + a * 2;
	float *slot = (float *)((char *)this + 0xC8 + (idx << 4));
	float old[4];
	old[0] = slot[0];
	old[1] = slot[1];
	old[2] = slot[2];
	old[3] = slot[3];

	if (a == 5)
	{
		slot[0] = 1.0f;
		slot[1] = 1.0f;
		slot[2] = 1.0f;
		slot[3] = 1.0f;
	}
	else if (g_012BA144)
	{
		slot[0] = *((float *)((char *)this + 4 + idx * 4)) * (&g_milesVolume012BA12C)[a] * m_vol;
		if (b == 1)
			slot[0] = slot[0] * m_atten;
		slot[1] = slot[0] * m_scale;
		slot[2] = m_product[a] * slot[0];
		slot[3] = slot[2] * m_scale;

		float x0 = slot[0];
		if (x0 < 0.0f)
			x0 = 0.0f;
		else if (x0 > 1.0f)
			x0 = 1.0f;
		slot[0] = x0;

		float x1 = slot[1];
		if (x1 < 0.0f)
			x1 = 0.0f;
		else if (x1 > 1.0f)
			x1 = 1.0f;
		slot[1] = x1;

		float x2 = slot[2];
		if (x2 < 0.0f)
			x2 = 0.0f;
		else if (x2 > 1.0f)
			x2 = 1.0f;
		slot[2] = x2;

		float x3 = slot[3];
		if (x3 < 0.0f)
			x3 = 0.0f;
		else if (x3 > 1.0f)
			x3 = 1.0f;
		slot[3] = x3;
	}
	else
	{
		slot[0] = 0.0f;
		slot[1] = 0.0f;
		slot[2] = 0.0f;
		slot[3] = 0.0f;
	}

	for (int i = 0; i < 4; ++i)
	{
		if (slot[i] != old[i])
			*((unsigned char *)this + 0x188 + (b + a * 2) * 4 + i) = 2;
	}
}

void Rva00699180Owner::refreshAll()
{
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 2; ++j)
			refreshPair(i, j);
	}
}

void Rva00699180Owner::setVolumes(float volume, unsigned char flags)
{
	if (flags & 1)
	{
		m_base[4] = volume;
		m_base[5] = volume;
		for (int i = 0; i < 2; ++i)
			refreshPair(2, i);
	}
	if (flags & 2)
	{
		m_base[0] = volume;
		refreshPair(0, 0);
	}
	if (flags & 4)
	{
		m_base[1] = volume;
		refreshPair(0, 1);
	}
	if (flags & 8)
	{
		m_base[2] = volume;
		m_base[8] = volume;
		m_base[3] = volume;
		m_base[9] = volume;
		for (int i = 0; i < 2; ++i)
			refreshPair(1, i);
		for (int i = 0; i < 2; ++i)
			refreshPair(4, i);
	}
	if (flags & 0x10)
	{
		m_base[6] = volume;
		m_base[7] = volume;
		for (int i = 0; i < 2; ++i)
			refreshPair(3, i);
	}
}

// Retail 0x006994C0 updates one product channel, then its two output pairs.
// The receiver layout is shared by the matched productClamp and refreshPair bodies.
class Rva006994C0Owner {
public:
    void recomputeProductChannel(int index);
};

void Rva006994C0Owner::recomputeProductChannel(int index)
{
    ((Rva00699430Owner *)this)->productClamp(index);
    for (int i = 0; i < 2; ++i) {
        ((Rva00699180Owner *)this)->refreshPair(index, i);
    }
}

// Retail 0069F2F0: erase matching eight-byte entries in all six vectors.
// Both existing helper definitions must remain visible to preserve ECX.
void Rva00699180Owner::removeByKey(unsigned int key)
{
	for (int i = 0; i < 6; ++i)
	{
		unsigned char removed = 0;
		_STL::vector<Rva00699180Pair> &bucket = m_buckets[i];
		_STL::vector<Rva00699180Pair>::iterator it = bucket.begin();
		while (it != bucket.end())
		{
			if (it->m_key == key)
			{
				it = bucket.erase(it);
				removed = 1;
			}
			else
				++it;
		}
		if (removed)
		{
			((Rva00699430Owner *)this)->productClamp(i);
			for (int j = 0; j < 2; ++j)
				refreshPair(i, j);
		}
	}
}

// Retail 0x0069F3B0: for every (bucket, value) record of the source's
// +0x8C list, erase the first matching (value, key) entry from that bucket,
// then re-clamp the bucket's product and refresh its two output pairs (the
// removal counterpart of Rva006A8210Entry::applyEntryList).  Matched caller
// Rva0069F4D0ChannelNotify declares the receiver and name.
struct Rva0069F4D0Record
{
	int m_bucket;
	float m_value;
};

class Rva0069F4D0Block
{
public:
	void notify(void *source, int key);
};

void Rva0069F4D0Block::notify(void *source, int key)
{
	Rva00699180Owner *owner = (Rva00699180Owner *)this;
	const Rva0069F4D0Record *const *range =
		(const Rva0069F4D0Record *const *)(*(const int *)source + 0x8C);
	const Rva0069F4D0Record *it = range[0];
	const Rva0069F4D0Record *end = range[1];

	for (; it != end; ++it)
	{
		const int bucketIndex = it->m_bucket;
		if (bucketIndex != -1)
		{
			float value = it->m_value;
			_STL::vector<Rva00699180Pair>::iterator last = owner->m_buckets[bucketIndex].end();
			_STL::vector<Rva00699180Pair>::iterator found = owner->m_buckets[bucketIndex].begin();
			bool searching = true;
			while (searching && found != last)
			{
				if (found->m_value == value && found->m_key == (unsigned int)key)
				{
					owner->m_buckets[bucketIndex].erase(found);
					searching = false;
				}
				else
					++found;
			}

			((Rva00699430Owner *)this)->productClamp(bucketIndex);
			for (int i = 0; i < 2; ++i)
				owner->refreshPair(bucketIndex, i);
		}
	}
}

// Retail 0x00699150 (27 B): file-static test whether the record behind the holder has a
// +0x54 value not at or above the frame-time scale at 0x0111BB98. The holder arrives in EAX through
// the private static convention; the record type is address-named.
extern float g_bfmeElapsedScale;

struct Rva00699150Record
{
	unsigned char m_unmodelled00[0x54];
	float m_value54;
};

static int rva00699150(Rva00699150Record *const *holder)
{
	if ((*holder)->m_value54 >= g_bfmeElapsedScale)
		return 0;
	return 1;
}

// absent-from-retail: TU-local caller that keeps the static above alive.
int rva00699150Caller(Rva00699150Record *const *holder)
{
	return rva00699150(holder);
}
