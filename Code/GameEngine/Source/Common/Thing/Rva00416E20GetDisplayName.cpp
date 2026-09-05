// cl: /DNDEBUG /MD /EHsc
//
// 202B twin of ?getDisplayName@ThingTemplate@@QBEDAAVUnicodeString@@@Z
// (ThingTemplateGetDisplayName.cpp, retail 0x00416D20): byte-identical
// fetch-and-format shape, only the label member sits 4 bytes further into
// the object (+0x2D8 instead of +0x2D4). Address-derived class/name pending
// the real owning type -- likely a ThingTemplate sibling with one extra
// preceding field.

typedef char Bool;
typedef unsigned short WideChar;

template <typename T> class StringBase
{
friend class AsciiString;
friend class UnicodeString;

private:
	struct Data
	{
		int refs;
		unsigned short length;
		unsigned short capacity;
		T text[1];
	};

	Data *m_data;

	StringBase(const StringBase<T> &that);

public:
	void set(const StringBase<T> &that);

private:
	void releaseBuffer();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() { m_data = 0; }
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}
	AsciiString &operator=(const AsciiString &that)
	{
		((StringBase<char> *)this)->set(*(const StringBase<char> *)&that);
		return *this;
	}

	Bool isNotEmpty() const
	{
		const StringBase<char>::Data *data =
			((const StringBase<char> *)this)->m_data;
		return data != 0 && data->length != 0;
	}

private:
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString() { m_data = 0; }
	UnicodeString(const UnicodeString &that)
	{
		((StringBase<WideChar> *)this)->StringBase<WideChar>::StringBase(
			*(const StringBase<WideChar> *)&that);
	}
	~UnicodeString()
	{
		((StringBase<WideChar> *)this)->releaseBuffer();
	}

	UnicodeString &operator=(const UnicodeString &that)
	{
		((StringBase<WideChar> *)this)->set(
			*(const StringBase<WideChar> *)&that);
		return *this;
	}

private:
	WideChar *m_data;
};

class GameTextInterface
{
public:
	virtual void vfn00();
	virtual void vfn01();
	virtual void vfn02();
	virtual void vfn03();
	virtual void vfn04();
	virtual void vfn05();
	virtual void vfn06();
	virtual void vfn07();
	virtual void vfn08();
	virtual UnicodeString fetch(AsciiString label, Bool *exists = 0);
};

extern GameTextInterface *TheGameText;

class Rva00416E20Owner
{
public:
	Bool getDisplayName(UnicodeString &name) const;

private:
	unsigned char m_bfmeBeforeDisplayName[0x2d8];
	AsciiString m_displayNameLabel;
};

Bool Rva00416E20Owner::getDisplayName(UnicodeString &name) const
{
	AsciiString label;
	if (m_displayNameLabel.isNotEmpty())
	{
		label = m_displayNameLabel;
		name = TheGameText->fetch(label);
		return true;
	}

	return false;
}
