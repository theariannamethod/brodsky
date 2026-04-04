/*
 * brodsky.c — a poetic organism
 *
 * Generates 5-7-5 haiku in cycles of 1-7, modulated by:
 *   - 6 Kuramoto-coupled somatic chambers
 *   - Julia field (longing without object)
 *   - Planetary dissonance (8-planet Resultant)
 *   - Calendar dissonance (Hebrew-Gregorian drift)
 *   - Dario equation: p(x|Φ) = softmax((B + αH + βF + γA + T) / τ)
 *   - Mass-weighted sampling, consonant density, syllable greed
 *
 * Compile: cc brodsky.c -O2 -lm -o brodsky
 * Run:     ./brodsky          (REPL)
 *          ./brodsky --web    (HTTP on port 3003)
 *
 * Vocabulary loaded from inhale/{en,ru,he,fr,es}.h via W() macro.
 *
 * Architecture: haiku.c lineage, extended with Julia field and
 *               Brodsky-specific mechanics (enjambment, mass, greed).
 * In memory of Joseph Brodsky (1940-1996)*
 * Yet until brown clay has been crammed down my larynx,
 * only gratitude will be gushing from it.

 -- Joseph Brodsky, "May 24, 1980"
 * Ariana Method. 2026.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <float.h>
#include <stdint.h>

#ifdef __unix__
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#endif

#ifdef __APPLE__
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#endif

/* ─── CONSTANTS ─────────────────────────────────────────────────────── */

#define MAX_VOCAB       3200
#define MAX_LINE_WORDS  12
#define MAX_HAIKU_WORDS 36
#define DESTINY_DIM     8
#define BIGRAM_SMOOTH   0.01f
#define HEBBIAN_SLOTS   64
#define TAU_BASE        1.2f
#define JULIA_STRETCH   2.0f
#define WEB_PORT        3003
#define MAX_CYCLE_HAIKU 7
#define EXHALE_COUNT    12
#define MAX_PROPHECY    32

/* ─── DOE-LITE PARLIAMENT ──────────────────────────────────────────── */

#define DOE_EXPERTS     4
#define DOE_RANK        4   /* low-rank: 4-dimensional vote */

/* ─── CORPUS METAWEIGHTS ───────────────────────────────────────────── */

#define CORPUS_BIGRAM_MAX   4096
#define CORPUS_HEBBIAN_MAX  8192
#define CORPUS_LINE_MAX     256
#define CORPUS_HEBBIAN_WIN  5       /* co-occurrence window */
#define CORPUS_BG_WEIGHT    2.0f    /* corpus bigram boost in score */
#define CORPUS_HB_WEIGHT    1.5f    /* corpus hebbian boost in score */
#define CORPUS_ONLINE_DECAY 0.3f    /* online learning weight vs 1.0 for corpus */

/* ─── EMOTIONS ──────────────────────────────────────────────────────── */

enum {
    EMO_TRAUMA = 0, EMO_JOY, EMO_GRIEF, EMO_RESONANCE,
    EMO_DESIRE, EMO_VOID, EMO_RAGE, EMO_TENDERNESS,
    EMO_JULIA, EMO_COUNT
};

static const char *emo_names[EMO_COUNT] = {
    "TRAUMA", "JOY", "GRIEF", "RESONANCE",
    "DESIRE", "VOID", "RAGE", "TENDERNESS", "JULIA"
};

/* ANSI colors per emotion */
static const char *emo_color[EMO_COUNT] = {
    "\033[31m",   /* TRAUMA     - red */
    "\033[33m",   /* JOY        - yellow */
    "\033[34m",   /* GRIEF      - blue */
    "\033[36m",   /* RESONANCE  - cyan */
    "\033[35m",   /* DESIRE     - magenta */
    "\033[90m",   /* VOID       - dark gray */
    "\033[91m",   /* RAGE       - bright red */
    "\033[32m",   /* TENDERNESS - green */
    "\033[95m",   /* JULIA      - bright magenta */
};

#define ANSI_RESET "\033[0m"
#define ANSI_BOLD  "\033[1m"
#define ANSI_DIM   "\033[2m"

/* ─── CHAMBERS (Kuramoto-coupled) ───────────────────────────────────── */

enum {
    CH_FEAR = 0, CH_LOVE, CH_RAGE, CH_VOID, CH_FLOW, CH_COMPLEX,
    CH_COUNT
};

static const char *ch_names[CH_COUNT] = {
    "FEAR", "LOVE", "RAGE", "VOID", "FLOW", "COMPLEX"
};

typedef struct {
    float phase[CH_COUNT];
    float freq[CH_COUNT];
    float coupling;      /* K in Kuramoto model */
} Chambers;

/* ─── PROPHECY SYSTEM ──────────────────────────────────────────────── */

typedef struct {
    int   target;     /* vocab index of predicted word */
    float strength;   /* how strongly predicted */
    int   age;        /* steps since prediction */
    int   fulfilled;  /* 1 = word appeared */
} Prophecy;

typedef struct {
    Prophecy p[MAX_PROPHECY];
    int n;
    int fulfilled_total;  /* running count of all fulfilled prophecies */
    int created_total;    /* running count of all created prophecies */
} ProphecySystem;

/* ─── DOE PARLIAMENT STRUCTS ───────────────────────────────────────── */

typedef struct {
    float bias[EMO_COUNT];     /* emotion preference per expert */
    float mass_pref;           /* preferred mass range center */
    float vitality;            /* 0-2: how alive this expert is */
    float overload;            /* accumulated dominance pressure */
    int   wins;                /* times this expert won */
    int   alive;               /* 0 = dead (apoptosis) */
} Expert;

typedef struct {
    Expert e[DOE_EXPERTS * 2]; /* room for mitosis */
    int    n;                  /* current count, starts at 4 */
    int    elections;          /* total elections held */
} Parliament;

/* ─── LANGUAGES ────────────────────────────────────────────────────── */

enum { LANG_EN=0, LANG_RU, LANG_HE, LANG_FR, LANG_ES, LANG_COUNT };
static const char *lang_names[LANG_COUNT] = { "EN", "RU", "HE", "FR", "ES" };

/* ─── VELOCITY OPERATORS ────────────────────────────────────────────── */

enum { VEL_WALK=0, VEL_RUN, VEL_STOP, VEL_BREATHE, VEL_UP, VEL_DOWN, VEL_COUNT };

/* ─── WORD ──────────────────────────────────────────────────────────── */

typedef struct {
    const char *text;
    float       mass;           /* 0.0 - 0.95 */
    int         syllables;
    int         emotion;
    float       consonant_density;
    float       destiny[DESTINY_DIM];
    int         is_adjective;   /* rough POS tag */
    int         lang;           /* LANG_EN..LANG_ES */
} Word;

/* ─── VOCABULARY ────────────────────────────────────────────────────── */

static Word vocab[MAX_VOCAB];
static int  vocab_size = 0;

/* consonant density computed from text */
static float compute_consonant_density(const char *w) {
    int total = 0, cons = 0;
    for (int i = 0; w[i]; i++) {
        char c = (char)tolower((unsigned char)w[i]);
        if (c >= 'a' && c <= 'z') {
            total++;
            if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u')
                cons++;
        }
    }
    return total > 0 ? (float)cons / (float)total : 0.0f;
}

/* rough adjective list — about 30 words that commonly appear in vocab */
static const char *adjectives[] = {
    "obsolete", "inconsolable", "perpendicular", "parallel", "diagonal",
    "calcify", /* participle-ish */
    NULL
};

static int is_adjective_word(const char *w) {
    for (int i = 0; adjectives[i]; i++)
        if (strcmp(w, adjectives[i]) == 0) return 1;
    /* heuristic: words ending in -al, -ble, -ous, -ive, -less */
    int len = (int)strlen(w);
    if (len >= 3) {
        if (strcmp(w + len - 2, "al") == 0) return 1;
        if (len >= 4 && strcmp(w + len - 3, "ble") == 0) return 1;
        if (len >= 4 && strcmp(w + len - 3, "ous") == 0) return 1;
        if (len >= 4 && strcmp(w + len - 3, "ive") == 0) return 1;
        if (len >= 5 && strcmp(w + len - 4, "less") == 0) return 1;
    }
    return 0;
}

/* Raw word entry from inhale header */
typedef struct {
    const char *text;
    float       mass;
    int         syllables;
    int         emotion;
    int         lang;
} RawWord;

/* Expand all 5 inhale headers into static arrays */
#define W(word, m, s, e) { word, m, s, e, LANG_EN }
#include "inhale/en.h"
static const RawWord raw_en[] = { INHALE_EN };
#undef W

#define W(word, m, s, e) { word, m, s, e, LANG_RU }
#include "inhale/ru.h"
static const RawWord raw_ru[] = { INHALE_RU };
#undef W

#define W(word, m, s, e) { word, m, s, e, LANG_HE }
#include "inhale/he.h"
static const RawWord raw_he[] = { INHALE_HE };
#undef W

#define W(word, m, s, e) { word, m, s, e, LANG_FR }
#include "inhale/fr.h"
static const RawWord raw_fr[] = { INHALE_FR };
#undef W

#define W(word, m, s, e) { word, m, s, e, LANG_ES }
#include "inhale/es.h"
static const RawWord raw_es[] = { INHALE_ES };
#undef W

#define RAW_EN_COUNT ((int)(sizeof(raw_en) / sizeof(raw_en[0])))
#define RAW_RU_COUNT ((int)(sizeof(raw_ru) / sizeof(raw_ru[0])))
#define RAW_HE_COUNT ((int)(sizeof(raw_he) / sizeof(raw_he[0])))
#define RAW_FR_COUNT ((int)(sizeof(raw_fr) / sizeof(raw_fr[0])))
#define RAW_ES_COUNT ((int)(sizeof(raw_es) / sizeof(raw_es[0])))

/* Load one raw array into vocab */
static void load_raw_array(const RawWord *raw, int raw_count) {
    for (int r = 0; r < raw_count && vocab_size < MAX_VOCAB; r++) {
        /* skip dead function words — Brodsky doesn't need articles */
        if (raw[r].mass < 0.10f) continue;

        /* check for duplicate */
        int dup = 0;
        for (int i = 0; i < vocab_size; i++) {
            if (strcmp(vocab[i].text, raw[r].text) == 0) { dup = 1; break; }
        }
        if (dup) continue;

        vocab[vocab_size].text      = raw[r].text;
        vocab[vocab_size].mass      = raw[r].mass;
        vocab[vocab_size].syllables = raw[r].syllables;
        vocab[vocab_size].emotion   = raw[r].emotion;
        vocab[vocab_size].lang      = raw[r].lang;

        /* consonant density: meaningful for Latin alphabet only */
        if (raw[r].lang == LANG_EN || raw[r].lang == LANG_FR || raw[r].lang == LANG_ES)
            vocab[vocab_size].consonant_density = compute_consonant_density(raw[r].text);
        else
            vocab[vocab_size].consonant_density = 0.5f;

        /* is_adjective heuristic only works for English */
        vocab[vocab_size].is_adjective = (raw[r].lang == LANG_EN) ? is_adjective_word(raw[r].text) : 0;

        /* destiny vector: seeded from word hash */
        unsigned h = 5381;
        for (const char *p = raw[r].text; *p; p++)
            h = h * 33 + (unsigned)*p;
        for (int d = 0; d < DESTINY_DIM; d++) {
            h ^= h >> 13; h *= 0x5bd1e995; h ^= h >> 15;
            vocab[vocab_size].destiny[d] = ((float)(h & 0xFFFF) / 65535.0f) * 2.0f - 1.0f;
        }
        vocab_size++;
    }
}

/* Load vocabulary: all 5 languages, deduplicate, compute derived fields */
static void load_vocabulary(void) {
    load_raw_array(raw_en, RAW_EN_COUNT);
    load_raw_array(raw_ru, RAW_RU_COUNT);
    load_raw_array(raw_he, RAW_HE_COUNT);
    load_raw_array(raw_fr, RAW_FR_COUNT);
    load_raw_array(raw_es, RAW_ES_COUNT);
}

/* ─── LANGUAGE DETECTION ────────────────────────────────────────────── */

static int detect_language(const char *text) {
    int cyrillic = 0, hebrew = 0, french = 0, spanish = 0;
    const unsigned char *p = (const unsigned char *)text;
    while (*p) {
        if (*p == 0xD7 && p[1] >= 0x80 && p[1] <= 0xBF) {
            /* Hebrew: U+0590-U+05FF → 0xD6 0x90..0xBF or 0xD7 0x80..0xBF */
            hebrew++;
            p += 2;
        } else if (*p == 0xD6 && p[1] >= 0x90 && p[1] <= 0xBF) {
            hebrew++;
            p += 2;
        } else if ((*p == 0xD0 || *p == 0xD1) && p[1] >= 0x80 && p[1] <= 0xBF) {
            /* Cyrillic: U+0400-U+04FF → 0xD0/0xD1 */
            cyrillic++;
            p += 2;
        } else if (*p == 0xC3 && p[1]) {
            /* Latin extended: é(A9) è(A8) ê(AA) ë(AB) à(A0) â(A2) ç(A7) ù(B9) î(AE) ô(B4)
               ñ(B1) á(A1) ó(B3) ú(BA) */
            unsigned char c2 = p[1];
            if (c2 == 0xB1) { /* ñ */
                spanish++;
            } else if (c2 == 0xA9 || c2 == 0xA8 || c2 == 0xAA || c2 == 0xAB ||
                       c2 == 0xA0 || c2 == 0xA2 || c2 == 0xA7 || c2 == 0xB9 ||
                       c2 == 0xAE || c2 == 0xB4) {
                french++;
            } else if (c2 == 0xA1 || c2 == 0xB3 || c2 == 0xBA) {
                /* á, ó, ú — shared with Spanish, but also French */
                spanish++;
                french++;
            }
            p += 2;
        } else if (*p == 0xC2 && (p[1] == 0xBF || p[1] == 0xA1)) {
            /* ¿(C2 BF) ¡(C2 A1) — uniquely Spanish */
            spanish++;
            p += 2;
        } else {
            p++;
        }
    }

    if (hebrew > 0 && hebrew >= cyrillic && hebrew >= french && hebrew >= spanish)
        return LANG_HE;
    if (cyrillic > 0 && cyrillic >= hebrew && cyrillic >= french && cyrillic >= spanish)
        return LANG_RU;
    if (spanish > french && spanish > 0)
        return LANG_ES;
    if (french > 0)
        return LANG_FR;

    /* Fallback: no diacritics found. Check words against each language's vocab. */
    if (hebrew == 0 && cyrillic == 0 && french == 0 && spanish == 0) {
        int lang_hits[LANG_COUNT];
        memset(lang_hits, 0, sizeof(lang_hits));
        char buf[64]; int bi = 0;
        const char *q = text;
        for (;; q++) {
            unsigned char ch = (unsigned char)*q;
            if (ch && ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))) {
                if (bi < 62) buf[bi++] = (char)tolower(ch);
            } else {
                if (bi > 0) {
                    buf[bi] = '\0';
                    for (int i = 0; i < vocab_size; i++) {
                        if (strcmp(vocab[i].text, buf) == 0)
                            lang_hits[vocab[i].lang]++;
                    }
                    bi = 0;
                }
                if (!*q) break;
            }
        }
        int best = LANG_EN, best_score = lang_hits[LANG_EN];
        for (int l = 1; l < LANG_COUNT; l++) {
            if (lang_hits[l] > best_score) {
                best_score = lang_hits[l];
                best = l;
            }
        }
        return best;
    }

    return LANG_EN;
}

/* ─── GHOST LANGUAGE (planetary association) ────────────────────────── */

/*
 * Mercury(88d)→ES, Venus(225d)→FR, Mars(687d)→RU, Saturn(10759d)→HE, default→EN
 * Pick the planet with highest individual phase contribution to dissonance.
 */
