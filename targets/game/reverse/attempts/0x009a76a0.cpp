// ?Rva009A76A0@@YAXPBEPAHIIIIPBH@Z
// partial score=0.9379 date=2026-09-30
// cl: /DNDEBUG /MD /O2
void __cdecl Rva009A76A0(
	const unsigned char *source,
	int *destination,
	unsigned sourcePitch,
	unsigned sourceDelta,
	unsigned rows,
	unsigned columns,
	const int *weights)
{
	unsigned row, column;
	for(row=0; row<rows; ++row) {
	 column=0;
	 if(columns>0) {
	 const unsigned char *previous=source-sourceDelta;
	 const unsigned char *next=source+sourceDelta;
	 do {
	  int value = next[sourceDelta]*weights[3] + source[0]*weights[1] + next[0]*weights[2] + previous[0]*weights[0];
	  value=(value+0x40)>>7;
	  if(value<0) value=0;
	  else if(value>255) value=255;
	  destination[column]=value;
	  ++source; ++next; ++previous; ++column;
	 } while(column<columns);
	 }
	 source+=sourcePitch-columns;
	 destination+=columns;
	}
}
