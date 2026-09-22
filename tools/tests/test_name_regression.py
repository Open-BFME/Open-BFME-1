"""Historical identity survives an RVA bank move and an owner-name change."""
import json
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import name_regression as N

FIXTURES = Path(__file__).parent / 'fixtures/name_regression'
BEFORE = (FIXTURES / 'before.cpp').read_text()
AFTER = (FIXTURES / 'after.cpp').read_text()
BANK = 'reverse/attempts/0x00695e20.cpp'
CODE = 'Code/GameEngine/Source/Common/Rva00695E20LodGate.cpp'
EXPECTED = {
    ('GameLODManager', 'Rva00695E20LodView'),
    ('m_rowFlags', 'm_field174'),
    ('m_activeRow', 'm_field16CC'),
    ('m_lodSelector', 'm_fieldB60'),
}


def git(root, *args):
    return N.git(root, *args)


def put(root, path, text, stage=True):
    p = root / path
    p.parent.mkdir(parents=True, exist_ok=True)
    p.write_text(text)
    if stage:
        git(root, 'add', '--', path)


@pytest.fixture
def repo(tmp_path):
    git(tmp_path, 'init', '-q')
    git(tmp_path, 'config', 'user.name', 'Fixture')
    git(tmp_path, 'config', 'user.email', 'fixture@example.invalid')
    return tmp_path


def commit(root):
    git(root, 'commit', '-qm', 'fixture')
    return git(root, 'rev-parse', 'HEAD').strip()


def incident(root, keep_bank=False, path=CODE):
    put(root, BANK, BEFORE)
    old = commit(root)
    if not keep_bank:
        git(root, 'rm', '-q', BANK)
    put(root, path, AFTER)
    put(root, 'reverse/functions.csv', f'?check@Rva00695E20LodGate@@QBE_NXZ,,0x00695E20,54,{path},matched,evidence\n')
    return old


def test_exact_original_commit_fixture():
    assert set(N.regressions(BEFORE, AFTER)) == EXPECTED


@pytest.mark.parametrize('old,new', [
    ('GameLODManager', 'Rva00695E20LodView'),
    ('m_activeRow', 'm_field16CC'),
    ('calculateScore', 'sub_00123456'),
    ('calculateScore', 'Rva00123456'),
    ('m_pendingEvents', 'm_unk20'),
])
def test_descriptive_to_opaque_token_substitution(old, new):
    assert (old, new) in N.regressions(f'int {old}();', f'int {new}();')


def test_unknown_member_type_does_not_hide_simple_rename():
    a = 'class Known {\nUnknown m_events;\n};'
    b = a.replace('m_events', 'm_field20')
    assert N.regressions(a, b) == [('m_events', 'm_field20')]


def test_layout_catches_owner_and_field_despite_extra_body_changes():
    a = 'class Known {\nint m_events;\nint m_count;\n};'
    b = 'class Rva00123456 {\nint m_field0;\nint m_field4;\nvoid newlyAdded();\n};'
    assert set(N.regressions(a, b)) >= {('Known', 'Rva00123456'), ('m_events', 'm_field0'), ('m_count', 'm_field4')}


@pytest.mark.parametrize('before,after', [
    ('int m_count;', 'int m_total;'),
    ('float m_viewAngle;', 'float m_fieldOfView;'),
    ('int m_count;', 'int m_reservedCapacity;'),
    ('int m_identifier;', 'int m_id;'),
    ('int m_field0;', 'int m_field4;'),
    ('int m_field0;', 'int m_count;'),
    ('', 'class Rva00123456 { int m_field0; };'),
    ('// Known m_count\nint x;', '// Rva00123456 m_field0\nint x;'),
    ('const char *s = "Known";', 'const char *s = "Rva00123456";'),
    ('/* class Known { int m_count; }; */', '/* class Rva00123456 { int m_field0; }; */'),
    ('int m_count;', ''),
    ('int m_4;', 'int m_pad;'),
    ('int m_bfmeXEQ;', 'int m_x;'),
    ('UnsignedShort m_value;', 'Rva00123456ShortField m_value;'),
])
def test_no_regression_for_preservation_improvement_or_unrelated_changes(before, after):
    assert N.regressions(before, after) == []


