// ?usePluralShadowName@BfmeThingTemplateShadowSelector@@QBE_NXZ
// cl: /O2 /DNDEBUG /DWIN32 /MD /EHsc
//
// BfmeThingTemplateShadowSelector::usePluralShadowName, retail 0x0087E8D0
// (36 bytes of a 47-byte body; the tail falls through into the already
// matched ?dup_0087e8f4@@YAXXZ alias of W3DTerrainBackground::isCulled,
// reused here by identical-code folding for the single-element check).
//
// The selector sits at ThingTemplate+0x60 and its begin/end pointers walk a
// vector of 36-byte shadow-layer entries; the retail predicate is true only
// when the vector holds exactly one entry whose first field equals 2.

typedef int Int;
typedef bool Bool;

class BfmeThingTemplateShadowSelector
{
public:
	Bool usePluralShadowName() const;

private:
	char m_pad[ 0x2c ];
	const char * volatile m_begin;
	const char *m_end;
};

Bool BfmeThingTemplateShadowSelector::usePluralShadowName() const
{
	Int count = (Int)(m_end - m_begin) / 36;
	if (count != 1)
		return false;
	return *(const Int *)m_begin == 2;
}
