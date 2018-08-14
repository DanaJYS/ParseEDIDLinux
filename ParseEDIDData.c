#include "common.h"

static EDID_BASICTIMING EstTiming1[] = 
{
    {800, 600, 60, 0},
    {800, 600, 56, 0},
    {640, 480, 75, 0},
    {640, 480, 72, 0},
    {640, 480, 67, 0},
    {640, 480, 60, 0},
    {720, 400, 88, 0},
    {720, 400, 70, 0},
};

static EDID_BASICTIMING EstTiming2[] = 
{
    {1280, 1024, 75, 0},
    {1024, 768, 75, 0},
    {1024, 768, 70, 0},
    {1024, 768, 60, 0},
    {1024, 768, 87, 0},
    {832, 624, 75, 0},
    {800, 600, 75, 0},
    {800, 600, 72, 0},
};

static EDID_BASICTIMING EstTiming3[] = 
{
    {1152, 870, 75, 0},
};

int getEstablishMode(int *edidData, pEDID_BASICTIMING pEstTimings)
{
    int EstModeIndex = 0;
    unsigned char ulMask = 0x01;
    int i = 0;
    edidData = edidData + ESTABTIMING;
    for(i = 0; i < 8; i++)
    {
        if(*edidData & ulMask)
        {
            pEstTimings[EstModeIndex].valid = 1;
            pEstTimings[EstModeIndex].xResolution = EstTiming1[i].xResolution;
            pEstTimings[EstModeIndex].yResolution = EstTiming1[i].yResolution;
            pEstTimings[EstModeIndex].RefreshRate = EstTiming1[i].RefreshRate;

	    EstModeIndex++;
        }
	ulMask = ulMask << 1;
    }

    edidData += 1;
    ulMask = 0x01;
    for(i = 0; i < 8; i++)
    {
        if(*edidData & ulMask)
        {
            pEstTimings[EstModeIndex].valid = 1;
            pEstTimings[EstModeIndex].xResolution = EstTiming2[i].xResolution;
            pEstTimings[EstModeIndex].yResolution = EstTiming2[i].yResolution;
            pEstTimings[EstModeIndex].RefreshRate = EstTiming2[i].RefreshRate;

	    EstModeIndex++;
        }
	ulMask = ulMask << 1;
    }

    edidData += 1;
    ulMask = 0x80;
    if(*edidData & ulMask)
    {
        pEstTimings[EstModeIndex].valid = 1;
	pEstTimings[EstModeIndex].xResolution = EstTiming3[0].xResolution;
	pEstTimings[EstModeIndex].yResolution = EstTiming3[0].yResolution;
	pEstTimings[EstModeIndex].RefreshRate = EstTiming3[0].RefreshRate;

	EstModeIndex++;
    }

    for(i = EstModeIndex; i < 17; i++)
    {
        pEstTimings[EstModeIndex].valid = 
	pEstTimings[EstModeIndex].xResolution = 
	pEstTimings[EstModeIndex].yResolution = 
	pEstTimings[EstModeIndex].RefreshRate = 0;
    }

    return EstModeIndex;
}

int getStandMode(int *edidData, pEDID_BASICTIMING pStandTimings)
{
    int i = 0;
    int StandModeIndex = 0;

    edidData += STANDTIMING;

    for(i = 0; i < 8; i++)
    {
	if(*(edidData + i*2) == 0x00 || *(edidData + i*2) == 0x01)
	{
	    break;
	}
	
	pStandTimings[StandModeIndex].valid = 1;
	pStandTimings[StandModeIndex].xResolution = (*(edidData+i*2)+31)*8;
	pStandTimings[StandModeIndex].RefreshRate = (*(edidData+i*2+1) & 0x3f)+60;

	switch((*(edidData+i*2+1) & 0xc0) >> 6)
	{
	    case 0: //16:10
		pStandTimings[StandModeIndex].yResolution = pStandTimings[StandModeIndex].xResolution * 10 / 16;
		break;
	    case 1: //4:3
		pStandTimings[StandModeIndex].yResolution = pStandTimings[StandModeIndex].xResolution * 3 / 4;
		break;
	    case 2: //5:4
		pStandTimings[StandModeIndex].yResolution = pStandTimings[StandModeIndex].xResolution * 4 / 5;
		break;
	    case 3: //16:9
		pStandTimings[StandModeIndex].yResolution = pStandTimings[StandModeIndex].xResolution * 9 / 10;
		break;
	}
	StandModeIndex++;
    }

    for(i = StandModeIndex; i < 8; i++)
    {
	pStandTimings[i].valid =
	pStandTimings[i].xResolution =
	pStandTimings[i].yResolution =
	pStandTimings[i].RefreshRate = 0;
    }

    return StandModeIndex;
}

int mapMaskGetEDIDInfo(int *edidData, DETAILTIMING_MAPTABLE *mapTable)
{
    int i = 0, j = 0;
    int tempData = 0;
    int uret = 0;
    
    while(mapTable->index >= 0)
    {
	tempData = *(edidData+mapTable->index);

	for(i = 0; i < 8; i++)
	{
	    if(mapTable->mask & 1<<i)
	    {
		uret += (tempData & (1<<i)) ? 1<<j : 0;
		j++;
	    }
	}
	mapTable++;
    }

    return uret;
}

