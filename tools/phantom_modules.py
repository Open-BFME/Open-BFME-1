#!/usr/bin/env python3
"""Which module classes the ledger names that BFME never shipped.

THE CLAIM AND WHAT BACKS IT. A module class is only reachable from INI if
ModuleFactory registers it, and the registration macro stringifies the class
identifier, so a shipped module class X necessarily puts the eight-to-forty
byte ASCII run "X" into the image. Two facts follow, and this tool reports
exactly those two, never an inference between them:

  ABSENT      the byte sequence of the class name occurs NOWHERE in
              lotrbfme.exe -- not as a literal, not inside a longer string, not
              anywhere in any section -- and Zero Hour registers a concrete
              module class of that name. BFME did not ship the class, so every
              ledger row naming it carries a borrowed Zero Hour name rather
              than an identity. This is a proof, not a search result.
  REGISTERED  targets/game/reverse/module_registry.tsv lists it. The class exists and the
              registry gives its two factory bodies.

and three states it deliberately refuses to decide:

  UNREGISTERED_NAMED  the name is in the image but no registration uses it:
              abstract bases (UpdateModule, DieModule) whose names appear as
              module-type tags, plus classes reached some other way. Nothing is
              proved either direction.
  UNDECIDED   the name is absent from the image AND Zero Hour does not register
              it either -- an abstract base or a plain struct. Such a class
              needs no literal even when it exists, so absence proves nothing.
  SUBSTRING   the name occurs only inside a longer run. Reported separately
              because a suffix hit is not a literal.

WHY NOT JUST READ THE STRING POOL. The module names are not one blob. The
literal for LockWeaponCreate sits at 0x00C8FD94 among thirty neighbours, but
ModelConditionSoundSelectorClientBehavior is at 0x00C8E57C and W3DTreeDraw at
0x00D1D234, thousands of bytes away in either direction. Scanning one window
would have called both of those absent. The whole file is the search space.

ABSENT IS NOT A LICENCE TO RETRACT, AND THE COUNTER-EXAMPLE IS IN THE TREE.
`??0TechBuildingBehaviorModuleData@@QAE@XZ` cleared every test above -- the name
is nowhere in the image, no registration builds one, no Zero Hour class derives
from it -- and retracting it was still wrong. tools/ctor_vtable.py reads the
vftable operand that build.py masks away, and it put that row in its CONFIRMED
bucket: the body at 0x0008A430 installs a vtable whose slot 0 the ledger also
calls TechBuildingBehaviorModuleData, while both rows left on the address are
CONTRADICTED by that same vtable. Positive evidence about a body outranks the
absence of a string, so --candidates refuses any row ctor_vtable confirms.

That screen only reaches constructors, which is all ctor_vtable classifies. The
other blockers are structural and are checked for every row: a retraction must
not unclaim an address, must not empty a source file, and must not remove the
one symbol naming a vtable on everyone else's behalf. None of this proves a
retraction safe by itself -- the last word is ./build.sh on the affected
sources, because a row can be load-bearing through a relocation from a sibling
row even when the class is fictional. Drop AnimationSteeringUpdate's ModuleData
destructor and the ??_G thunk beside it stops resolving its call.

  python3 tools/phantom_modules.py               # write targets/game/reverse/phantom_modules.tsv
  python3 tools/phantom_modules.py --rows        # list the affected ledger rows
  python3 tools/phantom_modules.py --candidates  # screen those rows for retraction
"""
import collections, csv, re, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build
import module_registry as reg

