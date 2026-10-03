# Complete GameTextManager::getCSFInfo extent

Old47B claim ends inside virtual CALL [EDX+0C] at43617D. Retail and
independent Ghidra function creation prove121B, endingRET4 at4361C6
thenINT3. The GeneralsMD GameText.cpp twin names the same getCSFInfo
method: open a binary file, read24B CSFHeader, validate magic43534620,
copy label count, choose language based on version>=2, close, return success.

At the complete size the old source differs in exactly two bytes:
virtual read uses+10 instead of retail+0C; close uses+0C instead of+08.
All other121 bytes match after the genuine FileSystem::openFile relocation.
The source already has BFMEGameTextFileReadLayout for matched readLine and
getChar. Move that existing local ABI view before getCSFInfo, name its
previously unused slot2 close, and use it for both calls. The independent
matched CachedFileInputStream open/close in DataChunk.cpp likewise proves
close+08, and the ZH File declaration/twin supplies the semantic identities.
No shared File header, new type, or callee pin is required.

Local GameTextManager fields are already correct: count+08, language+7820.
Both offsets appear directly in the previously omitted retail tail. Keep
all header parsing and flag behavior unchanged. The full source gate must
verify all26 claims, including the existing users of the moved ABI view.
