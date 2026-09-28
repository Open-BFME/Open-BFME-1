"""Deterministic router tests; fake CLI launches real processes, never inference."""
import copy
import io
import json
import os
from pathlib import Path
import signal
import sqlite3
import subprocess
import sys
import tempfile
import time
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import opencode_router as r
from test_opencode_go_budget import payload

FAKE = '''#!/usr/bin/env python3
import json,os,sys,time,subprocess
from pathlib import Path
if '--version' in sys.argv:
 print('opencode v2.0.18'); sys.exit()
assert os.environ.get('PWD') == str(Path.cwd()), 'OpenCode location would use wrong PWD'
model=sys.argv[sys.argv.index('--model')+1]
Path('selected-model.txt').write_text(model)
base=model.split('#')[0]
prompt=sys.stdin.read()
Path('received.txt').write_text(prompt)
print(json.dumps({'type':'step_start','sessionID':'fixture-session'}),flush=True)
if 'DETACH' in prompt:
 child=subprocess.Popen([sys.executable,'-c','import time;time.sleep(30)'],start_new_session=True)
 Path('detached.pid').write_text(str(child.pid))
if 'SLOW' in prompt: time.sleep(20)
if 'BADVARIANT' in prompt and model.endswith('#medium'):
 print(json.dumps({'type':'error','error':{'type':'model.variant-unavailable','message':'Variant unavailable for '+model}}),flush=True)
elif base.endswith('/quota'):
 print(json.dumps({'type':'error','error':{'status':429,'message':'usage limit reached'}}),flush=True)
 time.sleep(20) # router must interrupt internal retries immediately
elif 'FAIL_FIRST' in prompt and '"model":' not in prompt:
 print(json.dumps({'type':'text','part':{'text':'ROUTER_RESULT '+json.dumps({'outcome':'failure','approaches':['change register lifetime'],'files_touched':['body.cpp'],'remaining_byte_differences':['+0x20 eax/ecx'],'discoveries':['callee ABI proven']})}}),flush=True)
else:
 time.sleep(.25)
 print(json.dumps({'type':'text','part':{'text':'ROUTER_RESULT '+json.dumps({'outcome':'success','summary':'fixture completed'})}}),flush=True)
'''