OUT = build.ROOT / 'targets/game/reverse/phantom_modules.tsv'
ZH_FACTORIES = [
    'inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/Thing/ModuleFactory.cpp',
    'inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/Common/Thing/W3DModuleFactory.cpp',
]
FACTORY_SYMBOL = re.compile(r'^\?(friend_newModuleInstance|friend_newModuleData)@([A-Za-z0-9_]+)@@')
MODULE_FACTORY_TU = 'game/GameEngine/Source/Common/Thing/ModuleFactory.cpp'
# Every '@'-terminated component of a mangled name. The class can be the LEADING
# one (??0X@@, ??1X@@, ??_GX@@) as easily as a qualifier between separators
# (?method@X@@), so the '@X@' spelling this used to search for cannot see a
# constructor or a destructor at all. That blind spot is why three phantom
# ModuleData constructors survived the initFromINIMultiProc pass, and why the
# affected-row count was under-reported by more than half -- 84 rows across 33
# classes where the true figure was 197 across 48. --candidates prints the live
# count rather than trusting any number written here. Junk components ('QAE',
# type codes) match too and are harmless: they are only ever looked up in a set
# of known class names.
NAMED = re.compile(r'([A-Za-z_][A-Za-z0-9_]*)@')
# `??_G`, `??_E`, `??0`, `??1` and friends. The operator code has to come off
# first: '_' opens an identifier, so scanning `??_GFooModuleData@@` straight
# yields `_GFooModuleData` and the class is missed exactly as if the whole
# pattern were wrong. Vector deleting destructors are the family that names a
# vtable for everyone else, so losing them loses the sole-attester screen.
OPERATOR = re.compile(r'^\?\?(?:_[A-Za-z0-9]|[0-9A-Z])')
MODULE_DATA = 'ModuleData'
RVA_COLUMN_CAP = 12
# The tree's spellings for 'not identified yet' name no class, so they can
# neither be confirmed nor contradicted here.
PLACEHOLDER = re.compile(r'^(Gen_|Rva[0-9A-F]{8}|Bfme|BFME)')
DATA = reg.DATA


def zh_registry():
    names = set()
    pat = re.compile(r'addModule[A-Za-z]*\(\s*([A-Za-z0-9_]+)\s*\)')
    for rel in ZH_FACTORIES:
        path = build.ROOT / rel
        if not path.exists():
            raise SystemExit(f"missing Zero Hour reference {rel}; it is the oracle for 'concrete module class'")
        names |= set(pat.findall(path.read_text(encoding='utf-8', errors='replace')))
    return names


def occurrences(name):
    """Count every occurrence of the raw byte sequence, and of a NUL-terminated
    run exactly equal to it, anywhere in the file."""
    raw = name.encode()
    total = terminated = 0
    i = DATA.find(raw)
    while i >= 0:
        total += 1
        if DATA[i + len(raw)] == 0:
            terminated += 1
        i = DATA.find(raw, i + 1)
    return total, terminated


def stem(cls):
    """A ModuleData class registers under the class it belongs to."""
    return cls[:-len(MODULE_DATA)] if cls.endswith(MODULE_DATA) and len(cls) > len(MODULE_DATA) else cls


def components(name):
    """Every class a mangled name could be naming, ModuleData already folded."""
    return {stem(c) for c in NAMED.findall(OPERATOR.sub('', name, count=1))}


def discover_classes(rows):
    """The classes to put a verdict on: every one the ledger names through a
    module-factory symbol, plus every one named by a row placed in the ZH
    ModuleFactory translation unit.

    Deliberately narrow. This decides WHICH classes get judged, so widening it
    would drag every template parameter in the ledger into the tally; finding a
    judged class's rows is rows_naming's job and is not narrow at all.
    """
    out = set()
    qualifier = re.compile(r'@([A-Za-z0-9_]+)@@')
    for r in rows:
        m = FACTORY_SYMBOL.match(r['name'])
        if m:
            if not PLACEHOLDER.match(m.group(2)):
                out.add(m.group(2))
        elif r['source'] == MODULE_FACTORY_TU and '$' not in r['name']:
            # '$' means a template mangling, whose qualifier fragments
            # (PAUFXBoneInfo, W4NameKeyType) are type codes, not class names.
            for q in qualifier.finditer(r['name']):
                c = q.group(1)
                if c[0].isupper() and not PLACEHOLDER.match(c):
                    out.add(c)
                    break
    return out


