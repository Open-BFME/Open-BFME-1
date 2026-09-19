// ?setTextureSlot@Rva00933490Owner@@QAEXABQAVTextureClass@@H@Z
// Address-derived REF_PTR_SET-style texture slot setter: Add_Ref (inline
// word++ at ref-count offset+4) on the incoming texture, Release_Ref the
// outgoing slot occupant through the already-named TextureClass method, then
// store the new pointer. The array of slots is embedded at this+8, indexed
// by the second argument; the first argument is a const reference to a
// pointer (address-passed), which is why retail dereferences it repeatedly
// instead of caching the value across the Release_Ref call.
class TextureClass
{
public:
	void Release_Ref(void);
	char m_pad0[4];
	unsigned short m_refCount;
};

class Rva00933490Owner
{
public:
	char m_pad0[8];
	void setTextureSlot(TextureClass* const& newTex, int index);
};

void Rva00933490Owner::setTextureSlot(TextureClass* const& newTex, int index)
{
	TextureClass** slot = (TextureClass**)((char*)this + 8) + index;
	if (newTex)
		++newTex->m_refCount;

	if (*slot)
	{
		(*slot)->Release_Ref();
		*slot = newTex;
	}
	else
	{
		*slot = newTex;
	}
}
