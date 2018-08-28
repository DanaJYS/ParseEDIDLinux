#include"common.h"
//#include"I2c.h"

#define EDID_SIZE                        256
#define CBIOS_HDMI_NORMAL_VIC_COUNTS     107
#define MAX_EDID_BLOCK_NUM               4 
// some data index in base EDID block
#define MONITORIDINDEX                   0x08
#define VERSIONINDEX                     0x12
#define DISPLAYPARAINDEX                 0x14
#define COLORCHARACTERINDEX              0x19
#define ESTABLISH_TIMINGS_INDEX          0x23
#define STANDARD_TIMINGS_INDEX           0x26
#define DETAILED_TIMINGS_INDEX           0x36
#define EXTENSION_FLAG_INDEX             0x7E

typedef struct _CBIOS_HDMI_FORMAT_MTX
{
    int FormatNum;
    int XRes;
    int YRes;
    char Interlace;
    int RefRate[2];
    char AspectRatio;
    char DefalutRefRateIndex;
    int PixelClock;
}CBIOS_HDMI_FORMAT_MTX;

typedef struct _CBIOS_Module_EDID_ESTTIMINGS
{
    int    XResolution;       //Horizontal size
    int    YResolution;       //Vertical Size
    int    RefreshRate;       //Refresh rate
    char    Protocol;     
}CBIOS_Module_EDID_ESTTIMINGS;

// CEA data block types tags definition
#define CEA_TAG                          0x02
typedef enum _CBIOS_CEA_BLOCK_TAG
{
    RSVD_CEA_BLOCK_TAG1 = 0x00,
    AUDIO_DATA_BLOCK_TAG,
    VIDEO_DATA_BLOCK_TAG, 
    VENDOR_SPECIFIC_DATA_BLOCK_TAG,
    SPEAKER_ALLOCATION_DATA_BLOCK_TAG,
    VESA_DTC_DATA_BLOCK_TAG,
    RSVD_CEA_BLOCK_TAG2,
    CEA_EXTENDED_BLOCK_TAG
}CBIOS_CEA_BLOCK_TAG;


typedef enum _CBIOS_CEA_EXTENDED_BLOCK_TAG
{
    VIDEO_CAPABILITY_DATA_BLOCK_TAG = 0x00,
    VENDOR_SPECIFIC_VIDEO_DATA_BLOCK_TAG,
    VESA_VIDEO_DISPLAY_DEVICE_DATA_BLOCK_TAG,
    RSVD_VESA_VIDEO_TIMING_DATA_BLOCK_TAG,
    RSVD_HDMI_VIDEO_DATA_BLOCK,
    COLORIMETRY_DATA_BLOCK_TAG,
    HDR_STATIC_METADATA_DATA_BLOCK,
    //7-12 reserved for video-related blocks
    VIDEO_FMT_PREFERENCE_DATA_BLOCK = 0xD,
    YCBCR420_VIDEO_DATA_BLOCK,
    YCBCR420_CAP_MAP_DATA_BLOCK,
    CEA_MISC_AUDIO_FIELDS_TAG,
    VENDOR_SPECIFIC_AUDIO_DATA_BLOCK_TAG,
    RSVD_HDMI_AUDIO_DATA_BLOCK_TAG,
    //19-31 reserved for audio-related blocks
    //32-255 reserved for general
}CBIOS_CEA_EXTENDED_BLOCK_TAG;


//int  ParseEdid();
//void DisplayEdidRawData(unsigned char *pEdid);
void DisplayParseEdid(unsigned char *pEdid);
void DisplayEdidHeader(char *pEdidInfo);
void DisplayEdidVendorIdenti(char *pEdidInfo);
void DisplayEdidEDIDversion(char *pEdidInfo);
void DisplayEdidDisplayParams(char *pEdidInfo);
void DisplayEdidColorCharacters(char *pEdidInfo);
void DisplayEdidEstTimings(char *pEdidInfo);
void DisplayEdidStdTimings(char *pEdidInfo);
void DisplayEdidDetailedTimings(char *pEdidInfo);
void DisplayEdidExtFlagandChecksum(char *pEdidInfo);
void DisplayCEA861(char *pEdidInfo);
void ParseVIDEO_DATA_BLOCK(char *pEdidInfo,int Length,int * SVD_mode, int *SVD_mode_info);
void ParseAUDIO_DATA_BLOCK(char *pEdidInfo,int Length);
void ParseSpeakerAllocation(char *pEdidInfo, int Length);
void ParseHFVSDB(char *pEdidInfo, int Length);
void ParseVSDB(char *pEdidInfo, int Length, int *SVD_mode, int *SVD_mode_num);
void ParseDetailedTiming(char *pEdidInfo,int Offset);

