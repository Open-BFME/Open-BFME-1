// ?rva00765DC0@W3DModelDrawModuleData@@QBEPBUModelConditionInfo@@ABV?$BitFlags@$0HF@@@@Z
// cl: /O2 /DNDEBUG /MD
// Second condition-state lookup of BFME's W3DModelDrawModuleData, retail 0x00765DC0 (384 bytes).
// Identity: ILT 0x0000CE5F jumps here and the matched getPristineBonePositionsForConditionState
// (0x00775760) calls it through that thunk as a one-argument const method that returns a state.
// The body walks the condition-state vector at +0x24/+0x28 (0xBC-byte records, mask at +4) and
// keeps the first record whose non-empty mask is covered by the argument, else the first record
// with an empty mask. The mask is ten dwords wide. The template argument 117 only keeps the
// mangled name the caller files already use for the argument type.
template <int N>
class BitFlags
{
public:
	unsigned int value[10];
};

typedef BitFlags<117> ModelConditionFlags;

struct ModelConditionInfo
{
	unsigned char m_unmodelled00[4];
	ModelConditionFlags m_conditionsYes;
	unsigned char m_unmodelled2C[0xBC - 0x2C];
};

class W3DModelDrawModuleData
{
public:
	const ModelConditionInfo *rva00765DC0(const ModelConditionFlags &c) const;

private:
	ModelConditionInfo *begin() const { return m_begin; }
	ModelConditionInfo *end() const { return m_end; }

	unsigned char m_unmodelled00[0x24];
	ModelConditionInfo *m_begin;
	ModelConditionInfo *m_end;
};

static bool isEmpty(const ModelConditionFlags &f)
{
	for (unsigned i = 0; i < 10; ++i)
		if (f.value[i] != 0)
			return false;
	return true;
}

const ModelConditionInfo *W3DModelDrawModuleData::rva00765DC0(const ModelConditionFlags &c) const
{
	ModelConditionFlags bits = c;
	for (ModelConditionInfo *it = begin(); it != end(); ++it)
	{
		ModelConditionFlags mask = it->m_conditionsYes;
		if (isEmpty(mask))
			continue;
		for (unsigned i = 0; i < 10; ++i)
			mask.value[i] &= bits.value[i];
		unsigned j = 0;
		do
		{
			if (mask.value[j] != it->m_conditionsYes.value[j])
				goto next;
			++j;
		} while (j < 10);
		return it;
	next:;
	}
	for (ModelConditionInfo *it = begin(); it != end(); ++it)
	{
		bits = it->m_conditionsYes;
		if (isEmpty(bits))
			return it;
	}
	return 0;
}
