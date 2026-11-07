#ifndef GAMETEXT_H
#define GAMETEXT_H

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
#endif /* GAMETEXT_H */
