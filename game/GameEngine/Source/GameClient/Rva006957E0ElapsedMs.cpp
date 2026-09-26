// address-derived name; owning class unidentified.
// Elapsed-ms-since-last-frame accessor on TheGameClient (0x012F1464),
// guarded by this+0x604/this+0x631; a negative delta clamps to 0.
class ClientRoot4120
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25();
	virtual unsigned int getFrame();	///< slot 26 / +0x68
};

extern ClientRoot4120 *TheGameClient;	///< 0x012F1464
extern float g_bfmeElapsedScale;		///< 0x0111BB98 (ms per frame)
extern float g_bfmeZeroDT;				///< 0x01075350, readonly zero float

class Rva006957E0Owner
{
public:
	float getElapsedMs();

	char m_pad00[0x48];
	unsigned int m_lastFrame;
	char m_pad4C[0x604 - 0x4C];
	unsigned int m_guard1;
	char m_pad608[0x631 - 0x608];
	unsigned char m_guard2;
};

float Rva006957E0Owner::getElapsedMs()
{
	if (m_guard1 || m_guard2)
	{
		if (TheGameClient)
			m_lastFrame = TheGameClient->getFrame();
		return g_bfmeElapsedScale;
	}

	if (!TheGameClient)
		return g_bfmeElapsedScale;

	unsigned int frame = TheGameClient->getFrame();
	float delta = ((float)frame - (float)m_lastFrame) * g_bfmeElapsedScale;
	delta = (delta < g_bfmeZeroDT) ? 0.0f : delta;

	m_lastFrame = TheGameClient->getFrame();
	return delta;
}
