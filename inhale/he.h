/* inhale/he.h — Hebrew heavy vocabulary for brodsky.c
 * ~220 words. Biblical + Amichai + architectural/imperial lexicon.
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
/* === NATURE — טבע === */ \
W("גיר",              0.45, 1, EMO_VOID), \
W("בזלת",             0.50, 2, EMO_VOID), \
W("קרחון",            0.50, 2, EMO_VOID), \
W("משקע",             0.40, 2, EMO_VOID), \
W("שחיקה",            0.45, 3, EMO_VOID), \
W("ערפל",             0.35, 2, EMO_VOID), \
W("אזוב",             0.30, 2, EMO_VOID), \
/* === LIGHT WORDS — for contrast === */ \
W("אבק",              0.30, 2, EMO_VOID), \
W("מלח",              0.35, 2, EMO_VOID), \
W("עצם",              0.55, 2, EMO_TRAUMA), \
W("אפר",              0.45, 2, EMO_VOID), \
W("חלודה",            0.40, 3, EMO_VOID), \
W("שעווה",            0.30, 3, EMO_VOID), \
W("גיר",              0.30, 1, EMO_VOID), \
/* === BIBLICAL HEAVY — כבדים מקראיים === */ \
W("גאולה",            0.75, 3, EMO_RESONANCE), \
W("חורבן",            0.85, 2, EMO_TRAUMA), \
W("נבואה",            0.65, 3, EMO_RESONANCE), \
W("גילוי",            0.60, 2, EMO_RESONANCE), \
W("כפרה",             0.60, 3, EMO_TRAUMA), \
W("שואה",             0.90, 2, EMO_TRAUMA), \
W("תשובה",            0.55, 3, EMO_RESONANCE), \
W("צדק",              0.55, 2, EMO_RESONANCE), \
W("משפט",             0.55, 2, EMO_VOID), \
W("עדות",             0.50, 2, EMO_RESONANCE), \
W("ברית",             0.60, 2, EMO_RESONANCE), \
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
/* END */
