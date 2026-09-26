// One hundred and nineteen singleton forwarders.
//
// Each is two instructions: load the ADDRESS of a global object into ecx and
// tail-jump. The immediate is an address rather than a load, so the global is
// the object itself and not a pointer to one, and the jump means the callee
// takes exactly the arguments the wrapper was handed -- none.
//
// Found by classifying every small gen_asm dump by its mnemonic sequence.
// Byte-grouping never clusters these: the object address and the jump target
// differ in every one, so no two share a masked byte pattern.

class Gen_0005C450Target
{
public:
	void bfmeForward(void);					// retail 0x00018205
};

extern Gen_0005C450Target TheBfmeObject_0005C450;		// 0x134fb18
class Gen_006D1870Target
{
public:
	void bfmeForward(void);					// retail 0x00002603
};

extern Gen_006D1870Target TheBfmeObject_006D1870;		// 0x12f7ff0
class Gen_009372E0Target
{
public:
	void bfmeForward(void);					// retail 0x009DB820
};

extern Gen_009372E0Target TheBfmeObject_009372E0;		// 0x1346e74
class Gen_00C6FC80Target
{
public:
	void bfmeForward(void);					// retail 0x0003CD49
};

extern Gen_00C6FC80Target TheBfmeObject_00C6FC80;		// 0x12ed570
class Gen_00C6FC90Target
{
public:
	void bfmeForward(void);					// retail 0x0003F76A
};

extern Gen_00C6FC90Target TheBfmeObject_00C6FC90;		// 0x12ed55c
class Gen_00C6FCA0Target
{
public:
	void bfmeForward(void);					// retail 0x0003F76A
};

extern Gen_00C6FCA0Target TheBfmeObject_00C6FCA0;		// 0x12ed548
class Gen_00C6FCB0Target
{
public:
	void bfmeForward(void);					// retail 0x0003FC29
};

extern Gen_00C6FCB0Target TheBfmeObject_00C6FCB0;		// 0x12ed534
class Gen_00C6FE10Target
{
public:
	void bfmeForward(void);					// retail 0x000390C7
};

extern Gen_00C6FE10Target TheBfmeObject_00C6FE10;		// 0x12effa0
class Gen_00C6FE50Target
{
public:
	void bfmeForward(void);					// retail 0x0002842F
};

extern Gen_00C6FE50Target TheBfmeObject_00C6FE50;		// 0x12f0770
class Gen_00C6FE70Target
{
public:
	void bfmeForward(void);					// retail 0x00014538
};

extern Gen_00C6FE70Target TheBfmeObject_00C6FE70;		// 0x12f08a0
class Gen_00C6FEF0Target
{
public:
	void bfmeForward(void);					// retail 0x000422B7
};

extern Gen_00C6FEF0Target TheBfmeObject_00C6FEF0;		// 0x12f1000
class Gen_00C6FF00Target
{
public:
	void bfmeForward(void);					// retail 0x0000A380
};

extern Gen_00C6FF00Target TheBfmeObject_00C6FF00;		// 0x12f1050
class Gen_00C6FF10Target
{
public:
	void bfmeForward(void);					// retail 0x0003CDDA
};

extern Gen_00C6FF10Target TheBfmeObject_00C6FF10;		// 0x12f10dc
class Gen_00C6FF20Target
{
public:
	void bfmeForward(void);					// retail 0x00016F9A
};

extern Gen_00C6FF20Target TheBfmeObject_00C6FF20;		// 0x12f10f8
class Gen_00C6FF30Target
{
public:
	void bfmeForward(void);					// retail 0x00016F9A
};

extern Gen_00C6FF30Target TheBfmeObject_00C6FF30;		// 0x12f10f4
class Gen_00C6FF60Target
{
public:
	void bfmeForward(void);					// retail 0x00026F35
};

extern Gen_00C6FF60Target TheBfmeObject_00C6FF60;		// 0x12f1318
class Gen_00C6FFA0Target
{
public:
	void bfmeForward(void);					// retail 0x0000B23A
};

extern Gen_00C6FFA0Target TheBfmeObject_00C6FFA0;		// 0x12f1404
class Gen_00C6FFC0Target
{
public:
	void bfmeForward(void);					// retail 0x00036985
};

extern Gen_00C6FFC0Target TheBfmeObject_00C6FFC0;		// 0x12f146c
class Gen_00C6FFF0Target
{
public:
	void bfmeForward(void);					// retail 0x00014475
};

extern Gen_00C6FFF0Target TheBfmeObject_00C6FFF0;		// 0x12f15a4
class Gen_00C70000Target
{
public:
	void bfmeForward(void);					// retail 0x000442DD
};

extern Gen_00C70000Target TheBfmeObject_00C70000;		// 0x12f1598
class Gen_00C70010Target
{
public:
	void bfmeForward(void);					// retail 0x000154F6
};

extern Gen_00C70010Target TheBfmeObject_00C70010;		// 0x12f15a8
class Gen_00C70020Target
{
public:
	void bfmeForward(void);					// retail 0x000154F6
};

extern Gen_00C70020Target TheBfmeObject_00C70020;		// 0x12f15ac
class Gen_00C70030Target
{
public:
	void bfmeForward(void);					// retail 0x000464D4
};

extern Gen_00C70030Target TheBfmeObject_00C70030;		// 0x12f15b0
class Gen_00C70070Target
{
public:
	void bfmeForward(void);					// retail 0x0000123F
};

extern Gen_00C70070Target TheBfmeObject_00C70070;		// 0x12f19b8
class Gen_00C70080Target
{
public:
	void bfmeForward(void);					// retail 0x0003A8E1
};

