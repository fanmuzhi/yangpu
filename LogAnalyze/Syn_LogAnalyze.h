#pragma once

#include "Syn_LogUtils.h"

#include <string>
#include <vector>

enum Syn_LogExceptionCode
{
	Syn_OK = 0,
	Syn_FileNotExists,
	Syn_SubstandardFormat,
	Syn_FileOpenFailed,
	Syn_FileNull,
	Syn_LogResultNull,
	Syn_SubstandardValue,
	Syn_BlankSpace
};

class Syn_LogAnalyze
{

public:
	Syn_LogAnalyze();
	virtual ~Syn_LogAnalyze();

	int LogAnalysis(std::string strLogFilePath);

	int GetLogContent(Syn_LogAnalyzeValue * &oLogAnalyzeValue);

	std::string GetLogFilePath();

protected:

	int GetListOfLineContent(std::string strLogFilePath, std::vector<std::string> &oListOfLineContent);

	int DivideLineContent(std::string strLineContent, std::vector<std::string> &oListOfValue);

	int AnalyzeAndFill(std::vector<std::string> &ioListOfLineContent);

	void InitLogAnalyzeValue();
	
	bool GetImageFrame(std::vector<std::string> &listOfLineContent, size_t StartPos, size_t EndPos, uint8_t arrImage[160][160], unsigned &oRowNumber, unsigned &oColsNumber);

private:

	Syn_LogAnalyzeValue *_pSyn_LogAnalyzeValue;

	std::string _strLogPath;
};

