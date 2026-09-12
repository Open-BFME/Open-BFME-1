// ??0RunOffMapBehaviorModuleData@@QAE@XZ
// partial score=0.84 date=2026-09-12
// cl: /DNDEBUG /MD /EHsc

// Retail 0x01336E50 -- already pinned under two other type tags
// (Rva0036CA00Str / Rva002E5FF0Str) by other converted bodies; this file
// reuses the same address as a real UnicodeString, matching the retail
// ?set@UnicodeString@@ call.
class UnicodeString
{
public:
	UnicodeString(void) { m_text = 0; }
	~UnicodeString(void);

	void set(const UnicodeString &that);

private:
	void *m_text;
};

extern UnicodeString Rva01336E50Str;

class RunOffMapBehaviorModuleDataBase
{
public:
	virtual ~RunOffMapBehaviorModuleDataBase() {}

protected:
	unsigned int m_unused04;
};

class RunOffMapBehaviorModuleData : public RunOffMapBehaviorModuleDataBase
{
public:
	RunOffMapBehaviorModuleData();
	virtual ~RunOffMapBehaviorModuleData();

private:
	volatile float m_speed1;   // +0x08
	volatile float m_speed2;   // +0x0c
	volatile bool m_flag10;    // +0x10
	UnicodeString m_text14;    // +0x14
	volatile bool m_flag18;    // +0x18
};

// ??0RunOffMapBehaviorModuleData@@QAE@XZ
RunOffMapBehaviorModuleData::RunOffMapBehaviorModuleData()
{
	m_flag18 = false;
	m_speed1 = 10.0f;
	m_speed2 = 10.0f;
	m_flag10 = false;
	m_text14.set( Rva01336E50Str );
}
