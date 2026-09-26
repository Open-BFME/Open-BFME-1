// cl: /DNDEBUG /MD /EHsc
// BFME sold-state transitions.  The retail routines are the paired helpers at
// 0x001C8010 and 0x001C8080; both update the status bit, selection state, and
// the optional per-module sale interface.

typedef unsigned int UnsignedInt;

class ObjectStatusMaskType
{
public:
	void set( int bit )
	{
		m_bits[bit >> 5] |= 1 << (bit & 31);
	}

	void reset( int bit )
	{
		m_bits[bit >> 5] &= ~(1 << (bit & 31));
	}

private:
	UnsignedInt m_bits[3];
};

class Drawable
{
public:
	void friend_clearSelected();
	void friend_setSelected();
};

class BfmeObjectDrawableDispatch
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual Drawable *getDrawable();
};

class BfmeSaleInterface
{
public:
	virtual void sold();
	virtual void unsold();
};

class BfmeBehaviorInterface
{
public:
	virtual void anchor00();
	virtual void anchor04();
	virtual void anchor08();
	virtual void anchor0c();
	virtual void anchor10();
	virtual void anchor14();
	virtual void anchor18();
	virtual void anchor1c();
	virtual void anchor20();
	virtual void anchor24();
	virtual void anchor28();
	virtual void anchor2c();
	virtual void anchor30();
	virtual void anchor34();
	virtual void anchor38();
	virtual void anchor3c();
	virtual void anchor40();
	virtual void anchor44();
	virtual void anchor48();
	virtual void anchor4c();
	virtual void anchor50();
	virtual void anchor54();
	virtual void anchor58();
	virtual void anchor5c();
	virtual void anchor60();
	virtual void anchor64();
	virtual void anchor68();
	virtual void anchor6c();
	virtual void anchor70();
	virtual void anchor74();
	virtual void anchor78();
	virtual void anchor7c();
	virtual void anchor80();
	virtual void anchor84();
	virtual void anchor88();
	virtual BfmeSaleInterface *getSaleInterface();
};

class Gen001C8010
{
public:
	void setSold();

private:
	unsigned char m_pad00[0x94];
	ObjectStatusMaskType m_status;
	unsigned char m_pad98[0x150];
	char **m_behaviors;
	unsigned char m_pad1f4[0x14d];
	unsigned char m_modulesReady;
};

class Gen001C8080
{
public:
	void clearSold();

private:
	unsigned char m_pad00[0x94];
	ObjectStatusMaskType m_status;
	unsigned char m_pad98[0x150];
	char **m_behaviors;
	unsigned char m_pad1f4[0x14d];
	unsigned char m_modulesReady;
};

void Gen001C8010::setSold()
{
	m_status.set( 19 );

	Drawable *drawable = reinterpret_cast<BfmeObjectDrawableDispatch *>(this)->getDrawable();
	if( drawable )
		drawable->friend_clearSelected();

	if( m_modulesReady == 0 )
		return;

	char **module = m_behaviors;
	for( ; *module; ++module )
	{
		BfmeSaleInterface *sale = reinterpret_cast<BfmeBehaviorInterface *>(
			*module + 0x0c)->getSaleInterface();
		if( sale )
			sale->sold();
	}
}

void Gen001C8080::clearSold()
{
	m_status.reset( 19 );

	Drawable *drawable = reinterpret_cast<BfmeObjectDrawableDispatch *>(this)->getDrawable();
	if( drawable )
		drawable->friend_setSelected();

	if( m_modulesReady == 0 )
		return;

	char **module = m_behaviors;
	for( ; *module; ++module )
	{
		BfmeSaleInterface *sale = reinterpret_cast<BfmeBehaviorInterface *>(
			*module + 0x0c)->getSaleInterface();
		if( sale )
			sale->unsold();
	}
}
