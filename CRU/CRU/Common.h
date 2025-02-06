//---------------------------------------------------------------------------
#ifndef CommonH
#define CommonH
//---------------------------------------------------------------------------
#include <vcl.h>

#include <windows.h>
#include <setupapi.h>

#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
//---------------------------------------------------------------------------
#ifndef LLONG_MAX
#define LLONG_MAX			9223372036854775807LL
#endif

#ifndef LLONG_MIN
#define LLONG_MIN			(-LLONG_MAX - 1)
#endif

#define BLANK				INT_MIN
#define INVALID				(INT_MIN + 1)
#define DECIMAL_BLANK		LLONG_MIN
#define DECIMAL_INVALID		(LLONG_MIN + 1)
#define TEXTSIZE			256
//---------------------------------------------------------------------------
bool IsDigit(char);
bool IsHexDigit(char);
bool IsSpace(char);
bool IsUpper(char);
bool IsLower(char);
char ValueToHex(unsigned char);
unsigned char HexToValue(char);
bool DataToHex(const unsigned char *, int, char *, bool = false);
bool HexToData(const char *, unsigned char *, int, bool = false);
bool Trim(char *);
bool ToUpper(char *);
//---------------------------------------------------------------------------
#endif
