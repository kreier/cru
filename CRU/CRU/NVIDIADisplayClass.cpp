//---------------------------------------------------------------------------
#include "Common.h"
#pragma hdrstop

#include "NVIDIADisplayClass.h"
//---------------------------------------------------------------------------
#define NVAPI_OK                        0
#define NVAPI_MAX_PHYSICAL_GPUS         64
#define NV_GPU_DISPLAYIDS_VER           ((1 << 16) | sizeof(NV_GPU_DISPLAYIDS))
#define NV_EDID_VER                     ((3 << 16) | sizeof(NV_EDID))
#define NV_EDID_DATA_SIZE               256
//---------------------------------------------------------------------------
struct NV_GPU_DISPLAYIDS
{
	int version;
	int connectorType;
	int displayId;
	int isDynamic : 1;
	int isMultiStreamRootNode : 1;
	int isActive : 1;
	int isCluster : 1;
	int isOSVisible : 1;
	int isWFD : 1;
	int isConnected : 1;
	int reservedInternal : 10;
	int isPhysicallyConnected : 1;
	int reserved : 14;
};

struct NV_EDID
{
	int version;
	unsigned char EDID_Data[NV_EDID_DATA_SIZE];
	int sizeofEDID;
	int edidId;
	int offset;
};
//---------------------------------------------------------------------------
typedef void *(*NVAPI_QUERYINTERFACE)(int);
typedef int (*NVAPI_INITIALIZE)();
typedef int (*NVAPI_ENUMPHYSICALGPUS)(int **, int *);
typedef int (*NVAPI_GPU_GETCONNECTEDDISPLAYIDS)(int *, NV_GPU_DISPLAYIDS *, int *, int);
typedef int (*NVAPI_SYS_GETGPUANDOUTPUTIDFROMDISPLAYID)(int, int **, int *);
typedef int (*NVAPI_GPU_GETEDID)(int *, int, NV_EDID *);
typedef int (*NVAPI_UNLOAD)();
//---------------------------------------------------------------------------
NVAPI_QUERYINTERFACE                    	NvAPI_QueryInterface;
NVAPI_INITIALIZE                        	NvAPI_Initialize;
NVAPI_ENUMPHYSICALGPUS                  	NvAPI_EnumPhysicalGPUs;
NVAPI_GPU_GETCONNECTEDDISPLAYIDS			NvAPI_GPU_GetConnectedDisplayIds;
NVAPI_SYS_GETGPUANDOUTPUTIDFROMDISPLAYID	NvAPI_SYS_GetGpuAndOutputIdFromDisplayId;
NVAPI_GPU_GETEDID                       	NvAPI_GPU_GetEDID;
NVAPI_UNLOAD                            	NvAPI_Unload;
//---------------------------------------------------------------------------
bool NVIDIADisplayClass::LoadEDIDList(EDIDListClass &EDIDList)
{
	HMODULE Library;
	int *GPUList[NVAPI_MAX_PHYSICAL_GPUS];
	int GPUCount;
	int GPUIndex;
	int DisplayCount;
	int DisplayIndex;
	int DisplayID;
	NV_EDID DisplayEDID;
	int EDIDSize;
	int DataSize;
	unsigned char NewDisplayEDID[MAX_EDID_BLOCKS * 128];
	int Offset;
	bool Status = false;

	Library = LoadLibrary("nvapi.dll");

	if (!Library)
		return false;

	NvAPI_QueryInterface = (NVAPI_QUERYINTERFACE)GetProcAddress(Library, "nvapi_QueryInterface");

	if (!NvAPI_QueryInterface)
		return false;

	NvAPI_Initialize = (NVAPI_INITIALIZE)NvAPI_QueryInterface(0x0150E828);
	NvAPI_EnumPhysicalGPUs = (NVAPI_ENUMPHYSICALGPUS)NvAPI_QueryInterface(0xE5AC921F);
	NvAPI_GPU_GetConnectedDisplayIds = (NVAPI_GPU_GETCONNECTEDDISPLAYIDS)NvAPI_QueryInterface(0x0078DBA2);
	NvAPI_SYS_GetGpuAndOutputIdFromDisplayId = (NVAPI_SYS_GETGPUANDOUTPUTIDFROMDISPLAYID)NvAPI_QueryInterface(0x112BA1A5);
	NvAPI_GPU_GetEDID = (NVAPI_GPU_GETEDID)NvAPI_QueryInterface(0x37D32E69);
	NvAPI_Unload = (NVAPI_UNLOAD)NvAPI_QueryInterface(0xD22BDD7E);

	if (!NvAPI_Initialize)
		return false;

	if (!NvAPI_EnumPhysicalGPUs)
		return false;

	if (!NvAPI_GPU_GetConnectedDisplayIds)
		return false;

	if (!NvAPI_SYS_GetGpuAndOutputIdFromDisplayId)
		return false;

	if (!NvAPI_GPU_GetEDID)
		return false;

	if (!NvAPI_Unload)
		return false;

	if (NvAPI_Initialize() != NVAPI_OK)
		return false;

	if (NvAPI_EnumPhysicalGPUs(GPUList, &GPUCount) != NVAPI_OK)
		return false;

	for (GPUIndex = 0; GPUIndex < GPUCount; GPUIndex++)
	{
		if (NvAPI_GPU_GetConnectedDisplayIds(GPUList[GPUIndex], NULL, &DisplayCount, 0) != NVAPI_OK)
			continue;

		if (DisplayCount <= 0)
			continue;

		std::vector<NV_GPU_DISPLAYIDS> DisplayList(DisplayCount);
		DisplayList[0].version = NV_GPU_DISPLAYIDS_VER;

		if (NvAPI_GPU_GetConnectedDisplayIds(GPUList[GPUIndex], &DisplayList[0], &DisplayCount, 0) != NVAPI_OK)
			continue;

		for (DisplayIndex = 0; DisplayIndex < DisplayCount; DisplayIndex++)
		{
			DisplayID = DisplayList[DisplayIndex].displayId;
			std::memset(&DisplayEDID, 0, sizeof DisplayEDID);
			DisplayEDID.version = NV_EDID_VER;

			if (NvAPI_GPU_GetEDID(GPUList[GPUIndex], DisplayID, &DisplayEDID) != NVAPI_OK)
			{
				int *GPUHandle;
				int OutputID;

				if (NvAPI_SYS_GetGpuAndOutputIdFromDisplayId(DisplayID, &GPUHandle, &OutputID) != NVAPI_OK)
					continue;

				if (NvAPI_GPU_GetEDID(GPUHandle, OutputID, &DisplayEDID) != NVAPI_OK)
					continue;

				GPUList[GPUIndex] = GPUHandle;
				DisplayID = OutputID;
			}

			EDIDSize = DisplayEDID.sizeofEDID;

			if (EDIDSize > MAX_EDID_BLOCKS * 128)
				EDIDSize = MAX_EDID_BLOCKS * 128;

			DataSize = EDIDSize;

			if (DataSize > NV_EDID_DATA_SIZE)
				DataSize = NV_EDID_DATA_SIZE;

			std::memset(NewDisplayEDID, 0, MAX_EDID_BLOCKS * 128);
			std::memcpy(NewDisplayEDID, DisplayEDID.EDID_Data, DataSize);

			for (Offset = NV_EDID_DATA_SIZE; Offset < EDIDSize; Offset += NV_EDID_DATA_SIZE)
			{
				std::memset(&DisplayEDID, 0, sizeof DisplayEDID);
				DisplayEDID.version = NV_EDID_VER;
				DisplayEDID.offset = Offset;

				if (NvAPI_GPU_GetEDID(GPUList[GPUIndex], DisplayID, &DisplayEDID) != NVAPI_OK)
					break;

				if (DisplayEDID.EDID_Data[0] == 0)
					break;

				DataSize = EDIDSize - Offset;

				if (DataSize > NV_EDID_DATA_SIZE)
					DataSize = NV_EDID_DATA_SIZE;

				std::memcpy(&NewDisplayEDID[Offset], DisplayEDID.EDID_Data, DataSize);
			}

			EDIDList.Add(NewDisplayEDID);
			Status = true;
		}
	}

	NvAPI_Unload();
	FreeLibrary(Library);
	return Status;
}
//---------------------------------------------------------------------------
