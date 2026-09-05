// cl: /DNDEBUG /MD /EHsc
//
// ScriptEngine::setSway, retail 0x00336B20. ZH twin writes BreezeInfo from
// a five-parameter ScriptAction: direction + sin/cos, intensity, lean,
// period (min 1), randomness. BFME keeps the same struct at +0x17604.

extern "C" float __cdecl sinf(float);
extern "C" float __cdecl cosf(float);

class Parameter
{
public:
	int getInt() const { return m_int; }
	float getReal() const { return m_real; }

private:
	char m_unknown[8];
	int m_int;
	float m_real;
};

class ScriptAction
{
public:
	Parameter *getParameter(int ndx)
	{
		if (ndx >= 0 && ndx < m_numParms)
			return m_parms[ndx];
		return 0;
	}

private:
	char m_unknown[8];
	int m_numParms;
	Parameter *m_parms[12];
};

struct Coord2D
{
	float x;
	float y;
};

struct BreezeInfo
{
	float m_direction;
	Coord2D m_directionVec;
	float m_intensity;
	float m_lean;
	float m_randomness;
	short m_breezePeriod;
	short m_breezeVersion;
};

class ScriptEngine
{
protected:
	void setSway(ScriptAction *pAction);

private:
	unsigned char m_unreconstructed[0x17604];
	BreezeInfo m_breezeInfo;
};

// ?setSway@ScriptEngine@@IAEXPAVScriptAction@@@Z
void ScriptEngine::setSway(ScriptAction *pAction)
{
	++m_breezeInfo.m_breezeVersion;
	m_breezeInfo.m_direction = pAction->getParameter(0)->getReal();
	m_breezeInfo.m_directionVec.x = sinf(m_breezeInfo.m_direction);
	m_breezeInfo.m_directionVec.y = cosf(m_breezeInfo.m_direction);
	m_breezeInfo.m_intensity = pAction->getParameter(1)->getReal();
	m_breezeInfo.m_lean = pAction->getParameter(2)->getReal();
	m_breezeInfo.m_breezePeriod = (short)pAction->getParameter(3)->getInt();
	if (m_breezeInfo.m_breezePeriod < 1)
		m_breezeInfo.m_breezePeriod = 1;
	m_breezeInfo.m_randomness = pAction->getParameter(4)->getReal();
}
