// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

typedef bool Bool;
typedef unsigned char Byte;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	UnsignedInt m_data;
	const Overridable *m_next;
};

template<int BitCount>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	int count() const;
	UnsignedInt m_bits;
};

class ObjectIsMobileBody
{
public:
	Bool isMobile() const;

private:
	const Byte *finalTemplateData() const;

	Byte m_pad00[4];
	const Overridable *m_template;
	Byte m_pad08[0x94 - 0x08];
	UnsignedInt m_status;
	Byte m_pad98[0x1a4 - 0x98];
	BitFlags<13> m_disabledFlags;
};

// ?finalTemplateData@ObjectIsMobileBody@@ absent-from-retail
const Byte *ObjectIsMobileBody::finalTemplateData() const
{
	const Overridable *value = m_template;
	if (value != 0 && value->m_next != 0)
		value = value->m_next->getFinalOverride();
	return reinterpret_cast<const Byte *>(value);
}

Bool ObjectIsMobileBody::isMobile() const
{
	const Byte *templateData = finalTemplateData();
	if ((templateData[0xc8] & 4) != 0)
		return false;

	if (m_disabledFlags.m_bits != 0)
	{
		if ((m_disabledFlags.m_bits & 0x100) == 0)
			return false;

		BitFlags<13> flags = m_disabledFlags;
		if (flags.count() != 1)
			return false;
	}

	templateData = finalTemplateData();
	if ((*reinterpret_cast<const UnsignedInt *>(templateData + 0xd0) & 0x10000000) != 0
		&& (m_status & 0x04000000) != 0)
		return false;

	return true;
}