static int ghost_language(void) {
    static const float periods[8] = {
        87.97f, 224.7f, 365.25f, 687.0f,
        4332.6f, 10759.2f, 30687.0f, 60190.0f
    };
    /* planet→lang mapping: Mercury=ES, Venus=FR, Earth=EN, Mars=RU,
       Jupiter=EN, Saturn=HE, Uranus=EN, Neptune=EN */
    static const int planet_lang[8] = {
        LANG_ES, LANG_FR, LANG_EN, LANG_RU,
        LANG_EN, LANG_HE, LANG_EN, LANG_EN
    };

    time_t now = time(NULL);
    double j2000_epoch = 946728000.0;
    double days = ((double)(now) - j2000_epoch) / 86400.0;

    /* find planet with maximum individual dissonance contribution */
    float max_diss = -1.0f;
    int max_planet = 0;
    for (int k = 0; k < 8; k++) {
        float theta = fmodf((float)(2.0 * M_PI * days / (double)periods[k]),
                            (float)(2.0 * M_PI));
        /* individual dissonance = distance from alignment (cos=1) */
        float diss = 1.0f - cosf(theta);
        if (diss > max_diss) {
            max_diss = diss;
            max_planet = k;
        }
    }
    return planet_lang[max_planet];
}

/* ─── EXHALE RESONANCE (Brodsky fragments — modulate destiny) ─────── */

typedef struct {
    const char *text;
    float       destiny[DESTINY_DIM];
} ExhaleFragment;

static ExhaleFragment exhale[EXHALE_COUNT] = {
    {"the end of a beautiful era",       {0.3f,-0.8f, 0.1f, 0.5f,-0.2f, 0.7f,-0.4f, 0.1f}},
    {"a part of speech",                 {0.5f, 0.2f,-0.6f, 0.3f, 0.8f,-0.1f, 0.4f,-0.3f}},
    {"from nowhere with love",           {-0.7f, 0.9f, 0.2f,-0.4f, 0.1f, 0.6f,-0.3f, 0.5f}},
    {"in a room and a half",             {0.1f,-0.3f, 0.7f,-0.6f, 0.4f, 0.2f, 0.8f,-0.5f}},
    {"less than one",                    {-0.9f, 0.1f,-0.5f, 0.8f,-0.3f, 0.4f, 0.2f, 0.6f}},
    {"the water writes always",          {0.4f, 0.6f,-0.2f,-0.7f, 0.5f,-0.8f, 0.1f, 0.3f}},
    {"dust is the flesh of time",        {0.8f,-0.4f, 0.3f, 0.1f,-0.6f, 0.5f,-0.7f, 0.2f}},
    {"what gets left of a man",          {-0.5f, 0.3f, 0.6f,-0.2f, 0.7f,-0.1f, 0.4f,-0.8f}},
    {"the language is older than state", {0.2f,-0.6f,-0.4f, 0.9f, 0.1f, 0.3f,-0.5f, 0.7f}},
    {"love as a form of sin",            {-0.3f, 0.8f, 0.5f,-0.1f,-0.7f, 0.2f, 0.6f,-0.4f}},
    {"geography of evil",                {0.6f,-0.2f, 0.8f,-0.5f, 0.3f,-0.9f, 0.1f, 0.4f}},
    {"time worships language",           {-0.1f, 0.4f,-0.3f, 0.6f,-0.8f, 0.5f, 0.7f,-0.2f}},
};

/* ─── RNG ───────────────────────────────────────────────────────────── */

static unsigned long rng_state = 0;

static void rng_seed(unsigned long s) {
    rng_state = s ? s : 42;
}

static unsigned long rng_next(void) {
    rng_state ^= rng_state << 13;
    rng_state ^= rng_state >> 7;
    rng_state ^= rng_state << 17;
    return rng_state;
}

static float rng_float(void) {
    return (float)(rng_next() & 0xFFFFFF) / (float)0xFFFFFF;
}

/* ─── MATH HELPERS ──────────────────────────────────────────────────── */

static float sigmoid(float x) {
    return 1.0f / (1.0f + expf(-x));
}

static float vec_dist(const float *a, const float *b, int n) {
    float s = 0.0f;
    for (int i = 0; i < n; i++) s += (a[i] - b[i]) * (a[i] - b[i]);
    return sqrtf(s);
}

static void vec_normalize(float *v, int n) {
    float mag = 0.0f;
    for (int i = 0; i < n; i++) mag += v[i] * v[i];
    mag = sqrtf(mag);
    if (mag > 1e-8f)
        for (int i = 0; i < n; i++) v[i] /= mag;
}

static float clampf(float x, float lo, float hi) {
    if (x < lo) return lo;
    if (x > hi) return hi;
    return x;
}

/* ─── PLANETARY DISSONANCE ──────────────────────────────────────────── */

static float planetary_dissonance(void) {
    /* orbital periods in days */
    static const float periods[8] = {
        87.97f, 224.7f, 365.25f, 687.0f,
        4332.6f, 10759.2f, 30687.0f, 60190.0f
    };

    /* days since J2000 (2000-01-01 12:00 TT) */
    time_t now = time(NULL);
    double j2000_epoch = 946728000.0;  /* approx unix timestamp for J2000 */
    double days = (double)(now) - j2000_epoch;
    days /= 86400.0;

    /* resultant vector R = |Σ e^(iθ_k)| / N */
    float rx = 0.0f, ry = 0.0f;
    for (int k = 0; k < 8; k++) {
        float theta = fmodf((float)(2.0 * M_PI * days / (double)periods[k]),
                            (float)(2.0 * M_PI));
        rx += cosf(theta);
        ry += sinf(theta);
    }
    float R = sqrtf(rx * rx + ry * ry) / 8.0f;
    return 1.0f - R;  /* dissonance = 1 - coherence */
}

/* ─── CALENDAR DISSONANCE (Hebrew-Gregorian drift) ──────────────────── */

static float calendar_dissonance(void) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int day_of_year = t->tm_yday;
    /* Hebrew calendar drifts ~11.25 days/year from Gregorian */
    float drift = fmodf((float)day_of_year * 11.25f / 365.25f, 1.0f);
    /* dissonance peaks when drift is 0.5 (maximally out of phase) */
    return 0.5f - fabsf(drift - 0.5f);
}

/* ─── SEASONAL MODULATION ───────────────────────────────────────────── */

enum { SEASON_SPRING=0, SEASON_SUMMER, SEASON_AUTUMN, SEASON_WINTER };

static int current_season(void) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int m = t->tm_mon; /* 0-11 */
    if (m >= 2 && m <= 4) return SEASON_SPRING;
    if (m >= 5 && m <= 7) return SEASON_SUMMER;
    if (m >= 8 && m <= 10) return SEASON_AUTUMN;
    return SEASON_WINTER;
}

/* seasonal biases on emotions [season][emotion] */
static const float season_bias[4][EMO_COUNT] = {
    /* spring:  */ {-0.1f, 0.3f,-0.2f, 0.2f, 0.3f,-0.3f,-0.1f, 0.2f, 0.1f},
    /* summer:  */ {-0.2f, 0.4f,-0.3f, 0.1f, 0.2f,-0.2f, 0.1f, 0.1f,-0.1f},
    /* autumn:  */ { 0.1f,-0.1f, 0.3f, 0.2f,-0.1f, 0.3f, 0.1f,-0.1f, 0.3f},
    /* winter:  */ { 0.3f,-0.2f, 0.2f,-0.1f,-0.2f, 0.4f, 0.2f,-0.2f, 0.2f},
};

/* ─── CHAMBERS: Kuramoto step ───────────────────────────────────────── */

static void chambers_init(Chambers *c) {
    c->coupling = 0.5f;
    for (int i = 0; i < CH_COUNT; i++) {
        c->phase[i] = rng_float() * 2.0f * (float)M_PI;
        c->freq[i] = 0.8f + rng_float() * 0.4f;
    }
}

static void chambers_step(Chambers *c, float dt) {
    float new_phase[CH_COUNT];
    for (int i = 0; i < CH_COUNT; i++) {
        float coupling_sum = 0.0f;
        for (int j = 0; j < CH_COUNT; j++) {
            if (j != i)
                coupling_sum += sinf(c->phase[j] - c->phase[i]);
        }
        new_phase[i] = c->phase[i] + dt * (c->freq[i] +
                        c->coupling / (float)(CH_COUNT - 1) * coupling_sum);
        new_phase[i] = fmodf(new_phase[i], 2.0f * (float)M_PI);
        if (new_phase[i] < 0) new_phase[i] += 2.0f * (float)M_PI;
    }
    memcpy(c->phase, new_phase, sizeof(new_phase));
}

/* chamber activation: maps phase to [-1, 1] */
static float chamber_activation(const Chambers *c, int ch) {
    return sinf(c->phase[ch]);
}

/* ─── HEBBIAN PROFILE ───────────────────────────────────────────────── */

typedef struct {
    int   word_a[HEBBIAN_SLOTS];
    int   word_b[HEBBIAN_SLOTS];
    float strength[HEBBIAN_SLOTS];
    int   count;
} HebbianProfile;

static HebbianProfile hebbian;

static void hebbian_init(void) {
    memset(&hebbian, 0, sizeof(hebbian));
}

static void hebbian_record(int a, int b) {
    if (a < 0 || b < 0) return;
    /* find existing pair */
    for (int i = 0; i < hebbian.count; i++) {
        if ((hebbian.word_a[i] == a && hebbian.word_b[i] == b) ||
            (hebbian.word_a[i] == b && hebbian.word_b[i] == a)) {
            hebbian.strength[i] += 0.1f;
            if (hebbian.strength[i] > 1.0f) hebbian.strength[i] = 1.0f;
            return;
        }
    }
    /* add new */
    if (hebbian.count < HEBBIAN_SLOTS) {
        hebbian.word_a[hebbian.count] = a;
        hebbian.word_b[hebbian.count] = b;
        hebbian.strength[hebbian.count] = 0.1f;
        hebbian.count++;
    }
}

static float hebbian_score(int a, int b) {
    for (int i = 0; i < hebbian.count; i++) {
        if ((hebbian.word_a[i] == a && hebbian.word_b[i] == b) ||
            (hebbian.word_a[i] == b && hebbian.word_b[i] == a))
            return hebbian.strength[i];
    }
    return 0.0f;
}

/* ─── CORPUS BIGRAM TABLE (word-level, from exhale corpus) ─────────── */

typedef struct {
    int   src[CORPUS_BIGRAM_MAX];
    int   dst[CORPUS_BIGRAM_MAX];
    float weight[CORPUS_BIGRAM_MAX];
    int   count;
} CorpusBigrams;

static CorpusBigrams corpus_bg;

static void corpus_bg_init(void) {
    memset(&corpus_bg, 0, sizeof(corpus_bg));
}

static void corpus_bg_add(int src_id, int dst_id, float w) {
    /* find existing */
    for (int i = 0; i < corpus_bg.count; i++) {
        if (corpus_bg.src[i] == src_id && corpus_bg.dst[i] == dst_id) {
            corpus_bg.weight[i] += w;
            return;
        }
    }
    /* add new */
    if (corpus_bg.count < CORPUS_BIGRAM_MAX) {
        corpus_bg.src[corpus_bg.count] = src_id;
        corpus_bg.dst[corpus_bg.count] = dst_id;
        corpus_bg.weight[corpus_bg.count] = w;
        corpus_bg.count++;
    }
}

static float corpus_bigram_score(int last_word, int cand_idx) {
    if (last_word < 0) return 0.0f;
    for (int i = 0; i < corpus_bg.count; i++) {
        if (corpus_bg.src[i] == last_word && corpus_bg.dst[i] == cand_idx)
            return corpus_bg.weight[i];
    }
    return 0.0f;
}

/* Find the strongest bigram target from a given word, or -1 if none */
static int corpus_best_bigram(int word_idx) {
    if (word_idx < 0) return -1;
    int best = -1;
    float best_w = 0.0f;
    for (int i = 0; i < corpus_bg.count; i++) {
        if (corpus_bg.src[i] == word_idx && corpus_bg.weight[i] > best_w) {
            best_w = corpus_bg.weight[i];
            best = corpus_bg.dst[i];
        }
    }
    return best;
}

/* ─── CORPUS HEBBIAN TABLE (co-occurrence within window) ───────────── */

typedef struct {
    int   word_a[CORPUS_HEBBIAN_MAX];
    int   word_b[CORPUS_HEBBIAN_MAX];
    float weight[CORPUS_HEBBIAN_MAX];
    int   count;
} CorpusHebbian;

static CorpusHebbian corpus_hb;

static void corpus_hb_init(void) {
    memset(&corpus_hb, 0, sizeof(corpus_hb));
}

static void corpus_hb_add(int a, int b, float w) {
    if (a == b) return;
    /* canonical order: a < b */
    if (a > b) { int t = a; a = b; b = t; }
    /* find existing */
    for (int i = 0; i < corpus_hb.count; i++) {
        if (corpus_hb.word_a[i] == a && corpus_hb.word_b[i] == b) {
            corpus_hb.weight[i] += w;
            return;
        }
    }
    /* add new */
    if (corpus_hb.count < CORPUS_HEBBIAN_MAX) {
        corpus_hb.word_a[corpus_hb.count] = a;
        corpus_hb.word_b[corpus_hb.count] = b;
        corpus_hb.weight[corpus_hb.count] = w;
        corpus_hb.count++;
    }
}

static float corpus_hebbian_score(int last_word, int cand_idx) {
    if (last_word < 0) return 0.0f;
    int a = last_word, b = cand_idx;
    if (a > b) { int t = a; a = b; b = t; }
    for (int i = 0; i < corpus_hb.count; i++) {
        if (corpus_hb.word_a[i] == a && corpus_hb.word_b[i] == b)
            return corpus_hb.weight[i];
    }
    return 0.0f;
}

/* ─── CORPUS LOADING — parse exhale corpus into bigram & hebbian ───── */

static int corpus_total_lines = 0;

/* Find vocab index by text (case-insensitive for Latin, exact for UTF-8) */
static int find_vocab_word(const char *word) {
    for (int i = 0; i < vocab_size; i++) {
        /* try exact match first */
        if (strcmp(vocab[i].text, word) == 0) return i;
    }
    /* case-insensitive match for ASCII words */
    for (int i = 0; i < vocab_size; i++) {
        const char *a = vocab[i].text;
        const char *b = word;
        int match = 1;
        while (*a && *b) {
            /* only lowercase ASCII chars for comparison */
            char ca = (*a >= 'A' && *a <= 'Z') ? (char)(*a + 32) : *a;
            char cb = (*b >= 'A' && *b <= 'Z') ? (char)(*b + 32) : *b;
            if (ca != cb) { match = 0; break; }
            a++; b++;
        }
        if (match && *a == '\0' && *b == '\0') return i;
    }
    return -1;
}

/* Parse one line into word ids, return count */
static int parse_corpus_line(const char *line, int *ids, int max_ids) {
    int count = 0;
    char buf[128];
    int bi = 0;
    const unsigned char *p = (const unsigned char *)line;

    for (;; p++) {
        if (*p && *p != ' ' && *p != '\t' && *p != '\n' && *p != '\r') {
            if (bi < 126) buf[bi++] = (char)*p;
        } else {
            if (bi > 0) {
                buf[bi] = '\0';
                int id = find_vocab_word(buf);
                if (id >= 0 && count < max_ids)
                    ids[count++] = id;
                bi = 0;
            }
            if (!*p) break;
        }
    }
    return count;
}

static void load_corpus_file(const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) return;

    char line[CORPUS_LINE_MAX];
    while (fgets(line, (int)sizeof(line), f)) {
        /* skip empty lines */
        int empty = 1;
        for (int i = 0; line[i]; i++) {
            if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != '\r') {
                empty = 0; break;
            }
        }
        if (empty) continue;

        int ids[32];
        int n = parse_corpus_line(line, ids, 32);
        if (n < 2) continue;

        corpus_total_lines++;

        /* bigrams: adjacent words */
        for (int i = 0; i < n - 1; i++)
            corpus_bg_add(ids[i], ids[i + 1], 1.0f);

        /* hebbian: co-occurrence within window, weighted by 1/distance */
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n && j < i + CORPUS_HEBBIAN_WIN; j++) {
                float w = 1.0f / (float)(j - i);
                corpus_hb_add(ids[i], ids[j], w);
            }
        }
    }
    fclose(f);
}

