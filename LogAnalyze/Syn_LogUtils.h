#pragma once

#include <stdint.h>
#include <string>
#include <vector>
#include <map>

typedef struct
{
	bool bExcuted;
	std::string strTestResult;
}Syn_InitlizationResult;

typedef struct
{
	bool bExcuted;
	std::string strTestResult;

	typedef struct
	{
		std::string strRAMName;
		std::string strRAMResults;
		uint32_t	RAMAddress;
	}Syn_RAMInfo;

	std::vector<Syn_RAMInfo> listOfRAMInfo;

}Syn_RAMTestResult;

typedef struct
{
	bool bExcuted;
	std::string strTestResult;
	std::vector<uint32_t> listOfResponse;
}Syn_OpensShortTestResult;

typedef struct
{
	bool bExcuted;
	std::string strTestResult;
	std::vector<uint32_t> listOfResponse;
}Syn_PixelPatchTestResult;

typedef struct
{
	bool bExcuted;
	std::string strTestResult;
	std::vector<uint32_t> listOfResponse;
}Syn_WoVarTestResult;

typedef struct
{
	bool bExcuted;
	std::string strTestResult;
	std::vector<uint8_t> listOfResponse1;
	std::vector<uint8_t> listOfResponse2;
}Syn_AFETestResult;

typedef struct
{
	bool bExcuted;
	std::string strTestResult;
	float Current_uA;
}Syn_WOFLowpowerTestResult;

typedef struct
{
	bool bExcuted;
	std::string strTestResult;
	std::vector<uint8_t> listOfStage1;
	std::vector<uint8_t> listOfStage2;//Stage2 or Stage2 Used
	std::vector<uint8_t> listOfStage2OTP;//Stage2 OTP
	std::string strStage2VarianceScore;
	int FlexID;
}Syn_CablicationResult;

typedef struct
{
	bool bExcuted;
	std::string strTestResult;
	int NoFingerValue;
	int WithFingerValue;
	int GainValue;
	int DeltaValue;
}Syn_WOFTestResult;

typedef struct
{
	bool bExcuted;
	std::string strTestResult;
	int NoFingerValue;
	int WithFingerValue;
	int GainValue;
	int DeltaValue;
}Syn_SCMWOFTestResult;

typedef struct
{
	bool bExcuted;
	std::string strTestResult;
	uint8_t CurrentState;
	int ExpectedState;
}Syn_ButtonTestResult;

typedef struct
{
	bool bExcuted;
	std::string strTestResult;
	std::vector<int> listOfPeggedPixelRows;
	std::vector<int> listOfPeggedPixelColumns;
}Syn_PeggedPixelsTestResult;

typedef struct
{
	bool bExcuted;
	std::string strTestResult;
	std::vector<int> listOfFlooredPixelRows;
	std::vector<int> listOfFlooredPixelColumns;
}Syn_FlooredPixelsTestResult;

typedef struct
{
	bool bExcuted;
	std::string strTestResult;
}Syn_DRdyTestResult;

typedef struct
{
	bool bExcuted;
	std::string strTestResult;
	std::vector<int> listOfConsecutivePeggedRows;
	std::vector<int> listOfConsecutivePeggedColumns;
	std::vector<int> listOfConsecutiveFlooredRows;
	std::vector<int> listOfConsecutiveFlooredColumns;
}Syn_ConsecutivePixelsTestResult;

typedef struct
{
	bool bExcuted;
	std::string strTestResult;
	float ImageAcqDigCurrent_uA;
	float ImageAcqAnaCurrent_uA;
}Syn_CurrentTestResult;

typedef struct
{
	bool bExcuted;
	std::string strTestResult;
	float spivcc_current_uA;
	float vcc_current_uA;
}Syn_DeepSleepTestResult;

typedef struct
{
	bool bExcuted;
	std::string strTestResult;
	float RetainModeCurrent;
}Syn_RetainModeTestResult;

