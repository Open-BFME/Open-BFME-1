// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva008A0E00Owner
{
public:
	int remove(void *key);

	int m_count;
	void *m_entries[0x200];
};

class Rva008A1460Releasable
{
public:
	virtual void slot0();
	virtual void release();
};

struct Rva008A1460Bucket
{
	void *m_owner;
	Rva008A1460Releasable *m_value;
	char m_padding[0x0c];
	int m_count;
	char m_padding2[0x04];
	Rva008A1460Releasable **m_values;
};

struct Rva008A1460Tail
{
	void *m_value;
	Rva008A1460Bucket *m_buckets;
	int m_count;
};

struct Rva008A1460VectorEntry
{
	Rva008A1460Releasable *m_value;
	char m_padding[0x18];
};

class BfmeD1046
{
public:
	void bfmeGo1046D(void);
};

extern char *Rva008A5380Holder;

class Rva008A1460Owner
{
public:
	void cleanup(void);

private:
	char m_padding[0x14];
	Rva008A0E00Owner m_owner;
	int m_vectorCount;
	Rva008A1460VectorEntry *m_vector;
	int m_vectorUnused;
	Rva008A1460Releasable *m_values[0x40];
	int m_valuesGap;
	Rva008A1460Releasable *m_moreValues[0x40];
	char m_padding2[0x804];
	Rva008A1460Tail m_tail;
};

void Rva008A1460Owner::cleanup(void)
{
	register Rva008A1460Owner *owner = this;
	int counts[2];
	counts[0] = owner->m_owner.m_count;
	register int index = 0;
	int bucketOffset = 0;
	for (; index < 0x200; ++index)
	{
		if (owner->m_owner.m_entries[index] != 0)
		{
			owner->m_owner.remove(owner->m_owner.m_entries[index]);
			--counts[0];
			if (counts[0] == 0)
				break;
		}
	}

	bucketOffset = 0;
	counts[1] = 0;
	for (; counts[1] < reinterpret_cast<int *>(Rva008A5380Holder)[0x12a4 / 4];
		++counts[1], bucketOffset += 0x20)
	{
		if (reinterpret_cast<Rva008A1460Bucket *>(
			reinterpret_cast<char *>(owner->m_tail.m_buckets) + bucketOffset)->m_owner != 0)
		{
			reinterpret_cast<Rva008A1460Bucket *>(
				reinterpret_cast<char *>(owner->m_tail.m_buckets) + bucketOffset)->m_value->release();
			counts[0] = 0;
			for (; counts[0] < reinterpret_cast<Rva008A1460Bucket *>(
					reinterpret_cast<char *>(owner->m_tail.m_buckets) + bucketOffset)->m_count; ++counts[0])
			{
				Rva008A1460Bucket *bucket = reinterpret_cast<Rva008A1460Bucket *>(
					reinterpret_cast<char *>(owner->m_tail.m_buckets) + bucketOffset);
				int remaining = bucket->m_count;
				if (remaining > 0)
				{
					for (; remaining > 0; --remaining)
					{
						bucket->m_values[bucket->m_count - 1]->release();
						--bucket->m_count;
					}
				}
			}
			reinterpret_cast<Rva008A1460Bucket *>(
				reinterpret_cast<char *>(owner->m_tail.m_buckets) + bucketOffset)->m_owner = 0;
			--owner->m_tail.m_count;
		}
	}

	for (index = 0; index < 0x40; ++index)
	{
		if (owner->m_values[index] != 0)
		{
			owner->m_values[index]->release();
			owner->m_values[index] = 0;
		}
	}
	for (index = 0; index < 0x40; ++index)
	{
		if (owner->m_moreValues[index] != 0)
		{
			owner->m_moreValues[index]->release();
			owner->m_moreValues[index] = 0;
		}
	}

	for (index = 0; index < owner->m_vectorCount; ++index)
		owner->m_vector[index].m_value->release();
	owner->m_vectorCount = 0;

	reinterpret_cast<BfmeD1046 *>(&owner->m_tail)->bfmeGo1046D();
}