def rows_naming(rows, classes):
    """{class: [row]} for every ledger row that names one of `classes`.

    A row is attributed to a class when any '@'-terminated component of its
    mangled name is that class, or is that class's ModuleData. Nested types
    count -- `?begin@?$vector@UDetonatorInfo@MinefieldBehavior@@...` is a claim
    about MinefieldBehavior whatever else it is about.
    """
    out = collections.defaultdict(list)
    for r in rows:
        for c in sorted(components(r['name']) & classes):
            out[c].append(r)
    return out


def classify():
    rows = reg.ledger_rows()
    table = reg.build_table()
    registered = {r['name'] for r in table}
    zh = zh_registry()
    universe = discover_classes(rows) | zh
    owned = rows_naming(rows, {stem(c) for c in universe})

    verdicts = {}
    for cls in universe:
        base = stem(cls)
        rs = owned.get(base, [])
        total, terminated = occurrences(base)
        if base in registered:
            v = 'REGISTERED'
        elif total == 0 and base in zh:
            v = 'ABSENT'
        elif total == 0:
            v = 'UNDECIDED'
        elif terminated:
            v = 'UNREGISTERED_NAMED'
        else:
            v = 'SUBSTRING'
        verdicts[cls] = dict(verdict=v, stem=base, occurrences=total, terminated=terminated,
                             zh=base in zh, rows=rs)
    return table, verdicts


def vtable_confirmed():
    """(row names, class stems) tools/ctor_vtable.py backs with vtable evidence.

    The fifth proof, in the two strengths it comes in. build.py masks the
    vftable operand, so these constructors look identical to every other
    constructor of their shape; ctor_vtable reads that operand instead and comes
    back with positive evidence a masked byte comparison cannot see.

    By NAME is evidence about one body: this constructor installs a vtable the
    ledger names for this very class, so the row is right and retracting it
    deletes a true identity. By CLASS is weaker but decides just as much here:
    somewhere in the image a constructor installs a vtable naming this class, so
    the class is real whatever its rows say. A row naming a real class on the
    wrong bytes is a misplacement -- a different defect, whose fix is to move the
    row, not delete it -- so it must not be retracted as a phantom either.

    Constructors are all ctor_vtable classifies, so a row absent from the name
    set is unevidenced rather than cleared; the class set is what carries the
    verdict over to a class's non-constructor rows.
    """
    import ctor_vtable as V
    names, classes = set(), set()
    for f in V.scan():
        if f.verdict == V.CONFIRMED:
            names.add(f.name)
            classes.add(stem(f.cls))
    return names, classes


def blockers(candidates, rows, confirmed, confirmed_classes):
    """{row name: [reason a retraction is unsafe]}, empty list meaning screened
    clean. `candidates` is every row this pass would retract, so emptiness is
    judged against the whole batch rather than one row at a time."""
    picked = {r['name'] for r in candidates}
    at_rva, in_src = collections.defaultdict(list), collections.defaultdict(list)
    for r in rows:
        at_rva[r['target_rva'].lower()].append(r)
        in_src[r['source']].append(r)
    import ctor_vtable as V
    out = {}
    for r in candidates:
        peers = at_rva[r['target_rva'].lower()]
        why = []
        if r['name'] in confirmed:
            why.append('vtable-confirmed: ctor_vtable says this body installs THIS class')
        else:
            real = sorted(components(r['name']) & confirmed_classes)
            if real:
                why.append('real-class: a constructor elsewhere installs a vtable naming %s, '
                           'so this row is misplaced, not phantom' % real[0])
        if len(peers) == 1:
            why.append('sole-claimant: retracting unclaims the address')
        elif all(p['name'] in picked for p in peers):
            why.append('all-claimants-picked: the batch would unclaim the address')
        if all(s['name'] in picked for s in in_src[r['source']]):
            why.append('empties-source: %s would be left with no rows' % r['source'])
        mine = V.attester_class(r['name'])
        if mine and len({V.attester_class(p['name']) for p in peers} - {None}) == 1:
            why.append('sole-attester: this address stops naming %s for other rows' % mine)
        out[r['name']] = why
    return out


