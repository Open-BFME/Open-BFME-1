// ?rva007418B0@W3DView@@UAEXPBUCoord3D@@PAVRva007418B0Path@@HHHH@Z
// cl: /DNDEBUG /MD
//
// W3DView primary vftable 0x011217A0 slot 24 (+0x60) reaches this body through
// ILT 0x00011C4D (the slot before rva00741250, W3DViewRva00741250.cpp). The
// method name is not recovered, so it keeps its address. It seeds a three-point
// camera path: the current position (+0x0C) into the 0x14-byte record at +0x16AC,
// the goal (a path record's +8 point, or the bare Coord3D) into +0x16C0, then the
// mirrored lead-in/lead-out points start-(goal-start) at +0x1698 and goal+(goal-start)
// at +0x16D4, each copied into its working slot (+0x2AC..+0x2E8) through
// Rva007409A0::operator= (0x007409A0, ILT 0x0003A25B).
//
// Shape (probe, 0.585 prior bank -> exact): `start` bound by reference before the
// branches and `goal` only after them (retail materializes &goal in EDI inside each
// branch), and the delta filled member-wise before the subtraction (retail forwards
// x/y as float loads but copies z as a dword; a struct copy kept all three in memory).

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Rva007409A0
{
public:
	Rva007409A0 &operator=(const Rva007409A0 &other);

	Coord3D m_pod;
private:
	char m_unreconstructed0C[0x14 - 0x0c];
};

class Rva007418B0Path
{
	char m_unreconstructed00[0x08];
public:
	Coord3D m_pos;		// +0x08
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	float m_28;
};

// 0x00740F60 and 0x0073CB10 are still gen dumps; the calls name their ILT rows.
class W3DView;
void j_00033fa5();
void j_000321fa();
typedef void (W3DView::*Rva007418B0Setup)(int a3, int a4, int a5, int a6);
typedef void (W3DView::*Rva007418B0Advance)(int value);

class W3DView
{
public:
	virtual void slot000();
	virtual void slot001();
	virtual void slot002();
	virtual void slot003();
	virtual void slot004();
	virtual void slot005();
	virtual void slot006();
	virtual void slot007();
	virtual void slot008();
	virtual void slot009();
	virtual void slot010();
	virtual void slot011();
	virtual void slot012();
	virtual void slot013();
	virtual void slot014();
	virtual void slot015();
	virtual void slot016();
	virtual void slot017();
	virtual void slot018();
	virtual void slot019();
	virtual void slot020();
	virtual void slot021();
	virtual void slot022();
	virtual void slot023();
	virtual void rva007418B0(const Coord3D *pos, Rva007418B0Path *path, int a3, int a4, int a5, int a6);
	virtual void slot025();
	virtual void slot026();
	virtual void slot027(int value);
	virtual void slot028();
	virtual void slot029();
	virtual void slot030();
	virtual void slot031();
	virtual void slot032();
	virtual void slot033();
	virtual void slot034();
	virtual void slot035();
	virtual void slot036();
	virtual void slot037();
	virtual void slot038();
	virtual void slot039();
	virtual void slot040();
	virtual void slot041();
	virtual void slot042();
	virtual void slot043();
	virtual void slot044();
	virtual void slot045();
	virtual void slot046();
	virtual void slot047();
	virtual void slot048();
	virtual void slot049();
	virtual void slot050();
	virtual void slot051();
	virtual void slot052();
	virtual void slot053();
	virtual void slot054();
	virtual void slot055();
	virtual void slot056();
	virtual void slot057();
	virtual void slot058(int a, int b, int c, int d);
	virtual void slot059(float a, int b, int c, int d);
	virtual void slot060(int a, int b, int c, int d);
	virtual void slot061(int a, int b, int c, int d);
	virtual void slot062();
	virtual void slot063();
	virtual void slot064();
	virtual void slot065();
	virtual void slot066();
	virtual void slot067();
	virtual void slot068();
	virtual void slot069();
	virtual void slot070();
	virtual void slot071();
	virtual void slot072();
	virtual void slot073();
	virtual void slot074();
	virtual void slot075();
	virtual void slot076();
	virtual void slot077();
	virtual void slot078();
	virtual void slot079();
	virtual void slot080();
	virtual void slot081();
	virtual void slot082();
	virtual void slot083();
	virtual void slot084();
	virtual void slot085();
	virtual void slot086();
	virtual void slot087();
	virtual void slot088();
	virtual void slot089();
	virtual void slot090();
	virtual void slot091();
	virtual void slot092();
	virtual void slot093();
	virtual void slot094();
	virtual void slot095();
	virtual void slot096();
	virtual void slot097();
	virtual void slot098();
	virtual void slot099();
	virtual void slot100();
	virtual void slot101();
	virtual void slot102();
	virtual void slot103();
	virtual void slot104();
	virtual void slot105();
	virtual void slot106();
	virtual void slot107();
	virtual void slot108();
	virtual void slot109();
	virtual void slot110();
	virtual void slot111();
	virtual void slot112();
	virtual void slot113();
	virtual void slot114();
	virtual void slot115();
	virtual void slot116();
	virtual void slot117();
	virtual void slot118();
	virtual void slot119();
	virtual void slot120();
	virtual void slot121();
	virtual void slot122();
	virtual void slot123();
	virtual void slot124();
	virtual void slot125();
	virtual void slot126();
	virtual void slot127();
	virtual void slot128();
	virtual void slot129();
	virtual void slot130();
	virtual void slot131();
	virtual void slot132();
	virtual float slot133(float value);
private:
	char m_unreconstructed0004[0x0c - 4];
public:
	Coord3D m_pos0C;
private:
	char m_unreconstructed018[0x138 - 0x18];
public:
	int m_int138;
private:
	char m_unreconstructed13C[0x284 - 0x13c];
public:
	int m_int284;
private:
	char m_unreconstructed288[0x2ac - 0x288];
public:
	Rva007409A0 m_work2AC;
	Rva007409A0 m_work2C0;
	Rva007409A0 m_work2D4;
	Rva007409A0 m_work2E8;
private:
	char m_unreconstructed2FC[0x1698 - 0x2fc];
public:
	Rva007409A0 m_point1698;
	Rva007409A0 m_point16AC;
	Rva007409A0 m_point16C0;
	Rva007409A0 m_point16D4;
private:
	char m_unreconstructed16E8[0x16f0 - 0x16e8];
public:
	int m_int16F0;
	int m_int16F4;
private:
	char m_unreconstructed16F8[0x1ae8 - 0x16f8];
public:
	int m_int1AE8;
	int m_int1AEC;
private:
	char m_unreconstructed1AF0[0x1ef0 - 0x1af0];
public:
	int m_int1EF0;
private:
	char m_unreconstructed1EF4[0x22f0 - 0x1ef4];
public:
	int m_int22F0;
private:
	char m_unreconstructed22F4[0x2354 - 0x22f4];
public:
	int m_int2354;
};

