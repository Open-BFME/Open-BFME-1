// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureClass
{
public:
	void Release_Ref(void);
};

class BfmeTexPtr
{
public:
	~BfmeTexPtr(void)
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	TextureClass *m_ptr;
};

class Gen_0092F190
{
public:
	~Gen_0092F190(void);

private:
	BfmeTexPtr m_first;					// +0x00
	BfmeTexPtr m_second;					// +0x04
};

// ??1Gen_0092F190@@QAE@XZ
Gen_0092F190::~Gen_0092F190(void)
{
}