def test_old_names_in_comments_do_not_hide_regression():
    assert set(N.regressions(BEFORE, AFTER + '\n// GameLODManager m_activeRow m_rowFlags m_lodSelector\n')) == EXPECTED


def test_staged_bank_move(repo):
    incident(repo)
    findings, accepted = N.check(repo, 'HEAD', ':')
    assert {(f.old_name, f.new_name) for f in findings} == EXPECTED
    assert all(f.old_path == BANK and f.new_path == CODE for f in findings)
    assert accepted == 0


def test_bank_need_not_be_deleted_and_filename_need_not_have_rva(repo):
    incident(repo, keep_bank=True, path='Code/LodGate.cpp')
    findings, _ = N.check(repo, 'HEAD', ':')
    assert {(f.old_name, f.new_name) for f in findings} == EXPECTED


def test_worktree_fix_does_not_hide_staged_regression(repo):
    incident(repo)
    put(repo, CODE, BEFORE, stage=False)
    assert len(N.check(repo, 'HEAD', ':')[0]) == 4


def test_unstaged_regression_does_not_change_clean_index(repo):
    incident(repo)
    put(repo, CODE, BEFORE)
    put(repo, CODE, AFTER, stage=False)
    assert N.check(repo, 'HEAD', ':')[0] == []


def test_committed_range_reads_snapshots_not_worktree(repo):
    old = incident(repo)
    new = commit(repo)
    put(repo, CODE, BEFORE, stage=False)
    assert len(N.check(repo, old, new)[0]) == 4


def test_same_path_change_without_rva_or_ledger(repo):
    put(repo, 'Code/Named.cpp', BEFORE)
    commit(repo)
    put(repo, 'Code/Named.cpp', AFTER)
    assert len(N.check(repo, 'HEAD', ':')[0]) == 4


def test_git_move_without_rva_or_ledger(repo):
    put(repo, 'Code/Old.cpp', BEFORE)
    commit(repo)
    git(repo, 'rm', '-q', 'Code/Old.cpp')
    put(repo, 'Code/New.cpp', BEFORE.replace('m_lodSelector', 'm_fieldB60'))
    findings, _ = N.check(repo, 'HEAD', ':')
    assert [(f.old_name, f.new_name) for f in findings] == [('m_lodSelector', 'm_fieldB60')]


def correction(repo, finding, **changes):
    entry = dict(vars(finding), evidence='docs/identity.md', reason='Independent caller contradicts the old owner; see the decoded call in identity.md.')
    entry.update(changes)
    put(repo, 'docs/identity.md', 'Fixture: independently decoded target differs from the old identity.\n')
    put(repo, N.CORRECTIONS, json.dumps([entry]))


def test_documented_correction_is_exact_and_does_not_exempt_other_names(repo):
    incident(repo)
    finding = N.check(repo, 'HEAD', ':')[0][0]
    correction(repo, finding)
    remaining, accepted = N.check(repo, 'HEAD', ':')
    assert len(remaining) == 3 and accepted == 1
    assert finding not in remaining
    put(repo, CODE, AFTER + '\n// changed snapshot\n')
    assert len(N.check(repo, 'HEAD', ':')[0]) == 4


@pytest.mark.parametrize('changes', [{'reason': ''}, {'reason': None}, {'evidence': None}, {'evidence': 'docs/missing.md'}, {'evidence': '/tmp/evidence'}])
def test_correction_requires_tracked_evidence_and_reason(repo, changes):
    incident(repo)
    correction(repo, N.check(repo, 'HEAD', ':')[0][0], **changes)
    with pytest.raises(ValueError, match='evidence and a reason'):
        N.check(repo, 'HEAD', ':')


def test_unstaged_evidence_is_not_accepted(repo):
    incident(repo)
    correction(repo, N.check(repo, 'HEAD', ':')[0][0])
    git(repo, 'rm', '--cached', 'docs/identity.md')
    with pytest.raises(ValueError, match='evidence and a reason'):
        N.check(repo, 'HEAD', ':')


def test_non_source_files_do_not_trigger_name_regressions(repo):
    put(repo, 'docs/example.cpp', BEFORE)
    commit(repo)
    put(repo, 'docs/example.cpp', AFTER)
    assert N.check(repo, 'HEAD', ':') == ([], 0)


