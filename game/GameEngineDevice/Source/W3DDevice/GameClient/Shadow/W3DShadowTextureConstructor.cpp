// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug
// readable body of ??0W3DShadowTexture@@QAE@XZ: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadow.cpp
//
// W3DShadowTexture::W3DShadowTexture, retail 0x007AF400, 122 bytes (plain ret).
// It stamps the vftables recorded for W3DShadowTexture's RefCountClass and
// HashableClass bases (0x011283F8/0x011283EC), and ilt_oracle CONFIRMS the
// name at ILT 0x000455F7. The shadow-texture manager's texture lookup at
// 0x007AFD10 constructs through it; the matched destructor is 0x007AF4E0.
// The layout is Zero Hour's member for member. The body is Zero Hour's, plus
// the two initialisations BFME adds: a null texture and an empty name.

#include "refcount.h"
#include "hash.h"
#include "vector3.h"
#include "matrix3.h"
#include "aabox.h"
#include "sphere.h"

class TextureClass;
#define W3D_NAME_LEN 16

class W3DShadowTexture : public RefCountClass, public HashableClass
{
	public:

		W3DShadowTexture( void );
		// Retail's destructor (0x007AF4E0) lives in W3DShadowTextureDestructor.cpp; declared
		// only, so this unit emits no non-retail implicit copy.
		~W3DShadowTexture( void );

		virtual	const char * Get_Key( void )	{ return m_namebuf;	}

	private:

		char m_namebuf[2*W3D_NAME_LEN];
		TextureClass *m_texture;
		Vector3		m_lastLightPosition;
		Matrix3x3	m_lastObjectOrientation;
		AABoxClass	m_areaEffectBox;
		SphereClass	m_areaEffectSphere;
		Vector3		m_shadowUV[2];
};

W3DShadowTexture::W3DShadowTexture( void )
{
	m_texture = NULL;
	m_lastLightPosition.Set(0,0,0); m_lastObjectOrientation.Make_Identity();
	m_namebuf[0] = 0;
	m_shadowUV[0].Set(1.0f,0.0f,0.0f);
	m_shadowUV[1].Set(0.0f,-1.0f,0.0f);
}
