//local
#include "Syn_LogAnalyze.h"

#include <fstream>
#include <iostream>

Syn_LogAnalyze::Syn_LogAnalyze()
:_pSyn_LogAnalyzeValue(nullptr)
, _strLogPath("")
{
}

Syn_LogAnalyze::~Syn_LogAnalyze()
{
	if (nullptr != _pSyn_LogAnalyzeValue)
	{
		delete _pSyn_LogAnalyzeValue;
		_pSyn_LogAnalyzeValue = nullptr;
	}
}

int Syn_LogAnalyze::LogAnalysis(std::string strLogFilePath)
{
	int rc(0);

	unsigned Counts = strLogFilePath.size();
	if (0 == Counts)
		return Syn_LogExceptionCode::Syn_FileNotExists;
	if (".csv" != strLogFilePath.substr(Counts - 4, 4))
		return Syn_LogExceptionCode::Syn_SubstandardFormat;

	std::vector<std::string> listOfLineContent;
	rc = GetListOfLineContent(strLogFilePath, listOfLineContent);
	if (Syn_LogExceptionCode::Syn_OK != rc)
		return rc;

	_strLogPath = strLogFilePath;

	rc = this->AnalyzeAndFill(listOfLineContent);

	return rc;
}

int Syn_LogAnalyze::GetLogContent(Syn_LogAnalyzeValue * &oLogAnalyzeValue)
{
	if (nullptr == _pSyn_LogAnalyzeValue)
		return Syn_LogResultNull;

	oLogAnalyzeValue = _pSyn_LogAnalyzeValue;

	return Syn_OK;
}

std::string Syn_LogAnalyze::GetLogFilePath()
{
	return _strLogPath;
}

int Syn_LogAnalyze::GetListOfLineContent(std::string strLogFilePath, std::vector<std::string> &oListOfLineContent)
{
	oListOfLineContent.clear();

	std::ifstream input;
	input.open(strLogFilePath, std::ios_base::in);
	if (input.fail())
		return Syn_FileOpenFailed;

	while (!input.eof())
	{
		std::string sLineContent;
		while (getline(input, sLineContent))
		{
			oListOfLineContent.push_back(sLineContent);
		}
	}

	input.close();

	return Syn_OK;
}

int Syn_LogAnalyze::DivideLineContent(std::string strLineContent, std::vector<std::string> &oListOfValue)
{
	oListOfValue.clear();
	unsigned Counts = strLineContent.size();
	if (0 == Counts)
		return Syn_SubstandardValue;

	char SeparatorSymbol(',');

	if (SeparatorSymbol != strLineContent[Counts - 1])
		strLineContent.push_back(SeparatorSymbol);

	unsigned StartPos(0);
	for (size_t t = 0; t < strLineContent.size(); t++)
	{
		if (SeparatorSymbol == strLineContent[t])
		{
			std::string sSubString = strLineContent.substr(StartPos, t - StartPos);
			StartPos = t + 1;
			if (0 != sSubString.size()&&"," != sSubString)
				oListOfValue.push_back(sSubString);
		}
	}

	if (0 == oListOfValue.size())
		return Syn_BlankSpace;

	return Syn_OK;
}

