// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Source/WWVegas/WWSaveLoad
// Open-BFME5: clean C++ restoration of BFME geometry-buffer uniqueness.

#include "sharebuf.h"
#include "vector3.h"
#include "vector4.h"

class MeshModelClass
{
public:
	void Make_Geometry_Unique();

private:
	unsigned char m_padding00[0x30];
	ShareBufferClass<Vector3> *m_buffer30;
	ShareBufferClass<Vector3> *m_buffer34;
	unsigned char m_padding38[8];
	ShareBufferClass<Vector3> *m_buffer40;
	ShareBufferClass<Vector3> *m_buffer44;
	unsigned char m_padding48[8];
	ShareBufferClass<Vector4> *m_buffer50;
};

void MeshModelClass::Make_Geometry_Unique()
{
	ShareBufferClass<Vector3> *buffer30 =
		NEW_REF(ShareBufferClass<Vector3>, (*m_buffer30));
	REF_PTR_SET(m_buffer30, buffer30);
	REF_PTR_RELEASE(buffer30);

	ShareBufferClass<Vector3> *buffer40 =
		NEW_REF(ShareBufferClass<Vector3>, (*m_buffer40));
	REF_PTR_SET(m_buffer40, buffer40);
	REF_PTR_RELEASE(buffer40);

	if (m_buffer34 != 0 && m_buffer44 != 0) {
		ShareBufferClass<Vector3> *buffer34 =
			NEW_REF(ShareBufferClass<Vector3>, (*m_buffer34));
		REF_PTR_SET(m_buffer34, buffer34);
		REF_PTR_RELEASE(buffer34);

		ShareBufferClass<Vector3> *buffer44 =
			NEW_REF(ShareBufferClass<Vector3>, (*m_buffer44));
		REF_PTR_SET(m_buffer44, buffer44);
		REF_PTR_RELEASE(buffer44);
	}

	ShareBufferClass<Vector4> *buffer50 =
		NEW_REF(ShareBufferClass<Vector4>, (*m_buffer50));
	REF_PTR_SET(m_buffer50, buffer50);
	REF_PTR_RELEASE(buffer50);
}
