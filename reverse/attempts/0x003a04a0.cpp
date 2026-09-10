// ?accepts@Rva2225E0Filter@@QAE_NPAVObject@@PAVPlayer@@@Z
// partial score=0.97 date=2026-09-10
// cl: /O2 /EHs-c-
// Open-BFME: Rva2225E0Filter::accepts at retail 0x003A04A0.
// The filtered-count callers and the existing ILT pin establish this private
// predicate's Object/Player ABI; the source is kept in a dedicated TU so the
// small override walk retains its retail frame.

typedef bool Bool;

class Player;

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride(void);

	char m_bfmeHead[0x04];
	BfmeOverridable *m_bfmeNextOverride;
};

class BfmeFilterObject
{
public:
	Bool bfmeQuery(Player *player);

	char m_bfmeHead[0x04];
	BfmeOverridable *m_bfmeOverride;
};

class Object : public BfmeFilterObject
{
};

class Rva2225E0Filter
{
public:
	Bool accepts(Object *object, Player *player);

private:
	Bool bfmeTest(BfmeOverridable *override, Bool queried);
};

// ?accepts@Rva2225E0Filter@@QAE_NPAVObject@@PAVPlayer@@@Z
Bool Rva2225E0Filter::accepts(Object *object, Player *player)
{
	if (!object)
		return false;

	BfmeOverridable *override = object->m_bfmeOverride;
	BfmeOverridable *walked;

	if (override == 0)
		walked = 0;
	else if (override->m_bfmeNextOverride)
		walked = override->m_bfmeNextOverride->friend_getFinalOverride();
	else
		walked = override;

	return bfmeTest(walked, object->bfmeQuery(player));
}
