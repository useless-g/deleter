#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <stddef.h>
#include <Wincrypt.h>

int USDoD522022M_R (char *Filename, FILE* File, size_t* N, int r);
int FILE_open (char *Filename, FILE** File);
int FILE_close (FILE* File);
int flenght (FILE* File, size_t* N);
BYTE KSGPSC (char* p_r);
int main()
{
    int n;
    size_t *N;
    size_t L = 0;
    char c, r;
    int cint = 1;
    char answer[MAX_PATH];
    char Filename[MAX_PATH];
    FILE* File = NULL;
    FILE** p_File = NULL;
    while (File == NULL)
    {
        if ((printf("Input correct path to the file. : \n")) < 0)
        {
            printf("Error of output. ");
            return 1;
        }
        if ((fgets (Filename, MAX_PATH, stdin)) == NULL)
        {
            printf ("Error.");
            return 2;
        }
        Filename[strlen(Filename)-1] = '\0';
        if ((File = fopen(Filename, "rb")) == NULL)
            printf("Error: incorrect path. \n");
    }
    N = &L;
    p_File = &File;
    if ((flenght(File, N))!= 0)
    {
        printf("Error of flenght.\n");
        FILE_close(File);
        return 3;
    }
    if ((FILE_close(File)) != 0)
    {
        printf("Error of close.");
        return 4;
    }
    if ((printf ("Are you sure, that you want to delete this file? \n ")) < 0)
    {
        printf ("Error of output ");
        return 5;
    }
    while (((strcmp(answer, "yes")) != 0) && (strcmp(answer, "no")) != 0)
    {
        if ((printf("If yes - input \"yes\", else - input \"no\" \n")) < 0)
        {
            printf("Error of output. ");
            return 6;
        }
        if ((scanf("%s", answer)) != 1)
        {
            printf("Error.");
            return 7;
        }
    }
    if ((strcmp(answer, "no")) == 0)
        return 0;

    if ((printf("Rewrite with USDoD522022M(input\'1\') or the bytes you entered(input\"2\") or close the programm(input any other number) ? \n")) < 0)
    {
        printf("Error of output. ");
        return 8;
    }
    if((scanf("%d", &n)) != 1)
    {
        printf("Error of input. \n");
        return 9;
    }
    if ((n != 1) && (n != 2))
        return 0;

    if (n == 2)
    {
        if ((printf("input any number of [0;255] to rewrite the file. Input 256 if you want to end rewriting. \n")) < 0)
        {
            printf("Error of output. ");
            return 10;
        }
        if ((scanf("%d", &cint)) != 1)
        {
            printf("Error of input. \n");
            return 11;
        }
        while ((cint < 256) && (cint > -1))
        {
            if ((FILE_open(Filename, p_File)) != 0)
            {
                printf("Error. \n");
                return 12;
            }
            c = cint;
            for(size_t i = 0; i < (*N); ++i)
            {
                if (fwrite(&c, sizeof(char), 1, File) < 1)
                {
                    printf("Error of fwrite. \n");
                    FILE_close(File);
                    return 13;
                }
            }
            if ((FILE_close(File)) != 0)
            {
                printf("Error file closing. \n");
                return 14;
            }
            if ((printf("input any number of [0;255] to rewrite the file. \n")) < 0)
            {
                printf("Error of output. ");
                return 15;
            }
            if((scanf("%d", &cint)) != 1)
            {
                printf("Error of input. \n");
                return 16;
            }
        }
        return 0;
    }
    else
    {
        if ((FILE_open(Filename, p_File)) != 0)
        {
            printf("Error. \n");
            return 17;
        }
        if ((USDoD522022M_R(Filename, File, N, 0)) != 0)
        {
            printf("Error of USDoD522022M_R.");
            FILE_close(File);
            return 18;
        }
        if ((FILE_open(Filename, p_File)) != 0)
        {
            printf("Error. \n");
            return 19;
        }
        if ((USDoD522022M_R(Filename, File, N, 255)) != 0)
        {
            printf("Error of USDoD522022M_R.");
            FILE_close(File);
            return 20;
        }
        if ((FILE_open(Filename, p_File)) != 0)
        {
            printf("Error. \n");
            return 21;
        }

        if ((KSGPSC(&r)) != 0)
        {
            printf("Error of crypt.");
            FILE_close(File);
            return 22;
        }

        if ((USDoD522022M_R(Filename, File, N, r)) != 0)
        {
            printf("Error of USDoD522022M_R.");
            FILE_close(File);
            return 23;
        }
    }
    return 0;
}

