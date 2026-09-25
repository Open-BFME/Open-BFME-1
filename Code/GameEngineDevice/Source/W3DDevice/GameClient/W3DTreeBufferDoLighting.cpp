// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib
// W3DTreeBuffer::doLighting, retail 0x00732700 (470 bytes, ret 0x18, `this` unused).
// Zero Hour twin: GeneralsMD W3DTreeBuffer.cpp W3DTreeBuffer::doLighting -- const,
// returns the packed diffuse, first parameter the normal, and the same
// vertexDiffuse != 0xFFFFFFFF block modulating blue, green then red (that statement
// order is byte-decisive here). Retail sits between W3DTreeBuffer::updateSway
// (0x00732500) and freeTreeBuffers (0x00732960), and loadTreesInVertexAndIndexBuffers
// (0x00734CB0) calls it twice through its ILT thunk, once with 0xFFFFFFFF, as the
// twin's caller does. BFME passes precomputed light rays and colours instead of
// the twin's TerrainLighting array; MSVC 7.1 unrolls the three-light loop.
#include "vector3.h"
#include "wwmath.h"

typedef unsigned int UnsignedInt;

// Three floats copied as a trivially-copyable aggregate (retail moves them through
// integer registers, which the real Vector3's user copy constructor does not);
// elements 0, 1, 2 feed the red, green and blue bytes of the packed result.
struct Rva00732700Rgb
{
	float red;
	float green;
	float blue;
};

class W3DTreeBuffer
{
protected:
	UnsignedInt doLighting(const Vector3 *normal, const Rva00732700Rgb *shade,
		const Vector3 *light, const Rva00732700Rgb *diffuse,
		UnsignedInt vertexDiffuse, UnsignedInt alpha) const;
};

UnsignedInt W3DTreeBuffer::doLighting(const Vector3 *normal,
	const Rva00732700Rgb *shade, const Vector3 *light, const Rva00732700Rgb *diffuse,
	UnsignedInt vertexDiffuse, UnsignedInt alpha) const
{
	Rva00732700Rgb shadeValue = *shade;
	float lighting;

	for (int i = 0; i < 3; i++) {
		lighting = Vector3::Dot_Product(light[i], *normal);
		lighting = WWMath::Fabs(lighting);
		shadeValue.red += lighting * diffuse[i].red;
		shadeValue.green += lighting * diffuse[i].green;
		shadeValue.blue += lighting * diffuse[i].blue;
	}

	UnsignedInt red = WWMath::Float_To_Long(shadeValue.red * 255.0f);
	UnsignedInt green = WWMath::Float_To_Long(shadeValue.green * 255.0f);
	UnsignedInt blue = WWMath::Float_To_Long(shadeValue.blue * 255.0f);

	if (vertexDiffuse != 0xFFFFFFFF) {
		blue = (vertexDiffuse & 0xFF) * blue >> 8;
		green = ((vertexDiffuse >> 8) & 0xFF) * green >> 8;
		red = ((vertexDiffuse >> 16) & 0xFF) * red >> 8;
	}
	if (red > 0xFF) red = 0xFF;
	if (green > 0xFF) green = 0xFF;
	if (blue > 0xFF) blue = 0xFF;
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}
