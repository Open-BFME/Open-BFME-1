// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Primary-table virtual slot 1, RVA 0x005FC320 (105 bytes).
// Tables 0x01112D14 (installed by the ParticleModuleState005FC800 constructor
// at 0x005FC800) and 0x01112144 (installed over it by the derived module that
// Rva005E6350Template::createModule builds) both route slot 1 through ILT
// 0x00007A2C. The constructor proves the layout: +0x04 from its first
// argument, +0x0C byte, +0x14 and +0x18 words, +0x1C byte set to 1.
// Historical method name unknown. TheGameClient slot 26 (+0x68) is getFrame,
// as in the matched LifeEvent slot 1 at 0x005FC450.

typedef unsigned int UnsignedInt;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Matrix3D;

class FXList
{
public:
	bool bfmeIsBlocked();
	void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx,
		Real primarySpeed, const Coord3D *secondary) const;
};

class GameClient
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
	virtual void slot24();
	virtual void slot25();
	virtual UnsignedInt getFrame();
};

extern GameClient *TheGameClient;

// The object the constructor's first argument points at; only the fields
// this body touches are modelled.
struct Rva005FC320Target
{
	unsigned char m_pad00[0x1c];
	Coord3D m_coord1c;
	unsigned char m_pad28[0x40];
	UnsignedInt m_dword68;
	UnsignedInt m_dword6c;
};

class ParticleModuleState005FC800
{
public:
	virtual void slot00();
	virtual void slot01();

private:
	Rva005FC320Target *m_ptr04;
	unsigned char m_pad08[4];
	bool m_byte0c;
	unsigned char m_pad0d[7];
	UnsignedInt m_dword14;
	FXList *m_fxList18;
	bool m_byte1c;
	unsigned char m_pad1d[3];
};

void ParticleModuleState005FC800::slot01()
{
	if (!m_byte1c)
		return;
	if (!m_fxList18)
		return;

	Rva005FC320Target *target = m_ptr04;
	if (TheGameClient->getFrame() - target->m_dword6c < m_dword14)
		return;

	const Coord3D *position = &target->m_coord1c;
	FXList *fx = m_fxList18;
	if (fx && fx->bfmeIsBlocked())
		fx = 0;
	if (fx)
		fx->doFXPos(position, 0, 0.0f, 0);

	bool flag = m_byte0c;
	m_byte1c = false;
	if (flag)
		m_ptr04->m_dword68 = 1;
}