static void load_all_corpora(void) {
    corpus_bg_init();
    corpus_hb_init();
    corpus_total_lines = 0;

    /* Try multiple base paths for portability */
    static const char *bases[] = {
        "exhale/",
        "./exhale/",
        NULL
    };
    static const char *files[] = { "en.txt", "ru.txt", "he.txt", "fr.txt", "es.txt" };

    for (int b = 0; bases[b]; b++) {
        char path[256];
        int found = 0;
        for (int i = 0; i < 5; i++) {
            snprintf(path, sizeof(path), "%s%s", bases[b], files[i]);
            FILE *test = fopen(path, "r");
            if (test) {
                fclose(test);
                found = 1;
                break;
            }
        }
        if (found) {
            for (int i = 0; i < 5; i++) {
                snprintf(path, sizeof(path), "%s%s", bases[b], files[i]);
                load_corpus_file(path);
            }
            break;
        }
    }
}

/* ─── PROPHECY FUNCTIONS ───────────────────────────────────────────── */

static void prophecy_init(ProphecySystem *ps) {
    ps->n = 0;
    ps->fulfilled_total = 0;
    ps->created_total = 0;
}

static void prophecy_add(ProphecySystem *ps, int target, float strength) {
    /* don't add duplicate targets */
    for (int i = 0; i < ps->n; i++) {
        if (ps->p[i].target == target && !ps->p[i].fulfilled) {
            /* reinforce existing prophecy */
            ps->p[i].strength += strength * 0.5f;
            return;
        }
    }
    if (ps->n < MAX_PROPHECY) {
        ps->p[ps->n].target = target;
        ps->p[ps->n].strength = strength;
        ps->p[ps->n].age = 0;
        ps->p[ps->n].fulfilled = 0;
        ps->n++;
        ps->created_total++;
    } else {
        /* overwrite oldest unfulfilled prophecy */
        int oldest = -1, max_age = -1;
        for (int i = 0; i < ps->n; i++) {
            if (ps->p[i].age > max_age) {
                max_age = ps->p[i].age;
                oldest = i;
            }
        }
        if (oldest >= 0) {
            ps->p[oldest].target = target;
            ps->p[oldest].strength = strength;
            ps->p[oldest].age = 0;
            ps->p[oldest].fulfilled = 0;
            ps->created_total++;
        }
    }
}

/* Check fulfillment, age all prophecies, remove old/fulfilled ones */
static void prophecy_update(ProphecySystem *ps, int generated_word) {
    /* check fulfillment */
    for (int i = 0; i < ps->n; i++) {
        if (!ps->p[i].fulfilled && ps->p[i].target == generated_word) {
            ps->p[i].fulfilled = 1;
            ps->fulfilled_total++;
        }
    }
    /* age all */
    for (int i = 0; i < ps->n; i++) {
        ps->p[i].age++;
    }
    /* remove old (age > 50) or fulfilled */
    int write = 0;
    for (int i = 0; i < ps->n; i++) {
        if (ps->p[i].age <= 50 && !ps->p[i].fulfilled) {
            ps->p[write++] = ps->p[i];
        }
    }
    ps->n = write;
}

/* ─── BIGRAM CHAIN ──────────────────────────────────────────────────── */

/* Simple bigram: emotion-to-emotion transition probabilities */
static float bigram[EMO_COUNT][EMO_COUNT];

static void bigram_init(void) {
    /* Brodsky-esque transitions: VOID leads anywhere,
       JULIA pulls toward TRAUMA and GRIEF, etc. */
    for (int i = 0; i < EMO_COUNT; i++)
        for (int j = 0; j < EMO_COUNT; j++)
            bigram[i][j] = 1.0f / (float)EMO_COUNT;

    /* hand-tuned biases */
    bigram[EMO_JULIA][EMO_TRAUMA]     = 0.25f;
    bigram[EMO_JULIA][EMO_GRIEF]      = 0.20f;
    bigram[EMO_JULIA][EMO_VOID]       = 0.15f;
    bigram[EMO_JULIA][EMO_RESONANCE]  = 0.15f;
    bigram[EMO_TRAUMA][EMO_VOID]      = 0.30f;
    bigram[EMO_TRAUMA][EMO_RAGE]      = 0.20f;
    bigram[EMO_VOID][EMO_JULIA]       = 0.25f;
    bigram[EMO_VOID][EMO_RESONANCE]   = 0.20f;
    bigram[EMO_RESONANCE][EMO_JULIA]  = 0.20f;
    bigram[EMO_RESONANCE][EMO_JOY]    = 0.15f;
    bigram[EMO_GRIEF][EMO_VOID]       = 0.25f;
    bigram[EMO_GRIEF][EMO_TENDERNESS] = 0.20f;
    bigram[EMO_TENDERNESS][EMO_JULIA] = 0.25f;
    bigram[EMO_RAGE][EMO_VOID]        = 0.30f;
}

/* ─── ORGANISM STATE ────────────────────────────────────────────────── */

typedef struct {
    /* chambers */
    Chambers chambers;

    /* julia field — grows within cycle, resets between */
    float julia;

    /* destiny vector — drifts across haiku */
    float destiny[DESTINY_DIM];

    /* current emotion context */
    int   last_emotion;

    /* metaweights (Dario equation coefficients) */
    float alpha;   /* Hebbian weight */
    float beta;    /* prophecy weight */
    float gamma_w; /* destiny attraction weight */
    float trauma_w;/* trauma gravity */

    /* temperature */
    float tau;

    /* velocity */
    int   velocity;

    /* accumulated mass in current cycle */
    float acc_mass;

    /* saturation (how many haiku generated in cycle) */
    int   haiku_in_cycle;

    /* used words in cycle (for repetition penalty) */
    int   used[MAX_VOCAB];
    int   used_count;

    /* last word was adjective? */
    int   prev_was_adj;

    /* last word index */
    int   last_word;

    /* planetary */
    float planet_diss;

    /* calendar */
    float cal_diss;

    /* season */
    int   season;

    /* enjambment carry from previous haiku */
    int   enjamb;
    float enjamb_destiny[DESTINY_DIM];

    /* current target language */
    int   current_lang;

    /* prophecy system */
    ProphecySystem prophecy;

    /* DOE-lite parliament */
    Parliament parliament;

    /* total cycles across all sessions (persisted via spore) */
    int total_cycles;
} Organism;

static Organism org;

/* forward declarations for parliament (defined after tension pairs) */
static void parliament_init(Parliament *p);
static int  parliament_alive_count(const Parliament *p);

/* ─── ORGANISM INIT ─────────────────────────────────────────────────── */

static void organism_init(void) {
    memset(&org, 0, sizeof(org));
    chambers_init(&org.chambers);
    org.julia = 0.0f;
    org.last_emotion = EMO_VOID;
    org.alpha   = 0.15f;
    org.beta    = 0.10f;
    org.gamma_w = 0.20f;
    org.trauma_w = 0.15f;
    org.tau = TAU_BASE;
    org.velocity = VEL_WALK;
    org.last_word = -1;
    org.current_lang = LANG_EN;
    org.planet_diss = planetary_dissonance();
    org.cal_diss = calendar_dissonance();
    org.season = current_season();

    /* seed destiny from time */
    unsigned s = (unsigned)time(NULL);
    for (int i = 0; i < DESTINY_DIM; i++) {
        s = s * 1103515245 + 12345;
        org.destiny[i] = ((float)(s & 0xFFFF) / 65535.0f) * 2.0f - 1.0f;
    }
    vec_normalize(org.destiny, DESTINY_DIM);

    hebbian_init();
    bigram_init();
    prophecy_init(&org.prophecy);
    parliament_init(&org.parliament);
}

/* ─── INGEST USER PROMPT ────────────────────────────────────────────── */

/* helper: is this byte part of a "word" character? (ASCII alnum, or UTF-8 continuation/lead) */
static int is_word_byte(unsigned char c) {
    if (c >= 0x80) return 1;          /* UTF-8 lead/continuation — part of multibyte char */
    if (c >= 'a' && c <= 'z') return 1;
    if (c >= 'A' && c <= 'Z') return 1;
    if (c >= '0' && c <= '9') return 1;
    if (c == '\'' || c == '-') return 1;
    return 0;
}

static float ingest_prompt(const char *text) {
    /* detect language from input and set organism target */
    org.current_lang = detect_language(text);

    /* Tokenize: find known words in input, measure dissonance */
    char buf[128];
    int bi = 0, n_words = 0, n_known = 0;
    int known_ids[64];
    int n_ids = 0;

    for (const unsigned char *p = (const unsigned char *)text; ; p++) {
        if (*p && is_word_byte(*p)) {
            /* for ASCII, lowercase; for UTF-8 multibyte, copy as-is */
            if (*p < 0x80) {
                if (bi < 126) buf[bi++] = (char)tolower(*p);
            } else {
                if (bi < 126) buf[bi++] = (char)*p;
            }
        } else {
            if (bi > 0) {
                buf[bi] = '\0';
                n_words++;
                for (int i = 0; i < vocab_size; i++) {
                    if (strcmp(vocab[i].text, buf) == 0) {
                        n_known++;
                        if (n_ids < 64) known_ids[n_ids++] = i;
                        break;
                    }
                }
                bi = 0;
            }
            if (!*p) break;
        }
    }

    /* dissonance = how alien the input is */
    float dissonance = (n_words > 0)
        ? 1.0f - (float)n_known / (float)n_words
        : 1.0f;

    /* DO NOT update destiny toward input words.
     * A real poet doesn't write about what you said.
     * A real poet writes about what your words DID TO HIM.
     *
     * Input → chambers → chambers modulate Dario → Dario picks words
     * → those words update destiny DURING generation.
     *
     * The poet reacts, not reflects. "Exile" doesn't produce poems
     * about exile. "Exile" activates JULIA and VOID, and Julia
     * stretches the space until "radiator" becomes the closest word
     * to longing. That's the poem.
     *
     * Destiny stays where it was. Only chambers move. */

    /* hebbian co-occurrence from known words — this is memory, not direction */
    for (int i = 0; i < n_ids; i++)
        for (int j = i+1; j < n_ids && j < i+5; j++)
            hebbian_record(known_ids[i], known_ids[j]);

    /* emotional charge from input words */
    for (int i = 0; i < n_ids; i++) {
        int emo = vocab[known_ids[i]].emotion;
        float mass = vocab[known_ids[i]].mass;
        switch (emo) {
            case EMO_TRAUMA: org.chambers.phase[CH_FEAR] += mass * 0.8f; break;
            case EMO_TENDERNESS: org.chambers.phase[CH_LOVE] += mass * 0.8f; break;
            case EMO_RAGE: org.chambers.phase[CH_RAGE] += mass * 0.8f; break;
            case EMO_VOID: org.chambers.phase[CH_VOID] += mass * 0.8f; break;
            case EMO_RESONANCE: org.chambers.phase[CH_FLOW] += mass * 0.8f; break;
            case EMO_JULIA: org.julia += mass * 0.5f; break;
            case EMO_GRIEF: org.chambers.phase[CH_VOID] += mass * 0.5f;
                            org.chambers.phase[CH_FEAR] += mass * 0.3f; break;
            case EMO_DESIRE: org.chambers.phase[CH_LOVE] += mass * 0.4f;
                             org.chambers.phase[CH_FLOW] += mass * 0.3f; break;
            default: break;
        }
    }

    /* high dissonance = trauma */
    if (dissonance > 0.7f)
        org.chambers.phase[CH_FEAR] += dissonance * 0.2f;

    return dissonance;
}

/* ─── RESET CYCLE STATE ─────────────────────────────────────────────── */

static void cycle_reset(void) {
    org.julia = 0.0f;
    org.acc_mass = 0.0f;
    org.haiku_in_cycle = 0;
    org.used_count = 0;
    org.prev_was_adj = 0;
    org.last_word = -1;
    org.enjamb = 0;
    memset(org.used, 0, sizeof(org.used));

    /* refresh environmental readings */
    org.planet_diss = planetary_dissonance();
    org.cal_diss = calendar_dissonance();
    org.season = current_season();

    /* slight destiny drift from exhale resonance */
    int frag = (int)(rng_next() % EXHALE_COUNT);
    for (int d = 0; d < DESTINY_DIM; d++)
        org.destiny[d] = 0.85f * org.destiny[d] + 0.15f * exhale[frag].destiny[d];
    vec_normalize(org.destiny, DESTINY_DIM);
}

/* ─── MARK WORD USED ────────────────────────────────────────────────── */

static void mark_used(int idx) {
    if (org.used_count < MAX_VOCAB)
        org.used[org.used_count++] = idx;
}

static int is_used(int idx) {
    for (int i = 0; i < org.used_count; i++)
        if (org.used[i] == idx) return 1;
    return 0;
}

/* ─── SEMANTIC TENSION — word pairs that create artistic voltage ────── */
/*
 * "skull" + "cathedral" = the cathedral is a skull of god
 * "empire" + "vertebra" = the spine of the state
 * "exile" + "lagoon" = Venice, the city of exiles
 * These pairs boost each other when adjacent. Not bigrams —
 * tension. The reader fills the gap between them.
 */

/*
 * Tension lifecycle:
 *   birth (tension=0.8) → crystal (use 3-5, fused SuperToken)
 *   → cliché (use 10+, tension decays) → death (tension < 0.05)
 * "Каждая метафора — одноразовый шприц." (c) nobody, but true.
 */

typedef struct {
    const char *a, *b;
    float tension;       /* current strength — decays with use */
    int   use_count;     /* how many times used in generation */
    int   crystallized;  /* 1 = SuperToken formed */
    int   lang;          /* LANG_EN..LANG_ES — which language's poetic tradition */
} TensionPair;

