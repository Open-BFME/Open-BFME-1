// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Lift the HLodClass::Get_Current_LOD naked dump to clean C++.
//
// Retail asks the object how many sub-objects the current LOD has and returns
// null when there are none -- MSVC 7.1 reuses the already-zero test result
// instead of re-zeroing eax, which is why the early return has no `xor eax,eax`.
// The filler virtuals exist only to put the two real calls on their retail
// vtable offsets (+0x228 and +0x230); none of them is ever defined.

class RenderObjClass;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/hlod.h
class HLodClass
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
	virtual void unused130();
	virtual void unused131();
	virtual void unused132();
	virtual void unused133();
	virtual void unused134();
	virtual void unused135();
	virtual void unused136();
	virtual void unused137();
	virtual int Get_Sub_Object_Count(int) const;		///< vtable +0x228
	virtual void unused139();
	virtual RenderObjClass *Get_Sub_Object(int, int) const;	///< vtable +0x230
	virtual RenderObjClass *Get_Current_LOD(void);

private:
	unsigned char m_unreconstructed_04[0x128 - 4];
	int m_currentLod;							///< retail this+0x128
};

// ?Get_Current_LOD@HLodClass@@UAEPAVRenderObjClass@@XZ
RenderObjClass *HLodClass::Get_Current_LOD(void)
{
	if (Get_Sub_Object_Count(m_currentLod) == 0)
		return 0;

	return Get_Sub_Object(m_currentLod, 0);
}
