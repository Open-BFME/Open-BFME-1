// ?method@Rva008BC710@@QAEXPAUBfmeNode1285@@HH@Z
// partial score=0.3954 date=2026-09-27
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern "C" int __cdecl isdigit(int value);
extern "C" int __cdecl atoi(const char *text);

struct BfmeStringData1285
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned int m_capacity;
	char m_text[1];
};

struct BfmeString1285
{
	BfmeStringData1285 *m_data;
};

struct BfmeNode1285;
struct BfmeDescriptor1285;

struct BfmeIterator1285
{
	BfmeStringData1285 *m_name;
	BfmeNode1285 *m_taggedNode;
};

class BfmeIteratorList1285
{
public:
	BfmeIterator1285 *bfmeFirst1285();
	BfmeIterator1285 *bfmeNext1285(BfmeIterator1285 *iterator);
};

struct BfmeNodeInfo1285
{
	char m_padding00[0x0c];
	BfmeDescriptor1285 *m_descriptor0c;
	BfmeIteratorList1285 *m_list10;
	char m_padding14[4];
	int m_flags18;
};

struct BfmeNode1285
{
	virtual void bfmeAttachVirtual1285();
	virtual void bfmeReleaseVirtual1285();

	unsigned int m_flags04;
	char m_padding08[4];
	BfmeString1285 m_name0c;
	char m_padding10[0x3c];
	BfmeNode1285 *m_next4c;
	BfmeNodeInfo1285 *m_info50;

	void bfmeSetState1285(int state);
};

class BfmeLookup1285
{
public:
	BfmeNode1285 *bfmeFind1285(int key);
};

class BfmeEntrySource1285
{
public:
	BfmeLookup1285 *bfmeGetLookup1285();
};

struct BfmeRecord1285
{
	int m_mask;
	void *m_payload;
};

struct BfmeAudio1285
{
	char m_padding00[8];
	void *m_handle08;
};

struct BfmeDescriptor1285
{
	char m_padding00[0x34];
	int m_count34;
	BfmeRecord1285 *m_records38;
	BfmeAudio1285 **m_audio3c;
};

struct BfmeRoute1285
{
	int m_mask;
	int m_index;
	int m_code;
};

class BfmeR1227
{
public:
	void bfmeAdd1227(void *payload, void *source, void *extra);
};

class BfmeRouteManager1285
{
public:
	bool bfmeAllows1285(BfmeNode1285 *node);
	void bfmeSubmit1285(void *entry, BfmeNode1285 *node, int zero, int encoded);
};

class BfmeBroadcast1285 : public BfmeR1227
{
public:
	void bfmeAdvance1285();
	void bfmeBroadcast1285(BfmeNode1285 *entry, int mode);
	void bfmeFlush1285();

private:
	char m_padding00[0x14];
	int m_count14;
	BfmeNode1285 *m_entries18[512];
	char m_padding818[0x126c - 0x818];
	BfmeNode1285 *m_current126c;
};

extern BfmeStringData1285 g_bfmeEmptyString1285;
extern float g_bfmeDirectionWeight1285;
extern float g_bfmeInvalidScore1285;
// AptInput reaches the same singleton through two independently witnessed class slices.
extern void *g_bfmeHolderBU;
extern float g_bfmeMinimumScore1285;
extern void *g_bfmeExtra1282;
extern BfmeRoute1285 g_bfmeRouteTable1282[7];
extern int g_bfmeRouteKeys1282[1];
extern void (__cdecl *g_bfmePlay1282)(void *handle, int zero);

class BfmeN1034;

class BfmeTab1034
{
public:
	BfmeN1034 *bfmeFind1034F(int key);
};

class BfmeEntrySource1282
{
public:
	BfmeTab1034 *bfmeGetLookup1282();
};

struct BfmeRecord1282
{
	int m_mask;
	void *m_payload;
};

struct BfmeAudio1282
{
	char m_padding00[8];
	void *m_handle08;
};

struct BfmeDescriptor1282
{
	char m_padding00[0x34];
	int m_count34;
	BfmeRecord1282 *m_records38;
	BfmeAudio1282 **m_audio3c;
};

struct BfmeEntryInfo1282
{
	char m_padding00[0x0c];
	BfmeDescriptor1282 *m_descriptor0c;
	char m_padding10[8];
	int m_flags18;
};

struct BfmeEntry1282
{
	char m_padding00[0x4c];
	BfmeEntrySource1282 *m_source4c;
	BfmeEntryInfo1282 *m_info50;
};

class BfmeRouteManager1282
{
public:
	void bfmeSubmit1282(void *entry, BfmeN1034 *node, int zero, int encoded);
};

class BfmeBroadcast1282 : public BfmeR1227
{
public:
	void bfmeBroadcast1282(BfmeEntry1282 *entry, int mode);
	void bfmeFlush1282();
};


