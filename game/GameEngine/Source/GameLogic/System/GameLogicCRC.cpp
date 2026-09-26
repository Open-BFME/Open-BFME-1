// cl: /DNDEBUG /MD /EHsc
// BFME GameLogic CRC at RVA 0x00383150 (499 bytes).
// The retail ABI takes ONE optional byte-stream pointer and returns with ret 4.
// The report caller at 0x00065470 passes literal zero, not a mode plus string.
// The nonzero argument path forwards its pointer to the stream writer that
// emits EALA/RTS2 through stream vslot +0x10 (0x009D6300 -> 0x009D8460).
// Local views below preserve the observed BFME layouts without changing ZH headers.
// CRC transfer class spelling is reconstructed: constructor 0x0006B190 calls
// base 0x009D8630, installs vtable 0x01075B08, and owns flag +0x40/CRC +0x44.
// Base spelling follows the existing recovered block writer at 0x009D88F0.
class Snapshot { public: virtual ~Snapshot(); };
class BfmeByteStream;
class Rva009D8630BlockWriter {
public:
	Rva009D8630BlockWriter();
	virtual ~Rva009D8630BlockWriter();
	virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4();
	virtual int beginBlock(const char *name); virtual void slot6(); virtual void slot7(); virtual void slot8();
	virtual void slot9(); virtual void slot10(); virtual void slot11();
	virtual void xferSnapshot(Snapshot*);
	virtual void slot13(); virtual void slot14(); virtual void slot15(); virtual void slot16();
	virtual void slot17(); virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23(); virtual void slot24();
	virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28();
	virtual void xferUnsignedInt(unsigned int*);
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35(); virtual void slot36();
	virtual void xferEnum(void *context, const void *bytes, unsigned int count);
	bool open(BfmeByteStream*); void close();
private: char data[0x3c];
};
class BFMECRCWriter: public Rva009D8630BlockWriter {
public:
	BFMECRCWriter(bool full): full(full), crc(0) {}
	// These slots differ from the base writer in retail vtable 0x01075B08.
	virtual void slot3(); virtual void slot4(); virtual int beginBlock(const char *name); virtual void slot11();
	// Final slot +0x94 is the recovered rotate/add accumulator at 0x009D6330.
	virtual void xferEnum(void *context, const void *bytes, unsigned int count);
	bool full; unsigned int crc;
};
// The exact parameter-check transfer is currently ledgered with this older
// address-derived class spelling in BfmeConv1705.cpp. Keep its proven callee.
class BfmeXferFW;
class BfmeThingFW { public: void bfmeXferFW(BfmeXferFW *); };
class CRCParameterCheck : public BfmeThingFW {};
extern CRCParameterCheck* TheCRCParameterCheck;
extern bool g_bfmeCRCForceAll, g_bfmeCRCSkipObjects, g_bfmeCRCSkipPartition, g_bfmeCRCSkipCollision, g_bfmeCRCSkipShroud, g_bfmeCRCSkipTaint, g_bfmeCRCSkipPlayers, g_bfmeCRCSkipAI;
// Global identities are independently anchored by retail initialization tags:
// Partition/Collision/Shroud: stores at 0x0038A23D/0x0038A316/0x0038A2AB
// are followed by their matching The... string tags at +0x13/+0x10/+0x10.
// Taint/PlayerList/AI: The... tags at 0x00079EA4/0x0007A00E/0x00079D1E
// precede addresses 0x012ED5C0/0x012ED748/0x012EF214 passed to initSubsystem.
// BfmeTaintManager is a reconstructed spelling already used by its exact
// world-circle updater (0x008810D0); the registration proves the global name.
struct SystemBase { virtual ~SystemBase(); int pad; };
class PartitionManager: public SystemBase, public Snapshot {};
extern PartitionManager* ThePartitionManager;
class CollisionManager: public SystemBase, public Snapshot {};
extern CollisionManager* TheCollisionManager;
class ShroudManager: public SystemBase, public Snapshot {};
extern ShroudManager* TheShroudManager;
class BfmeTaintManager: public SystemBase, public Snapshot {};
extern BfmeTaintManager* TheTaintManager;
class PlayerList: public SystemBase, public Snapshot {};
extern PlayerList* ThePlayerList;
class AI: public SystemBase, public Snapshot {};
extern AI* TheAI;
struct ObjectBase { virtual ~ObjectBase(); char pad0[0x5c]; };
struct Object: public ObjectBase, public Snapshot { char pad1[0x24]; Object* next; };
class GameLogic { public: unsigned int getCRC(BfmeByteStream*); char pad[0xa8]; Object* first; };
void setFPMode(); unsigned int GetGameLogicRandomSeedCRC();
unsigned int GameLogic::getCRC(BfmeByteStream* stream) {
	setFPMode();
	BFMECRCWriter writer(g_bfmeCRCForceAll);
	Rva009D8630BlockWriter *xfer = &writer;
	if (stream)
		writer.open(stream);
	if (TheCRCParameterCheck)
		TheCRCParameterCheck->bfmeXferFW(reinterpret_cast<BfmeXferFW *>(&writer));
	if (g_bfmeCRCForceAll || !g_bfmeCRCSkipObjects)
	{
		for (Object *obj = first; obj; obj = obj->next)
			xfer->xferSnapshot(obj);
	}
	unsigned int seed = GetGameLogicRandomSeedCRC();
	xfer->xferUnsignedInt(&seed);
	if (g_bfmeCRCForceAll || !g_bfmeCRCSkipPartition)
		xfer->xferSnapshot(ThePartitionManager);
	if (g_bfmeCRCForceAll || !g_bfmeCRCSkipCollision)
		xfer->xferSnapshot(TheCollisionManager);
	if (g_bfmeCRCForceAll || !g_bfmeCRCSkipShroud)
		xfer->xferSnapshot(TheShroudManager);
	if (g_bfmeCRCForceAll || !g_bfmeCRCSkipTaint)
		xfer->xferSnapshot(TheTaintManager);
	if (g_bfmeCRCForceAll || !g_bfmeCRCSkipPlayers)
		xfer->xferSnapshot(ThePlayerList);
	if (g_bfmeCRCForceAll || !g_bfmeCRCSkipAI)
		xfer->xferSnapshot(TheAI);
	writer.close();
	return writer.crc;
}
