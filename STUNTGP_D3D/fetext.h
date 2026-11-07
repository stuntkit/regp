#ifndef FETEXT_H
#define FETEXT_H

int FeCsv_SkipBlankLines(char *text, int *pos);
int FeCsv_IsBlank(char c);
int FeCsv_IsNewline(char c);
int FeCsv_SkipLine(char *text, int *pos);
int FeCsv_ReadField(char *out, char *text, int *pos);
char *FeCsv_Load(char *name);
int FUN_4409c0(char *text, int width, float size, int maxLines);
int FeText_Assign(char *key, char *value, int count);
char *FeText_AddString(char *str);

// Front-end language csv, kept loaded while the front end runs.
extern char *g_6087a0;

#endif /* FETEXT_H */
