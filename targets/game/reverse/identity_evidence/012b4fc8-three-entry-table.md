# Three entries at VA 012B4FC8

The matched getter at RVA 00746DE0 and setter at 00746DA0 index the
same VA 012B4FC8 in 16-byte steps and access the first three DWORDs.
Rva0074A680ParserRegistration::ParseLightingDataChunk (RVA 00747FF0) independently writes three
float components to each of VA 012B4FC8, 012B4FD8, and 012B4FE8.
The corresponding independently recorded DIR32 names are
Value012B4FC8, Value012B4FD8, and Value012B4FE8. The highlight-filter
postRender body at 007D7040 reads the same indexed 16-byte records.

Retail contains exactly three repetitions of DWORDs 3F000000,
3F000000, 3F000000, 00000000 in these 48 bytes. The next datum begins
at VA 012B4FF8: g_bfmeDefaultCU, independently named by the matched
reset at RVA 00421DE0, which copies the entire 36-byte block. It is not part of this table.
The three witnessed entry addresses and distinct following datum
bound the complete 48-byte table. The existing BfmeEntryFA view has
four public DWORD fields and sizeof 16, with no initialization code.
Its semantic field identities remain opaque.

Define the existing g_bfmeTableFA symbol as the complete mutable array;
keep the witnessed DWORD bit patterns instead of changing the caller
view or introducing any pin, alias, address global, or DIR32 record.