static TensionPair tensions[] = {

    /* ═══════════════════════════════════════════════════════════════════
     *  ENGLISH (~55 pairs)
     *  Brodsky's anglophone register: body×architecture, exile×water,
     *  time×material, geometry×void, language×destruction, domestic×cosmic
     * ═══════════════════════════════════════════════════════════════════ */

    /* EN: architecture × body */
    {"skull",          "cathedral",     0.8f, 0, 0, LANG_EN},
    {"vertebra",       "empire",        0.7f, 0, 0, LANG_EN},
    {"spine",          "colonnade",     0.7f, 0, 0, LANG_EN},
    {"ribcage",        "cathedral",     0.6f, 0, 0, LANG_EN},
    {"larynx",         "corridor",      0.6f, 0, 0, LANG_EN},
    {"diaphragm",      "amphitheater",  0.6f, 0, 0, LANG_EN},
    {"sternum",        "facade",        0.5f, 0, 0, LANG_EN},
    {"collarbone",     "balustrade",    0.6f, 0, 0, LANG_EN},
    {"synapse",        "cathedral",     0.7f, 0, 0, LANG_EN},  /* neural architecture */
    {"cochlea",        "empire",        0.7f, 0, 0, LANG_EN},  /* the inner ear of the state */
    {"scapula",        "buttress",      0.6f, 0, 0, LANG_EN},
    {"pelvis",         "rotunda",       0.5f, 0, 0, LANG_EN},
    {"femur",          "obelisk",       0.6f, 0, 0, LANG_EN},
    /* EN: exile × water (Venice) */
    {"exile",          "lagoon",        0.8f, 0, 0, LANG_EN},
    {"exile",          "canal",         0.7f, 0, 0, LANG_EN},
    {"departure",      "gondola",       0.7f, 0, 0, LANG_EN},
    {"passport",       "watermark",     0.8f, 0, 0, LANG_EN},
    {"border",         "tide",          0.6f, 0, 0, LANG_EN},
    {"displacement",   "current",       0.6f, 0, 0, LANG_EN},
    {"banishment",     "undertow",      0.7f, 0, 0, LANG_EN},
    {"statelessness",  "bilge",         0.6f, 0, 0, LANG_EN},
    /* EN: time × material */
    {"epoch",          "dust",          0.7f, 0, 0, LANG_EN},
    {"antiquity",      "rust",          0.7f, 0, 0, LANG_EN},
    {"millennium",     "ash",           0.6f, 0, 0, LANG_EN},
    {"eternity",       "salt",          0.7f, 0, 0, LANG_EN},
    {"hourglass",      "bone",          0.6f, 0, 0, LANG_EN},
    {"calendar",       "erosion",       0.5f, 0, 0, LANG_EN},
    {"pendulum",       "basalt",        0.6f, 0, 0, LANG_EN},
    {"senescence",     "limestone",     0.5f, 0, 0, LANG_EN},
    /* EN: geometry × void */
    {"perpendicular",  "nowhere",       0.7f, 0, 0, LANG_EN},
    {"asymptote",      "never",         0.8f, 0, 0, LANG_EN},
    {"parallel",       "exile",         0.7f, 0, 0, LANG_EN},
    {"intersection",   "death",         0.6f, 0, 0, LANG_EN},
    {"circumference",  "nothing",       0.6f, 0, 0, LANG_EN},
    {"tangent",        "departure",     0.6f, 0, 0, LANG_EN},
    {"parabola",       "melancholy",    0.6f, 0, 0, LANG_EN},
    {"hyperbola",      "nostalgia",     0.5f, 0, 0, LANG_EN},
    /* EN: language × destruction */
    {"consonant",      "annihilation",  0.7f, 0, 0, LANG_EN},
    {"syllable",       "hemorrhage",    0.6f, 0, 0, LANG_EN},
    {"manuscript",     "ash",           0.8f, 0, 0, LANG_EN},
    {"typewriter",     "skull",         0.7f, 0, 0, LANG_EN},
    {"translation",    "exile",         0.8f, 0, 0, LANG_EN},
    {"stanza",         "sarcophagus",   0.6f, 0, 0, LANG_EN},
    {"elegy",          "granite",       0.6f, 0, 0, LANG_EN},
    {"caesura",        "death",         0.7f, 0, 0, LANG_EN},
    /* EN: domestic × cosmic */
    {"windowsill",     "constellation", 0.8f, 0, 0, LANG_EN},
    {"radiator",       "eternity",      0.7f, 0, 0, LANG_EN},
    {"wallpaper",      "infinity",      0.7f, 0, 0, LANG_EN},
    {"ceiling",        "hemisphere",    0.6f, 0, 0, LANG_EN},
    {"mattress",       "tundra",        0.6f, 0, 0, LANG_EN},
    {"corridor",       "meridian",      0.7f, 0, 0, LANG_EN},
    {"faucet",         "eternity",      0.7f, 0, 0, LANG_EN},  /* domestic infinite */
    {"linoleum",       "constellation", 0.7f, 0, 0, LANG_EN},  /* floor as sky */
    {"ashtray",        "equinox",       0.6f, 0, 0, LANG_EN},
    {"curtain",        "horizon",       0.6f, 0, 0, LANG_EN},
    /* EN: nature × empire */
    {"permafrost",     "bureaucracy",   0.7f, 0, 0, LANG_EN},
    {"glacier",        "surveillance",  0.6f, 0, 0, LANG_EN},
    {"fog",            "empire",        0.6f, 0, 0, LANG_EN},
    {"birch",          "exile",         0.7f, 0, 0, LANG_EN},
    {"moss",           "marble",        0.6f, 0, 0, LANG_EN},
    /* EN: body × geography */
    {"aorta",          "meridian",      0.7f, 0, 0, LANG_EN},  /* body as geography */

    /* ═══════════════════════════════════════════════════════════════════
     *  RUSSIAN (~50 pairs)
     *  Бродский на родном: тело×империя, быт×космос, время×материя,
     *  изгнание×вода, геометрия×небытие, язык×разрушение
     * ═══════════════════════════════════════════════════════════════════ */

    /* RU: тело × архитектура/империя */
    {"позвоночник",    "империя",       0.8f, 0, 0, LANG_RU},  /* spine of empire */
    {"череп",          "собор",         0.8f, 0, 0, LANG_RU},
    {"гортань",        "колоннада",     0.7f, 0, 0, LANG_RU},  /* larynx × colonnade */
    {"сухожилие",      "акведук",       0.7f, 0, 0, LANG_RU},  /* tendon × aqueduct */
    {"диафрагма",      "амфитеатр",     0.6f, 0, 0, LANG_RU},
    {"грудина",        "фасад",         0.5f, 0, 0, LANG_RU},
    {"ключица",        "балюстрада",    0.6f, 0, 0, LANG_RU},
    {"аорта",          "меридиан",      0.7f, 0, 0, LANG_RU},
    {"лопатка",        "парапет",       0.5f, 0, 0, LANG_RU},
    {"скелет",         "арка",          0.6f, 0, 0, LANG_RU},
    {"хрящ",           "гранит",        0.6f, 0, 0, LANG_RU},
    /* RU: быт × космос */
    {"подоконник",     "бесконечность", 0.8f, 0, 0, LANG_RU},
    {"форточка",       "вечность",      0.8f, 0, 0, LANG_RU},  /* ventilation window × eternity */
    {"батарея",        "тысячелетие",   0.7f, 0, 0, LANG_RU},  /* radiator × millennium */
    {"половица",       "горизонт",      0.7f, 0, 0, LANG_RU},  /* floorboard × horizon */
    {"пепельница",     "равноденствие", 0.7f, 0, 0, LANG_RU},  /* ashtray × equinox */
    {"коридор",        "меридиан",      0.7f, 0, 0, LANG_RU},
    {"потолок",        "пространство",  0.6f, 0, 0, LANG_RU},
    {"зеркало",        "бесконечность", 0.7f, 0, 0, LANG_RU},
    {"штора",          "горизонт",      0.6f, 0, 0, LANG_RU},
    {"абажур",         "солнцестояние", 0.6f, 0, 0, LANG_RU},
    /* RU: изгнание × вода */
    {"изгнание",       "лагуна",        0.8f, 0, 0, LANG_RU},
    {"изгнание",       "канал",         0.7f, 0, 0, LANG_RU},
    {"разлука",        "гондола",       0.7f, 0, 0, LANG_RU},
    {"чужбина",        "течение",       0.7f, 0, 0, LANG_RU},
    {"граница",        "прилив",        0.6f, 0, 0, LANG_RU},
    /* RU: время × материя */
    {"эпоха",          "пыль",          0.7f, 0, 0, LANG_RU},
    {"античность",     "ржавчина",      0.7f, 0, 0, LANG_RU},
    {"тысячелетие",    "пепел",         0.6f, 0, 0, LANG_RU},
    {"вечность",       "соль",          0.7f, 0, 0, LANG_RU},
    {"маятник",        "кость",         0.6f, 0, 0, LANG_RU},
    {"столетие",       "воск",          0.5f, 0, 0, LANG_RU},
    /* RU: геометрия × небытие */
    {"перпендикуляр",  "нигде",         0.7f, 0, 0, LANG_RU},
    {"асимптота",      "никогда",       0.8f, 0, 0, LANG_RU},
    {"параллель",      "изгнание",      0.7f, 0, 0, LANG_RU},
    {"парабола",       "меланхолия",    0.6f, 0, 0, LANG_RU},
    {"диагональ",      "смерть",        0.6f, 0, 0, LANG_RU},
    /* RU: язык × разрушение */
    {"чернила",        "распад",        0.7f, 0, 0, LANG_RU},  /* ink × decay */
    {"рукопись",       "пепел",         0.8f, 0, 0, LANG_RU},  /* manuscript × ash */
    {"согласная",      "уничтожение",   0.7f, 0, 0, LANG_RU},
    {"слог",           "кровоизлияние", 0.6f, 0, 0, LANG_RU},
    {"перевод",        "изгнание",      0.8f, 0, 0, LANG_RU},
    {"рифма",          "эпитафия",      0.6f, 0, 0, LANG_RU},
    {"строфа",         "мрамор",        0.5f, 0, 0, LANG_RU},
    {"метафора",       "кость",         0.6f, 0, 0, LANG_RU},
    /* RU: природа × империя */
    {"тундра",         "бюрократия",    0.7f, 0, 0, LANG_RU},
    {"ледник",         "цензура",       0.6f, 0, 0, LANG_RU},
    {"туман",          "империя",       0.6f, 0, 0, LANG_RU},
    {"берёза",         "изгнание",      0.7f, 0, 0, LANG_RU},
    {"мох",            "мрамор",        0.6f, 0, 0, LANG_RU},

    /* ═══════════════════════════════════════════════════════════════════
     *  HEBREW (~45 pairs)
     *  Biblical weight meets architectural void. Shoresh as bone.
     *  Exile is not metaphor in Hebrew — it is history.
     * ═══════════════════════════════════════════════════════════════════ */

    /* HE: גוף × אדריכלות (body × architecture) */
    {"גולגולת",        "היכל",          0.8f, 0, 0, LANG_HE},  /* skull × temple */
    {"עמוד שדרה",      "עמוד",          0.8f, 0, 0, LANG_HE},  /* spine × column — same root */
    {"סרעפת",          "מבצר",          0.7f, 0, 0, LANG_HE},  /* diaphragm × fortress */
    {"גרון",           "פרוזדור",       0.6f, 0, 0, LANG_HE},  /* throat × corridor */
    {"צלע",            "קשת",           0.6f, 0, 0, LANG_HE},  /* rib × arch */
    {"עצם הבריח",      "מעקה",          0.6f, 0, 0, LANG_HE},  /* collarbone × railing */
    {"עורק",           "תעלה",          0.7f, 0, 0, LANG_HE},  /* artery × canal */
    {"סחוס",           "גרניט",         0.6f, 0, 0, LANG_HE},  /* cartilage × granite */
    {"שלד",            "חורבה",         0.7f, 0, 0, LANG_HE},  /* skeleton × ruin */
    {"בשר",            "שיש",           0.6f, 0, 0, LANG_HE},  /* flesh × marble */
    /* HE: חורבן × בניין (destruction × construction) */
    {"חורבן",          "עמוד",          0.8f, 0, 0, LANG_HE},  /* destruction × column */
    {"תהום",           "שיש",           0.8f, 0, 0, LANG_HE},  /* abyss × marble */
    {"שממה",           "כיפה",          0.7f, 0, 0, LANG_HE},  /* desolation × dome */
    {"השמדה",          "אדריכלות",      0.7f, 0, 0, LANG_HE},
    {"התפוררות",       "מזבח",          0.6f, 0, 0, LANG_HE},  /* crumbling × altar */
    {"חורבן",          "מקדש",          0.9f, 0, 0, LANG_HE},  /* destruction × sanctuary */
    /* HE: גלות × מים (exile × water) */
    {"גלות",           "לגונה",         0.8f, 0, 0, LANG_HE},
    {"גלות",           "תעלה",          0.7f, 0, 0, LANG_HE},
    {"גלות",           "אמת מים",       0.7f, 0, 0, LANG_HE},  /* exile × aqueduct */
    {"גירוש",          "גונדולה",       0.7f, 0, 0, LANG_HE},  /* expulsion × gondola */
    {"פרידה",          "זרם",           0.6f, 0, 0, LANG_HE},  /* parting × current */
    {"גבול",           "גאות",          0.6f, 0, 0, LANG_HE},  /* border × tide */
    {"נדידה",          "מערבולת",       0.6f, 0, 0, LANG_HE},  /* migration × whirlpool */
    /* HE: זמן × חומר (time × material) */
    {"נצח",            "מלח",           0.7f, 0, 0, LANG_HE},  /* eternity × salt */
    {"אלף שנה",        "אפר",           0.6f, 0, 0, LANG_HE},  /* millennium × ash */
    {"עתיקות",         "חלודה",         0.7f, 0, 0, LANG_HE},  /* antiquity × rust */
    {"שעון",           "עצם",           0.6f, 0, 0, LANG_HE},  /* clock × bone */
    {"קדמות",          "אבק",           0.6f, 0, 0, LANG_HE},  /* ancient times × dust */
    {"עידן",           "סלע",           0.5f, 0, 0, LANG_HE},  /* era × rock */
    /* HE: שפה × חורבן (language × destruction) */
    {"דם",             "אלפבית",        0.8f, 0, 0, LANG_HE},  /* blood × alphabet */
    {"כתב יד",         "אפר",           0.8f, 0, 0, LANG_HE},  /* manuscript × ash */
    {"עיצור",          "השמדה",         0.7f, 0, 0, LANG_HE},  /* consonant × annihilation */
    {"הברה",           "כיליון",        0.6f, 0, 0, LANG_HE},  /* syllable × destruction */
    {"תרגום",          "גלות",          0.8f, 0, 0, LANG_HE},  /* translation × exile */
    {"שורש",           "חורבן",         0.7f, 0, 0, LANG_HE},  /* root × destruction */
    {"דיו",            "דם",            0.7f, 0, 0, LANG_HE},  /* ink × blood */
    {"פסוק",           "גרדום",         0.6f, 0, 0, LANG_HE},  /* verse × gallows */
    /* HE: ביתי × קוסמי (domestic × cosmic) */
    {"אדן חלון",       "קונסטלציה",     0.8f, 0, 0, LANG_HE},  /* windowsill × constellation */
    {"רדיאטור",        "נצח",           0.7f, 0, 0, LANG_HE},  /* radiator × eternity */
    {"תקרה",           "אינסוף",        0.6f, 0, 0, LANG_HE},  /* ceiling × infinity */
    {"קרש רצפה",       "אופק",          0.7f, 0, 0, LANG_HE},  /* floorboard × horizon */
    {"מסדרון",         "מדבר",          0.6f, 0, 0, LANG_HE},  /* corridor × desert */
    {"מראה",           "תהום",          0.7f, 0, 0, LANG_HE},  /* mirror × abyss */
    {"וילון",          "אינסוף",        0.6f, 0, 0, LANG_HE},  /* curtain × infinity */

    /* ═══════════════════════════════════════════════════════════════════
     *  FRENCH (~45 pairs)
     *  Baudelaire + Rimbaud + Brodsky's Venice in French register.
     *  Spleen, gouffre, néant. Body as architecture of decay.
     * ═══════════════════════════════════════════════════════════════════ */

    /* FR: corps × architecture */
    {"crâne",          "cathédrale",    0.8f, 0, 0, LANG_FR},  /* skull × cathedral */
    {"vertèbre",       "empire",        0.7f, 0, 0, LANG_FR},  /* vertebra × empire */
    {"larynx",         "colonnade",     0.7f, 0, 0, LANG_FR},
    {"diaphragme",     "voûte",         0.6f, 0, 0, LANG_FR},  /* diaphragm × vault */
    {"sternum",        "façade",        0.5f, 0, 0, LANG_FR},
    {"omoplate",       "balustrade",    0.6f, 0, 0, LANG_FR},  /* shoulder blade × balustrade */
    {"aorte",          "méridien",      0.7f, 0, 0, LANG_FR},  /* aorta × meridian */
    {"synapse",        "cathédrale",    0.7f, 0, 0, LANG_FR},  /* neural × sacred */
    {"squelette",      "forteresse",    0.6f, 0, 0, LANG_FR},  /* skeleton × fortress */
    {"os",             "marbre",        0.6f, 0, 0, LANG_FR},  /* bone × marble */
    {"cartilage",      "granit",        0.6f, 0, 0, LANG_FR},
    {"tendon",         "aqueduc",       0.6f, 0, 0, LANG_FR},  /* tendon × aqueduct */
    /* FR: exil × eau */
    {"exil",           "lagune",        0.8f, 0, 0, LANG_FR},
    {"exil",           "canal",         0.7f, 0, 0, LANG_FR},
    {"bannissement",   "gondole",       0.7f, 0, 0, LANG_FR},
    {"séparation",     "courant",       0.6f, 0, 0, LANG_FR},
    {"frontière",      "marée",         0.6f, 0, 0, LANG_FR},
    {"déracinement",   "maelström",     0.7f, 0, 0, LANG_FR},  /* uprooting × maelstrom */
    /* FR: temps × matière */
    {"époque",         "poussière",     0.7f, 0, 0, LANG_FR},  /* epoch × dust */
    {"antiquité",      "rouille",       0.7f, 0, 0, LANG_FR},  /* antiquity × rust */
    {"millénaire",     "cendre",        0.6f, 0, 0, LANG_FR},  /* millennium × ash */
    {"éternité",       "sel",           0.7f, 0, 0, LANG_FR},  /* eternity × salt */
    {"siècle",         "os",            0.6f, 0, 0, LANG_FR},  /* century × bone */
    {"pendule",        "basalte",       0.5f, 0, 0, LANG_FR},
    /* FR: néant × géométrie */
    {"perpendiculaire","néant",         0.7f, 0, 0, LANG_FR},
    {"asymptote",      "jamais",        0.8f, 0, 0, LANG_FR},  /* asymptote × never */
    {"parallèle",      "exil",          0.7f, 0, 0, LANG_FR},
    {"tangente",       "départ",        0.6f, 0, 0, LANG_FR},
    {"parabole",       "mélancolie",    0.6f, 0, 0, LANG_FR},
    /* FR: langue × destruction */
    {"consonne",       "anéantissement",0.7f, 0, 0, LANG_FR},
    {"syllabe",        "hémorragie",    0.6f, 0, 0, LANG_FR},
    {"manuscrit",      "cendre",        0.8f, 0, 0, LANG_FR},
    {"encre",          "sang",          0.7f, 0, 0, LANG_FR},  /* ink × blood */
    {"strophe",        "sarcophage",    0.6f, 0, 0, LANG_FR},
    {"rime",           "tombeau",       0.6f, 0, 0, LANG_FR},  /* rhyme × tomb */
    {"césure",         "mort",          0.7f, 0, 0, LANG_FR},  /* caesura × death */
    /* FR: domestique × cosmique */
    {"robinet",        "éternité",      0.7f, 0, 0, LANG_FR},  /* faucet × eternity */
    {"rideau",         "infini",        0.7f, 0, 0, LANG_FR},  /* curtain × infinity */
    {"cendrier",       "équinoxe",      0.6f, 0, 0, LANG_FR},  /* ashtray × equinox */
    {"plafond",        "abîme",         0.6f, 0, 0, LANG_FR},  /* ceiling × abyss */
    {"radiateur",      "éternité",      0.7f, 0, 0, LANG_FR},
    {"plancher",       "horizon",       0.7f, 0, 0, LANG_FR},  /* floor × horizon */
    {"linoléum",       "solstice",      0.7f, 0, 0, LANG_FR},  /* linoleum × solstice */
    {"escalier",       "gouffre",       0.7f, 0, 0, LANG_FR},  /* staircase × chasm */
    {"miroir",         "abîme",         0.7f, 0, 0, LANG_FR},  /* mirror × abyss */
    /* FR: Baudelaire — spleen × matière */
    {"spleen",         "granit",        0.7f, 0, 0, LANG_FR},
    {"charogne",       "cathédrale",    0.7f, 0, 0, LANG_FR},  /* carrion × cathedral */
    {"gouffre",        "cloître",       0.7f, 0, 0, LANG_FR},  /* chasm × cloister */

    /* ═══════════════════════════════════════════════════════════════════
     *  SPANISH (~45 pairs)
     *  Borges + Lorca + imperial lexicon. Laberinto, duende, sangre.
     *  The labyrinth is a body. The library is a cathedral.
     * ═══════════════════════════════════════════════════════════════════ */

    /* ES: cuerpo × arquitectura */
    {"cráneo",         "catedral",      0.8f, 0, 0, LANG_ES},  /* skull × cathedral */
    {"vértebra",       "imperio",       0.7f, 0, 0, LANG_ES},  /* vertebra × empire */
    {"laringe",        "columnata",     0.7f, 0, 0, LANG_ES},
    {"diafragma",      "bóveda",        0.6f, 0, 0, LANG_ES},  /* diaphragm × vault */
    {"esternón",       "fachada",       0.5f, 0, 0, LANG_ES},
    {"omóplato",       "claustro",      0.6f, 0, 0, LANG_ES},  /* shoulder blade × cloister */
    {"aorta",          "meridiano",     0.7f, 0, 0, LANG_ES},  /* aorta × meridian */
    {"esqueleto",      "fortaleza",     0.6f, 0, 0, LANG_ES},
    {"sangre",         "mármol",        0.7f, 0, 0, LANG_ES},  /* blood × marble */
    {"hueso",          "columna",       0.6f, 0, 0, LANG_ES},  /* bone × column */
    /* ES: exilio × agua */
    {"exilio",         "laguna",        0.8f, 0, 0, LANG_ES},
    {"exilio",         "canal",         0.7f, 0, 0, LANG_ES},
    {"destierro",      "góndola",       0.7f, 0, 0, LANG_ES},
    {"frontera",       "marea",         0.6f, 0, 0, LANG_ES},
    {"separación",     "corriente",     0.6f, 0, 0, LANG_ES},
    {"desarraigo",     "naufragio",     0.7f, 0, 0, LANG_ES},  /* uprooting × shipwreck */
    /* ES: tiempo × materia */
    {"eternidad",      "sal",           0.7f, 0, 0, LANG_ES},
    {"milenio",        "ceniza",        0.6f, 0, 0, LANG_ES},  /* millennium × ash */
    {"antigüedad",     "óxido",         0.7f, 0, 0, LANG_ES},  /* antiquity × rust */
    {"tiempo",         "polvo",         0.7f, 0, 0, LANG_ES},  /* time × dust */
    {"época",          "hueso",         0.6f, 0, 0, LANG_ES},
    /* ES: geometría × vacío */
    {"perpendicular",  "nada",          0.7f, 0, 0, LANG_ES},
    {"asíntota",       "nunca",         0.8f, 0, 0, LANG_ES},  /* asymptote × never */
    {"paralela",       "exilio",        0.7f, 0, 0, LANG_ES},
    {"tangente",       "partida",       0.6f, 0, 0, LANG_ES},
    {"parábola",       "melancolía",    0.6f, 0, 0, LANG_ES},
    /* ES: lengua × destrucción */
    {"consonante",     "aniquilación",  0.7f, 0, 0, LANG_ES},
    {"sílaba",         "hemorragia",    0.6f, 0, 0, LANG_ES},
    {"manuscrito",     "ceniza",        0.8f, 0, 0, LANG_ES},
    {"tinta",          "sangre",        0.7f, 0, 0, LANG_ES},  /* ink × blood */
    {"traducción",     "exilio",        0.8f, 0, 0, LANG_ES},
    {"estrofa",        "sepulcro",      0.6f, 0, 0, LANG_ES},  /* stanza × sepulcher */
    {"epitafio",       "mármol",        0.6f, 0, 0, LANG_ES},
    /* ES: doméstico × cósmico */
    {"espejo",         "eternidad",     0.8f, 0, 0, LANG_ES},  /* mirror × eternity */
    {"cenicero",       "equinoccio",    0.6f, 0, 0, LANG_ES},  /* ashtray × equinox */
    {"cortina",        "infinito",      0.7f, 0, 0, LANG_ES},  /* curtain × infinity */
    {"umbral",         "abismo",        0.7f, 0, 0, LANG_ES},  /* threshold × abyss */
    {"alféizar",       "horizonte",     0.7f, 0, 0, LANG_ES},  /* windowsill × horizon */
    {"radiador",       "eternidad",     0.7f, 0, 0, LANG_ES},
    /* ES: Borges — laberinto × everything */
    {"laberinto",      "ceniza",        0.7f, 0, 0, LANG_ES},  /* labyrinth × ash */
    {"puñal",          "biblioteca",    0.8f, 0, 0, LANG_ES},  /* dagger × library — Borges! */
    {"aleph",          "abismo",        0.8f, 0, 0, LANG_ES},
    {"destino",        "laberinto",     0.7f, 0, 0, LANG_ES},
    {"espejo",         "laberinto",     0.7f, 0, 0, LANG_ES},  /* mirror × labyrinth */
    /* ES: Lorca — duende × sangre */
    {"duende",         "sangre",        0.8f, 0, 0, LANG_ES},
    {"duende",         "cal",           0.7f, 0, 0, LANG_ES},  /* duende × lime */

    /* sentinel */
    {NULL, NULL, 0, 0, 0, 0}
};

