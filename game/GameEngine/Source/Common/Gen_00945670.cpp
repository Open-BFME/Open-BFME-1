// Clean reconstruction of the fallback comparison at retail RVA 0x00945670.
// The owning type's identity is not recovered.  The 25th virtual slot and
// the field at +0x2F8 are the layout facts required by the retail body.

extern float g_bfmeDefaultBR; // retail 0x01075350

class Gen_00945670
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual float value();

	float process();

private:
	unsigned char m_pad[0x2F8 - 4];
	float m_fallback;
};

float Gen_00945670::process()
{
	if (value() > g_bfmeDefaultBR)
		return value();
	return m_fallback;
}
