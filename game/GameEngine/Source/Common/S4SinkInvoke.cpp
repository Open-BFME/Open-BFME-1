// ?invoke@S4Sink004135C0@@QAEXABVAsciiString@@HHHH@Z
// cl: /DNDEBUG /MD /EHsc

class AsciiString;
class S4Sub004135C0;

class S4Sub004135C0
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void invoke( const AsciiString &, int, int, int, int );
};

class S4Item004135C0
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual S4Sub004135C0 *getSub();
};

class S4Sink004135C0
{
public:
	void invoke( const AsciiString &name, int a, int b, int c, int d );

private:
	char m_padding[0x150];
	S4Item004135C0 **m_items;
};

void S4Sink004135C0::invoke( const AsciiString &name, int a, int b, int c, int d )
{
	const volatile int &localA = a;
	const volatile int &localB = b;
	for(S4Item004135C0 **item = m_items; *item; ++item)
	{
		S4Sub004135C0 *sub = (*item)->getSub();
		if(sub)
			sub->invoke(name, localA, localB, c, d);
	}
}

