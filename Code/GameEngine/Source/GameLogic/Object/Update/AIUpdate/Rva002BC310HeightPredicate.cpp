// cl: /DNDEBUG /MD
//
// Address-derived recovery for the BFME height predicate at retail RVA
// 0x002BC310.  Its sole direct call is Thing::getHeightAboveTerrain; the
// surrounding owner and data offsets are the retail layout evidence.

class Thing
{
public:
	unsigned char m_unreconstructed000[ 0x40 ];
	float m_heightLimit40;

	float getHeightAboveTerrain() const;
};

class Rva002BC310Data
{
public:
	unsigned char m_unreconstructed000[ 0x44 ];
	float m_height44;
};

class Rva002BC310Owner
{
public:
	unsigned char checkHeight();

private:
	unsigned char m_unreconstructed000[ 8 ];
	Thing *m_thing;
	unsigned char m_unreconstructed00c[ 0x1c0 ];
	Rva002BC310Data *m_data;
};

extern float g_Rva01095F98;

// ?checkHeight@Rva002BC310Owner@@QAEEXZ
unsigned char Rva002BC310Owner::checkHeight()
{
	Thing *thing = m_thing;
	Rva002BC310Data *data = m_data;
	if (thing != 0 && data != 0)
	{
		float threshold = data->m_height44 + data->m_height44;
		float height = thing->getHeightAboveTerrain();
		unsigned char result = height > threshold;
		volatile float *heightField = &data->m_height44;
		int second = thing->m_heightLimit40 > threshold
			? (int)(height > *heightField * g_Rva01095F98)
			: 0;
		second |= result;
		return (unsigned char)second;
	}
	return 0;
}
