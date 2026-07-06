import json
wl=json.load(open('reverse/scriptengine_actions_worklist.json'))
def esc(s):
    return '"'+s.replace('\\','\\\\').replace('"','\\"').replace('\n','\\n').replace('\t','\\t')+'"'
out=['// cl: /DNDEBUG /MD /EHsc','#include "script_engine.h"','',
     'void ScriptEngine::init(void)','{','\tTemplate *curTemplate;']
for r in wl:
    if not r['internalName'] or r['uiName'] is None: continue   # skip the 11 unclean for now
    out.append(f"\tcurTemplate = &m_actionTemplates[{r['i']}];")
    out.append(f"\tcurTemplate->m_internalName = {esc(r['internalName'])};")
    out.append(f"\tcurTemplate->m_uiName = {esc(r['uiName'])};")
    out.append(f"\tcurTemplate->m_numParameters = {r['numParameters']};")
    for k,p in enumerate(r['parameters']):
        out.append(f"\tcurTemplate->m_parameters[{k}] = {p};")
    out.append(f"\tcurTemplate->m_numUiStrings = {r['numUiStrings']};")
    for k,s in enumerate(r['uiStrings']):
        if s is not None: out.append(f"\tcurTemplate->m_uiStrings[{k}] = {esc(s)};")
out.append('}')
open('src/game/script_engine.cpp','w').write('\n'.join(out)+'\n')
print(f"generated {len([r for r in wl if r['internalName'] and r['uiName'] is not None])} template blocks")
