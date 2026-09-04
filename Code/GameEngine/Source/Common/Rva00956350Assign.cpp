// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00956350 is the assignment body for a RenderObj-derived BFME
// object.  The unnamed outer type is retained as an RVA-derived name until a
// caller or vtable identity establishes its original class name.

class RenderObjClass
{
public:
	RenderObjClass &operator=(const RenderObjClass &that);
	char m_base[0xCC];
};

class BfmeTexVGX
{
public:
	void bfmeReleaseVGX();
	int m_bfme00;
	unsigned short m_bfmeRefs;
};

class BfmeThingVGX
{
public:
	BfmeThingVGX &bfmeAssignVGX(const BfmeThingVGX &that);
	BfmeTexVGX *m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	int m_bfme18;
	int m_bfme1c;
	char m_bfme20;
};

class Rva00956350Object : public RenderObjClass
{
public:
	Rva00956350Object &operator=(const Rva00956350Object &that);

	int m_cc;
	int m_d0;
	int m_d4;
	int m_d8;
	int m_dc;
	int m_e0;
	int m_e4;
	BfmeThingVGX m_vgx;
};

Rva00956350Object &Rva00956350Object::operator=(const Rva00956350Object &that)
{
	RenderObjClass::operator=(that);
	if (this != &that)
	{
		m_cc = that.m_cc;
		m_d0 = that.m_d0;
		m_d4 = that.m_d4;
		m_dc = that.m_dc;
		m_e0 = that.m_e0;
		m_e4 = that.m_e4;
		m_vgx.bfmeAssignVGX(that.m_vgx);
	}
	return *this;
}