// ?rva007418B0@W3DView@@UAEXPBUCoord3D@@PAVRva007418B0Path@@HHHH@Z
void W3DView::rva007418B0(const Coord3D *pos, Rva007418B0Path *path, int a3, int a4, int a5, int a6)
{
	Rva007409A0 &start = m_point16AC;
	start.m_pod = m_pos0C;
	m_work2C0 = start;
	m_int1AE8 = 0;
	if (path)
	{
		m_point16C0.m_pod = path->m_pos;
		m_work2D4 = m_point16C0;
		m_int1AEC = 0;
		slot058(path->m_24, a3, a5, a6);
		float value = path->m_28;
		value = slot133(value);
		slot059(value, a3, a5, a6);
		slot060(path->m_1C, a3, a5, a6);
		slot061(path->m_20, a3, a5, a6);
	}
	else
	{
		if (pos == 0)
			return;
		m_point16C0.m_pod = *pos;
		m_work2D4 = m_point16C0;
		m_int1AEC = 0;
	}

	Rva007409A0 &goal = m_point16C0;
	Coord3D delta;
	delta.x = goal.m_pod.x;
	delta.y = goal.m_pod.y;
	delta.z = goal.m_pod.z;
	delta.x -= start.m_pod.x;
	delta.y -= start.m_pod.y;
	delta.z -= start.m_pod.z;

	Coord3D point = start.m_pod;
	point.x -= delta.x;
	point.y -= delta.y;
	point.z -= delta.z;
	m_point1698.m_pod = point;
	m_work2AC = m_point1698;

	point = goal.m_pod;
	point.x += delta.x;
	point.y += delta.y;
	point.z += delta.z;
	m_point16D4.m_pod = point;
	m_work2E8 = m_point16D4;

	m_int22F0 = 2;
	union { void (*raw)(); Rva007418B0Setup member; } setup = { &j_00033fa5 };
	(this->*setup.member)(a3, a4, a5, a6);
	if (path)
	{
		m_int1EF0 = path->m_14;
		m_int16F0 = path->m_18;
		m_int16F4 = path->m_18;
	}
	if (m_int284 == 1)
	{
		union { void (*raw)(); Rva007418B0Advance member; } advance = { &j_000321fa };
		(this->*advance.member)(1);
		m_int2354 = 1;
		m_int138 = 0;
		slot027(0);
	}
}
