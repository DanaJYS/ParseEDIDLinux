#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

//basic EDID index
#define VEND_PROD_IDENTIFI      0x08
#define EDIDSTRUCTVERSION       0x12
#define BASICDISPPARAM      0x14
#define COLORCHARAC     0x19
#define ESTABTIMING     0x23
#define STANDTIMING     0x26
#define DETAILTIMING        0x36
#define EXTENFLAG       0x7e
#define CHECKSUM        0x7f

#define vSyncPOSITIVE   1
#define vSyncNEGATIVE   0

typedef struct _EDID_BASICTIMING
{
    int  xResolution;
    int  yResolution;
    int  RefreshRate;
    int  valid;
} EDID_BASICTIMING, *pEDID_BASICTIMING;

typedef struct _EDID_DETAILTIMING
{
    int     RefreshRate;
    int     PixelClock;
    int     xResolution;
    int     yResolution;
    int     hBlank;
    int     hSyncOffset;
    int     hSyncPulseWidth;
    int     vBlank;
    int     vSyncOffset;
    int     vSyncPulseHeight;
    int     hImageSize;
    int     vImageSize;
    int     hBorder;
    int     vBorder;
    int     valid;
    int     Interlaced;
    int     vSync;
    int     hSync;
    int     IsNativeMode;
} EDID_DETAILTIMING, *pEDID_DETAILTIMING;

typedef struct _EDID_STRUCT
{
    EDID_BASICTIMING	EstTiming[17];
    EDID_BASICTIMING	StandTiming[8];
    EDID_DETAILTIMING	DetailTiming[4];
} EDID_STRUCT;


typedef struct _DETAILTIMING_MAPTABLE
{
    int index;
    int mask;
}  DETAILTIMING_MAPTABLE;

//parse edid function
int getEstablishMode(int *edidData, pEDID_BASICTIMING pEstTimings);
int getStandMode(int *edidData, pEDID_BASICTIMING pStandTimings);
int mapMaskGetEDIDInfo(int *edidData, DETAILTIMING_MAPTABLE *mapTable);
int getDetailMode(int *edidData, pEDID_DETAILTIMING pDetailTimings);