// ?bfmeSelectSplitResult@BfmeHordeContainOwner@@QAEHPAVBfmeSplitResultInput@@PAUBfmeSelectedTemplate@@@Z
// partial score=0.92 date=2026-09-03
// ?bfmeSelectSplitResult@BfmeHordeContainOwner@@QAEHPAVBfmeSplitResultInput@@PAUBfmeSelectedTemplate@@@Z
// partial score=0.92 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME5: select a HordeContain split result, retail 0x0023CDD0.

typedef unsigned int UnsignedInt;

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride( void );
	BfmeOverridable *getFinalOverride( void )
	{
		return m_next == 0 ? this : m_next->friend_getFinalOverride();
	}

	char m_zero[ 4 ];
	BfmeOverridable *m_next;
	char m_head[ 0xd4 - 8 ];
	UnsignedInt m_kindFlags;
};

class BfmeSplitResultInput
{
public:
	char m_head[ 4 ];
	BfmeOverridable *m_template;
};

struct BfmeSelectedTemplate
{
	BfmeOverridable *m_value;
};

class BfmeSplitResult
{
public:
	BfmeSelectedTemplate m_template;
	int m_rank;
};

class BfmeHordeContainOwner
{
public:
	int bfmeSelectSplitResult( BfmeSplitResultInput *input,
		BfmeSelectedTemplate *selectedTemplate );

	char m_head[ 0x1c0 ];
	BfmeSplitResult **m_splitResultsBegin;
	BfmeSplitResult **m_splitResultsEnd;
};

int BfmeHordeContainOwner::bfmeSelectSplitResult(
	BfmeSplitResultInput *input, BfmeSelectedTemplate *selectedTemplate )
{
	BfmeSplitResultInput *source = input;
	BfmeOverridable *volatile wanted;
	if ( source->m_template == 0 )
		wanted = 0;
	else
		wanted = source->m_template->getFinalOverride();

	BfmeSplitResult **first = m_splitResultsBegin;
	BfmeSplitResult **last = m_splitResultsEnd;
	if ( first == last )
		return -1;

	BfmeOverridable *check = source->m_template;
	if ( check != 0 )
		check = check->getFinalOverride();

	if ( ( check->m_kindFlags & 0x1000 ) == 0 )
	{
		UnsignedInt count = last - first;
		UnsignedInt i = 0;
		if ( count > 0 )
		{
			BfmeOverridable *wantedValue = wanted;
			BfmeSplitResult **current = first;
				do
			{
					BfmeSplitResult *candidate = *current;
					if ( candidate->m_template.m_value == wantedValue )
					{
						BfmeSplitResult *selected = first[ i ];
						BfmeSelectedTemplate selectedValue = selected->m_template;
						BfmeSelectedTemplate *output = selectedTemplate;
						*output = selectedValue;
						BfmeSplitResult **base = m_splitResultsBegin;
						BfmeSplitResult *rankResult = base[ i ];
						return rankResult->m_rank;
				}
				++i;
				++current;
			}
			while ( i < count );
		}
	}

	register BfmeSplitResult *selected = first[ 0 ];
	BfmeSelectedTemplate selectedValue = selected->m_template;
	BfmeSelectedTemplate *output = selectedTemplate;
	*output = selectedValue;
	BfmeSplitResult **base = m_splitResultsBegin;
	BfmeSplitResult *rankResult = base[ 0 ];
	return rankResult->m_rank;
}
