class Rva002B6880Nested
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6();
};

class Rva002B6880Object
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14();
	virtual void v15( int value );

	void update( int value );

	unsigned char m_padding[0x18];
	Rva002B6880Nested *m_nested;
};

void Rva002B6880Object::update( int value )
{
	v15( value );
	m_nested->v6();
}
