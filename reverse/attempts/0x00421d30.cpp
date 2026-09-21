// ??0Rva00421D30@@QAE@XZ (owner identity unknown)
// partial score=0.92 date=2026-09-08
class Rva00421D30Vec
{
public:
	float m_bfmeXZV;
	float m_bfmeYZV;
	float m_bfmeZZV;
};

class Rva00421D30
{
public:
	Rva00421D30();

	float m_bfme00ZV;
	float m_bfme04ZV;
	float m_bfme08ZV;
	float m_bfme0CZV;
	float m_bfme10ZV;
	float m_bfme14ZV;
	float m_bfme18ZV;
	float m_bfme1CZV;
	float m_bfme20ZV;
	float m_bfme24ZV;
	Rva00421D30Vec m_bfme28ZV;
	Rva00421D30Vec m_bfme34ZV;
	Rva00421D30Vec m_bfme40ZV;
	float m_bfme4CZV;
	float m_bfme50ZV;
	float m_bfme54ZV;
};

Rva00421D30::Rva00421D30()
{
	m_bfme34ZV.m_bfmeXZV = 0.5f;
	m_bfme34ZV.m_bfmeYZV = 0.5f;
	m_bfme34ZV.m_bfmeZZV = 0.5f;

	m_bfme40ZV = m_bfme34ZV;
	m_bfme28ZV = m_bfme34ZV;

	m_bfme00ZV = 4.0f;
	m_bfme04ZV = 0.7f;
	m_bfme08ZV = 1.0f;
	m_bfme0CZV = 1.0f;
	m_bfme10ZV = 1.0f;
	m_bfme14ZV = 1.0f;
	m_bfme18ZV = 1.0f;
	m_bfme1CZV = 1.0f;
	m_bfme24ZV = 1.0f;
	m_bfme20ZV = 1.0f;
	m_bfme4CZV = 1.0f;
	m_bfme50ZV = 1.0f;
	m_bfme54ZV = 5.0f;
}
