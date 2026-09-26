// ?assign@Rva00958960Holder@@QAEPAU1@PAURva00958960Ref@@@Z
struct Rva00958960Ref;
struct Rva00958960RefVt {
	void* m_0;
	void (__stdcall* addRef)(Rva00958960Ref* self);
	void (__stdcall* release)(Rva00958960Ref* self);
};
struct Rva00958960Ref { Rva00958960RefVt* m_vt; };
struct Rva00958960Holder {
	Rva00958960Ref* m_ref;
	Rva00958960Holder* assign(Rva00958960Ref* ref);
};
Rva00958960Holder* Rva00958960Holder::assign(Rva00958960Ref* ref)
{
	Rva00958960Ref* old = m_ref;
	if (old != ref) {
		m_ref = ref;
		if (ref)
			ref->m_vt->addRef(ref);
		if (old)
			old->m_vt->release(old);
	}
	return this;
}
