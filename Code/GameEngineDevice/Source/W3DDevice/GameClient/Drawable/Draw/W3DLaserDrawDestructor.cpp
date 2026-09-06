// cl: /DNDEBUG /MD /EHsc
// BFME W3DLaserDraw destructor.  The shipped BFME class has a larger
// DrawableModule base and a texture-vector member than the later reference
// header, so keep this recovered layout local to the destructor TU.

class W3DLaserDrawModuleData
{
public:
	char m_padding20[0x20];
	unsigned int m_numBeams;
	char m_padding24[0x14];
	unsigned int m_segments;
};

class DrawableModule
{
	protected:
	virtual ~DrawableModule();

	W3DLaserDrawModuleData *m_moduleData;
	int m_bfmeField;
};

class DrawModule : public DrawableModule
{
protected:
	virtual ~DrawModule() {}
};

class LaserDrawInterface
{
public:
	virtual void bfmeLaserDrawInterfaceSlot();
};

class SegmentedLineClass
{
public:
	virtual void Release();
};

class Gen_00757830
{
public:
	~Gen_00757830();

	void *m_start;
	void *m_finish;
	void *m_end;
};

class RTS3DScene
{
public:
	virtual void bfmeSceneSlot0();
	virtual void bfmeSceneSlot1();
	virtual void bfmeSceneSlot2();
	virtual void Remove_Render_Object(SegmentedLineClass *line);
};

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

class W3DLaserDraw : public DrawModule, public LaserDrawInterface
{
public:
	virtual void doDrawModule();

protected:
	virtual ~W3DLaserDraw();

	SegmentedLineClass **m_line3D;
	Gen_00757830 m_textureVector;
};

void __cdecl operator delete[](void *block);

// ??1W3DLaserDraw@@MAE@XZ
W3DLaserDraw::~W3DLaserDraw()
{
	const W3DLaserDrawModuleData *data = m_moduleData;

	for (int i = 0; i < data->m_numBeams * data->m_segments; i++)
	{
		W3DDisplay::m_3DScene->Remove_Render_Object(m_line3D[i]);
		SegmentedLineClass *line = m_line3D[i];
		if (line)
		{
			if (--reinterpret_cast<int *>(line)[1] == 0)
				line->Release();
			m_line3D[i] = 0;
		}
	}

	void *block = m_line3D;
	operator delete[](block);
}
