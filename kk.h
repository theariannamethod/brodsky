/*
 * kk.h — Knowledge Kernel (the library)
 *
 * Brodsky reads. His docs/ folder is his bookshelf.
 * Each document is parsed through vocab — words he recognizes become
 * gravitational attractors. Collocations from reading create new
 * Hebbian connections between words that never met in exhale/ corpus.
 * The poet who reads writes differently from the poet in a vacuum.
 *
 * Three mechanisms:
 * 1. Heavy words — most frequent vocab hits in a doc get rank-weighted boost
 * 2. Collocations — word pairs from docs create temporary Hebbian bonds
 * 3. Chamber mood — doc's emotion profile subtly shifts the chambers
 *
 * score = mass × (1 + corpus_pull) × (1 + dario) × (1 + kk_pull)
 *
 * Header-only. #include in brodsky.c after type definitions.
 * If docs/ folder is absent — silent fallback, zero overhead.
 *
 * (c) 2026 arianna method
 */

#ifndef KK_H
#define KK_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <dirent.h>

/* ─── CONSTANTS ────────────────────────────────────────────────────── */

#define KK_DOC_MAX          16      /* max documents in docs/ */
#define KK_HEAVY_MAX        32      /* heavy words per doc */
#define KK_COLLOC_MAX       512     /* collocation pairs per doc */
#define KK_COLLOC_WIN       5       /* co-occurrence window in doc text */
#define KK_HEAVY_WEIGHT     0.3f    /* heavy word boost in score */
#define KK_COLLOC_WEIGHT    0.5f    /* collocation boost in score */
#define KK_PROPHECY_PROB    0.15f   /* chance to inject doc word as prophecy per cycle */
#define KK_CHAMBER_BLEND    0.08f   /* doc emotion blended into chambers (8%) */

/* ─── DATA STRUCTURES ──────────────────────────────────────────────── */

typedef struct {
    int a, b;
    float weight;
} KKColloc;

typedef struct {
    char     name[64];
    int      heavy[KK_HEAVY_MAX];           /* vocab word IDs, ranked by freq */
    int      n_heavy;
    float    chamber_mood[6];               /* emotion profile: FEAR,LOVE,RAGE,VOID,FLOW,COMPLEX */
    KKColloc colloc[KK_COLLOC_MAX];         /* word pairs that co-occur */
    int      n_colloc;
} KKDoc;

typedef struct {
    KKDoc docs[KK_DOC_MAX];
    int   n_docs;
    int   active;                           /* index of currently resonant doc, -1 = none */
} KnowledgeKernel;

static KnowledgeKernel kk;

/* ─── INIT ─────────────────────────────────────────────────────────── */

static void kk_init(void) {
    memset(&kk, 0, sizeof(kk));
    kk.active = -1;
}

/* ─── INGEST ───────────────────────────────────────────────────────── */
/*
 * Dependencies from host (brodsky.c):
 *   find_vocab_word(const char *) → int
 *   vocab[i].emotion, .mass, .is_preposition, .is_connective
 *   vocab_size, MAX_VOCAB, EMO_COUNT
 */

