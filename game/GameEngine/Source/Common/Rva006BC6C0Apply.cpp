// cl: /O2 /Ob0

// retail global: RTS3DScene *W3DDisplay::m_3DScene (0x012F8058),
// mangled ?m_3DScene@W3DDisplay@@2PAVRTS3DScene@@A.
class RTS3DScene
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08(int value);
};

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

class Rva006BC6C0
{
	char m_lead[4];
	int m_at4;

public:
	void apply();
};

void Rva006BC6C0::apply()
{
	W3DDisplay::m_3DScene->slot08(m_at4);
}