int Syn_LogAnalyze::AnalyzeAndFill(std::vector<std::string> &ioListOfLineContent)
{
	int rc(0);

	unsigned listSize = ioListOfLineContent.size();
	if (0 == listSize)
		return Syn_SubstandardValue;

	this->InitLogAnalyzeValue();

	for (size_t t = 0; t < listSize; t++)
	{
		std::vector<std::string> listOfValue;
		rc = DivideLineContent(ioListOfLineContent[t], listOfValue);
		if (Syn_OK != rc || 0 == listOfValue.size())
			continue;

		unsigned int currentLineSize = listOfValue.size();
		std::string strTagValue = listOfValue[0];
		
		if ("MTLog" == strTagValue)
		{
			if (currentLineSize >= 3)
			{
				_pSyn_LogAnalyzeValue->SiteNumber = std::stoi(listOfValue[1]);
				_pSyn_LogAnalyzeValue->DeviceSerialNumber = std::stoi(listOfValue[2]);
			}
		}
		else if ("Version" == strTagValue)
		{
			if (currentLineSize >= 2)
				_pSyn_LogAnalyzeValue->SW_Version = listOfValue[1];
		}
		else if ("Config file" == strTagValue)
		{
			if (currentLineSize >= 2)
				_pSyn_LogAnalyzeValue->ConfigFilePath = listOfValue[1];
		}
		else if ("Test Time" == strTagValue)
		{
			if (currentLineSize >= 2)
				_pSyn_LogAnalyzeValue->TestDate = listOfValue[1];
		}
		else if ("Sensor Serial Number" == strTagValue)
		{
			if (currentLineSize >= 2)
				_pSyn_LogAnalyzeValue->SensorSerialNumber = listOfValue[1];
		}
		else if ("Initialization" == strTagValue)
		{
			if (currentLineSize >= 2)
			{
				_pSyn_LogAnalyzeValue->InitlizationResult.bExcuted = true;
				_pSyn_LogAnalyzeValue->InitlizationResult.strTestResult = listOfValue[1];
			}
		}
		else if ("RAMTest" == strTagValue)
		{
			if ((t + 2) >= listSize || currentLineSize < 8)
				continue;
			std::vector<std::string> listOfNextLineValue1, listOfNextLineValue2;
			rc = DivideLineContent(ioListOfLineContent[t + 1], listOfNextLineValue1);
			if (Syn_OK != rc || listOfNextLineValue1.size() < 5)
				continue;
			rc = DivideLineContent(ioListOfLineContent[t + 2], listOfNextLineValue2);
			if (Syn_OK != rc || listOfNextLineValue2.size() < 6)
				continue;
			_pSyn_LogAnalyzeValue->RAMTestResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->RAMTestResult.strTestResult = listOfValue[1];
			for (size_t m = 0; m < listOfNextLineValue1.size(); m++)
			{
				Syn_RAMTestResult::Syn_RAMInfo TempRAMInfo;
				TempRAMInfo.strRAMName = listOfValue[m + 3];
				TempRAMInfo.strRAMResults = listOfNextLineValue1[m];
				TempRAMInfo.RAMAddress = std::stoi(listOfNextLineValue2[m + 1]);

				_pSyn_LogAnalyzeValue->RAMTestResult.listOfRAMInfo.push_back(TempRAMInfo);
			}
		}
		else if ("Opens/Shorts Test" == strTagValue)
		{
			if (currentLineSize < 4)
				continue;
			_pSyn_LogAnalyzeValue->OpensShortTestResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->OpensShortTestResult.strTestResult = listOfValue[1];
			for (size_t m = 3; m < listOfValue.size(); m++)
				_pSyn_LogAnalyzeValue->OpensShortTestResult.listOfResponse.push_back(std::stoi(listOfValue[m]));
		}
		else if ("Pixel Patch" == strTagValue)
		{
			_pSyn_LogAnalyzeValue->PixelPatchTestResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->PixelPatchTestResult.strTestResult = listOfValue[1];
			//nextline
			if ((t + 1) >= listSize)
				continue;
			std::vector<std::string> listOfNextLineValue;
			rc = DivideLineContent(ioListOfLineContent[t + 1], listOfNextLineValue);
			if (Syn_OK == rc)
			{
				for (size_t m = 0; m < listOfNextLineValue.size();m++)
					_pSyn_LogAnalyzeValue->PixelPatchTestResult.listOfResponse.push_back(std::stoi(listOfNextLineValue[m]));
			}
		}
		else if ("WoVarTest" == strTagValue)
		{
			_pSyn_LogAnalyzeValue->WoVarTestResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->WoVarTestResult.strTestResult = listOfValue[1];
			//nextline
			if ((t + 1) >= listSize)
				continue;
			std::vector<std::string> listOfNextLineValue;
			rc = DivideLineContent(ioListOfLineContent[t + 1], listOfNextLineValue);
			if (Syn_OK == rc)
			{
				for (size_t m = 0; m < listOfNextLineValue.size(); m++)
					_pSyn_LogAnalyzeValue->WoVarTestResult.listOfResponse.push_back(std::stoi(listOfNextLineValue[m]));
			}
		}
		else if ("AFE Test" == strTagValue)
		{
			if (currentLineSize < 4||(t + 1) >= listSize)
				continue;
			_pSyn_LogAnalyzeValue->AFETestResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->AFETestResult.strTestResult = listOfValue[1];
			for (size_t m = 3; m < listOfValue.size(); m++)
				_pSyn_LogAnalyzeValue->AFETestResult.listOfResponse1.push_back(std::stoi(listOfValue[m]));
			std::vector<std::string> listOfNextLineValue;
			rc = DivideLineContent(ioListOfLineContent[t + 1], listOfNextLineValue);
			if (Syn_OK == rc)
			{
				for (size_t m = 0; m < listOfNextLineValue.size(); m++)
					_pSyn_LogAnalyzeValue->AFETestResult.listOfResponse2.push_back(std::stoi(listOfNextLineValue[m]));
			}
		}
		else if ("WOF-Low Power" == strTagValue)
		{
			if (currentLineSize < 5)
				continue;
			_pSyn_LogAnalyzeValue->WOFLowpowerTestResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->WOFLowpowerTestResult.strTestResult = listOfValue[1];
			_pSyn_LogAnalyzeValue->WOFLowpowerTestResult.Current_uA = std::stof(listOfValue[4]);
		}
		else if ("Calibration" == strTagValue)
		{
			if (currentLineSize < 2)
				continue;
			_pSyn_LogAnalyzeValue->CablicationResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->CablicationResult.strTestResult = listOfValue[1];
		}
		else if ("Stage1" == strTagValue)
		{
			if (currentLineSize < 2)
				continue;
			for (size_t m = 1; m < listOfValue.size(); m++)
				_pSyn_LogAnalyzeValue->CablicationResult.listOfStage1.push_back(std::stoi(listOfValue[m], 0, 16));
		}
		else if ("Stage2" == strTagValue || "Stage2 Used" == strTagValue)
		{
			if (currentLineSize <= 2)
				continue;
			for (size_t m = 1; m < listOfValue.size(); m++)
				_pSyn_LogAnalyzeValue->CablicationResult.listOfStage2.push_back(std::stoi(listOfValue[m], 0, 16));
		}
		else if ("Stage2 OTP" == strTagValue)
		{
			if (currentLineSize <= 2)
				continue;
			for (size_t m = 1; m < listOfValue.size(); m++)
				_pSyn_LogAnalyzeValue->CablicationResult.listOfStage2OTP.push_back(std::stoi(listOfValue[m], 0, 16));
		}
		else if ("Stage2 Variance Score" == strTagValue)
		{
			if (currentLineSize < 2)
				continue;
			_pSyn_LogAnalyzeValue->CablicationResult.strStage2VarianceScore = listOfValue[1];
		}
		else if ("FlexId" == strTagValue)
		{
			if (currentLineSize < 2)
				continue;
			_pSyn_LogAnalyzeValue->CablicationResult.FlexID = std::stoi(listOfValue[1], 0, 16);
		}
		else if ("WOF Zone0 FingerDown" == strTagValue)
		{
			if (currentLineSize < 2 || (t + 1) >= listSize)
				continue;
			_pSyn_LogAnalyzeValue->Zone0FDWOFTestResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->Zone0FDWOFTestResult.strTestResult = listOfValue[1];
			std::vector<std::string> listOfNextLineValue;
			rc = DivideLineContent(ioListOfLineContent[t + 1], listOfNextLineValue);
			if (Syn_OK == rc&&listOfNextLineValue.size()>=4)
			{
				_pSyn_LogAnalyzeValue->Zone0FDWOFTestResult.NoFingerValue = std::stoi(listOfNextLineValue[0]);
				_pSyn_LogAnalyzeValue->Zone0FDWOFTestResult.WithFingerValue = std::stoi(listOfNextLineValue[1]);
				_pSyn_LogAnalyzeValue->Zone0FDWOFTestResult.GainValue = std::stoi(listOfNextLineValue[2]);
				_pSyn_LogAnalyzeValue->Zone0FDWOFTestResult.DeltaValue = std::stoi(listOfNextLineValue[3]);
			}
		}
		else if ("WOF Zone0 FingerUp" == strTagValue)
		{
			if (currentLineSize < 2 || (t + 1) >= listSize)
				continue;
			_pSyn_LogAnalyzeValue->Zone0FUWOFTestResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->Zone0FUWOFTestResult.strTestResult = listOfValue[1];
			std::vector<std::string> listOfNextLineValue;
			rc = DivideLineContent(ioListOfLineContent[t + 1], listOfNextLineValue);
			if (Syn_OK == rc&&listOfNextLineValue.size() >= 4)
			{
				_pSyn_LogAnalyzeValue->Zone0FUWOFTestResult.NoFingerValue = std::stoi(listOfNextLineValue[0]);
				_pSyn_LogAnalyzeValue->Zone0FUWOFTestResult.WithFingerValue = std::stoi(listOfNextLineValue[1]);
				_pSyn_LogAnalyzeValue->Zone0FUWOFTestResult.GainValue = std::stoi(listOfNextLineValue[2]);
				_pSyn_LogAnalyzeValue->Zone0FUWOFTestResult.DeltaValue = std::stoi(listOfNextLineValue[3]);
			}
		}
		else if ("WOF Zone1 FingerDown" == strTagValue || "WOF Zone1  FingerDown" == strTagValue)
		{
			if (currentLineSize < 2 || (t + 1) >= listSize)
				continue;
			_pSyn_LogAnalyzeValue->Zone1FDWOFTestResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->Zone1FDWOFTestResult.strTestResult = listOfValue[1];
			std::vector<std::string> listOfNextLineValue;
			rc = DivideLineContent(ioListOfLineContent[t + 1], listOfNextLineValue);
			if (Syn_OK == rc&&listOfNextLineValue.size() >= 4)
			{
				_pSyn_LogAnalyzeValue->Zone1FDWOFTestResult.NoFingerValue = std::stoi(listOfNextLineValue[0]);
				_pSyn_LogAnalyzeValue->Zone1FDWOFTestResult.WithFingerValue = std::stoi(listOfNextLineValue[1]);
				_pSyn_LogAnalyzeValue->Zone1FDWOFTestResult.GainValue = std::stoi(listOfNextLineValue[2]);
				_pSyn_LogAnalyzeValue->Zone1FDWOFTestResult.DeltaValue = std::stoi(listOfNextLineValue[3]);
			}
		}
		else if ("WOF Zone1 FingerUp" == strTagValue)
		{
			if (currentLineSize < 2 || (t + 1) >= listSize)
				continue;
			_pSyn_LogAnalyzeValue->Zone1FUWOFTestResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->Zone1FUWOFTestResult.strTestResult = listOfValue[1];
			std::vector<std::string> listOfNextLineValue;
			rc = DivideLineContent(ioListOfLineContent[t + 1], listOfNextLineValue);
			if (Syn_OK == rc&&listOfNextLineValue.size() >= 4)
			{
				_pSyn_LogAnalyzeValue->Zone1FUWOFTestResult.NoFingerValue = std::stoi(listOfNextLineValue[0]);
				_pSyn_LogAnalyzeValue->Zone1FUWOFTestResult.WithFingerValue = std::stoi(listOfNextLineValue[1]);
				_pSyn_LogAnalyzeValue->Zone1FUWOFTestResult.GainValue = std::stoi(listOfNextLineValue[2]);
				_pSyn_LogAnalyzeValue->Zone1FUWOFTestResult.DeltaValue = std::stoi(listOfNextLineValue[3]);
			}
		}
		else if ("SCM Bottom WakeOnFinger Test" == strTagValue || "SCM Zone0 WakeOnFinger Test" == strTagValue)
		{
			if (currentLineSize < 2 || (t + 1) >= listSize)
				continue;
			_pSyn_LogAnalyzeValue->Zone0SCMWOFTestResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->Zone0SCMWOFTestResult.strTestResult = listOfValue[1];
			std::vector<std::string> listOfNextLineValue;
			rc = DivideLineContent(ioListOfLineContent[t + 1], listOfNextLineValue);
			if (Syn_OK == rc&&listOfNextLineValue.size() >= 4)
			{
				_pSyn_LogAnalyzeValue->Zone0SCMWOFTestResult.NoFingerValue = std::stoi(listOfNextLineValue[0]);
				_pSyn_LogAnalyzeValue->Zone0SCMWOFTestResult.WithFingerValue = std::stoi(listOfNextLineValue[1]);
				_pSyn_LogAnalyzeValue->Zone0SCMWOFTestResult.GainValue = std::stoi(listOfNextLineValue[2]);
				_pSyn_LogAnalyzeValue->Zone0SCMWOFTestResult.DeltaValue = std::stoi(listOfNextLineValue[3]);
			}
		}
		else if ("SCM Top WakeOnFinger Test" == strTagValue || "SCM Zone1 WakeOnFinger Test" == strTagValue)
		{
			if (currentLineSize < 2 || (t + 1) >= listSize)
				continue;
			_pSyn_LogAnalyzeValue->Zone1SCMWOFTestResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->Zone1SCMWOFTestResult.strTestResult = listOfValue[1];
			std::vector<std::string> listOfNextLineValue;
			rc = DivideLineContent(ioListOfLineContent[t + 1], listOfNextLineValue);
			if (Syn_OK == rc&&listOfNextLineValue.size() >= 4)
			{
				_pSyn_LogAnalyzeValue->Zone1SCMWOFTestResult.NoFingerValue = std::stoi(listOfNextLineValue[0]);
				_pSyn_LogAnalyzeValue->Zone1SCMWOFTestResult.WithFingerValue = std::stoi(listOfNextLineValue[1]);
				_pSyn_LogAnalyzeValue->Zone1SCMWOFTestResult.GainValue = std::stoi(listOfNextLineValue[2]);
				_pSyn_LogAnalyzeValue->Zone1SCMWOFTestResult.DeltaValue = std::stoi(listOfNextLineValue[3]);
			}
		}
		else if ("Button Test Without Stimulus" == strTagValue)
		{
			if (currentLineSize < 2 || (t + 1) >= listSize)
				continue;
			_pSyn_LogAnalyzeValue->ButtonTestWithoutStimulusResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->ButtonTestWithoutStimulusResult.strTestResult = listOfValue[1];
			std::vector<std::string> listOfNextLineValue;
			rc = DivideLineContent(ioListOfLineContent[t + 1], listOfNextLineValue);
			if (Syn_OK == rc&&listOfNextLineValue.size() >= 2)
			{
				_pSyn_LogAnalyzeValue->ButtonTestWithoutStimulusResult.CurrentState = std::stoi(listOfNextLineValue[0]);
				_pSyn_LogAnalyzeValue->ButtonTestWithoutStimulusResult.ExpectedState = std::stoi(listOfNextLineValue[1]);
			}
		}
		else if ("Button Test With Stimulus" == strTagValue)
		{
			if (currentLineSize < 2 || (t + 1) >= listSize)
				continue;
			_pSyn_LogAnalyzeValue->ButtonTestWithStimulusResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->ButtonTestWithStimulusResult.strTestResult = listOfValue[1];
			std::vector<std::string> listOfNextLineValue;
			rc = DivideLineContent(ioListOfLineContent[t + 1], listOfNextLineValue);
			if (Syn_OK == rc&&listOfNextLineValue.size() >= 2)
			{
				_pSyn_LogAnalyzeValue->ButtonTestWithStimulusResult.CurrentState = std::stoi(listOfNextLineValue[0]);
				_pSyn_LogAnalyzeValue->ButtonTestWithStimulusResult.ExpectedState = std::stoi(listOfNextLineValue[1]);
			}
		}
		else if ("Pegged Pixels Test" == strTagValue)
		{
			if (currentLineSize < 5 || (t + 1) >= listSize)
				continue;
			_pSyn_LogAnalyzeValue->PeggedPixelsTestResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->PeggedPixelsTestResult.strTestResult = listOfValue[1];
			for (size_t m = 4; m < listOfValue.size(); m++)
				_pSyn_LogAnalyzeValue->PeggedPixelsTestResult.listOfPeggedPixelRows.push_back(std::stoi(listOfValue[m]));
			std::vector<std::string> listOfNextLineValue;
			rc = DivideLineContent(ioListOfLineContent[t + 1], listOfNextLineValue);
			if (Syn_OK == rc)
			{
				for (size_t m = 1; m < listOfNextLineValue.size(); m++)
					_pSyn_LogAnalyzeValue->PeggedPixelsTestResult.listOfPeggedPixelColumns.push_back(std::stoi(listOfNextLineValue[m]));
			}
		}
		else if ("Floored Pixels Test" == strTagValue)
		{
			if (currentLineSize < 5 || (t + 1) >= listSize)
				continue;
			_pSyn_LogAnalyzeValue->FlooredPixelsTestResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->FlooredPixelsTestResult.strTestResult = listOfValue[1];
			for (size_t m = 4; m < listOfValue.size(); m++)
				_pSyn_LogAnalyzeValue->FlooredPixelsTestResult.listOfFlooredPixelRows.push_back(std::stoi(listOfValue[m]));
			std::vector<std::string> listOfNextLineValue;
			rc = DivideLineContent(ioListOfLineContent[t + 1], listOfNextLineValue);
			if (Syn_OK == rc)
			{
				for (size_t m = 1; m < listOfNextLineValue.size(); m++)
					_pSyn_LogAnalyzeValue->FlooredPixelsTestResult.listOfFlooredPixelColumns.push_back(std::stoi(listOfNextLineValue[m]));
			}
		}
		else if ("DRdy Test" == strTagValue)
		{
			if (currentLineSize < 2)
				continue;
			_pSyn_LogAnalyzeValue->DRdyTestResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->DRdyTestResult.strTestResult = listOfValue[1];
		}
		else if ("Consecutive Pixels Test" == strTagValue)
		{
			if (currentLineSize < 5)
				continue;
			_pSyn_LogAnalyzeValue->ConsecutivePixelsTestResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->ConsecutivePixelsTestResult.strTestResult = listOfValue[1];
			for (size_t m = 4; m < listOfValue.size(); m++)
				_pSyn_LogAnalyzeValue->ConsecutivePixelsTestResult.listOfConsecutivePeggedRows.push_back(std::stoi(listOfValue[m]));
		}
		else if ("Floored Rows" == strTagValue)
		{
			if (currentLineSize < 2)
				continue;
			for (size_t m = 1; m < listOfValue.size(); m++)
				_pSyn_LogAnalyzeValue->ConsecutivePixelsTestResult.listOfConsecutiveFlooredRows.push_back(std::stoi(listOfValue[m]));
		}
		else if ("Pegged Columns" == strTagValue)
		{
			if (currentLineSize < 2)
				continue;
			for (size_t m = 1; m < listOfValue.size(); m++)
				_pSyn_LogAnalyzeValue->ConsecutivePixelsTestResult.listOfConsecutivePeggedColumns.push_back(std::stoi(listOfValue[m]));
		}
		else if ("Floored Columns" == strTagValue)
		{
			if (currentLineSize < 2)
				continue;
			for (size_t m = 1; m < listOfValue.size(); m++)
				_pSyn_LogAnalyzeValue->ConsecutivePixelsTestResult.listOfConsecutiveFlooredColumns.push_back(std::stoi(listOfValue[m]));
		}
		else if ("Current Test" == strTagValue)
		{
			if (currentLineSize < 5 || (t + 1) >= listSize)
				continue;
			_pSyn_LogAnalyzeValue->CurrentTestResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->CurrentTestResult.strTestResult = listOfValue[1];
			_pSyn_LogAnalyzeValue->CurrentTestResult.ImageAcqDigCurrent_uA = std::stof(listOfValue[4]);
			std::vector<std::string> listOfNextLineValue;
			rc = DivideLineContent(ioListOfLineContent[t + 1], listOfNextLineValue);
			if (rc == Syn_OK)
			{
				_pSyn_LogAnalyzeValue->CurrentTestResult.ImageAcqAnaCurrent_uA = std::stof(listOfNextLineValue[1]);
			}
		}
		else if ("Retain Mode Test" == strTagValue)
		{
			if (currentLineSize < 2 || (t + 1) >= listSize)
				continue;
			_pSyn_LogAnalyzeValue->RetainModeTestResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->RetainModeTestResult.strTestResult = listOfValue[1];
			std::vector<std::string> listOfNextLineValue;
			rc = DivideLineContent(ioListOfLineContent[t + 1], listOfNextLineValue);
			if (rc == Syn_OK&&listOfNextLineValue.size()>=1)
			{
				_pSyn_LogAnalyzeValue->RetainModeTestResult.RetainModeCurrent = std::stof(listOfNextLineValue[0]);
			}
		}
		else if ("SNR Test" == strTagValue)
		{
			if (currentLineSize < 2 || (t + 1) >= listSize)
				continue;
			_pSyn_LogAnalyzeValue->SNRTestResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->SNRTestResult.strTestResult = listOfValue[1];
			std::vector<std::string> listOfNextLineValue;
			rc = DivideLineContent(ioListOfLineContent[t + 1], listOfNextLineValue);
			if (rc == Syn_OK&&listOfNextLineValue.size()>=21)
			{
				for (size_t m = 0; m < listOfNextLineValue.size(); m=m+3)
				{
					_pSyn_LogAnalyzeValue->SNRTestResult.listOfSignalValue.push_back(std::stoi(listOfNextLineValue[m]));
					_pSyn_LogAnalyzeValue->SNRTestResult.listOfNoiseValue.push_back(std::stof(listOfNextLineValue[m+1]));
					_pSyn_LogAnalyzeValue->SNRTestResult.listOfSNRlValue.push_back(std::stof(listOfNextLineValue[m+2]));
				}
			}
		}
		else if ("Pixel Uniformity Test" == strTagValue)
		{
			if (currentLineSize < 2 || (t + 1) >= listSize)
				continue;
			_pSyn_LogAnalyzeValue->PixelUniformityTestResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->PixelUniformityTestResult.strTestResult = listOfValue[1];
			std::vector<std::string> listOfNextLineValue;
			rc = DivideLineContent(ioListOfLineContent[t + 1], listOfNextLineValue);
			if (Syn_OK == rc&&listOfNextLineValue.size() >= 3)
			{
				_pSyn_LogAnalyzeValue->PixelUniformityTestResult.MinimumPixel = std::stoi(listOfNextLineValue[0]);
				_pSyn_LogAnalyzeValue->PixelUniformityTestResult.MaximumPixel = std::stoi(listOfNextLineValue[1]);
				_pSyn_LogAnalyzeValue->PixelUniformityTestResult.FailingPixelCount = std::stoi(listOfNextLineValue[2]);
			}
		}
		else if ("Sharpness Test" == strTagValue)
		{
			if (currentLineSize < 2 || (t + 2) >= listSize)
				continue;
			_pSyn_LogAnalyzeValue->SharpnessTestResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->SharpnessTestResult.strTestResult = listOfValue[1];
			std::vector<std::string> listOfNextLineValue;
			rc = DivideLineContent(ioListOfLineContent[t + 2], listOfNextLineValue);
			if (Syn_OK == rc&&listOfNextLineValue.size()>=5)
			{
				_pSyn_LogAnalyzeValue->SharpnessTestResult.Variation = std::stof(listOfNextLineValue[0]);
				_pSyn_LogAnalyzeValue->SharpnessTestResult.Zone0Sharpness = std::stoi(listOfNextLineValue[1]);
				_pSyn_LogAnalyzeValue->SharpnessTestResult.Zone1Sharpness = std::stoi(listOfNextLineValue[2]);
				_pSyn_LogAnalyzeValue->SharpnessTestResult.Zone2Sharpness = std::stoi(listOfNextLineValue[3]);
				_pSyn_LogAnalyzeValue->SharpnessTestResult.OverallSharpness = std::stoi(listOfNextLineValue[4]);
			}
		}
		else if ("RxStandardDev Test" == strTagValue)
		{
			if (currentLineSize < 2 || (t + 1) >= listSize)
				continue;
			_pSyn_LogAnalyzeValue->RxStandardDevTestResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->RxStandardDevTestResult.strTestResult = listOfValue[1];
			std::vector<std::string> listOfNextLineValue;
			rc = DivideLineContent(ioListOfLineContent[t + 1], listOfNextLineValue);
			if (Syn_OK == rc)
			{
				for (size_t m = 1; m < listOfNextLineValue.size(); m++)
					_pSyn_LogAnalyzeValue->RxStandardDevTestResult.listOfPercent.push_back(std::stof(listOfNextLineValue[m]));
			}
		}
		else if ("Imperfections Test" == strTagValue)
		{
			if (currentLineSize < 5 || (t + 1) >= listSize)
				continue;
			_pSyn_LogAnalyzeValue->ImperfectionsTestResult.bExcuted = true;
			_pSyn_LogAnalyzeValue->ImperfectionsTestResult.strTestResult = listOfValue[1];
			for (size_t m = 4; m < listOfValue.size(); m++)
				_pSyn_LogAnalyzeValue->ImperfectionsTestResult.listOfConsecutivePeggedRows.push_back(std::stoi(listOfValue[m]));
			std::vector<std::string> listOfNextLineValue;
			rc = DivideLineContent(ioListOfLineContent[t + 1], listOfNextLineValue);
			if (Syn_OK == rc)
			{
				for (size_t m = 1; m < listOfNextLineValue.size(); m++)
					_pSyn_LogAnalyzeValue->ImperfectionsTestResult.listOfConsecutivePeggedCols.push_back(std::stoi(listOfNextLineValue[m]));
			}
		}
		else if ("Average No Finger" == strTagValue)
		{
			if (GetImageFrame(ioListOfLineContent, t + 1, listSize, _pSyn_LogAnalyzeValue->NoFingerResult.arr_NoFinger, _pSyn_LogAnalyzeValue->NoFingerResult.RowNumber, _pSyn_LogAnalyzeValue->NoFingerResult.ColumnNumber))
			{
				_pSyn_LogAnalyzeValue->NoFingerResult.bExcuted = true;
			}
		}
		else if ("Normalized Finger" == strTagValue)
		{
			if (GetImageFrame(ioListOfLineContent, t + 1, listSize, _pSyn_LogAnalyzeValue->FakeFingerResult.arr_FakeFinger, _pSyn_LogAnalyzeValue->FakeFingerResult.RowNumber, _pSyn_LogAnalyzeValue->FakeFingerResult.ColumnNumber))
			{
				_pSyn_LogAnalyzeValue->FakeFingerResult.bExcuted = true;
			}
		}
		else if ("TAG Value" == strTagValue)
		{
			for (unsigned int m = t + 1; m < listSize; m++)
			{
				std::vector<std::string> listOfNextLineValue;
				rc = DivideLineContent(ioListOfLineContent[m], listOfNextLineValue);
				if (0 != rc || 0 == listOfNextLineValue.size())
					break;
				std::string strFirstValue = listOfNextLineValue[0];
				if (std::string::npos!=strFirstValue.find_first_of("EXT_TAG_"))
				{
					std::string strTagName = listOfNextLineValue[0];
					std::vector<std::string> listOfTagValue;
					for (size_t n = 1; n < listOfNextLineValue.size(); n++)
						listOfTagValue.push_back(listOfNextLineValue[n]);
					_pSyn_LogAnalyzeValue->mapOfTagValue.insert(std::map<std::string, std::vector<std::string>>::value_type(strTagName, listOfTagValue));
				}
			}
		}
		//else if ("Bin Codes" == strTagValue)
		else if (std::string::npos != strTagValue.find("Bin Codes"))
		{
			for (size_t m = 1; m < listOfValue.size(); m++)
				_pSyn_LogAnalyzeValue->listOfBinCode.push_back(listOfValue[m]);
		}
		else
		{
			continue;
		}
	}

	return Syn_OK;
}