@unittest.skipUnless(sys.platform.startswith('linux'), 'Linux process groups')
class RouterTests(unittest.TestCase):
    def setUp(self):
        try:
            probe = r.fleet_cgroup.CgroupV2Unit.create('router-test-' + r.uuid.uuid4().hex)
            probe.remove()
        except r.fleet_cgroup.ContainmentUnavailable as exc:
            self.skipTest(str(exc))
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        for args in (('init', '-q'), ('config', 'user.name', 'fixture'),
                     ('config', 'user.email', 'fixture@example.invalid'),
                     ('commit', '--allow-empty', '-qm', 'submission')):
            subprocess.run(['git', *args], cwd=self.root, check=True, capture_output=True)
        self.state = self.root / 'state'
        self.fake = self.root / 'opencode'
        self.fake.write_text(FAKE)
        self.fake.chmod(0o755)
        self.c = r.config(r.DEFAULT_CONFIG)
        self.c.update(cost_aware=False, opencode=str(self.fake), go_overage_disabled=True, timeout=3,
                      cooldown=.3, failure_cooldown=.05, workers=3, variant_discovery=False)
        self.c['models'] = [self.model('one'), self.model('two'), self.model('strong','escalation')]
        with r.go_budget.database(self.state) as db:
            r.go_budget.write(db, dict(windows=r.go_budget.parse_usage(payload(reset=time.time()+10000)),
                observed_at=time.time(), next_refresh=time.time()+10000))
        with r.database(self.state) as db:
            db.execute('INSERT INTO settings VALUES (?,?)', ('claims_root', str(self.root)))

    def model(self, name, tier='bulk', **kw):
        return dict(id='opencode-go/'+name, tier=tier, enabled=True, concurrency=1, reserve=0, weight=1, **kw)

    def job(self, text='test', **kwargs):
        cwd = self.root / ('cwd-'+str(time.time_ns()))
        cwd.mkdir()
        return r.enqueue(self.state, 'bulk', text, cwd=cwd, **kwargs)

    def rows(self, table):
        with r.database(self.state) as db:
            return [dict(row) for row in db.execute('SELECT * FROM '+table)]

    def run_fleet(self, duration=5):
        return r.fleet(self.root, self.state, self.c, duration)

    def recover_usage(self):
        with r.go_budget.database(self.state) as db:
            cache = r.go_budget.read(db)
            cache['next_refresh'] = 0
            r.go_budget.write(db, cache)
        with patch.dict(os.environ, {r.go_budget.TOKEN_ENV: 'fixture'}):
            r.go_budget.refresh(self.state, self.c, fetcher=lambda *_: r.go_budget.parse_usage(payload(reset=time.time()+10000)))
        with r.database(self.state) as db:
            db.execute("UPDATE models SET cooldown=? WHERE id='opencode-go/quota'", (time.time()+300,))

    def test_economic_fleet_quota_variant_and_snapshot(self):
        self.c.update(cost_aware=True)
        self.c['models']=[self.model('quota',relative_cost=1,variants=['low','high']),
                          self.model('two',relative_cost=2,variants=['medium','high']),
                          self.model('strong','escalation',relative_cost=10,escalation_only=True)]
        self.job('arbitrary $(do-not-execute) `text`')
        self.run_fleet(1)
        self.assertEqual(len(self.rows('attempts')), 1)
        self.recover_usage()
        self.run_fleet()
        attempts=self.rows('attempts')
        self.assertEqual([a['status'] for a in attempts],['quota','success'])
        self.assertEqual([a['variant'] for a in attempts],['low','medium'])
        self.assertEqual(json.loads(attempts[1]['result'])['routing_cost']['relative_cost'],2)

    def test_economic_retry_handoff_and_high_reasoning(self):
        self.c.update(cost_aware=True,reasoning_after=1)
        self.c['models']=[self.model('one',relative_cost=1,variants=['medium','high']),
                          self.model('two',relative_cost=2,variants=['medium','high'])]
        self.job('FAIL_FIRST')
        self.run_fleet()
        attempts=self.rows('attempts')
        self.assertEqual([a['model'] for a in attempts],['opencode-go/one','opencode-go/two'])
        self.assertEqual([a['variant'] for a in attempts],['medium','high'])
        self.assertIn('callee ABI proven',(Path(attempts[1]['directory'])/'prompt.txt').read_text())

    def test_reserved_models_and_explicit_override(self):
        j = dict(model=None, tier='bulk')
        for _ in range(3):
            m = r.choose(self.c,j,{}, {}, [],0)
            self.assertNotEqual(m['tier'],'escalation')
        self.assertIsNone(r.choose(self.c,j,{'opencode-go/one':1,'opencode-go/two':1},{},[],0))
        j['model']='opencode-go/strong'
        self.assertEqual(r.choose(self.c,j,{}, {}, [],0)['tier'],'escalation')
        j.update(model=None,tier='escalation')
        self.assertEqual(r.choose(self.c,j,{}, {}, [],0)['tier'],'escalation')

    def test_reserves_weights_and_cooldown(self):
        self.c['models'][0].update(concurrency=2,reserve=1,weight=4)
        j=dict(model=None,tier='bulk')
        s={'opencode-go/one':{'dispatched':4},'opencode-go/two':{'dispatched':2}}
        self.assertEqual(r.choose(self.c,j,{},s,[],0)['id'],'opencode-go/one')
        self.assertEqual(r.choose(self.c,j,{'opencode-go/one':1},s,[],0)['id'],'opencode-go/two')
        s['opencode-go/one']['cooldown']=10
        self.assertEqual(r.choose(self.c,j,{},s,[],9)['id'],'opencode-go/two')
        self.assertEqual(r.choose(self.c,j,{},s,[],10)['id'],'opencode-go/one')

    def test_rate_limit_slow_start(self):
        self.c['models'][0].update(concurrency=16)
        db=sqlite3.connect(':memory:'); db.executescript(r.SCHEMA)
        mid='opencode-go/one'
        n=iter(range(10**6))
        def attempt(status,started,ended=None):
            db.execute('INSERT INTO attempts(id,model,status,started,ended) VALUES (?,?,?,?,?)',
                       (str(next(n)),mid,status,started,ended))
        self.assertEqual(r.ramp_caps(db,self.c,1000),{})  # never limited: no cap
        for t in range(16): attempt('quota',100,105)
        self.assertEqual(r.ramp_caps(db,self.c,1000)[mid],1)  # one probe first
        attempt('running',400)
        self.assertEqual(r.ramp_caps(db,self.c,430)[mid],1)   # probe not yet survived
        self.assertEqual(r.ramp_caps(db,self.c,470)[mid],2)
        attempt('success',410,900); attempt('failure',420,500); attempt('quota',430,436)
        self.assertEqual(r.ramp_caps(db,self.c,1000)[mid],1)  # a later quota restarts the ramp
        for t in (500,501,502,503): attempt('success',t,t+100)
        self.assertNotIn(mid,r.ramp_caps(db,self.c,1000))     # 2**4 reaches concurrency
        j=dict(model=None,tier='bulk')
        s={mid:{'ramp_cap':1}}
        self.assertEqual(r.choose(self.c,j,{},s,[],0)['id'],mid)
        self.assertEqual(r.choose(self.c,j,{mid:1},s,[],0)['id'],'opencode-go/two')

    def test_account_quota_defers_without_consuming_reasoning_budget(self):
        self.c['models'][0]['id']='opencode-go/quota'
        job=self.job()
        started=time.monotonic()
        self.run_fleet(1)
        self.assertLess(time.monotonic()-started,3)
        self.assertEqual([a['status'] for a in self.rows('attempts')],['quota'])
        self.assertEqual(self.rows('jobs')[0]['status'],'queued')
        self.recover_usage()
        self.run_fleet()
        attempts=self.rows('attempts')
        self.assertEqual([a['status'] for a in attempts],['quota','success'])
        j=self.rows('jobs')[0]
        self.assertEqual((j['failures'],j['availability_failures'],j['status']),(0,1,'completed'))
        self.assertEqual(attempts[1]['model'],'opencode-go/two')

    def test_all_quotas_exhausted_recover_without_busy_retry(self):
        self.c['models']=[self.model('quota')]
        self.c.update(cooldown=.2,availability_retries=2)
        self.job()
        self.run_fleet(1)
        self.run_fleet(1)
        attempts=self.rows('attempts')
        self.assertEqual(len(attempts),1)
        self.assertEqual(self.rows('jobs')[0]['status'],'queued')
        self.assertEqual(self.rows('jobs')[0]['failures'],0)

    def test_oversized_protocol_and_partial_lines(self):
        import io
        e=r.Events();e.drain(io.StringIO('x'*1048577))
        self.assertTrue(e.oversized)
        e=r.Events();stream=io.StringIO('{"type":"text"')
        e.drain(stream);self.assertEqual(stream.tell(),0)
        e.feed(json.dumps({'type':'text','part':{'text':'ROUTER_RESULT {"outcome":"success"}\\nROUTER_RESULT broken'}}))
        # A malformed final report cannot inherit an earlier success.
        e.text='ROUTER_RESULT {"outcome":"success"}'+chr(10)+'ROUTER_RESULT broken'
        self.assertEqual(e.result(0)['kind'],'failure')


    def test_failure_handoff_and_different_model(self):
        self.job('FAIL_FIRST')
        self.run_fleet()
        a=self.rows('attempts')
        self.assertEqual([x['status'] for x in a],['failure','success'])
        self.assertNotEqual(a[0]['model'],a[1]['model'])
        prompt=(Path(a[1]['directory'])/'prompt.txt').read_text()
        for evidence in ['change register lifetime','+0x20 eax/ecx','callee ABI proven',a[0]['directory']]:
            self.assertIn(evidence,prompt)

    def test_variants_by_task_class_and_model(self):
        model = self.model('one')
        caps = {model['id']: ['minimal','low','medium','high','xhigh','max']}
        for tier, expected in [('bulk','medium'), ('reasoning','high'), ('escalation','max')]:
            self.assertEqual(r.choose_variant(model, tier, caps), expected)
        model['variant_preferences'] = {'bulk':'low', 'escalation':'xhigh'}
        self.assertEqual(r.choose_variant(model, 'bulk', caps), 'low')
        self.assertEqual(r.choose_variant(model, 'escalation', caps), 'xhigh')
        caps[model['id']] = ['low','high']
        self.assertEqual(r.choose_variant(model, 'bulk', caps), 'low')
        self.assertEqual(r.choose_variant(model, 'escalation', caps), 'high')
        caps[model['id']] = ['medium','high']
        self.assertEqual(r.choose_variant(model, 'bulk', caps), 'medium')
        self.assertEqual(r.choose_variant(model, 'escalation', caps), 'high')

    def test_variant_metadata_fallback_and_provider_names(self):
        model = self.model('one')
        self.assertIsNone(r.choose_variant(model, 'escalation', {}))
        model.update(variants=['low','high'], variant_preferences={'bulk':'medium'})
        self.assertEqual(r.choose_variant(model, 'bulk', {}), 'low')
        self.assertIsNone(r.choose_variant(model, 'escalation', {model['id']: []}))
        model.update(variants=['none','thinking'], variant_preferences={'reasoning':'thinking','bulk':None})
        self.assertEqual(r.choose_variant(model, 'reasoning', {}), 'thinking')
        self.assertIsNone(r.choose_variant(model, 'bulk', {}))
        model.pop('variants');model.pop('variant_preferences')
        for tier in ('reasoning','escalation'):
            self.assertIsNone(r.choose_variant(model, tier, {model['id']: ['none','thinking']}))
        self.assertIsNone(r.choose_variant(model, 'bulk', {model['id']: ['max']}))
        model['id'] += '#high'
        self.assertEqual(r.choose_variant(model, 'bulk', {}), 'high')
        self.assertEqual(r.model_selection(model['id'], 'low'), 'opencode-go/one#low')

    def test_runtime_variant_catalog_and_outage(self):
        self.c['variant_discovery'] = True
        response = {'data': [
            {'providerID':'opencode-go','id':'one','variants':[{'id':'low'},{'id':'high'}]},
            {'providerID':'opencode-go','id':'two','variants':[]},
            {'providerID':'paid','id':'other','variants':[{'id':'max'}]},
        ], 'padding': 'x' * 300000}  # Larger than the observed CLI pipe truncation.
        def respond(data):
            def run(*args, **kwargs):
                kwargs['stdout'].write(data)
                return subprocess.CompletedProcess([],0)
            return run
        with patch.object(r.subprocess, 'run', side_effect=respond(json.dumps(response))) as call:
            self.assertEqual(r.discover_variants(self.c,self.root), {'opencode-go/one':['low','high'],'opencode-go/two':[]})
            self.assertEqual(call.call_args.args[0], [str(self.fake),'api','model.list'])
            startup=json.loads(call.call_args.kwargs['env']['OPENCODE_CONFIG_CONTENT'])
            self.assertFalse(startup['warming'])
            self.assertIn({'action':'provider.use','resource':'*','effect':'deny'},startup['experimental']['policies'])
        for data in ['{"data":[]}', 'not json', '{"data":[{"providerID":"opencode-go","id":"one","variants":[{}]}]}']:
            with patch.object(r.subprocess,'run',side_effect=respond(data)):
                self.assertEqual(r.discover_variants(self.c,self.root), {})
        with patch.object(r.subprocess,'run',side_effect=subprocess.TimeoutExpired('opencode',10)):
            self.assertEqual(r.discover_variants(self.c,self.root), {})

    def test_variant_launch_promotion_and_statistics(self):
        for m in self.c['models']:m['variants']=['low','medium','high','max']
        self.c['reasoning_after'] = 1
        job = self.job('FAIL_FIRST')
        self.run_fleet()
        attempts = self.rows('attempts')
        self.assertEqual([a['variant'] for a in attempts], ['medium','high'])
        self.assertEqual([a['tier'] for a in attempts], ['bulk','reasoning'])
        data = r.status(self.state,self.c)
        self.assertEqual(data['jobs'][0]['variant'], 'high')
        self.assertEqual(data['attempts'][0]['category'], 'bulk')
        self.assertGreater(data['attempts'][0]['duration_seconds'],0)
        self.assertEqual(len(data['configurations']),2)
        cwd=Path(self.rows('jobs')[0]['cwd'])
        self.assertEqual((cwd/'selected-model.txt').read_text(),r.model_selection(attempts[1]['model'],'high'))
        self.assertIn('"variant": "medium"',(cwd/'received.txt').read_text())
        import io
        from contextlib import redirect_stdout
        out=io.StringIO()
        with redirect_stdout(out):r.print_status(data)
        self.assertIn('#high',out.getvalue())
        self.assertIn('#medium',out.getvalue())
        self.c.update(escalation_after=1)
        self.job('FAIL_FIRST second')
        self.run_fleet()
        self.assertEqual(self.rows('attempts')[-1]['variant'],'max')

    def test_variant_quota_failover(self):
        self.c['models']=[self.model('quota',variants=['low']),self.model('two',variants=['medium'])]
        self.job();self.run_fleet(1)
        self.recover_usage()
        self.run_fleet()
        attempts=self.rows('attempts')
        self.assertEqual([a['status'] for a in attempts],['quota','success'])
        self.assertEqual([a['variant'] for a in attempts],['low','medium'])

    def test_legacy_pinned_model_statistics(self):
        self.c['models']=[self.model('one#high')]
        self.job();self.run_fleet()
        data=r.status(self.state,self.c)
        self.assertEqual(data['attempts'][0]['model'],'opencode-go/one#high')
        self.assertEqual(data['configurations'][0]['model'],'opencode-go/one')
        self.assertEqual(data['configurations'][0]['variant'],'high')

    def test_rejected_variant_falls_back_without_task_failure(self):
        self.c['models']=[self.model('one',variants=['medium','low'])]
        self.job('BADVARIANT');self.run_fleet()
        attempts=self.rows('attempts')
        self.assertEqual([a['status'] for a in attempts],['variant_unavailable','success'])
        self.assertEqual([a['variant'] for a in attempts],['medium','low'])
        self.assertEqual(self.rows('jobs')[0]['failures'],0)
        self.assertEqual(self.rows('jobs')[0]['availability_failures'],1)
        self.assertEqual(self.rows('models')[0]['cooldown'],0)
        self.c['models'][0]['variants']=['medium']
        self.job('BADVARIANT default');self.run_fleet()
        self.assertIsNone(self.rows('attempts')[-1]['variant'])
        self.assertEqual(self.rows('attempts')[-1]['status'],'success')

    def test_old_state_and_config_compatibility(self):
        self.job();self.run_fleet()
        original=self.rows('attempts')[0]
        with r.database(self.state) as db:
            db.execute('INSERT INTO measurements VALUES (?,?,?,?,?,?)',(original['id'],1,.2,3,'verified fixture',time.time()))
            db.execute('ALTER TABLE attempts DROP COLUMN variant')
        marker=(self.state/'identity').read_text()
        from concurrent.futures import ThreadPoolExecutor
        with ThreadPoolExecutor(max_workers=4) as pool:
            snapshots=list(pool.map(lambda _:r.status(self.state,self.c),range(8)))
        for data in snapshots:
            self.assertIsNone(data['attempts'][0]['variant'])
            self.assertEqual(data['measurements'][0]['iterations'],3)
            self.assertEqual(data['configurations'][0]['exact_matches'],1)
        self.assertEqual((self.state/'identity').read_text(),marker)
        old=copy.deepcopy(self.c);old.pop('variant_discovery')
        path=self.root/'old.json';path.write_text(json.dumps(old))
        self.assertEqual(r.config(path)['models'],old['models'])
        # An old process can still insert its explicit set of attempt columns.
        with r.database(self.state) as db:
            db.execute('INSERT INTO attempts(id,job,model,tier,status,started) VALUES (?,?,?,?,?,?)',
                       ('old-process',original['job'],original['model'],'bulk','running',time.time()))
        self.assertIsNone(self.rows('attempts')[-1]['variant'])

    def test_invalid_variant_configuration(self):
        path=self.root/'invalid.json'
        for value in [['low','low'],['bad#variant'],['$(touch PWNED)'],42,[None],None]:
            c=copy.deepcopy(self.c);c['models'][0]['variants']=value
            path.write_text(json.dumps(c))
            with self.assertRaises(ValueError):r.config(path)
        c=copy.deepcopy(self.c);c['models'][0]['variant_preferences']={'bulk':'--model paid/other'}
        path.write_text(json.dumps(c))
        with self.assertRaises(ValueError):r.config(path)

    def test_partial_and_blocked_reports_survive_as_failures(self):
        for word in ('partial', 'blocked'):
            ev = r.Events()
            ev.text = 'work\nROUTER_RESULT {"outcome":"%s","approaches":["a"],"discoveries":["d"]}\n' % word
            res = ev.result(0)
            self.assertEqual(res['kind'], 'failure')
            self.assertIsNotNone(res['report'])
            self.assertEqual(res['report']['outcome'], 'failure')
            self.assertEqual(res['report']['reported_outcome'], word)
            self.assertEqual(res['report']['approaches'], ['a'])
        ev = r.Events(); ev.text = 'ROUTER_RESULT {"outcome":"success"}\n'
        self.assertEqual(ev.result(0)['kind'], 'success')
        ev = r.Events(); ev.text = 'ROUTER_RESULT {"outcome":"whatever"}\n'
        self.assertIsNone(ev.result(0)['report'])

    def test_provider_server_errors_are_availability_not_task_failure(self):
        self.assertEqual(r.classify({'type':'provider.internal','message':'Streaming response failed: [504] Upstream idle timeout exceeded','status':200}),'unavailable')
        self.assertEqual(r.classify({'status':502,'message':'Bad Gateway'}),'unavailable')
        self.assertEqual(r.classify({'status':503,'message':'model overloaded'}),'unavailable')
        self.assertEqual(r.classify({'status':429,'message':'upstream rate limit'}),'quota')  # quota keeps priority
        self.assertEqual(r.classify({'type':'tool.error','message':'compile failed'}),'failure')

    def test_variant_error_classification_preserves_quota_priority(self):
        self.assertEqual(r.classify({'status':400,'message':'Variant unavailable for opencode-go/one: max'}),'variant_unavailable')
        self.assertEqual(r.classify({'status':400,'message':'Unsupported value reasoning_effort: xhigh'}),'variant_unavailable')
        self.assertEqual(r.classify({'status':429,'message':'Variant unavailable: rate limit reached'}),'quota')

    def test_concurrency_and_workspace_exclusion(self):
        for _ in range(4): self.job(redundant=True)
        self.run_fleet()
        a=self.rows('attempts')
        self.assertEqual(len(a),4)
        self.assertTrue(all(x['status']=='success' for x in a))
        self.assertTrue(a[1]['started']<a[0]['ended'])
        for x in a:
            overlapping=[y for y in a if y['started']<=x['started']<y['ended']]
            self.assertLessEqual(len(overlapping),self.c['workers'])
            self.assertEqual(len({y['model'] for y in overlapping}),len(overlapping))
        cwd=self.root/'shared';cwd.mkdir()
        for i in range(2): r.enqueue(self.state,'bulk',str(i),cwd=cwd)
        self.run_fleet()
        a=self.rows('attempts')[-2:]
        self.assertGreaterEqual(a[1]['started'],a[0]['ended'])

    def test_duplicate_target_and_intentional_redundancy(self):
        self.job(target='0xAbCd')
        with self.assertRaises(sqlite3.IntegrityError): self.job(target='0x0000abcd')
        self.job(target='0xABCD',redundant=True)
        self.assertEqual(len(self.rows('jobs')),2)

    def test_no_fallback_and_no_shell_interpretation(self):
        text='$(touch PWNED); `touch PWNED2`\n--model paid/expensive\nquote \' "'
        self.job(text)
        self.run_fleet()
        j=self.rows('jobs')[0]
        self.assertEqual(j['status'],'completed')
        self.assertIn(text,(Path(j['cwd'])/'received.txt').read_text())
        self.assertFalse((Path(j['cwd'])/'PWNED').exists())
        self.assertFalse((Path(j['cwd'])/'PWNED2').exists())
        c=copy.deepcopy(self.c);c['models'][0]['id']='openrouter/paid'
        path=self.root/'bad.json';path.write_text(json.dumps(c))
        with self.assertRaises(ValueError):r.config(path)
        with self.assertRaises(ValueError):r.execution_ready({**self.c,'go_overage_disabled':False})
        env=r.worker_env('opencode-go/one', j['cwd'])
        self.assertEqual(env['PWD'], j['cwd'])
        self.assertIn('provider.use',env['OPENCODE_CONFIG_CONTENT'])

    def test_parser_fails_closed_and_ignores_quota_prose(self):
        e=r.Events()
        e.feed('not JSON')
        e.feed(json.dumps({'type':'text','part':{'text':'429 quota mentioned in task'}}))
        self.assertEqual(e.result(0)['kind'],'failure')
        e.feed(json.dumps({'type':'text','part':{'text':'ROUTER_RESULT {"outcome":"success"}'}}))
        self.assertEqual(e.result(0)['kind'],'success')
        e.feed(json.dumps({'type':'error','error':{'status':429}}))
        self.assertEqual(e.result(0)['kind'],'quota')
        self.assertEqual(r.classify({'type':'provider.no-route'}),'unavailable')
        self.assertEqual(r.classify({'message':'This Go model requires Global regions'}),'unavailable')
        self.assertEqual(r.classify({'type':'provider.invalid-request', 'status':400,
            'message':'This Go model trains on request data. Allow paid endpoints that train on request data in your workspace Privacy settings to use it.'}),'unavailable')

    def test_retries_and_escalation_are_bounded(self):
        self.c.update(retries=3,reasoning_after=1,escalation_after=2)
        job=self.job()
        with r.database(self.state) as db:
            db.execute("INSERT INTO models(id) VALUES ('opencode-go/one')")
        for i in range(4):
            with r.database(self.state) as db:
                db.execute("INSERT INTO attempts(id,job,model,tier,status,started,directory) VALUES (?,?,?,'bulk','running',0,'fixture')",(str(i),job,'opencode-go/one'))
            r.finish(self.state,self.c,str(i),{'kind':'failure'},now=1)
            r.finish(self.state,self.c,str(i),{'kind':'failure'},now=2) # idempotence
            j=self.rows('jobs')[0]
            self.assertEqual(j['failures'],i+1)
            self.assertEqual(j['tier'],'reasoning' if i==0 else 'escalation')
        self.assertEqual(j['status'],'failed')

    def test_timeout_and_duration_stop_workers(self):
        self.c.update(timeout=.2,retries=0)
        self.job('SLOW')
        self.run_fleet()
        self.assertEqual(self.rows('attempts')[0]['status'],'timeout')
        self.assertEqual(self.rows('jobs')[0]['status'],'failed')
        self.job('SLOW',redundant=True)
        self.c['timeout']=20
        self.run_fleet(duration=.2)
        a=self.rows('attempts')[-1]
        self.assertEqual(a['status'],'interrupted')
        self.assertFalse(r.fleet_run.pid_alive(a['pid']))

    def test_crash_window_needs_review_and_retains_target(self):
        job=self.job(target='0x1234')
        with r.database(self.state) as db:
            db.execute("INSERT INTO models(id) VALUES ('opencode-go/one')")
            db.execute("INSERT INTO attempts(id,job,model,tier,status,started,directory) VALUES ('lost',?,'opencode-go/one','bulk','running',0,?)",(job,str(self.root)))
        r.recover(self.state,self.c,self.root)
        self.assertEqual(self.rows('jobs')[0]['status'],'needs_review')
        with self.assertRaises(sqlite3.IntegrityError):self.job(target='0x1234')

    def test_scheduler_lock_and_legacy_claim(self):
        with r.scheduler_lock(self.state) as held:
            self.assertTrue(held)
            with r.scheduler_lock(self.state) as second:self.assertFalse(second)
        self.job(target='0x00001234')
        legacy = 'legacy-' + r.uuid.uuid4().hex
        unit, record_path, record = r.claim_job(self.root, {'target':'0x00001234','redundant':False}, legacy, 10)
        self.addCleanup(unit.remove)
        self.run_fleet(duration=.2)
        self.assertEqual(self.rows('attempts'),[])
        self.assertIn('legacy',self.rows('jobs')[0]['note'])
        r.release_attempt(self.root,legacy,unit,record_path,record)
        unit.remove()
        self.run_fleet()
        self.assertEqual(self.rows('jobs')[0]['status'],'completed')

    def test_database_loss_fails_closed(self):
        (self.state/'router.sqlite').unlink()
        with self.assertRaisesRegex(ValueError,'database missing'):
            r.connect(self.state)

    def test_detached_descendants_are_contained(self):
        self.job('DETACH')
        self.run_fleet()
        job=self.rows('jobs')[0]
        pid=int((Path(job['cwd'])/'detached.pid').read_text())
        stat=Path(f'/proc/{pid}/stat')
        self.assertTrue(not stat.exists() or stat.read_text().rsplit(')',1)[1].split()[0]=='Z')
        self.assertEqual(job['status'],'completed')

    def test_scheduler_crash_watchdog_and_restart(self):
        self.c.update(timeout=1,retries=0)
        cfg=self.root/'config.json';cfg.write_text(json.dumps(self.c))
        self.job('SLOW')
        command=[sys.executable,str(Path(r.__file__)), '--config',str(cfg),
                 '--state',str(self.state),'--root',str(self.root)]
        scheduler=subprocess.Popen(command+['fleet','--duration','10s'],stdout=subprocess.DEVNULL,stderr=subprocess.PIPE)
        try:
            deadline=time.monotonic()+4
            while time.monotonic()<deadline:
                a=self.rows('attempts')
                if a and a[0]['pid']:
                    record=self.root/'build/fleet_runs'/('router-'+a[0]['id'])/'record.json'
                    if record.exists() and json.loads(record.read_text()).get('launch_phase')=='released':break
                time.sleep(.02)
            else:self.fail('scheduler did not release worker')
            scheduler.kill();scheduler.wait()
            # Child timeout supervisor survives its scheduler and empties cgroup.
            deadline=time.monotonic()+4
            while time.monotonic()<deadline:
                if r.fleet_run.cgroup_state(a[0]['cgroup'],'router-'+a[0]['id']) is False:break
                time.sleep(.05)
            else:self.fail('watchdog did not contain worker after scheduler crash')
            r.recover(self.state,self.c,self.root)
            # A crash is not a task failure: the verified-empty attempt is recorded
            # as interrupted and the job returns to the queue, spending no quota.
            job=self.rows('jobs')[0]
            self.assertEqual((job['status'],job['failures'],job['note']),('queued',0,'interrupted'))
            self.assertEqual(self.rows('attempts')[0]['status'],'interrupted')
            self.assertEqual(len(self.rows('attempts')),1)
            # The requeued job really runs again, and a genuine timeout does retire it.
            self.run_fleet()
            job=self.rows('jobs')[0]
            self.assertEqual((job['status'],job['failures']),('failed',1))
            self.assertEqual([a['status'] for a in self.rows('attempts')],['interrupted','timeout'])
        finally:
            if scheduler.poll() is None:scheduler.kill();scheduler.wait()
            scheduler.stderr.close()

    def test_sigint_stops_and_does_not_restart(self):
        self.c.update(timeout=20)
        cfg=self.root/'config.json';cfg.write_text(json.dumps(self.c))
        cwd=self.root/'signal-work';cwd.mkdir()
        command=[sys.executable,str(Path(r.__file__)),'--config',str(cfg),'--state',str(self.state),
                 '--root',str(self.root),'run','bulk','SLOW','--cwd',str(cwd),'--duration','10s']
        scheduler=subprocess.Popen(command,stdout=subprocess.DEVNULL,stderr=subprocess.PIPE)
        try:
            deadline=time.monotonic()+4
            while time.monotonic()<deadline:
                a=self.rows('attempts')
                if a and a[0]['pid']:break
                time.sleep(.02)
            else:self.fail('worker did not launch')
            scheduler.send_signal(signal.SIGINT)
            self.assertEqual(scheduler.wait(timeout=4),130)
            self.assertEqual(len(self.rows('attempts')),1)
            self.assertEqual(self.rows('attempts')[0]['status'],'interrupted')
        finally:
            if scheduler.poll() is None:scheduler.kill();scheduler.wait()
            scheduler.stderr.close()





