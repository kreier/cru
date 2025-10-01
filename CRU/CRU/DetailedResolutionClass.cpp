//---------------------------------------------------------------------------
#include "Common.h"
#pragma hdrstop

#include "DetailedResolutionClass.h"
//---------------------------------------------------------------------------
const int DetailedResolutionClass::MinTiming = TIMING_MANUAL;
const int DetailedResolutionClass::MaxTiming = TIMING_MANUAL_VTOTAL;

const char *DetailedResolutionClass::TimingText[] =
{
	"Manual",
	"Automatic PC",
	"Automatic HDTV",
	"Automatic CRT",
	"Native PC",
	"Native HDTV",
	"Exact",
	"Exact reduced",
	"Exact CRT",
	"CVT standard",
	"CVT-RB standard",
	"CVT-RB2 standard",
	"GTF standard",
	"Vertical total calculator (QFT)",
};

bool (DetailedResolutionClass::*DetailedResolutionClass::TimingFunction[])() =
{
	&CalculateManual,
	&CalculateAutomaticPC,
	&CalculateAutomaticHDTV,
	&CalculateAutomaticCRT,
	&CalculateNativePC,
	&CalculateNativeHDTV,
	&CalculateExact,
	&CalculateExactReduced,
	&CalculateExactCRT,
	&CalculateCVTStandard,
	&CalculateCVTRBStandard,
	&CalculateCVTRB2Standard,
	&CalculateGTFStandard,
	&CalculateManualVTotal,
};

const DetailedResolutionStruct DetailedResolutionClass::AutomaticPC[] =
{
	{ 1920, 1080, 0,  59500,  60500,   88,  44, 148,  4,  5,  36, 1, 1}, // 1920x1080 @ 60 Hz
	{ 1920, 1080, 0,  49500,  50500,  528,  44, 148,  4,  5,  36, 1, 1}, // 1920x1080 @ 50 Hz
	{ 1920, 1080, 0,  47500,  48500,  638,  44, 148,  4,  5,  36, 1, 1}, // 1920x1080 @ 48 Hz
	{ 1920, 1080, 0,  29500,  30500,   88,  44, 148,  4,  5,  36, 1, 1}, // 1920x1080 @ 30 Hz
	{ 1920, 1080, 0,  24500,  25500,  528,  44, 148,  4,  5,  36, 1, 1}, // 1920x1080 @ 25 Hz
	{ 1920, 1080, 0,  23500,  24500,  638,  44, 148,  4,  5,  36, 1, 1}, // 1920x1080 @ 24 Hz
	{ 1920, 1080, 1,  59500,  60500,   88,  44, 148,  4, 10,  31, 1, 1}, // 1920x1080i @ 60 Hz
	{ 1920, 1080, 1,  49500,  50500,  528,  44, 148,  4, 10,  31, 1, 1}, // 1920x1080i @ 50 Hz
	{ 1600,  900, 0,  59500,  60500,   24,  80,  96,  1,  3,  96, 1, 1}, // 1600x900 @ 60 Hz
	{ 1366,  768, 0,  59500,  60500,   70, 143, 213,  3,  3,  24, 1, 1}, // 1366x768 @ 60 Hz
	{ 1360,  768, 0,  59500,  60500,   64, 112, 256,  3,  6,  18, 1, 1}, // 1360x768 @ 60 Hz
	{ 1280,  720, 0,  59500,  60500,  110,  40, 220,  5,  5,  20, 1, 1}, // 1280x720 @ 60 Hz
	{ 1280,  720, 0,  49500,  50500,  440,  40, 220,  5,  5,  20, 1, 1}, // 1280x720 @ 50 Hz
	{ 1280,  720, 0,  47500,  48500,  960,  40, 220,  5,  5,  20, 1, 1}, // 1280x720 @ 48 Hz
	{ 1280,  720, 0,  29500,  30500, 1760,  40, 220,  5,  5,  20, 1, 1}, // 1280x720 @ 30 Hz
	{ 1280,  720, 0,  24500,  25500, 2420,  40, 220,  5,  5,  20, 1, 1}, // 1280x720 @ 25 Hz
	{ 1280,  720, 0,  23500,  24500, 1760,  40, 220,  5,  5,  20, 1, 1}, // 1280x720 @ 24 Hz
	{ 1440,  576, 1,  49500,  50500,   24, 126, 138,  4,  6,  39, 0, 0}, // 1440x576i @ 50 Hz
	{ 1440,  480, 1,  59500,  60500,   38, 124, 114,  8,  6,  31, 0, 0}, // 1440x480i @ 60 Hz
	{  720,  576, 0,  49500,  50500,   12,  64,  68,  5,  5,  39, 0, 0}, // 720x576 @ 50 Hz
	{  720,  480, 0,  59500,  60500,   16,  62,  60,  9,  6,  30, 0, 0}, // 720x480 @ 60 Hz
	{  640,  480, 0,  59500,  60500,   16,  96,  48, 10,  2,  33, 0, 0}, // 640x480 @ 60 Hz
	{0}
};

