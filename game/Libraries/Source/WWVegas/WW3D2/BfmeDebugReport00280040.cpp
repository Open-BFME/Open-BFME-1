// ?bfmeReportObsoleteAffectsKindOf00280040@@YAXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class BFMEIndexBufferDebugStream
{
public:
	virtual BFMEIndexBufferDebugStream *Put_Unsigned(unsigned value);
	virtual void Slot04();
	virtual void Slot08();
	virtual void Slot0C();
	virtual void Slot10();
	virtual void Slot14();
	virtual void Slot18();
	virtual void Slot1C();
	virtual void Slot20();
	virtual void Slot24();
	virtual void Slot28();
	virtual void Slot2C();
	virtual void Slot30();
	virtual void Slot34();
	virtual BFMEIndexBufferDebugStream *Put_String(const char *text);
	virtual void Slot3C();
	virtual void Slot40();
	virtual void Slot44();
	virtual void Slot48();
	virtual BFMEIndexBufferDebugStream *Finish(int report);
};

class BFMEIndexBufferDebugClass
{
public:
	virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
	virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
	virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
	virtual void Slot30(); virtual void Slot34(); virtual void Slot38(); virtual void Slot3C();
	virtual void Slot40(); virtual void Slot44(); virtual void Slot48(); virtual void Slot4C();
	virtual void Slot50(); virtual void Slot54(); virtual void Slot58(); virtual void Slot5C();
	virtual void Begin_Report();
	virtual void Slot64(); virtual void Slot68();
	virtual BFMEIndexBufferDebugStream *Get_Stream(void *owner, void *context);
};

extern BFMEIndexBufferDebugClass *g_BFMEIndexBufferDebug;
extern void _bfme_debugRecordCallsite(int kind);
bool __cdecl _bfme_debugReportingEnabled(void);

void __cdecl bfmeReportObsoleteAffectsKindOf00280040(void)
{
	if (!_bfme_debugReportingEnabled())
		return;
	_bfme_debugRecordCallsite(1);
	g_BFMEIndexBufferDebug->Begin_Report();
	BFMEIndexBufferDebugStream *stream = g_BFMEIndexBufferDebug->Get_Stream(0, 0);
	stream->Put_String(
		"AttributeModifierAuraUpdate... AffectsKindOf is obsolete, please "
		"replace with ObjectFilter. -M Lo")
		->Finish(2);
}