int USDoD522022M_R (char *Filename, FILE* File, size_t* N, int r)
{
    if (Filename == NULL)
    {
        printf("Error in USDoD522022M_1. \n");
        FILE_close(File);
        return 1;
    }
    if(File == NULL)
    {
        printf("Error in USDoD522022M_2. \n");
        FILE_close(File);
        return 2;
    }
    if(N == NULL)
    {
        printf("Error in USDoD522022M_2. \n");
        FILE_close(File);
        return 3;
    }
    char c = r;
    for(size_t i = 0; i < (*N); ++i)
    {
        if (fwrite(&c, sizeof(char), 1, File) < 1)
        {
            printf("Error in USDoD522022M_3. \n");
            FILE_close(File);
            return 4;
        }
    }
    if ((FILE_close(File)) != 0)
    {
        printf("Error in USDoD522022M_4. \n");
        return 5;
    }
    return 0;
}

int FILE_open(char *Filename, FILE** File)
{
    if (Filename == NULL)
    {
        printf("Error." );
        return 1;
    }
    if(File == NULL)
    {
        printf("Error in close. \n");
        return 2;
    }
    if ((*File = fopen(Filename, "wb")) == NULL)
    {
        printf("Error in open. \n");
        return 3;
    }
    if(fseek(*File, 0, SEEK_SET) != 0)
    {
        printf("Error in fseek. \n");
        return 4;
    }
    return 0;
}

int FILE_close(FILE* File)
{
    if(File == NULL)
    {
        printf("Error in close. \n");
        return 1;
    }
    if (fclose(File) != 0)
    {
        printf("Error in fclose.");
        return 2;
    }
    return 0;
}

int flenght(FILE* File, size_t* N)
{
    if(File == NULL)
    {
        printf("Error in flength. \n");
        FILE_close(File);
        return 1;
    }
    if(N == NULL)
    {
        printf("Error in flength. \n");
        FILE_close(File);
        return 2;
    }
    if (fseek(File, SEEK_SET, SEEK_END) != 0)
    {
        printf("Error in flength. \n");
        FILE_close(File);
        return 3;
    }
    (*N) = ftell(File);
    if ((*N) == -1)
    {
        printf("Error.\n");
        FILE_close(File);
        return 4;
    }
    if ((printf("\nfile size = %u bytes\n", *N)) < 0)
    {
        printf("Error.\n");
        FILE_close(File);
        return 5;
    }
    return 0;
}

BYTE KSGPSC(char* p_r)
{
    if(p_r == NULL)
    {
        printf("Error . \n");
        return 1;
    }
    HCRYPTPROV   hCryptProv = NULL;
    DWORD        dwMode = 0;
    BYTE         pbData[16];

    if(!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, 0))
    {
        printf("CryptAcquireContext error.\n");
        return 2;
    }

    if((CryptGenRandom (hCryptProv, 8, pbData)) == 0)
    {
        printf("CryptGenRandom error.\n");
        CryptReleaseContext(hCryptProv, dwMode);
        return 3;
    }

    if(!CryptReleaseContext(hCryptProv, dwMode))
    {
        printf("CryptReleaseContext error.\n");
        return 4;
    }
    *p_r = pbData[0];
    return 0;
}