const DetailedResolutionStruct DetailedResolutionClass::AutomaticHDTV[] =
{
	{10240, 4320, 0, 119500, 120500,  288, 176, 296, 16, 20, 144, 1, 1}, // 10240x4320 @ 120 Hz
	{10240, 4320, 0,  99500, 100500, 2192, 176, 592, 16, 20, 144, 1, 1}, // 10240x4320 @ 100 Hz
	{10240, 4320, 0,  59500,  60500,  288, 176, 296, 16, 20, 144, 1, 1}, // 10240x4320 @ 60 Hz
	{10240, 4320, 0,  49500,  50500, 2492, 176, 592, 16, 20,  44, 1, 1}, // 10240x4320 @ 50 Hz
	{10240, 4320, 0,  47500,  48500, 1492, 176, 592, 16, 20, 594, 1, 1}, // 10240x4320 @ 48 Hz
	{10240, 4320, 0,  29500,  30500,  288, 176, 296, 16, 20, 144, 1, 1}, // 10240x4320 @ 30 Hz
	{10240, 4320, 0,  24500,  25500, 2492, 176, 592, 16, 20,  44, 1, 1}, // 10240x4320 @ 25 Hz
	{10240, 4320, 0,  23500,  24500, 1492, 176, 592, 16, 20, 594, 1, 1}, // 10240x4320 @ 24 Hz
	{ 7680, 4320, 0, 119500, 120500,  352, 176, 592, 16, 20, 144, 1, 1}, // 7680x4320 @ 120 Hz
	{ 7680, 4320, 0,  99500, 100500, 2112, 176, 592, 16, 20, 144, 1, 1}, // 7680x4320 @ 100 Hz
	{ 7680, 4320, 0,  59500,  60500,  552, 176, 592, 16, 20,  44, 1, 1}, // 7680x4320 @ 60 Hz
	{ 7680, 4320, 0,  49500,  50500, 2352, 176, 592, 16, 20,  44, 1, 1}, // 7680x4320 @ 50 Hz
	{ 7680, 4320, 0,  47500,  48500, 2552, 176, 592, 16, 20, 144, 1, 1}, // 7680x4320 @ 48 Hz
	{ 7680, 4320, 0,  29500,  30500,  552, 176, 592, 16, 20,  44, 1, 1}, // 7680x4320 @ 30 Hz
	{ 7680, 4320, 0,  24500,  25500, 2352, 176, 592, 16, 20,  44, 1, 1}, // 7680x4320 @ 25 Hz
	{ 7680, 4320, 0,  23500,  24500, 2552, 176, 592, 16, 20, 144, 1, 1}, // 7680x4320 @ 24 Hz
	{ 5120, 2160, 0, 119500, 120500,  164,  88, 128,  8, 10,  72, 1, 1}, // 5120x2160 @ 120 Hz
	{ 5120, 2160, 0,  99500, 100500, 1096,  88, 296,  8, 10,  72, 1, 1}, // 5120x2160 @ 100 Hz
	{ 5120, 2160, 0,  59500,  60500,  164,  88, 128,  8, 10,  72, 1, 1}, // 5120x2160 @ 60 Hz
	{ 5120, 2160, 0,  49500,  50500, 1096,  88, 296,  8, 10,  72, 1, 1}, // 5120x2160 @ 50 Hz
	{ 5120, 2160, 0,  47500,  48500,  746,  88, 296,  8, 10, 297, 1, 1}, // 5120x2160 @ 48 Hz
	{ 5120, 2160, 0,  29500,  30500,  664,  88, 128,  8, 10,  22, 1, 1}, // 5120x2160 @ 30 Hz
	{ 5120, 2160, 0,  24500,  25500, 1696,  88, 296,  8, 10,  22, 1, 1}, // 5120x2160 @ 25 Hz
	{ 5120, 2160, 0,  23500,  24500, 1996,  88, 296,  8, 10,  22, 1, 1}, // 5120x2160 @ 24 Hz
	{ 4096, 2160, 0, 119500, 120500,   88,  88, 128,  8, 10,  72, 1, 1}, // 4096x2160 @ 120 Hz
	{ 4096, 2160, 0,  99500, 100500,  800,  88, 296,  8, 10,  72, 1, 1}, // 4096x2160 @ 100 Hz
	{ 4096, 2160, 0,  59500,  60500,   88,  88, 128,  8, 10,  72, 1, 1}, // 4096x2160 @ 60 Hz
	{ 4096, 2160, 0,  49500,  50500,  968,  88, 128,  8, 10,  72, 1, 1}, // 4096x2160 @ 50 Hz
	{ 4096, 2160, 0,  47500,  48500, 1020,  88, 296,  8, 10,  72, 1, 1}, // 4096x2160 @ 48 Hz
	{ 4096, 2160, 0,  29500,  30500,   88,  88, 128,  8, 10,  72, 1, 1}, // 4096x2160 @ 30 Hz
	{ 4096, 2160, 0,  24500,  25500,  968,  88, 128,  8, 10,  72, 1, 1}, // 4096x2160 @ 25 Hz
	{ 4096, 2160, 0,  23500,  24500, 1020,  88, 296,  8, 10,  72, 1, 1}, // 4096x2160 @ 24 Hz
	{ 3840, 2160, 0, 119500, 120500,  176,  88, 296,  8, 10,  72, 1, 1}, // 3840x2160 @ 120 Hz
	{ 3840, 2160, 0,  99500, 100500, 1056,  88, 296,  8, 10,  72, 1, 1}, // 3840x2160 @ 100 Hz
	{ 3840, 2160, 0,  59500,  60500,  176,  88, 296,  8, 10,  72, 1, 1}, // 3840x2160 @ 60 Hz
	{ 3840, 2160, 0,  49500,  50500, 1056,  88, 296,  8, 10,  72, 1, 1}, // 3840x2160 @ 50 Hz
	{ 3840, 2160, 0,  47500,  48500, 1276,  88, 296,  8, 10,  72, 1, 1}, // 3840x2160 @ 48 Hz
	{ 3840, 2160, 0,  29500,  30500,  176,  88, 296,  8, 10,  72, 1, 1}, // 3840x2160 @ 30 Hz
	{ 3840, 2160, 0,  24500,  25500, 1056,  88, 296,  8, 10,  72, 1, 1}, // 3840x2160 @ 25 Hz
	{ 3840, 2160, 0,  23500,  24500, 1276,  88, 296,  8, 10,  72, 1, 1}, // 3840x2160 @ 24 Hz
	{ 2560, 1080, 0, 119500, 120500,  548,  44, 148,  4,  5, 161, 1, 1}, // 2560x1080 @ 120 Hz
	{ 2560, 1080, 0,  99500, 100500,  218,  44, 148,  4,  5, 161, 1, 1}, // 2560x1080 @ 100 Hz
	{ 2560, 1080, 0,  59500,  60500,  248,  44, 148,  4,  5,  11, 1, 1}, // 2560x1080 @ 60 Hz
	{ 2560, 1080, 0,  49500,  50500,  548,  44, 148,  4,  5,  36, 1, 1}, // 2560x1080 @ 50 Hz
	{ 2560, 1080, 0,  47500,  48500,  998,  44, 148,  4,  5,  11, 1, 1}, // 2560x1080 @ 48 Hz
	{ 2560, 1080, 0,  29500,  30500,  768,  44, 148,  4,  5,  36, 1, 1}, // 2560x1080 @ 30 Hz
	{ 2560, 1080, 0,  24500,  25500,  448,  44, 148,  4,  5,  36, 1, 1}, // 2560x1080 @ 25 Hz
	{ 2560, 1080, 0,  23500,  24500,  998,  44, 148,  4,  5,  11, 1, 1}, // 2560x1080 @ 24 Hz
	{ 1920, 1080, 0, 119500, 120500,   88,  44, 148,  4,  5,  36, 1, 1}, // 1920x1080 @ 120 Hz
	{ 1920, 1080, 0,  99500, 100500,  528,  44, 148,  4,  5,  36, 1, 1}, // 1920x1080 @ 100 Hz
	{ 1920, 1080, 0,  59500,  60500,   88,  44, 148,  4,  5,  36, 1, 1}, // 1920x1080 @ 60 Hz
	{ 1920, 1080, 0,  49500,  50500,  528,  44, 148,  4,  5,  36, 1, 1}, // 1920x1080 @ 50 Hz
	{ 1920, 1080, 0,  47500,  48500,  638,  44, 148,  4,  5,  36, 1, 1}, // 1920x1080 @ 48 Hz
	{ 1920, 1080, 0,  29500,  30500,   88,  44, 148,  4,  5,  36, 1, 1}, // 1920x1080 @ 30 Hz
	{ 1920, 1080, 0,  24500,  25500,  528,  44, 148,  4,  5,  36, 1, 1}, // 1920x1080 @ 25 Hz
	{ 1920, 1080, 0,  23500,  24500,  638,  44, 148,  4,  5,  36, 1, 1}, // 1920x1080 @ 24 Hz
	{ 1920, 1080, 1, 119500, 120500,   88,  44, 148,  4, 10,  31, 1, 1}, // 1920x1080i @ 120 Hz
	{ 1920, 1080, 1,  99500, 100500,  528,  44, 148,  4, 10,  31, 1, 1}, // 1920x1080i @ 100 Hz
	{ 1920, 1080, 1,  59500,  60500,   88,  44, 148,  4, 10,  31, 1, 1}, // 1920x1080i @ 60 Hz
	{ 1920, 1080, 1,  49500,  50500,  528,  44, 148,  4, 10,  31, 1, 1}, // 1920x1080i @ 50 Hz
	{ 1680,  720, 0, 119500, 120500,   60,  40, 220,  5,  5,  95, 1, 1}, // 1680x720 @ 120 Hz
	{ 1680,  720, 0,  99500, 100500,   60,  40, 220,  5,  5,  95, 1, 1}, // 1680x720 @ 100 Hz
	{ 1680,  720, 0,  59500,  60500,  260,  40, 220,  5,  5,  20, 1, 1}, // 1680x720 @ 60 Hz
	{ 1680,  720, 0,  49500,  50500,  260,  40, 220,  5,  5,  20, 1, 1}, // 1680x720 @ 50 Hz
	{ 1680,  720, 0,  47500,  48500,  810,  40, 220,  5,  5,  20, 1, 1}, // 1680x720 @ 48 Hz
	{ 1680,  720, 0,  29500,  30500,  700,  40, 220,  5,  5,  20, 1, 1}, // 1680x720 @ 30 Hz
	{ 1680,  720, 0,  24500,  25500, 1228,  40, 220,  5,  5,  20, 1, 1}, // 1680x720 @ 25 Hz
	{ 1680,  720, 0,  23500,  24500, 1360,  40, 220,  5,  5,  20, 1, 1}, // 1680x720 @ 24 Hz
	{ 1600,  900, 0,  59500,  60500,   24,  80,  96,  1,  3,  96, 1, 1}, // 1600x900 @ 60 Hz
	{ 1366,  768, 0,  59500,  60500,   70, 143, 213,  3,  3,  24, 1, 1}, // 1366x768 @ 60 Hz
	{ 1360,  768, 0,  59500,  60500,   64, 112, 256,  3,  6,  18, 1, 1}, // 1360x768 @ 60 Hz
	{ 1280,  720, 0, 119500, 120500,  110,  40, 220,  5,  5,  20, 1, 1}, // 1280x720 @ 120 Hz
	{ 1280,  720, 0,  99500, 100500,  440,  40, 220,  5,  5,  20, 1, 1}, // 1280x720 @ 100 Hz
	{ 1280,  720, 0,  59500,  60500,  110,  40, 220,  5,  5,  20, 1, 1}, // 1280x720 @ 60 Hz
	{ 1280,  720, 0,  49500,  50500,  440,  40, 220,  5,  5,  20, 1, 1}, // 1280x720 @ 50 Hz
	{ 1280,  720, 0,  47500,  48500,  960,  40, 220,  5,  5,  20, 1, 1}, // 1280x720 @ 48 Hz
	{ 1280,  720, 0,  29500,  30500, 1760,  40, 220,  5,  5,  20, 1, 1}, // 1280x720 @ 30 Hz
	{ 1280,  720, 0,  24500,  25500, 2420,  40, 220,  5,  5,  20, 1, 1}, // 1280x720 @ 25 Hz
	{ 1280,  720, 0,  23500,  24500, 1760,  40, 220,  5,  5,  20, 1, 1}, // 1280x720 @ 24 Hz
	{ 1440,  576, 1, 199500, 200500,   24, 126, 138,  4,  6,  39, 0, 0}, // 1440x576i @ 200 Hz
	{ 1440,  576, 1,  99500, 100500,   24, 126, 138,  4,  6,  39, 0, 0}, // 1440x576i @ 100 Hz
	{ 1440,  576, 1,  49500,  50500,   24, 126, 138,  4,  6,  39, 0, 0}, // 1440x576i @ 50 Hz
	{ 1440,  480, 1, 239500, 240500,   38, 124, 114,  8,  6,  31, 0, 0}, // 1440x480i @ 240 Hz
	{ 1440,  480, 1, 119500, 120500,   38, 124, 114,  8,  6,  31, 0, 0}, // 1440x480i @ 120 Hz
	{ 1440,  480, 1,  59500,  60500,   38, 124, 114,  8,  6,  31, 0, 0}, // 1440x480i @ 60 Hz
	{  720,  576, 0, 199500, 200500,   12,  64,  68,  5,  5,  39, 0, 0}, // 720x576 @ 200 Hz
	{  720,  576, 0,  99500, 100500,   12,  64,  68,  5,  5,  39, 0, 0}, // 720x576 @ 100 Hz
	{  720,  576, 0,  49500,  50500,   12,  64,  68,  5,  5,  39, 0, 0}, // 720x576 @ 50 Hz
	{  720,  480, 0, 239500, 240500,   16,  62,  60,  9,  6,  30, 0, 0}, // 720x480 @ 240 Hz
	{  720,  480, 0, 119500, 120500,   16,  62,  60,  9,  6,  30, 0, 0}, // 720x480 @ 120 Hz
	{  720,  480, 0,  59500,  60500,   16,  62,  60,  9,  6,  30, 0, 0}, // 720x480 @ 60 Hz
	{  640,  480, 0,  59500,  60500,   16,  96,  48, 10,  2,  33, 0, 0}, // 640x480 @ 60 Hz
	{0}
};

const DetailedResolutionStruct DetailedResolutionClass::AutomaticCRT[] =
{
	{ 1920, 1440, 0,  74500,  75500,  144, 224, 352,  1,  3,  56, 0, 1}, // 1920x1440 @ 75 Hz
	{ 1920, 1440, 0,  59500,  60500,  128, 208, 344,  1,  3,  56, 0, 1}, // 1920x1440 @ 60 Hz
	{ 1856, 1392, 0,  74500,  75500,  128, 224, 352,  1,  3, 104, 0, 1}, // 1856x1392 @ 75 Hz
	{ 1856, 1392, 0,  59500,  60500,   96, 224, 352,  1,  3,  43, 0, 1}, // 1856x1392 @ 60 Hz
	{ 1792, 1344, 0,  74500,  75500,   96, 216, 352,  1,  3,  69, 0, 1}, // 1792x1344 @ 75 Hz
	{ 1792, 1344, 0,  59500,  60500,  128, 200, 328,  1,  3,  46, 0, 1}, // 1792x1344 @ 60 Hz
	{ 1600, 1200, 0,  84500,  85500,   64, 192, 304,  1,  3,  46, 1, 1}, // 1600x1200 @ 85 Hz
	{ 1600, 1200, 0,  74500,  75500,   64, 192, 304,  1,  3,  46, 1, 1}, // 1600x1200 @ 75 Hz
	{ 1600, 1200, 0,  69500,  70500,   64, 192, 304,  1,  3,  46, 1, 1}, // 1600x1200 @ 70 Hz
	{ 1600, 1200, 0,  64500,  65500,   64, 192, 304,  1,  3,  46, 1, 1}, // 1600x1200 @ 65 Hz
	{ 1600, 1200, 0,  59500,  60500,   64, 192, 304,  1,  3,  46, 1, 1}, // 1600x1200 @ 60 Hz
	{ 1280, 1024, 0,  84500,  85500,   64, 160, 224,  1,  3,  44, 1, 1}, // 1280x1024 @ 85 Hz
	{ 1280, 1024, 0,  74500,  75500,   16, 144, 248,  1,  3,  38, 1, 1}, // 1280x1024 @ 75 Hz
	{ 1280, 1024, 0,  59500,  60500,   48, 112, 248,  1,  3,  38, 1, 1}, // 1280x1024 @ 60 Hz
	{ 1280,  960, 0,  84500,  85500,   64, 160, 224,  1,  3,  47, 1, 1}, // 1280x960 @ 85 Hz
	{ 1280,  960, 0,  59500,  60500,   96, 112, 312,  1,  3,  36, 1, 1}, // 1280x960 @ 60 Hz
	{ 1152,  864, 0,  74500,  75500,   64, 128, 256,  1,  3,  32, 1, 1}, // 1152x864 @ 75 Hz
	{ 1024,  768, 0,  84500,  85500,   48,  96, 208,  1,  3,  36, 1, 1}, // 1024x768 @ 85 Hz
	{ 1024,  768, 0,  74500,  75500,   16,  96, 176,  1,  3,  28, 1, 1}, // 1024x768 @ 75 Hz
	{ 1024,  768, 0,  69500,  70500,   24, 136, 144,  3,  6,  29, 0, 0}, // 1024x768 @ 70 Hz
	{ 1024,  768, 0,  59500,  60500,   24, 136, 160,  3,  6,  29, 0, 0}, // 1024x768 @ 60 Hz
	{  800,  600, 0,  84500,  85500,   32,  64, 152,  1,  3,  27, 1, 1}, // 800x600 @ 85 Hz
	{  800,  600, 0,  74500,  75500,   16,  80, 160,  1,  3,  21, 1, 1}, // 800x600 @ 75 Hz
	{  800,  600, 0,  71500,  72500,   56, 120,  64, 37,  6,  23, 1, 1}, // 800x600 @ 72 Hz
	{  800,  600, 0,  59500,  60500,   40, 128,  88,  1,  4,  23, 1, 1}, // 800x600 @ 60 Hz
	{  800,  600, 0,  55500,  56500,   24,  72, 128,  1,  2,  22, 1, 1}, // 800x600 @ 56 Hz
	{ 1440,  576, 1,  49500,  50500,   24, 126, 138,  4,  6,  39, 0, 0}, // 1440x576i @ 50 Hz
	{ 1440,  480, 1,  59500,  60500,   38, 124, 114,  8,  6,  31, 0, 0}, // 1440x480i @ 60 Hz
	{  720,  576, 0,  49500,  50500,   12,  64,  68,  5,  5,  39, 0, 0}, // 720x576 @ 50 Hz
	{  720,  480, 0,  59500,  60500,   16,  62,  60,  9,  6,  30, 0, 0}, // 720x480 @ 60 Hz
	{  640,  480, 0,  84500,  85500,   56,  56,  80,  1,  3,  25, 0, 0}, // 640x480 @ 85 Hz
	{  640,  480, 0,  74500,  75500,   16,  64, 120,  1,  3,  16, 0, 0}, // 640x480 @ 75 Hz
	{  640,  480, 0,  71500,  72500,   24,  40, 128,  9,  3,  28, 0, 0}, // 640x480 @ 72 Hz
	{  640,  480, 0,  59500,  60500,   16,  96,  48, 10,  2,  33, 0, 0}, // 640x480 @ 60 Hz
	{0}
};