class EconomicsTests(unittest.TestCase):
    def setUp(self):
        self.c = r.config(r.DEFAULT_CONFIG)
        self.j = dict(model=None, tier='bulk', category='bulk')
        self.pool = [m for m in self.c['models'] if not m['escalation_only']]

    def select(self, **kw):
        return r.choose(self.c, self.j, kw.get('active', {}), kw.get('states', {}), kw.get('history', []), 100)

    def failure(self, model, status='failure', evidence=True):
        return dict(model=model['id'], status=status, result=json.dumps({'report':
            {'outcome':'failure','approaches':['proven failed shape']} if evidence else None}))

    def test_cost_order_and_bulk_exclusion(self):
        expected=['muse-spark-1.3-contributor','deepseek-v4.1-flash','mimo-v2.6-flash',
                  'gpt-6-luna','qwen3.8-flash','deepseek-v4-flash']
        active={}
        for name in expected:
            m=self.select(active=active)
            self.assertEqual(m['id'], 'opencode-go/'+name)
            active[m['id']]=m['concurrency']
        self.assertIsNone(self.select(active=active))

    def test_quota_failover_recovery_no_expensive_unlock(self):
        states={m['id']:dict(cooldown=101) for m in self.pool}
        self.assertIsNone(self.select(states=states, history=[self.failure(m,'quota') for m in self.pool]))
        states[self.pool[1]['id']]['cooldown']=100
        self.assertEqual(self.select(states=states)['id'],self.pool[1]['id'])

    def test_escalation_requires_real_evidence_and_two_models(self):
        self.j['tier']='escalation'
        states={m['id']:dict(cooldown=101) for m in self.pool}
        for status in ('quota','interrupted','timeout','unavailable'):
            self.assertIsNone(self.select(states=states,history=[self.failure(m,status) for m in self.pool]))
        self.assertIsNone(self.select(states=states,history=[self.failure(self.pool[0])]*4))
        self.assertIsNone(self.select(states=states,history=[self.failure(m,evidence=False) for m in self.pool]))
        history=[self.failure(m) for m in self.pool[:2]]
        self.assertEqual(self.select(states=states,history=history)['id'],'opencode-go/glm-5.3-flash')

    def test_parent_escalation_and_cost_ladder(self):
        self.j.update(category='escalation',tier='escalation')
        # Still use untried inexpensive workers before spending more.
        self.assertEqual(self.select()['id'],self.pool[0]['id'])
        history=[self.failure(m) for m in self.pool]
        self.assertEqual(self.select(history=history)['id'],'opencode-go/glm-5.3-flash')
        self.j.update(category='bulk',tier='bulk',model='opencode-go/kimi-k2.6')
        self.assertEqual(self.select()['id'],self.j['model'])

    def test_effectiveness_and_variant_are_separate_controls(self):
        m=self.pool[1];m['effectiveness']=2
        self.assertEqual(self.select()['id'],m['id'])
        caps={m['id']:['low','high','max']}
        self.assertEqual(r.choose_variant(m,'bulk',caps),'low')
        self.assertEqual(r.choose_variant(m,'reasoning',caps),'high')
        self.assertEqual(r.choose_variant(m,'escalation',caps),'high')
        m['variant_preferences']['escalation']='max'
        self.assertEqual(r.choose_variant(m,'escalation',caps),'max')

    def test_cost_events_deduplicate_and_unknown_is_not_free(self):
        e=r.Events()
        self.assertIsNone(e.result(0)['reported_cost_usd'])
        for cost in (.2,.3):
            e.feed(json.dumps(dict(type='step_finish',part=dict(id='one',cost=cost))))
        e.feed(json.dumps(dict(type='step_finish',part=dict(id='two',cost=.1))))
        e.feed(json.dumps(dict(type='step_finish',part=dict(id='bad',cost=-1))))
        self.assertAlmostEqual(e.result(0)['reported_cost_usd'],.4)
        self.assertEqual(e.result(0)['costed_steps'],2)

    def test_old_config_and_unknown_cost(self):
        for m in self.c['models']:
            m.pop('relative_cost',None)
        self.assertIsNone(self.select())
        self.c.pop('cost_aware')
        self.assertIsNotNone(self.select())

    def test_old_state_and_economic_measurement(self):
        with tempfile.TemporaryDirectory() as tmp:
            state=Path(tmp)
            job=r.enqueue(state,'bulk','task')
            with r.database(state) as db:
                db.execute('INSERT INTO attempts (id,job,model,tier,status,started,ended,result) VALUES (?,?,?,?,?,?,?,?)',
                    ('old',job,self.pool[0]['id'],'bulk','success',1,2,'{}'))
                db.execute('INSERT INTO attempts (id,job,model,tier,status,started,ended,result,variant) VALUES (?,?,?,?,?,?,?,?,?)',
                    ('new',job,self.pool[0]['id'],'bulk','success',2,3,json.dumps({'reported_cost_usd':.5}),'medium'))
                db.execute('INSERT INTO measurements VALUES (?,?,?,?,?,?)',('new',1,None,None,'verified',3))
                db.execute('INSERT INTO economic_measurements VALUES (?,?,?)',('new',187,1))
            x=r.status(state,self.c)
            self.assertIsNone(x['attempts'][0]['reported_cost_usd'])
            row=next(v for v in x['configurations'] if v['variant']=='medium')
            self.assertEqual(row['exact_matches_per_reported_usd'],2)
            self.assertEqual(row['bytes_gained_per_reported_usd'],374)
            self.assertEqual(row['useful_investigations_per_reported_usd'],2)


