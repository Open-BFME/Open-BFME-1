// cl: /DNDEBUG /MD /EHsc

// RunOffMapBehaviorModuleData::RunOffMapBehaviorModuleData, 0x00126760, 96
// bytes. ModuleFactory's data-create proc for "RunOffMapBehavior" (dp050 in
// module_factory.cpp) runs this through ILT 0x001267E0, which is the
// friend_newModuleData factory, so the class name is the module factory's.
//
// Layout, from the body itself: this+0x08 and this+0x0C get 10.0f, this+0x10
// and this+0x18 get 0, and the UnicodeString at this+0x14 is zeroed and then
// handed the interned empty literal at 0x01336E50 by
// ?set@UnicodeString@@QAEXABV1@@Z (0x00887C90, StringBase.cpp). The +0x04 dword
// of the base is never written, so the base ctor is elided and the vptr store
// at 0x0108E9F0 is the only base-side effect.
//
// ecx is loaded with the member's address before the vptr store and reused for
// both the member's own zeroing and the set call that follows -- it is the
// thiscall argument set up early, not a separate cursor.
//
// Two unwind states, 0 and 1, count the two destructible things built before
// the throwing call: the base and the member. 0x01336E50 needs no declaration
// of its own here: it is already pinned as an object under two other type
// tags, and the retail call takes its address as a real UnicodeString.
//
// The four scalar stores are plain, not volatile: left ordinary, MSVC 7.1
// schedules them after the set() argument push exactly as retail does, whereas
// qualifying them volatile pins them ahead of it and costs 15 bytes.
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
	float m_speed1;				// +0x08
	float m_speed2;				// +0x0c
	bool m_flag10;				// +0x10
	UnicodeString m_text14;		// +0x14
	bool m_flag18;				// +0x18
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
