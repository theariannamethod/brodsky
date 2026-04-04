/* inhale/he.h — Hebrew heavy vocabulary for brodsky.c
 * ~700 words. Biblical + Amichai + Goldberg + Ravikovitch lexicon.
 * Brodsky didn't write in Hebrew, but the organism does.
 * Every shoresh weighs like cast iron.
 * Syllable counts follow standard Hebrew phonology (vowel nuclei).
 * Each word: text, mass, syllables, emotion
 */

/* W(word, mass, syllables, emotion) */
#define INHALE_HE \
/* === ETERNALS — כבדים נצחיים === */ \
W("מוות",             0.95, 1, EMO_TRAUMA), \
W("אימפריה",          0.90, 4, EMO_VOID), \
W("נצח",              0.85, 2, EMO_RESONANCE), \
W("אינסוף",           0.80, 3, EMO_RESONANCE), \
W("קיום",             0.75, 2, EMO_VOID), \
W("מרחב",             0.75, 2, EMO_RESONANCE), \
W("זמן",              0.80, 2, EMO_RESONANCE), \
W("אין",              0.90, 1, EMO_VOID), \
W("תוהו",             0.85, 2, EMO_VOID), \
W("העדר",             0.80, 2, EMO_VOID), \
W("שכחה",             0.70, 3, EMO_VOID), \
W("בדידות",           0.80, 3, EMO_JULIA), \
W("תהום",             0.85, 2, EMO_VOID), \
W("גורל",             0.75, 2, EMO_TRAUMA), \
W("אלמוות",           0.80, 3, EMO_RESONANCE), \
/* === EXILE — גלות === */ \
W("גלות",             0.90, 2, EMO_JULIA), \
W("גירוש",            0.80, 2, EMO_JULIA), \
W("פרידה",            0.75, 3, EMO_JULIA), \
W("נדידה",            0.65, 3, EMO_JULIA), \
W("מולדת",            0.70, 3, EMO_JULIA), \
W("נכר",              0.65, 2, EMO_JULIA), \
W("גבול",             0.60, 2, EMO_JULIA), \
W("תפוצה",            0.65, 3, EMO_JULIA), \
W("שייכות",           0.60, 3, EMO_JULIA), \
W("אדישות",           0.65, 3, EMO_VOID), \
W("ניכור",            0.70, 2, EMO_VOID), \
W("געגוע",            0.70, 3, EMO_JULIA), \
W("מקלט",             0.55, 2, EMO_JULIA), \
W("נוודות",           0.60, 3, EMO_JULIA), \
W("מפה",              0.40, 2, EMO_JULIA), \
/* === ARCHITECTURE — אדריכלות === */ \
W("אדריכלות",         0.70, 5, EMO_RESONANCE), \
W("עמוד",             0.55, 2, EMO_VOID), \
W("טור",              0.50, 1, EMO_VOID), \
W("חומה",             0.60, 2, EMO_VOID), \
W("מבצר",             0.60, 2, EMO_VOID), \
W("קשת",              0.55, 2, EMO_VOID), \
W("כיפה",             0.55, 2, EMO_VOID), \
W("מזבח",             0.60, 2, EMO_VOID), \
W("היכל",             0.65, 2, EMO_VOID), \
W("מקדש",             0.70, 2, EMO_VOID), \
W("אמת מים",          0.55, 4, EMO_VOID), \
W("טיח",              0.40, 1, EMO_VOID), \
W("גרניט",            0.55, 2, EMO_VOID), \
W("שיש",              0.55, 1, EMO_VOID), \
W("מעקה",             0.50, 3, EMO_VOID), \
W("אבן",              0.50, 2, EMO_VOID), \
W("רצפה",             0.40, 2, EMO_VOID), \
W("מדרגה",            0.45, 3, EMO_VOID), \
W("חורבה",            0.60, 3, EMO_VOID), \
W("חורבן",            0.85, 2, EMO_TRAUMA), \
W("קמרון",            0.55, 2, EMO_VOID), \
W("אשנב",             0.50, 2, EMO_VOID), \
W("סף",               0.45, 1, EMO_VOID), \
W("אדן",              0.40, 2, EMO_VOID), \
W("משקוף",            0.50, 2, EMO_VOID), \
W("צריח",             0.55, 2, EMO_VOID), \
W("פרוזדור",          0.45, 3, EMO_VOID), \
W("אכסדרה",           0.50, 4, EMO_VOID), \
W("עליית גג",         0.40, 4, EMO_VOID), \
W("יסוד",             0.55, 2, EMO_RESONANCE), \
W("קורה",             0.45, 2, EMO_VOID), \
W("קונסטרוקציה",      0.55, 5, EMO_VOID), \
/* === GEOGRAPHY — גיאוגרפיה === */ \
W("מדבר",             0.55, 2, EMO_VOID), \
W("שממה",             0.65, 3, EMO_VOID), \
W("קו רוחב",          0.50, 3, EMO_RESONANCE), \
W("חצי אי",           0.50, 3, EMO_JULIA), \
W("ארכיפלג",          0.55, 4, EMO_RESONANCE), \
W("מפרץ",             0.45, 2, EMO_VOID), \
W("אופק",             0.55, 2, EMO_JULIA), \
W("יבשת",             0.50, 2, EMO_VOID), \
W("קרחון",            0.50, 2, EMO_VOID), \
W("ירושלים",          0.85, 5, EMO_JULIA), \
W("שפלה",             0.45, 2, EMO_VOID), \
W("נחל",              0.40, 2, EMO_VOID), \
W("צוק",              0.50, 1, EMO_VOID), \
W("מצוק",             0.55, 2, EMO_TRAUMA), \
/* === GEOMETRY — גיאומטריה === */ \
W("מאונך",            0.55, 3, EMO_RESONANCE), \
W("משיק",             0.50, 2, EMO_RESONANCE), \
W("פרבולה",           0.55, 4, EMO_RESONANCE), \
W("היפרבולה",         0.55, 4, EMO_RESONANCE), \
W("אסימפטוטה",        0.60, 5, EMO_JULIA), \
W("אלכסון",           0.50, 3, EMO_RESONANCE), \
W("מקביל",            0.50, 3, EMO_RESONANCE), \
W("היקף",             0.50, 2, EMO_RESONANCE), \
W("וקטור",            0.45, 2, EMO_RESONANCE), \
W("רדיוס",            0.45, 3, EMO_RESONANCE), \
W("ציר",              0.45, 1, EMO_RESONANCE), \
W("קואורדינטה",       0.50, 5, EMO_RESONANCE), \
/* === BODY — גוף === */ \
W("עמוד שדרה",        0.70, 4, EMO_TRAUMA), \
W("סחוס",             0.60, 2, EMO_TRAUMA), \
W("גיד",              0.55, 1, EMO_TRAUMA), \
W("עצם החזה",         0.60, 4, EMO_TRAUMA), \
W("גרון",             0.55, 2, EMO_TRAUMA), \
W("סרעפת",            0.55, 3, EMO_TRAUMA), \
W("עצם הבריח",        0.55, 4, EMO_TRAUMA), \
W("גולגולת",          0.70, 3, EMO_TRAUMA), \
W("שלד",              0.60, 2, EMO_TRAUMA), \
W("מאובן",            0.55, 3, EMO_VOID), \
W("רשתית",            0.50, 3, EMO_TRAUMA), \
W("אישון",            0.45, 3, EMO_TRAUMA), \
W("צלע",              0.55, 2, EMO_TRAUMA), \
W("בשר",              0.55, 2, EMO_TRAUMA), \
W("דם",               0.60, 1, EMO_TRAUMA), \
W("קרסול",            0.50, 2, EMO_TRAUMA), \
W("ירך",              0.55, 2, EMO_TRAUMA), \
W("עורק",             0.55, 2, EMO_TRAUMA), \
W("אגן",              0.50, 2, EMO_TRAUMA), \
W("קרום",             0.50, 1, EMO_TRAUMA), \
W("כף רגל",           0.45, 3, EMO_TRAUMA), \
W("פרק",              0.50, 2, EMO_TRAUMA), \
W("עורף",             0.55, 2, EMO_TRAUMA), \
W("כתף",              0.50, 2, EMO_TRAUMA), \
W("אמה",              0.45, 2, EMO_TRAUMA), \
W("טבור",             0.50, 2, EMO_TRAUMA), \
W("ריאה",             0.50, 3, EMO_TRAUMA), \
W("כליה",             0.50, 3, EMO_TRAUMA), \
W("לוע",              0.55, 1, EMO_TRAUMA), \
W("חיך",              0.45, 1, EMO_TRAUMA), \
W("אצבע",             0.40, 3, EMO_TENDERNESS), \
/* === WATER — מים === */ \
W("לגונה",            0.55, 3, EMO_JULIA), \
W("תעלה",             0.45, 3, EMO_JULIA), \
W("גונדולה",          0.50, 4, EMO_JULIA), \
W("רציף",             0.45, 2, EMO_JULIA), \
W("גאות",             0.40, 2, EMO_RESONANCE), \
W("שפל",              0.40, 1, EMO_VOID), \
W("זרם",              0.45, 1, EMO_RESONANCE), \
W("שיטפון",           0.55, 2, EMO_TRAUMA), \
W("אצה",              0.35, 2, EMO_VOID), \
W("מבוא ים",          0.45, 3, EMO_RESONANCE), \
W("מערבולת",          0.55, 4, EMO_TRAUMA), \
W("אדווה",            0.40, 3, EMO_RESONANCE), \
W("טפטוף",            0.35, 2, EMO_VOID), \
W("שלולית",           0.35, 3, EMO_VOID), \
/* === TIME — זמן === */ \
W("שעון",             0.45, 2, EMO_VOID), \
W("עתיקות",           0.60, 3, EMO_VOID), \
W("אלף שנה",          0.60, 3, EMO_VOID), \
W("לוח שנה",          0.40, 3, EMO_VOID), \
W("תקופה",            0.50, 3, EMO_VOID), \
W("דמדומים",          0.50, 4, EMO_JULIA), \
W("שחר",              0.40, 2, EMO_RESONANCE), \
W("חצות",             0.50, 2, EMO_VOID), \
W("קדמות",            0.55, 3, EMO_VOID), \
W("קיפאון",           0.60, 3, EMO_VOID), \
W("רגע",              0.40, 2, EMO_VOID), \
W("עידן",             0.55, 2, EMO_VOID), \
W("דור",              0.50, 1, EMO_RESONANCE), \
W("שקיעה",            0.45, 3, EMO_JULIA), \
W("הנץ",              0.40, 1, EMO_RESONANCE), \
W("סתיו",             0.45, 2, EMO_JULIA), \
W("ערב",              0.40, 2, EMO_JULIA), \
/* === ABSTRACT HEAVY — מופשט כבד === */ \
W("תרבות",            0.60, 3, EMO_VOID), \
W("התגלמות",          0.65, 4, EMO_RESONANCE), \
W("התפוררות",         0.65, 4, EMO_TRAUMA), \
W("השמדה",            0.80, 4, EMO_TRAUMA), \
W("התאבנות",          0.60, 4, EMO_VOID), \
W("התפרקות",          0.65, 4, EMO_TRAUMA), \
W("אובדן",            0.75, 2, EMO_JULIA), \
W("מלנכוליה",         0.70, 5, EMO_JULIA), \
W("הזיה",             0.50, 3, EMO_TRAUMA), \
W("שממון",            0.60, 2, EMO_VOID), \
W("ייאוש",            0.70, 2, EMO_TRAUMA), \
W("הכרת תודה",        0.50, 5, EMO_TENDERNESS), \
W("התגשמות",          0.55, 4, EMO_RESONANCE), \
W("כיליון",           0.70, 3, EMO_TRAUMA), \
W("כמיהה",            0.60, 3, EMO_DESIRE), \
W("ריקנות",           0.65, 3, EMO_VOID), \
W("יגון",             0.70, 2, EMO_GRIEF), \
W("תוגה",             0.65, 2, EMO_GRIEF), \
W("חרדה",             0.70, 3, EMO_TRAUMA), \
W("השלייה",           0.55, 4, EMO_VOID), \
W("כיסופים",          0.65, 3, EMO_DESIRE), \
/* === LANGUAGE & WRITING — שפה === */ \
W("עיצור",            0.50, 2, EMO_RESONANCE), \
W("תנועה",            0.45, 3, EMO_RESONANCE), \
W("הברה",             0.45, 3, EMO_RESONANCE), \
W("בית",              0.55, 1, EMO_RESONANCE), \
W("חרוז",             0.50, 2, EMO_RESONANCE), \
W("כתב יד",           0.55, 3, EMO_JULIA), \
W("תרגום",            0.50, 2, EMO_JULIA), \
W("דיו",              0.45, 1, EMO_VOID), \
W("אלפבית",           0.45, 3, EMO_RESONANCE), \
W("דקדוק",            0.50, 3, EMO_RESONANCE), \
W("תחביר",            0.55, 3, EMO_RESONANCE), \
W("שורש",             0.60, 2, EMO_RESONANCE), \
W("פיסוק",            0.40, 2, EMO_VOID), \
W("משל",              0.50, 2, EMO_RESONANCE), \
W("קינה",             0.60, 2, EMO_GRIEF), \
W("מליצה",            0.45, 3, EMO_VOID), \
W("פסוק",             0.55, 2, EMO_RESONANCE), \
/* === DOMESTIC — ביתי === */ \
W("תקרה",             0.40, 3, EMO_VOID), \
W("אדן חלון",         0.40, 3, EMO_JULIA), \
W("רדיאטור",          0.35, 4, EMO_VOID), \
W("מסדרון",           0.40, 3, EMO_VOID), \
W("מנורה",            0.35, 3, EMO_VOID), \
W("קרש רצפה",         0.35, 3, EMO_VOID), \
W("ארון",             0.30, 2, EMO_VOID), \
W("מזרן",             0.30, 2, EMO_VOID), \
W("מראה",             0.50, 3, EMO_RESONANCE), \
W("מפתן",             0.45, 2, EMO_VOID), \
W("וילון",            0.40, 2, EMO_VOID), \
W("קומקום",           0.35, 2, EMO_VOID), \
W("שולחן",            0.35, 2, EMO_VOID), \
W("סיר",              0.30, 1, EMO_VOID), \
W("כיור",             0.35, 2, EMO_VOID), \
W("מפתח",             0.45, 2, EMO_JULIA), \
W("מנעול",            0.45, 2, EMO_VOID), \
W("ציר דלת",          0.35, 3, EMO_VOID), \
W("תריס",             0.35, 2, EMO_VOID), \
W("כרית",             0.30, 2, EMO_TENDERNESS), \
/* === NATURE — טבע === */ \
W("גיר",              0.45, 1, EMO_VOID), \
W("בזלת",             0.50, 2, EMO_VOID), \
W("משקע",             0.40, 2, EMO_VOID), \
W("שחיקה",            0.45, 3, EMO_VOID), \
W("ערפל",             0.35, 2, EMO_VOID), \
W("אזוב",             0.30, 2, EMO_VOID), \
W("צור",              0.50, 1, EMO_VOID), \
W("חול",              0.35, 1, EMO_VOID), \
W("טחב",              0.30, 2, EMO_VOID), \
W("חרסית",            0.45, 2, EMO_VOID), \
W("עפר",              0.40, 2, EMO_VOID), \
W("סלע",              0.50, 2, EMO_VOID), \
W("חלמיש",            0.55, 2, EMO_VOID), \
W("כפור",             0.40, 2, EMO_VOID), \
W("ברד",              0.45, 2, EMO_TRAUMA), \
W("עלה",              0.25, 2, EMO_VOID), \
W("אדמה",             0.50, 3, EMO_RESONANCE), \
/* === LIGHT WORDS — for contrast === */ \
W("אבק",              0.30, 2, EMO_VOID), \
W("מלח",              0.35, 2, EMO_VOID), \
W("עצם",              0.55, 2, EMO_TRAUMA), \
W("אפר",              0.45, 2, EMO_VOID), \
W("חלודה",            0.40, 3, EMO_VOID), \
W("שעווה",            0.30, 3, EMO_VOID), \
W("פחם",              0.40, 2, EMO_VOID), \
W("עופרת",            0.55, 3, EMO_VOID), \
W("פשתן",             0.35, 2, EMO_VOID), \
W("צמר",              0.30, 2, EMO_TENDERNESS), \
/* === BIBLICAL HEAVY — כבדים מקראיים === */ \
W("גאולה",            0.75, 3, EMO_RESONANCE), \
W("נבואה",            0.65, 3, EMO_RESONANCE), \
W("גילוי",            0.60, 2, EMO_RESONANCE), \
W("כפרה",             0.60, 3, EMO_TRAUMA), \
W("שואה",             0.90, 2, EMO_TRAUMA), \
W("תשובה",            0.55, 3, EMO_RESONANCE), \
W("צדק",              0.55, 2, EMO_RESONANCE), \
W("משפט",             0.55, 2, EMO_VOID), \
W("עדות",             0.50, 2, EMO_RESONANCE), \
W("ברית",             0.60, 2, EMO_RESONANCE), \
W("קרבן",             0.65, 2, EMO_TRAUMA), \
W("מגפה",             0.70, 3, EMO_TRAUMA), \
W("מבול",             0.75, 2, EMO_TRAUMA), \
W("עקדה",             0.80, 3, EMO_TRAUMA), \
W("חטא",              0.60, 2, EMO_TRAUMA), \
W("תפילה",            0.55, 3, EMO_RESONANCE), \
W("קדושה",            0.60, 3, EMO_RESONANCE), \
W("חסד",              0.55, 2, EMO_TENDERNESS), \
W("משיח",             0.70, 2, EMO_RESONANCE), \
W("תורה",             0.60, 2, EMO_RESONANCE), \
W("מצווה",            0.50, 3, EMO_RESONANCE), \
W("עגלה",             0.45, 3, EMO_VOID), \
W("מרכבה",            0.65, 3, EMO_RESONANCE), \
W("כרוב",             0.55, 2, EMO_RESONANCE), \
W("שכינה",            0.70, 3, EMO_RESONANCE), \
/* === VERBS — heavy === */ \
W("להתפורר",          0.60, 4, EMO_TRAUMA), \
W("להתאבן",           0.55, 4, EMO_VOID), \
W("להחריב",           0.65, 3, EMO_TRAUMA), \
W("לגלות",            0.50, 3, EMO_JULIA), \
W("להתגבש",           0.50, 4, EMO_RESONANCE), \
W("להתאדות",          0.45, 4, EMO_VOID), \
W("לזכור",            0.55, 3, EMO_JULIA), \
W("לשכוח",            0.55, 3, EMO_VOID), \
W("לנטוש",            0.60, 3, EMO_JULIA), \
W("לדעוך",            0.50, 3, EMO_VOID), \
W("להתבונן",          0.45, 4, EMO_RESONANCE), \
W("לקפוא",            0.50, 3, EMO_VOID), \
W("להשמיד",           0.70, 3, EMO_TRAUMA), \
W("לחלחל",            0.50, 3, EMO_VOID), \
W("לשחוק",            0.50, 2, EMO_VOID), \
W("להתרסק",           0.65, 4, EMO_TRAUMA), \
W("לגהק",             0.40, 3, EMO_VOID), \
W("לנשום",            0.40, 3, EMO_RESONANCE), \
W("להיסדק",           0.55, 4, EMO_TRAUMA), \
W("לחרוץ",            0.55, 3, EMO_VOID), \
W("להחלים",           0.45, 3, EMO_JOY), \
W("לכרוע",            0.55, 3, EMO_TRAUMA), \
W("למשש",             0.40, 3, EMO_TENDERNESS), \
W("להרהר",            0.45, 3, EMO_RESONANCE), \
W("לחשוק",            0.55, 3, EMO_DESIRE), \
W("לקנא",             0.55, 3, EMO_RAGE), \
W("לרעוד",            0.50, 3, EMO_TRAUMA), \
W("לקלף",             0.45, 3, EMO_VOID), \
W("לתפור",            0.40, 3, EMO_TENDERNESS), \
W("להצטלק",           0.55, 4, EMO_TRAUMA), \
W("להתפלל",           0.50, 4, EMO_RESONANCE), \
W("לחפור",            0.50, 3, EMO_VOID), \
/* === EMOTIONAL CORE — גרעין רגשי === */ \
W("תשוקה",            0.70, 3, EMO_DESIRE), \
W("חמלה",             0.55, 3, EMO_TENDERNESS), \
W("בוז",              0.60, 1, EMO_RAGE), \
W("זעם",              0.75, 2, EMO_RAGE), \
W("חימה",             0.70, 2, EMO_RAGE), \
W("עלבון",            0.60, 2, EMO_RAGE), \
W("נחמה",             0.55, 3, EMO_TENDERNESS), \
W("ליטוף",            0.40, 2, EMO_TENDERNESS), \
W("חיבוק",            0.45, 2, EMO_TENDERNESS), \
W("חרטה",             0.65, 3, EMO_GRIEF), \
W("אבל",              0.75, 2, EMO_GRIEF), \
W("אשמה",             0.65, 3, EMO_GRIEF), \
W("שמחה",             0.40, 3, EMO_JOY), \
W("עונג",             0.45, 2, EMO_JOY), \
W("רוגע",             0.35, 2, EMO_JOY), \
W("צחוק",             0.35, 2, EMO_JOY), \
W("דאגה",             0.55, 3, EMO_GRIEF), \
W("חרפה",             0.70, 3, EMO_RAGE), \
W("קנאה",             0.60, 3, EMO_RAGE), \
/* === MISC HEAVY — כבדים שונים === */ \
W("ממשלה",            0.55, 3, EMO_VOID), \
W("אוכלוסייה",        0.50, 5, EMO_VOID), \
W("צילום",            0.50, 2, EMO_JULIA), \
W("סיגריה",           0.40, 4, EMO_VOID), \
W("קטר",              0.50, 2, EMO_VOID), \
W("כספית",            0.55, 3, EMO_RESONANCE), \
W("ברומטר",           0.45, 3, EMO_RESONANCE), \
W("חמצן",             0.40, 2, EMO_RESONANCE), \
W("מבוך",             0.65, 2, EMO_RESONANCE), \
W("ספרייה",           0.55, 3, EMO_RESONANCE), \
W("אנציקלופדיה",      0.50, 6, EMO_RESONANCE), \
W("פסיפס",            0.50, 3, EMO_VOID), \
W("ביורוקרטיה",       0.55, 5, EMO_VOID), \
W("סוברניות",         0.60, 4, EMO_VOID), \
W("טרנספורמציה",      0.60, 5, EMO_RESONANCE), \
W("קונסטלציה",        0.55, 4, EMO_RESONANCE), \
W("פרגמנט",           0.50, 3, EMO_VOID), \
W("מטוטלת",           0.50, 4, EMO_RESONANCE), \
W("פטיפון",           0.40, 3, EMO_JULIA), \
W("מכתב",             0.50, 2, EMO_JULIA), \
W("מברק",             0.50, 2, EMO_JULIA), \
W("דרכון",            0.50, 2, EMO_JULIA), \
W("בול דואר",         0.35, 3, EMO_JULIA), \
W("מכונת כתיבה",      0.45, 5, EMO_JULIA), \
W("עט",               0.35, 1, EMO_VOID), \
W("נייר",             0.30, 2, EMO_VOID), \
W("גלויה",            0.40, 3, EMO_JULIA), \
W("מדים",             0.45, 2, EMO_VOID), \
W("צנזורה",           0.55, 3, EMO_VOID), \
W("פרופיל",           0.45, 2, EMO_VOID), \
W("מגדלור",           0.50, 3, EMO_JULIA), \
W("רכבת",             0.45, 2, EMO_JULIA), \
W("פסים",             0.40, 2, EMO_VOID), \
W("ציפור",            0.35, 2, EMO_TENDERNESS), \
W("עורב",             0.45, 2, EMO_VOID), \
/* === AMICHAI / MODERN — עמיחי / מודרני === */ \
W("גשם",              0.40, 2, EMO_GRIEF), \
W("צל",               0.35, 1, EMO_VOID), \
W("שער",              0.45, 2, EMO_VOID), \
W("חצר",              0.40, 2, EMO_JULIA), \
W("סימטה",            0.40, 3, EMO_JULIA), \
W("שלט",              0.35, 2, EMO_VOID), \
W("סדק",              0.45, 2, EMO_TRAUMA), \
W("טלאי",             0.35, 2, EMO_TENDERNESS), \
W("מזוודה",           0.50, 4, EMO_JULIA), \
W("כביסה",            0.30, 3, EMO_VOID), \
W("חלון",             0.40, 2, EMO_JULIA), \
W("מרפסת",            0.40, 3, EMO_JULIA), \
W("אוטובוס",          0.35, 4, EMO_VOID), \
W("בית קברות",        0.65, 4, EMO_GRIEF), \
W("מצבה",             0.60, 3, EMO_GRIEF), \
W("פנס רחוב",         0.35, 3, EMO_JULIA), \
/* === FUNCTION WORDS — heavy only === */ \
W("לעולם לא",         0.55, 4, EMO_VOID), \
W("בשום מקום",         0.50, 3, EMO_VOID), \
W("דרך",              0.30, 2, EMO_VOID), \
W("למרות",            0.35, 2, EMO_VOID), \
W("בתוך",             0.25, 2, EMO_VOID), \
W("בין",              0.25, 1, EMO_VOID), \
W("לקראת",            0.30, 2, EMO_JULIA), \
W("מעבר",             0.35, 2, EMO_JULIA), \
W("מתחת",             0.30, 2, EMO_VOID), \
W("לאורך",            0.30, 2, EMO_VOID), \
W("אף פעם",           0.45, 3, EMO_VOID), \
W("תמיד",             0.35, 2, EMO_VOID), \
W("כבר",              0.25, 2, EMO_VOID), \
W("עדיין",            0.30, 2, EMO_VOID), \
W("מאז",              0.30, 2, EMO_VOID), \
W("בטרם",             0.35, 2, EMO_VOID), \
/* === IMPERIAL / POLITICAL — אימפריאלי === */ \
W("קיסר",             0.70, 2, EMO_VOID), \
W("כתר",              0.60, 2, EMO_VOID), \
W("שושלת",            0.65, 3, EMO_VOID), \
W("פרובינציה",        0.55, 4, EMO_VOID), \
W("גזירה",            0.65, 3, EMO_TRAUMA), \
W("דיכוי",            0.70, 2, EMO_RAGE), \
W("עריצות",           0.75, 3, EMO_RAGE), \
W("מנשר",             0.50, 2, EMO_VOID), \
W("מהפכה",            0.65, 3, EMO_RAGE), \
W("גרדום",            0.75, 2, EMO_TRAUMA), \
/* === SOUNDS & SENSES — צלילים === */ \
W("דממה",             0.60, 3, EMO_VOID), \
W("הד",               0.50, 1, EMO_RESONANCE), \
W("צלצול",            0.40, 2, EMO_RESONANCE), \
W("לחישה",            0.45, 3, EMO_TENDERNESS), \
W("יללה",             0.65, 3, EMO_GRIEF), \
W("נאקה",             0.55, 3, EMO_TRAUMA), \
W("נשימה",            0.45, 3, EMO_RESONANCE), \
W("ריח",              0.40, 1, EMO_RESONANCE), \
W("מגע",              0.45, 2, EMO_TENDERNESS), \
W("טעם",              0.40, 2, EMO_RESONANCE), \
W("צליל",             0.45, 2, EMO_RESONANCE), \
W("רעש",              0.50, 1, EMO_VOID), \
/* === EVERYDAY — שפת היומיום (אמיחי) === */ \
W("קפה",              0.25, 2, EMO_VOID), \
W("רמזור",            0.30, 2, EMO_VOID), \
W("מדרכה",            0.25, 3, EMO_VOID), \
W("חנייה",            0.25, 3, EMO_VOID), \
W("שקית",             0.20, 2, EMO_VOID), \
W("ברז",              0.25, 2, EMO_VOID), \
W("מכולת",            0.25, 3, EMO_VOID), \
W("תחנה",             0.30, 3, EMO_JULIA), \
W("מטריה",            0.25, 3, EMO_VOID), \
W("סנדל",             0.20, 2, EMO_VOID), \
W("גפרור",            0.25, 2, EMO_VOID), \
W("פחית",             0.20, 2, EMO_VOID), \
W("שעון יד",          0.30, 3, EMO_JULIA), \
W("משקפיים",          0.30, 3, EMO_VOID), \
W("ארנק",             0.25, 2, EMO_VOID), \
W("טלפון",            0.30, 2, EMO_VOID), \
W("עיתון",            0.30, 2, EMO_VOID), \
W("מטבע",             0.25, 2, EMO_VOID), \
W("סבון",             0.20, 2, EMO_VOID), \
W("מגבת",             0.20, 2, EMO_VOID), \
W("צלחת",             0.20, 2, EMO_VOID), \
W("כוס",              0.20, 1, EMO_VOID), \
W("כפית",             0.20, 2, EMO_VOID), \
W("חשבון",            0.30, 2, EMO_VOID), \
W("תור",              0.25, 1, EMO_VOID), \
W("כרטיס",            0.25, 2, EMO_VOID), \
W("מעטפה",            0.30, 3, EMO_JULIA), \
W("קופסה",            0.25, 3, EMO_VOID), \
/* === BODY (everyday, not medical) — גוף יומיומי === */ \
W("ברך",              0.35, 2, EMO_TRAUMA), \
W("עקב",              0.35, 2, EMO_TRAUMA), \
W("ציפורן",           0.30, 3, EMO_VOID), \
W("זקן",              0.35, 2, EMO_VOID), \
W("קמט",              0.40, 2, EMO_GRIEF), \
W("כף יד",            0.40, 3, EMO_TENDERNESS), \
W("שפתיים",           0.40, 3, EMO_DESIRE), \
W("עפעף",             0.35, 2, EMO_TENDERNESS), \
W("גב",               0.40, 1, EMO_TRAUMA), \
W("חזה",              0.45, 2, EMO_TRAUMA), \
W("אגודל",            0.30, 2, EMO_TENDERNESS), \
W("צוואר",            0.40, 2, EMO_TRAUMA), \
W("זיעה",             0.30, 2, EMO_VOID), \
W("דמעה",             0.50, 2, EMO_GRIEF), \
W("שריר",             0.40, 2, EMO_TRAUMA), \
/* === AMICHAI OBJECTS — חפצי עמיחי === */ \
W("תיק",              0.25, 1, EMO_VOID), \
W("דלת",              0.35, 2, EMO_JULIA), \
W("גדר",              0.30, 2, EMO_VOID), \
W("ספסל",             0.30, 2, EMO_JULIA), \
W("שולחן כתיבה",      0.35, 4, EMO_JULIA), \
W("מסגרת",            0.35, 3, EMO_VOID), \
W("מסמר",             0.30, 2, EMO_VOID), \
W("חבל",              0.30, 2, EMO_TRAUMA), \
W("חבל כביסה",        0.25, 4, EMO_JULIA), \
W("עגלת ילדים",       0.30, 4, EMO_TENDERNESS), \
W("טנק",              0.55, 1, EMO_TRAUMA), \
W("פצע",              0.55, 2, EMO_TRAUMA), \
W("תחבושת",           0.40, 3, EMO_TRAUMA), \
W("מפה גיאוגרפית",    0.40, 6, EMO_JULIA), \
W("צלחת אוכל",        0.20, 4, EMO_VOID), \
/* === EMOTIONS (colloquial) — רגשות יומיומיים === */ \
W("עצוב",             0.55, 2, EMO_GRIEF), \
W("עצבני",            0.50, 3, EMO_RAGE), \
W("עייף",             0.40, 2, EMO_VOID), \
W("רעב",              0.35, 2, EMO_VOID), \
W("מבולבל",           0.45, 3, EMO_VOID), \
W("גאה",              0.45, 2, EMO_JOY), \
W("מפוחד",            0.55, 3, EMO_TRAUMA), \
W("בודד",             0.60, 2, EMO_JULIA), \
W("מאוכזב",           0.55, 3, EMO_GRIEF), \
W("מרוצה",            0.35, 3, EMO_JOY), \
W("מותש",             0.45, 2, EMO_VOID), \
W("אדיש",             0.50, 2, EMO_VOID), \
/* === VERBS (everyday) — פעלים יומיומיים === */ \
W("לחכות",            0.45, 3, EMO_JULIA), \
W("לחפש",             0.40, 3, EMO_JULIA), \
W("להתגעגע",          0.65, 5, EMO_JULIA), \
W("לבכות",            0.55, 2, EMO_GRIEF), \
W("לצחוק",            0.35, 2, EMO_JOY), \
W("לישון",            0.30, 2, EMO_VOID), \
W("להתעורר",          0.40, 4, EMO_RESONANCE), \
W("לרוץ",             0.35, 2, EMO_VOID), \
W("לשבת",             0.25, 2, EMO_VOID), \
W("לעשן",             0.35, 2, EMO_VOID), \
W("לשתות",            0.30, 2, EMO_VOID), \
W("לאכול",            0.30, 2, EMO_VOID), \
W("לגעת",             0.40, 2, EMO_TENDERNESS), \
W("לנשק",             0.50, 2, EMO_DESIRE), \
W("לסגור",            0.35, 2, EMO_VOID), \
W("לפתוח",            0.35, 2, EMO_RESONANCE), \
W("לתלות",            0.35, 2, EMO_VOID), \
W("לכבס",             0.25, 2, EMO_VOID), \
W("לגהץ",             0.25, 2, EMO_VOID), \
W("להתקלף",           0.45, 4, EMO_TRAUMA), \
W("לספור",            0.35, 2, EMO_VOID), \
W("להמתין",           0.45, 3, EMO_JULIA), \
/* === NATURE (Israeli, not biblical) — טבע ישראלי === */ \
W("ברוש",             0.35, 1, EMO_VOID), \
W("חרוב",             0.35, 2, EMO_VOID), \
W("צבר",              0.40, 2, EMO_RESONANCE), \
W("חמסין",            0.45, 2, EMO_TRAUMA), \
W("שרב",              0.40, 2, EMO_VOID), \
W("זית",              0.35, 1, EMO_RESONANCE), \
W("תאנה",             0.35, 2, EMO_RESONANCE), \
W("בוגנוויליה",       0.30, 5, EMO_JULIA), \
W("פרג",              0.25, 2, EMO_TENDERNESS), \
W("אקליפטוס",         0.30, 4, EMO_VOID), \
W("ואדי",             0.40, 2, EMO_VOID), \
W("חולות",            0.35, 2, EMO_VOID), \
W("כרמל",             0.45, 2, EMO_RESONANCE), \
W("נגב",              0.45, 2, EMO_VOID), \
W("ים המלח",          0.50, 3, EMO_VOID), \
/* === PLACES / URBAN — מקומות עירוניים === */ \
W("שוק",              0.35, 1, EMO_RESONANCE), \
W("בית קפה",          0.30, 3, EMO_JULIA), \
W("תחנת אוטובוס",     0.30, 5, EMO_VOID), \
W("סופרמרקט",         0.25, 4, EMO_VOID), \
W("בנק",              0.30, 1, EMO_VOID), \
W("דואר",             0.30, 2, EMO_JULIA), \
W("בית חולים",        0.50, 4, EMO_TRAUMA), \
W("גן ילדים",         0.30, 4, EMO_TENDERNESS), \
W("מגרש",             0.30, 2, EMO_VOID), \
W("חניון",            0.25, 2, EMO_VOID), \
W("סמטה",             0.35, 2, EMO_JULIA), \
/* === WAR & PEACE (Amichai's terrain) — מלחמה ושלום === */ \
W("טייס",             0.45, 2, EMO_TRAUMA), \
W("פגז",              0.55, 2, EMO_TRAUMA), \
W("מקלחת",            0.25, 3, EMO_VOID), \
W("חייל",             0.55, 2, EMO_TRAUMA), \
W("צניחה",            0.50, 3, EMO_TRAUMA), \
W("תותח",             0.55, 2, EMO_TRAUMA), \
W("שלום",             0.55, 2, EMO_RESONANCE), \
W("פליט",             0.60, 2, EMO_JULIA), \
W("מחסום",            0.50, 2, EMO_TRAUMA), \
W("פיוס",             0.45, 2, EMO_TENDERNESS), \
W("רסיס",             0.50, 2, EMO_TRAUMA), \
/* === FOOD & DRINK (body of the everyday) — אוכל === */ \
W("לחם",              0.35, 2, EMO_RESONANCE), \
W("מים",              0.30, 1, EMO_RESONANCE), \
W("יין",              0.40, 1, EMO_RESONANCE), \
W("ביצה",             0.25, 2, EMO_VOID), \
W("שמן זית",          0.30, 3, EMO_RESONANCE), \
W("חלב",              0.30, 2, EMO_TENDERNESS), \
W("סוכר",             0.25, 2, EMO_VOID), \
W("פיתה",             0.25, 2, EMO_VOID), \
W("חומוס",            0.25, 2, EMO_VOID), \
W("רימון",            0.40, 2, EMO_RESONANCE), \
/* === FABRIC OF LIFE — אריג חיים === */ \
W("חתונה",            0.50, 3, EMO_JULIA), \
W("לוויה",            0.65, 3, EMO_GRIEF), \
W("ברית מילה",        0.55, 3, EMO_RESONANCE), \
W("שבת",              0.50, 2, EMO_RESONANCE), \
W("סליחה",            0.45, 3, EMO_TENDERNESS), \
W("תודה",             0.30, 2, EMO_TENDERNESS), \
W("שכן",              0.30, 2, EMO_VOID), \
W("חדר מדרגות",       0.30, 4, EMO_VOID), \
W("גג",               0.30, 1, EMO_JULIA), \
W("אנטנה",            0.25, 3, EMO_VOID), \
W("כביש",             0.30, 2, EMO_VOID), \
/* === GOLDBERG — European landscapes in Israel === */ \
W("אורן",             0.40, 2, EMO_JULIA), \
W("ערמון",            0.40, 2, EMO_JULIA), \
W("שלג",              0.45, 2, EMO_JULIA), \
W("גשר",              0.40, 2, EMO_JULIA), \
W("נהר",              0.40, 2, EMO_JULIA), \
W("אגם",              0.40, 2, EMO_JULIA), \
W("שדרה",             0.35, 3, EMO_JULIA), \
W("לילך",             0.35, 2, EMO_JULIA), \
W("מגדל",             0.45, 2, EMO_VOID), \
W("שביל",             0.30, 2, EMO_JULIA), \
W("גבעה",             0.35, 3, EMO_JULIA), \
W("מעיין",            0.35, 2, EMO_RESONANCE), \
W("אגמון",            0.30, 3, EMO_VOID), \
W("קרחת יער",         0.35, 4, EMO_JULIA), \
W("עמק",              0.40, 2, EMO_JULIA), \
W("יער",              0.35, 2, EMO_JULIA), \
W("מפל",              0.40, 2, EMO_RESONANCE), \
W("אפלה",            0.50, 3, EMO_VOID), \
W("רכס",              0.40, 2, EMO_VOID), \
W("שדה",              0.30, 2, EMO_JULIA), \
W("פלטרין",           0.40, 3, EMO_JULIA), \
W("דבקון",            0.30, 2, EMO_JULIA), \
W("אשור",             0.35, 2, EMO_JULIA), \
W("מזח",              0.35, 1, EMO_JULIA), \
W("פסגה",             0.40, 3, EMO_RESONANCE), \
/* === RAVIKOVITCH — fragility === */ \
W("זכוכית",           0.60, 3, EMO_TRAUMA), \
W("שבר",              0.55, 2, EMO_TRAUMA), \
W("קליפה",            0.40, 3, EMO_TRAUMA), \
W("שריטה",            0.45, 3, EMO_TRAUMA), \
W("חתך",              0.50, 2, EMO_TRAUMA), \
W("רסק",              0.55, 2, EMO_TRAUMA), \
W("שבריר",            0.45, 3, EMO_TRAUMA), \
W("בועה",             0.30, 3, EMO_TENDERNESS), \
W("קרע",              0.55, 2, EMO_TRAUMA), \
W("צלקת",             0.50, 3, EMO_TRAUMA), \
W("חבורה",            0.45, 3, EMO_TRAUMA), \
W("נפילה",            0.55, 3, EMO_TRAUMA), \
W("התמוטטות",         0.70, 4, EMO_TRAUMA), \
W("פגיעות",           0.55, 3, EMO_TRAUMA), \
W("שקיפות",           0.40, 3, EMO_RESONANCE), \
W("דקיקות",           0.35, 4, EMO_TENDERNESS), \
W("קלישות",           0.40, 3, EMO_TRAUMA), \
W("פריכות",           0.35, 3, EMO_TRAUMA), \
W("חד",               0.45, 1, EMO_TRAUMA), \
W("שפיץ",             0.40, 1, EMO_TRAUMA), \
W("להתנפץ",           0.60, 4, EMO_TRAUMA), \
W("להישבר",           0.55, 4, EMO_TRAUMA), \
W("לסדוק",            0.50, 3, EMO_TRAUMA), \
W("להתפרק",           0.55, 4, EMO_TRAUMA), \
W("לנפץ",             0.55, 3, EMO_TRAUMA), \
/* === DOMESTIC (expanded) — ביתי מורחב === */ \
W("מיטה",             0.30, 2, EMO_TENDERNESS), \
W("שמיכה",            0.30, 3, EMO_TENDERNESS), \
W("מברשת",            0.25, 3, EMO_VOID), \
W("מחבת",             0.25, 2, EMO_VOID), \
W("מגש",              0.20, 2, EMO_VOID), \
W("מפית",             0.20, 3, EMO_VOID), \
W("סירים",            0.25, 2, EMO_VOID), \
W("מטאטא",            0.25, 4, EMO_VOID), \
W("פח אשפה",          0.20, 3, EMO_VOID), \
W("כתם",              0.30, 2, EMO_VOID), \
W("נורה",             0.25, 2, EMO_VOID), \
W("שטיח",             0.30, 2, EMO_VOID), \
W("אגרטל",            0.30, 3, EMO_JULIA), \
W("פרח",              0.25, 2, EMO_TENDERNESS), \
W("עציץ",             0.25, 2, EMO_VOID), \
W("דוד חימום",         0.30, 3, EMO_VOID), \
W("ברז מטפטף",        0.25, 4, EMO_VOID), \
W("סדין",             0.25, 2, EMO_TENDERNESS), \
/* === CHILDREN / BIRTH — ילדים ולידה === */ \
W("תינוק",            0.50, 2, EMO_TENDERNESS), \
W("עריסה",            0.40, 3, EMO_TENDERNESS), \
W("חיתול",            0.30, 2, EMO_TENDERNESS), \
W("שליה",             0.65, 2, EMO_TRAUMA), \
W("לידה",             0.70, 3, EMO_RESONANCE), \
W("צירים",            0.60, 2, EMO_TRAUMA), \
W("בכי",              0.50, 2, EMO_GRIEF), \
W("חלב אם",           0.40, 3, EMO_TENDERNESS), \
W("הנקה",             0.40, 3, EMO_TENDERNESS), \
W("שפיר",             0.55, 2, EMO_RESONANCE), \
W("חבל טבור",          0.50, 3, EMO_RESONANCE), \
W("ערש",              0.35, 1, EMO_TENDERNESS), \
W("שיר ערש",          0.35, 2, EMO_TENDERNESS), \
W("רחם",              0.60, 2, EMO_RESONANCE), \
W("פג",               0.55, 1, EMO_TRAUMA), \
W("צמיחה",            0.40, 3, EMO_RESONANCE), \
W("חום גוף",          0.35, 2, EMO_TENDERNESS), \
W("אצבעון",           0.30, 3, EMO_TENDERNESS), \
/* === WEATHER — מזג אוויר === */ \
W("שמש",              0.35, 2, EMO_RESONANCE), \
W("עננה",             0.30, 3, EMO_VOID), \
W("סופה",             0.55, 2, EMO_TRAUMA), \
W("ברק",              0.55, 2, EMO_TRAUMA), \
W("רעם",              0.55, 2, EMO_TRAUMA), \
W("טל",               0.25, 1, EMO_TENDERNESS), \
W("רוח",              0.35, 2, EMO_RESONANCE), \
W("קשת בענן",         0.35, 4, EMO_JOY), \
W("שטף",              0.50, 1, EMO_TRAUMA), \
W("בצורת",            0.55, 3, EMO_TRAUMA), \
W("אדים",             0.25, 2, EMO_VOID), \
W("לחות",             0.30, 2, EMO_VOID), \
W("זריחה",            0.35, 3, EMO_RESONANCE), \
W("עשן",              0.35, 2, EMO_VOID), \
W("אובך",             0.35, 2, EMO_VOID), \
/* === ISRAELI NATURE (expanded) — טבע ישראלי מורחב === */ \
W("תפוז",             0.30, 2, EMO_JOY), \
W("שקד",              0.35, 2, EMO_RESONANCE), \
W("יסמין",            0.35, 2, EMO_TENDERNESS), \
W("כלנית",            0.35, 3, EMO_TENDERNESS), \
W("רקפת",             0.35, 3, EMO_TENDERNESS), \
W("נרקיס",            0.30, 2, EMO_TENDERNESS), \
W("צלף",              0.30, 2, EMO_VOID), \
W("חצב",              0.35, 2, EMO_VOID), \
W("דקל",              0.30, 2, EMO_VOID), \
W("תמר",              0.30, 2, EMO_RESONANCE), \
W("סברס",             0.35, 2, EMO_RESONANCE), \
W("לבנה",             0.35, 3, EMO_JULIA), \
W("אלון",             0.35, 2, EMO_RESONANCE), \
W("חרצית",            0.30, 2, EMO_VOID), \
W("פיקוס",            0.25, 2, EMO_VOID), \
/* === TEXTURE / SOUND — מרקם וצליל === */ \
W("חלק",              0.25, 2, EMO_VOID), \
W("מחוספס",           0.35, 3, EMO_VOID), \
W("דביק",             0.30, 2, EMO_VOID), \
W("רטוב",             0.30, 2, EMO_VOID), \
W("יבש",              0.30, 2, EMO_VOID), \
W("שקט",              0.35, 2, EMO_VOID), \
W("רך",               0.25, 1, EMO_TENDERNESS), \
W("קשה",              0.40, 2, EMO_VOID), \
W("צורם",             0.45, 2, EMO_TRAUMA), \
W("חריקה",            0.40, 3, EMO_TRAUMA), \
W("רישרוש",           0.30, 3, EMO_TENDERNESS), \
W("חלול",             0.35, 2, EMO_VOID), \
W("עמום",             0.35, 2, EMO_VOID), \
W("בהיר",             0.30, 2, EMO_RESONANCE), \
W("עכור",             0.35, 2, EMO_VOID), \
W("צלול",             0.30, 2, EMO_RESONANCE), \
W("מטושטש",           0.35, 3, EMO_VOID), \
W("זוהר",             0.40, 2, EMO_RESONANCE), \
/* === GOLDBERG VERBS — פעלים של גולדברג === */ \
W("להאפיל",           0.45, 3, EMO_VOID), \
W("לנשור",            0.40, 3, EMO_GRIEF), \
W("לנבול",            0.45, 3, EMO_GRIEF), \
W("להתייבש",          0.40, 4, EMO_VOID), \
W("להתכסות",          0.35, 4, EMO_VOID), \
W("להתערפל",          0.40, 4, EMO_VOID), \
W("להשיר",            0.40, 3, EMO_GRIEF), \
W("לגעגע",            0.50, 3, EMO_JULIA), \
W("להאדים",           0.35, 3, EMO_TENDERNESS), \
/* === RAVIKOVITCH VERBS — פעלים של רביקוביץ === */ \
W("להזדעזע",          0.50, 4, EMO_TRAUMA), \
W("לדמם",             0.55, 3, EMO_TRAUMA), \
W("לחבוש",            0.35, 3, EMO_TENDERNESS), \
W("להתקפל",           0.45, 4, EMO_TRAUMA), \
W("לכאוב",            0.55, 3, EMO_GRIEF), \
W("להתמוסס",          0.45, 4, EMO_VOID), \
W("להתפוצץ",          0.60, 4, EMO_TRAUMA), \
W("לקרוע",            0.50, 3, EMO_TRAUMA), \
W("להתפרר",           0.50, 4, EMO_VOID), \
/* === RHYME FAMILIES — משפחות חרוז === */ \
/* -et/-at rhymes: מוות, שבת, שקט */ \
W("דעת",              0.55, 2, EMO_RESONANCE), \
W("עת",               0.45, 1, EMO_VOID), \
W("אמת",              0.60, 2, EMO_RESONANCE), \
W("דלת",              0.35, 2, EMO_JULIA), \
W("רשת",              0.40, 2, EMO_VOID), \
W("כתבת",             0.35, 3, EMO_JULIA), \
W("גחלת",             0.45, 3, EMO_TRAUMA), \
W("תמצית",            0.50, 3, EMO_RESONANCE), \
/* -an rhymes: חורבן, זמן, קרבן */ \
W("אמן",              0.55, 2, EMO_RESONANCE), \
W("רעיון",            0.50, 3, EMO_RESONANCE), \
W("ביטחון",           0.55, 3, EMO_VOID), \
W("חיסרון",           0.55, 3, EMO_VOID), \
W("עוון",             0.65, 2, EMO_TRAUMA), \
W("פתרון",            0.45, 3, EMO_RESONANCE), \
W("ניצחון",           0.60, 3, EMO_JOY), \
W("תיקון",            0.55, 3, EMO_RESONANCE), \
/* -ut rhymes: גלות, דלות, מלכות */ \
W("דלות",             0.65, 2, EMO_GRIEF), \
W("מלכות",            0.65, 3, EMO_VOID), \
W("שתיקות",           0.55, 3, EMO_VOID), \
W("אכזריות",          0.70, 4, EMO_TRAUMA), \
W("עיוורות",          0.60, 3, EMO_TRAUMA), \
W("גבורות",           0.55, 3, EMO_RESONANCE), \
W("אחדות",            0.50, 3, EMO_RESONANCE), \
W("חירות",            0.60, 3, EMO_RESONANCE), \
/* -om rhymes: תהום, חלום, שלום, יום */ \
W("חלום",             0.55, 2, EMO_RESONANCE), \
W("יום",              0.40, 1, EMO_VOID), \
W("חום",              0.40, 1, EMO_TRAUMA), \
W("עולם",             0.60, 2, EMO_RESONANCE), \
W("אשם",              0.55, 2, EMO_GRIEF), \
W("רחום",             0.45, 2, EMO_TENDERNESS), \
W("תרדמת עולם",       0.55, 4, EMO_VOID), \
/* -ma rhymes: שממה, נשמה, אמא, אדמה */ \
W("נשמה",             0.70, 3, EMO_RESONANCE), \
W("אמא",              0.60, 2, EMO_TENDERNESS), \
W("דמעמה",            0.45, 3, EMO_GRIEF), \
W("מגמה",             0.40, 3, EMO_VOID), \
W("נקמה",             0.65, 3, EMO_RAGE), \
W("תכנית מעומעמה",    0.40, 5, EMO_VOID), \
W("מהומה",            0.50, 4, EMO_RAGE), \
W("תרומה",            0.45, 3, EMO_TENDERNESS), \
/* -on rhymes: חלון, ארון, סלון */ \
W("סלון",             0.35, 2, EMO_VOID), \
W("טלוויזיון",        0.35, 4, EMO_VOID), \
W("שיגעון",           0.60, 3, EMO_TRAUMA), \
W("עיתון",            0.30, 2, EMO_VOID), \
W("ריבון",            0.50, 2, EMO_RESONANCE), \
W("חשבון",            0.30, 2, EMO_VOID), \
/* -ir rhymes: ציר, שיר, עיר */ \
W("שיר",              0.55, 1, EMO_RESONANCE), \
W("עיר",              0.45, 1, EMO_JULIA), \
W("קיר",              0.40, 1, EMO_VOID), \
W("נהיר",             0.40, 2, EMO_RESONANCE), \
W("אסיר",             0.55, 2, EMO_TRAUMA), \
/* -av/-ev rhymes: ערב, כאב, לב */ \
W("לב",               0.55, 1, EMO_RESONANCE), \
W("כאב",              0.65, 2, EMO_TRAUMA), \
W("זהב",              0.45, 2, EMO_RESONANCE), \
W("עשב",              0.30, 2, EMO_VOID), \
W("כוכב",             0.40, 2, EMO_RESONANCE), \
/* -a rhymes: חרדה, חרפה, עקדה */ \
W("תקווה",            0.55, 3, EMO_RESONANCE), \
W("מנוחה",            0.40, 3, EMO_VOID), \
W("ברכה",             0.45, 3, EMO_TENDERNESS), \
W("מכה",              0.50, 2, EMO_TRAUMA), \
W("הלכה",             0.45, 3, EMO_RESONANCE), \
W("תלונה",            0.40, 3, EMO_VOID), \
W("טענה",             0.40, 3, EMO_RAGE), \
W("אהבה",             0.60, 3, EMO_DESIRE), \
/* END */
