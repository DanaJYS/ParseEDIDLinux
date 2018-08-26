#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define EDIDFILESIZE    2560
#define EDIDDATASIZE    1024



/*
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

#define MAX_EDID_BLOCK_NUM	4
#define CEA_TAG		0x02

typedef enum _CEA_BLOCK_TAG
{
    RSVD_CEA_BLOCK_TAG1 = 0x00,
    AUDIO_DATA_BLOCK_TAG,
    VIDEO_DATA_BLOCK_TAG, 
    VENDOR_SPECIFIC_DATA_BLOCK_TAG,
    SPEAKER_ALLOCATION_DATA_BLOCK_TAG,
    VESA_DTC_DATA_BLOCK_TAG,
    RSVD_CEA_BLOCK_TAG2,
    CEA_EXTENDED_BLOCK_TAG
}CEA_BLOCK_TAG;

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



typedef struct _HDMI_AUDIO_INFO
{
    CBIOS_HDMI_AUDIO_FORMAT_TYPE Format;
    unsigned int                    MaxChannelNum;
    union
    {
        struct
        {
            unsigned int	  SR_32kHz                 :1; 	// Bit0 = 1, support sample rate of 32kHz 
            unsigned int	  SR_44_1kHz               :1; 	// Bit1 = 1, support sample rate of 44.1kHz 
            unsigned int	  SR_48kHz                 :1;	 // Bit2 = 1, support sample rate of 48kHz 
            unsigned int	  SR_88_2kHz               :1; 	// Bit3 = 1, support sample rate of 88.2kHz 
            unsigned int	  SR_96kHz                 :1; 	// Bit4 = 1, support sample rate of 96kHz 
            unsigned int	  SR_176_4kHz              :1; 	// Bit5 = 1, support sample rate of 176.4kHz 
            unsigned int	  SR_192kHz                :1; 	// Bit6 = 1, support sample rate of 192kHz 
            unsigned int	  Reserved                 :25;
        }SampleRate;

        unsigned int                SampleRateUnit;
    };

    union
    {
        unsigned int		 Unit;
        
        // for audio format: LPCM
        struct
        {
            unsigned int	  BD_16bit                 :1; 	// Bit0 = 1, support bit depth of 16 bits 
            unsigned int	  BD_20bit                 :1; 	// Bit1 = 1, support bit depth of 20 bits 
            unsigned int	  BD_24bit                 :1; 	// Bit2 = 1, support bit depth of 24 bits 
            unsigned int	  Reserved                 :29;
        }BitDepth;

        // for audio format: AC-3, MPEG-1, MP3, MPED-2, AAC LC, DTS, ATRAC
        CBIOS_U32                MaxBitRate; // unit: kHz

        // for audio format: DSD, E-AC-3, DTS-HD, MLP, DST
        CBIOS_U32                AudioFormatDependValue; // for these audio formats, this value is defined in 
                                                            it's corresponding format-specific documents

        // for audio format: WMA Pro
        struct
        {
            CBIOS_U32  Value                    :3;
            CBIOS_U32  Reserved                 :29;
        }Profile;
    };
}CBIOS_HDMI_AUDIO_INFO, *PCBIOS_HDMI_AUDIO_INFO;

typedef struct _EDID_STRUCT
{
    EDID_BASICTIMING	EstTiming[17];
    EDID_BASICTIMING	StandTiming[8];
    EDID_DETAILTIMING	DetailTiming[4];

    unsigned int	TotalHDMIAudioFormatNum;
    
} EDID_STRUCT, *pEDID_STRUCT;


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
*/