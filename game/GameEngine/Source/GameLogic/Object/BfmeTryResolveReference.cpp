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

class Object;
struct Coord3D;
void doSetRallyPoint(Object *object, const Coord3D &location);
// The retail ILT resolves to the matched doSetRallyPoint object symbol, while
// this call site uses four cdecl slots and consumes EAX.
typedef BfmeBool (__cdecl *BfmeTryResolveReferenceCall)(BfmeReferenceOwner *owner,
	BfmeReferenceResolveState *state, int firstOption, int secondOption);

Bool bfmeResolveReferenceIfEnabled(BfmeReferenceOwner *owner,
		BfmeReferenceResolveState *state)
{
	BfmeOverridable *value = owner->m_value;
	if (value != 0 && value->m_next != 0)
		value = value->m_next->friend_getFinalOverride();

	if ((value->m_flags & 0x10) == 0)
		goto done;
	if (reinterpret_cast<BfmeTryResolveReferenceCall>(&doSetRallyPoint)(owner, state, 0, 0))
		++state->m_resolvedCount;
done:
	return true;
}
