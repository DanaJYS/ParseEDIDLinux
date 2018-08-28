#include "common.h"
#include "edid.h"

int readEDIDFile(char *fileName, char *fileData)
{
    FILE *fp = NULL;
    long fileSize = 0;

    if(fileName == NULL || fileData == NULL)
    {
        printf("fileName == NULL || edidData == NULL\n");
        return 0;
    }

    fp = fopen(fileName, "rb");
    if(fp == NULL)
    {
        printf("open file failed\n");
        return 0;
    }

    fseek(fp, 0, SEEK_END);
    fileSize = ftell(fp);
    if(fileSize <= 0)
    {
        printf("file size is 0\n");
        fclose(fp);
        return 0;
    }
    if(fileSize >= EDIDFILESIZE)
    {
        printf("file size over %d\n", EDIDFILESIZE);
        fclose(fp);
        return 0;
    }

    fseek(fp, 0, SEEK_SET);
    fread(fileData, fileSize, 1, fp);

    printf("%s\n", fileData);

    fclose(fp);

    return fileSize;
}

int getEDIDData(char *fData, unsigned char *edidData)
{
    char *ptok = NULL;
    char delim[] = "[ ],\r\n";
    int edidIndex = 0;
    unsigned int tempData = 0;
    int i = 0;

    ptok = strtok(fData, delim);
    while(NULL != ptok)
    {
        if(NULL == strchr(ptok, '.'))
        {
            if(0 != sscanf(ptok, "%x", &tempData))
            {
                edidData[edidIndex++] = (unsigned char)tempData;

                if(edidIndex >= EDIDDATASIZE)
                {
                    printf("EDID data num over %d\n", EDIDDATASIZE);
                    return 0;
                }
            }
        }

        ptok = strtok(NULL, delim);
    }

    printf("Get EDID data frome file:\n");
    printf("=============================================================\n");
    for(i = 0; i < edidIndex; i++)
    {
        printf("0x%02x, ", edidData[i]);

        if(i%16 == 15)
            printf("\n");
    }
    printf("=============================================================\n");

    return edidIndex;
}

int main(int argc, char *argv[])
{
    char pStr[EDIDFILESIZE] = {0,0};
    unsigned char edidData[EDIDDATASIZE] = {0,0};
    int edidSize = 0;
    int fSize = 0;
    int i = 0;

    fSize = readEDIDFile(argv[1], pStr);
    if(fSize <= 0)
        return 0;
    
    pStr[fSize] = '\0';
    printf("fileSize = %d\n", fSize);

    edidSize = getEDIDData(pStr, edidData);
    if(edidSize <= 0)
        return 0;
    printf("EDID size is %d\n", edidSize);

    if(IsEDIDValid(edidData, edidSize))
    {
    	DisplayParseEdid(edidData);
    }
    else
    {
    	printf("Edid data invalid!\n");
    }
  
    return 1;
}
