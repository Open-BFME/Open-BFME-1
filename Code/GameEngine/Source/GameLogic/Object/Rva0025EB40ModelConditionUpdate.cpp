class Rva0025EB40Drawable
{
private:
	char m_pad[ 0x114 ];

public:
	unsigned int m_conditionFlags;
};

class Object
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual Rva0025EB40Drawable *getDrawable();
	void notifyModelConditionChanged();

private:
	char m_pad[ 0x124 ];

public:
	union
	{
		unsigned int m_conditionFlags;
		unsigned char m_conditionFlagByte;
	};
};

class Rva0025EB40State
{
public:
	void prepare();
};

class Rva0025EB40ModelConditionUpdate
{
public:
	void update();

private:
	char m_pad[ 8 ];
	Object *m_object;
};

void Rva0025EB40ModelConditionUpdate::update()
{
	( (Rva0025EB40State *)this )->prepare();

	Object *object = m_object;
	if( ( object->m_conditionFlagByte & 0x10 ) == 0 )
	{
		object->m_conditionFlags |= 0x10;
		object->notifyModelConditionChanged();
	}

	Rva0025EB40Drawable *drawable = m_object->getDrawable();
	if( drawable )
		drawable->m_conditionFlags |= 0x10;
}
