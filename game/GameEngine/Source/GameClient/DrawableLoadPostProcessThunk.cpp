// cl: /DNDEBUG /MD /EHsc
// readable body of ?loadPostProcess@Drawable@@MAEXXZ: game/GameEngine/Source/GameClient/Drawable.cpp
//
// Retail 0x004120A0, 45 bytes.  loadPostProcess overrides the Snapshot base at
// Drawable+0x60, so `this` arrives adjusted.  Like Zero Hour it restores the
// transform from the owning object (m_object at Drawable+0xFC, through the
// Thing transform copy at 0x00132200); the ambient-sound restart is gone, and
// BFME instead tail-calls slot 1 of the object held at Drawable+0x3BC, whose
// type is not established here.

class Matrix3D;

class Thing
{
public:
	virtual ~Thing();
	void rva00132200(const Matrix3D *mtx);
	const Matrix3D *getTransformMatrix() const { return (const Matrix3D *)m_transform; }

private:
	const void *m_template;
	char m_transform[0x30];
	char m_unmodelled38[0x28];
};

class Object : public Thing
{
};

class Snapshot
{
protected:
	virtual void crc();
	virtual void xfer();
	virtual void loadPostProcess();
};

class Rva004120A0Restorable
{
public:
	virtual void slot0();
	virtual void slot1();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable : public Thing, public Snapshot
{
protected:
	virtual void loadPostProcess();

private:
	char m_unmodelled64[0xFC - 0x64];
	Object *m_object;
	char m_unmodelled100[0x3BC - 0x100];
	Rva004120A0Restorable *m_restorable3BC;
};

void Drawable::loadPostProcess()
{
	if (m_object != 0)
		rva00132200(m_object->getTransformMatrix());

	if (m_restorable3BC)
		m_restorable3BC->slot1();
}
