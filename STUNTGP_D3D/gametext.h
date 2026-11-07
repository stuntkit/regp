#ifndef GAMETEXT_H
#define GAMETEXT_H

void Scores_Load();
int Scores_Assign(char *key, char *value, int count);
int Scores_Parse(char *str);
void Scores_LoadIfNeeded();
void FUN_445610();
void Gameplay_Load();
int Gameplay_Assign(char *key, char *value, int count);
float Gameplay_Parse(char *str, int *pool);
void Gameplay_LoadIfNeeded();

int Csv_SkipBlankLines(char *text, int *pos);
int Csv_IsBlank(char c);
int Csv_IsNewline(char c);
int Csv_ReadField(char *out, char *text, int *pos);
char *Csv_Load(char *name);
void Text_InitKeys();
void Text_LoadLanguage(int language);
int Text_Assign(char *key, char *value, int count);
char *Text_AddString(char *str);
void FUN_445f80();
extern char *g_6127a0[105];
extern int g_4835e0;

#endif /* GAMETEXT_H */