typedef struct
{
	bool bExcuted;
	std::string strTestResult;
	std::vector<int> listOfSignalValue;
	std::vector<float> listOfNoiseValue;
	std::vector<float> listOfSNRlValue;
}Syn_SNRTestResult;

typedef struct
{
	bool bExcuted;
	std::string strTestResult;
	int MinimumPixel;
	int MaximumPixel;
	int FailingPixelCount;
}Syn_PixelUniformityTestResult;

typedef struct
{
	bool bExcuted;
	std::string strTestResult;
	float Variation;
	int Zone0Sharpness;
	int Zone1Sharpness;
	int Zone2Sharpness;
	int OverallSharpness;
}Syn_SharpnessTestResult;

typedef struct
{
	bool bExcuted;
	std::string strTestResult;
	std::vector<float> listOfPercent;
}Syn_RxStandardDevTestResult;

typedef struct
{
	bool bExcuted;
	std::string strTestResult;
	std::vector<int> listOfConsecutivePeggedRows;
	std::vector<int> listOfConsecutivePeggedCols;
}Syn_ImperfectionsTestResult;

typedef struct
{
	bool bExcuted;
	unsigned int RowNumber;
	unsigned int ColumnNumber;
	uint8_t arr_NoFinger[160][160];
}Syn_NoFingerResult;

typedef struct
{
	bool bExcuted;
	unsigned int RowNumber;
	unsigned int ColumnNumber;
	uint8_t arr_FakeFinger[160][160];
}Syn_FakeFingerResult;

struct Syn_LogAnalyzeValue
{
	unsigned		SiteNumber;
	std::string		DeviceSerialNumber;
	std::string		SW_Version;
	std::string		ConfigFilePath;
	std::string		TestDate;
	std::string		SensorSerialNumber;

	Syn_InitlizationResult			InitlizationResult;
	Syn_RAMTestResult				RAMTestResult;
	Syn_OpensShortTestResult		OpensShortTestResult;
	Syn_PixelPatchTestResult		PixelPatchTestResult;
	Syn_WoVarTestResult				WoVarTestResult;
	Syn_AFETestResult				AFETestResult;
	Syn_WOFLowpowerTestResult		WOFLowpowerTestResult;
	Syn_CablicationResult			CablicationResult;
	Syn_WOFTestResult				Zone0FDWOFTestResult;
	Syn_WOFTestResult				Zone0FUWOFTestResult;
	Syn_WOFTestResult				Zone1FDWOFTestResult;
	Syn_WOFTestResult				Zone1FUWOFTestResult;
	Syn_SCMWOFTestResult			Zone0SCMWOFTestResult;
	Syn_SCMWOFTestResult			Zone1SCMWOFTestResult;
	Syn_ButtonTestResult			ButtonTestWithoutStimulusResult;
	Syn_ButtonTestResult			ButtonTestWithStimulusResult;
	Syn_PeggedPixelsTestResult		PeggedPixelsTestResult;
	Syn_FlooredPixelsTestResult		FlooredPixelsTestResult;
	Syn_DRdyTestResult				DRdyTestResult;
	Syn_ConsecutivePixelsTestResult ConsecutivePixelsTestResult;
	Syn_CurrentTestResult			CurrentTestResult;
	Syn_DeepSleepTestResult			DeepSleepTestResult;
	Syn_RetainModeTestResult		RetainModeTestResult;
	Syn_SNRTestResult				SNRTestResult;
	Syn_PixelUniformityTestResult	PixelUniformityTestResult;
	Syn_SharpnessTestResult			SharpnessTestResult;
	Syn_RxStandardDevTestResult		RxStandardDevTestResult;
	Syn_ImperfectionsTestResult		ImperfectionsTestResult;
	Syn_NoFingerResult				NoFingerResult;
	Syn_FakeFingerResult			FakeFingerResult;

	std::map<std::string, std::vector<std::string>> mapOfTagValue;

	std::vector<std::string>		listOfBinCode;
};