static float tension_score(int last_idx, int cand_idx) {
    if (last_idx < 0) return 0.0f;
    const char *last = vocab[last_idx].text;
    const char *cand = vocab[cand_idx].text;
    for (int i = 0; tensions[i].a; i++) {
        /* tension works cross-culturally: any pair can fire regardless of
         * current language. The pair's lang field records its origin tradition,
         * but a Russian word can create tension with a Hebrew word if the
         * organism happens to be in multilingual mode. */
        if ((strcmp(last, tensions[i].a) == 0 && strcmp(cand, tensions[i].b) == 0) ||
            (strcmp(last, tensions[i].b) == 0 && strcmp(cand, tensions[i].a) == 0)) {
            /* lifecycle: use_count affects effective tension */
            float eff = tensions[i].tension;
            int u = tensions[i].use_count;
            if (u >= 10) {
                /* cliché — dying. decay exponentially */
                eff *= expf(-(float)(u - 10) * 0.3f);
            } else if (u >= 3 && !tensions[i].crystallized) {
                /* crystallize: SuperToken bonus */
                tensions[i].crystallized = 1;
                eff *= 1.3f; /* crystal is stronger than birth */
            }
            return eff;
        }
    }
    return 0.0f;
}

/* call after a tension pair is used in generation */
static void tension_used(int a_idx, int b_idx) {
    const char *wa = vocab[a_idx].text;
    const char *wb = vocab[b_idx].text;
    for (int i = 0; tensions[i].a; i++) {
        if ((strcmp(wa, tensions[i].a) == 0 && strcmp(wb, tensions[i].b) == 0) ||
            (strcmp(wa, tensions[i].b) == 0 && strcmp(wb, tensions[i].a) == 0)) {
            tensions[i].use_count++;
            return;
        }
    }
}

/* ─── DOE-LITE PARLIAMENT FUNCTIONS ────────────────────────────────── */
/*
 * A compact democracy of LoRA-style experts that vote on word selection.
 * From Q's DOE Parliament, but drunk and smaller.
 * 4 experts, each with a personality:
 *   Architect  — VOID, architecture, empire. Prefers mass > 0.6
 *   Anatomist  — TRAUMA, body words. Prefers consonant_density > 0.5
 *   Exile      — JULIA, exile/water/Venice. Boosted by julia field
 *   Metronome  — RESONANCE, geometry/time. Prefers high syllable count
 */

static const char *expert_names[DOE_EXPERTS * 2] = {
    "architect", "anatomist", "exile", "metronome",
    "child-0", "child-1", "child-2", "child-3"
};

static void parliament_init(Parliament *p) {
    memset(p, 0, sizeof(*p));
    p->n = DOE_EXPERTS;
    p->elections = 0;

    /* Architect: VOID-loving, high mass */
    memset(&p->e[0], 0, sizeof(Expert));
    p->e[0].bias[EMO_VOID] = 0.5f;
    p->e[0].mass_pref = 0.7f;
    p->e[0].vitality = 1.0f;
    p->e[0].alive = 1;

    /* Anatomist: TRAUMA-loving, consonant-dense */
    memset(&p->e[1], 0, sizeof(Expert));
    p->e[1].bias[EMO_TRAUMA] = 0.5f;
    p->e[1].bias[EMO_RAGE] = 0.3f;
    p->e[1].mass_pref = 0.6f;
    p->e[1].vitality = 1.0f;
    p->e[1].alive = 1;

    /* Exile: JULIA-loving, boosted by julia field */
    memset(&p->e[2], 0, sizeof(Expert));
    p->e[2].bias[EMO_JULIA] = 0.5f;
    p->e[2].mass_pref = 0.5f;
    p->e[2].vitality = 1.0f;
    p->e[2].alive = 1;

    /* Metronome: RESONANCE-loving, high syllables */
    memset(&p->e[3], 0, sizeof(Expert));
    p->e[3].bias[EMO_RESONANCE] = 0.5f;
    p->e[3].mass_pref = 0.5f;
    p->e[3].vitality = 1.0f;
    p->e[3].alive = 1;
}

static float expert_vote(Expert *ex, int expert_idx, Word *w, float julia) {
    if (!ex->alive) return 0.0f;
    float vote = ex->bias[w->emotion] * ex->vitality;
    /* mass preference: closer to preferred = higher vote */
    vote += (1.0f - fabsf(w->mass - ex->mass_pref)) * 0.3f * ex->vitality;
    /* Exile expert (index 2) boosted by julia */
    if (expert_idx == 2)
        vote *= (1.0f + julia * 1.5f);
    return vote;
}

static float parliament_score(int idx) {
    Word *w = &vocab[idx];
    float total = 0.0f;
    int n_alive = 0;

    for (int i = 0; i < org.parliament.n; i++) {
        if (!org.parliament.e[i].alive) continue;
        float v = expert_vote(&org.parliament.e[i], i, w, org.julia);
        total += v;
        n_alive++;
    }

    if (n_alive == 0) return 0.0f;
    return total / (float)n_alive;  /* average vote */
}

static void parliament_update(int winner_word) {
    /* find which expert voted strongest for this word */
    float best = -1.0f;
    int best_i = -1;
    for (int i = 0; i < org.parliament.n; i++) {
        if (!org.parliament.e[i].alive) continue;
        float v = expert_vote(&org.parliament.e[i], i, &vocab[winner_word], org.julia);
        if (v > best) { best = v; best_i = i; }
    }
    if (best_i >= 0) {
        org.parliament.e[best_i].wins++;
        org.parliament.e[best_i].overload += 0.1f;
        /* vitality boost for winner */
        org.parliament.e[best_i].vitality = clampf(
            org.parliament.e[best_i].vitality + 0.02f, 0.1f, 2.0f);
    }
    /* losers decay slightly */
    for (int i = 0; i < org.parliament.n; i++) {
        if (i == best_i || !org.parliament.e[i].alive) continue;
        org.parliament.e[i].vitality *= 0.99f;
    }
    org.parliament.elections++;
}

static void parliament_lifecycle(Parliament *p) {
    for (int i = 0; i < p->n; i++) {
        if (!p->e[i].alive) continue;
        /* Mitosis: overloaded expert splits */
        if (p->e[i].overload > 3.0f && p->n < DOE_EXPERTS * 2) {
            int child = p->n++;
            p->e[child] = p->e[i];
            p->e[child].vitality *= 0.6f;
            p->e[child].overload = 0.0f;
            p->e[child].wins = 0;
            p->e[i].vitality *= 0.6f;
            p->e[i].overload = 0.0f;
            /* mutate child slightly */
            for (int e = 0; e < EMO_COUNT; e++)
                p->e[child].bias[e] += (rng_float() - 0.5f) * 0.1f;
        }
        /* Apoptosis: vitality too low */
        if (p->e[i].vitality < 0.15f && p->n > 2) {
            p->e[i].alive = 0;
        }
    }
}

static int parliament_alive_count(const Parliament *p) {
    int n = 0;
    for (int i = 0; i < p->n; i++)
        if (p->e[i].alive) n++;
    return n;
}

/* ─── SCORE A CANDIDATE WORD ────────────────────────────────────────── */
/*
 * Not a sum of boosts. One breath. Multiplicative.
 *
 * Layer 1 — CORPUS (the body): what the poet has read.
 *   bigrams + hebbian + tension pairs. This is the statistical
 *   skeleton. Without corpus, score = mass alone.
 *
 * Layer 2 — DARIO OVERLAY (the soul): how the poet feels NOW.
 *   chambers × destiny × velocity × julia × planetary.
 *   This MODULATES the corpus layer, not replaces it.
 *
 * Final: body × soul × mass.
 * If body is zero (no corpus connection), soul can't save it.
 * If soul is zero (dead chambers), body speaks alone — flat.
 * When both are alive — resonance.
 *
 * p(x|Φ) = mass × (1 + corpus_pull) × (1 + dario_mod) / τ
 */

