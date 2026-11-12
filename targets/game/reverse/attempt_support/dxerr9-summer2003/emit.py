"""Reproduce private switch candidates from target evidence and the recorded donor."""
import argparse,collections,json,pathlib,re
ROOT=pathlib.Path(__file__).resolve().parents[5]

def source(suffix, flags, order, evidence_dir):
    data=json.loads((evidence_dir/('dxerr-'+suffix+'.json')).read_text())
    donor=(ROOT/'inputs/reference/open-bfme-2/Code/Libraries/Source/DirectX'/('dxerr'+suffix+'.cpp')).read_text()
    target={c['hr']:c for c in data['cases']}
    groups=[]; pending=[]
    for line in donor.splitlines():
        match=re.search(r'case (0x[0-9A-F]+):',line)
        if match: pending.append(int(match[1],16))
        if 'return ' in line and pending:
            present=[h for h in pending if h in target]
            for value in dict.fromkeys(target[h]['value'] for h in present):
                groups.append(([h for h in present if target[h]['value']==value],value))
            pending=[]
    seen={h for hrs,v in groups for h in hrs}
    extras=collections.defaultdict(list)
    for h,c in target.items():
        if h not in seen:extras[(c['origin'],c['value'])].append(h)
    for (origin,value),hrs in sorted(extras.items(),key=lambda item:min(item[1])):
        key=min(hrs)
        candidates=[(h,i) for i,(hs,v) in enumerate(groups) for h in hs if h>>16==key>>16 and h>key]
        index=min(candidates)[1] if candidates else len(groups)
        groups.insert(index,(hrs,value))
    if suffix.startswith('description') and order=='donor':
        retained=[]; d3drm=[]
        for group in groups:
            (d3drm if any(0x88760352<=h<=0x8876036C for h in group[0]) else retained).append(group)
        index=next(i for i,(hs,v) in enumerate(retained) if 0x88760866 in hs)+1
        groups=retained[:index]+sorted(d3drm,key=lambda g:min(g[0]))+retained[index:]
    if order=='origin':
        recovered=collections.defaultdict(list)
        for h,c in target.items(): recovered[(c['origin'],c['value'])].append(h)
        groups=[(hs,value) for (origin,value),hs in sorted(recovered.items())]
    if order=='numeric':groups.sort(key=lambda g:min(g[0]))
    assert {h for hrs,v in groups for h in hrs}==set(target)
    name='DXGetError'+('String' if suffix.startswith('string') else 'Description')+'9'+suffix[-1].upper()
    ctype='unsigned short' if data['wide'] else 'char'
    lines=['// cl: '+flags, 'extern "C" const '+ctype+'* __stdcall '+name+'(long hr)', '{', '    switch (hr)', '    {']
    prefix='L' if data['wide'] else ''
    for hrs,value in groups:
        if suffix.startswith('description') and value in ('Invalid flags', 'Invalid group'):
            for h in hrs:
                lines.append('    case 0x%08X:'%h)
                lines.append('        return '+prefix+json.dumps(value,ensure_ascii=True)+';')
        else:
            for h in hrs:lines.append('    case 0x%08X:'%h)
            lines.append('        return '+prefix+json.dumps(value,ensure_ascii=True)+';')
    lines+=['    default: return '+prefix+json.dumps(data['default'])+';', '    }','}','']
    return '\n'.join(lines)

if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-dir',type=pathlib.Path,required=True)
    parser.add_argument('--out-dir',type=pathlib.Path,required=True)
    args=parser.parse_args()
    args.out_dir.mkdir(parents=True,exist_ok=True)
    for suffix in ('stringa','stringw','descriptiona','descriptionw'):
        order='origin' if suffix.startswith('string') else 'donor'
        path=args.out_dir/('dxerr'+suffix+'.cpp')
        path.write_text(source(suffix,'/O1 /G6 /MT /DNDEBUG',order,args.evidence_dir))
        print(path)
