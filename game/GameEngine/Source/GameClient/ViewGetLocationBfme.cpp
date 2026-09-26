// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME View::getLocation, retail RVA 0x0045B5E0.
// The base View vtable at 0x010F6940 routes slot 91 through thunk 0x00445E80.

class ViewLocation
{
public:
	bool m_valid;
	char m_pad01[3];
	float m_pos[3];
	float m_angle;
	float m_pitch;
	float m_zoom;
	float m_heightAboveGround;

	void init( float x, float y, float z, float angle, float pitch, float zoom,
		float heightAboveGround )
	{
		m_pos[0] = x;
		m_pos[1] = y;
		m_pos[2] = z;
		m_angle = angle;
		m_pitch = pitch;
		m_zoom = zoom;
		m_heightAboveGround = heightAboveGround;
		m_valid = true;
	}
};

class View
{
public:
	#define VIEW_SLOT(n) virtual void slot##n();
	VIEW_SLOT(00) VIEW_SLOT(04) VIEW_SLOT(08) VIEW_SLOT(0C)
	VIEW_SLOT(10) VIEW_SLOT(14) VIEW_SLOT(18) VIEW_SLOT(1C)
	VIEW_SLOT(20) VIEW_SLOT(24) VIEW_SLOT(28) VIEW_SLOT(2C)
	VIEW_SLOT(30) VIEW_SLOT(34) VIEW_SLOT(38) VIEW_SLOT(3C)
	VIEW_SLOT(40) VIEW_SLOT(44) VIEW_SLOT(48) VIEW_SLOT(4C)
	VIEW_SLOT(50) VIEW_SLOT(54) VIEW_SLOT(58) VIEW_SLOT(5C)
	VIEW_SLOT(60) VIEW_SLOT(64) VIEW_SLOT(68) VIEW_SLOT(6C)
	VIEW_SLOT(70) VIEW_SLOT(74) VIEW_SLOT(78) VIEW_SLOT(7C)
	VIEW_SLOT(80) VIEW_SLOT(84) VIEW_SLOT(88) VIEW_SLOT(8C)
	VIEW_SLOT(90) VIEW_SLOT(94) VIEW_SLOT(98) VIEW_SLOT(9C)
	VIEW_SLOT(A0) VIEW_SLOT(A4) VIEW_SLOT(A8) VIEW_SLOT(AC)
	VIEW_SLOT(B0) VIEW_SLOT(B4) VIEW_SLOT(B8) VIEW_SLOT(BC)
	VIEW_SLOT(C0) VIEW_SLOT(C4) VIEW_SLOT(C8) VIEW_SLOT(CC)
	VIEW_SLOT(D0) VIEW_SLOT(D4) VIEW_SLOT(D8) VIEW_SLOT(DC)
	VIEW_SLOT(E0) VIEW_SLOT(E4) VIEW_SLOT(E8) VIEW_SLOT(EC)
	VIEW_SLOT(F0) VIEW_SLOT(F4) VIEW_SLOT(F8)
	virtual float getAngle();
	virtual void slot100();
	virtual float getPitch();
	virtual void slot108();
	virtual float getHeightAboveGround();
	virtual void slot110(); virtual void slot114(); virtual void slot118(); virtual void slot11C();
	virtual float getZoom();
	VIEW_SLOT(124) VIEW_SLOT(128) VIEW_SLOT(12C) VIEW_SLOT(130)
	VIEW_SLOT(134) VIEW_SLOT(138) VIEW_SLOT(13C) VIEW_SLOT(140)
	VIEW_SLOT(144) VIEW_SLOT(148) VIEW_SLOT(14C) VIEW_SLOT(150)
	VIEW_SLOT(154) VIEW_SLOT(158) VIEW_SLOT(15C) VIEW_SLOT(160)
	VIEW_SLOT(164) VIEW_SLOT(168)
	virtual void getLocation( ViewLocation *location );
	#undef VIEW_SLOT

	void *m_next;
	unsigned int m_id;
	float m_pos[3];
};

void View::getLocation( ViewLocation *location )
{
	location->init( m_pos[0], m_pos[1], m_pos[2], getAngle(), getPitch(), getZoom(),
		getHeightAboveGround() );
}