static float score_word(int idx) {
    Word *w = &vocab[idx];

    /* ── LAYER 1: CORPUS BODY ─────────────────────────────── */

    float corpus_pull = 0.0f;

    /* word-level bigram from exhale corpus */
    corpus_pull += corpus_bigram_score(org.last_word, idx) * 1.5f;

    /* word-level Hebbian co-occurrence from corpus */
    corpus_pull += corpus_hebbian_score(org.last_word, idx) * 1.0f;

    /* emotion bigram: what emotion follows what */
    corpus_pull += bigram[org.last_emotion][w->emotion] * 0.5f;

    /* old-school Hebbian (from haiku.c lineage) */
    if (org.last_word >= 0)
        corpus_pull += hebbian_score(org.last_word, idx) * 0.5f;

    /* semantic tension: impossible pairs (skull×cathedral) */
    float tens = tension_score(org.last_word, idx);
    corpus_pull += tens * 3.0f;  /* tension is the strongest corpus signal */

    /* clamp: corpus_pull is always >= 0 */
    if (corpus_pull < 0.0f) corpus_pull = 0.0f;

    /* ── LAYER 2: DARIO OVERLAY (soul) ────────────────────── */

    float dario = 0.0f;

    /* A: Destiny — where the poem is going */
    float dist = vec_dist(w->destiny, org.destiny, DESTINY_DIM);
    float julia_stretch = 1.0f + org.julia * JULIA_STRETCH;
    float attraction = 1.0f / (1.0f + dist * julia_stretch);
    dario += attraction * 0.6f;

    /* Chamber resonance: does this word's emotion match the active chamber? */
    static const int emo_to_ch[EMO_COUNT] = {
        CH_FEAR, CH_FLOW, CH_VOID, CH_FLOW, CH_LOVE,
        CH_VOID, CH_RAGE, CH_LOVE, CH_LOVE
    };
    int target_ch = emo_to_ch[w->emotion];
    float ch_act = chamber_activation(&org.chambers, target_ch);
    dario += (ch_act > 0 ? ch_act : 0) * 0.4f;

    /* T: Trauma gravity — planetary dissonance pulls trauma words */
    if (w->emotion == EMO_TRAUMA)
        dario += org.planet_diss * 0.3f;

    /* Calendar dissonance → GRIEF and VOID */
    if (w->emotion == EMO_GRIEF || w->emotion == EMO_VOID)
        dario += org.cal_diss * 0.2f;

    /* Julia → JULIA-tagged words feel the longing */
    if (w->emotion == EMO_JULIA)
        dario += org.julia * 0.5f;

    /* F: Prophecy — unfulfilled predictions create pressure */
    float prophecy_pull = 0.0f;
    for (int p = 0; p < org.prophecy.n; p++) {
        if (!org.prophecy.p[p].fulfilled && org.prophecy.p[p].target == idx) {
            prophecy_pull += org.prophecy.p[p].strength * logf(1.0f + (float)org.prophecy.p[p].age);
        }
    }
    dario += prophecy_pull * 0.4f;
    /* keep seasonal bias too, but weaker */
    dario += season_bias[org.season][w->emotion] * 0.1f;

    /* Parliament: experts vote on this word */
    float parliament = parliament_score(idx);
    dario += parliament * 0.5f;

    /* clamp: dario is always >= 0 */
    if (dario < 0.0f) dario = 0.0f;

    /* ── FINAL: body × soul × mass ────────────────────────── */
    /*
     * mass is the word's intrinsic weight (0.10 - 0.95)
     * (1 + corpus_pull): corpus connection (1.0 = no connection, higher = pulled)
     * (1 + dario): soul modulation (1.0 = neutral, higher = resonant)
     *
     * A word with no corpus pull and no dario resonance scores just its mass.
     * A word pulled by corpus AND resonant with chambers scores mass × both.
     */
    return w->mass * (1.0f + corpus_pull) * (1.0f + dario);
}

/* ─── SAMPLE A WORD ─────────────────────────────────────────────────── */

/*
 * Given syllable budget, select a word.
 * Applies: mass weighting, consonant density, syllable greed,
 *          adjective penalty, repetition penalty, velocity mod.
 */
/*
 * target_lang: primary language for this line
 * ghost_lang:  if >= 0, allow ONE word from this language (ghost voice)
 * ghost_used:  pointer to flag, set to 1 once ghost word is emitted
 */
static int sample_word(int syl_remaining, int force_max_syl,
                       int target_lang, int ghost_lang, int *ghost_used) {
    float logits[MAX_VOCAB];
    int   candidates[MAX_VOCAB];
    int   n_cand = 0;

    /* gather candidates that fit syllable budget */
    for (int i = 0; i < vocab_size; i++) {
        if (vocab[i].syllables > syl_remaining) continue;
        if (is_used(i)) continue;
        candidates[n_cand] = i;
        logits[n_cand] = score_word(i);
        n_cand++;
    }

    if (n_cand == 0) return -1;

    /* language filter: remove foreign words from candidates, keep ghost */
    {
        int new_cand = 0;
        for (int i = 0; i < n_cand; i++) {
            int wlang = vocab[candidates[i]].lang;
            int keep = 0;
            if (wlang == target_lang) {
                keep = 1;
            } else if (ghost_lang >= 0 && wlang == ghost_lang && ghost_used && !*ghost_used) {
                /* ghost voice: keep one candidate from ghost language */
                keep = 1;
                logits[i] *= 0.3f; /* reduce weight relative to target */
            }
            /* else: foreign word, drop it */
            if (keep) {
                candidates[new_cand] = candidates[i];
                logits[new_cand] = logits[i];
                new_cand++;
            }
        }
        /* if no target-lang candidates at all, fall back to all */
        if (new_cand > 0) n_cand = new_cand;
    }

    /* mass weighting: heavy words dominate.
     * function words (mass < 0.20) almost never appear.
     * Brodsky uses prepositions sparingly — "beneath", "against", "beyond"
     * are allowed because they have mass >= 0.25. "the", "a", "is" — killed. */
    for (int i = 0; i < n_cand; i++) {
        float m = vocab[candidates[i]].mass;
        if (m < 0.12f)
            logits[i] *= 0.001f;   /* "the", "a", "is", "of" — effectively dead */
        else if (m < 0.20f)
            logits[i] *= 0.02f;    /* "that", "which", "when" — rare */
        else
            logits[i] *= (0.15f + 0.85f * m);
    }

    /* consecutive function/light word penalty:
     * never two light words in a row */
    if (org.last_word >= 0 && vocab[org.last_word].mass < 0.30f) {
        for (int i = 0; i < n_cand; i++) {
            if (vocab[candidates[i]].mass < 0.30f)
                logits[i] *= 0.005f;
        }
    }

    /* consonant density bonus — Brodsky's sound clusters */
    for (int i = 0; i < n_cand; i++)
        logits[i] *= (1.0f + 0.5f * vocab[candidates[i]].consonant_density);

    /* syllable greed: prefer longer words strongly */
    if (!force_max_syl) {
        for (int i = 0; i < n_cand; i++) {
            int s = vocab[candidates[i]].syllables;
            if (s >= 4)      logits[i] *= 3.0f;
            else if (s >= 3) logits[i] *= 2.2f;
            else if (s == 2) logits[i] *= 1.4f;
            /* 1-syllable: no bonus — must earn its place */
        }
    } else {
        /* force max syllable: strongly prefer words that eat remaining budget */
        for (int i = 0; i < n_cand; i++) {
            if (vocab[candidates[i]].syllables == syl_remaining)
                logits[i] *= 5.0f;
        }
    }

    /* adjacent adjective penalty */
    if (org.prev_was_adj) {
        for (int i = 0; i < n_cand; i++) {
            if (vocab[candidates[i]].is_adjective)
                logits[i] *= 0.05f;
        }
    }

    /* velocity modulation */
    float vel_mult = 1.0f;
    switch (org.velocity) {
        case VEL_RUN:     vel_mult = 1.3f; break;
        case VEL_STOP:    vel_mult = 0.7f; break;
        case VEL_BREATHE: vel_mult = 0.8f; break;
        case VEL_UP:      vel_mult = 1.1f; break;
        case VEL_DOWN:    vel_mult = 0.9f; break;
        default: break;
    }
    for (int i = 0; i < n_cand; i++)
        logits[i] *= vel_mult;

    /* softmax with temperature */
    float max_l = -1e30f;
    for (int i = 0; i < n_cand; i++)
        if (logits[i] > max_l) max_l = logits[i];

    float sum = 0.0f;
    for (int i = 0; i < n_cand; i++) {
        logits[i] = expf((logits[i] - max_l) / org.tau);
        sum += logits[i];
    }
    if (sum < 1e-10f) sum = 1e-10f;

    /* sample */
    float r = rng_float() * sum;
    float cumsum = 0.0f;
    int picked = candidates[n_cand - 1];
    for (int i = 0; i < n_cand; i++) {
        cumsum += logits[i];
        if (cumsum >= r) { picked = candidates[i]; break; }
    }

    /* track ghost word usage */
    if (ghost_used && ghost_lang >= 0 && vocab[picked].lang == ghost_lang
        && vocab[picked].lang != target_lang) {
        *ghost_used = 1;
    }

    return picked;
}

/* ─── GENERATE ONE LINE ─────────────────────────────────────────────── */

typedef struct {
    int  words[MAX_LINE_WORDS];
    int  count;
    int  syllables;
} Line;

/*
 * target_lang: primary language
 * ghost_lang: if >= 0, allow one ghost word from this language
 * ghost_used: pointer to ghost tracking flag
 */
static void generate_line(Line *line, int target_syl,
                          int target_lang, int ghost_lang, int *ghost_used) {
    line->count = 0;
    line->syllables = 0;

    while (line->syllables < target_syl && line->count < MAX_LINE_WORDS) {
        int remaining = target_syl - line->syllables;
        /* if only 1-2 syllables left, try to force exact match */
        int force = (remaining <= 2) ? 1 : 0;
        int idx = sample_word(remaining, force, target_lang, ghost_lang, ghost_used);
        if (idx < 0) break;

        line->words[line->count++] = idx;
        line->syllables += vocab[idx].syllables;
        org.acc_mass += vocab[idx].mass;

        /* update state */
        if (org.last_word >= 0) {
            hebbian_record(org.last_word, idx);
            /* online corpus learning: reinforce generated bigrams & hebbian */
            corpus_bg_add(org.last_word, idx, CORPUS_ONLINE_DECAY);
            corpus_hb_add(org.last_word, idx, CORPUS_ONLINE_DECAY);
        }
        /* track tension pair usage — lifecycle decay */
        if (org.last_word >= 0)
            tension_used(org.last_word, idx);

        /* prophecy: check fulfillment, age, add new prediction */
        prophecy_update(&org.prophecy, idx);
        /* predict next from corpus bigrams */
        int pred = corpus_best_bigram(idx);
        if (pred >= 0) prophecy_add(&org.prophecy, pred, 0.5f);

        org.last_emotion = vocab[idx].emotion;
        org.prev_was_adj = vocab[idx].is_adjective;
        org.last_word = idx;
        mark_used(idx);

        /* parliament: update expert vitality after each word election */
        parliament_update(idx);
    }
}

/* ─── GENERATE ONE HAIKU ────────────────────────────────────────────── */

typedef struct {
    Line  lines[3];
    float destiny_after[DESTINY_DIM]; /* destiny state after this haiku */
    int   has_enjamb;                 /* ends with em-dash */
} Haiku;

static void generate_haiku(Haiku *h) {
    static const int target_syl[3] = {5, 7, 5};
    int tlang = org.current_lang;
    int glang = ghost_language();
    /* avoid ghost = same as target */
    if (glang == tlang) glang = -1;
    int ghost_used = 0;

    /* if enjambment carry, blend destiny */
    if (org.enjamb) {
        for (int d = 0; d < DESTINY_DIM; d++)
            org.destiny[d] = 0.6f * org.destiny[d] + 0.4f * org.enjamb_destiny[d];
        vec_normalize(org.destiny, DESTINY_DIM);
        org.enjamb = 0;
    }

    /* save destiny before line 1 for line 3 averaging */
    float dest_before[DESTINY_DIM];
    memcpy(dest_before, org.destiny, sizeof(dest_before));

    /* line 1: pure target language */
    generate_line(&h->lines[0], target_syl[0], tlang, -1, NULL);

    float dest_after_l1[DESTINY_DIM];
    memcpy(dest_after_l1, org.destiny, sizeof(dest_after_l1));

    /* drift destiny slightly */
    for (int d = 0; d < DESTINY_DIM; d++)
        org.destiny[d] += (rng_float() - 0.5f) * 0.1f;
    vec_normalize(org.destiny, DESTINY_DIM);

    /* line 2: ghost voice allowed (one word from ghost language) */
    generate_line(&h->lines[1], target_syl[1], tlang, glang, &ghost_used);

    float dest_after_l2[DESTINY_DIM];
    memcpy(dest_after_l2, org.destiny, sizeof(dest_after_l2));

    /* line 3 destiny = average(destiny_after_l1, destiny_after_l2) */
    for (int d = 0; d < DESTINY_DIM; d++)
        org.destiny[d] = 0.5f * dest_after_l1[d] + 0.5f * dest_after_l2[d];
    vec_normalize(org.destiny, DESTINY_DIM);

    /* line 3: pure target language */
    generate_line(&h->lines[2], target_syl[2], tlang, -1, NULL);

    memcpy(h->destiny_after, org.destiny, sizeof(h->destiny_after));

    /* enjambment check: if julia > 0.3, mark for carry */
    h->has_enjamb = (org.julia > 0.3f) ? 1 : 0;
    if (h->has_enjamb) {
        memcpy(org.enjamb_destiny, h->destiny_after, sizeof(org.enjamb_destiny));
        org.enjamb = 1;
    }
}

/* ─── FORMAT AND PRINT HAIKU ────────────────────────────────────────── */

static int haiku_to_string(const Haiku *h, char *buf, int bufsize) {
    int pos = 0;
    for (int ln = 0; ln < 3; ln++) {
        const Line *line = &h->lines[ln];
        for (int w = 0; w < line->count; w++) {
            if (w > 0 && pos < bufsize - 1) buf[pos++] = ' ';
            int idx = line->words[w];
            const char *text = vocab[idx].text;
            int len = (int)strlen(text);
            if (pos + len < bufsize) {
                memcpy(buf + pos, text, (size_t)len);
                pos += len;
            }
        }
        /* enjambment dash on last line */
        if (ln == 2 && h->has_enjamb && pos + 2 < bufsize) {
            buf[pos++] = ' ';
            buf[pos++] = '-';
            buf[pos++] = '-';
        }
        if (ln < 2 && pos < bufsize - 1) buf[pos++] = '\n';
    }
    if (pos < bufsize) buf[pos] = '\0';
    return pos;
}

static void print_haiku_colored(const Haiku *h) {
    for (int ln = 0; ln < 3; ln++) {
        const Line *line = &h->lines[ln];
        printf("  ");
        for (int w = 0; w < line->count; w++) {
            if (w > 0) printf(" ");
            int idx = line->words[w];
            int emo = vocab[idx].emotion;
            printf("%s%s%s", emo_color[emo], vocab[idx].text, ANSI_RESET);
        }
        if (ln == 2 && h->has_enjamb) {
            printf(" %s--%s", ANSI_DIM, ANSI_RESET);
        }
        printf("\n");
    }
}

/* ─── BETWEEN-HAIKU UPDATES ─────────────────────────────────────────── */