extern Gen_00C70080Target TheBfmeObject_00C70080;		// 0x12f19cc
class Gen_00C70090Target
{
public:
	void bfmeForward(void);					// retail 0x00029109
};

extern Gen_00C70090Target TheBfmeObject_00C70090;		// 0x12f1990
class Gen_00C700A0Target
{
public:
	void bfmeForward(void);					// retail 0x00026EEF
};

extern Gen_00C700A0Target TheBfmeObject_00C700A0;		// 0x12f19a4
class Gen_00C700B0Target
{
public:
	void bfmeForward(void);					// retail 0x0000D828
};

extern Gen_00C700B0Target TheBfmeObject_00C700B0;		// 0x12f2570
class Gen_00C700C0Target
{
public:
	void bfmeForward(void);					// retail 0x0000D828
};

extern Gen_00C700C0Target TheBfmeObject_00C700C0;		// 0x12f2574
class Gen_00C700D0Target
{
public:
	void bfmeForward(void);					// retail 0x0000D828
};

extern Gen_00C700D0Target TheBfmeObject_00C700D0;		// 0x12f2578
class Gen_00C700E0Target
{
public:
	void bfmeForward(void);					// retail 0x0000D828
};

extern Gen_00C700E0Target TheBfmeObject_00C700E0;		// 0x12f257c
class Gen_00C70100Target
{
public:
	void bfmeForward(void);					// retail 0x0001B7C5
};

extern Gen_00C70100Target TheBfmeObject_00C70100;		// 0x12f3354
class Gen_00C70110Target
{
public:
	void bfmeForward(void);					// retail 0x00026F35
};

extern Gen_00C70110Target TheBfmeObject_00C70110;		// 0x12f3370
class Gen_00C70120Target
{
public:
	void bfmeForward(void);					// retail 0x000398FB
};

extern Gen_00C70120Target TheBfmeObject_00C70120;		// 0x12f3884
class Gen_00C70130Target
{
public:
	void bfmeForward(void);					// retail 0x0003B304
};

extern Gen_00C70130Target TheBfmeObject_00C70130;		// 0x12f3af8
class Gen_00C70140Target
{
public:
	void bfmeForward(void);					// retail 0x0003B304
};

extern Gen_00C70140Target TheBfmeObject_00C70140;		// 0x12f3afc
class Gen_00C70150Target
{
public:
	void bfmeForward(void);					// retail 0x0003B304
};

extern Gen_00C70150Target TheBfmeObject_00C70150;		// 0x12f3b00
class Gen_00C70160Target
{
public:
	void bfmeForward(void);					// retail 0x0003B304
};

extern Gen_00C70160Target TheBfmeObject_00C70160;		// 0x12f3dc4
class Gen_00C70170Target
{
public:
	void bfmeForward(void);					// retail 0x0001642D
};

extern Gen_00C70170Target TheBfmeObject_00C70170;		// 0x12f4024
class Gen_00C70180Target
{
public:
	void bfmeForward(void);					// retail 0x0001642D
};

extern Gen_00C70180Target TheBfmeObject_00C70180;		// 0x12f406c
class Gen_00C70190Target
{
public:
	void bfmeForward(void);					// retail 0x0001642D
};

extern Gen_00C70190Target TheBfmeObject_00C70190;		// 0x12f418c
class Gen_00C701A0Target
{
public:
	void bfmeForward(void);					// retail 0x0003C4CA
};

extern Gen_00C701A0Target TheBfmeObject_00C701A0;		// 0x12f463c
class Gen_00C701B0Target
{
public:
	void bfmeForward(void);					// retail 0x0003B304
};

extern Gen_00C701B0Target TheBfmeObject_00C701B0;		// 0x12f48c8
class Gen_00C701C0Target
{
public:
	void bfmeForward(void);					// retail 0x0000D828
};

extern Gen_00C701C0Target TheBfmeObject_00C701C0;		// 0x12f4978
class Gen_00C701D0Target
{
public:
	void bfmeForward(void);					// retail 0x0003B304
};

extern Gen_00C701D0Target TheBfmeObject_00C701D0;		// 0x12f498c
class Gen_00C701E0Target
{
public:
	void bfmeForward(void);					// retail 0x0000D828
};

extern Gen_00C701E0Target TheBfmeObject_00C701E0;		// 0x12f49a0
class Gen_00C701F0Target
{
public:
	void bfmeForward(void);					// retail 0x0000D828
};

extern Gen_00C701F0Target TheBfmeObject_00C701F0;		// 0x12f4b00
class Gen_00C70500Target
{
public:
	void bfmeForward(void);					// retail 0x0000D828
};

extern Gen_00C70500Target TheBfmeObject_00C70500;		// 0x12f696c
class Gen_00C70510Target
{
public:
	void bfmeForward(void);					// retail 0x0000D828
};

extern Gen_00C70510Target TheBfmeObject_00C70510;		// 0x12f6960
class Gen_00C70610Target
{
public:
	void bfmeForward(void);					// retail 0x0000D828
};

extern Gen_00C70610Target TheBfmeObject_00C70610;		// 0x12f6ad4
class Gen_00C70620Target
{
public:
	void bfmeForward(void);					// retail 0x0000D828
};

extern Gen_00C70620Target TheBfmeObject_00C70620;		// 0x12f6ac8
class Gen_00C70640Target
{
public:
	void bfmeForward(void);					// retail 0x0000D828
};

extern Gen_00C70640Target TheBfmeObject_00C70640;		// 0x12f6aa4
class Gen_00C70650Target
{
public:
	void bfmeForward(void);					// retail 0x0000D828
};