class LifecycleAccountingTests(unittest.TestCase):
    """A scheduler interruption is lifecycle, never evidence against model or task.

    Exercises finish()/recover()/status() directly, so it needs no cgroup v2, no
    CLI and no inference.
    """

    def setUp(self):
        self.c = r.config(r.DEFAULT_CONFIG)
        self.c.update(retries=1, reasoning_after=1, escalation_after=2,
                      availability_retries=2, cooldown=300, failure_cooldown=30,
                      cost_aware=False)
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.state = Path(self.tmp.name) / 'state'
        self.claims = Path(self.tmp.name) / 'claims'
        self.model = self.c['models'][0]['id']

    def job(self, target=None):
        return r.enqueue(self.state, 'bulk', 'fixture ' + str(target), target=target)

    def rows(self, table):
        with r.database(self.state) as db:
            return [dict(row) for row in db.execute('SELECT * FROM ' + table)]

    def attempt(self, job, model=None):
        model = model or self.model
        aid = 'attempt-%d' % len(self.rows('attempts'))
        with r.database(self.state) as db:
            db.execute('INSERT OR IGNORE INTO models(id) VALUES (?)', (model,))
            db.execute("INSERT INTO attempts (id,job,model,tier,status,started,directory,cgroup) "
                       "VALUES (?,?,?,'bulk','running',0,?,'/fixture/never-created')",
                       (aid, job, model, str(self.tmp.name)))
        return aid

    def finish(self, aid, kind):
        r.finish(self.state, self.c, aid, {'kind': kind}, now=1000.0)

    def lost_attempt(self, job):
        """A 'running' attempt left behind by a scheduler that never returned."""
        with r.database(self.state) as db:
            db.execute('INSERT OR IGNORE INTO models(id) VALUES (?)', (self.model,))
            db.execute("INSERT INTO attempts (id,job,model,tier,status,started,directory,cgroup) "
                       "VALUES ('lost',?,?,'bulk','running',0,?,'/fixture/never-created')",
                       (job, self.model, str(self.tmp.name)))
    def test_interruptions_requeue_without_spending_quota(self):
        job = self.job()
        for _ in range(3):
            self.finish(self.attempt(job), r.INTERRUPTED)
            j = self.rows('jobs')[0]
            self.assertEqual((j['status'], j['failures'], j['availability_failures'], j['tier']),
                             ('queued', 0, 0, 'bulk'))
        # No model is blamed: no cooldown, no reason.
        self.assertEqual((self.rows('models')[0]['cooldown'], self.rows('models')[0]['reason']), (0, ''))
        self.assertEqual([a['status'] for a in self.rows('attempts')], [r.INTERRUPTED] * 3)
        self.assertTrue(all(a['ended'] == 1000.0 for a in self.rows('attempts')))
        # The first genuine failure is the first to spend anything.
        self.finish(self.attempt(job), 'failure')
        j = self.rows('jobs')[0]
        self.assertEqual((j['status'], j['failures'], j['tier']), ('queued', 1, 'reasoning'))
        self.assertEqual(self.rows('models')[0]['cooldown'], 1030.0)
        self.assertEqual(self.rows('models')[0]['reason'], 'failure')
        self.assertEqual([a['status'] for a in self.rows('attempts')],
                         [r.INTERRUPTED] * 3 + ['failure'])

    def test_interruptions_alone_never_exhaust_escalation_or_retries(self):
        # The demonstrated defect: three interruptions terminally failed a job and
        # promoted its tier, so one real failure then escalated it immediately.
        job = self.job()
        for _ in range(6):
            self.finish(self.attempt(job), r.INTERRUPTED)
        j = self.rows('jobs')[0]
        self.assertEqual((j['status'], j['failures'], j['tier']), ('queued', 0, 'bulk'))
        self.finish(self.attempt(job), 'failure')
        j = self.rows('jobs')[0]
        self.assertEqual((j['status'], j['failures'], j['tier']), ('queued', 1, 'reasoning'))
        self.finish(self.attempt(job), 'failure')
        j = self.rows('jobs')[0]
        self.assertEqual((j['status'], j['failures'], j['tier']), ('failed', 2, 'escalation'))

    def test_interruption_preserves_tier_after_threshold_change(self):
        job = self.job()
        with r.database(self.state) as db:
            db.execute('UPDATE jobs SET failures=1 WHERE id=?', (job,))
        self.c['escalation_after'] = 1
        self.finish(self.attempt(job), r.INTERRUPTED)
        j = self.rows('jobs')[0]
        self.assertEqual((j['status'], j['failures'], j['tier']), ('queued', 1, 'bulk'))

    def test_timeout_and_output_limit_still_spend_the_failure_budget(self):
        job = self.job()
        for kind in (r.INTERRUPTED, 'timeout', r.INTERRUPTED, 'output_limit'):
            self.finish(self.attempt(job), kind)
        j = self.rows('jobs')[0]
        self.assertEqual((j['status'], j['failures'], j['tier']), ('failed', 2, 'escalation'))
        self.assertEqual(j['availability_failures'], 0)
        self.assertEqual([a['status'] for a in self.rows('attempts')],
                         [r.INTERRUPTED, 'timeout', r.INTERRUPTED, 'output_limit'])
        # An interruption never resurrects a job that already reached a terminal state.
        self.finish(self.attempt(job), r.INTERRUPTED)
        self.assertEqual(self.rows('jobs')[0]['status'], 'failed')

    def test_availability_kinds_spend_only_availability_budget(self):
        job = self.job()
        for kind in (r.INTERRUPTED, 'quota', r.INTERRUPTED, 'unavailable', 'variant_unavailable'):
            self.finish(self.attempt(job), kind)
        j = self.rows('jobs')[0]
        self.assertEqual((j['status'], j['failures'], j['availability_failures'], j['tier']),
                         ('failed', 0, 3, 'bulk'))
        # variant_unavailable costs no cooldown: it only stops that variant being reused.
        self.assertEqual(self.rows('models')[0]['cooldown'], 1300.0)
        self.assertEqual(self.rows('models')[0]['reason'], 'unavailable')

    def test_needs_review_and_cancellation_stay_terminal(self):
        reviewed = self.job(target='0x1234')
        self.finish(self.attempt(reviewed), 'needs_review')
        j = self.rows('jobs')[0]
        self.assertEqual((j['status'], j['failures']), ('needs_review', 0))
        # needs_review retains ownership, so the model is still held back.
        self.assertEqual(self.rows('models')[0]['cooldown'], 1030.0)
        with self.assertRaises(sqlite3.IntegrityError):
            self.job(target='0x1234')
        self.finish(self.attempt(self.job(target='0x5678')), 'cancelled')
        j = self.rows('jobs')[1]
        self.assertEqual((j['status'], j['failures']), ('cancelled', 0))

    def test_restart_recovery_requeues_verified_empty_attempts(self):
        job = self.job(target='0x1234')
        self.lost_attempt(job)
        (self.claims / 'build').mkdir(parents=True)  # a claims database, as a prior scheduler left
        r.fleet_run.connect(self.claims).close()
        with patch.object(r.fleet_run, 'cgroup_state', return_value=False):
            r.recover(self.state, self.c, self.claims)
        j = self.rows('jobs')[0]
        self.assertEqual((j['status'], j['failures'], j['note']), ('queued', 0, r.INTERRUPTED))
        self.assertEqual(self.rows('attempts')[0]['status'], r.INTERRUPTED)
        self.assertEqual(self.rows('models')[0]['cooldown'], 0)
        # Requeued under the same job id, so it still owns the exclusive target.
        self.assertEqual(self.rows('jobs')[0]['id'], job)
        with self.assertRaises(sqlite3.IntegrityError):
            self.job(target='0x1234')

    def test_restart_recovery_retains_unknown_containment(self):
        job = self.job(target='0x1234')
        self.lost_attempt(job)
        with patch.object(r.fleet_run, 'cgroup_state', return_value=True):
            r.recover(self.state, self.c, self.claims)
        j = self.rows('jobs')[0]
        self.assertEqual((j['status'], j['failures'], j['note']), ('needs_review', 0, 'needs_review'))
        # recover() finishes at wall time, so the cooldown is a real timestamp.
        self.assertGreater(self.rows('models')[0]['cooldown'], time.time())
        with self.assertRaises(sqlite3.IntegrityError):
            self.job(target='0x1234')

    def test_finish_is_idempotent_for_interruptions(self):
        aid = self.attempt(self.job())
        self.finish(aid, r.INTERRUPTED)
        self.finish(aid, 'failure')  # a repeated finish is ignored, as for any kind
        j = self.rows('jobs')[0]
        self.assertEqual((j['status'], j['failures']), ('queued', 0))
        self.assertEqual(self.rows('attempts')[0]['status'], r.INTERRUPTED)

    def test_status_separates_interruptions_from_task_failures(self):
        job = self.job()
        for kind in (r.INTERRUPTED, 'failure', r.INTERRUPTED, 'timeout'):
            self.finish(self.attempt(job), kind)
        data = r.status(self.state, self.c)
        m = next(m for m in data['models'] if m['id'] == self.model)
        self.assertEqual((m['task_failures'], m['interruptions']), (2, 2))
        row = data['configurations'][0]
        self.assertEqual((row['attempts'], row['task_failures'], row['interruptions']), (4, 2, 2))
        self.assertEqual(len(data['attempts']), 4)
        with patch.object(r.sys, 'stdout', io.StringIO()):
            r.print_status(data)


if __name__=='__main__':unittest.main()
