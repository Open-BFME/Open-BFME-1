// Open-BFME: retail 0x0015A790 rebuilds the ten cost buckets owned by the
// same BFME object as computeSize at 0x0015AAC0.

typedef int Int;

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	unsigned char m_pad00[4];
	Overridable *m_nextOverride;
	unsigned char m_pad08[0x74 - 0x08];
	Int m_kindOrType;
	unsigned char m_pad78[0x440 - 0x78];
	Int m_value440;
};

class Rva0015A790Locomotor
{
public:
	unsigned char m_pad00[4];
	Overridable *m_template;
};

class Rva0015A790AIUpdate
{
public:
	unsigned char m_pad00[0x1CC];
	Rva0015A790Locomotor *m_currentLocomotor;
};

class Rva0015A790Object
{
public:
	unsigned char m_pad00[4];
	Overridable *m_template;
	unsigned char m_pad08[0x204 - 0x08];
	Rva0015A790AIUpdate *m_ai;
};

struct Rva0015A790Bucket
{
	Int m_count;
	Rva0015A790Object *m_items[6];
};

class Rva0015AAC0Owner
{
public:
	void rebuildBuckets();

	Int m_count;
	Int m_bucketCapacity;
	Rva0015A790Bucket m_buckets[10];
	Int m_candidateCount;
	Rva0015A790Object *m_candidates[1];
	unsigned char m_pad128[0x1B4 - 0x128];
	Int m_maxValue;
	unsigned char m_ready;
};

// ?rebuildBuckets@Rva0015AAC0Owner@@QAEXXZ
void Rva0015AAC0Owner::rebuildBuckets()
{
	m_maxValue = 0;
	Int bucketValue = 0;
	Int bucketIndex = 0;
	if (m_count > 0)
	{
		Rva0015A790Bucket *bucket = m_buckets;
		do
		{
			bucket->m_count = 0;
			++bucketIndex;
			bucket = (Rva0015A790Bucket *)((char *)bucket + 0x1C);
		}
		while (bucketIndex < m_count);
	}

	m_count = 0;
	Int pass = 0;
	do
	{
		if (m_count >= 10)
			break;

		Int candidateCount = m_candidateCount;
		Int candidateIndex = 0;
		if (candidateCount > 0)
		{
			Rva0015A790Object **candidate = m_candidates;
			do
			{
				Rva0015A790Object *object = *candidate;
				Rva0015A790AIUpdate *ai = object->m_ai;
				if (ai)
				{
					Rva0015A790Locomotor *locomotor = ai->m_currentLocomotor;
					if (locomotor)
					{
						Overridable *locomotorTemplate = locomotor->m_template;
						if (locomotorTemplate && locomotorTemplate->m_nextOverride)
							locomotorTemplate = (Overridable *)locomotorTemplate->m_nextOverride->getFinalOverride();

						if (locomotorTemplate->m_kindOrType == pass)
						{
							Overridable *objectTemplate = object->m_template;
							if (objectTemplate && objectTemplate->m_nextOverride)
								objectTemplate = (Overridable *)objectTemplate->m_nextOverride->getFinalOverride();

							bucketValue += objectTemplate->m_value440;
							if (bucketValue > m_bucketCapacity)
							{
								if (++m_count >= 10)
									break;

								objectTemplate = object->m_template;
								if (objectTemplate && objectTemplate->m_nextOverride)
									objectTemplate = (Overridable *)objectTemplate->m_nextOverride->getFinalOverride();
								bucketValue = objectTemplate->m_value440;
							}

							Rva0015A790Bucket *bucket =
								&m_buckets[m_count];
							if (bucket->m_count < 6)
								bucket->m_items[bucket->m_count++] = object;
							if (m_maxValue < bucketValue)
								m_maxValue = bucketValue;
						}
					}
				}
				++candidateIndex;
				++candidate;
			}
			while (candidateIndex < m_candidateCount);
		}

		if (pass == 3 || pass == 6 || pass == 0 || pass == 9 || pass == 12)
		{
			if (bucketValue > 0)
				++m_count;
			bucketValue = 0;
		}
		++pass;
	}
	while (pass < 13);

	m_ready = 1;
}
