# Generates getCommandTypeAsAsciiString from enum.json. Best form found (64% aligned, 2026-07-06):
# switch (for jump tables) + `AsciiString commandName;` default-construct then assign (drives the
# two-AsciiString EH prologue). Remaining divergence: RVO-return-slot 0-init scheduling at byte 25.
import json
m={int(k):v for k,v in json.load(open('reverse/whale_msgname/enum.json')).items()}
seen=set(); byval=[]
for v,name in sorted(m.items()):
    if name in seen: continue
    seen.add(name); byval.append((v,name))
elines='\n'.join(f"\t{name} = {v}," for v,name in byval if v!=0)
enum="enum Type {\n\tMSG_INVALID = 0,\n"+elines+"\n\tMSG_COUNT = 1900\n};"
open('src/game/message_stream.h','w').write('#pragma once\n#include "ascii_string.h"\nclass GameMessage {\npublic:\n\t'+enum.replace('\n','\n\t')+'\n\tAsciiString getCommandTypeAsAsciiString(Type t);\n};\n')
body=['// cl: /DNDEBUG /MD /EHsc','#include "message_stream.h"','','AsciiString GameMessage::getCommandTypeAsAsciiString(GameMessage::Type t)','{','\tAsciiString commandName;','\tcommandName = "UnknownMessage";','\tif (t >= GameMessage::MSG_COUNT) { commandName = "Invalid command"; }','\tswitch (t)','\t{']
for v,name in byval:
    if v!=0: body.append(f'\t\tcase {name}: return "{name}";')
body+=['\t}','\treturn commandName;','}']
open('src/game/message_stream.cpp','w').write('\n'.join(body)+'\n')