const DetailedResolutionStruct DetailedResolutionClass::Native[] =
{
	{ 1920, 1080, 0,  60000}, // 1920x1080 @ 60 Hz
	{ 1920, 1080, 1,  60000}, // 1920x1080i @ 60 Hz
	{ 1600,  900, 0,  60000}, // 1600x900 @ 60 Hz
	{ 1366,  768, 0,  59789}, // 1366x768 @ 60 Hz
	{ 1360,  768, 0,  60015}, // 1360x768 @ 60 Hz
	{ 1280,  720, 0,  60000}, // 1280x720 @ 60 Hz
	{ 1440,  576, 1,  50000}, // 1440x576i @ 50 Hz
	{ 1440,  480, 1,  59940}, // 1440x480i @ 60 Hz
	{  720,  576, 0,  50000}, // 720x576 @ 50 Hz
	{  720,  480, 0,  59940}, // 720x480 @ 60 Hz
	{  640,  480, 0,  60000}, // 640x480 @ 60 Hz
	{0}
};

// {0.98, 1.02, VSync} * VActive * 4000 / HActive
const int DetailedResolutionClass::AspectVSync[][3] =
{
	{2205, 2295, 5}, // 2250 (16:9)
	{2352, 2448, 7}, // 2400 (15:9)
	{2450, 2550, 6}, // 2500 (16:10)
	{2940, 3060, 4}, // 3000 (4:3)
	{3136, 3264, 7}, // 3200 (5:4)
	{0}
};

const int DetailedResolutionClass::C = 40;
const int DetailedResolutionClass::J = 20;
const int DetailedResolutionClass::K = 128;
const int DetailedResolutionClass::M = 600;

const int DetailedResolutionClass::CPrime = (C - J) * K / 256 + J;
const int DetailedResolutionClass::MPrime = M * K / 256;

const int DetailedResolutionClass::MinTimeCVT = 550000000;
const int DetailedResolutionClass::MinTimeCVTRB = 460000000;
const int DetailedResolutionClass::MinTimeCVTRB2 = 460000000;
const int DetailedResolutionClass::MinTimeGTF = 550000000;

const int DetailedResolutionClass::MinHActive[] = {1, 1, 1};
const int DetailedResolutionClass::MaxHActive[] = {4095, 65536, 65536};
const int DetailedResolutionClass::MinHFront[] = {1, 1, 1};
const int DetailedResolutionClass::MaxHFront[] = {1023, 32768, 32768};
const int DetailedResolutionClass::MinHSync[] = {1, 1, 1};
const int DetailedResolutionClass::MaxHSync[] = {1023, 65536, 65536};
const int DetailedResolutionClass::MinHBack[] = {0, 0, 0};
const int DetailedResolutionClass::MaxHBlank[] = {4095, 65536, 65536};

const int DetailedResolutionClass::MinVActive[] = {1, 1, 1};
const int DetailedResolutionClass::MaxVActive[] = {4095, 65536, 65536};
const int DetailedResolutionClass::MinVFront[] = {1, 1, 1};
const int DetailedResolutionClass::MaxVFront[] = {63, 32768, 32768};
const int DetailedResolutionClass::MinVSync[] = {1, 1, 1};
const int DetailedResolutionClass::MaxVSync[] = {63, 65536, 65536};
const int DetailedResolutionClass::MinVBack[] = {0, 0, 0};
const int DetailedResolutionClass::MaxVBlank[] = {4095, 65536, 65536};

const long long DetailedResolutionClass::MinPClock[] = {1, 1, 1};
const long long DetailedResolutionClass::MaxPClock[] = {65535, 16777216, 16777216};
const int DetailedResolutionClass::PClockPrecision[] = {100, 100, 1000};

const bool DetailedResolutionClass::BordersAvailable[] = {true, false, false};
const bool DetailedResolutionClass::InterlacedAvailable[] = {true, true, true};
const bool DetailedResolutionClass::PreferredAvailable[] = {false, true, true};