// REL32 caller RVA 0x008BCD60 targets 0x008BC710; ret12 at 0x008BCC94.
// Switch tables end at 0x008BCCB4 followed by int3 padding.
class Rva008BC710 : public BfmeR1227 {
public:
 void method(BfmeNode1285 *node, int direction, int state);
 __forceinline void emit(BfmeEntry1282 *entry, int mode);
 char pad[0x1240];
 BfmeNode1285 *f1240;
 char pad1244[0x126c-0x1244];
 BfmeNode1285 *current;
 int active;
};
BfmeNode1285 *bfmeFindDirectional1285(int,BfmeNode1285*,BfmeNode1285*);
__forceinline void Rva008BC710::emit(BfmeEntry1282 *entry, int mode)
{
	BfmeDescriptor1282 *descriptor = entry->m_info50->m_descriptor0c;
	for (int index = 0; index < descriptor->m_count34; ++index) {
		BfmeRecord1282 *record = &descriptor->m_records38[index];
		if ((record->m_mask & mode) != 0)
			bfmeAdd1227(&record->m_payload, entry->m_source4c, g_bfmeExtra1282);
	}

	int routeMask = 0;
	if ((mode & 8) != 0) routeMask = 0x800;
	if ((mode & 4) != 0) routeMask |= 0x400;
	if ((mode & 0x40) != 0) routeMask |= 0x1000;
	if ((mode & 1) != 0) routeMask |= 0x2000;
	if ((mode & 2) != 0) routeMask |= 0x4000;
	if ((mode & 0x20) != 0) routeMask |= 0x8000;
	if ((mode & 0x10) != 0) routeMask |= 0x10000;

	if ((entry->m_info50->m_flags18 & routeMask) != 0) {
		int *route = &g_bfmeRouteTable1282[0].m_index;
		for (; (int)route < (int)&g_bfmeRouteTable1282[7].m_index; route += 3) {
			if ((route[-1] & routeMask) != 0) {
				BfmeN1034 *node = entry->m_source4c->bfmeGetLookup1282()->bfmeFind1034F(
					(int)&g_bfmeRouteKeys1282[route[0]]);
				if (node != 0) {
					int encoded = ((route[1] & 0x7f) << 10) | 5;
					reinterpret_cast<BfmeRouteManager1282 *>(g_bfmeHolderBU)
						->bfmeSubmit1282(entry, node, 0, encoded);
				}
			}
		}
	}

	if (descriptor->m_audio3c != 0) {
		switch (mode) {
		case 2:
			if (descriptor->m_audio3c[0] != 0)
				g_bfmePlay1282(descriptor->m_audio3c[0]->m_handle08, 0);
			break;
		case 1:
			if (descriptor->m_audio3c[1] != 0)
				g_bfmePlay1282(descriptor->m_audio3c[1]->m_handle08, 0);
			break;
		case 4:
			if (descriptor->m_audio3c[2] != 0)
				g_bfmePlay1282(descriptor->m_audio3c[2]->m_handle08, 0);
			break;
		case 8:
			if (descriptor->m_audio3c[3] != 0)
				g_bfmePlay1282(descriptor->m_audio3c[3]->m_handle08, 0);
			break;
		}
	}
	((BfmeBroadcast1282*)this)->bfmeFlush1282();
}


void Rva008BC710::method(BfmeNode1285 *node,int direction,int state) {
 switch(direction) {
 case 1: case 2: case 14: case 15:
  if(!active && state==0) {
   ((BfmeBroadcast1285*)this)->bfmeAdvance1285();
   if(current) {
    if(!node) node=bfmeFindDirectional1285(direction,current->m_next4c,current);
    else {
     unsigned flags=node->m_flags04;
     if(((flags&63)==13 && ((unsigned char)~(flags>>15)&1)==0) || ((flags&63)==18 && ((unsigned char)~(flags>>15)&1)==0))
      node=bfmeFindDirectional1285(direction,node,0);
    }
    if(node) {
     current->bfmeSetState1285(1);
     node->bfmeSetState1285(2);
     emit((BfmeEntry1282*)current,2);
     ((BfmeBroadcast1282*)this)->bfmeBroadcast1282((BfmeEntry1282*)node,1);
     if(current) current->bfmeReleaseVirtual1285();
     current=node;
     node->bfmeAttachVirtual1285();
    }
   }
  }
  break;
 case 0:
  if(!current) { active=state==0; active=state!=1; return; }
  if(!active && state==0) {
   active=1;
   current->bfmeSetState1285(4);
   emit((BfmeEntry1282*)current,4);
  }
  if(active && state==1) {
   active=0;
   if(*(int*)((char*)current->m_info50+0x1c)==2) {
    current->bfmeSetState1285(1);
    emit((BfmeEntry1282*)current,0x40);
    if(current) {
     current->bfmeSetState1285(2);
     if(f1240 != current->m_next4c) ((BfmeBroadcast1282*)this)->bfmeBroadcast1282((BfmeEntry1282*)current,1);
     else emit((BfmeEntry1282*)current,8);
    }
   } else {
    current->bfmeSetState1285(2);
    emit((BfmeEntry1282*)current,8);
   }
  }
  break;
 }
}
