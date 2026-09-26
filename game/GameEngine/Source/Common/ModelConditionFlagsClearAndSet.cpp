// cl: /DNDEBUG /DWIN32 /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME: ModelConditionFlags::clearAndSet, retail 0x001C5FA0.

#include <bitset>

class ModelConditionFlags
{
public:
	void clearAndSet( const ModelConditionFlags &clr,
		const ModelConditionFlags &set );

private:
	_STL::bitset<304> m_bits;
};

void ModelConditionFlags::clearAndSet( const ModelConditionFlags &clr,
	const ModelConditionFlags &set )
{
	m_bits &= ~clr.m_bits;
	m_bits |= set.m_bits;
}
