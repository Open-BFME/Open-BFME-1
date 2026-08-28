// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// W3DPoliceCarDraw::createDynamicLight -- the Zero Hour body compiles to
// retail's exact instruction sequence, `lea ecx,[esp+4]` between the Ambient
// and Diffuse store groups included; what differs is only the LIGHT LAYOUT.
// BFME's RenderObjClass is 0x34 bytes larger than Zero Hour's and carries two
// more virtuals ahead of Set_Position, which shifts every field this body
// touches by exactly +0x34 (Ambient 0xA4->0xD8, Diffuse 0xB0->0xE4,
// FarAttenStart/End 0xD0/0xD4->0x104/0x108, m_enabled 0x114->0x148) and moves
// Set_Position from vtable slot 20 to slot 22.
//
// The layout lives in vendored headers, so the classes below are a TU-scoped
// ABI slice at BFME's offsets and declare nothing this one body does not
// touch.  The field names and the setEnabled/Set_Ambient/Set_Diffuse/
// Set_Far_Attenuation_Range bodies are Zero Hour's own, unchanged.
#define NULL 0

// Vector3 verbatim from WWMath/vector3.h, ABI slice: the assignment-body
// constructors and the explicit operator= are load-bearing, a member-init
// list here reorders the temporary against `this`.
class Vector3
{
public:
	float X;
	float Y;
	float Z;

	Vector3(void) { }
	Vector3(const Vector3 & v) { X = v.X; Y = v.Y; Z = v.Z; }
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }

	Vector3 & operator = (const Vector3 & v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDynamicLight.h
class W3DDynamicLight
{
public:
	// BFME RenderObjClass slots 0..21; only their count matters, so
	// Set_Position lands on slot 22 == [vptr+0x58].
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21();
	virtual void Set_Position(const Vector3 &p);

	void Set_Ambient(const Vector3 &color) { Ambient = color; }
	void Set_Diffuse(const Vector3 &color) { Diffuse = color; }
	void Set_Far_Attenuation_Range(double fStart, double fEnd) { FarAttenStart = fStart; FarAttenEnd = fEnd; }
	void setEnabled(bool enabled) { m_enabled = enabled; m_decayRange = false; m_decayFrameCount = 0; m_decayColor = false; m_increaseFrameCount = 0; }

	char			m_renderObjSlice[0xD4];		// vptr at +0x00, LightClass head through +0xD7
	Vector3			Ambient;					// +0xD8
	Vector3			Diffuse;					// +0xE4
	char			m_specularAndNearSlice[0x14];	// Specular +0xF0, Near attenuation +0xFC/+0x100
	float			FarAttenStart;				// +0x104
	float			FarAttenEnd;				// +0x108
	char			m_spotAndCounterSlice[0x3C];	// spot/persist tail and W3DDynamicLight's own head
	bool			m_enabled;					// +0x148
	bool			m_decayRange;				// +0x149
	bool			m_decayColor;				// +0x14A
	char			m_curFrameCountSlice[9];	// m_curDecayFrameCount +0x14C, m_curIncreaseFrameCount +0x150
	unsigned int	m_decayFrameCount;			// +0x154
	unsigned int	m_increaseFrameCount;		// +0x158
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DScene.h
class RTS3DScene
{
public:
	W3DDynamicLight *getADynamicLight(void);		// 0x00712420, already matched
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplay.h
class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;					// 0x012F8058
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DPoliceCarDraw.h
class W3DPoliceCarDraw
{
protected:
	W3DDynamicLight *createDynamicLight(void);
};

W3DDynamicLight *W3DPoliceCarDraw::createDynamicLight( void )
{
	W3DDynamicLight *light = NULL;

	// get me a dynamic light from the scene
	light = W3DDisplay::m_3DScene->getADynamicLight();
	if( light )
	{

		light->setEnabled( true );
		light->Set_Ambient( Vector3( 0.0f, 0.0f, 0.0f ) );
		// Use all ambient, and no diffuse.  This produces a circle of light on
		// even and uneven ground.  Diffuse lighting shows up ground unevenness, which looks
		// funny on a searchlight.  So  no diffuse.  jba.
		light->Set_Diffuse( Vector3( 0.0f, 0.0f, 0.0f ) );
		light->Set_Position( Vector3( 0.0f, 0.0f, 0.0f ) );
		light->Set_Far_Attenuation_Range( 5, 15 );

	}  // end if

	return light;

}  // end createDynamicSearchLight