extern Gen_00C70650Target TheBfmeObject_00C70650;		// 0x12f6a98
class Gen_00C70670Target
{
public:
	void bfmeForward(void);					// retail 0x0000D828
};

extern Gen_00C70670Target TheBfmeObject_00C70670;		// 0x12f6a74
class Gen_00C70680Target
{
public:
	void bfmeForward(void);					// retail 0x0000D828
};

extern Gen_00C70680Target TheBfmeObject_00C70680;		// 0x12f6a68
class Gen_00C706A0Target
{
public:
	void bfmeForward(void);					// retail 0x0000D828
};

extern Gen_00C706A0Target TheBfmeObject_00C706A0;		// 0x12f6a44
class Gen_00C706B0Target
{
public:
	void bfmeForward(void);					// retail 0x0000D828
};

extern Gen_00C706B0Target TheBfmeObject_00C706B0;		// 0x12f6a38
class Gen_00C706D0Target
{
public:
	void bfmeForward(void);					// retail 0x0000D828
};

extern Gen_00C706D0Target TheBfmeObject_00C706D0;		// 0x12f6a14
class Gen_00C706E0Target
{
public:
	void bfmeForward(void);					// retail 0x0000D828
};

extern Gen_00C706E0Target TheBfmeObject_00C706E0;		// 0x12f6a08
class Gen_00C708D0Target
{
public:
	void bfmeForward(void);					// retail 0x00011D5B
};

extern Gen_00C708D0Target TheBfmeObject_00C708D0;		// 0x12f7180
class Gen_00C70900Target
{
public:
	void bfmeForward(void);					// retail 0x0003B2B9
};

extern Gen_00C70900Target TheBfmeObject_00C70900;		// 0x12f7784
class Gen_00C70970Target
{
public:
	void bfmeForward(void);					// retail 0x0000D828
};

extern Gen_00C70970Target TheBfmeObject_00C70970;		// 0x12f8044
class Gen_00C709A0Target
{
public:
	void bfmeForward(void);					// retail 0x009DB450
};

extern Gen_00C709A0Target TheBfmeObject_00C709A0;		// 0x12f878c
class Gen_00C709B0Target
{
public:
	void bfmeForward(void);					// retail 0x009DB350
};

extern Gen_00C709B0Target TheBfmeObject_00C709B0;		// 0x12f9800
class Gen_00C709C0Target
{
public:
	void bfmeForward(void);					// retail 0x0003AC01
};

extern Gen_00C709C0Target TheBfmeObject_00C709C0;		// 0x12f9808
class Gen_00C70AB0Target
{
public:
	void bfmeForward(void);					// retail 0x00046BD2
};

extern Gen_00C70AB0Target TheBfmeObject_00C70AB0;		// 0x1306978
class Gen_00C70AD0Target
{
public:
	void bfmeForward(void);					// retail 0x0000F71D
};

extern Gen_00C70AD0Target TheBfmeObject_00C70AD0;		// 0x1306c6c
class Gen_00C70B00Target
{
public:
	void bfmeForward(void);					// retail 0x000461DC
};

extern Gen_00C70B00Target TheBfmeObject_00C70B00;		// 0x1306f3c
class Gen_00C70B10Target
{
public:
	void bfmeForward(void);					// retail 0x000461DC
};

extern Gen_00C70B10Target TheBfmeObject_00C70B10;		// 0x1306f54
class Gen_00C70B40Target
{
public:
	void bfmeForward(void);					// retail 0x00030652
};

extern Gen_00C70B40Target TheBfmeObject_00C70B40;		// 0x1307214
class Gen_00C70B50Target
{
public:
	void bfmeForward(void);					// retail 0x00044120
};

extern Gen_00C70B50Target TheBfmeObject_00C70B50;		// 0x1307228
class Gen_00C70B60Target
{
public:
	void bfmeForward(void);					// retail 0x0003BFE3
};

extern Gen_00C70B60Target TheBfmeObject_00C70B60;		// 0x1307284
class Gen_00C70B70Target
{
public:
	void bfmeForward(void);					// retail 0x0002DEA7
};

extern Gen_00C70B70Target TheBfmeObject_00C70B70;		// 0x13072b8
class Gen_00C70BA0Target
{
public:
	void bfmeForward(void);					// retail 0x000085B2
};

extern Gen_00C70BA0Target TheBfmeObject_00C70BA0;		// 0x1307348
class Gen_00C70BB0Target
{
public:
	void bfmeForward(void);					// retail 0x000179E0
};

extern Gen_00C70BB0Target TheBfmeObject_00C70BB0;		// 0x13073c0
class Gen_00C70BC0Target
{
public:
	void bfmeForward(void);					// retail 0x00023F92
};

extern Gen_00C70BC0Target TheBfmeObject_00C70BC0;		// 0x1309c18
class Gen_00C70BD0Target
{
public:
	void bfmeForward(void);					// retail 0x00832740
};

extern Gen_00C70BD0Target TheBfmeObject_00C70BD0;		// 0x130a451
class Gen_00C70BE0Target
{
public:
	void bfmeForward(void);					// retail 0x00843610
};

extern Gen_00C70BE0Target TheBfmeObject_00C70BE0;		// 0x130a450
class Gen_00C70C00Target
{
public:
	void bfmeForward(void);					// retail 0x0000EAFC
};

extern Gen_00C70C00Target TheBfmeObject_00C70C00;		// 0x130a45c
class Gen_00C70C70Target
{
public:
	void bfmeForward(void);					// retail 0x0081D040
};

extern Gen_00C70C70Target TheBfmeObject_00C70C70;		// 0x130b19c
class Gen_00C70C80Target
{
public:
	void bfmeForward(void);					// retail 0x00848AC0
};

