#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <ctype.h>
#include <string.h>

#include "ConvertUTF.h"
#include "smutil.h"

#if 0
// 270 included, 1113842 excluded, 0 errors, 14 states, 32 columns, 704 bytes.
//
#define DIGIT_START_STATE (0)
#define DIGIT_ISMEMBER_STATE (14)
#define DIGIT_ISNOTMEMBER_STATE (15)

unsigned char digit_itt[256] =
{
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 2, 2, 2, 2, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 7, 8, 9, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 11, 10, 12, 13, 14, 14, 14, 14, 15, 16, 17, 16, 18, 19, 20, 19, 20, 19, 20, 21, 22, 21, 22, 21, 22, 21, 21, 21, 23, 10, 24, 25, 10, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 26, 0, 27, 0, 0, 0, 0, 28, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

unsigned char digit_stt[14][32] =
{
    {  15,  14,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,   1,   2,   3,   6,   9,  10},
    {  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  14,  14,  14,  14,  14,  14,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15},
    {  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  14,  14,  14,  15,  15,  15,  15,  15,  15,  15,  15},
    {  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,   4,  15,   4,   4,  15,   4,  15,   4,   5,   5,   1,  15,  15,  15,  15,  15,  15},
    {  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  14,  14,  14,  14,  14,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15},
    {  15,  15,  15,  15,  15,  15,  15,  14,  14,  14,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15},
    {  15,  15,  15,   7,  15,  15,  15,  15,  15,  15,  15,  15,   1,   5,  15,   8,  15,   5,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15},
    {  15,  15,  14,  14,  14,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15},
    {  15,  15,  15,  15,  14,  14,  14,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15},
    {  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,   5,  15,  15,  15,  15,  15,  15},
    {  15,  15,  15,  15,  15,  15,  15,  11,  15,  15,  15,  12,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15},
    {  15,  15,  15,  15,  15,  15,  15,  15,  15,   1,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15},
    {  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  13,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15},
    {  15,  15,  15,  15,  15,  15,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  15,  15,  15,  15,  15,  15}
};

void VerifyTables(FILE *fp)
{
    fprintf(stderr, "Testing final ITT and STT.\n");
    fseek(fp, 0, SEEK_SET);
    int nextcode = ReadCodePoint(fp);
    int i;
    for (i = 0; i <= UNI_MAX_LEGAL_UTF32; i++)
    {
        bool bMember;
        if (i == nextcode)
        {
            if (!isPrivateUse(i))
            {
                bMember = true;
            }
            else
            {
                bMember = false;
            }

            if (0 <= nextcode)
            {
                nextcode = ReadCodePoint(fp);
            }
        }
        else
        {
            bMember = false;
        }

        UTF32 Source[2];
        Source[0] = i;
        Source[1] = L'\0';
        const UTF32 *pSource = Source;

        UTF8 Target[5];
        UTF8 *pTarget = Target;

        ConversionResult cr;
        cr = ConvertUTF32toUTF8(&pSource, pSource+1, &pTarget, pTarget+sizeof(Target)-1, lenientConversion);

        if (conversionOK == cr)
        {
            int iState = DIGIT_START_STATE;
            UTF8 *p = Target;
            while (  p < pTarget
                  && iState < DIGIT_ISMEMBER_STATE)
            {
                iState = digit_stt[iState][digit_itt[(unsigned char)*p]];
                p++;
            }

            if (  (  DIGIT_ISMEMBER_STATE == iState
                  && !bMember)
               || (  DIGIT_ISNOTMEMBER_STATE == iState
                  && bMember))
            {
                printf("Input Translation Table and State Transition Table do not work.\n");
                exit(0);
            }
        }
    }
}
#endif

StateMachine sm;

int DecodeCodePoint(char *p)
{
    if (!isxdigit(*p))
    {
        // The first field was empty or contained invalid data.
        //
        return -1;
    }

    int codepoint = 0;
    while (isxdigit(*p))
    {
        char ch = *p;
        if (  ch <= '9'
           && '0' <= ch)
        {
            ch = ch - '0';
        }
        else if (  ch <= 'F'
                && 'A' <= ch)
        {
            ch = ch - 'A' + 10;
        }
        else if (  ch <= 'f'
                && 'a' <= ch)
        {
            ch = ch - 'a' + 10;
        }
        else
        {
            return -1;
        }
        codepoint = (codepoint << 4) + ch;
        p++;
    }
    return codepoint;
}

int ReadCodePoint(FILE *fp, int *pValue)
{
    char buffer[1024];
    char *p;

    for (;;)
    {
        if (fgets(buffer, sizeof(buffer), fp) == NULL)
        {
            *pValue = -1;
            return -1;
        }
        p = strchr(buffer, '#');
        if (NULL != p)
        {
            // Ignore comment.
            //
            *p = '\0';
        }
        p = buffer;

        // Skip leading whitespace.
        //
        while (isspace(*p))
        {
            p++;
        }
    
        // Look for end of string or comment.
        //
        if ('\0' == *p)
        {
            // We skip blank lines.
            //
            continue;
        }
        break;
    }

#define MAX_FIELDS 15

    int   nFields = 0;
    char *aFields[MAX_FIELDS];
    for (nFields = 0; nFields < MAX_FIELDS; )
    {
        // Skip leading whitespace.
        //
        while (isspace(*p))
        {
            p++;
        }

        aFields[nFields++] = p;
        char *q = strchr(p, ';');
        if (NULL == q)
        {
            // Trim trailing whitespace.
            //
            size_t i = strlen(p) - 1;
            while (isspace(p[i]))
            {
                p[i] = '\0';
            }
            break;
        }
        else
        {
            *q = '\0';
            p = q + 1;

            // Trim trailing whitespace.
            //
            q--;
            while (isspace(*q))
            {
                *q = '\0';
                q--;
            }
        }
    }

    // Field #0 - Code Point
    //
    int codepoint = DecodeCodePoint(aFields[0]);

    // Field #6 - Decimal Digit Property.
    //
    int Value;
    p = aFields[6];
    if (!isdigit(*p))
    {
        Value = -1;
    }
    else
    {
        Value = 0;
        do
        {
            Value = Value * 10 + (*p - '0');
            p++;
        } while (isdigit(*p));
    }

    // Field #12 - Simple Uppercase Mapping.
    //
    int Uppercase = DecodeCodePoint(aFields[12]);

    // Field #13 = Simple Lowercase Mapping.
    //
    int Lowercase = DecodeCodePoint(aFields[13]);

    if (0 <= Value)
    {
        *pValue = Value;
    }
    else
    {
        if (  Uppercase < 0
           && Lowercase < 0)
        {
            *pValue = -1;
        }
        else
        {
            if (Uppercase < 0)
            {
                Uppercase = codepoint;
            }
            if (Lowercase < 0)
            {
                Lowercase = codepoint;
            }

            if (Lowercase == codepoint)
            {
                *pValue = Uppercase - codepoint;
            }
            else
            {
                *pValue = Lowercase - codepoint;
            }
        }
    }
    return codepoint;
}

void TestTable(FILE *fp)
{
    fprintf(stderr, "Testing STT table.\n");
    fseek(fp, 0, SEEK_SET);
    int Value;
    int nextcode = ReadCodePoint(fp, &Value);
    int i;
    for (i = 0; i <= UNI_MAX_LEGAL_UTF32; i++)
    {
        bool bMember;
        if (i == nextcode)
        {
            if (!isPrivateUse(i))
            {
                bMember = true;
            }
            else
            {
                bMember = false;
            }

            if (0 <= nextcode)
            {
                nextcode = ReadCodePoint(fp, &Value);
            }
        }
        else
        {
            bMember = false;
        }

        UTF32 Source[2];
        Source[0] = i;
        Source[1] = L'\0';
        const UTF32 *pSource = Source;

        UTF8 Target[5];
        UTF8 *pTarget = Target;

        ConversionResult cr;
        cr = ConvertUTF32toUTF8(&pSource, pSource+1, &pTarget, pTarget+sizeof(Target)-1, lenientConversion);

        if (conversionOK == cr)
        {
            sm.TestString(Target, pTarget, bMember);
        }
    }
}

void LoadStrings(FILE *fp)
{
    int cIncluded = 0;
    int cExcluded = 0;
    int cErrors   = 0;

    fseek(fp, 0, SEEK_SET);
    int Value;
    int nextcode = ReadCodePoint(fp, &Value);

    int i;
    for (i = 0; i <= UNI_MAX_LEGAL_UTF32; i++)
    {
        bool bMember;
        if (i == nextcode)
        {
            if (!isPrivateUse(i))
            {
                bMember = true;
                cIncluded++;
            }
            else
            {
                bMember = false;
                cExcluded++;
            }

            if (0 <= nextcode)
            {
                nextcode = ReadCodePoint(fp, &Value);
            }
        }
        else
        {
            bMember = false;
            cExcluded++;
        }

        UTF32 Source[2];
        Source[0] = i;
        Source[1] = L'\0';
        const UTF32 *pSource = Source;

        UTF8 Target[5];
        UTF8 *pTarget = Target;

        ConversionResult cr;
        cr = ConvertUTF32toUTF8(&pSource, pSource+1, &pTarget, pTarget+sizeof(Target)-1, lenientConversion);

        if (conversionOK == cr)
        {
            sm.RecordString(Target, pTarget, bMember);
        }
        else
        {
            cErrors++;
        }
    }
    printf("// %d included, %d excluded, %d errors.\n", cIncluded, cExcluded, cErrors);
    fprintf(stderr, "%d included, %d excluded, %d errors.\n", cIncluded, cExcluded, cErrors);
    sm.ReportStatus();
}

void BuildAndOutputTable(FILE *fp, char *UpperPrefix, char *LowerPrefix)
{
    // Construct State Transition Table.
    //
    sm.Init();
    LoadStrings(fp);
    TestTable(fp);
    sm.SetUndefinedStates();
    TestTable(fp);

    // Optimize State Transition Table.
    //
    sm.RemoveAllNonMemberRows();
    TestTable(fp);
    sm.RemoveAllNonMemberRows();
    TestTable(fp);
    sm.RemoveAllNonMemberRows();
    TestTable(fp);
    sm.RemoveDuplicateRows();
    TestTable(fp);
    sm.DetectDuplicateColumns();

    // Output State Transition Table.
    //
    sm.NumberStates();
    sm.OutputTables(UpperPrefix, LowerPrefix);
}

int main(int argc, char *argv[])
{
    char *pPrefix;
    char *pFilename;
    if (argc < 3)
    {
#if 0
        fprintf(stderr, "Usage: %s prefix unicodedata.txt\n", argv[0]);
        exit(0);
#else
        pFilename = "AlphaUpper.txt";
        pPrefix   = "alupp";
#endif
    }
    else
    {
        pPrefix   = argv[1];
        pFilename = argv[2];
    }

    FILE *fp = fopen(pFilename, "rb");
    if (NULL == fp)
    {
        fprintf(stderr, "Cannot open %s\n", pFilename);
        exit(0);
    }

    size_t nPrefix = strlen(pPrefix);
    char *pPrefixLower = new char[nPrefix+1];
    char *pPrefixUpper = new char[nPrefix+1];
    memcpy(pPrefixLower, pPrefix, nPrefix+1);
    memcpy(pPrefixUpper, pPrefix, nPrefix+1);

    size_t i;
    for (i = 0; i < nPrefix; i++)
    {
        if (isupper(pPrefixLower[i]))
        {
            pPrefixLower[i] = static_cast<char>(tolower(pPrefixLower[i]));
        }

        if (islower(pPrefixUpper[i]))
        {
            pPrefixUpper[i] = static_cast<char>(toupper(pPrefixUpper[i]));
        }
    }

    BuildAndOutputTable(fp, pPrefixUpper, pPrefixLower);
    //VerifyTables(fp);

    fclose(fp);
}