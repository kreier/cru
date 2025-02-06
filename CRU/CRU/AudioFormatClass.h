//---------------------------------------------------------------------------
#ifndef AudioFormatClassH
#define AudioFormatClassH
//---------------------------------------------------------------------------
#include "ItemClass.h"
//---------------------------------------------------------------------------
enum
{
	AUDIO_NONE,
	AUDIO_BIT_DEPTHS,
	AUDIO_BIT_RATE,
	AUDIO_FLAGS,
	AUDIO_PROFILE,
	AUDIO_MPEG4,
	AUDIO_MPEG4_H,
	AUDIO_MPEG4_MPS,
	AUDIO_MPEGH_3D,
	AUDIO_EXTENSION_FLAGS,
	AUDIO_EXTENSION,
	AUDIO_INVALID
};
//---------------------------------------------------------------------------
struct AudioFormatStruct
{
	const char *Text;
	int Code;
	int Channels;
	int SampleRates;
	int Type;
};
//---------------------------------------------------------------------------
class AudioFormatClass : public ItemClass
{
private:
	static const AudioFormatStruct Formats[];
	static const char *ChannelsText[];
	static const char *LevelText[];
	static const int MinFormat;
	static const int MaxFormat;
	static const int MinExtension;
	static const int MaxExtension;
	static const int MinChannels;
	static const int MaxChannels;
	static const int MinChannels3D;
	static const int MaxChannels3D;
	static const int MinSampleRate;
	static const int MaxSampleRate;
	static const int MinBitDepth;
	static const int MaxBitDepth;
	static const int MinBitRate;
	static const int MaxBitRate;
	static const int ModBitRate;
	static const int MinFlags;
	static const int MaxFlags;
	static const int MinProfile;
	static const int MaxProfile;
	static const int MinLevel;
	static const int MaxLevel;
	static const int MinExtensionFlags;
	static const int MaxExtensionFlags;

	int Format;
	int Extension;
	int Channels;
	int Channels3D;
	int SampleRates;
	int BitDepths;
	int BitRate;
	int Flags;
	int Profile;
	bool FrameLength960;
	bool FrameLength1024;
	bool SystemH;
	bool ExplicitMPS;
	int Level;
	bool LowComplexity;
	bool Baseline;
	int ExtensionFlags;
	int LastFormat;
	unsigned char OtherFlags[3];

public:
	AudioFormatClass();
	bool Read(const unsigned char *, int);
	bool Write(unsigned char *, int);
	bool GetInfoText(char *, int);
	bool GetFormatText(char *, int);
	bool GetFormatText(int, char *, int);
	int GetFormat();
	bool SetFormat(int);
	int GetExtension();
	bool SetExtension(int);
	int GetType();
	int GetMaxChannels();
	bool GetChannelsText(int, char *, int);
	int GetChannels();
	bool SetChannels(int);
	int GetChannels3D();
	bool SetChannels3D(int);
	int GetSampleRates();
	bool GetSampleRate(int);
	bool SetSampleRate(int, bool);
	bool GetBitDepth(int);
	bool SetBitDepth(int, bool);
	int GetBitRate();
	bool SetBitRate(int);
	int GetFlags();
	bool SetFlags(int);
	int GetProfile();
	bool SetProfile(int);
	bool GetFrameLength960();
	bool SetFrameLength960(bool);
	bool GetFrameLength1024();
	bool SetFrameLength1024(bool);
	bool GetSystemH();
	bool SetSystemH(bool);
	bool GetExplicitMPS();
	bool SetExplicitMPS(bool);
	bool GetLevelText(int, char *, int);
	int GetLevel();
	bool SetLevel(int);
	bool GetLowComplexity();
	bool SetLowComplexity(bool);
	bool GetBaseline();
	bool SetBaseline(bool);
	int GetExtensionFlags();
	bool SetExtensionFlags(int);
	bool IsValid();
	bool IsValidFormat();
	bool IsValidExtension();
	bool IsValidChannels();
	bool IsValidChannels3D();
	bool IsValidBitRate();
	bool IsValidFlags();
	bool IsValidProfile();
	bool IsValidLevel();
	bool IsValidExtensionFlags();
	bool IsSupported();
};
//---------------------------------------------------------------------------
#endif