extern Gen_00C70C80Target TheBfmeObject_00C70C80;		// 0x130bcac
class Gen_00C70CC0Target
{
public:
	void bfmeForward(void);					// retail 0x0001642D
};

extern Gen_00C70CC0Target TheBfmeObject_00C70CC0;		// 0x130bcb4
class Gen_00C70DD0Target
{
public:
	void bfmeForward(void);					// retail 0x0001642D
};

extern Gen_00C70DD0Target TheBfmeObject_00C70DD0;		// 0x130c098
class Gen_00C70DE0Target
{
public:
	void bfmeForward(void);					// retail 0x0001642D
};

extern Gen_00C70DE0Target TheBfmeObject_00C70DE0;		// 0x130c08c
class Gen_00C70DF0Target
{
public:
	void bfmeForward(void);					// retail 0x0001642D
};

extern Gen_00C70DF0Target TheBfmeObject_00C70DF0;		// 0x130c0a4
class Gen_00C70E00Target
{
public:
	void bfmeForward(void);					// retail 0x0003BE17
};

extern Gen_00C70E00Target TheBfmeObject_00C70E00;		// 0x130c080
class Gen_00C70E10Target
{
public:
	void bfmeForward(void);					// retail 0x0003BE17
};

extern Gen_00C70E10Target TheBfmeObject_00C70E10;		// 0x130c0b0
class Gen_00C70E20Target
{
public:
	void bfmeForward(void);					// retail 0x0001642D
};

extern Gen_00C70E20Target TheBfmeObject_00C70E20;		// 0x130c074
class Gen_00C70E30Target
{
public:
	void bfmeForward(void);					// retail 0x0001642D
};

extern Gen_00C70E30Target TheBfmeObject_00C70E30;		// 0x130c0c8
class Gen_00C70E40Target
{
public:
	void bfmeForward(void);					// retail 0x0003BE17
};

extern Gen_00C70E40Target TheBfmeObject_00C70E40;		// 0x130c0bc
class Gen_00C70E50Target
{
public:
	void bfmeForward(void);					// retail 0x00832740
};

extern Gen_00C70E50Target TheBfmeObject_00C70E50;		// 0x130c0d4
class Gen_00C70E60Target
{
public:
	void bfmeForward(void);					// retail 0x00853580
};

extern Gen_00C70E60Target TheBfmeObject_00C70E60;		// 0x130ce58
class Gen_00C70E80Target
{
public:
	void bfmeForward(void);					// retail 0x00887940
};

extern Gen_00C70E80Target TheBfmeObject_00C70E80;		// 0x12d4d04
class Gen_00C70F00Target
{
public:
	void bfmeForward(void);					// retail 0x0000D828
};

extern Gen_00C70F00Target TheBfmeObject_00C70F00;		// 0x1336e50
class Gen_00C70F10Target
{
public:
	void bfmeForward(void);					// retail 0x0003B304
};

extern Gen_00C70F10Target TheBfmeObject_00C70F10;		// 0x1336e54
class Gen_00C70F80Target
{
public:
	void bfmeForward(void);					// retail 0x008C6020
};

extern Gen_00C70F80Target TheBfmeObject_00C70F80;		// 0x1338748
class Gen_00C70FC0Target
{
public:
	void bfmeForward(void);					// retail 0x008FFF30
};

extern Gen_00C70FC0Target TheBfmeObject_00C70FC0;		// 0x133f468
class Gen_00C70FD0Target
{
public:
	void bfmeForward(void);					// retail 0x009035E0
};

extern Gen_00C70FD0Target TheBfmeObject_00C70FD0;		// 0x1340c50
class Gen_00C71000Target
{
public:
	void bfmeForward(void);					// retail 0x009035E0
};

extern Gen_00C71000Target TheBfmeObject_00C71000;		// 0x1340ec0
class Gen_00C71010Target
{
public:
	void bfmeForward(void);					// retail 0x0003A7B0
};

extern Gen_00C71010Target TheBfmeObject_00C71010;		// 0x13411d0
class Gen_00C71020Target
{
public:
	void bfmeForward(void);					// retail 0x0003A7B0
};

extern Gen_00C71020Target TheBfmeObject_00C71020;		// 0x1341130
class Gen_00C71030Target
{
public:
	void bfmeForward(void);					// retail 0x0090B5F0
};

extern Gen_00C71030Target TheBfmeObject_00C71030;		// 0x13405e8
class Gen_00C71060Target
{
public:
	void bfmeForward(void);					// retail 0x0090EA60
};

extern Gen_00C71060Target TheBfmeObject_00C71060;		// 0x13411f0
class Gen_00C712B0Target
{
public:
	void bfmeForward(void);					// retail 0x00960030
};

extern Gen_00C712B0Target TheBfmeObject_00C712B0;		// 0x13466c8
class Gen_00C712C0Target
{
public:
	void bfmeForward(void);					// retail 0x009DB7A0
};

extern Gen_00C712C0Target TheBfmeObject_00C712C0;		// 0x1346718
class Gen_00C712D0Target
{
public:
	void bfmeForward(void);					// retail 0x0092C5E0
};

extern Gen_00C712D0Target TheBfmeObject_00C712D0;		// 0x1346db0
class Gen_00C712E0Target
{
public:
	void bfmeForward(void);					// retail 0x000461DC
};

extern Gen_00C712E0Target TheBfmeObject_00C712E0;		// 0x1346dc0
class Gen_00C712F0Target
{
public:
	void bfmeForward(void);					// retail 0x00030652
};

extern Gen_00C712F0Target TheBfmeObject_00C712F0;		// 0x1346e70
class Gen_00C71300Target
{
public:
	void bfmeForward(void);					// retail 0x009DB7A0
};

