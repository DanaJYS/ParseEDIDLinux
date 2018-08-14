#include "common.h"

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
        printf("file size is over %d\n", EDIDFILESIZE);
        fclose(fp);
        return 0;
    }

    fseek(fp, 0, SEEK_SET);
    fread(fileData, fileSize, 1, fp);

    printf("%s\n", fileData);

    fclose(fp);

    return fileSize;
}

int getEDIDData(char *fData, int *edidData)
{
    char *ptok = NULL;
    char delim[] = "[ ],\r\n";
    int edidIndex = 0;
    int tempData = 0;
    int i = 0;

    ptok = strtok(fData, delim);
    while(NULL != ptok)
    {
        if(NULL == strchr(ptok, '.'))
        {
            if(0 != sscanf(ptok, "%x", &tempData))
            {
                edidData[edidIndex++] = tempData;

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
    int edidData[EDIDDATASIZE] = {0,0};
    int edidSize = 0;
    int fSize = 0;

    EDID_STRUCT testEDIDStruct = {0};
    memset(&testEDIDStruct, 0, sizeof(EDID_STRUCT));

    int i = 0;

    fSize = readEDIDFile(argv[1], pStr);
    if(fSize <= 0)
        return 1;
    
    pStr[fSize] = '\0';
    printf("fileSize = %d\n", fSize);

    edidSize = getEDIDData(pStr, edidData);
    if(edidSize <= 0)
        return 1;
    printf("EDID size is %d\n", edidSize);

    getEstablishMode(edidData, testEDIDStruct.EstTiming);

    printf("\nEstablish mode list:\n");
    while(testEDIDStruct.EstTiming[i].valid)
    {
            printf("%dx%d@%d\n", testEDIDStruct.EstTiming[i].xResolution, testEDIDStruct.EstTiming[i].yResolution,
                testEDIDStruct.EstTiming[i].RefreshRate);   

	i++;
    }

    printf("\nStand mode list:\n");
    i = 0;
    getStandMode(edidData, testEDIDStruct.StandTiming);
    while(testEDIDStruct.StandTiming[i].valid && i < 8)
    {
            printf("%dx%d@%d\n", testEDIDStruct.StandTiming[i].xResolution, testEDIDStruct.StandTiming[i].yResolution,
                testEDIDStruct.StandTiming[i].RefreshRate); 

	i++;
    }

    i = 0;
    printf("\nDetailed mode list:\n");
    getDetailMode(edidData, testEDIDStruct.DetailTiming);
    while(testEDIDStruct.DetailTiming[i].valid && i < 4)
    {
        printf("Detaild mode %d:\n", i);
        printf("PixelClock: %d\n", testEDIDStruct.DetailTiming[i].PixelClock);
        printf("xResolution: %d\n", testEDIDStruct.DetailTiming[i].xResolution);
        printf("yResolution: %d\n", testEDIDStruct.DetailTiming[i].yResolution);
        printf("hBlank: %d\n", testEDIDStruct.DetailTiming[i].hBlank);
        printf("hSyncOffset: %d\n", testEDIDStruct.DetailTiming[i].hSyncOffset);
        printf("hSyncPulseWidth: %d\n", testEDIDStruct.DetailTiming[i].hSyncPulseWidth);
        printf("vBlank: %d\n", testEDIDStruct.DetailTiming[i].vBlank);
        printf("vSyncOffset: %d\n", testEDIDStruct.DetailTiming[i].vSyncOffset);
        printf("vSyncPulseHeight: %d\n", testEDIDStruct.DetailTiming[i].vSyncPulseHeight);
        printf("hImageSize: %d\n", testEDIDStruct.DetailTiming[i].hImageSize);
        printf("vImageSize: %d\n", testEDIDStruct.DetailTiming[i].vImageSize);
        printf("hBorder: %d\n", testEDIDStruct.DetailTiming[i].hBorder);
        printf("vBorder: %d\n", testEDIDStruct.DetailTiming[i].vBorder);
        printf("Interlaced: %d\n", testEDIDStruct.DetailTiming[i].Interlaced);
        printf("vSync: %d\n", testEDIDStruct.DetailTiming[i].vSync);
        printf("hSync: %d\n", testEDIDStruct.DetailTiming[i].hSync);
        printf("RefreshRate: %d\n", testEDIDStruct.DetailTiming[i].RefreshRate);
        printf("\n");
        

	i++;
    }

    
    return 1;
}