static void kk_ingest_file(const char *path, const char *filename) {
    FILE *f = fopen(path, "r");
    if (!f) return;
    if (kk.n_docs >= KK_DOC_MAX) { fclose(f); return; }

    KKDoc *doc = &kk.docs[kk.n_docs];
    memset(doc, 0, sizeof(*doc));
    strncpy(doc->name, filename, sizeof(doc->name) - 1);

    /* read entire file, parse words, count vocab hits */
    int word_freq[MAX_VOCAB];
    memset(word_freq, 0, sizeof(int) * (size_t)vocab_size);

    /* track word sequence for collocations */
    int seq[65536];
    int seq_len = 0;

    char line[1024];
    while (fgets(line, (int)sizeof(line), f)) {
        char buf[128];
        int bi = 0;
        const unsigned char *p = (const unsigned char *)line;

        for (;; p++) {
            if (*p && *p != ' ' && *p != '\t' && *p != '\n' && *p != '\r'
                && *p != '.' && *p != ',' && *p != ';' && *p != ':'
                && *p != '(' && *p != ')' && *p != '"' && *p != '\'') {
                if (bi < 126) buf[bi++] = (char)*p;
            } else {
                if (bi > 0) {
                    buf[bi] = '\0';
                    int id = find_vocab_word(buf);
                    if (id >= 0) {
                        word_freq[id]++;
                        if (seq_len < 65536) seq[seq_len++] = id;
                    }
                    bi = 0;
                }
                if (!*p) break;
            }
        }
    }
    fclose(f);

    /* build emotion profile from ALL matched words (before heavy extraction) */
    static const int emo_to_ch_kk[EMO_COUNT] = {
        0, 4, 3, 4, 1, 3, 2, 1, 1
        /* TRAUMA→FEAR, JOY→FLOW, GRIEF→VOID, RESONANCE→FLOW, DESIRE→LOVE,
           VOID→VOID, RAGE→RAGE, TENDERNESS→LOVE, JULIA→LOVE */
    };
    float total_hits = 0;
    for (int i = 0; i < vocab_size; i++) {
        if (word_freq[i] > 0) {
            int ch = emo_to_ch_kk[vocab[i].emotion];
            doc->chamber_mood[ch] += (float)word_freq[i];
            total_hits += (float)word_freq[i];
        }
    }

    /* extract heavy words: top KK_HEAVY_MAX by frequency, filtered */
    doc->n_heavy = 0;
    int freq_copy[MAX_VOCAB];
    memcpy(freq_copy, word_freq, sizeof(int) * (size_t)vocab_size);
    for (int pick = 0; pick < KK_HEAVY_MAX * 3 && doc->n_heavy < KK_HEAVY_MAX; pick++) {
        int best = -1, best_freq = 0;
        for (int i = 0; i < vocab_size; i++) {
            if (freq_copy[i] > best_freq) {
                best = i; best_freq = freq_copy[i];
            }
        }
        if (best < 0 || best_freq < 2) break;
        freq_copy[best] = 0;  /* consumed */
        /* skip function words and low-mass filler */
        if (vocab[best].is_preposition || vocab[best].is_connective) continue;
        if (vocab[best].mass < 0.25f) continue;
        doc->heavy[doc->n_heavy++] = best;
    }
    /* normalize mood to [0,1] */
    if (total_hits > 0) {
        for (int c = 0; c < 6; c++)
            doc->chamber_mood[c] /= total_hits;
    }

    /* extract collocations: word pairs within window */
    doc->n_colloc = 0;
    for (int i = 0; i < seq_len && doc->n_colloc < KK_COLLOC_MAX; i++) {
        for (int j = i + 1; j < seq_len && j < i + KK_COLLOC_WIN; j++) {
            if (seq[i] == seq[j]) continue;
            float w = 1.0f / (float)(j - i);
            int found = -1;
            for (int k = 0; k < doc->n_colloc; k++) {
                if ((doc->colloc[k].a == seq[i] && doc->colloc[k].b == seq[j]) ||
                    (doc->colloc[k].a == seq[j] && doc->colloc[k].b == seq[i])) {
                    found = k; break;
                }
            }
            if (found >= 0) {
                doc->colloc[found].weight += w;
            } else if (doc->n_colloc < KK_COLLOC_MAX) {
                doc->colloc[doc->n_colloc].a = seq[i];
                doc->colloc[doc->n_colloc].b = seq[j];
                doc->colloc[doc->n_colloc].weight = w;
                doc->n_colloc++;
            }
        }
    }

    kk.n_docs++;
}