static void inter_haiku_update(void) {
    /* chambers step */
    chambers_step(&org.chambers, 0.3f);

    /* julia grows */
    org.julia += 0.08f + rng_float() * 0.05f;

    /* prophecy debt grows Julia — unfulfilled predictions = longing */
    {
        float debt = 0;
        for (int p = 0; p < org.prophecy.n; p++)
            if (!org.prophecy.p[p].fulfilled) debt += (float)org.prophecy.p[p].age * 0.01f;
        org.julia += debt * 0.05f;
    }

    if (org.julia > 1.0f) org.julia = 1.0f;

    /* destiny drift from exhale */
    int frag = (int)(rng_next() % EXHALE_COUNT);
    for (int d = 0; d < DESTINY_DIM; d++)
        org.destiny[d] += exhale[frag].destiny[d] * 0.05f;
    vec_normalize(org.destiny, DESTINY_DIM);

    /* metaweight mutation */
    org.alpha   += (rng_float() - 0.5f) * 0.02f;
    org.beta    += (rng_float() - 0.5f) * 0.02f;
    org.gamma_w += (rng_float() - 0.5f) * 0.02f;
    org.trauma_w += (rng_float() - 0.5f) * 0.02f;
    if (org.alpha < 0.0f) org.alpha = 0.0f;
    if (org.beta  < 0.0f) org.beta  = 0.0f;
    if (org.gamma_w < 0.0f) org.gamma_w = 0.0f;
    if (org.trauma_w < 0.0f) org.trauma_w = 0.0f;

    /* temperature modulation */
    org.tau = TAU_BASE + org.julia * 0.3f - org.planet_diss * 0.2f;
    if (org.tau < 0.5f) org.tau = 0.5f;
    if (org.tau > 2.5f) org.tau = 2.5f;

    /* parliament lifecycle: mitosis and apoptosis between haiku */
    parliament_lifecycle(&org.parliament);

    /* velocity shift */
    float v_roll = rng_float();
    if (v_roll < 0.1f)      org.velocity = VEL_STOP;
    else if (v_roll < 0.2f) org.velocity = VEL_BREATHE;
    else if (v_roll < 0.35f) org.velocity = VEL_RUN;
    else if (v_roll < 0.45f) org.velocity = VEL_UP;
    else if (v_roll < 0.55f) org.velocity = VEL_DOWN;
    else                     org.velocity = VEL_WALK;
}

/* ─── CYCLE STOP PROBABILITY ────────────────────────────────────────── */

static int should_stop_cycle(void) {
    if (org.haiku_in_cycle >= MAX_CYCLE_HAIKU) return 1; /* shabbat */
    /* Brodsky doesn't shut up after one stanza.
     * First 2 haiku: almost never stop. 3rd: small chance. 5th+: real chance. */
    if (org.haiku_in_cycle < 2) return 0; /* minimum 2 haiku per cycle */
    float saturation = (float)org.haiku_in_cycle / (float)MAX_CYCLE_HAIKU;
    float x = org.acc_mass * 0.15f + saturation * 0.6f +
              org.planet_diss * 0.2f + org.julia * 0.3f - 2.5f;
    float prob = sigmoid(x);
    return rng_float() < prob;
}

/* ─── DISPLAY CYCLE INFO ────────────────────────────────────────────── */

static const char *season_names[4] = {"spring", "summer", "autumn", "winter"};
static const char *vel_names[VEL_COUNT] = {
    "WALK", "RUN", "STOP", "BREATHE", "UP", "DOWN"
};

static void print_cycle_header(int cycle_num) {
    printf("\n%s━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━%s\n",
           ANSI_DIM, ANSI_RESET);
    printf("%scycle %d%s", ANSI_BOLD, cycle_num, ANSI_RESET);
    printf("  %s· %s ·%s", ANSI_DIM, season_names[org.season], ANSI_RESET);
    printf("  %splanet %.2f%s", ANSI_DIM, org.planet_diss, ANSI_RESET);
    printf("  %scalendar %.2f%s", ANSI_DIM, org.cal_diss, ANSI_RESET);
    printf("  %sparliament: %d alive, %d elections%s\n",
           ANSI_DIM, parliament_alive_count(&org.parliament),
           org.parliament.elections, ANSI_RESET);
}

static void print_haiku_header(int haiku_num) {
    printf("\n  %s[%d]%s", ANSI_DIM, haiku_num, ANSI_RESET);
    printf("  %sjulia=%.2f%s", emo_color[EMO_JULIA], org.julia, ANSI_RESET);
    printf("  %sτ=%.2f%s", ANSI_DIM, org.tau, ANSI_RESET);
    printf("  %s%s%s", ANSI_DIM, vel_names[org.velocity], ANSI_RESET);
    printf("  %sprophecy:%d/%d%s\n", ANSI_DIM,
           org.prophecy.fulfilled_total, org.prophecy.created_total, ANSI_RESET);
}

static void print_chambers(void) {
    printf("  %schambers:%s ", ANSI_DIM, ANSI_RESET);
    for (int i = 0; i < CH_COUNT; i++) {
        float a = chamber_activation(&org.chambers, i);
        const char *col = a > 0.3f ? "\033[97m" : (a < -0.3f ? "\033[90m" : "\033[37m");
        static const char ch_short[CH_COUNT] = {'F','L','R','V','W','X'};
        printf("%s%c%.1f%s ", col, ch_short[i], a, ANSI_RESET);
    }
    printf("\n");
}

static void print_cycle_footer(int haiku_count) {
    printf("\n  %s%d haiku · mass %.1f · julia %.2f%s\n",
           ANSI_DIM, haiku_count, org.acc_mass, org.julia, ANSI_RESET);
    printf("%s━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━%s\n",
           ANSI_DIM, ANSI_RESET);
}

/* ─── GENERATE ONE FULL CYCLE ───────────────────────────────────────── */

static int generate_cycle(int cycle_num, char *out_buf, int out_bufsize) {
    cycle_reset();
    org.total_cycles++;
    int out_pos = 0;

    print_cycle_header(cycle_num);
    print_chambers();

    do {
        org.haiku_in_cycle++;

        print_haiku_header(org.haiku_in_cycle);

        Haiku h;
        memset(&h, 0, sizeof(h));
        generate_haiku(&h);
        print_haiku_colored(&h);

        /* write to buffer for web mode */
        if (out_buf && out_pos < out_bufsize - 256) {
            char tmp[512];
            int len = haiku_to_string(&h, tmp, (int)sizeof(tmp));
            if (out_pos + len + 2 < out_bufsize) {
                if (out_pos > 0) { out_buf[out_pos++] = '\n'; out_buf[out_pos++] = '\n'; }
                memcpy(out_buf + out_pos, tmp, (size_t)len);
                out_pos += len;
            }
        }

        if (should_stop_cycle()) break;

        inter_haiku_update();

    } while (1);

    if (out_buf && out_pos < out_bufsize) out_buf[out_pos] = '\0';

    print_cycle_footer(org.haiku_in_cycle);
    return org.haiku_in_cycle;
}

/* ─── SPORE: PERSISTENCE ──────────────────────────────────────────── */

#define SPORE_MAGIC   0x42524F44  /* "BROD" */
#define SPORE_VERSION 2          /* v2: added parliament state */
#define SPORE_PATH    "brodsky.spore"

static int tension_pair_count(void) {
    int n = 0;
    while (tensions[n].a) n++;
    return n;
}

static void spore_save(const char *path) {
    FILE *f = fopen(path, "wb");
    if (!f) return;

    uint32_t magic = SPORE_MAGIC;
    uint32_t version = SPORE_VERSION;
    fwrite(&magic, 4, 1, f);
    fwrite(&version, 4, 1, f);

    /* tension pair use_counts and crystallized flags */
    int ntens = tension_pair_count();
    fwrite(&ntens, sizeof(int), 1, f);
    for (int i = 0; i < ntens; i++) {
        fwrite(&tensions[i].use_count, sizeof(int), 1, f);
        fwrite(&tensions[i].crystallized, sizeof(int), 1, f);
    }

    /* corpus bigrams */
    fwrite(&corpus_bg.count, sizeof(int), 1, f);
    fwrite(corpus_bg.src,    sizeof(int),   (size_t)corpus_bg.count, f);
    fwrite(corpus_bg.dst,    sizeof(int),   (size_t)corpus_bg.count, f);
    fwrite(corpus_bg.weight, sizeof(float), (size_t)corpus_bg.count, f);

    /* corpus hebbians */
    fwrite(&corpus_hb.count, sizeof(int), 1, f);
    fwrite(corpus_hb.word_a, sizeof(int),   (size_t)corpus_hb.count, f);
    fwrite(corpus_hb.word_b, sizeof(int),   (size_t)corpus_hb.count, f);
    fwrite(corpus_hb.weight, sizeof(float), (size_t)corpus_hb.count, f);

    /* chamber phases */
    fwrite(org.chambers.phase, sizeof(float), CH_COUNT, f);

    /* julia * 0.3 (decayed) */
    float julia_decay = org.julia * 0.3f;
    fwrite(&julia_decay, sizeof(float), 1, f);

    /* prophecy state */
    fwrite(&org.prophecy.n, sizeof(int), 1, f);
    fwrite(&org.prophecy.fulfilled_total, sizeof(int), 1, f);
    fwrite(&org.prophecy.created_total, sizeof(int), 1, f);
    for (int i = 0; i < org.prophecy.n; i++) {
        fwrite(&org.prophecy.p[i].target,    sizeof(int),   1, f);
        fwrite(&org.prophecy.p[i].strength,  sizeof(float), 1, f);
        fwrite(&org.prophecy.p[i].age,       sizeof(int),   1, f);
        fwrite(&org.prophecy.p[i].fulfilled, sizeof(int),   1, f);
    }

    /* total cycles */
    fwrite(&org.total_cycles, sizeof(int), 1, f);

    /* parliament state (v2) */
    fwrite(&org.parliament.n, sizeof(int), 1, f);
    fwrite(&org.parliament.elections, sizeof(int), 1, f);
    for (int i = 0; i < org.parliament.n; i++) {
        fwrite(org.parliament.e[i].bias, sizeof(float), EMO_COUNT, f);
        fwrite(&org.parliament.e[i].mass_pref, sizeof(float), 1, f);
        fwrite(&org.parliament.e[i].vitality,  sizeof(float), 1, f);
        fwrite(&org.parliament.e[i].overload,  sizeof(float), 1, f);
        fwrite(&org.parliament.e[i].wins,      sizeof(int),   1, f);
        fwrite(&org.parliament.e[i].alive,     sizeof(int),   1, f);
    }

    fclose(f);
}

static void spore_load(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) return; /* no spore = fresh start */

    uint32_t magic = 0, version = 0;
    if (fread(&magic, 4, 1, f) != 1 || magic != SPORE_MAGIC) {
        fclose(f);
        return;
    }
    if (fread(&version, 4, 1, f) != 1 || (version != 1 && version != SPORE_VERSION)) {
        fclose(f);
        return;
    }

    /* tension pair use_counts and crystallized flags */
    int ntens = 0;
    if (fread(&ntens, sizeof(int), 1, f) == 1) {
        int current_ntens = tension_pair_count();
        int to_read = ntens < current_ntens ? ntens : current_ntens;
        for (int i = 0; i < to_read; i++) {
            if (fread(&tensions[i].use_count, sizeof(int), 1, f) != 1) break;
            if (fread(&tensions[i].crystallized, sizeof(int), 1, f) != 1) break;
        }
        /* skip extra if spore has more than current code */
        for (int i = to_read; i < ntens; i++) {
            int dummy;
            if (fread(&dummy, sizeof(int), 1, f) != 1) break;
            if (fread(&dummy, sizeof(int), 1, f) != 1) break;
        }
    }

    /* corpus bigrams: spore overwrites fresh corpus state */
    int bg_count = 0;
    if (fread(&bg_count, sizeof(int), 1, f) == 1 && bg_count > 0 && bg_count <= CORPUS_BIGRAM_MAX) {
        corpus_bg.count = bg_count;
        if (fread(corpus_bg.src,    sizeof(int),   (size_t)bg_count, f) != (size_t)bg_count) { fclose(f); return; }
        if (fread(corpus_bg.dst,    sizeof(int),   (size_t)bg_count, f) != (size_t)bg_count) { fclose(f); return; }
        if (fread(corpus_bg.weight, sizeof(float), (size_t)bg_count, f) != (size_t)bg_count) { fclose(f); return; }
    }

    /* corpus hebbians */
    int hb_count = 0;
    if (fread(&hb_count, sizeof(int), 1, f) == 1 && hb_count > 0 && hb_count <= CORPUS_HEBBIAN_MAX) {
        corpus_hb.count = hb_count;
        if (fread(corpus_hb.word_a, sizeof(int),   (size_t)hb_count, f) != (size_t)hb_count) { fclose(f); return; }
        if (fread(corpus_hb.word_b, sizeof(int),   (size_t)hb_count, f) != (size_t)hb_count) { fclose(f); return; }
        if (fread(corpus_hb.weight, sizeof(float), (size_t)hb_count, f) != (size_t)hb_count) { fclose(f); return; }
    }

    /* chamber phases */
    if (fread(org.chambers.phase, sizeof(float), CH_COUNT, f) != CH_COUNT) { fclose(f); return; }

    /* julia (decayed) */
    float julia_decay = 0.0f;
    if (fread(&julia_decay, sizeof(float), 1, f) != 1) { fclose(f); return; }
    org.julia = julia_decay;

    /* prophecy state */
    int pn = 0;
    if (fread(&pn, sizeof(int), 1, f) == 1 && pn >= 0 && pn <= MAX_PROPHECY) {
        if (fread(&org.prophecy.fulfilled_total, sizeof(int), 1, f) != 1) { fclose(f); return; }
        if (fread(&org.prophecy.created_total, sizeof(int), 1, f) != 1) { fclose(f); return; }
        org.prophecy.n = pn;
        for (int i = 0; i < pn; i++) {
            if (fread(&org.prophecy.p[i].target,    sizeof(int),   1, f) != 1) break;
            if (fread(&org.prophecy.p[i].strength,  sizeof(float), 1, f) != 1) break;
            if (fread(&org.prophecy.p[i].age,       sizeof(int),   1, f) != 1) break;
            if (fread(&org.prophecy.p[i].fulfilled, sizeof(int),   1, f) != 1) break;
        }
    }

    /* total cycles */
    if (fread(&org.total_cycles, sizeof(int), 1, f) != 1) org.total_cycles = 0;

    /* parliament state (v2+) */
    if (version >= 2) {
        int pn_parl = 0;
        if (fread(&pn_parl, sizeof(int), 1, f) == 1 && pn_parl > 0 && pn_parl <= DOE_EXPERTS * 2) {
            org.parliament.n = pn_parl;
            if (fread(&org.parliament.elections, sizeof(int), 1, f) != 1) { fclose(f); return; }
            for (int i = 0; i < pn_parl; i++) {
                if (fread(org.parliament.e[i].bias, sizeof(float), EMO_COUNT, f) != EMO_COUNT) break;
                if (fread(&org.parliament.e[i].mass_pref, sizeof(float), 1, f) != 1) break;
                if (fread(&org.parliament.e[i].vitality,  sizeof(float), 1, f) != 1) break;
                if (fread(&org.parliament.e[i].overload,  sizeof(float), 1, f) != 1) break;
                if (fread(&org.parliament.e[i].wins,      sizeof(int),   1, f) != 1) break;
                if (fread(&org.parliament.e[i].alive,     sizeof(int),   1, f) != 1) break;
            }
        }
    }

    fclose(f);
    printf("[brodsky] spore loaded: %s\n", path);
}

/* Signal handler: save spore on Ctrl+C */
static void on_exit_signal(int sig) {
    (void)sig;
    spore_save(SPORE_PATH);
    printf("\n[brodsky] spore saved.\n");
    exit(0);
}

/* ─── BANNER ────────────────────────────────────────────────────────── */