def test_invalid_correction_file_fails_closed(repo):
    incident(repo)
    put(repo, N.CORRECTIONS, '{}')
    with pytest.raises(ValueError, match='must contain a list'):
        N.check(repo, 'HEAD', ':')


def test_cli_failure_and_success(repo, monkeypatch, capsys):
    incident(repo)
    monkeypatch.setattr(N, 'ROOT', repo)
    assert N.main(['HEAD', ':']) == 1
    assert '4 descriptive-to-placeholder' in capsys.readouterr().out
    put(repo, CODE, BEFORE)
    assert N.main(['HEAD', ':']) == 0


def test_restore_is_not_a_regression():
    restored = AFTER.replace('Rva00695E20LodView', 'GameLODManager').replace('m_field174', 'm_rowFlags').replace('m_field16CC', 'm_activeRow').replace('m_fieldB60', 'm_lodSelector')
    assert N.regressions(AFTER, restored) == []


def test_rva_ledger_link_between_semantic_paths(repo):
    old_path, new_path = 'Code/Named.cpp', 'Code/Moved.cpp'
    put(repo, old_path, BEFORE)
    put(repo, 'reverse/functions.csv', f'?check@@YAXXZ,,0x00695E20,54,{old_path},matched,evidence\n')
    commit(repo)
    git(repo, 'rm', '-q', old_path)
    put(repo, new_path, AFTER)
    put(repo, 'reverse/functions.csv', f'?check@@YAXXZ,,0x00695E20,54,{new_path},matched,evidence\n')
    assert len(N.check(repo, 'HEAD', ':')[0]) == 4


def test_source_path_with_spaces(repo):
    path = 'Code/Space In Name.cpp'
    put(repo, path, BEFORE)
    commit(repo)
    put(repo, path, AFTER)
    assert len(N.check(repo, 'HEAD', ':')[0]) == 4


@pytest.mark.parametrize('path', ['Code/Owner.cxx', 'Code/Owner.cc', 'Code/Owner.hh', 'reference/shims/Owner.h'])
def test_authored_source_and_shim_suffixes(repo, path):
    put(repo, path, BEFORE)
    commit(repo)
    put(repo, path, AFTER)
    assert len(N.check(repo, 'HEAD', ':')[0]) == 4


HOOKS = Path(__file__).resolve().parents[2] / '.githooks'


def hook_fixture(repo):
    # Unrelated gates are inert; run the real hook to verify that it refuses
    # unreviewed checker code even if that local checker would return success.
    for tool in ('name_regression', 'name_oracle', 'check_case_collisions',
                 'conversion_gate', 'check_csv', 'retired_guard'):
        put(repo, f'tools/{tool}.py', 'raise SystemExit(0)\n')
    put(repo, 'Code/Names.cpp', BEFORE)
    return commit(repo)


def run_hook(repo, hook, old):
    head = git(repo, 'rev-parse', 'HEAD').strip()
    refs = f'refs/heads/main {head} refs/heads/main {old}\n' if hook == 'pre-push' else ''
    return subprocess.run(['bash', str(HOOKS / hook)], cwd=repo,
                          input=refs, text=True, capture_output=True)


@pytest.mark.parametrize('hook', ['pre-commit', 'pre-push'])
@pytest.mark.parametrize('checker', ['name_regression', 'name_oracle'])
def test_real_hooks_refuse_unstaged_checker_changes(repo, hook, checker):
    old = hook_fixture(repo)
    put(repo, 'Code/Names.cpp', AFTER)
    if hook == 'pre-push':
        commit(repo)
    put(repo, f'tools/{checker}.py', 'raise SystemExit(0)  # unreviewed\n', stage=False)
    result = run_hook(repo, hook, old)
    assert result.returncode != 0
    assert 'name checker differs from' in result.stderr
    assert f'tools/{checker}.py' in result.stderr


@pytest.mark.parametrize('hook', ['pre-commit', 'pre-push'])
def test_real_hooks_refuse_an_untracked_checker(repo, hook):
    old = hook_fixture(repo)
    git(repo, 'rm', '--cached', 'tools/name_regression.py')
    put(repo, 'Code/Names.cpp', AFTER)
    if hook == 'pre-push':
        commit(repo)
    result = run_hook(repo, hook, old)
    assert result.returncode != 0
    assert 'name checker differs from' in result.stderr