def true_owner(table):
    inst = collections.defaultdict(set)
    data = collections.defaultdict(set)
    for r in table:
        inst[r['inst']].add(r['name'])
        data[r['data']].add(r['name'])
    return inst, data


def main():
    table, verdicts = classify()
    inst, data = true_owner(table)
    counts = collections.Counter(v['verdict'] for v in verdicts.values())
    print('  '.join(f"{k}={counts[k]}" for k in
                    ('REGISTERED', 'ABSENT', 'UNREGISTERED_NAMED', 'SUBSTRING', 'UNDECIDED')))

    if '--candidates' in sys.argv:
        absent = {c for c, v in verdicts.items() if v['verdict'] == 'ABSENT'}
        seen, candidates = set(), []
        for cls in sorted(absent):
            for r in verdicts[cls]['rows']:
                if r['name'] not in seen:
                    seen.add(r['name'])
                    candidates.append(r)
        rows = reg.ledger_rows()
        why = blockers(candidates, rows, *vtable_confirmed())
        clean = [r for r in candidates if not why[r['name']]]
        print(f"{len(candidates)} rows name an ABSENT class, across "
              f"{len({verdicts[c]['stem'] for c in absent if verdicts[c]['rows']})} classes")
        for r in sorted(candidates, key=lambda x: (bool(why[x['name']]), x['name'])):
            reasons = why[r['name']]
            print(f"{'BLOCKED' if reasons else 'screened'}  {r['target_rva']}  {r['name']}")
            print(f"          {r['source']}")
            for reason in reasons:
                print(f"          - {reason}")
        print(f"\n{len(clean)} screened clean, {len(candidates) - len(clean)} blocked.")
        print("Screened clean is not proven safe: run ./build.sh on every affected "
              "source before committing, because a row can anchor a sibling row's "
              "relocation even when its class is fictional.")
        return

    if '--rows' in sys.argv:
        for cls in sorted(c for c, v in verdicts.items() if v['verdict'] == 'ABSENT'):
            for r in sorted(verdicts[cls]['rows'], key=lambda x: x['target_rva']):
                m = FACTORY_SYMBOL.match(r['name'])
                owner = ''
                if m:
                    a = int(r['target_rva'], 16)
                    who = (inst if m.group(1).endswith('Instance') else data).get(a)
                    owner = '|'.join(sorted(who)) if who else ''
                print(f"{cls}\t{r['target_rva']}\t{r['target_size']}\t{r['status']}\t{owner}\t{r['name']}\t{r['source']}")
        return

    with open(OUT, 'w', newline='', encoding='utf-8') as f:
        w = csv.writer(f, delimiter='\t', lineterminator='\r\n')
        w.writerow(['class', 'verdict', 'registration_name', 'image_occurrences',
                    'nul_terminated_runs', 'zh_registers_it', 'ledger_rows', 'claimed_rvas'])
        for cls in sorted(verdicts):
            v = verdicts[cls]
            rvas = sorted({r['target_rva'] for r in v['rows']})
            # ledger_rows carries the real count; this column is a pointer, and
            # a class with a hundred addresses needs --rows, not a longer line.
            # Say so rather than truncating quietly.
            shown = ' '.join(rvas[:RVA_COLUMN_CAP])
            if len(rvas) > RVA_COLUMN_CAP:
                shown += ' +%d-more-see---rows' % (len(rvas) - RVA_COLUMN_CAP)
            w.writerow([cls, v['verdict'], v['stem'], v['occurrences'], v['terminated'],
                        'yes' if v['zh'] else 'no', len(v['rows']), shown])
    print(f"{OUT.relative_to(build.ROOT)}: {len(verdicts)} classes")


if __name__ == '__main__':
    main()