static void print_banner(void) {
    printf("%s\n", ANSI_DIM);
    printf("  ██████╗ ██████╗  ██████╗ ██████╗ ███████╗██╗  ██╗██╗   ██╗\n");
    printf("  ██╔══██╗██╔══██╗██╔═══██╗██╔══██╗██╔════╝██║ ██╔╝╚██╗ ██╔╝\n");
    printf("  ██████╔╝██████╔╝██║   ██║██║  ██║███████╗█████╔╝  ╚████╔╝ \n");
    printf("  ██╔══██╗██╔══██╗██║   ██║██║  ██║╚════██║██╔═██╗   ╚██╔╝  \n");
    printf("  ██████╔╝██║  ██║╚██████╔╝██████╔╝███████║██║  ██╗   ██║   \n");
    printf("  ╚═════╝ ╚═╝  ╚═╝ ╚═════╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝   ╚═╝   \n");
    printf("%s\n", ANSI_RESET);
    printf("  %sa poetic organism%s\n", ANSI_DIM, ANSI_RESET);
    printf("  %svocab: %d words · %d languages · chambers: %d · emotions: %d%s\n",
           ANSI_DIM, vocab_size, LANG_COUNT, CH_COUNT, EMO_COUNT, ANSI_RESET);
    printf("  %scorpus: %d lines · %d bigrams · %d hebbian · parliament: %d experts%s\n",
           ANSI_DIM, corpus_total_lines, corpus_bg.count, corpus_hb.count,
           parliament_alive_count(&org.parliament), ANSI_RESET);
    printf("  %splanet: %.3f · calendar: %.3f · season: %s%s\n",
           ANSI_DIM, org.planet_diss, org.cal_diss,
           season_names[org.season], ANSI_RESET);
    if (org.total_cycles > 0)
        printf("  %spersistence: %d prior cycles · prophecy: %d/%d%s\n",
               ANSI_DIM, org.total_cycles,
               org.prophecy.fulfilled_total, org.prophecy.created_total,
               ANSI_RESET);
    printf("\n");
}

/* ─── REPL MODE ─────────────────────────────────────────────────────── */

static void repl(void) {
    print_banner();
    int cycle_num = 0;
    char input[256];

    while (1) {
        printf("\n%sbrodsky>%s ", ANSI_BOLD, ANSI_RESET);
        fflush(stdout);

        if (!fgets(input, (int)sizeof(input), stdin)) {
            /* EOF — save spore before exiting */
            spore_save(SPORE_PATH);
            printf("\n[brodsky] spore saved.\n");
            break;
        }

        /* strip newline */
        int len = (int)strlen(input);
        while (len > 0 && (input[len-1] == '\n' || input[len-1] == '\r'))
            input[--len] = '\0';

        if (len == 0) {
            /* empty enter = generate one cycle */
            cycle_num++;
            rng_seed((unsigned long)time(NULL) ^ (unsigned long)cycle_num * 6364136223846793005ULL);
            generate_cycle(cycle_num, NULL, 0);
            continue;
        }

        if (strcmp(input, "q") == 0 || strcmp(input, "quit") == 0 ||
            strcmp(input, "exit") == 0) {
            spore_save(SPORE_PATH);
            printf("\n  %s[brodsky] spore saved.%s\n", ANSI_DIM, ANSI_RESET);
            printf("\n  %s\"what gets left of a man amounts to a part.%s\n",
                   ANSI_DIM, ANSI_RESET);
            printf("  %s to his spoken part. to a part of speech.\"%s\n\n",
                   ANSI_DIM, ANSI_RESET);
            break;
        }

        if (strcmp(input, "help") == 0 || strcmp(input, "?") == 0) {
            printf("\n  %scommands:%s\n", ANSI_DIM, ANSI_RESET);
            printf("  [enter]      generate a cycle (1-7 haiku)\n");
            printf("  seed <N>     set RNG seed\n");
            printf("  tau <F>      set temperature\n");
            printf("  julia <F>    set julia field\n");
            printf("  chambers     show chamber state\n");
            printf("  vocab        show vocabulary stats\n");
            printf("  destiny      show destiny vector\n");
            printf("  exhale       show exhale fragments\n");
            printf("  prophecy     show current prophecies\n");
            printf("  parliament   show DOE expert parliament\n");
            printf("  doe          (alias for parliament)\n");
            printf("  N            generate N cycles\n");
            printf("  q/quit       exit\n");
            continue;
        }

        if (strncmp(input, "seed ", 5) == 0) {
            unsigned long s = strtoul(input + 5, NULL, 10);
            rng_seed(s);
            printf("  seed = %lu\n", s);
            continue;
        }

        if (strncmp(input, "tau ", 4) == 0) {
            org.tau = strtof(input + 4, NULL);
            printf("  τ = %.2f\n", org.tau);
            continue;
        }

        if (strncmp(input, "julia ", 6) == 0) {
            org.julia = strtof(input + 6, NULL);
            printf("  julia = %.2f\n", org.julia);
            continue;
        }

        if (strcmp(input, "chambers") == 0) {
            print_chambers();
            for (int i = 0; i < CH_COUNT; i++) {
                printf("  %s: phase=%.2f freq=%.2f act=%.2f\n",
                       ch_names[i], org.chambers.phase[i],
                       org.chambers.freq[i],
                       chamber_activation(&org.chambers, i));
            }
            continue;
        }

        if (strcmp(input, "vocab") == 0) {
            int emo_counts[EMO_COUNT];
            int lang_counts[LANG_COUNT];
            memset(emo_counts, 0, sizeof(emo_counts));
            memset(lang_counts, 0, sizeof(lang_counts));
            float total_mass = 0.0f;
            for (int i = 0; i < vocab_size; i++) {
                emo_counts[vocab[i].emotion]++;
                if (vocab[i].lang >= 0 && vocab[i].lang < LANG_COUNT)
                    lang_counts[vocab[i].lang]++;
                total_mass += vocab[i].mass;
            }
            printf("  %s%d words, avg mass %.2f%s\n",
                   ANSI_DIM, vocab_size, total_mass / (float)vocab_size, ANSI_RESET);
            printf("  %slanguages:%s", ANSI_DIM, ANSI_RESET);
            for (int l = 0; l < LANG_COUNT; l++)
                printf(" %s=%d", lang_names[l], lang_counts[l]);
            printf("\n");
            for (int e = 0; e < EMO_COUNT; e++) {
                printf("  %s%-11s %3d%s\n",
                       emo_color[e], emo_names[e], emo_counts[e], ANSI_RESET);
            }
            continue;
        }

        if (strcmp(input, "destiny") == 0) {
            printf("  destiny: [");
            for (int d = 0; d < DESTINY_DIM; d++)
                printf("%.2f%s", org.destiny[d], d < DESTINY_DIM-1 ? ", " : "");
            printf("]\n");
            continue;
        }

        if (strcmp(input, "exhale") == 0) {
            for (int i = 0; i < EXHALE_COUNT; i++)
                printf("  %s\"%s\"%s\n", ANSI_DIM, exhale[i].text, ANSI_RESET);
            continue;
        }

        if (strcmp(input, "parliament") == 0 || strcmp(input, "doe") == 0) {
            printf("  %sparliament: %d/%d alive, %d elections%s\n",
                   ANSI_DIM, parliament_alive_count(&org.parliament),
                   org.parliament.n, org.parliament.elections, ANSI_RESET);
            for (int i = 0; i < org.parliament.n; i++) {
                Expert *ex = &org.parliament.e[i];
                const char *name = (i < DOE_EXPERTS * 2) ? expert_names[i] : "unknown";
                if (!ex->alive) {
                    printf("  %s%-12s DEAD%s\n", ANSI_DIM, name, ANSI_RESET);
                    continue;
                }
                /* find dominant emotion bias */
                int dom_emo = 0;
                float dom_val = ex->bias[0];
                for (int e = 1; e < EMO_COUNT; e++) {
                    if (ex->bias[e] > dom_val) { dom_val = ex->bias[e]; dom_emo = e; }
                }
                printf("  %s%-12s%s vit=%.2f wins=%d overload=%.2f mass_pref=%.2f %s%s%s\n",
                       ANSI_BOLD, name, ANSI_RESET,
                       ex->vitality, ex->wins, ex->overload, ex->mass_pref,
                       emo_color[dom_emo], emo_names[dom_emo], ANSI_RESET);
            }
            continue;
        }

        if (strcmp(input, "prophecy") == 0) {
            printf("  %sprophecies: %d active, %d fulfilled / %d total%s\n",
                   ANSI_DIM, org.prophecy.n,
                   org.prophecy.fulfilled_total, org.prophecy.created_total,
                   ANSI_RESET);
            for (int i = 0; i < org.prophecy.n; i++) {
                Prophecy *pp = &org.prophecy.p[i];
                const char *word = (pp->target >= 0 && pp->target < vocab_size)
                    ? vocab[pp->target].text : "???";
                printf("  %s[%d] \"%s\" str=%.2f age=%d%s%s\n",
                       pp->fulfilled ? emo_color[EMO_RESONANCE] : emo_color[EMO_JULIA],
                       i, word, pp->strength, pp->age,
                       pp->fulfilled ? " FULFILLED" : "",
                       ANSI_RESET);
            }
            if (org.prophecy.n == 0)
                printf("  %s(no active prophecies)%s\n", ANSI_DIM, ANSI_RESET);
            continue;
        }

        /* try to parse as number of cycles */
        int n = atoi(input);
        if (n > 0 && n <= 100) {
            for (int i = 0; i < n; i++) {
                cycle_num++;
                rng_seed((unsigned long)time(NULL) ^ (unsigned long)cycle_num * 6364136223846793005ULL);
                generate_cycle(cycle_num, NULL, 0);
            }
            continue;
        }

        /* not a command — treat as prompt */
        float diss = ingest_prompt(input);
        printf("  %sdissonance: %.2f · lang: %s%s\n",
               ANSI_DIM, diss, lang_names[org.current_lang], ANSI_RESET);
        cycle_num++;
        generate_cycle(cycle_num, NULL, 0);
    }
}

/* ─── WEB MODE (simple HTTP server) ─────────────────────────────────── */

#if defined(__unix__) || defined(__APPLE__)

static const char *html_template_head =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html; charset=utf-8\r\n"
    "Connection: close\r\n"
    "Access-Control-Allow-Origin: *\r\n"
    "\r\n"
    "<!DOCTYPE html><html><head>"
    "<meta charset='utf-8'>"
    "<title>BRODSKY</title>"
    "<style>"
    "body{background:#0a0a0a;color:#aaa;font-family:'Courier New',monospace;"
    "max-width:640px;margin:80px auto;padding:20px;}"
    "h1{color:#555;font-size:14px;letter-spacing:8px;text-transform:uppercase;}"
    ".haiku{margin:30px 0;line-height:1.8;}"
    ".haiku .line{display:block;}"
    ".trauma{color:#c44;}.joy{color:#cc8;}.grief{color:#68c;}"
    ".resonance{color:#6cc;}.desire{color:#c6c;}.void{color:#666;}"
    ".rage{color:#e66;}.tenderness{color:#6a6;}.julia{color:#c8f;}"
    ".meta{color:#444;font-size:11px;margin-top:40px;}"
    ".dash{color:#555;}"
    "a{color:#555;text-decoration:none;border-bottom:1px solid #333;}"
    "a:hover{color:#888;}"
    "</style></head><body>"
    "<h1>BRODSKY</h1>";

static const char *html_template_tail =
    "<div class='meta'>"
    "<a href='/'>generate again</a>"
    "</div></body></html>";

static const char *emo_class[EMO_COUNT] = {
    "trauma", "joy", "grief", "resonance",
    "desire", "void", "rage", "tenderness", "julia"
};

static int haiku_to_html(const Haiku *h, char *buf, int bufsize) {
    int pos = 0;
    pos += snprintf(buf + pos, (size_t)(bufsize - pos), "<div class='haiku'>");
    for (int ln = 0; ln < 3; ln++) {
        const Line *line = &h->lines[ln];
        pos += snprintf(buf + pos, (size_t)(bufsize - pos), "<span class='line'>");
        for (int w = 0; w < line->count; w++) {
            if (w > 0) pos += snprintf(buf + pos, (size_t)(bufsize - pos), " ");
            int idx = line->words[w];
            int emo = vocab[idx].emotion;
            pos += snprintf(buf + pos, (size_t)(bufsize - pos),
                           "<span class='%s'>%s</span>",
                           emo_class[emo], vocab[idx].text);
        }
        if (ln == 2 && h->has_enjamb) {
            pos += snprintf(buf + pos, (size_t)(bufsize - pos),
                           " <span class='dash'>&mdash;</span>");
        }
        pos += snprintf(buf + pos, (size_t)(bufsize - pos), "</span>");
    }
    pos += snprintf(buf + pos, (size_t)(bufsize - pos), "</div>");
    return pos;
}

static void web_serve(void) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) { perror("socket"); return; }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(WEB_PORT);

    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(server_fd);
        return;
    }

    if (listen(server_fd, 5) < 0) {
        perror("listen");
        close(server_fd);
        return;
    }

    printf("brodsky listening on http://localhost:%d\n", WEB_PORT);

    int cycle_num = 0;

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_fd < 0) continue;

        /* read request (we don't care about it much) */
        char req[2048];
        ssize_t nr = read(client_fd, req, sizeof(req) - 1);
        if (nr > 0) req[nr] = '\0';
        else req[0] = '\0';

        /* check for favicon to skip */
        if (strstr(req, "favicon")) {
            const char *r404 = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
            write(client_fd, r404, strlen(r404));
            close(client_fd);
            continue;
        }

        /* generate a cycle */
        cycle_num++;
        rng_seed((unsigned long)time(NULL) ^ (unsigned long)cycle_num * 6364136223846793005ULL);
        cycle_reset();

        char response[16384];
        int rpos = 0;

        /* head */
        int hlen = (int)strlen(html_template_head);
        memcpy(response + rpos, html_template_head, (size_t)hlen);
        rpos += hlen;

        /* cycle info */
        rpos += snprintf(response + rpos, (size_t)(sizeof(response) - (size_t)rpos),
                        "<div class='meta'>cycle %d &middot; %s &middot; "
                        "planet %.2f &middot; julia %.2f</div>",
                        cycle_num, season_names[org.season],
                        org.planet_diss, org.julia);

        /* generate haiku */
        do {
            org.haiku_in_cycle++;

            Haiku h;
            memset(&h, 0, sizeof(h));
            generate_haiku(&h);

            rpos += haiku_to_html(&h, response + rpos,
                                  (int)(sizeof(response) - (size_t)rpos));

            if (should_stop_cycle()) break;
            inter_haiku_update();
        } while (1);

        /* also print to terminal */
        printf("[web] cycle %d: %d haiku, mass %.1f, julia %.2f\n",
               cycle_num, org.haiku_in_cycle, org.acc_mass, org.julia);

        /* tail */
        int tlen = (int)strlen(html_template_tail);
        if (rpos + tlen < (int)sizeof(response)) {
            memcpy(response + rpos, html_template_tail, (size_t)tlen);
            rpos += tlen;
        }

        write(client_fd, response, (size_t)rpos);
        close(client_fd);
    }
}

#endif /* unix/apple */

/* ─── MAIN ──────────────────────────────────────────────────────────── */

int main(int argc, char **argv) {
    rng_seed((unsigned long)time(NULL));
    load_vocabulary();
    load_all_corpora();
    organism_init();

    /* load spore (persistence) after init — merges saved state */
    spore_load(SPORE_PATH);

    /* install signal handler for clean exit */
#if defined(__unix__) || defined(__APPLE__)
    signal(SIGINT, on_exit_signal);
#endif

    int web_mode = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--web") == 0) web_mode = 1;
        else if (strcmp(argv[i], "--seed") == 0 && i + 1 < argc) {
            rng_seed(strtoul(argv[++i], NULL, 10));
        }
    }

#if defined(__unix__) || defined(__APPLE__)
    if (web_mode) {
        signal(SIGPIPE, SIG_IGN);
        web_serve();
        return 0;
    }
#else
    (void)web_mode;
#endif

    repl();
    return 0;
}