int getDetailMode(int *edidData, pEDID_DETAILTIMING pDetailTimings)
{
   int i = 0;
   int DetailModeIndex = 0;
   edidData += DETAILTIMING;

   int pixelclock = 0;
   int hActive = 0, vActive = 0, hBlank = 0, vBlank = 0;

   DETAILTIMING_MAPTABLE PixelClockTable[] = {{0, 0xff}, {1, 0xff}, {-1, 0}};
   DETAILTIMING_MAPTABLE xResolutionTable[] = {{2, 0xff}, {4, 0xf0}, {-1, 0}};
   DETAILTIMING_MAPTABLE hBlankTable[] = {{3, 0xff}, {4, 0x0f}, {-1, 0}};
   DETAILTIMING_MAPTABLE yResolutionTable[] = {{5, 0xff}, {7, 0xf0}, {-1, 0}};
   DETAILTIMING_MAPTABLE vBlankTable[] = {{6, 0xff}, {7, 0x0f}, {-1, 0}};
   DETAILTIMING_MAPTABLE hSyncOffsetTable[] = {{8, 0xff}, {11, 0xc0}, {-1, 0}};
   DETAILTIMING_MAPTABLE hSyncPulseWidthTable[] = {{9, 0xff}, {11, 0x30}, {-1, 0}};
   DETAILTIMING_MAPTABLE vSyncOffsetTable[] = {{10, 0xf0}, {11, 0x0c}, {-1, 0}};
   DETAILTIMING_MAPTABLE vSyncPulseHeightTable[] = {{10, 0x0f}, {11, 0x03}, {-1, 0}};
   DETAILTIMING_MAPTABLE hImageSizeTable[] = {{12, 0xff}, {14, 0xf0}, {-1, 0}};
   DETAILTIMING_MAPTABLE vImageSizeTable[] = {{13, 0xff}, {14, 0x0f}, {-1, 0}};
   DETAILTIMING_MAPTABLE hBorderTable[] = {{15, 0xff}, {-1, 0}};
   DETAILTIMING_MAPTABLE vBorderTable[] = {{16, 0xff}, {-1, 0}};
   

   for(i = 0; i < 4; i++)
   {
	 if(*(edidData+i*18) == 0x00 && *(edidData+i*18+1) == 0x00)
	     break;

	 pDetailTimings[DetailModeIndex].PixelClock = 10000 * mapMaskGetEDIDInfo(edidData + i*18, PixelClockTable);
        pDetailTimings[DetailModeIndex].xResolution = mapMaskGetEDIDInfo(edidData + i*18, xResolutionTable);
        pDetailTimings[DetailModeIndex].hBlank = mapMaskGetEDIDInfo(edidData + i*18, hBlankTable);
        pDetailTimings[DetailModeIndex].yResolution = mapMaskGetEDIDInfo(edidData + i*18, yResolutionTable);
        pDetailTimings[DetailModeIndex].vBlank = mapMaskGetEDIDInfo(edidData + i*18, vBlankTable);
        pDetailTimings[DetailModeIndex].hSyncOffset = mapMaskGetEDIDInfo(edidData + i*18, hSyncOffsetTable);
        pDetailTimings[DetailModeIndex].hSyncPulseWidth = mapMaskGetEDIDInfo(edidData + i*18, hSyncPulseWidthTable);
        pDetailTimings[DetailModeIndex].vSyncOffset = mapMaskGetEDIDInfo(edidData + i*18, vSyncOffsetTable);
        pDetailTimings[DetailModeIndex].vSyncPulseHeight = mapMaskGetEDIDInfo(edidData + i*18, vSyncPulseHeightTable);
        pDetailTimings[DetailModeIndex].hImageSize = mapMaskGetEDIDInfo(edidData + i*18, hImageSizeTable);
        pDetailTimings[DetailModeIndex].vImageSize = mapMaskGetEDIDInfo(edidData + i*18, vImageSizeTable);
        pDetailTimings[DetailModeIndex].hBorder = mapMaskGetEDIDInfo(edidData + i*18, hBorderTable);
        pDetailTimings[DetailModeIndex].vBorder = mapMaskGetEDIDInfo(edidData + i*18, vBorderTable);

        if(pDetailTimings[DetailModeIndex].xResolution == 0 ||pDetailTimings[DetailModeIndex].yResolution == 0)
            break;

        if(pDetailTimings[DetailModeIndex].hBlank == 0 ||pDetailTimings[DetailModeIndex].vBlank == 0)
            break;

        pDetailTimings[DetailModeIndex].valid = 1;
        if(edidData[i*18 + 0x11] & 0x80)
        {
            pDetailTimings[DetailModeIndex].Interlaced = 1;
        }

        if((edidData[i*18 + 0x11] & 0x18) == 0x18)
        {
            if((edidData[i*18 + 0x11] & 0x04) == 0x04)
                pDetailTimings[DetailModeIndex].vSync = vSyncPOSITIVE;
            else
                pDetailTimings[DetailModeIndex].vSync = vSyncNEGATIVE;

            if((edidData[i*18 + 0x11] & 0x02) == 0x02)
                pDetailTimings[DetailModeIndex].hSync = vSyncPOSITIVE;
            else
                pDetailTimings[DetailModeIndex].hSync = vSyncNEGATIVE;
        }
        else
        {
            pDetailTimings[DetailModeIndex].vSync = vSyncNEGATIVE;
            pDetailTimings[DetailModeIndex].hSync = vSyncNEGATIVE;
        }

        pixelclock = pDetailTimings[DetailModeIndex].PixelClock;
        hActive = pDetailTimings[DetailModeIndex].xResolution;
        vActive = pDetailTimings[DetailModeIndex].yResolution;
        hBlank = pDetailTimings[DetailModeIndex].hBlank;
        vBlank = pDetailTimings[DetailModeIndex].vBlank;
        pDetailTimings[DetailModeIndex].RefreshRate = pixelclock/(hActive + hBlank)/(vActive + vBlank);

        DetailModeIndex++;
   } 

   return DetailModeIndex;
}