// cl: /DNDEBUG /MD /EHsc

typedef int Bool;
typedef bool BfmeBool;

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride();

	unsigned char m_head[4];
	BfmeOverridable *m_next;
	unsigned char m_pad[0xC8];
	unsigned int m_flags;
};

struct BfmeReferenceOwner
{
	unsigned char m_pad[4];
	BfmeOverridable *m_value;
};

struct BfmeReferenceResolveState
{
	unsigned char m_pad[0x0C];
	int m_resolvedCount;
};

extern BfmeBool bfmeTryResolveReference(BfmeReferenceOwner *owner,
	BfmeReferenceResolveState *state, int firstOption, int secondOption);

Bool bfmeResolveReferenceIfEnabled(BfmeReferenceOwner *owner,
		BfmeReferenceResolveState *state)
{
	BfmeOverridable *value = owner->m_value;
	if (value != 0 && value->m_next != 0)
		value = value->m_next->friend_getFinalOverride();

	if ((value->m_flags & 0x10) == 0)
		goto done;
	if (bfmeTryResolveReference(owner, state, 0, 0))
		++state->m_resolvedCount;
done:
	return true;
}