extern Gen_00C71300Target TheBfmeObject_00C71300;		// 0x1346e74
class Gen_00C71310Target
{
public:
	void bfmeForward(void);					// retail 0x009380E0
};

extern Gen_00C71310Target TheBfmeObject_00C71310;		// 0x1346e78
class Gen_00C71460Target
{
public:
	void bfmeForward(void);					// retail 0x000461DC
};

extern Gen_00C71460Target TheBfmeObject_00C71460;		// 0x134b158
class Gen_00C71470Target
{
public:
	void bfmeForward(void);					// retail 0x000461DC
};

extern Gen_00C71470Target TheBfmeObject_00C71470;		// 0x134b170
class Gen_00C71480Target
{
public:
	void bfmeForward(void);					// retail 0x0094EA80
};

extern Gen_00C71480Target TheBfmeObject_00C71480;		// 0x134b188
class Gen_00C71490Target
{
public:
	void bfmeForward(void);					// retail 0x0094EAB0
};

extern Gen_00C71490Target TheBfmeObject_00C71490;		// 0x134b1a0
class Gen_00C714A0Target
{
public:
	void bfmeForward(void);					// retail 0x00960030
};

extern Gen_00C714A0Target TheBfmeObject_00C714A0;		// 0x134b1b8
class Gen_00C71550Target
{
public:
	void bfmeForward(void);					// retail 0x009DD640
};

extern Gen_00C71550Target TheBfmeObject_00C71550;		// 0x134ecf0
class Gen_00C71560Target
{
public:
	void bfmeForward(void);					// retail 0x009DB7A0
};

extern Gen_00C71560Target TheBfmeObject_00C71560;		// 0x134edfc
class Gen_00C71570Target
{
public:
	void bfmeForward(void);					// retail 0x009DB7A0
};

extern Gen_00C71570Target TheBfmeObject_00C71570;		// 0x134edf0
class Gen_00C71580Target
{
public:
	void bfmeForward(void);					// retail 0x009DB7A0
};

extern Gen_00C71580Target TheBfmeObject_00C71580;		// 0x134edf8