void Syn_LogAnalyze::InitLogAnalyzeValue()
{
	if (NULL != _pSyn_LogAnalyzeValue)
	{
		delete _pSyn_LogAnalyzeValue;
		_pSyn_LogAnalyzeValue = NULL;
	}
	_pSyn_LogAnalyzeValue = new Syn_LogAnalyzeValue();

	_pSyn_LogAnalyzeValue->InitlizationResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->RAMTestResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->OpensShortTestResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->PixelPatchTestResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->WoVarTestResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->AFETestResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->WOFLowpowerTestResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->CablicationResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->Zone0FDWOFTestResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->Zone0FUWOFTestResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->Zone1FDWOFTestResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->Zone1FUWOFTestResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->Zone0SCMWOFTestResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->Zone1SCMWOFTestResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->ButtonTestWithoutStimulusResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->ButtonTestWithStimulusResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->PeggedPixelsTestResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->FlooredPixelsTestResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->DRdyTestResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->ConsecutivePixelsTestResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->CurrentTestResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->RetainModeTestResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->SNRTestResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->PixelUniformityTestResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->SharpnessTestResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->RxStandardDevTestResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->ImperfectionsTestResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->NoFingerResult.bExcuted = false;
	_pSyn_LogAnalyzeValue->FakeFingerResult.bExcuted = false;
}

bool Syn_LogAnalyze::GetImageFrame(std::vector<std::string> &listOfLineContent, size_t StartPos, size_t EndPos, uint8_t arrImage[160][160], unsigned &oRowNumber, unsigned &oColsNumber)
{
	if (EndPos <= StartPos)
		return false;

	//Judge
	std::vector<std::string> ListOfJudgeValue;
	int rc = DivideLineContent(listOfLineContent[StartPos], ListOfJudgeValue);
	if (0 != rc || 0 == ListOfJudgeValue.size())
		return false;

	oRowNumber = 0;
	for (size_t i = StartPos; i != EndPos; i++)
	{
		std::vector<std::string> ListOfValue;
		int rc = DivideLineContent(listOfLineContent[i], ListOfValue);
		if (0 != rc || 0 == ListOfValue.size())
			break;

		oColsNumber = ListOfValue.size();
		for (size_t m = 0; m < oColsNumber; m++)
		{
			arrImage[oRowNumber][m] = std::stoi(ListOfValue[m]);
		}
		oRowNumber++;
	}

	return true;
}