/* Scan docs/ directory and ingest all .txt files */
static void kk_load(void) {
    kk_init();

    static const char *bases[] = { "docs/", "./docs/", NULL };

    for (int b = 0; bases[b]; b++) {
        DIR *dir = opendir(bases[b]);
        if (!dir) continue;

        struct dirent *ent;
        while ((ent = readdir(dir)) != NULL) {
            int len = (int)strlen(ent->d_name);
            if (len < 5) continue;
            if (strcmp(ent->d_name + len - 4, ".txt") != 0) continue;

            char path[512];
            snprintf(path, sizeof(path), "%s%s", bases[b], ent->d_name);
            kk_ingest_file(path, ent->d_name);
        }
        closedir(dir);
        break;  /* found docs/ dir, done */
    }
}

/* ─── RUNTIME (scoring, doc selection, injection) ──────────────────── */

/* Find dominant chamber by maximum activation.
 * Takes chamber phases directly — no dependency on global org. */
static int kk_dominant_chamber(const float *phase, int n_ch) {
    int best = 0;
    float best_act = sinf(phase[0]);
    for (int i = 1; i < n_ch; i++) {
        float a = sinf(phase[i]);
        if (a > best_act) { best_act = a; best = i; }
    }
    return best;
}

/* Choose the most resonant document based on dominant chamber.
 * Caller passes chamber phases + rng function. */
static void kk_choose_doc(const float *ch_phase, int n_ch, float (*rng_fn)(void)) {
    if (kk.n_docs <= 0) { kk.active = -1; return; }

    int dom = kk_dominant_chamber(ch_phase, n_ch);
    float best_score = -1e30f;
    int best = 0;

    for (int d = 0; d < kk.n_docs; d++) {
        float score = kk.docs[d].chamber_mood[dom] * 10.0f;
        score += rng_fn() * 0.5f;
        if (score > best_score) { best_score = score; best = d; }
    }
    kk.active = best;
}

/* Score contribution from active doc's heavy words (rank-weighted) */
static float kk_heavy_score(int word_idx) {
    if (kk.active < 0) return 0.0f;
    KKDoc *doc = &kk.docs[kk.active];
    for (int i = 0; i < doc->n_heavy; i++) {
        if (doc->heavy[i] == word_idx)
            return 1.0f / (1.0f + (float)i);
    }
    return 0.0f;
}

/* Score contribution from active doc's collocations with last_word */
static float kk_colloc_score(int last_word, int cand_idx) {
    if (kk.active < 0 || last_word < 0) return 0.0f;
    KKDoc *doc = &kk.docs[kk.active];
    for (int i = 0; i < doc->n_colloc; i++) {
        if ((doc->colloc[i].a == last_word && doc->colloc[i].b == cand_idx) ||
            (doc->colloc[i].a == cand_idx && doc->colloc[i].b == last_word))
            return doc->colloc[i].weight;
    }
    return 0.0f;
}

/* Inject a heavy word from active doc as prophecy target.
 * Caller passes prophecy_add function pointer + rng. */
static void kk_prophecy_inject(void (*add_fn)(ProphecySystem*, int, float),
                               ProphecySystem *ps, float (*rng_fn)(void)) {
    if (kk.active < 0) return;
    KKDoc *doc = &kk.docs[kk.active];
    if (doc->n_heavy <= 0) return;

    int pick = 0;
    float r = rng_fn();
    for (int i = 0; i < doc->n_heavy; i++) {
        float threshold = 1.0f / (1.0f + (float)i);
        if (r < threshold * 0.3f) { pick = i; break; }
        pick = i;
    }
    add_fn(ps, doc->heavy[pick], 0.3f);
}

/* Blend active doc's mood into chamber phases (subtle background radiation) */
static void kk_blend_chambers(float *ch_phase, int n_ch) {
    if (kk.active < 0) return;
    KKDoc *doc = &kk.docs[kk.active];
    int lim = n_ch < 6 ? n_ch : 6;
    for (int c = 0; c < lim; c++) {
        ch_phase[c] += doc->chamber_mood[c] * KK_CHAMBER_BLEND;
    }
}

#endif /* KK_H */
