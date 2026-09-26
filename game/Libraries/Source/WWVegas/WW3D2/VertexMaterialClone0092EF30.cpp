// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: VertexMaterialClass::Clone at 0x0092EF30 (94 B): allocate a
// 0x6c-byte VertexMaterialClass with the global operator new, default
// construct it (EH state around the raw allocation), copy-assign from this,
// return it. The ported vertmaterial.h spells the allocation through NEW_REF,
// which adds a registration call retail does not have.
class VertexMaterialClass
{
public:
	VertexMaterialClass();
	VertexMaterialClass &operator=(const VertexMaterialClass &);
	VertexMaterialClass *Clone();
private:
	char m_body[0x6c];
};

VertexMaterialClass *VertexMaterialClass::Clone()
{
	VertexMaterialClass *mat = new VertexMaterialClass;
	*mat = *this;
	return mat;
}