// ?bfmeForward_0005C450@@YAXXZ
void bfmeForward_0005C450(void)
{
	TheBfmeObject_0005C450.bfmeForward();
}
// ?bfmeForward_006D1870@@YAXXZ
void bfmeForward_006D1870(void)
{
	TheBfmeObject_006D1870.bfmeForward();
}
// ?bfmeForward_009372E0@@YAXXZ
void bfmeForward_009372E0(void)
{
	TheBfmeObject_009372E0.bfmeForward();
}
// ?bfmeForward_00C6FC80@@YAXXZ
void bfmeForward_00C6FC80(void)
{
	TheBfmeObject_00C6FC80.bfmeForward();
}
// ?bfmeForward_00C6FC90@@YAXXZ
void bfmeForward_00C6FC90(void)
{
	TheBfmeObject_00C6FC90.bfmeForward();
}
// ?bfmeForward_00C6FCA0@@YAXXZ
void bfmeForward_00C6FCA0(void)
{
	TheBfmeObject_00C6FCA0.bfmeForward();
}
// ?bfmeForward_00C6FCB0@@YAXXZ
void bfmeForward_00C6FCB0(void)
{
	TheBfmeObject_00C6FCB0.bfmeForward();
}
// ?bfmeForward_00C6FE10@@YAXXZ
void bfmeForward_00C6FE10(void)
{
	TheBfmeObject_00C6FE10.bfmeForward();
}
// ?bfmeForward_00C6FE50@@YAXXZ
void bfmeForward_00C6FE50(void)
{
	TheBfmeObject_00C6FE50.bfmeForward();
}
// ?bfmeForward_00C6FE70@@YAXXZ
void bfmeForward_00C6FE70(void)
{
	TheBfmeObject_00C6FE70.bfmeForward();
}
// ?bfmeForward_00C6FEF0@@YAXXZ
void bfmeForward_00C6FEF0(void)
{
	TheBfmeObject_00C6FEF0.bfmeForward();
}
// ?bfmeForward_00C6FF00@@YAXXZ
void bfmeForward_00C6FF00(void)
{
	TheBfmeObject_00C6FF00.bfmeForward();
}
// ?bfmeForward_00C6FF10@@YAXXZ
void bfmeForward_00C6FF10(void)
{
	TheBfmeObject_00C6FF10.bfmeForward();
}
// ?bfmeForward_00C6FF20@@YAXXZ
void bfmeForward_00C6FF20(void)
{
	TheBfmeObject_00C6FF20.bfmeForward();
}
// ?bfmeForward_00C6FF30@@YAXXZ
void bfmeForward_00C6FF30(void)
{
	TheBfmeObject_00C6FF30.bfmeForward();
}
// ?bfmeForward_00C6FF60@@YAXXZ
void bfmeForward_00C6FF60(void)
{
	TheBfmeObject_00C6FF60.bfmeForward();
}
// ?bfmeForward_00C6FFA0@@YAXXZ
void bfmeForward_00C6FFA0(void)
{
	TheBfmeObject_00C6FFA0.bfmeForward();
}
// ?bfmeForward_00C6FFC0@@YAXXZ
void bfmeForward_00C6FFC0(void)
{
	TheBfmeObject_00C6FFC0.bfmeForward();
}
// ?bfmeForward_00C6FFF0@@YAXXZ
void bfmeForward_00C6FFF0(void)
{
	TheBfmeObject_00C6FFF0.bfmeForward();
}
// ?bfmeForward_00C70000@@YAXXZ
void bfmeForward_00C70000(void)
{
	TheBfmeObject_00C70000.bfmeForward();
}
// ?bfmeForward_00C70010@@YAXXZ
void bfmeForward_00C70010(void)
{
	TheBfmeObject_00C70010.bfmeForward();
}
// ?bfmeForward_00C70020@@YAXXZ
void bfmeForward_00C70020(void)
{
	TheBfmeObject_00C70020.bfmeForward();
}
// ?bfmeForward_00C70030@@YAXXZ
void bfmeForward_00C70030(void)
{
	TheBfmeObject_00C70030.bfmeForward();
}
// ?bfmeForward_00C70070@@YAXXZ
void bfmeForward_00C70070(void)
{
	TheBfmeObject_00C70070.bfmeForward();
}
// ?bfmeForward_00C70080@@YAXXZ
void bfmeForward_00C70080(void)
{
	TheBfmeObject_00C70080.bfmeForward();
}
// ?bfmeForward_00C70090@@YAXXZ
void bfmeForward_00C70090(void)
{
	TheBfmeObject_00C70090.bfmeForward();
}
// ?bfmeForward_00C700A0@@YAXXZ
void bfmeForward_00C700A0(void)
{
	TheBfmeObject_00C700A0.bfmeForward();
}
// ?bfmeForward_00C700B0@@YAXXZ
void bfmeForward_00C700B0(void)
{
	TheBfmeObject_00C700B0.bfmeForward();
}
// ?bfmeForward_00C700C0@@YAXXZ
void bfmeForward_00C700C0(void)
{
	TheBfmeObject_00C700C0.bfmeForward();
}
// ?bfmeForward_00C700D0@@YAXXZ
void bfmeForward_00C700D0(void)
{
	TheBfmeObject_00C700D0.bfmeForward();
}
// ?bfmeForward_00C700E0@@YAXXZ
void bfmeForward_00C700E0(void)
{
	TheBfmeObject_00C700E0.bfmeForward();
}
// ?bfmeForward_00C70100@@YAXXZ
void bfmeForward_00C70100(void)
{
	TheBfmeObject_00C70100.bfmeForward();
}
// ?bfmeForward_00C70110@@YAXXZ
void bfmeForward_00C70110(void)
{
	TheBfmeObject_00C70110.bfmeForward();
}
// ?bfmeForward_00C70120@@YAXXZ
void bfmeForward_00C70120(void)
{
	TheBfmeObject_00C70120.bfmeForward();
}
// ?bfmeForward_00C70130@@YAXXZ
void bfmeForward_00C70130(void)
{
	TheBfmeObject_00C70130.bfmeForward();
}
// ?bfmeForward_00C70140@@YAXXZ
void bfmeForward_00C70140(void)
{
	TheBfmeObject_00C70140.bfmeForward();
}
// ?bfmeForward_00C70150@@YAXXZ
void bfmeForward_00C70150(void)
{
	TheBfmeObject_00C70150.bfmeForward();
}
// ?bfmeForward_00C70160@@YAXXZ
void bfmeForward_00C70160(void)
{
	TheBfmeObject_00C70160.bfmeForward();
}
// ?bfmeForward_00C70170@@YAXXZ
void bfmeForward_00C70170(void)
{
	TheBfmeObject_00C70170.bfmeForward();
}
// ?bfmeForward_00C70180@@YAXXZ
void bfmeForward_00C70180(void)
{
	TheBfmeObject_00C70180.bfmeForward();
}
// ?bfmeForward_00C70190@@YAXXZ
void bfmeForward_00C70190(void)
{
	TheBfmeObject_00C70190.bfmeForward();
}
// ?bfmeForward_00C701A0@@YAXXZ
void bfmeForward_00C701A0(void)
{
	TheBfmeObject_00C701A0.bfmeForward();
}
// ?bfmeForward_00C701B0@@YAXXZ
void bfmeForward_00C701B0(void)
{
	TheBfmeObject_00C701B0.bfmeForward();
}
// ?bfmeForward_00C701C0@@YAXXZ
void bfmeForward_00C701C0(void)
{
	TheBfmeObject_00C701C0.bfmeForward();
}
// ?bfmeForward_00C701D0@@YAXXZ
void bfmeForward_00C701D0(void)
{
	TheBfmeObject_00C701D0.bfmeForward();
}
// ?bfmeForward_00C701E0@@YAXXZ
void bfmeForward_00C701E0(void)
{
	TheBfmeObject_00C701E0.bfmeForward();
}
// ?bfmeForward_00C701F0@@YAXXZ
void bfmeForward_00C701F0(void)
{
	TheBfmeObject_00C701F0.bfmeForward();
}
// ?bfmeForward_00C70500@@YAXXZ
void bfmeForward_00C70500(void)
{
	TheBfmeObject_00C70500.bfmeForward();
}
// ?bfmeForward_00C70510@@YAXXZ
void bfmeForward_00C70510(void)
{
	TheBfmeObject_00C70510.bfmeForward();
}
// ?bfmeForward_00C70610@@YAXXZ
void bfmeForward_00C70610(void)
{
	TheBfmeObject_00C70610.bfmeForward();
}
// ?bfmeForward_00C70620@@YAXXZ
void bfmeForward_00C70620(void)
{
	TheBfmeObject_00C70620.bfmeForward();
}
// ?bfmeForward_00C70640@@YAXXZ
void bfmeForward_00C70640(void)
{
	TheBfmeObject_00C70640.bfmeForward();
}
// ?bfmeForward_00C70650@@YAXXZ
void bfmeForward_00C70650(void)
{
	TheBfmeObject_00C70650.bfmeForward();
}
// ?bfmeForward_00C70670@@YAXXZ
void bfmeForward_00C70670(void)
{
	TheBfmeObject_00C70670.bfmeForward();
}
// ?bfmeForward_00C70680@@YAXXZ
void bfmeForward_00C70680(void)
{
	TheBfmeObject_00C70680.bfmeForward();
}
// ?bfmeForward_00C706A0@@YAXXZ
void bfmeForward_00C706A0(void)
{
	TheBfmeObject_00C706A0.bfmeForward();
}
// ?bfmeForward_00C706B0@@YAXXZ
void bfmeForward_00C706B0(void)
{
	TheBfmeObject_00C706B0.bfmeForward();
}
// ?bfmeForward_00C706D0@@YAXXZ
void bfmeForward_00C706D0(void)
{
	TheBfmeObject_00C706D0.bfmeForward();
}
// ?bfmeForward_00C706E0@@YAXXZ
void bfmeForward_00C706E0(void)
{
	TheBfmeObject_00C706E0.bfmeForward();
}
// ?bfmeForward_00C708D0@@YAXXZ
void bfmeForward_00C708D0(void)
{
	TheBfmeObject_00C708D0.bfmeForward();
}
// ?bfmeForward_00C70900@@YAXXZ
void bfmeForward_00C70900(void)
{
	TheBfmeObject_00C70900.bfmeForward();
}
// ?bfmeForward_00C70970@@YAXXZ
void bfmeForward_00C70970(void)
{
	TheBfmeObject_00C70970.bfmeForward();
}
// ?bfmeForward_00C709A0@@YAXXZ
void bfmeForward_00C709A0(void)
{
	TheBfmeObject_00C709A0.bfmeForward();
}
// ?bfmeForward_00C709B0@@YAXXZ
void bfmeForward_00C709B0(void)
{
	TheBfmeObject_00C709B0.bfmeForward();
}
// ?bfmeForward_00C709C0@@YAXXZ
void bfmeForward_00C709C0(void)
{
	TheBfmeObject_00C709C0.bfmeForward();
}
// ?bfmeForward_00C70AB0@@YAXXZ
void bfmeForward_00C70AB0(void)
{
	TheBfmeObject_00C70AB0.bfmeForward();
}
// ?bfmeForward_00C70AD0@@YAXXZ
void bfmeForward_00C70AD0(void)
{
	TheBfmeObject_00C70AD0.bfmeForward();
}
// ?bfmeForward_00C70B00@@YAXXZ
void bfmeForward_00C70B00(void)
{
	TheBfmeObject_00C70B00.bfmeForward();
}
// ?bfmeForward_00C70B10@@YAXXZ
void bfmeForward_00C70B10(void)
{
	TheBfmeObject_00C70B10.bfmeForward();
}
// ?bfmeForward_00C70B40@@YAXXZ
void bfmeForward_00C70B40(void)
{
	TheBfmeObject_00C70B40.bfmeForward();
}
// ?bfmeForward_00C70B50@@YAXXZ
void bfmeForward_00C70B50(void)
{
	TheBfmeObject_00C70B50.bfmeForward();
}
// ?bfmeForward_00C70B60@@YAXXZ
void bfmeForward_00C70B60(void)
{
	TheBfmeObject_00C70B60.bfmeForward();
}
// ?bfmeForward_00C70B70@@YAXXZ
void bfmeForward_00C70B70(void)
{
	TheBfmeObject_00C70B70.bfmeForward();
}
// ?bfmeForward_00C70BA0@@YAXXZ
void bfmeForward_00C70BA0(void)
{
	TheBfmeObject_00C70BA0.bfmeForward();
}
// ?bfmeForward_00C70BB0@@YAXXZ
void bfmeForward_00C70BB0(void)
{
	TheBfmeObject_00C70BB0.bfmeForward();
}
// ?bfmeForward_00C70BC0@@YAXXZ
void bfmeForward_00C70BC0(void)
{
	TheBfmeObject_00C70BC0.bfmeForward();
}
// ?bfmeForward_00C70BD0@@YAXXZ
void bfmeForward_00C70BD0(void)
{
	TheBfmeObject_00C70BD0.bfmeForward();
}
// ?bfmeForward_00C70BE0@@YAXXZ
void bfmeForward_00C70BE0(void)
{
	TheBfmeObject_00C70BE0.bfmeForward();
}
// ?bfmeForward_00C70C00@@YAXXZ
void bfmeForward_00C70C00(void)
{
	TheBfmeObject_00C70C00.bfmeForward();
}
// ?bfmeForward_00C70C70@@YAXXZ
void bfmeForward_00C70C70(void)
{
	TheBfmeObject_00C70C70.bfmeForward();
}
// ?bfmeForward_00C70C80@@YAXXZ
void bfmeForward_00C70C80(void)
{
	TheBfmeObject_00C70C80.bfmeForward();
}
// ?bfmeForward_00C70CC0@@YAXXZ
void bfmeForward_00C70CC0(void)
{
	TheBfmeObject_00C70CC0.bfmeForward();
}
// ?bfmeForward_00C70DD0@@YAXXZ
void bfmeForward_00C70DD0(void)
{
	TheBfmeObject_00C70DD0.bfmeForward();
}
// ?bfmeForward_00C70DE0@@YAXXZ
void bfmeForward_00C70DE0(void)
{
	TheBfmeObject_00C70DE0.bfmeForward();
}
// ?bfmeForward_00C70DF0@@YAXXZ
void bfmeForward_00C70DF0(void)
{
	TheBfmeObject_00C70DF0.bfmeForward();
}
// ?bfmeForward_00C70E00@@YAXXZ
void bfmeForward_00C70E00(void)
{
	TheBfmeObject_00C70E00.bfmeForward();
}
// ?bfmeForward_00C70E10@@YAXXZ
void bfmeForward_00C70E10(void)
{
	TheBfmeObject_00C70E10.bfmeForward();
}
// ?bfmeForward_00C70E20@@YAXXZ
void bfmeForward_00C70E20(void)
{
	TheBfmeObject_00C70E20.bfmeForward();
}
// ?bfmeForward_00C70E30@@YAXXZ
void bfmeForward_00C70E30(void)
{
	TheBfmeObject_00C70E30.bfmeForward();
}
// ?bfmeForward_00C70E40@@YAXXZ
void bfmeForward_00C70E40(void)
{
	TheBfmeObject_00C70E40.bfmeForward();
}
// ?bfmeForward_00C70E50@@YAXXZ
void bfmeForward_00C70E50(void)
{
	TheBfmeObject_00C70E50.bfmeForward();
}
// ?bfmeForward_00C70E60@@YAXXZ
void bfmeForward_00C70E60(void)
{
	TheBfmeObject_00C70E60.bfmeForward();
}
// ?bfmeForward_00C70E80@@YAXXZ
void bfmeForward_00C70E80(void)
{
	TheBfmeObject_00C70E80.bfmeForward();
}
// ?bfmeForward_00C70F00@@YAXXZ
void bfmeForward_00C70F00(void)
{
	TheBfmeObject_00C70F00.bfmeForward();
}
// ?bfmeForward_00C70F10@@YAXXZ
void bfmeForward_00C70F10(void)
{
	TheBfmeObject_00C70F10.bfmeForward();
}
// ?bfmeForward_00C70F80@@YAXXZ
void bfmeForward_00C70F80(void)
{
	TheBfmeObject_00C70F80.bfmeForward();
}
// ?bfmeForward_00C70FC0@@YAXXZ
void bfmeForward_00C70FC0(void)
{
	TheBfmeObject_00C70FC0.bfmeForward();
}
// ?bfmeForward_00C70FD0@@YAXXZ
void bfmeForward_00C70FD0(void)
{
	TheBfmeObject_00C70FD0.bfmeForward();
}
// ?bfmeForward_00C71000@@YAXXZ
void bfmeForward_00C71000(void)
{
	TheBfmeObject_00C71000.bfmeForward();
}
// ?bfmeForward_00C71010@@YAXXZ
void bfmeForward_00C71010(void)
{
	TheBfmeObject_00C71010.bfmeForward();
}
// ?bfmeForward_00C71020@@YAXXZ
void bfmeForward_00C71020(void)
{
	TheBfmeObject_00C71020.bfmeForward();
}
// ?bfmeForward_00C71030@@YAXXZ
void bfmeForward_00C71030(void)
{
	TheBfmeObject_00C71030.bfmeForward();
}
// ?bfmeForward_00C71060@@YAXXZ
void bfmeForward_00C71060(void)
{
	TheBfmeObject_00C71060.bfmeForward();
}
// ?bfmeForward_00C712B0@@YAXXZ
void bfmeForward_00C712B0(void)
{
	TheBfmeObject_00C712B0.bfmeForward();
}
// ?bfmeForward_00C712C0@@YAXXZ
void bfmeForward_00C712C0(void)
{
	TheBfmeObject_00C712C0.bfmeForward();
}
// ?bfmeForward_00C712D0@@YAXXZ
void bfmeForward_00C712D0(void)
{
	TheBfmeObject_00C712D0.bfmeForward();
}
// ?bfmeForward_00C712E0@@YAXXZ
void bfmeForward_00C712E0(void)
{
	TheBfmeObject_00C712E0.bfmeForward();
}
// ?bfmeForward_00C712F0@@YAXXZ
void bfmeForward_00C712F0(void)
{
	TheBfmeObject_00C712F0.bfmeForward();
}
// ?bfmeForward_00C71300@@YAXXZ
void bfmeForward_00C71300(void)
{
	TheBfmeObject_00C71300.bfmeForward();
}
// ?bfmeForward_00C71310@@YAXXZ
void bfmeForward_00C71310(void)
{
	TheBfmeObject_00C71310.bfmeForward();
}
// ?bfmeForward_00C71460@@YAXXZ
void bfmeForward_00C71460(void)
{
	TheBfmeObject_00C71460.bfmeForward();
}
// ?bfmeForward_00C71470@@YAXXZ
void bfmeForward_00C71470(void)
{
	TheBfmeObject_00C71470.bfmeForward();
}
// ?bfmeForward_00C71480@@YAXXZ
void bfmeForward_00C71480(void)
{
	TheBfmeObject_00C71480.bfmeForward();
}
// ?bfmeForward_00C71490@@YAXXZ
void bfmeForward_00C71490(void)
{
	TheBfmeObject_00C71490.bfmeForward();
}
// ?bfmeForward_00C714A0@@YAXXZ
void bfmeForward_00C714A0(void)
{
	TheBfmeObject_00C714A0.bfmeForward();
}
// ?bfmeForward_00C71550@@YAXXZ
void bfmeForward_00C71550(void)
{
	TheBfmeObject_00C71550.bfmeForward();
}
// ?bfmeForward_00C71560@@YAXXZ
void bfmeForward_00C71560(void)
{
	TheBfmeObject_00C71560.bfmeForward();
}
// ?bfmeForward_00C71570@@YAXXZ
void bfmeForward_00C71570(void)
{
	TheBfmeObject_00C71570.bfmeForward();
}
// ?bfmeForward_00C71580@@YAXXZ
void bfmeForward_00C71580(void)
{
	TheBfmeObject_00C71580.bfmeForward();
}