bool DetailedResolutionClass::Copied;
int DetailedResolutionClass::CopyType;
int DetailedResolutionClass::CopyHActive;
int DetailedResolutionClass::CopyHFront;
int DetailedResolutionClass::CopyHSync;
int DetailedResolutionClass::CopyHBlank;
int DetailedResolutionClass::CopyVActive;
int DetailedResolutionClass::CopyVFront;
int DetailedResolutionClass::CopyVSync;
int DetailedResolutionClass::CopyVBlank;
int DetailedResolutionClass::CopyHBorder;
int DetailedResolutionClass::CopyVBorder;
bool DetailedResolutionClass::CopyHPolarity;
bool DetailedResolutionClass::CopyVPolarity;
int DetailedResolutionClass::CopyStereo;
long long DetailedResolutionClass::CopyPClock;
bool DetailedResolutionClass::CopyInterlaced;
bool DetailedResolutionClass::CopyPreferred;
//---------------------------------------------------------------------------
DetailedResolutionClass::DetailedResolutionClass(int NewType)
{
	Type = 0;
	Timing = 0;
	Last = 0;
	HActive = 1024;
	VActive = 768;
	HBorder = 0;
	VBorder = 0;
	Stereo = 0;
	LastRate = 0;
	VRate = 60000;
	Interlaced = false;
	Fields = Interlaced + 1;
	Preferred = false;
	CalculateAutomaticCRT();
	UpdateReset();
	SetType(NewType);
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::Read(const unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	switch (Type)
	{
		case 0:
			if (MaxSize < 18)
				return false;

			if (Data[0] == 0 && Data[1] == 0)
				return false;

			HActive = ((Data[4] << 4) & 3840) | Data[2];
			HFront = ((Data[11] << 2) & 768) | Data[8];
			HSync = ((Data[11] << 4) & 768) | Data[9];
			HBlank = ((Data[4] << 8) & 3840) | Data[3];
			VActive = ((Data[7] << 4) & 3840) | Data[5];
			VFront = ((Data[11] << 2) & 48) | ((Data[10] >> 4) & 15);
			VSync = ((Data[11] << 4) & 48) | (Data[10] & 15);
			VBlank = ((Data[7] << 8) & 3840) | Data[6];
			HBorder = Data[15];
			VBorder = Data[16];
			HPolarity = Data[17] & 2;
			VPolarity = Data[17] & 4;
			Stereo = Data[17] & 97;

			if (Stereo == 1)
				Stereo = 0;

			ActualPClock = (Data[1] << 8) | Data[0];
			Interlaced = Data[17] & 128;
			Fields = Interlaced + 1;
			Preferred = false;

			if (Interlaced)
			{
				VActive *= 2;
				VFront *= 2;
				VSync *= 2;
				VBlank *= 2;
				VBlank++;
			}

			break;

		case 1:
		case 2:
			if (MaxSize < 20)
				return false;

			HActive = ((Data[5] << 8) | Data[4]) + 1;
			HFront = (((Data[9] & 127) << 8) | Data[8]) + 1;
			HSync = ((Data[11] << 8) | Data[10]) + 1;
			HBlank = ((Data[7] << 8) | Data[6]) + 1;
			VActive = ((Data[13] << 8) | Data[12]) + 1;
			VFront = (((Data[17] & 127) << 8) | Data[16]) + 1;
			VSync = ((Data[19] << 8) | Data[18]) + 1;
			VBlank = ((Data[15] << 8) | Data[14]) + 1;
			HBorder = 0;
			VBorder = 0;
			HPolarity = Data[9] & 128;
			VPolarity = Data[17] & 128;
			Stereo = Data[3] & 96;
			ActualPClock = ((Data[2] << 16) | (Data[1] << 8) | Data[0]) + 1;
			Interlaced = Data[3] & 16;
			Fields = Interlaced + 1;
			Preferred = Data[3] & 128;
			break;
	}

	Init();
	UpdateReset();
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::Init()
{
	CalculateHBack();
	CalculateHTotal();
	CalculateVBack();
	CalculateVTotal();
	CalculateActualVRate();
	CalculateActualHRate();
	VRate = (ActualVRate + 500) / 1000 * 1000;
	HRate = ActualHRate;
	PClock = ActualPClock;
	CalculateActualPClockFromVRate();

	if (ActualPClock != PClock)
	{
		if (VRate % 24000 == 0 || VRate % 30000 == 0)
		{
			VRate = VRate * 1000 / 1001;
			CalculateActualPClockFromVRate();
		}
	}

	if (ActualPClock != PClock)
	{
		VRate = (ActualVRate + 50) / 100 * 100;
		CalculateActualPClockFromVRate();
	}

	if (ActualPClock != PClock)
	{
		VRate = ActualVRate;
		ActualPClock = PClock;
	}

	UpdateInterlaced();
	UpdateInterlacedRate();
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::Write(unsigned char *Data, int MaxSize)
{
	if (!Data)
		return false;

	if (!IsValid())
		return false;

	switch (Type)
	{
		case 0:
			if (MaxSize < 18)
				return false;

			if (Interlaced)
			{
				VActive /= 2;
				VFront /= 2;
				VSync /= 2;
				VBlank /= 2;
			}

			Data[0] = ActualPClock & 255;
			Data[1] = (ActualPClock >> 8) & 255;
			Data[2] = HActive & 255;
			Data[3] = HBlank & 255;
			Data[4] = ((HActive & 3840) >> 4) | ((HBlank & 3840) >> 8);
			Data[5] = VActive & 255;
			Data[6] = VBlank & 255;
			Data[7] = ((VActive & 3840) >> 4) | ((VBlank & 3840) >> 8);
			Data[8] = HFront & 255;
			Data[9] = HSync & 255;
			Data[10] = ((VFront & 15) << 4) | (VSync & 15);
			Data[11] = ((HFront & 768) >> 2) | ((HSync & 768) >> 4) | ((VFront & 48) >> 2) | ((VSync & 48) >> 4);
			Data[12] = (HActive >> 2) & 255;
			Data[13] = (VActive >> 2) & 255;
			Data[14] = (((HActive >> 2) & 3840) >> 4) | (((VActive >> 2) & 3840) >> 8);
			Data[15] = HBorder;
			Data[16] = VBorder;
			Data[17] = (HPolarity ? 2 : 0) | (VPolarity ? 4 : 0) | 8 | 16 | Stereo | (Interlaced ? 128 : 0);

			if (Interlaced)
			{
				VActive *= 2;
				VFront *= 2;
				VSync *= 2;
				VBlank *= 2;
				VBlank++;
			}

			break;

		case 1:
		case 2:
			if (MaxSize < 20)
				return false;

			Data[0] = --ActualPClock & 255;
			Data[1] = (ActualPClock >> 8) & 255;
			Data[2] = (ActualPClock++ >> 16) & 255;
			Data[3] = (Interlaced ? 16 : 0) | Stereo | (Preferred ? 128 : 0);
			Data[4] = --HActive & 255;
			Data[5] = (HActive++ >> 8) & 255;
			Data[6] = --HBlank & 255;
			Data[7] = (HBlank++ >> 8) & 255;
			Data[8] = --HFront & 255;
			Data[9] = (HFront++ >> 8) & 127;
			Data[9] |= HPolarity ? 128 : 0;
			Data[10] = --HSync & 255;
			Data[11] = (HSync++ >> 8) & 255;
			Data[12] = --VActive & 255;
			Data[13] = (VActive++ >> 8) & 255;
			Data[14] = --VBlank & 255;
			Data[15] = (VBlank++ >> 8) & 255;
			Data[16] = --VFront & 255;
			Data[17] = (VFront++ >> 8) & 127;
			Data[17] |= VPolarity ? 128 : 0;
			Data[18] = --VSync & 255;
			Data[19] = (VSync++ >> 8) & 255;
			break;
	}

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::GetText(char *Text, int TextSize, const char *Dash)
{
	if (!IsValid())
		return false;

	std::snprintf(Text, TextSize, "%dx%d%s%s @ %lld.%03lld Hz (%lld.%0*lld MHz) [%s/%s]%s%s", HActive - HBorder * 2, VActive - VBorder * Fields * 2, Interlaced ? "i" : "", HBorder || VBorder ? "*" : "", ActualVRate / 1000, ActualVRate % 1000, ActualPClock / PClockPrecision[Type], GetPClockDigits(), ActualPClock % PClockPrecision[Type], HPolarity ? "+" : Dash, VPolarity ? "+" : Dash, Stereo ? " (3D)" : "", Preferred ? "*" : "");
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::SetType(int NewType)
{
	int OldType = Type;

	switch (NewType)
	{
		case 1:
			Type = 1;
			break;

		case 7:
			Type = 2;
			break;

		default:
			Type = 0;
			break;
	}

	if (ActualPClock != DECIMAL_BLANK)
	{
		ActualPClock = ActualPClock * PClockPrecision[Type] / PClockPrecision[OldType];
		ResetPClock = ResetPClock * PClockPrecision[Type] / PClockPrecision[OldType];
	}

	Init();
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::GetTimingText(int Timing, char *Text, int TextSize)
{
	if (Timing < MinTiming || Timing > MaxTiming)
		return false;

	std::snprintf(Text, TextSize, "%s", TimingText[Timing]);
	return true;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetTiming()
{
	if (!IsValidTiming())
		return -1;

	return Timing;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::SetTiming(int Value)
{
	if (Timing == TIMING_MANUAL_VTOTAL && Value == TIMING_MANUAL)
		PClock = ActualPClock;

	Timing = Value;
	Update();
	UpdateInterlaced();
	UpdateInterlacedRate();
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CopyPossible()
{
	if (!IsSupported())
		return false;

	if (!Copied)
		return true;

	if (CopyHActive == HActive)
	if (CopyHFront == HFront)
	if (CopyHSync == HSync)
	if (CopyHBlank == HBlank)
	if (CopyVActive == VActive)
	if (CopyVFront == VFront)
	if (CopyVSync == VSync)
	if (CopyVBlank == VBlank)
	if (CopyHBorder == HBorder)
	if (CopyVBorder == VBorder)
	if (CopyHPolarity == HPolarity)
	if (CopyVPolarity == VPolarity)
	if (CopyType == Type ? CopyStereo == Stereo : !CopyStereo && !Stereo)
	if (CopyPClock == ActualPClock * 1000 / PClockPrecision[Type])
	if (CopyInterlaced == Interlaced)
	if (CopyPreferred == Preferred)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::Copy()
{
	if (!IsSupported())
		return false;

	Copied = true;
	CopyType = Type;
	CopyHActive = HActive;
	CopyHFront = HFront;
	CopyHSync = HSync;
	CopyHBlank = HBlank;
	CopyVActive = VActive;
	CopyVFront = VFront;
	CopyVSync = VSync;
	CopyVBlank = VBlank;
	CopyHBorder = HBorder;
	CopyVBorder = VBorder;
	CopyHPolarity = HPolarity;
	CopyVPolarity = VPolarity;
	CopyStereo = Stereo;
	CopyPClock = ActualPClock * 1000 / PClockPrecision[Type];
	CopyInterlaced = Interlaced;
	CopyPreferred = Preferred;
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::PasteInterlacedPossible()
{
	if (Type == CopyType)
		return true;

	if (CopyVActive % 2 == 0)
	if (CopyVSync % 2 == 0)
	if (CopyVBlank % 2 != 0)
		return true;

	return false;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::PasteStereoPossible()
{
	if (Type == CopyType)
		return true;

	if (!CopyStereo)
		return true;

	return false;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::PastePossible()
{
	if (!Copied)
		return false;

	if (CopyInterlaced && !PasteInterlacedPossible())
		return false;

	if (HActive == CopyHActive)
	if (HFront == CopyHFront)
	if (HSync == CopyHSync)
	if (HBlank == CopyHBlank)
	if (GetValue(VActive) == GetValue(CopyVActive))
	if (GetValue(VFront) == GetValue(CopyVFront))
	if (GetValue(VSync) == GetValue(CopyVSync))
	if (GetValue(VBlank) == GetValue(CopyVBlank))
	if (HBorder == CopyHBorder || !BordersAvailable[Type])
	if (VBorder == CopyVBorder || !BordersAvailable[Type])
	if (HPolarity == CopyHPolarity)
	if (VPolarity == CopyVPolarity)
	if (Stereo == CopyStereo || !PasteStereoPossible())
	if (ActualPClock == (CopyPClock * PClockPrecision[Type] + 999) / 1000)
	if (Interlaced == CopyInterlaced || !InterlacedAvailable[Type])
	if (Preferred == CopyPreferred || !PreferredAvailable[Type])
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::Paste()
{
	if (!Copied)
		return false;

	Timing = 0;
	HActive = CopyHActive;
	HFront = CopyHFront;
	HSync = CopyHSync;
	HBlank = CopyHBlank;

	if (CopyInterlaced && Type == 0)
	{
		VActive = CopyVActive / 2 * 2;
		VFront = CopyVFront / 2 * 2;
		VSync = CopyVSync / 2 * 2;
		VBlank = CopyVBlank / 2 * 2 + 1;
	}
	else
	{
		VActive = CopyVActive;
		VFront = CopyVFront;
		VSync = CopyVSync;
		VBlank = CopyVBlank;
	}

	if (BordersAvailable[Type])
	{
		HBorder = CopyHBorder;
		VBorder = CopyVBorder;
	}

	HPolarity = CopyHPolarity;
	VPolarity = CopyVPolarity;
	Stereo = PasteStereoPossible() ? CopyStereo : Stereo;
	ActualPClock = (CopyPClock * PClockPrecision[Type] + 999) / 1000;
	Interlaced = InterlacedAvailable[Type] ? CopyInterlaced : Interlaced;
	Fields = Interlaced + 1;
	Preferred = PreferredAvailable[Type] ? CopyPreferred : Preferred;
	Init();
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::UpdateReset()
{
	ResetHActive = HActive;
	ResetHFront = HFront;
	ResetHSync = HSync;
	ResetHBlank = HBlank;
	ResetVActive = VActive;
	ResetVFront = VFront;
	ResetVSync = VSync;
	ResetVBlank = VBlank;
	ResetHBorder = HBorder;
	ResetVBorder = VBorder;
	ResetHPolarity = HPolarity;
	ResetVPolarity = VPolarity;
	ResetStereo = Stereo;
	ResetPClock = ActualPClock;
	ResetInterlaced = Interlaced;
	ResetPreferred = Preferred;
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::ResetPossible()
{
	if (HActive == ResetHActive)
	if (HFront == ResetHFront)
	if (HSync == ResetHSync)
	if (HBlank == ResetHBlank)
	if (VActive == ResetVActive)
	if (VFront == ResetVFront)
	if (VSync == ResetVSync)
	if (VBlank == ResetVBlank)
	if (HBorder == ResetHBorder)
	if (VBorder == ResetVBorder)
	if (HPolarity == ResetHPolarity)
	if (VPolarity == ResetVPolarity)
	if (Stereo == ResetStereo)
	if (ActualPClock == ResetPClock)
	if (Interlaced == ResetInterlaced)
	if (Preferred == ResetPreferred)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::Reset()
{
	Timing = 0;
	HActive = ResetHActive;
	HFront = ResetHFront;
	HSync = ResetHSync;
	HBlank = ResetHBlank;
	VActive = ResetVActive;
	VFront = ResetVFront;
	VSync = ResetVSync;
	VBlank = ResetVBlank;
	HBorder = ResetHBorder;
	VBorder = ResetVBorder;
	HPolarity = ResetHPolarity;
	VPolarity = ResetVPolarity;
	Stereo = ResetStereo;
	ActualPClock = ResetPClock;
	Interlaced = ResetInterlaced;
	Fields = Interlaced + 1;
	Preferred = ResetPreferred;
	Init();
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsLast(int Value)
{
	return Value == Last;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetHActive()
{
	return HActive;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetHFront()
{
	return HFront;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetHSync()
{
	return HSync;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetHBack()
{
	return HBack;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetHBlank()
{
	return HBlank;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetHTotal()
{
	return HTotal;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::Positive(int Value)
{
	return Value != BLANK && Value != INVALID && Value >= 0;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetValue(int Value)
{
	if (Interlaced && Type == 0 && Positive(Value))
		return Value / 2;

	return Value;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetVActive()
{
	return GetValue(VActive);
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetVFront()
{
	return GetValue(VFront);
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetVSync()
{
	return GetValue(VSync);
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetVBack()
{
	return GetValue(VBack);
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetVBlank()
{
	return GetValue(VBlank);
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetVTotal()
{
	return GetValue(VTotal);
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::GetHPolarity()
{
	return HPolarity;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::GetVPolarity()
{
	return VPolarity;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::GetVActiveLinesText(char *Text, int TextSize)
{
	if (Interlaced && Type == 0 && IsSupportedVActive())
		std::snprintf(Text, TextSize, "lines = %d", VActive);
	else
		std::snprintf(Text, TextSize, "lines");

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::GetVFrontLinesText(char *Text, int TextSize)
{
	if (Interlaced && Type == 0 && IsSupportedVFront())
		std::snprintf(Text, TextSize, "lines = %d.5", VFront);
	else
		std::snprintf(Text, TextSize, "lines");

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::GetVSyncLinesText(char *Text, int TextSize)
{
	if (Interlaced && Type == 0 && IsSupportedVSync())
		std::snprintf(Text, TextSize, "lines = %d", VSync);
	else
		std::snprintf(Text, TextSize, "lines");

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::GetVBackLinesText(char *Text, int TextSize)
{
	if (Interlaced && Type == 0 && IsSupportedVBack())
		std::snprintf(Text, TextSize, "lines = %d.5", VBack - 1);
	else
		std::snprintf(Text, TextSize, "lines");

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::GetVBlankLinesText(char *Text, int TextSize)
{
	if (Interlaced && Type == 0 && IsSupportedVBlank())
		std::snprintf(Text, TextSize, "lines = %d", VBlank);
	else
		std::snprintf(Text, TextSize, "lines");

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::GetVTotalLinesText(char *Text, int TextSize)
{
	if (Interlaced && Type == 0 && IsSupportedVTotal())
		std::snprintf(Text, TextSize, "lines = %d", VTotal);
	else
		std::snprintf(Text, TextSize, "lines");

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsLastRate(int Value)
{
	if (Timing == TIMING_MANUAL_VTOTAL && LastRate == 1)
		return Value == 2;

	return Value == LastRate;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetVRateDigits()
{
	return 3;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetHRateDigits()
{
	return 3;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetPClockDigits()
{
	return PClockPrecision[Type] == 100 ? 2 : 3;
}
//---------------------------------------------------------------------------
long long DetailedResolutionClass::GetVRate()
{
	return VRate;
}
//---------------------------------------------------------------------------
long long DetailedResolutionClass::GetHRate()
{
	return HRate;
}
//---------------------------------------------------------------------------
long long DetailedResolutionClass::GetPClock()
{
	return PClock;
}
//---------------------------------------------------------------------------
long long DetailedResolutionClass::GetActualVRate()
{
	return ActualVRate;
}
//---------------------------------------------------------------------------
long long DetailedResolutionClass::GetActualHRate()
{
	return ActualHRate;
}
//---------------------------------------------------------------------------
long long DetailedResolutionClass::GetActualPClock()
{
	return ActualPClock;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::GetActualVRateText(char *Text, int TextSize, const char *Dash)
{
	if (ActualVRate != DECIMAL_BLANK)
		std::snprintf(Text, TextSize, "Actual: %lld.%03lld Hz", ActualVRate / 1000, ActualVRate % 1000);
	else
		std::snprintf(Text, TextSize, "Actual: %s Hz", Dash);

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::GetActualHRateText(char *Text, int TextSize, const char *Dash)
{
	if (ActualHRate != DECIMAL_BLANK)
		std::snprintf(Text, TextSize, "Actual: %lld.%03lld kHz", ActualHRate / 1000, ActualHRate % 1000);
	else
		std::snprintf(Text, TextSize, "Actual: %s kHz", Dash);

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::GetActualPClockText(char *Text, int TextSize, const char *Dash)
{
	if (IsSupportedActualPClock())
		std::snprintf(Text, TextSize, "Actual: %lld.%0*lld MHz", ActualPClock / PClockPrecision[Type], GetPClockDigits(), ActualPClock % PClockPrecision[Type]);
	else
		std::snprintf(Text, TextSize, "Actual: %s MHz", Dash);

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::SetLast(int Value)
{
	Last = Value;
	UpdateInterlaced();
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::SetHActive(int Value)
{
	HActive = Value;
	Update();
	UpdateInterlaced();
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::SetHFront(int Value)
{
	HFront = Value;
	Update();
	UpdateInterlaced();
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::SetHSync(int Value)
{
	HSync = Value;
	Update();
	UpdateInterlaced();
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::SetHBack(int Value)
{
	HBack = Value;
	Last = 0;
	Update();
	UpdateInterlaced();
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::SetHBlank(int Value)
{
	HBlank = Value;
	Last = 1;
	Update();
	UpdateInterlaced();
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::SetHTotal(int Value)
{
	HTotal = Value;
	Last = 2;
	Update();
	UpdateInterlaced();
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::SetVActive(int Value)
{
	if (Interlaced && Type == 0 && Positive(Value))
		VActive = Value * 2;
	else
		VActive = Value;

	Update();
	UpdateInterlaced();
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::SetVFront(int Value)
{
	if (Interlaced && Type == 0 && Positive(Value))
		VFront = Value * 2;
	else
		VFront = Value;

	Update();
	UpdateInterlaced();
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::SetVSync(int Value)
{
	if (Interlaced && Type == 0 && Positive(Value))
		VSync = Value * 2;
	else
		VSync = Value;

	Update();
	UpdateInterlaced();
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::SetVBack(int Value)
{
	if (Interlaced && Type == 0 && Positive(Value))
		VBack = Value * 2 + 1;
	else
		VBack = Value;

	Last = 0;
	Update();
	UpdateInterlaced();
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::SetVBlank(int Value)
{
	if (Interlaced && Type == 0 && Positive(Value))
		VBlank = Value * 2 + 1;
	else
		VBlank = Value;

	Last = 1;
	Update();
	UpdateInterlaced();
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::SetVTotal(int Value)
{
	if (Interlaced && Type == 0 && Positive(Value))
		VTotal = Value * 2 + 1;
	else
		VTotal = Value;

	Last = 2;
	Update();
	UpdateInterlaced();
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::SetHPolarity(bool Value)
{
	HPolarity = Value;
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::SetVPolarity(bool Value)
{
	VPolarity = Value;
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::SetLastRate(int Value)
{
	LastRate = Value;

	if (Timing == TIMING_MANUAL_VTOTAL)
		Update();

	UpdateInterlacedRate();
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::SetVRate(long long Value)
{
	VRate = Value;

	if (Timing == 0)
		LastRate = 0;

	Update();
	UpdateInterlacedRate();
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::SetHRate(long long Value)
{
	HRate = Value;

	if (Timing == 0)
		LastRate = 1;

	Update();
	UpdateInterlacedRate();
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::SetPClock(long long Value)
{
	PClock = Value;

	if (Timing == 0)
		LastRate = 2;

	Update();
	UpdateInterlacedRate();
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::InterlacedPossible()
{
	return InterlacedAvailable[Type];
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::GetInterlaced()
{
	return Interlaced;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::SetInterlaced(bool Value)
{
	if (Interlaced == Value)
		return true;

	Interlaced = Value;
	Fields = Interlaced + 1;

	std::swap(VActive, VActiveI);
	std::swap(VFront, VFrontI);
	std::swap(VSync, VSyncI);
	std::swap(VBack, VBackI);
	std::swap(VBlank, VBlankI);
	std::swap(VTotal, VTotalI);
	std::swap(VRate, VRateI);

	Update();
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::PreferredPossible()
{
	return PreferredAvailable[Type];
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::GetPreferred()
{
	return Preferred;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::SetPreferred(bool Value)
{
	Preferred = Value;
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::Update()
{
	if (!IsValidTiming())
		return CalculateManual();

	if (!(this->*TimingFunction[Timing])())
	{
		HFront = BLANK;
		HSync = BLANK;
		HBack = BLANK;
		HBlank = BLANK;
		HTotal = BLANK;
		VFront = BLANK;
		VSync = BLANK;
		VBack = BLANK;
		VBlank = BLANK;
		VTotal = BLANK;
		HRate = DECIMAL_BLANK;
		PClock = DECIMAL_BLANK;
		ActualVRate = DECIMAL_BLANK;
		ActualHRate = DECIMAL_BLANK;
		ActualPClock = DECIMAL_BLANK;
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::UpdateInterlaced()
{
	VActiveI = VActive;
	VFrontI = VFront;
	VSyncI = VSync;
	VBackI = VBack;
	VBlankI = VBlank;
	VTotalI = VTotal;

	if (Interlaced)
	{
		if (VActive == 1080 && VFront == 4 && VSync == 10 && VBack == 31)
		{
			VFrontI = 4;
			VSyncI = 5;
			VBackI = 36;
		}
		else
		{
			if (Positive(VFront))
				VFrontI = VFront / 2;

			if (Positive(VSync))
				VSyncI = VSync / 2;

			if (Positive(VBack))
				VBackI = VBack / 2;

			if (Positive(VBlank))
				VBlankI = VBlank / 2;

			if (Positive(VTotal))
				VTotalI = VTotal / 2;
		}
	}
	else
	{
		if (VActive == 1080 && VFront == 4 && VSync == 5 && VBack == 36)
		{
			VFrontI = 4;
			VSyncI = 10;
			VBackI = 31;
		}
		else
		{
			if (Type == 0 && Positive(VActive))
			{
				if (VActive % 2 != 0 || HActive >= VActive * 2 && VActive != 480 && VActive != 576)
					VActiveI = VActive * 2;
			}

			if (Positive(VFront))
				VFrontI = VFront * 2;

			if (Positive(VSync))
				VSyncI = VSync * 2;

			if (Positive(VBack))
				VBackI = VBack * 2 + 1;

			if (Positive(VBlank))
				VBlankI = VBlank * 2 + 1;

			if (Positive(VTotal))
				VTotalI = VTotal * 2 + 1;
		}
	}

	if (Positive(VFrontI) && Positive(VSyncI) && Positive(VBackI))
		VBlankI = VFrontI + VSyncI + VBackI;

	if (Positive(VActiveI) && Positive(VBlankI))
		VTotalI = VActiveI + VBlankI;

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::UpdateInterlacedRate()
{
	if (IsSupportedVRate() && !Interlaced && VRate < 45000)
		VRateI = VRate * 2;
	else
		VRateI = VRate;

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateManual()
{
	switch (Last)
	{
		case 0:
			CalculateHBlank();
			CalculateHTotal();
			CalculateVBlank();
			CalculateVTotal();
			break;

		case 1:
			CalculateHBack();
			CalculateHTotal();
			CalculateVBack();
			CalculateVTotal();
			break;

		case 2:
			CalculateHBackFromHTotal();
			CalculateHBlank();
			CalculateVBackFromVTotal();
			CalculateVBlank();
			break;
	}

	switch (LastRate)
	{
		case 0:
			CalculateActualPClockFromVRate();
			CalculateActualVRate();
			CalculateActualHRate();
			HRate = ActualHRate;
			PClock = ActualPClock;
			break;

		case 1:
			CalculateActualPClockFromHRate();
			CalculateActualVRate();
			CalculateActualHRate();
			VRate = ActualVRate;
			PClock = ActualPClock;
			break;

		case 2:
			ActualPClock = PClock;
			CalculateActualVRate();
			CalculateActualHRate();
			VRate = ActualVRate;
			HRate = ActualHRate;
			break;
	}

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateManualVTotal()
{
	switch (Last)
	{
		case 0:
			CalculateHBlank();
			CalculateHTotal();
			break;

		case 1:
			CalculateHBack();
			CalculateHTotal();
			break;

		case 2:
			CalculateHBackFromHTotal();
			CalculateHBlank();
			break;
	}

	CalculateVTotalFromFrequencies();
	CalculateVBackFromVTotal();
	CalculateVBlank();

	if (LastRate == 0)
		CalculateActualPClockFromVRate();
	else
		ActualPClock = PClock;

	CalculateActualVRate();
	CalculateActualHRate();
	HRate = ActualHRate;
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateNative(bool Digital)
{
	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return false;

	int Index;

	for (Index = 0; Native[Index].HActive != 0; Index++)
		if (HActive == Native[Index].HActive && VActive == Native[Index].VActive && Interlaced == Native[Index].Interlaced)
			break;

	if (Native[Index].HActive != 0)
	{
		VRate = Native[Index].MinVRate;
		CalculateAutomaticPC();
	}
	else
	{
		VRate = 60000;

		if (Digital || HSync <= 48)
		{
			if (HFront <= 48 || HSync <= 32 || HBack <= 80)
				CalculateAutomaticPC();
			else
				CalculateAutomaticHDTV();
		}
		else
		{
			CalculateCVTStandard();
		}

		int Multiple = PClockPrecision[Type] / 4;
		ActualPClock = ActualPClock / Multiple * Multiple;
	}

	HBorder = 0;
	VBorder = 0;
	Stereo = 0;
	CalculateActualVRate();
	CalculateActualHRate();
	VRate = ActualVRate;
	HRate = ActualHRate;
	PClock = ActualPClock;
	UpdateInterlaced();
	UpdateInterlacedRate();
	UpdateReset();
	return IsSupported();
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateAutomaticPC()
{
	HPolarity = true;
	VPolarity = false;

	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return false;

	int Index;

	for (Index = 0; AutomaticPC[Index].HActive != 0; Index++)
		if (HActive == AutomaticPC[Index].HActive && VActive == AutomaticPC[Index].VActive && Interlaced == AutomaticPC[Index].Interlaced)
			if (VRate >= AutomaticPC[Index].MinVRate && VRate <= AutomaticPC[Index].MaxVRate)
				break;

	if (AutomaticPC[Index].HActive != 0)
	{
		HFront = AutomaticPC[Index].HFront;
		HSync = AutomaticPC[Index].HSync;
		HBack = AutomaticPC[Index].HBack;
		VFront = AutomaticPC[Index].VFront;
		VSync = AutomaticPC[Index].VSync;
		VBack = AutomaticPC[Index].VBack;
		HPolarity = AutomaticPC[Index].HPolarity;
		VPolarity = AutomaticPC[Index].VPolarity;
		CalculateHBlank();
		CalculateHTotal();
		CalculateVBlank();
		CalculateVTotal();
		CalculateActualPClockFromVRate();
		CalculateActualVRate();
		CalculateActualHRate();
		HRate = ActualHRate;
		PClock = ActualPClock;

		if (IsValid() || !IsValidHActive() || !IsValidVActive() || !IsValidActualPClock())
			return IsSupported();
	}

	return CalculateCVTRBStandard();
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateAutomaticHDTV()
{
	HPolarity = true;
	VPolarity = true;

	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return false;

	int Index;

	for (Index = 0; AutomaticHDTV[Index].HActive != 0; Index++)
		if (HActive == AutomaticHDTV[Index].HActive && VActive == AutomaticHDTV[Index].VActive && Interlaced == AutomaticHDTV[Index].Interlaced)
			if (VRate >= AutomaticHDTV[Index].MinVRate && VRate <= AutomaticHDTV[Index].MaxVRate)
				break;

	if (AutomaticHDTV[Index].HActive != 0)
	{
		HFront = AutomaticHDTV[Index].HFront;
		HSync = AutomaticHDTV[Index].HSync;
		HBack = AutomaticHDTV[Index].HBack;
		VFront = AutomaticHDTV[Index].VFront;
		VSync = AutomaticHDTV[Index].VSync;
		VBack = AutomaticHDTV[Index].VBack;
		HPolarity = AutomaticHDTV[Index].HPolarity;
		VPolarity = AutomaticHDTV[Index].VPolarity;
		CalculateHBlank();
		CalculateHTotal();
		CalculateVBlank();
		CalculateVTotal();
		CalculateActualPClockFromVRate();
		CalculateActualVRate();
		CalculateActualHRate();
		HRate = ActualHRate;
		PClock = ActualPClock;

		if (IsValid() || !IsValidHActive() || !IsValidVActive() || !IsValidActualPClock())
			return IsSupported();
	}

	return CalculateCVTRBStandard();
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateAutomaticCRT()
{
	HPolarity = false;
	VPolarity = true;

	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return false;

	int Index;

	for (Index = 0; AutomaticCRT[Index].HActive != 0; Index++)
		if (HActive == AutomaticCRT[Index].HActive && VActive == AutomaticCRT[Index].VActive && Interlaced == AutomaticCRT[Index].Interlaced)
			if (VRate >= AutomaticCRT[Index].MinVRate && VRate <= AutomaticCRT[Index].MaxVRate)
				break;

	if (AutomaticCRT[Index].HActive != 0)
	{
		HFront = AutomaticCRT[Index].HFront;
		HSync = AutomaticCRT[Index].HSync;
		HBack = AutomaticCRT[Index].HBack;
		VFront = AutomaticCRT[Index].VFront;
		VSync = AutomaticCRT[Index].VSync;
		VBack = AutomaticCRT[Index].VBack;
		HPolarity = AutomaticCRT[Index].HPolarity;
		VPolarity = AutomaticCRT[Index].VPolarity;
		CalculateHBlank();
		CalculateHTotal();
		CalculateVBlank();
		CalculateVTotal();
		CalculateActualPClockFromVRate();
		CalculateActualVRate();
		CalculateActualHRate();
		HRate = ActualHRate;
		PClock = ActualPClock;

		if (IsValid() || !IsValidHActive() || !IsValidVActive() || !IsValidActualPClock())
			return IsSupported();
	}

	return CalculateCVTStandard();
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateNativePC()
{
	HPolarity = true;
	VPolarity = false;

	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return false;

	int Index;

	for (Index = 0; Native[Index].HActive != 0; Index++)
		if (HActive == Native[Index].HActive && VActive == Native[Index].VActive && Interlaced == Native[Index].Interlaced)
			break;

	long long OldVRate = VRate;

	if (Native[Index].HActive != 0)
		VRate = Native[Index].MinVRate;
	else
		VRate = 60000;

	CalculateAutomaticPC();
	VRate = OldVRate;
	CalculateActualPClockFromVRate();
	CalculateActualVRate();
	CalculateActualHRate();
	HRate = ActualHRate;
	PClock = ActualPClock;
	return IsSupported();
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateNativeHDTV()
{
	HPolarity = true;
	VPolarity = true;

	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return false;

	int Index;

	for (Index = 0; Native[Index].HActive != 0; Index++)
		if (HActive == Native[Index].HActive && VActive == Native[Index].VActive && Interlaced == Native[Index].Interlaced)
			break;

	long long OldVRate = VRate;

	if (Native[Index].HActive != 0)
		VRate = Native[Index].MinVRate;
	else
		VRate = 60000;

	CalculateAutomaticHDTV();
	VRate = OldVRate;
	CalculateActualPClockFromVRate();
	CalculateActualVRate();
	CalculateActualHRate();
	HRate = ActualHRate;
	PClock = ActualPClock;
	return IsSupported();
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateExact()
{
	HPolarity = ResetHPolarity;
	VPolarity = ResetVPolarity;

	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return false;

	HFront = 48;
	HSync = 32;

	if (Interlaced)
		HTotal = (HActive + HFront + HSync + 160) / 160 * 160;
	else
		HTotal = (HActive + HFront + HSync + 80) / 80 * 80;

	VFront = GetVFrontForCVT();
	VSync = GetVSyncForCVT();

	if (Interlaced)
		VTotal = (VActive + VFront + VSync + 125) / 250 * 250 + 125;
	else
		VTotal = (VActive + VFront + VSync + 125) / 125 * 125;

	CalculateHBackFromHTotal();
	CalculateHBlank();
	CalculateVBackFromVTotal();
	CalculateVBlank();
	CalculateActualPClockFromVRate();
	CalculateActualVRate();
	CalculateActualHRate();
	HRate = ActualHRate;
	PClock = ActualPClock;
	return IsSupported();
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateExactReduced()
{
	HPolarity = ResetHPolarity;
	VPolarity = ResetVPolarity;

	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return false;

	HFront = 48;
	HSync = 32;

	if (Interlaced)
		HTotal = (HActive + HFront + HSync + 160) / 160 * 160;
	else
		HTotal = (HActive + HFront + HSync + 80) / 80 * 80;

	VFront = GetVFrontForCVT();
	VSync = GetVSyncForCVT();

	if (HTotal % 400 == 0 || VRate % 5000 == 0)
	{
		if (Interlaced)
			VTotal = (VActive + VFront + VSync + 25) / 50 * 50 + 25;
		else
			VTotal = (VActive + VFront + VSync + 25) / 25 * 25;
	}
	else
	{
		if (Interlaced)
			VTotal = (VActive + VFront + VSync + 125) / 250 * 250 + 125;
		else
			VTotal = (VActive + VFront + VSync + 125) / 125 * 125;
	}

	CalculateHBackFromHTotal();
	CalculateHBlank();
	CalculateVBackFromVTotal();
	CalculateVBlank();
	CalculateActualPClockFromVRate();

	if (HActive * VActive <= 2048 * 1200 && ActualPClock > 165 * PClockPrecision[Type] && !Interlaced)
	{
		HFront = 24;
		HSync = 32;
		HTotal = (HActive + HFront + HSync + 80) / 80 * 80;
		VFront = GetVFrontForCVT();
		VSync = GetVSyncForCVT();

		if (HTotal % 400 == 0 || VRate % 5000 == 0)
			VTotal = (VActive + VFront + VSync + 25) / 25 * 25;
		else
			VTotal = (VActive + VFront + VSync + 125) / 125 * 125;

		CalculateHBackFromHTotal();
		CalculateHBlank();
		CalculateVBackFromVTotal();
		CalculateVBlank();
		CalculateActualPClockFromVRate();
	}

	CalculateActualVRate();
	CalculateActualHRate();
	HRate = ActualHRate;
	PClock = ActualPClock;
	return IsSupported();
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateExactCRT()
{
	HPolarity = ResetHPolarity;
	VPolarity = ResetVPolarity;

	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return false;

	CalculateCVTStandard();

	if (Interlaced)
	{
		HTotal = (HTotal + 159) / 160 * 160;
		VTotal = (VTotal + 124) / 250 * 250 + 125;
	}
	else
	{
		HTotal = (HTotal + 79) / 80 * 80;
		VTotal = (VTotal + 124) / 125 * 125;
	}

	CalculateHBackFromHTotal();
	CalculateHBlank();
	CalculateVBackFromVTotal();
	CalculateVBlank();
	CalculateActualPClockFromVRate();
	CalculateActualVRate();
	CalculateActualHRate();
	HRate = ActualHRate;
	PClock = ActualPClock;
	return IsSupported();
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateCVTStandard()
{
	HPolarity = false;
	VPolarity = true;

	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return false;

	long long OldVRate = VRate;
	CalculateCVT();
	CalculateActualPClockFromVRate();
	CalculateActualVRate();
	VRate = ActualVRate;
	CalculateCVT();
	CalculateActualPClockFromVRate();
	CalculateActualVRate();
	CalculateActualHRate();
	VRate = OldVRate;
	HRate = ActualHRate;
	PClock = ActualPClock;
	return IsSupported();
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateCVTRBStandard()
{
	HPolarity = true;
	VPolarity = false;

	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return false;

	long long OldVRate = VRate;
	CalculateCVTRB();
	CalculateActualPClockFromVRate();
	CalculateActualVRate();
	VRate = ActualVRate;
	CalculateCVTRB();
	CalculateActualPClockFromVRate();
	CalculateActualVRate();
	CalculateActualHRate();
	VRate = OldVRate;
	HRate = ActualHRate;
	PClock = ActualPClock;
	return IsSupported();
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateCVTRB2Standard()
{
	HPolarity = true;
	VPolarity = false;

	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return false;

	long long OldVRate = VRate;
	CalculateCVTRB2();
	CalculateActualPClockFromVRate();
	CalculateActualVRate();
	VRate = ActualVRate;
	CalculateCVTRB2();
	CalculateActualPClockFromVRate();
	CalculateActualVRate();
	CalculateActualHRate();
	VRate = OldVRate;
	HRate = ActualHRate;
	PClock = ActualPClock;
	return IsSupported();
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateGTFStandard()
{
	HPolarity = false;
	VPolarity = true;

	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return false;

	long long OldVRate = VRate;
	CalculateGTF();
	CalculateActualPClockFromVRate();
	CalculateActualVRate();
	VRate = ActualVRate;
	CalculateGTF();
	CalculateActualPClockFromVRate();
	CalculateActualVRate();
	CalculateActualHRate();
	VRate = OldVRate;
	HRate = ActualHRate;
	PClock = ActualPClock;
	return IsSupported();
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateCVT()
{
	HPolarity = false;
	VPolarity = true;

	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return false;

	HFront = GetHFrontForCVT();
	HSync = GetHSyncForCVT();
	HBack = GetHBackForCVT();
	VFront = GetVFrontForCVT();
	VSync = GetVSyncForCVT();
	VBack = GetVBackForCVT();
	CalculateHBlank();
	CalculateHTotal();
	CalculateVBlank();
	CalculateVTotal();
	CalculateActualPClockForCVT();
	CalculateActualVRate();
	CalculateActualHRate();
	HRate = ActualHRate;
	PClock = ActualPClock;
	return IsSupported();
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateCVTRB()
{
	HPolarity = true;
	VPolarity = false;

	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return false;

	HFront = 48;
	HSync = 32;
	HBack = 80;
	VFront = GetVFrontForCVTRB();
	VSync = GetVSyncForCVTRB();
	VBack = GetVBackForCVTRB();
	CalculateHBlank();
	CalculateHTotal();
	CalculateVBlank();
	CalculateVTotal();
	CalculateActualPClockForCVTRB();
	CalculateActualVRate();
	CalculateActualHRate();
	HRate = ActualHRate;
	PClock = ActualPClock;
	return IsSupported();
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateCVTRB2()
{
	HPolarity = true;
	VPolarity = false;

	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return false;

	HFront = 8;
	HSync = 32;
	HBack = 40;
	VFront = GetVFrontForCVTRB2();
	VSync = GetVSyncForCVTRB2();
	VBack = GetVBackForCVTRB2();
	CalculateHBlank();
	CalculateHTotal();
	CalculateVBlank();
	CalculateVTotal();
	CalculateActualPClockForCVTRB2();
	CalculateActualVRate();
	CalculateActualHRate();
	HRate = ActualHRate;
	PClock = ActualPClock;
	return IsSupported();
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateGTF()
{
	HPolarity = false;
	VPolarity = true;

	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return false;

	HFront = GetHFrontForGTF();
	HSync = GetHSyncForGTF();
	HBack = GetHBackForGTF();
	VFront = GetVFrontForGTF();
	VSync = GetVSyncForGTF();
	VBack = GetVBackForGTF();
	CalculateHBlank();
	CalculateHTotal();
	CalculateVBlank();
	CalculateVTotal();
	CalculateActualPClockForGTF();
	CalculateActualVRate();
	CalculateActualHRate();
	HRate = ActualHRate;
	PClock = ActualPClock;
	return IsSupported();
}
//---------------------------------------------------------------------------
long long DetailedResolutionClass::GetHPeriodForCVT()
{
	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return 0;

	if (VRate == 0)
		return MinTimeCVT;

	return (1000000000000000LL * Fields / VRate - MinTimeCVT * Fields) / (VActive + GetVFrontForCVT() + Interlaced);
}
//---------------------------------------------------------------------------
long long DetailedResolutionClass::GetHPeriodForCVTRB()
{
	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return 0;

	if (VRate == 0)
		return MinTimeCVTRB;

	return (1000000000000000LL * Fields / VRate - MinTimeCVTRB * Fields) / VActive;
}
//---------------------------------------------------------------------------
long long DetailedResolutionClass::GetHPeriodForCVTRB2()
{
	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return 0;

	if (VRate == 0)
		return MinTimeCVTRB2;

	return (1000000000000000LL * Fields / VRate - MinTimeCVTRB2 * Fields) / VActive;
}
//---------------------------------------------------------------------------
long long DetailedResolutionClass::GetHPeriodForGTF()
{
	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return 0;

	if (VRate == 0)
		return MinTimeGTF;

	return (1000000000000000LL * Fields / VRate - MinTimeGTF * Fields) / (VActive + GetVFrontForGTF() + Interlaced);
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetHFrontForCVT()
{
	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return BLANK;

	return GetHBackForCVT() - GetHSyncForCVT();
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetHFrontForGTF()
{
	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return BLANK;

	return GetHBackForGTF() - GetHSyncForGTF();
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetHSyncForCVT()
{
	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return BLANK;

	return (HActive + GetHBlankForCVT()) / 100 * 8;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetHSyncForGTF()
{
	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return BLANK;

	return (HActive + GetHBlankForGTF() + 50) / 100 * 8;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetHBackForCVT()
{
	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return BLANK;

	return GetHBlankForCVT() / 2;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetHBackForGTF()
{
	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return BLANK;

	return GetHBlankForGTF() / 2;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetHBlankForCVT()
{
	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return BLANK;

	long long HPeriod = GetHPeriodForCVT();

	if (HPeriod <= 0)
		return BLANK;

	long long IdealDutyCycle = CPrime * 1000000000LL - MPrime * HPeriod;

	if (IdealDutyCycle < 20000000000LL)
		IdealDutyCycle = 20000000000LL;

	return HActive * IdealDutyCycle / (100000000000LL - IdealDutyCycle) / 16 * 16;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetHBlankForGTF()
{
	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return BLANK;

	long long HPeriod = GetHPeriodForGTF();

	if (HPeriod <= 0)
		return BLANK;

	long long IdealDutyCycle = CPrime * 1000000000LL - MPrime * HPeriod;
/*
	if (IdealDutyCycle < 20000000000LL)
		IdealDutyCycle = 20000000000LL;
*/
	return (HActive * IdealDutyCycle / (100000000000LL - IdealDutyCycle) + 8) / 16 * 16;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetVFrontForCVT()
{
	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return BLANK;

	return 3 * Fields;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetVFrontForCVTRB()
{
	return GetVFrontForCVT();
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetVFrontForCVTRB2()
{
	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return BLANK;

	long long HPeriod = GetHPeriodForCVTRB2();

	if (HPeriod <= 0)
		return BLANK;

	int VBlank = MinTimeCVTRB2 / HPeriod + 1;
	int VFront = VBlank * Fields + Interlaced - GetVSyncForCVTRB2() - GetVBackForCVTRB2();

	if (VFront < 1 * Fields)
		VFront = 1 * Fields;

	return VFront;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetVFrontForGTF()
{
	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return BLANK;

	return 1 * Fields;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetVSyncForCVT()
{
	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return BLANK;

	int Aspect = VActive * 4000 / HActive;

	for (int Index = 0; AspectVSync[Index][0] != 0; Index++)
		if (Aspect >= AspectVSync[Index][0] && Aspect <= AspectVSync[Index][1])
			return AspectVSync[Index][2] * Fields;

	return 10 * Fields;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetVSyncForCVTRB()
{
	return GetVSyncForCVT();
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetVSyncForCVTRB2()
{
	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return BLANK;

	return 8 * Fields;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetVSyncForGTF()
{
	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return BLANK;

	return 3 * Fields;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetVBackForCVT()
{
	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return BLANK;

	long long HPeriod = GetHPeriodForCVT();

	if (HPeriod <= 0)
		return BLANK;

	int VSyncVBack = MinTimeCVT / HPeriod + 1;
	int VBack = VSyncVBack * Fields + Interlaced - GetVSyncForCVT();

	if (VBack < 6 * Fields + Interlaced)
		VBack = 6 * Fields + Interlaced;

	return VBack;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetVBackForCVTRB()
{
	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return BLANK;

	long long HPeriod = GetHPeriodForCVTRB();

	if (HPeriod <= 0)
		return BLANK;

	int VBlank = MinTimeCVTRB / HPeriod + 1;
	int VBack = VBlank * Fields + Interlaced - GetVFrontForCVTRB() - GetVSyncForCVTRB();

	if (VBack < 6 * Fields + Interlaced)
		VBack = 6 * Fields + Interlaced;

	return VBack;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetVBackForCVTRB2()
{
	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return BLANK;

	return 6 * Fields + Interlaced;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetVBackForGTF()
{
	if (!IsSupportedHActive() || !IsSupportedVActive() || !IsSupportedVRate())
		return BLANK;

	long long HPeriod = GetHPeriodForGTF();

	if (HPeriod <= 0)
		return BLANK;

	int VSyncVBack = (MinTimeGTF * 2 / HPeriod + 1) / 2;
	int VBack = VSyncVBack * Fields + Interlaced - GetVSyncForGTF();
/*
	if (VBack < 6 * Fields + Interlaced)
		VBack = 6 * Fields + Interlaced;
*/
	return VBack;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateHBack()
{
	if (!IsSupportedHBlank() || !IsSupportedHFront() || !IsSupportedHSync())
	{
		HBack = BLANK;
		return false;
	}

	HBack = HBlank - HFront - HSync;

	if (!IsSupportedHBack())
	{
		HBack = BLANK;
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateHBackFromHTotal()
{
	if (!IsSupportedHTotal() || !IsSupportedHActive() || !IsSupportedHFront() || !IsSupportedHSync())
	{
		HBack = BLANK;
		return false;
	}

	HBack = HTotal - HActive - HFront - HSync;

	if (!IsSupportedHBack())
	{
		HBack = BLANK;
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateHBlank()
{
	if (!IsSupportedHFront() || !IsSupportedHSync() || !IsSupportedHBack())
	{
		HBlank = BLANK;
		return false;
	}

	HBlank = HFront + HSync + HBack;

	if (!IsSupportedHBlank())
	{
		HBlank = BLANK;
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateHTotal()
{
	if (!IsSupportedHActive() || !IsSupportedHFront() || !IsSupportedHSync() || !IsSupportedHBack())
	{
		HTotal = BLANK;
		return false;
	}

	HTotal = HActive + HFront + HSync + HBack;

	if (!IsSupportedHTotal())
	{
		HTotal = BLANK;
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateVBack()
{
	if (!IsSupportedVBlank() || !IsSupportedVFront() || !IsSupportedVSync())
	{
		VBack = BLANK;
		return false;
	}

	VBack = VBlank - VFront - VSync;

	if (!IsSupportedVBack())
	{
		VBack = BLANK;
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateVBackFromVTotal()
{
	if (!IsSupportedVTotal() || !IsSupportedVActive() || !IsSupportedVFront() || !IsSupportedVSync())
	{
		VBack = BLANK;
		return false;
	}

	VBack = VTotal - VActive - VFront - VSync;

	if (!IsSupportedVBack())
	{
		VBack = BLANK;
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateVBlank()
{
	if (!IsSupportedVFront() || !IsSupportedVSync() || !IsSupportedVBack())
	{
		VBlank = BLANK;
		return false;
	}

	VBlank = VFront + VSync + VBack;

	if (!IsSupportedVBlank())
	{
		VBlank = BLANK;
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateVTotal()
{
	if (!IsSupportedVActive() || !IsSupportedVFront() || !IsSupportedVSync() || !IsSupportedVBack())
	{
		VTotal = BLANK;
		return false;
	}

	VTotal = VActive + VFront + VSync + VBack;

	if (!IsSupportedVTotal())
	{
		VTotal = BLANK;
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateVTotalFromFrequencies()
{
	if (!IsSupportedPClock() || !IsSupportedHTotal() || !IsSupportedVRate())
	{
		VTotal = BLANK;
		return false;
	}

	long long Value = PClock * GetVRateDivisor() / HTotal / VRate;

	if (Interlaced && Value % 2 == 0)
		Value--;

	if (GetValue(Value) < GetMinVTotal(1) || GetValue(Value) > GetMaxVTotal(1))
	{
		VTotal = BLANK;
		return false;
	}

	VTotal = Value;
	return true;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetVRateDivisor()
{
	return 1000000000 * Fields / PClockPrecision[Type];
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetHRateDivisor()
{
	return 1000000 / PClockPrecision[Type];
}
//---------------------------------------------------------------------------
long long DetailedResolutionClass::GetVRateLimit(int Subtract)
{
	return (LLONG_MAX - Subtract) / HTotal / VTotal;
}
//---------------------------------------------------------------------------
long long DetailedResolutionClass::GetHRateLimit(int Subtract)
{
	return (LLONG_MAX - Subtract) / HTotal;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateActualVRate()
{
	if (!IsSupportedActualPClock() || !IsSupportedHTotal() || !IsSupportedVTotal())
	{
		ActualVRate = DECIMAL_BLANK;
		return false;
	}

	ActualVRate = ActualPClock * GetVRateDivisor() / HTotal / VTotal;
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateActualHRate()
{
	if (!IsSupportedActualPClock() || !IsSupportedHTotal())
	{
		ActualHRate = DECIMAL_BLANK;
		return false;
	}

	ActualHRate = ActualPClock * GetHRateDivisor() / HTotal;
	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateActualPClockForCVT()
{
	if (!IsSupportedVRate() || !IsSupportedHTotal() || !IsSupportedVTotal())
	{
		ActualPClock = DECIMAL_BLANK;
		return false;
	}

	long long HPeriod = GetHPeriodForCVT();

	if (HPeriod <= 0)
	{
		ActualPClock = DECIMAL_BLANK;
		return false;
	}

	long long Multiplier = 1000000LL * PClockPrecision[Type];
	int Multiple = PClockPrecision[Type] / 4;
	ActualPClock = HTotal * Multiplier / HPeriod / Multiple * Multiple;

	if (!IsSupportedActualPClock())
	{
		ActualPClock = DECIMAL_BLANK;
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateActualPClockForCVTRB()
{
	if (!IsSupportedVRate() || !IsSupportedHTotal() || !IsSupportedVTotal())
	{
		ActualPClock = DECIMAL_BLANK;
		return false;
	}

	if (VRate > GetVRateLimit())
	{
		ActualPClock = DECIMAL_BLANK;
		return false;
	}

	int Multiple = PClockPrecision[Type] / 4;
	ActualPClock = VRate * HTotal * VTotal / GetVRateDivisor() / Multiple * Multiple;

	if (!IsSupportedActualPClock())
	{
		ActualPClock = DECIMAL_BLANK;
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateActualPClockForCVTRB2()
{
	if (!IsSupportedVRate() || !IsSupportedHTotal() || !IsSupportedVTotal())
	{
		ActualPClock = DECIMAL_BLANK;
		return false;
	}

	if (VRate > GetVRateLimit())
	{
		ActualPClock = DECIMAL_BLANK;
		return false;
	}

	ActualPClock = VRate * HTotal * VTotal / GetVRateDivisor();

	if (!IsSupportedActualPClock())
	{
		ActualPClock = DECIMAL_BLANK;
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateActualPClockForGTF()
{
	if (!IsSupportedVRate() || !IsSupportedHTotal() || !IsSupportedVTotal())
	{
		ActualPClock = DECIMAL_BLANK;
		return false;
	}

	int Divisor = GetVRateDivisor();

	if (VRate > GetVRateLimit(Divisor / 2))
	{
		ActualPClock = DECIMAL_BLANK;
		return false;
	}

	ActualPClock = (VRate * HTotal * VTotal + Divisor / 2) / Divisor;

	if (!IsSupportedActualPClock())
	{
		ActualPClock = DECIMAL_BLANK;
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateActualPClockFromVRate()
{
	if (!IsSupportedVRate() || !IsSupportedHTotal() || !IsSupportedVTotal())
	{
		ActualPClock = DECIMAL_BLANK;
		return false;
	}

	if (VRate == 0)
	{
		ActualPClock = 1;
		return true;
	}

	int Divisor = GetVRateDivisor();

	if (VRate > GetVRateLimit(Divisor - 1))
	{
		ActualPClock = DECIMAL_BLANK;
		return false;
	}

	ActualPClock = (VRate * HTotal * VTotal + (Divisor - 1)) / Divisor;

	if (!IsSupportedActualPClock())
	{
		ActualPClock = DECIMAL_BLANK;
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::CalculateActualPClockFromHRate()
{
	if (!IsSupportedHRate() || !IsSupportedHTotal())
	{
		ActualPClock = DECIMAL_BLANK;
		return false;
	}

	if (HRate == 0)
	{
		ActualPClock = 1;
		return true;
	}

	int Divisor = GetHRateDivisor();

	if (HRate > GetHRateLimit(Divisor - 1))
	{
		ActualPClock = DECIMAL_BLANK;
		return false;
	}

	ActualPClock = (HRate * HTotal + (Divisor - 1)) / Divisor;

	if (!IsSupportedActualPClock())
	{
		ActualPClock = DECIMAL_BLANK;
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsValid()
{
	if (IsValidHActive())
	if (IsValidHFront())
	if (IsValidHSync())
	if (IsValidHBack())
	if (IsValidHBlank())
	if (IsValidHTotal())
	if (IsValidVActive())
	if (IsValidVFront())
	if (IsValidVSync())
	if (IsValidVBack())
	if (IsValidVBlank())
	if (IsValidVTotal())
	if (IsValidActualPClock())
		return true;

	return false;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsValidTiming()
{
	return Timing >= MinTiming && Timing <= MaxTiming;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsValidHActive()
{
	return HActive >= MinHActive[Type] && HActive <= MaxHActive[Type];
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsValidHFront()
{
	return HFront >= MinHFront[Type] && HFront <= MaxHFront[Type];
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsValidHSync()
{
	return HSync >= MinHSync[Type] && HSync <= MaxHSync[Type];
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsValidHBack()
{
	return HBack >= GetMinHBack(Type) && HBack <= GetMaxHBack(Type);
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsValidHBlank()
{
	return HBlank >= GetMinHBlank(Type) && HBlank <= GetMaxHBlank(Type);
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsValidHTotal()
{
	return HTotal >= GetMinHTotal(Type) && HTotal <= GetMaxHTotal(Type);
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsValidVActive()
{
	return GetValue(VActive) >= MinVActive[Type] && GetValue(VActive) <= MaxVActive[Type];
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsValidVFront()
{
	return GetValue(VFront) >= MinVFront[Type] && GetValue(VFront) <= MaxVFront[Type];
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsValidVSync()
{
	return GetValue(VSync) >= MinVSync[Type] && GetValue(VSync) <= MaxVSync[Type];
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsValidVBack()
{
	return GetValue(VBack) >= GetMinVBack(Type) && GetValue(VBack) <= GetMaxVBack(Type);
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsValidVBlank()
{
	return GetValue(VBlank) >= GetMinVBlank(Type) && GetValue(VBlank) <= GetMaxVBlank(Type);
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsValidVTotal()
{
	return GetValue(VTotal) >= GetMinVTotal(Type) && GetValue(VTotal) <= GetMaxVTotal(Type);
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsValidVRate()
{
	switch (Timing)
	{
		case TIMING_MANUAL:
			if (!IsSupportedHTotal() || !IsSupportedVTotal())
				return VRate >= 0;

			return IsValidActualPClock();

		case TIMING_MANUAL_VTOTAL:
			if (!IsSupportedPClock() || !IsSupportedHTotal())
				return VRate > 0;

			return IsValidVTotal();
	}

	if (!IsSupportedHActive() || !IsSupportedVActive())
		return VRate >= 0;

	return IsValid();
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsValidHRate()
{
	if (!IsSupportedHTotal())
		return HRate >= 0;

	return IsValidActualPClock();
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsValidPClock()
{
	return PClock >= MinPClock[Type] && PClock <= MaxPClock[Type];
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsValidActualPClock()
{
	return ActualPClock >= MinPClock[Type] && ActualPClock <= MaxPClock[Type];
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsSupported()
{
	if (IsSupportedHActive())
	if (IsSupportedHFront())
	if (IsSupportedHSync())
	if (IsSupportedHBack())
	if (IsSupportedHBlank())
	if (IsSupportedHTotal())
	if (IsSupportedVActive())
	if (IsSupportedVFront())
	if (IsSupportedVSync())
	if (IsSupportedVBack())
	if (IsSupportedVBlank())
	if (IsSupportedVTotal())
	if (IsSupportedActualPClock())
		return true;

	return false;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsSupportedHActive()
{
	return HActive >= MinHActive[1] && HActive <= MaxHActive[1];
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsSupportedHFront()
{
	return HFront >= MinHFront[1] && HFront <= MaxHFront[1];
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsSupportedHSync()
{
	return HSync >= MinHSync[1] && HSync <= MaxHSync[1];
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsSupportedHBack()
{
	return HBack >= GetMinHBack(1) && HBack <= GetMaxHBack(1);
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsSupportedHBlank()
{
	return HBlank >= GetMinHBlank(1) && HBlank <= GetMaxHBlank(1);
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsSupportedHTotal()
{
	return HTotal >= GetMinHTotal(1) && HTotal <= GetMaxHTotal(1);
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsSupportedVActive()
{
	return GetValue(VActive) >= MinVActive[1] && GetValue(VActive) <= MaxVActive[1];
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsSupportedVFront()
{
	return GetValue(VFront) >= MinVFront[1] && GetValue(VFront) <= MaxVFront[1];
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsSupportedVSync()
{
	return GetValue(VSync) >= MinVSync[1] && GetValue(VSync) <= MaxVSync[1];
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsSupportedVBack()
{
	return GetValue(VBack) >= GetMinVBack(1) && GetValue(VBack) <= GetMaxVBack(1);
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsSupportedVBlank()
{
	return GetValue(VBlank) >= GetMinVBlank(1) && GetValue(VBlank) <= GetMaxVBlank(1);
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsSupportedVTotal()
{
	return GetValue(VTotal) >= GetMinVTotal(1) && GetValue(VTotal) <= GetMaxVTotal(1);
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsSupportedVRate()
{
	if (Timing == TIMING_MANUAL_VTOTAL)
		return VRate > 0;

	return VRate >= 0;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsSupportedHRate()
{
	return HRate >= 0;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsSupportedPClock()
{
	int Multiplier = PClockPrecision[Type] / PClockPrecision[1];
	return PClock >= MinPClock[Type] && PClock <= MaxPClock[1] * Multiplier;
}
//---------------------------------------------------------------------------
bool DetailedResolutionClass::IsSupportedActualPClock()
{
	int Multiplier = PClockPrecision[Type] / PClockPrecision[1];
	return ActualPClock >= MinPClock[Type] && ActualPClock <= MaxPClock[1] * Multiplier;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetMinHBack(int Type)
{
	return MinHBack[Type];
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetMaxHBack(int Type)
{
	int ClampHFront = IsValidHFront() ? HFront : MinHFront[Type];
	int ClampHSync = IsValidHSync() ? HSync : MinHSync[Type];
	return MaxHBlank[Type] - ClampHFront - ClampHSync;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetMinHBlank(int Type)
{
	int ClampHFront = IsValidHFront() ? HFront : MinHFront[Type];
	int ClampHSync = IsValidHSync() ? HSync : MinHSync[Type];
	return ClampHFront + ClampHSync + MinHBack[Type];
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetMaxHBlank(int Type)
{
	return MaxHBlank[Type];
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetMinHTotal(int Type)
{
	int ClampHActive = IsValidHActive() ? HActive : MinHActive[Type];
	int ClampHFront = IsValidHFront() ? HFront : MinHFront[Type];
	int ClampHSync = IsValidHSync() ? HSync : MinHSync[Type];
	return ClampHActive + ClampHFront + ClampHSync + MinHBack[Type];
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetMaxHTotal(int Type)
{
	int ClampHActive = IsValidHActive() ? HActive : MaxHActive[Type];
	return ClampHActive + MaxHBlank[Type];
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetMinVBack(int Type)
{
	return MinVBack[Type];
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetMaxVBack(int Type)
{
	int ClampVFront = IsValidVFront() ? GetValue(VFront) : MinVFront[Type];
	int ClampVSync = IsValidVSync() ? GetValue(VSync) : MinVSync[Type];
	return MaxVBlank[Type] - ClampVFront - ClampVSync;
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetMinVBlank(int Type)
{
	int ClampVFront = IsValidVFront() ? GetValue(VFront) : MinVFront[Type];
	int ClampVSync = IsValidVSync() ? GetValue(VSync) : MinVSync[Type];
	return ClampVFront + ClampVSync + MinVBack[Type];
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetMaxVBlank(int Type)
{
	return MaxVBlank[Type];
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetMinVTotal(int Type)
{
	int ClampVActive = IsValidVActive() ? GetValue(VActive) : MinVActive[Type];
	int ClampVFront = IsValidVFront() ? GetValue(VFront) : MinVFront[Type];
	int ClampVSync = IsValidVSync() ? GetValue(VSync) : MinVSync[Type];
	return ClampVActive + ClampVFront + ClampVSync + MinVBack[Type];
}
//---------------------------------------------------------------------------
int DetailedResolutionClass::GetMaxVTotal(int Type)
{
	int ClampVActive = IsValidVActive() ? GetValue(VActive) : MaxVActive[Type];
	return ClampVActive + MaxVBlank[Type];
}
//---------------------------------------------------------------------------