def test_real_commit_hook_allows_checker_matching_index(repo):
    old = hook_fixture(repo)
    put(repo, 'docs/change.md', 'Unrelated documentation.\n')
    result = run_hook(repo, 'pre-commit', old)
    assert result.returncode == 0, result.stdout + result.stderr


def test_reordered_retained_class_is_not_renamed_to_added_namespace():
    before = """
    class Logic {
    public:
        int find(int);
     };
     extern Logic *global;
    
    class Thing {
    public:
        char m_head[0x74];
     int m_identifier;
     };
    
    class Host {
    public:
        void run(Thing *thing);
     char m_head[8];
     int *m_object;
     char m_middle[0x14];
     int m_identifier;
     };
    
    void Host::run(Thing *thing) { int old = m_identifier;
     if(old) { int result = global->find(old);
     if (!result) m_identifier=0;
     } if(thing) { m_identifier=thing->m_identifier;
     notify(m_object);
     send(m_object);
     } }
    """
    after = """
    class Thing {
    public:
        void forward(int *m_object);
     char m_head[0x74];
     int m_identifier;
     };
    
    class Logic {
    public:
        int find(int);
     };
     extern Logic *global;
    
    namespace Rva00256AE0 {
    class Host {
    public:
        void run(Thing *thing);
     char m_head[8];
     int *m_object;
     char m_middle[0x14];
     int m_identifier;
     };
    
    void Host::run(Thing *thing) { int old = m_identifier;
     if(old) { int result = global->find(old);
     if (!result) m_identifier=0;
     } if(thing) { m_identifier=thing->m_identifier;
     thing->forward(m_object);
     send(m_object);
     } }
    }
    """
    assert N.regressions(before, after) == []
    # Keeping the type does not exempt a real member-name regression.
    changed = after.replace('int m_identifier;', 'int m_at74;', 1)
    assert ('m_identifier', 'm_at74') in N.regressions(before, changed)


def test_forward_declaration_does_not_preserve_renamed_type():
    before = 'class Thing {\nint m_count;\n};'
    after = 'class Thing;\nnamespace Rva00123456 {\nclass Rva00123456Type {\nint m_count;\n};\n}'
    assert ('Thing', 'Rva00123456Type') in N.regressions(before, after)


def test_retained_class_spelling_does_not_hide_unrelated_method_rename():
    before = """
    class BfmeThingESN { public: int m_bfme74ESN; };
    class BfmeHostESN {
    public:
        void BfmeThingESN();
    };
    void BfmeHostESN::BfmeThingESN() {}
    """
    after = """
    class BfmeThingESN { public: int m_bfme74ESN; };
    namespace Rva00256AE0 {
    class BfmeHostESN {
    public:
        void Rva00256AE0();
    };
    void BfmeHostESN::Rva00256AE0() {}
    }
    """
    assert ('BfmeThingESN', 'Rva00256AE0') in N.regressions(before, after)


@pytest.mark.parametrize('spelling', ['__declspec', '_declspec'])
@pytest.mark.parametrize('attribute', ['naked', 'noinline', 'novtable'])
def test_compiler_attribute_is_not_a_name_lost_during_conversion(spelling, attribute):
    before = f'{spelling}({attribute}) void d_004af520() {{ __asm {{ ret }} }}'
    after = 'typedef char Check[sizeof(Rva00344C50CounterMap) == 12 ? 1 : -1];'
    assert N.regressions(before, after) == []


def test_attribute_spelling_does_not_exempt_an_actual_function_name():
    before = '__declspec(naked) void generated() {}\nvoid naked() {}'
    after = '__declspec(naked) void generated() {}\nvoid Rva00123456() {}'
    assert ('naked', 'Rva00123456') in N.regressions(before, after)


def test_attribute_does_not_exempt_the_function_it_annotates():
    before = '__declspec(naked) void calculateScore() {}'
    after = '__declspec(naked) void Rva00123456() {}'
    assert ('calculateScore', 'Rva00123456') in N.regressions(before, after)
