/* inhale/es.h — Spanish heavy vocabulary for brodsky.c
 * ~225 words. Borges + architectural/imperial lexicon.
 * Spanish syllable counting: vowel nuclei, diphthongs = 1 syllable.
 * ai, ei, oi, au, eu, ou, ia, ie, io, iu, ua, ue, uo = diphthongs (1 syl).
 * Hiatus when accent mark breaks diphthong: ía, úa, etc. = 2 syllables.
 * Each word: text, mass, syllables, emotion
 */

/* W(word, mass, syllables, emotion) */
#define INHALE_ES \
/* === ETERNIDADES PESADAS === */ \
W("muerte",           0.95, 2, EMO_TRAUMA), \
W("imperio",          0.90, 3, EMO_VOID), \
W("eternidad",        0.85, 4, EMO_RESONANCE), \
W("infinito",         0.80, 4, EMO_RESONANCE), \
W("existencia",       0.75, 4, EMO_VOID), \
W("espacio",          0.75, 3, EMO_RESONANCE), \
W("tiempo",           0.80, 2, EMO_RESONANCE), \
W("nada",             0.90, 2, EMO_VOID), \
W("vacío",            0.80, 3, EMO_VOID), \
W("ausencia",         0.75, 3, EMO_VOID), \
W("olvido",           0.70, 3, EMO_VOID), \
W("soledad",          0.80, 3, EMO_JULIA), \
W("abismo",           0.80, 3, EMO_VOID), \
/* === EXILIO === */ \
W("exilio",           0.90, 3, EMO_JULIA), \
W("destierro",        0.80, 3, EMO_JULIA), \
W("separación",       0.75, 4, EMO_JULIA), \
W("partida",          0.65, 3, EMO_JULIA), \
W("provincia",        0.60, 3, EMO_JULIA), \
W("patria",           0.70, 2, EMO_JULIA), \
W("extranjero",       0.65, 4, EMO_JULIA), \
W("frontera",         0.60, 3, EMO_JULIA), \
W("hemisferio",       0.55, 4, EMO_VOID), \
W("pertenencia",      0.60, 4, EMO_JULIA), \
W("indiferencia",     0.65, 5, EMO_VOID), \
W("desarraigo",       0.70, 4, EMO_JULIA), \
/* === ARQUITECTURA & IMPERIO === */ \
W("arquitectura",     0.70, 5, EMO_RESONANCE), \
W("columnata",        0.65, 4, EMO_VOID), \
W("balaustrada",      0.60, 4, EMO_VOID), \
W("muelle",           0.50, 2, EMO_JULIA), \
W("fachada",          0.55, 3, EMO_VOID), \
W("cornisa",          0.50, 3, EMO_VOID), \
W("pórtico",          0.55, 3, EMO_VOID), \
W("catedral",         0.70, 3, EMO_VOID), \
W("acueducto",        0.55, 4, EMO_VOID), \
W("anfiteatro",       0.60, 5, EMO_VOID), \
W("estuco",           0.40, 3, EMO_VOID), \
W("granito",          0.55, 3, EMO_VOID), \
W("mármol",           0.60, 2, EMO_VOID), \
W("parapeto",         0.50, 4, EMO_VOID), \
W("peristilo",        0.55, 4, EMO_VOID), \
W("columna",          0.55, 3, EMO_VOID), \
W("pilastra",         0.50, 3, EMO_VOID), \
W("bóveda",           0.55, 3, EMO_VOID), \
W("fortaleza",        0.60, 4, EMO_VOID), \
W("burocracia",       0.55, 4, EMO_VOID), \
W("adoquín",          0.45, 3, EMO_VOID), \
/* === GEOGRAFÍA === */ \
W("latitud",          0.55, 3, EMO_RESONANCE), \
W("longitud",         0.55, 3, EMO_RESONANCE), \
W("meridiano",        0.60, 4, EMO_RESONANCE), \
W("península",        0.55, 4, EMO_JULIA), \
W("archipiélago",     0.55, 5, EMO_RESONANCE), \
W("estrecho",         0.45, 3, EMO_VOID), \
W("continente",       0.55, 4, EMO_VOID), \
W("tundra",           0.50, 2, EMO_VOID), \
W("horizonte",        0.55, 4, EMO_JULIA), \
W("desierto",         0.55, 3, EMO_VOID), \
/* === GEOMETRÍA === */ \
W("perpendicular",    0.65, 5, EMO_RESONANCE), \
W("tangente",         0.50, 3, EMO_RESONANCE), \
W("parábola",         0.55, 4, EMO_RESONANCE), \
W("hipérbola",        0.55, 4, EMO_RESONANCE), \
W("asíntota",         0.60, 4, EMO_JULIA), \
W("diagonal",         0.50, 4, EMO_RESONANCE), \
W("paralela",         0.55, 4, EMO_RESONANCE), \
W("circunferencia",   0.60, 5, EMO_RESONANCE), \
W("vector",           0.50, 2, EMO_RESONANCE), \
/* === CUERPO — grotesco === */ \
W("vértebra",         0.70, 3, EMO_TRAUMA), \
W("cartílago",        0.60, 4, EMO_TRAUMA), \
W("tendón",           0.55, 2, EMO_TRAUMA), \
W("esternón",         0.60, 3, EMO_TRAUMA), \
W("laringe",          0.55, 3, EMO_TRAUMA), \
W("diafragma",        0.55, 4, EMO_TRAUMA), \
W("clavícula",        0.55, 4, EMO_TRAUMA), \
W("cráneo",           0.65, 3, EMO_TRAUMA), \
W("esqueleto",        0.60, 4, EMO_TRAUMA), \
W("retina",           0.50, 3, EMO_TRAUMA), \
W("pupila",           0.45, 3, EMO_TRAUMA), \
W("costilla",         0.50, 3, EMO_TRAUMA), \
W("osamenta",         0.55, 4, EMO_TRAUMA), \
W("carne",            0.55, 2, EMO_TRAUMA), \
W("sangre",           0.60, 2, EMO_TRAUMA), \
/* === AGUA — Venecia === */ \
W("laguna",           0.55, 3, EMO_JULIA), \
W("canal",            0.45, 2, EMO_JULIA), \
W("góndola",          0.50, 3, EMO_JULIA), \
W("embarcadero",      0.55, 5, EMO_JULIA), \
W("marea",            0.40, 3, EMO_RESONANCE), \
W("corriente",        0.40, 3, EMO_RESONANCE), \
W("resaca",           0.50, 3, EMO_TRAUMA), \
W("afluente",         0.45, 4, EMO_RESONANCE), \
W("inundación",       0.55, 4, EMO_TRAUMA), \
W("estuario",         0.50, 4, EMO_RESONANCE), \
/* === TIEMPO & ENVEJECIMIENTO === */ \
W("cronómetro",       0.55, 4, EMO_VOID), \
W("reloj de arena",   0.50, 5, EMO_VOID), \
W("antigüedad",       0.60, 4, EMO_VOID), \
W("milenio",          0.60, 3, EMO_VOID), \
W("calendario",       0.45, 4, EMO_VOID), \
W("época",            0.55, 3, EMO_VOID), \
W("crepúsculo",       0.55, 4, EMO_JULIA), \
W("alba",             0.40, 2, EMO_RESONANCE), \
W("medianoche",       0.50, 4, EMO_VOID), \
W("equinoccio",       0.55, 4, EMO_RESONANCE), \
W("solsticio",        0.55, 3, EMO_RESONANCE), \
W("inmovilidad",      0.60, 5, EMO_VOID), \
/* === ABSTRACTOS PESADOS === */ \
W("civilización",     0.65, 5, EMO_VOID), \
W("metamorfosis",     0.70, 5, EMO_RESONANCE), \
W("destrucción",      0.70, 3, EMO_TRAUMA), \
W("aniquilación",     0.80, 5, EMO_TRAUMA), \
W("petrificación",    0.60, 5, EMO_VOID), \
W("desintegración",   0.65, 5, EMO_TRAUMA), \
W("melancolía",       0.70, 5, EMO_JULIA), \
W("alucinación",      0.55, 5, EMO_TRAUMA), \
W("hemorragia",       0.65, 4, EMO_TRAUMA), \
W("desolación",       0.65, 4, EMO_VOID), \
W("obsolescencia",    0.55, 5, EMO_VOID), \
W("deterioro",        0.60, 4, EMO_TRAUMA), \
W("desesperación",    0.75, 5, EMO_TRAUMA), \
W("abandono",         0.65, 4, EMO_JULIA), \
W("gratitud",         0.50, 3, EMO_TENDERNESS), \
W("descomposición",   0.60, 5, EMO_TRAUMA), \
/* === LENGUA & ESCRITURA === */ \
W("consonante",       0.50, 4, EMO_RESONANCE), \
W("vocal",            0.45, 2, EMO_RESONANCE), \
W("sílaba",           0.50, 3, EMO_RESONANCE), \
W("estrofa",          0.55, 3, EMO_RESONANCE), \
W("rima",             0.50, 2, EMO_RESONANCE), \
W("manuscrito",       0.55, 4, EMO_JULIA), \
W("traducción",       0.50, 3, EMO_JULIA), \
W("tinta",            0.45, 2, EMO_VOID), \
W("alfabeto",         0.45, 4, EMO_RESONANCE), \
W("gramática",        0.50, 4, EMO_RESONANCE), \
W("sintaxis",         0.55, 3, EMO_RESONANCE), \
/* === DOMÉSTICO === */ \
W("techo",            0.40, 2, EMO_VOID), \
W("alféizar",         0.35, 3, EMO_JULIA), \
W("radiador",         0.35, 3, EMO_VOID), \
W("pasillo",          0.45, 3, EMO_VOID), \
W("lámpara",          0.30, 3, EMO_VOID), \
W("tarima",           0.35, 3, EMO_VOID), \
W("armario",          0.35, 3, EMO_VOID), \
W("colchón",          0.30, 2, EMO_VOID), \
W("espejo",           0.55, 3, EMO_RESONANCE), \
W("escalera",         0.45, 4, EMO_VOID), \
/* === NATURALEZA — dura, escasa === */ \
W("caliza",           0.50, 3, EMO_VOID), \
W("basalto",          0.50, 3, EMO_VOID), \
W("obsidiana",        0.50, 4, EMO_VOID), \
W("glaciar",          0.50, 2, EMO_VOID), \
W("sedimento",        0.45, 4, EMO_VOID), \
W("erosión",          0.50, 3, EMO_VOID), \
W("niebla",           0.35, 2, EMO_VOID), \
W("musgo",            0.25, 2, EMO_VOID), \
W("abedul",           0.35, 3, EMO_JULIA), \
/* === PALABRAS LIGERAS — para contraste === */ \
W("polvo",            0.30, 2, EMO_VOID), \
W("sal",              0.30, 1, EMO_VOID), \
W("hueso",            0.55, 2, EMO_TRAUMA), \
W("ceniza",           0.45, 3, EMO_VOID), \
W("óxido",            0.40, 3, EMO_VOID), \
W("hollín",           0.35, 2, EMO_VOID), \
W("cera",             0.30, 2, EMO_VOID), \
W("tiza",             0.30, 2, EMO_VOID), \
W("estaño",           0.30, 3, EMO_VOID), \
/* === BORGES === */ \
W("laberinto",        0.70, 4, EMO_RESONANCE), \
W("biblioteca",       0.60, 5, EMO_RESONANCE), \
W("destino",          0.65, 3, EMO_JULIA), \
W("puñal",            0.55, 2, EMO_TRAUMA), \
W("moneda",           0.45, 3, EMO_VOID), \
W("arena",            0.40, 3, EMO_VOID), \
W("tigre",            0.55, 2, EMO_RAGE), \
W("ruina",            0.60, 2, EMO_VOID), \
W("centinela",        0.50, 4, EMO_VOID), \
W("aleph",            0.75, 2, EMO_RESONANCE), \
W("zahir",            0.60, 2, EMO_RESONANCE), \
/* === VERBOS — pesados, mecánicos === */ \
W("calcificar",       0.55, 4, EMO_VOID), \
W("deteriorar",       0.60, 4, EMO_TRAUMA), \
W("desintegrar",      0.65, 4, EMO_TRAUMA), \
W("petrificar",       0.55, 4, EMO_VOID), \
W("corroer",          0.55, 3, EMO_TRAUMA), \
W("erosionar",        0.50, 4, EMO_VOID), \
W("cristalizar",      0.55, 4, EMO_RESONANCE), \
W("evaporar",         0.45, 4, EMO_VOID), \
W("acumular",         0.45, 4, EMO_VOID), \
W("recordar",         0.55, 3, EMO_JULIA), \
W("olvidar",          0.55, 3, EMO_VOID), \
W("abandonar",        0.60, 4, EMO_JULIA), \
W("habitar",          0.45, 3, EMO_JULIA), \
W("extinguir",        0.50, 3, EMO_VOID), \
W("contemplar",       0.45, 3, EMO_RESONANCE), \
W("aniquilar",        0.70, 4, EMO_TRAUMA), \
/* === DIVERSOS PESADOS === */ \
W("gobierno",         0.55, 3, EMO_VOID), \
W("población",        0.50, 3, EMO_VOID), \
W("fotografía",       0.50, 5, EMO_JULIA), \
W("cigarrillo",       0.40, 4, EMO_VOID), \
W("locomotora",       0.55, 5, EMO_VOID), \
W("mercurio",         0.55, 3, EMO_RESONANCE), \
W("barómetro",        0.50, 4, EMO_RESONANCE), \
W("oxígeno",          0.45, 4, EMO_RESONANCE), \
/* === PALABRAS FUNCIÓN — solo pesadas === */ \
W("nunca",            0.50, 2, EMO_VOID), \
W("en ninguna parte", 0.50, 6, EMO_VOID), \
W("nada",             0.55, 2, EMO_VOID), \
W("nadie",            0.50, 2, EMO_VOID), \
W("a pesar de",       0.35, 4, EMO_VOID), \
W("entre",            0.25, 2, EMO_VOID), \
W("más allá",         0.40, 3, EMO_JULIA), \
W("debajo",           0.30, 3, EMO_VOID), \
W("a través",         0.30, 3, EMO_VOID), \
W("por doquier",      0.35, 3, EMO_VOID), \
W("siempre",          0.40, 2, EMO_VOID), \
W("todavía",          0.30, 4, EMO_VOID), \
W("ya",               0.25, 1, EMO_VOID), \
W("quizás",           0.30, 2, EMO_VOID), \
/* END */
