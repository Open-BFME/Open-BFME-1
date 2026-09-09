// ?getRva0058B590Value@Player@@QBEJH@Z
// partial score=0.64 date=2026-09-09
// cl: /DNDEBUG /DRELEASE_DEBUG_LOGGING /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#ifndef NULL
#define NULL 0
#endif

extern "C" __declspec(dllimport) double __cdecl floor(double);

typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;

extern float BfmeZeroRange;
extern float g_bfmeScaleBC;
extern float g_bfmeK1253;

struct BfmeObject;

struct BfmeObjectHashNode
{
	BfmeObjectHashNode *m_next;
	UnsignedInt m_id;
	BfmeObject *m_object;
};

struct BfmeGameLogic
{
	unsigned char m_pad00[0xb4];
	BfmeObjectHashNode **m_objectBucketsBegin;
	BfmeObjectHashNode **m_objectBucketsEnd;
};

extern BfmeGameLogic *TheBfmeGameLogic;

struct BfmeObject
{
	unsigned char m_pad00[0x118];
	unsigned char m_status;
};

struct BfmePlayerValue
{
	Int *m_key;
	Real *m_valuesBegin;
	Real *m_valuesEnd;
	unsigned char m_pad0c[4];
	UnsignedInt m_objectID;
};

struct BfmePlayerValueNode
{
	BfmePlayerValueNode *m_next;
	BfmePlayerValueNode *m_prev;
	BfmePlayerValue *m_value;
};

class Player
{
public:
	long getRva0058B590Value(int value) const;
};

long Player::getRva0058B590Value(int value) const
{
	Real result = BfmeZeroRange;
	BfmePlayerValueNode *anchor = *(BfmePlayerValueNode **)((const unsigned char *)this + 0x640);
	BfmePlayerValueNode *node = anchor->m_next;
	Int valueIndex = 0;

	if (node != anchor)
	{
		while (node != anchor)
		{
			BfmePlayerValue *entry = node->m_value;
			UnsignedInt objectID = entry->m_objectID;
			if (objectID != 0)
			{
				BfmeObjectHashNode **buckets = TheBfmeGameLogic->m_objectBucketsBegin;
				UnsignedInt bucketCount = (UnsignedInt)(TheBfmeGameLogic->m_objectBucketsEnd - buckets);
				BfmeObjectHashNode *hash = buckets[objectID % bucketCount];
				while (hash != NULL && hash->m_id != objectID)
					hash = hash->m_next;
				if (hash != NULL)
				{
					BfmeObject *object = hash->m_object;
					if (object != NULL && (object->m_status & 8) == 0)
					{
						if (*entry->m_key == value)
						{
							Int count = (Int)(entry->m_valuesEnd - entry->m_valuesBegin);
							if (valueIndex < count)
								result = entry->m_valuesBegin[valueIndex++];
						}
					}
				}
			}
			node = node->m_next;
		}
	}

	return (long)floor((double)(g_bfmeK1253 - result * g_bfmeScaleBC));
}
