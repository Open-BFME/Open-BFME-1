// ?Initialize@Rva00964150FVFInfo@@QAEXII@Z
// partial score=0.89 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath
#include <D3dx8core.h>

class Rva00964150FVFInfo
{
public:
	void Initialize(unsigned fvf, unsigned vertex_size);

private:
	unsigned FVF;
	unsigned fvf_size;
	unsigned location_offset;
	unsigned normal_offset;
	unsigned blend_offset;
	unsigned texcoord_offset[8];
	unsigned diffuse_offset;
	unsigned specular_offset;
	unsigned format;
};

struct FVFInfoClassBFMEFormatTable
{
	unsigned first;
	unsigned values[15];
};

static const FVFInfoClassBFMEFormatTable FVFInfoClassBFMEFormats = {
	0x00000002, {
		0x00000012, 0x00000112, 0x00000212, 0x00000152, 0x00000252,
		0x00000142, 0x00000242, 0x00000102, 0x00000202, 0x00540452,
		0x000b0312, 0x00000052, 0x00000344, 0x00000444, 0x00000000
	}
};

void Rva00964150FVFInfo::Initialize(unsigned fvf, unsigned vertex_size)
{
	unsigned zero = 0;
	FVF = fvf;
	fvf_size = fvf != zero ? D3DXGetFVFVertexSize(fvf) : vertex_size;
	location_offset = zero;
	blend_offset = location_offset;
	if ((FVF & 0x002) == 0x002)
		blend_offset += 3 * sizeof(float);

	normal_offset = blend_offset;
	if ((FVF & 0x00c) == 0x00c && (FVF & 0x1000) == 0x1000)
		normal_offset += 3 * sizeof(float) + sizeof(unsigned);

	diffuse_offset = normal_offset;
	if ((FVF & 0x010) == 0x010)
		diffuse_offset += 3 * sizeof(float);

	specular_offset = diffuse_offset;
	if ((FVF & 0x040) == 0x040)
		specular_offset += sizeof(unsigned);

	texcoord_offset[0] = specular_offset;
	if ((FVF & 0x080) == 0x080)
		texcoord_offset[0] += sizeof(unsigned);

	unsigned shift = 15;
	unsigned count = 7;
	unsigned *offset = &texcoord_offset[1];
	do {
		unsigned previous = offset[-1];
		unsigned size_one = 3u << shift;
		*offset = previous;
		unsigned matched = FVF;
		matched &= size_one;
		if (matched == size_one)
			previous += sizeof(float);
		else
			previous += 2 * sizeof(float);
		*offset = previous;
		++offset;
		++shift;
	} while (--count != 0);

	this->format = 15;
	unsigned value = 2;
	const unsigned *format = FVFInfoClassBFMEFormats.values;
	unsigned groups = 3;
	do {
		if (FVF == format[-1]) this->format = value - 2;
		if (FVF == format[0]) this->format = value - 1;
		if (FVF == format[1]) this->format = value;
		if (FVF == format[2]) this->format = value + 1;
		if (FVF == format[3]) this->format = value + 2;
		value += 5;
		format += 5;
	} while (--groups != 0);
}
