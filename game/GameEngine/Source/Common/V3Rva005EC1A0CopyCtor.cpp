// cl: /EHs-c-

class V3HeadBase
{
public:
	virtual void slot0();
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
};

class V3Base14
{
public:
	virtual void slot0();
};

class V3Base18
{
public:
	virtual void slot0();
};

class Rva005EC230 : public V3HeadBase, public V3Base14, public V3Base18
{
public:
	Rva005EC230(const Rva005EC230 &other);
};

class V3InlineTail
{
public:
	virtual void slot0();
	unsigned char m_data[0x80];
};

class V3Mid : public Rva005EC230
{
public:
	V3Mid(const V3Mid &other) : Rva005EC230(other) {}
};

class Rva005EC1A0 : public V3Mid, public V3InlineTail
{
public:
	Rva005EC1A0(const Rva005EC1A0 &other);
};

Rva005EC1A0::Rva005EC1A0(const Rva005EC1A0 &other)
	: V3Mid(other)
	, V3InlineTail(other)
{
}
