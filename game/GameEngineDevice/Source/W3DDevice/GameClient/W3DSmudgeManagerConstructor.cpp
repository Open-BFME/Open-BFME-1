// cl: /O2 /Ob0

class SmudgeManager
{
public:
	SmudgeManager();
	virtual void handle();

private:
	char m_pad[0x20];
};

// Native W3DSmudge.cpp owns this base-interface singleton. Retail terrain init
// stores the constructed W3DSmudgeManager at VA 0x012F9D88 (RVA 0x00730716);
// resource callers dispatch through its base slots +0x0C and +0x10.
SmudgeManager *TheSmudgeManager = 0;

class W3DSmudgeManager : public SmudgeManager
{
	void *m_smudgeGroup;
	void *m_posBuffer;
	void *m_RGBABuffer;
	void *m_sizeBuffer;
	void *m_indexBuffer;
	int m_backBufferWidth;
	int m_backBufferHeight;
	unsigned int m_probeColor;

public:
	W3DSmudgeManager();
};

W3DSmudgeManager::W3DSmudgeManager()
{
	m_smudgeGroup = 0;
	m_posBuffer = 0;
	m_RGBABuffer = 0;
	m_sizeBuffer = 0;
	m_indexBuffer = 0;
	m_backBufferWidth = 0;
	m_backBufferHeight = 0;
	m_probeColor = 0x00FFEEDD;
}
