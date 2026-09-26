// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc
// BFME retail 0x001B5630: Locomotor state copy assignment.

struct BfmeLocomotorCoord3D
{
	float x;
	float y;
	float z;
};

class Locomotor
{
public:
	virtual void slot();

	protected:
	Locomotor &operator=(const Locomotor &that);

	void *m_template;
	BfmeLocomotorCoord3D m_maintainPos;
	BfmeLocomotorCoord3D m_position;
	unsigned int m_field20;
	unsigned int m_field24;
	unsigned int m_field28;
	unsigned int m_field2c;
	unsigned int m_field30;
	unsigned int m_field34;
	unsigned int m_field38;
	unsigned int m_field3c;
	unsigned int m_field40;
	unsigned int m_field44;
	unsigned int m_field48;
	unsigned int m_field4c;
	unsigned int m_field50;
	unsigned int m_field54;
	unsigned int m_field58;
	unsigned int m_field5c;
	unsigned int m_field60;
	unsigned int m_field64;
	unsigned int m_field68;
	unsigned int m_field6c;
	unsigned int m_field70;
	unsigned int m_field74;
	unsigned int m_field78;
	unsigned int m_field7c;
	unsigned int m_field80;
	unsigned int m_field84;
	unsigned int m_field88;
	unsigned int m_field8c;
	unsigned int m_field90;
	unsigned char m_field94;
	unsigned char m_field95;
	unsigned short m_field96;
	unsigned int m_field98;
	unsigned int m_field9c;
	unsigned int m_fielda0;

};

Locomotor &Locomotor::operator=(const Locomotor &that)
{
	if (this != &that)
	{
		m_template = that.m_template;
		m_maintainPos = that.m_maintainPos;
		m_position = that.m_position;
		m_field20 = that.m_field20;
		m_field24 = that.m_field24;
		m_field28 = that.m_field28;
		m_field2c = that.m_field2c;
		m_field30 = that.m_field30;
		m_field34 = that.m_field34;
		m_field38 = that.m_field38;
		m_field3c = that.m_field3c;
		m_field40 = that.m_field40;
		m_field44 = that.m_field44;
		m_field48 = that.m_field48;
		m_field4c = that.m_field4c;
		m_field50 = that.m_field50;
		m_field54 = that.m_field54;
		m_field58 = that.m_field58;
		m_field5c = that.m_field5c;
		m_field60 = that.m_field60;
		m_field64 = that.m_field64;
		m_field68 = that.m_field68;
		m_field6c = that.m_field6c;
		m_field70 = that.m_field70;
		m_field74 = that.m_field74;
		m_field78 = that.m_field78;
		m_field7c = that.m_field7c;
		m_field80 = that.m_field80;
		m_field84 = that.m_field84;
		m_field88 = that.m_field88;
		m_field8c = that.m_field8c;
		m_field90 = that.m_field90;
		m_field94 = that.m_field94;
		m_field95 = that.m_field95;
		m_field98 = that.m_field98;
		m_field9c = that.m_field9c;
		m_fielda0 = that.m_fielda0;
	}
	return *this;
}
