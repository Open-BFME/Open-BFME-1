// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Lift the ParticleBufferClass::On_Frame_Update naked dump to clean C++.
//
// Zero Hour's part_buf.cpp carries this body. Its WWPROFILE and WWASSERT
// compile away in a release build, which is why retail is only the three
// remaining steps: drop the cached bounding volumes, let the emitter run, and
// hand a finished buffer back to the scene for release.
//
// Retail pins the layout ZH leaves symbolic: the cached-bounds flag is bit
// 0x20000 of the word at this+0x10 (`and dword ptr [esi+0x10], 0xFFFDFFFF`),
// Scene is at this+0x80 and Emitter at this+0x254. The filler virtuals only
// place the three real calls on their retail vtable offsets.

class ParticleBufferClass;

enum RegisterType { ON_FRAME_UPDATE = 0, LIGHT = 1, RELEASE = 2 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/scene.h
class SceneClass
{
public:
	virtual void unused000();
	virtual void unused001();
	virtual void unused002();
	virtual void unused003();
	virtual void unused004();
	virtual void unused005();
	virtual void unused006();
	virtual void unused007();
	virtual void unused008();
	virtual void unused009();
	virtual void unused010();
	virtual void unused011();
	virtual void unused012();
	virtual void unused013();
	virtual void Register(ParticleBufferClass *, int);	///< vtable +0x38
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/part_emt.h
class ParticleEmitterClass
{
public:
	virtual void unused000();
	virtual void unused001();
	virtual void unused002();
	virtual void unused003();
	virtual void unused004();
	virtual void unused005();
	virtual void unused006();
	virtual void unused007();
	virtual void unused008();
	virtual void unused009();
	virtual void unused010();
	virtual void unused011();
	virtual void unused012();
	virtual void unused013();
	virtual void unused014();
	virtual void unused015();
	virtual void unused016();
	virtual void unused017();
	virtual void unused018();
	virtual void unused019();
	virtual void unused020();
	virtual void unused021();
	virtual void unused022();
	virtual void unused023();
	virtual void unused024();
	virtual void unused025();
	virtual void unused026();
	virtual void unused027();
	virtual void unused028();
	virtual void unused029();
	virtual void unused030();
	virtual void unused031();
	virtual void unused032();
	virtual void unused033();
	virtual void unused034();
	virtual void unused035();
	virtual void unused036();
	virtual void unused037();
	virtual void unused038();
	virtual void unused039();
	virtual void unused040();
	virtual void unused041();
	virtual void unused042();
	virtual void unused043();
	virtual void unused044();
	virtual void unused045();
	virtual void unused046();
	virtual void unused047();
	virtual void unused048();
	virtual void unused049();
	virtual void unused050();
	virtual void unused051();
	virtual void unused052();
	virtual void unused053();
	virtual void unused054();
	virtual void unused055();
	virtual void unused056();
	virtual void unused057();
	virtual void unused058();
	virtual void unused059();
	virtual void unused060();
	virtual void unused061();
	virtual void unused062();
	virtual void unused063();
	virtual void unused064();
	virtual void unused065();
	virtual void unused066();
	virtual void unused067();
	virtual void unused068();
	virtual void unused069();
	virtual void unused070();
	virtual void unused071();
	virtual void unused072();
	virtual void unused073();
	virtual void unused074();
	virtual void unused075();
	virtual void unused076();
	virtual void unused077();
	virtual void unused078();
	virtual void unused079();
	virtual void unused080();
	virtual void unused081();
	virtual void unused082();
	virtual void unused083();
	virtual void unused084();
	virtual void unused085();
	virtual void unused086();
	virtual void unused087();
	virtual void unused088();
	virtual void unused089();
	virtual void unused090();
	virtual void unused091();
	virtual void unused092();
	virtual void unused093();
	virtual void unused094();
	virtual void unused095();
	virtual void unused096();
	virtual void unused097();
	virtual void unused098();
	virtual void unused099();
	virtual void unused100();
	virtual void unused101();
	virtual void unused102();
	virtual void unused103();
	virtual void unused104();
	virtual void unused105();
	virtual void unused106();
	virtual void unused107();
	virtual void unused108();
	virtual void unused109();
	virtual void unused110();
	virtual void unused111();
	virtual void unused112();
	virtual void unused113();
	virtual void unused114();
	virtual void unused115();
	virtual void unused116();
	virtual void unused117();
	virtual void unused118();
	virtual void unused119();
	virtual void unused120();
	virtual void unused121();
	virtual void unused122();
	virtual void unused123();
	virtual void unused124();
	virtual void unused125();
	virtual void unused126();
	virtual void unused127();
	virtual void unused128();
	virtual void unused129();
	virtual void Emit(void);							///< vtable +0x208
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/part_buf.h
class ParticleBufferClass
{
public:
	virtual void unused000();
	virtual void unused001();
	virtual void unused002();
	virtual void unused003();
	virtual void unused004();
	virtual void unused005();
	virtual void unused006();
	virtual void unused007();
	virtual void unused008();
	virtual void unused009();
	virtual void unused010();
	virtual void unused011();
	virtual void unused012();
	virtual void unused013();
	virtual void unused014();
	virtual void unused015();
	virtual void unused016();
	virtual void unused017();
	virtual void unused018();
	virtual void unused019();
	virtual void unused020();
	virtual void unused021();
	virtual void unused022();
	virtual void unused023();
	virtual void unused024();
	virtual void unused025();
	virtual void unused026();
	virtual void unused027();
	virtual void unused028();
	virtual void unused029();
	virtual void unused030();
	virtual void unused031();
	virtual void unused032();
	virtual void unused033();
	virtual void unused034();
	virtual void unused035();
	virtual void unused036();
	virtual void unused037();
	virtual void unused038();
	virtual void unused039();
	virtual void unused040();
	virtual void unused041();
	virtual void unused042();
	virtual void unused043();
	virtual void unused044();
	virtual void unused045();
	virtual void unused046();
	virtual void unused047();
	virtual void unused048();
	virtual void unused049();
	virtual void unused050();
	virtual void unused051();
	virtual void unused052();
	virtual void unused053();
	virtual void unused054();
	virtual void unused055();
	virtual void unused056();
	virtual void unused057();
	virtual void unused058();
	virtual void unused059();
	virtual void unused060();
	virtual void unused061();
	virtual void unused062();
	virtual void unused063();
	virtual void unused064();
	virtual void unused065();
	virtual void unused066();
	virtual void unused067();
	virtual void unused068();
	virtual void unused069();
	virtual void unused070();
	virtual void unused071();
	virtual void unused072();
	virtual void unused073();
	virtual void unused074();
	virtual void unused075();
	virtual void unused076();
	virtual void unused077();
	virtual void unused078();
	virtual void unused079();
	virtual void unused080();
	virtual void unused081();
	virtual void unused082();
	virtual void unused083();
	virtual void unused084();
	virtual void unused085();
	virtual void unused086();
	virtual void unused087();
	virtual void unused088();
	virtual void unused089();
	virtual void unused090();
	virtual void unused091();
	virtual void unused092();
	virtual void unused093();
	virtual void unused094();
	virtual void unused095();
	virtual void unused096();
	virtual void unused097();
	virtual void unused098();
	virtual void unused099();
	virtual void unused100();
	virtual void unused101();
	virtual void unused102();
	virtual void unused103();
	virtual void unused104();
	virtual void unused105();
	virtual void unused106();
	virtual void unused107();
	virtual void unused108();
	virtual void unused109();
	virtual void unused110();
	virtual void unused111();
	virtual void unused112();
	virtual void unused113();
	virtual void unused114();
	virtual void unused115();
	virtual void unused116();
	virtual void unused117();
	virtual void unused118();
	virtual void unused119();
	virtual void unused120();
	virtual bool Is_Complete(void);						///< vtable +0x1E4
	virtual void On_Frame_Update(void);

	void Invalidate_Cached_Bounding_Volumes(void) { Flags &= ~CACHED_BOUNDING_VOLUMES_VALID; }

private:
	enum { CACHED_BOUNDING_VOLUMES_VALID = 0x00020000 };

	unsigned char m_unreconstructed_04[0x10 - 4];
	unsigned int Flags;									///< retail this+0x10
	unsigned char m_unreconstructed_14[0x80 - 0x14];
	SceneClass *Scene;									///< retail this+0x80
	unsigned char m_unreconstructed_84[0x254 - 0x84];
	ParticleEmitterClass *Emitter;						///< retail this+0x254
};

// ?On_Frame_Update@ParticleBufferClass@@UAEXXZ
void ParticleBufferClass::On_Frame_Update(void)
{
	Invalidate_Cached_Bounding_Volumes();

	if (Emitter)
	{
		Emitter->Emit();
	}

	if (Is_Complete())
	{
		Scene->Register(this, RELEASE);
	}
}
