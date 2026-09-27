"""No inference/network: account cache, policy, races and provider boundaries."""
import copy
from datetime import datetime, timezone
import json
import os
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch
import sys
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import opencode_go_budget as b
import opencode_router as r


def payload(used=20, reset=20000):
    return {'usage': {k: {'percent': used, 'status': 'rate-limited' if used == 100 else 'ok',
        'resetsAt': datetime.fromtimestamp(reset, timezone.utc).isoformat()}
        for k in ('rolling', 'weekly', 'monthly')}}


class BudgetTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.state = Path(self.tmp.name)
        self.c = r.config(r.DEFAULT_CONFIG)
        self.job = dict(tier='bulk', category='bulk', model=None, budget_justification='')
        self.cheap = next(m for m in self.c['models'] if b.economical(m, self.c))
        self.expensive = next(m for m in self.c['models'] if m['enabled'] and not b.economical(m, self.c))
        self.env = patch.dict(os.environ, {b.TOKEN_ENV: 'fixture-secret'})
        self.env.start(); self.addCleanup(self.env.stop)

    def seed(self, used=20, now=1000, reset=20000):
        with b.database(self.state) as db:
            b.write(db, dict(windows=b.parse_usage(payload(used, reset)), observed_at=now))
        return b.snapshot(self.state, self.c, now)

    def select(self, budget, job=None, active=None, history=()):
        return r.choose(self.c, job or self.job, active or {}, {}, history, 1000, budget)

    def test_parsing_and_provider_rounding(self):
        w = b.parse_usage(payload(63))['5h']
        self.assertEqual((w['used_percent'], w['remaining_percent']), (63,37))
        self.assertTrue(w['authoritative'])
        for bad in (float('nan'), -1, 101, True, '63'):
            with self.assertRaises(ValueError): b.parse_usage(payload(bad))
        d = payload(); del d['usage']['weekly']
        with self.assertRaises(KeyError): b.parse_usage(d)
        for ts in ('2026-10-01T00:00:00', 'garbage', None):
            d = payload(); d['usage']['rolling']['resetsAt'] = ts
            with self.assertRaises((ValueError,TypeError)): b.parse_usage(d)

    def test_all_thresholds_and_exact_edges(self):
        for remaining, mode in ((100,'normal'), (70.01,'normal'), (70,'economical'),
                (30,'economical'), (29.99,'restricted'), (10,'restricted'),
                (9.99,'conservation'), (0.01,'conservation'), (0,'exhausted')):
            with self.subTest(remaining=remaining):
                self.assertEqual(self.seed(100-remaining)['pacing_mode'],mode)
        self.c['go_budget']={'normal_remaining':80}
        self.assertEqual(self.seed(25)['pacing_mode'],'economical')

    def test_weekly_monthly_exhaustion_overrides_5h(self):
        for key in ('weekly','monthly'):
            d=payload(); d['usage'][key]['status']='rate-limited'
            with b.database(self.state) as db:
                b.write(db,dict(windows=b.parse_usage(d),observed_at=1000))
            self.assertEqual(b.snapshot(self.state,self.c,1000)['pacing_mode'],'exhausted')

    def test_cache_refresh_interval_and_failure_retains_last(self):
        calls=[]
        def fetch(*args): calls.append(1); return b.parse_usage(payload(63))
        self.assertTrue(b.refresh(self.state,self.c,1000,fetch))
        self.assertFalse(b.refresh(self.state,self.c,1299,fetch))
        self.assertEqual(len(calls),1)
        def fail(*args): raise OSError('credential must never appear')
        self.assertFalse(b.refresh(self.state,self.c,1300,fail))
        s=b.snapshot(self.state,self.c,1300)
        self.assertEqual(s['windows']['5h']['used_percent'],63)
        self.assertTrue(s['refresh_failed']); self.assertFalse(s['stale'])
        self.assertNotIn('credential must',json.dumps(s))
        self.assertTrue(b.snapshot(self.state,self.c,1900)['stale'])

    def test_missing_credentials_and_stale_conserve(self):
        with patch.dict(os.environ,{},clear=True):
            self.assertFalse(b.refresh(self.state,self.c,1000))
        s=b.snapshot(self.state,self.c,1000)
        self.assertEqual(s['error'],'credentials_missing')
        self.assertEqual(s['pacing_mode'],'stale')
        self.assertTrue(b.economical(self.select(s),self.c))
        self.assertIsNone(self.select(s, active={self.cheap['id']:1}))
        self.job['model']=self.expensive['id']
        self.assertIsNone(self.select(s))

    def test_window_boundaries_do_not_invent_recovery(self):
        self.seed(100,now=1000,reset=1100)
        for now in (1099.999,1100,1100.001,100000):
            self.assertTrue(b.snapshot(self.state,self.c,now)['exhausted'])
        self.seed(20,now=1000,reset=1100)
        self.assertFalse(b.snapshot(self.state,self.c,1099.999)['stale'])
        self.assertTrue(b.snapshot(self.state,self.c,1100)['stale'])
        self.assertTrue(b.snapshot(self.state,self.c,999)['stale'])
        self.assertEqual(b.timestamp('2026-10-01T00:00:00Z'),b.timestamp('2026-09-30T21:00:00-03:00'))
        self.assertLess(b.timestamp('2028-02-29T23:59:59Z'),b.timestamp('2028-03-01T00:00:00Z'))

    def test_explicit_expensive_override_obeys_pressure(self):
        self.job['model']=self.expensive['id']
        self.assertIsNotNone(self.select(self.seed(20)))
        self.assertIsNone(self.select(self.seed(40)))
        self.job.update(tier='escalation',category='escalation',budget_justification='valuable blocker')
        self.assertIsNotNone(self.select(self.seed(40)))
        self.assertIsNone(self.select(self.seed(80)))
        history=[dict(model=m['id'],status='failure',result=json.dumps({'report':{'outcome':'failure','approaches':['proven blocker']}}))
                 for m in self.c['models'] if b.economical(m,self.c)][:3]
        self.assertIsNotNone(self.select(self.seed(80),history=history))
        self.assertIsNone(self.select(self.seed(95),history=history))

    def test_cheap_selection_and_conservation_value(self):
        for used in (20,40,80): self.assertTrue(b.economical(self.select(self.seed(used)),self.c))
        s=self.seed(95)
        self.assertIsNone(self.select(s))
        self.job['budget_justification']='finish banked body; likely 400 verified bytes'
        self.assertTrue(b.economical(self.select(s),self.c))
        self.assertIsNone(self.select(s,active={self.cheap['id']:1}))

    def test_quota_overrides_snapshot_and_recovers_only_on_fresh_get(self):
        self.seed(20)
        b.quota(self.state,self.c,1001)
        self.assertIsNone(self.select(b.snapshot(self.state,self.c,1002)))
        self.assertFalse(b.refresh(self.state,self.c,1200,lambda *_:b.parse_usage(payload())))
        self.assertTrue(b.refresh(self.state,self.c,1301,lambda *_:b.parse_usage(payload())))
        self.assertFalse(b.snapshot(self.state,self.c,1301)['exhausted'])

    def test_quota_during_network_response_not_cleared(self):
        def fetch(*_):
            b.quota(self.state,self.c,1001)
            return b.parse_usage(payload())
        b.refresh(self.state,self.c,1000,fetch)
        self.assertTrue(b.snapshot(self.state,self.c,1002)['exhausted'])

    def test_refresh_lease_and_api_throttle(self):
        def fetch(*_):
            self.assertFalse(b.refresh(self.state,self.c,1001,lambda *_:self.fail('duplicate GET')))
            raise b.urllib.error.HTTPError(b.URL,429,'throttled',{'Retry-After':'1200'},None)
        b.refresh(self.state,self.c,1000,fetch)
        s=b.snapshot(self.state,self.c,1001)
        self.assertFalse(s['exhausted']); self.assertEqual(s['next_refresh'],2200)
        self.assertEqual(s['error'],'usage_http_429')

    def test_unmetered_requires_evidence_and_does_not_enable_go_free_models(self):
        self.assertTrue(all(m.get('metered',True) for m in self.c['models'] if m['id'].startswith('opencode-go/')))
        self.assertFalse(any('bunny' in m['id'] and m['enabled'] for m in self.c['models'] if m['id'].startswith('opencode-go/')))
        m=copy.deepcopy(self.cheap); m.update(metered=False,unmetered_evidence='fixture verified provider contract')
        self.c['models']=[m]
        self.assertEqual(self.select(self.seed(100)),m)
        del m['unmetered_evidence']
        p=self.state/'config.json'; p.write_text(json.dumps(self.c))
        with self.assertRaisesRegex(ValueError,'evidence'): r.config(p)

    def test_old_state_and_config_and_secret_isolation(self):
        self.c.pop('go_budget',None)
        jid=r.enqueue(self.state,'bulk','task')
        with r.database(self.state) as db:
            j=dict(db.execute('SELECT * FROM jobs WHERE id=?',(jid,)).fetchone())
        self.assertEqual(j['budget_justification'],'')
        self.assertIsNotNone(r.choose(self.c,j,{}, {},[],1000))
        self.assertNotIn(b.TOKEN_ENV,r.worker_env(self.cheap['id'],self.state))
        self.assertEqual(r.compact_status(self.state,self.c)['queued_count'],1)

    def test_corrupt_cache_and_durable_quota_fallback(self):
        jid=r.enqueue(self.state,'bulk','task')
        with r.database(self.state) as db:
            db.execute("INSERT INTO attempts(id,job,model,status,started,ended) VALUES('q',?,?,'quota',1000,1001)",(jid,self.cheap['id']))
        with b.database(self.state) as db:
            b.write(db, {'windows': {'5h': {}}})
        s=r.budget_snapshot(self.state,self.c)
        self.assertEqual(s['pacing_mode'],'exhausted')
        self.assertEqual(s['error'],'cache_unavailable')
        self.assertFalse(r.refresh_budget(self.state,self.c))

    def test_elapsed_reset_response_cannot_clear_quota(self):
        self.seed(100)
        b.quota(self.state,self.c,1001)
        self.assertFalse(b.refresh(self.state,self.c,1400,lambda *_:b.parse_usage(payload(reset=1400))))
        self.assertTrue(b.snapshot(self.state,self.c,1400)['exhausted'])

    def test_redirect_rejected_and_httpdate_throttle(self):
        self.assertIsNone(b.NoRedirect().redirect_request(None,None,302,'',{},'https://other.test'))
        def fetch(*_):
            raise b.urllib.error.HTTPError(b.URL,429,'',{'Retry-After':'Thu, 01 Jan 1970 01:00:00 GMT'},None)
        b.refresh(self.state,self.c,1000,fetch)
        self.assertEqual(b.snapshot(self.state,self.c,1000)['next_refresh'],3600)

    def test_stale_preserves_evidence_based_alternative_choice(self):
        s=self.seed(40)
        history=[dict(model=self.cheap['id'],status='failure',result='{}')]
        self.assertNotEqual(self.select(s,history=history)['id'],self.cheap['id'])

    def test_later_transport_error_cannot_hide_provider_quota(self):
        events=r.Events()
        events.feed(json.dumps({'type':'error','error':{'status':429}}))
        events.feed(json.dumps({'type':'error','error':{'message':'connection closed'}}))
        self.assertEqual(events.result(1)['kind'],'quota')
        self.assertEqual(events.result(1,'timeout')['kind'],'quota')

    def test_finish_quota_preserves_job_no_task_failure(self):
        jid=r.enqueue(self.state,'bulk','task')
        with r.database(self.state) as db:
            db.execute("INSERT INTO attempts(id,job,model,status,started) VALUES('a',?,?,'running',1000)",(jid,self.cheap['id']))
        r.finish(self.state,self.c,'a',dict(kind='quota'),1001)
        with r.database(self.state) as db:
            j=dict(db.execute('SELECT * FROM jobs WHERE id=?',(jid,)).fetchone())
        self.assertEqual(j['status'],'queued'); self.assertEqual(j['failures'],0)
        self.assertTrue(b.snapshot(self.state,self.c,1002)['exhausted'])

if __name__=='__main__': unittest.main()
