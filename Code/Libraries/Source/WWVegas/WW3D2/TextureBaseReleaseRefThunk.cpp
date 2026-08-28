// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureBaseClass
{
public:
	void Release_Ref();
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void Delete_This();

private:
	unsigned int m_refBits;
};

// ?Release_Ref@TextureBaseClass@@QAEXXZ
void TextureBaseClass::Release_Ref()
{
	if ((m_refBits & 0xffff) == 0)
		return;
	*reinterpret_cast<unsigned short *>(&m_refBits) =
		static_cast<unsigned short>(*reinterpret_cast<unsigned short *>(&m_refBits) - 1);
	if ((m_refBits & 0xffff) != 0)
		return;
	if ((m_refBits & 0x1000000) == 0)
		return;
	Delete_This();
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureClass
{
public:
	void Release_Ref();
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void Delete_This();

private:
	unsigned int m_refBits;
};

// ?Release_Ref@TextureClass@@QAEXXZ
void TextureClass::Release_Ref()
{
	if ((m_refBits & 0xffff) == 0)
		return;
	*reinterpret_cast<unsigned short *>(&m_refBits) =
		static_cast<unsigned short>(*reinterpret_cast<unsigned short *>(&m_refBits) - 1);
	if ((m_refBits & 0xffff) != 0)
		return;
	if ((m_refBits & 0x1000000) == 0)
		return;
	Delete_This();
}
