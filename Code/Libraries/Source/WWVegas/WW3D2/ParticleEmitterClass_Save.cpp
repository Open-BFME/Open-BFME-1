// BFME's emitter save wrapper returns the definition's save result directly.
// The later public header models the API as WW3DErrorType, but the retail
// function is the bool wrapper at 0x00980320.

class ChunkSaveClass;

class ParticleEmitterDefClass
{
public:
	virtual void Dummy0(void);
	virtual void Dummy1(void);
	virtual bool Save_W3D(ChunkSaveClass &chunk_save);
};

class ParticleEmitterClass
{
public:
	ParticleEmitterDefClass *Build_Definition(void) const;
	bool Save(ChunkSaveClass &chunk_save) const;
};

// ?Save@ParticleEmitterClass@@QBE_NAAVChunkSaveClass@@@Z
bool ParticleEmitterClass::Save(ChunkSaveClass &chunk_save) const
{
	bool result = false;
	ParticleEmitterDefClass *definition = Build_Definition();
	if (definition != 0) {
		result = definition->Save_W3D(chunk_save);
	}
	return result;
}
