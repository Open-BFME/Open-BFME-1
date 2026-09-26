// cl: /DNDEBUG /MD
// Retail RVA 0x001B49E0. Copies a three-float position into three fields that
// sit sixteen bytes apart at +0x70, +0x80 and +0x90, which is the translation
// column of a row-major transform based at +0x64. Nothing names the owner, so
// the class keeps an address-derived name.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Rva001B49E0Owner
{
public:
	void setPosition( const Coord3D *position );

	unsigned char m_bfmePad000[ 0x70 ];
	float m_bfmeRow0;
	unsigned char m_bfmePad074[ 0x0c ];
	float m_bfmeRow1;
	unsigned char m_bfmePad084[ 0x0c ];
	float m_bfmeRow2;
};

void Rva001B49E0Owner::setPosition( const Coord3D *position )
{
	Coord3D local;

	local.x = position->x;
	local.y = position->y;
	local.z = position->z;

	m_bfmeRow0 = local.x;
	m_bfmeRow1 = local.y;
	m_bfmeRow2 = local.z;
}
