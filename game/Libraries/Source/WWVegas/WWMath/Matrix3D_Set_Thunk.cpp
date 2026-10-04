// cl: /DNDEBUG /MD /EHsc
// Retail FVF layout initializer; the EA member spelling is unproven.

extern "C" unsigned __stdcall D3DXGetFVFVertexSize(unsigned);

class BFMEVertexFVFInfo
{
public:
	BFMEVertexFVFInfo(unsigned fvf, unsigned vertexSize);
	void Rva00964150(unsigned fvf, unsigned vertexSize);

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

typedef char BFMEVertexFVFInfoSizeCheck[sizeof(BFMEVertexFVFInfo) == 0x40 ? 1 : -1];

static const unsigned FVFInfoClassBFMEFormats[15] = {
	0x00000002, 0x00000012, 0x00000112, 0x00000212, 0x00000152,
	0x00000252, 0x00000142, 0x00000242, 0x00000102, 0x00000202,
	0x00540452, 0x000b0312, 0x00000052, 0x00000344, 0x00000444
};

void BFMEVertexFVFInfo::Rva00964150(unsigned fvf, unsigned vertexSize)
{
	unsigned zero = 0;
	FVF = fvf;
	fvf_size = fvf != zero ? D3DXGetFVFVertexSize(fvf) : vertexSize;
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
		*offset = previous;
		if ((int(FVF) & (3 << shift)) == (3 << shift))
			previous += sizeof(float);
		else
			previous += 2 * sizeof(float);
		*offset = previous;
		++offset;
		++shift;
	} while (--count != 0);

	format = 15;
	for (int i = 0; i < 15; ++i) {
		if (FVF == FVFInfoClassBFMEFormats[i])
			format = i;
	}
}
