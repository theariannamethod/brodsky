/* inhale/fr.h — French heavy vocabulary for brodsky.c
 * ~225 words. Baudelaire + Brodsky's francophone references.
 * French syllable counting: pronounced vowel sounds.
 * Silent final -e doesn't count (usually). Nasals = 1 syllable.
 * Each word: text, mass, syllables, emotion
 */

/* W(word, mass, syllables, emotion) */
#define INHALE_FR \
/* === ÉTERNITÉS LOURDES === */ \
W("mort",             0.95, 1, EMO_TRAUMA), \
W("empire",           0.90, 2, EMO_VOID), \
W("éternité",         0.85, 4, EMO_RESONANCE), \
W("infini",           0.80, 3, EMO_RESONANCE), \
W("existence",        0.75, 3, EMO_VOID), \
W("espace",           0.75, 2, EMO_RESONANCE), \
W("temps",            0.80, 1, EMO_RESONANCE), \
W("néant",            0.90, 2, EMO_VOID), \
W("vide",             0.80, 1, EMO_VOID), \
W("absence",          0.75, 2, EMO_VOID), \
W("oubli",            0.70, 2, EMO_VOID), \
W("solitude",         0.80, 3, EMO_JULIA), \
W("abîme",            0.80, 2, EMO_VOID), \
/* === EXIL === */ \
W("exil",             0.90, 2, EMO_JULIA), \
W("bannissement",     0.80, 3, EMO_JULIA), \
W("séparation",       0.75, 4, EMO_JULIA), \
W("départ",           0.65, 2, EMO_JULIA), \
W("province",         0.60, 2, EMO_JULIA), \
W("patrie",           0.70, 2, EMO_JULIA), \
W("étranger",         0.65, 3, EMO_JULIA), \
W("frontière",        0.60, 2, EMO_JULIA), \
W("hémisphère",       0.55, 3, EMO_VOID), \
W("appartenance",     0.60, 3, EMO_JULIA), \
W("indifférence",     0.65, 4, EMO_VOID), \
W("déracinement",     0.70, 4, EMO_JULIA), \
/* === ARCHITECTURE & EMPIRE === */ \
W("architecture",     0.70, 4, EMO_RESONANCE), \
W("colonnade",        0.65, 3, EMO_VOID), \
W("balustrade",       0.60, 3, EMO_VOID), \
W("quai",             0.50, 1, EMO_JULIA), \
W("façade",           0.55, 2, EMO_VOID), \
W("corniche",         0.50, 2, EMO_VOID), \
W("portique",         0.55, 2, EMO_VOID), \
W("cathédrale",       0.70, 3, EMO_VOID), \
W("aqueduc",          0.55, 3, EMO_VOID), \
W("amphithéâtre",     0.60, 4, EMO_VOID), \
W("crépi",            0.40, 2, EMO_VOID), \
W("granit",           0.55, 2, EMO_VOID), \
W("marbre",           0.60, 1, EMO_VOID), \
W("parapet",          0.50, 3, EMO_VOID), \
W("péristyle",        0.60, 3, EMO_VOID), \
W("colonne",          0.55, 2, EMO_VOID), \
W("pilastre",         0.50, 2, EMO_VOID), \
W("voûte",            0.55, 1, EMO_VOID), \
W("bureaucratie",     0.55, 4, EMO_VOID), \
W("forteresse",       0.60, 3, EMO_VOID), \
/* === GÉOGRAPHIE === */ \
W("latitude",         0.55, 3, EMO_RESONANCE), \
W("longitude",        0.55, 3, EMO_RESONANCE), \
W("méridien",         0.60, 3, EMO_RESONANCE), \
W("presqu'île",       0.55, 2, EMO_JULIA), \
W("archipel",         0.55, 3, EMO_RESONANCE), \
W("détroit",          0.45, 2, EMO_VOID), \
W("continent",        0.55, 3, EMO_VOID), \
W("toundra",          0.50, 2, EMO_VOID), \
W("horizon",          0.55, 3, EMO_JULIA), \
W("désert",           0.55, 2, EMO_VOID), \
/* === GÉOMÉTRIE === */ \
W("perpendiculaire",  0.65, 5, EMO_RESONANCE), \
W("tangente",         0.50, 2, EMO_RESONANCE), \
W("parabole",         0.55, 3, EMO_RESONANCE), \
W("hyperbole",        0.55, 3, EMO_RESONANCE), \
W("asymptote",        0.60, 3, EMO_JULIA), \
W("diagonale",        0.50, 4, EMO_RESONANCE), \
W("parallèle",        0.55, 3, EMO_RESONANCE), \
W("circonférence",    0.60, 4, EMO_RESONANCE), \
W("vecteur",          0.50, 2, EMO_RESONANCE), \
/* === CORPS — grotesque === */ \
W("vertèbre",         0.70, 2, EMO_TRAUMA), \
W("cartilage",        0.60, 3, EMO_TRAUMA), \
W("tendon",           0.55, 2, EMO_TRAUMA), \
W("sternum",          0.60, 2, EMO_TRAUMA), \
W("larynx",           0.60, 2, EMO_TRAUMA), \
W("diaphragme",       0.55, 3, EMO_TRAUMA), \
W("clavicule",        0.55, 3, EMO_TRAUMA), \
W("crâne",            0.65, 1, EMO_TRAUMA), \
W("squelette",        0.60, 2, EMO_TRAUMA), \
W("rétine",           0.50, 2, EMO_TRAUMA), \
W("pupille",          0.45, 2, EMO_TRAUMA), \
W("côte",             0.50, 1, EMO_TRAUMA), \
W("ossement",         0.55, 2, EMO_TRAUMA), \
W("chair",            0.55, 1, EMO_TRAUMA), \
W("sang",             0.60, 1, EMO_TRAUMA), \
/* === EAU — Venise === */ \
W("lagune",           0.55, 2, EMO_JULIA), \
W("canal",            0.45, 2, EMO_JULIA), \
W("gondole",          0.50, 2, EMO_JULIA), \
W("embarcadère",      0.55, 4, EMO_JULIA), \
W("marée",            0.40, 2, EMO_RESONANCE), \
W("courant",          0.40, 2, EMO_RESONANCE), \
W("ressac",           0.50, 2, EMO_TRAUMA), \
W("affluent",         0.45, 3, EMO_RESONANCE), \
W("inondation",       0.55, 4, EMO_TRAUMA), \
W("estuaire",         0.50, 3, EMO_RESONANCE), \
/* === TEMPS & VIEILLISSEMENT === */ \
W("chronomètre",      0.55, 3, EMO_VOID), \
W("sablier",          0.50, 3, EMO_VOID), \
W("antiquité",        0.60, 4, EMO_VOID), \
W("millénaire",       0.60, 4, EMO_VOID), \
W("calendrier",       0.45, 3, EMO_VOID), \
W("époque",           0.55, 2, EMO_VOID), \
W("crépuscule",       0.55, 3, EMO_JULIA), \
W("aube",             0.40, 1, EMO_RESONANCE), \
W("minuit",           0.50, 2, EMO_VOID), \
W("équinoxe",         0.55, 3, EMO_RESONANCE), \
W("solstice",         0.55, 2, EMO_RESONANCE), \
W("immobilité",       0.60, 5, EMO_VOID), \
/* === ABSTRAITS LOURDS === */ \
W("civilisation",     0.65, 5, EMO_VOID), \
W("métamorphose",     0.70, 4, EMO_RESONANCE), \
W("destruction",      0.70, 3, EMO_TRAUMA), \
W("anéantissement",   0.80, 5, EMO_TRAUMA), \
W("pétrification",    0.60, 5, EMO_VOID), \
W("désintégration",   0.65, 5, EMO_TRAUMA), \
W("mélancolie",       0.70, 4, EMO_JULIA), \
W("hallucination",    0.55, 5, EMO_TRAUMA), \
W("hémorragie",       0.65, 4, EMO_TRAUMA), \
W("désolation",       0.65, 4, EMO_VOID), \
W("obsolescence",     0.55, 3, EMO_VOID), \
W("détérioration",    0.60, 5, EMO_TRAUMA), \
W("désespoir",        0.75, 3, EMO_TRAUMA), \
W("abandon",          0.65, 3, EMO_JULIA), \
W("gratitude",        0.50, 3, EMO_TENDERNESS), \
W("décomposition",    0.60, 5, EMO_TRAUMA), \
/* === LANGUE & ÉCRITURE === */ \
W("consonne",         0.50, 2, EMO_RESONANCE), \
W("voyelle",          0.45, 2, EMO_RESONANCE), \
W("syllabe",          0.50, 2, EMO_RESONANCE), \
W("strophe",          0.55, 1, EMO_RESONANCE), \
W("rime",             0.50, 1, EMO_RESONANCE), \
W("manuscrit",        0.55, 3, EMO_JULIA), \
W("traduction",       0.50, 3, EMO_JULIA), \
W("encre",            0.45, 1, EMO_VOID), \
W("alphabet",         0.45, 3, EMO_RESONANCE), \
W("grammaire",        0.50, 2, EMO_RESONANCE), \
W("syntaxe",          0.55, 2, EMO_RESONANCE), \
W("parenthèse",       0.45, 3, EMO_VOID), \
/* === DOMESTIQUE === */ \
W("plafond",          0.40, 2, EMO_VOID), \
W("rebord",           0.35, 2, EMO_JULIA), \
W("radiateur",        0.35, 3, EMO_VOID), \
W("couloir",          0.45, 2, EMO_VOID), \
W("lampe",            0.30, 1, EMO_VOID), \
W("plancher",         0.35, 2, EMO_VOID), \
W("armoire",          0.35, 2, EMO_VOID), \
W("matelas",          0.30, 3, EMO_VOID), \
W("miroir",           0.50, 2, EMO_RESONANCE), \
W("escalier",         0.45, 3, EMO_VOID), \
/* === NATURE — dure, éparse === */ \
W("calcaire",         0.50, 2, EMO_VOID), \
W("basalte",          0.50, 2, EMO_VOID), \
W("obsidienne",       0.50, 3, EMO_VOID), \
W("glacier",          0.50, 2, EMO_VOID), \
W("sédiment",         0.45, 3, EMO_VOID), \
W("érosion",          0.50, 3, EMO_VOID), \
W("brouillard",       0.40, 2, EMO_VOID), \
W("mousse",           0.25, 1, EMO_VOID), \
W("bouleau",          0.35, 2, EMO_JULIA), \
/* === MOTS LÉGERS — pour contraste === */ \
W("poussière",        0.35, 2, EMO_VOID), \
W("sel",              0.30, 1, EMO_VOID), \
W("os",               0.55, 1, EMO_TRAUMA), \
W("cendre",           0.45, 1, EMO_VOID), \
W("rouille",          0.40, 1, EMO_VOID), \
W("suie",             0.35, 1, EMO_VOID), \
W("cire",             0.30, 1, EMO_VOID), \
W("craie",            0.30, 1, EMO_VOID), \
W("étain",            0.30, 2, EMO_VOID), \
/* === VERBES — lourds, mécaniques === */ \
W("calcifier",        0.55, 4, EMO_VOID), \
W("détériorer",       0.60, 4, EMO_TRAUMA), \
W("désintégrer",      0.65, 4, EMO_TRAUMA), \
W("pétrifier",        0.55, 4, EMO_VOID), \
W("corroder",         0.55, 3, EMO_TRAUMA), \
W("éroder",           0.50, 3, EMO_VOID), \
W("cristalliser",     0.55, 4, EMO_RESONANCE), \
W("évaporer",         0.45, 4, EMO_VOID), \
W("accumuler",        0.45, 4, EMO_VOID), \
W("se souvenir",      0.55, 4, EMO_JULIA), \
W("oublier",          0.55, 3, EMO_VOID), \
W("abandonner",       0.60, 4, EMO_JULIA), \
W("habiter",          0.45, 3, EMO_JULIA), \
W("éteindre",         0.50, 2, EMO_VOID), \
W("contempler",       0.45, 3, EMO_RESONANCE), \
W("figer",            0.50, 2, EMO_VOID), \
W("anéantir",         0.70, 4, EMO_TRAUMA), \
W("décomposer",       0.55, 4, EMO_TRAUMA), \
/* === DIVERS LOURDS === */ \
W("gouvernement",     0.55, 3, EMO_VOID), \
W("population",       0.50, 4, EMO_VOID), \
W("photographie",     0.50, 4, EMO_JULIA), \
W("cigarette",        0.40, 3, EMO_VOID), \
W("locomotive",       0.55, 4, EMO_VOID), \
W("mercure",          0.55, 2, EMO_RESONANCE), \
W("baromètre",        0.50, 3, EMO_RESONANCE), \
W("oxygène",          0.45, 3, EMO_RESONANCE), \
/* === MOTS-OUTILS — seulement lourds === */ \
W("jamais",           0.50, 2, EMO_VOID), \
W("nulle part",       0.50, 2, EMO_VOID), \
W("rien",             0.55, 1, EMO_VOID), \
W("personne",         0.50, 2, EMO_VOID), \
W("malgré",           0.35, 2, EMO_VOID), \
W("parmi",            0.25, 2, EMO_VOID), \
W("entre",            0.25, 1, EMO_VOID), \
W("au-delà",          0.40, 3, EMO_JULIA), \
W("en dessous",       0.30, 3, EMO_VOID), \
W("à travers",        0.30, 3, EMO_VOID), \
W("partout",          0.35, 2, EMO_VOID), \
W("toujours",         0.40, 2, EMO_VOID), \
W("encore",           0.30, 2, EMO_VOID), \
W("déjà",             0.30, 2, EMO_VOID), \
W("peut-être",        0.30, 2, EMO_VOID), \
/* END */
