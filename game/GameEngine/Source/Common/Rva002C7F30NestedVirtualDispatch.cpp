class Rva002C7F30Nested
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6();
};

class Rva002C7F30Object
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14();
	virtual void v15( int value );

	void dispatch( int value );

	unsigned char m_padding[0xDC];
	Rva002C7F30Nested *m_nested;
};

void Rva002C7F30Object::dispatch( int value )
{
	v15( value );
	m_nested->v6();
}
