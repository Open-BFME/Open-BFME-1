// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad

typedef int Int;
typedef short Short;
typedef bool Bool;
typedef unsigned char UnsignedByte;

struct BfmeBlendTileInfo0074C140
{
	Short blendNdx;
	UnsignedByte padding02[2];
	UnsignedByte horiz;
	UnsignedByte vert;
	UnsignedByte rightDiagonal;
	UnsignedByte leftDiagonal;
	UnsignedByte inverted;
	UnsignedByte longDiagonal;
	UnsignedByte padding0A[2];
	Int customBlendEdgeClass;
};

#pragma comment(linker, "/alternatename:?getUVForTileIndex@WorldHeightMap@@IAE_NHFQAM0_N@Z=?j_00009fc5@@YAXXZ")

class WorldHeightMap
{
public:
	Bool getExtraAlphaUVData(Int xIndex, Int yIndex, float U[4],
		float V[4], UnsignedByte alpha[4], Bool *needFlip, Bool *cliff);

	protected:
	Bool getUVForTileIndex(Int ndx, Short tileNdx, float U[4],
		float V[4], Bool fullTile);

private:
	char m_prefix00[8];
	Int m_width;
	char m_prefix0c[0x14];
	Int m_dataSize;
	char m_prefix24[0x68];
	Short *m_tileNdxes;
	Int *m_blendTileNdxes;
	Int *m_cliffInfoNdxes;
	Int *m_extraBlendTileNdxes;
	char m_prefix9c[0x8008];
	BfmeBlendTileInfo0074C140 *m_blendedTiles;
};

// ?getExtraAlphaUVData@WorldHeightMap@@QAE_NHHQAM0QAEPA_N2@Z
Bool WorldHeightMap::getExtraAlphaUVData(Int xIndex, Int yIndex, float U[4],
	float V[4], UnsignedByte alpha[4], Bool *needFlip, Bool *cliff)
{
	Int ndx = (yIndex*m_width)+xIndex;
	register Int zero = 0;
	#define BFME_NEED_FLIP_0074C140 \
		(*(*reinterpret_cast<Bool * volatile *>(&needFlip)))
	BFME_NEED_FLIP_0074C140 = zero;
	*cliff = zero;

	if ((ndx>=0) && (ndx<m_dataSize) && m_tileNdxes) {
		Int blendNdx = m_extraBlendTileNdxes[ndx];
		if (blendNdx == zero) {
			return 0;
		} else {
			const unsigned int blendBaseForCall =
				(unsigned int)m_blendedTiles;
			*cliff = getUVForTileIndex(ndx,
				*(Short *)((blendNdx << 4) + blendBaseForCall), U, V, zero);
			alpha[0] = alpha[1] = alpha[2] = alpha[3] = zero;
			const unsigned int blendBaseForHoriz =
				(unsigned int)m_blendedTiles;
			if (*(const UnsignedByte *)((blendNdx << 4) +
				blendBaseForHoriz + 4)) {
				BFME_NEED_FLIP_0074C140 =
					m_blendedTiles[blendNdx].inverted & 0x2;
				if (m_blendedTiles[blendNdx].inverted & 0x1) {
					alpha[0] = alpha[3] = 255;
				} else {
					alpha[1] = alpha[2] = 255;
				}
			}
			if (m_blendedTiles[blendNdx].vert) {
				BFME_NEED_FLIP_0074C140 =
					m_blendedTiles[blendNdx].inverted & 0x2;
				if (m_blendedTiles[blendNdx].inverted & 0x1) {
					alpha[0] = alpha[1] = 255;
				} else {
					alpha[2] = alpha[3] = 255;
				}
			}
			if (m_blendedTiles[blendNdx].rightDiagonal) {
				if (m_blendedTiles[blendNdx].inverted & 0x1) {
					alpha[1] = 255;
					if (m_blendedTiles[blendNdx].longDiagonal) {
						alpha[0] = 255;
						alpha[2] = 255;
					}
				} else {
					BFME_NEED_FLIP_0074C140 = 1;
					alpha[2] = 255;
					if (m_blendedTiles[blendNdx].longDiagonal) {
						alpha[1] = 255;
						alpha[3] = 255;
					}
				}
			}
			if (m_blendedTiles[blendNdx].leftDiagonal) {
				if (m_blendedTiles[blendNdx].inverted & 0x1) {
					BFME_NEED_FLIP_0074C140 = 1;
					alpha[0] = 255;
					if (m_blendedTiles[blendNdx].longDiagonal) {
						alpha[1] = 255;
						alpha[3] = 255;
					}
				} else {
					alpha[3] = 255;
					if (m_blendedTiles[blendNdx].longDiagonal) {
						alpha[0] = 255;
						alpha[2] = 255;
					}
				}
			}
			if (m_blendedTiles[blendNdx].customBlendEdgeClass>=zero) {
				alpha[0] = alpha[1] = alpha[2] = alpha[3] = zero;
				BFME_NEED_FLIP_0074C140 = zero;
			}
		}
	}

	return 1;
}

#undef BFME_NEED_FLIP_0074C140
