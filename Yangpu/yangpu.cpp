#include "yangpu.h"
#include <QtWidgets>
#include <QAxObject>

#include <iostream>

#include "Syn_LogUtils.h"

Yangpu::Yangpu(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	this->setAcceptDrops(true);
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	QObject::connect(ui.actionExit, SIGNAL(triggered(bool)), this, SLOT(Exit()));//Exit

	QObject::connect(ui.actionOpen, SIGNAL(triggered(bool)), this, SLOT(OpenFile()));

	QObject::connect(ui.actionSave, SIGNAL(triggered(bool)), this, SLOT(SaveExcel()));

	QObject::connect(ui.tableWidget, SIGNAL(cellClicked(int, int)), this, SLOT(TableWidgetCellClicked(int, int)));

	QObject::connect(ui.actionSingal_Item, SIGNAL(triggered(bool)), this, SLOT(SavePicSingalItem()));

	QObject::connect(ui.actionAll_Item, SIGNAL(triggered(bool)), this, SLOT(SavePicAllItem()));
}

Yangpu::~Yangpu()
{

}

void Yangpu::Exit()
{
	QCoreApplication::exit();
}

void Yangpu::OpenFile()
{
	/*QString strLogFilePath = QFileDialog::getOpenFileName(this, "Select Log File", "./", "csv file(*.csv)");
	if (0 == strLogFilePath.size())
		return;*/

	QList<QUrl> urls = QFileDialog::getOpenFileUrls(this, "Select Log Files");
	if (urls.isEmpty())
		return;

	std::vector<std::string> listOfCSVFile;
	for (QList<QUrl>::iterator i = urls.begin(); i != urls.end(); i++)
	{
		QString fileName = i->toLocalFile();

		if (fileName.isEmpty())
			continue;
		if (!fileName.endsWith(".csv"))
			continue;

		listOfCSVFile.push_back(fileName.toStdString());
	}

	GetLogInfo(listOfCSVFile);
}

void Yangpu::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("text/uri-list"))
		event->acceptProposedAction();
}

void Yangpu::dropEvent(QDropEvent * event)
{
	QList<QUrl> urls = event->mimeData()->urls();
	if (urls.isEmpty())
		return;

	/*QString fileName = urls.first().toLocalFile();
	if (fileName.isEmpty())
		return;

	if (!fileName.endsWith(".csv"))
		return;*/

	vector<string> listOfCSVFile;
	for (QList<QUrl>::iterator i = urls.begin(); i != urls.end(); i++)
	{
		QString fileName = i->toLocalFile();
		
		if (fileName.isEmpty())
			continue;
		if (!fileName.endsWith(".csv"))
			continue;

		listOfCSVFile.push_back(fileName.toStdString());
	}

	GetLogInfo(listOfCSVFile);
}

void Yangpu::GetLogInfo(vector<string> listOfLogFilePath)
{
	unsigned int ListCounts = listOfLogFilePath.size();
	if (0 == ListCounts)
		return;

	if (0 != _ListOfLogAnalyze.size())
	{
		for (size_t i = 0; i < _ListOfLogAnalyze.size(); i++)
		{
			bool IsExists(false);
			string sLogFilePath = _ListOfLogAnalyze[i]->GetLogFilePath();
			for (size_t j = 0; j < listOfLogFilePath.size(); j++)
			{
				if (sLogFilePath == listOfLogFilePath[j])
				{
					IsExists = true;
					break;
				}
			}

			if (!IsExists)
			{
				listOfLogFilePath.push_back(sLogFilePath);
			}
		}
	}

	ListCounts = listOfLogFilePath.size();
	this->ClearLogAnalyze();
	this->InitWidgetState();
	ui.tableWidget->setRowCount(ListCounts);

	for (size_t t = 0; t < ListCounts; t++)
	{
		Syn_LogAnalyze *pSyn_LogAnalyze = new Syn_LogAnalyze();
		int rc = pSyn_LogAnalyze->LogAnalysis(listOfLogFilePath[t]);
		if (0 != rc)
		{
			delete pSyn_LogAnalyze;
			pSyn_LogAnalyze = NULL;
			continue;
		}

		Syn_LogAnalyzeValue *pLogResults = NULL;
		rc = pSyn_LogAnalyze->GetLogContent(pLogResults);
		if (0 != rc || NULL == pLogResults)
		{
			delete pSyn_LogAnalyze;
			pSyn_LogAnalyze = NULL;
			continue;
		}

		_ListOfLogAnalyze.push_back(pSyn_LogAnalyze);
		
		if (0 != pLogResults->SensorSerialNumber.size())
		{
			QTableWidgetItem *itemSerialNumber = new QTableWidgetItem(QString::fromStdString(pLogResults->SensorSerialNumber));
			itemSerialNumber->setTextAlignment(Qt::AlignCenter);
			ui.tableWidget->setItem(t, 0, itemSerialNumber);
		}

		QString qsResult("");
		QColor qColor;
		if (1 == pLogResults->listOfBinCode.size() && "1" == pLogResults->listOfBinCode[0])
		{
			qsResult = "Pass";
			qColor = QColor(0, 255, 0);
		}
		else
		{
			qsResult = "Fail";
			qColor = QColor(255, 0, 0);
		}
		QTableWidgetItem *itemResult = new QTableWidgetItem(qsResult);
		itemResult->setTextAlignment(Qt::AlignCenter);
		itemResult->setBackgroundColor(qColor);
		ui.tableWidget->setItem(t, 1, itemResult);

		if (pLogResults->SNRTestResult.bExcuted)
		{
			QTableWidgetItem *itemSignal = new QTableWidgetItem(QString::number(pLogResults->SNRTestResult.listOfSignalValue[pLogResults->SNRTestResult.listOfSignalValue.size() - 1]));
			itemSignal->setTextAlignment(Qt::AlignCenter);
			ui.tableWidget->setItem(t, 2, itemSignal);

			QTableWidgetItem *itemNoise = new QTableWidgetItem(QString::number(pLogResults->SNRTestResult.listOfNoiseValue[pLogResults->SNRTestResult.listOfNoiseValue.size() - 1]));
			itemNoise->setTextAlignment(Qt::AlignCenter);
			ui.tableWidget->setItem(t, 3, itemNoise);

			QTableWidgetItem *itemSNR = new QTableWidgetItem(QString::number(pLogResults->SNRTestResult.listOfSNRlValue[pLogResults->SNRTestResult.listOfSNRlValue.size() - 1]));
			itemSNR->setTextAlignment(Qt::AlignCenter);
			ui.tableWidget->setItem(t, 4, itemSNR);
		}

		if (pLogResults->SharpnessTestResult.bExcuted)
		{
			QTableWidgetItem *itemSharpness = new QTableWidgetItem(QString::number(pLogResults->SharpnessTestResult.OverallSharpness));
			itemSharpness->setTextAlignment(Qt::AlignCenter);
			ui.tableWidget->setItem(t, 5, itemSharpness);
		}

		if (0 != pLogResults->listOfBinCode.size())
		{
			std::string strBinCodesValue = pLogResults->listOfBinCode[0];
			if (1 != pLogResults->listOfBinCode.size())
			{
				for (size_t i = 1; i < pLogResults->listOfBinCode.size(); i++)
				{
					strBinCodesValue = strBinCodesValue + "  " + pLogResults->listOfBinCode[i];
				}
			}

			QTableWidgetItem *itemBindeCodes = new QTableWidgetItem(QString::fromStdString(strBinCodesValue));
			itemBindeCodes->setTextAlignment(Qt::AlignCenter);
			ui.tableWidget->setItem(t, 6, itemBindeCodes);
		}
	}
}

void Yangpu::ClearLogAnalyze()
{
	if (0 == _ListOfLogAnalyze.size())
		return;

	for (size_t t = 0; t <_ListOfLogAnalyze.size(); t++)
	{
		Syn_LogAnalyze *pLogAnalyze = _ListOfLogAnalyze[t];
		if (NULL != pLogAnalyze)
		{
			delete pLogAnalyze;
			pLogAnalyze = NULL;
		}
	}

	_ListOfLogAnalyze.clear();
}

void Yangpu::InitWidgetState()
{
	//Basic Info
	ui.SerialNumberLineEdit->clear();
	ui.SoftwareVersionLineEdit->clear();
	ui.ConfigFileLineEdit->clear();
	ui.textBrowser->clear();

	//SNR
	ui.SignalZone1ValueLabel->setText("--");
	ui.SignalZone2ValueLabel->setText("--");
	ui.SignalZone3ValueLabel->setText("--");
	ui.SignalZone4ValueLabel->setText("--");
	ui.SignalZone5ValueLabel->setText("--");
	ui.SignalZone6ValueLabel->setText("--");
	ui.SignalOverAllValueLabel->setText("--");

	ui.NoiseZone1ValueLabel->setText("--");
	ui.NoiseZone2ValueLabel->setText("--");
	ui.NoiseZone3ValueLabel->setText("--");
	ui.NoiseZone4ValueLabel->setText("--");
	ui.NoiseZone5ValueLabel->setText("--");
	ui.NoiseZone6ValueLabel->setText("--");
	ui.NoiseOverAllValueLabel->setText("--");

	ui.SNRZone1ValueLabel->setText("--");
	ui.SNRZone2ValueLabel->setText("--");
	ui.SNRZone3ValueLabel->setText("--");
	ui.SNRZone4ValueLabel->setText("--");
	ui.SNRZone5ValueLabel->setText("--");
	ui.SNRZone6ValueLabel->setText("--");
	ui.SNROverAllValueLabel->setText("--");

	//Sharpness
	ui.SharpnesZone1ValueLabel->setText("--");
	ui.SharpnesZone2ValueLabel->setText("--");
	ui.SharpnesZone3ValueLabel->setText("--");
	ui.SharpnesOverAllValueLabel->setText("--");

	//WOF
	ui.WOFZone0FDNoFingerLabel->setText("--");
	ui.WOFZone0FDWithFingerLabel->setText("--");
	ui.WOFZone0FDGainLabel->setText("--");
	ui.WOFZone0FDDeltaLabel->setText("--");

	ui.WOFZone0FUNoFingerLabel->setText("--");
	ui.WOFZone0FUWithFingerLabel->setText("--");
	ui.WOFZone0FUGainLabel->setText("--");
	ui.WOFZone0FUDeltaLabel->setText("--");

	ui.WOFZone1FDNoFingerLabel->setText("--");
	ui.WOFZone1FDWithFingerLabel->setText("--");
	ui.WOFZone1FDGainLabel->setText("--");
	ui.WOFZone1FDDeltaLabel->setText("--");

	ui.WOFZone1FUNoFingerLabel->setText("--");
	ui.WOFZone1FUWithFingerLabel->setText("--");
	ui.WOFZone1FUGainLabel->setText("--");
	ui.WOFZone1FUDeltaLabel->setText("--");

	//SCM_WOF
	ui.SCMWOFZone0NoFingerLabel->setText("--");
	ui.SCMWOFZone0WithFingerLabel->setText("--");
	ui.SCMWOFZone0GainLabel->setText("--");
	ui.SCMWOFZone0DeltaLabel->setText("--");

	ui.SCMWOFZone1NoFingerLabel->setText("--");
	ui.SCMWOFZone1WithFingerLabel->setText("--");
	ui.SCMWOFZone1GainLabel->setText("--");
	ui.SCMWOFZone1DeltaLabel->setText("--");

	//NoFinger
	ui.NoFingerLabel->setText("--");
	ui.NoFingerDataTableWidget->setRowCount(0);
	ui.NoFingerDataTableWidget->setColumnCount(0);

	//FakeFinger
	ui.FakeFingerLabel->setText("--");
	ui.FakeFingerDataTableWidget->setRowCount(0);
	ui.FakeFingerDataTableWidget->setColumnCount(0);

}

void Yangpu::TableWidgetCellClicked(int rowNumber, int columnNumber)
{
	if (rowNumber < 0)
		return;

	Syn_LogAnalyze *pSyn_LogAnalyze = _ListOfLogAnalyze[rowNumber];
	if (NULL == pSyn_LogAnalyze)
		return;
	Syn_LogAnalyzeValue *pSyn_LogAnalyzeValue = NULL;
	int rc = pSyn_LogAnalyze->GetLogContent(pSyn_LogAnalyzeValue);
	if (0 != rc || NULL == pSyn_LogAnalyzeValue)
		return;

	this->InitWidgetState();

	//Basic Info
	if (0 != pSyn_LogAnalyzeValue->SensorSerialNumber.size())
	{
		ui.SerialNumberLineEdit->setText(QString::fromStdString(pSyn_LogAnalyzeValue->SensorSerialNumber));
	}
	if (0 != pSyn_LogAnalyzeValue->SW_Version.size())
	{
		ui.SoftwareVersionLineEdit->setText(QString::fromStdString(pSyn_LogAnalyzeValue->SW_Version));
	}
	if (0 != pSyn_LogAnalyzeValue->ConfigFilePath.size())
	{
		ui.ConfigFileLineEdit->setText(QString::fromStdString(pSyn_LogAnalyzeValue->ConfigFilePath));
	}
	if (0 != pSyn_LogAnalyzeValue->DeviceSerialNumber)
		ui.textBrowser->append("Device SerialNumber:" + QString::number(pSyn_LogAnalyzeValue->DeviceSerialNumber) + "\n");
	if (0 != pSyn_LogAnalyzeValue->TestDate.size())
		ui.textBrowser->append("Test Time:" + QString::fromStdString(pSyn_LogAnalyzeValue->TestDate) + "\n");
	for (auto iter = pSyn_LogAnalyzeValue->mapOfTagValue.begin(); iter != pSyn_LogAnalyzeValue->mapOfTagValue.end(); iter++)
	{
		QString qsTagName = QString::fromStdString(iter->first);
		QString qsTagValue;
		for (size_t i = 0; i < iter->second.size(); i++)
		{
			if (0 == i)
			{
				qsTagValue = QString::fromStdString((iter->second)[i]);
			}
			else
			{
				qsTagValue = qsTagValue + "," + QString::fromStdString((iter->second)[i]);
			}
		}

		ui.textBrowser->append(qsTagName + ":" + qsTagValue+"\n");
	}

	//SNR
	if (pSyn_LogAnalyzeValue->SNRTestResult.bExcuted)
	{
		unsigned int signalCounts = pSyn_LogAnalyzeValue->SNRTestResult.listOfSignalValue.size();
		if (signalCounts >= 7)
		{
			ui.SignalZone1ValueLabel->setText(QString::number(pSyn_LogAnalyzeValue->SNRTestResult.listOfSignalValue[0]));
			ui.SignalZone2ValueLabel->setText(QString::number(pSyn_LogAnalyzeValue->SNRTestResult.listOfSignalValue[1]));
			ui.SignalZone3ValueLabel->setText(QString::number(pSyn_LogAnalyzeValue->SNRTestResult.listOfSignalValue[2]));
			ui.SignalZone4ValueLabel->setText(QString::number(pSyn_LogAnalyzeValue->SNRTestResult.listOfSignalValue[3]));
			ui.SignalZone5ValueLabel->setText(QString::number(pSyn_LogAnalyzeValue->SNRTestResult.listOfSignalValue[4]));
			ui.SignalZone6ValueLabel->setText(QString::number(pSyn_LogAnalyzeValue->SNRTestResult.listOfSignalValue[5]));
			ui.SignalOverAllValueLabel->setText(QString::number(pSyn_LogAnalyzeValue->SNRTestResult.listOfSignalValue[6]));
		}

		unsigned int noiseCounts = pSyn_LogAnalyzeValue->SNRTestResult.listOfNoiseValue.size();
		if (noiseCounts >= 7)
		{
			ui.NoiseZone1ValueLabel->setText(QString::number(pSyn_LogAnalyzeValue->SNRTestResult.listOfNoiseValue[0]));
			ui.NoiseZone2ValueLabel->setText(QString::number(pSyn_LogAnalyzeValue->SNRTestResult.listOfNoiseValue[1]));
			ui.NoiseZone3ValueLabel->setText(QString::number(pSyn_LogAnalyzeValue->SNRTestResult.listOfNoiseValue[2]));
			ui.NoiseZone4ValueLabel->setText(QString::number(pSyn_LogAnalyzeValue->SNRTestResult.listOfNoiseValue[3]));
			ui.NoiseZone5ValueLabel->setText(QString::number(pSyn_LogAnalyzeValue->SNRTestResult.listOfNoiseValue[4]));
			ui.NoiseZone6ValueLabel->setText(QString::number(pSyn_LogAnalyzeValue->SNRTestResult.listOfNoiseValue[5]));
			ui.NoiseOverAllValueLabel->setText(QString::number(pSyn_LogAnalyzeValue->SNRTestResult.listOfNoiseValue[6]));
		}

		unsigned int snrCounts = pSyn_LogAnalyzeValue->SNRTestResult.listOfSNRlValue.size();
		if (snrCounts >= 7)
		{
			ui.SNRZone1ValueLabel->setText(QString::number(pSyn_LogAnalyzeValue->SNRTestResult.listOfSNRlValue[0]));
			ui.SNRZone2ValueLabel->setText(QString::number(pSyn_LogAnalyzeValue->SNRTestResult.listOfSNRlValue[1]));
			ui.SNRZone3ValueLabel->setText(QString::number(pSyn_LogAnalyzeValue->SNRTestResult.listOfSNRlValue[2]));
			ui.SNRZone4ValueLabel->setText(QString::number(pSyn_LogAnalyzeValue->SNRTestResult.listOfSNRlValue[3]));
			ui.SNRZone5ValueLabel->setText(QString::number(pSyn_LogAnalyzeValue->SNRTestResult.listOfSNRlValue[4]));
			ui.SNRZone6ValueLabel->setText(QString::number(pSyn_LogAnalyzeValue->SNRTestResult.listOfSNRlValue[5]));
			ui.SNROverAllValueLabel->setText(QString::number(pSyn_LogAnalyzeValue->SNRTestResult.listOfSNRlValue[6]));
		}
	}

	//Sharpness
	if (pSyn_LogAnalyzeValue->SharpnessTestResult.bExcuted)
	{
		ui.SharpnesZone1ValueLabel->setText(QString::number(pSyn_LogAnalyzeValue->SharpnessTestResult.Zone0Sharpness));
		ui.SharpnesZone2ValueLabel->setText(QString::number(pSyn_LogAnalyzeValue->SharpnessTestResult.Zone1Sharpness));
		ui.SharpnesZone3ValueLabel->setText(QString::number(pSyn_LogAnalyzeValue->SharpnessTestResult.Zone2Sharpness));
		ui.SharpnesOverAllValueLabel->setText(QString::number(pSyn_LogAnalyzeValue->SharpnessTestResult.OverallSharpness));
	}

	//WOF
	if (pSyn_LogAnalyzeValue->Zone0FDWOFTestResult.bExcuted)
	{
		ui.WOFZone0FDNoFingerLabel->setText(QString::number(pSyn_LogAnalyzeValue->Zone0FDWOFTestResult.NoFingerValue));
		ui.WOFZone0FDWithFingerLabel->setText(QString::number(pSyn_LogAnalyzeValue->Zone0FDWOFTestResult.WithFingerValue));
		ui.WOFZone0FDGainLabel->setText(QString::number(pSyn_LogAnalyzeValue->Zone0FDWOFTestResult.GainValue));
		ui.WOFZone0FDDeltaLabel->setText(QString::number(pSyn_LogAnalyzeValue->Zone0FDWOFTestResult.DeltaValue));
	}

	if (pSyn_LogAnalyzeValue->Zone0FUWOFTestResult.bExcuted)
	{
		ui.WOFZone0FUNoFingerLabel->setText(QString::number(pSyn_LogAnalyzeValue->Zone0FUWOFTestResult.NoFingerValue));
		ui.WOFZone0FUWithFingerLabel->setText(QString::number(pSyn_LogAnalyzeValue->Zone0FUWOFTestResult.WithFingerValue));
		ui.WOFZone0FUGainLabel->setText(QString::number(pSyn_LogAnalyzeValue->Zone0FUWOFTestResult.GainValue));
		ui.WOFZone0FUDeltaLabel->setText(QString::number(pSyn_LogAnalyzeValue->Zone0FUWOFTestResult.DeltaValue));
	}

	if (pSyn_LogAnalyzeValue->Zone1FDWOFTestResult.bExcuted)
	{
		ui.WOFZone1FDNoFingerLabel->setText(QString::number(pSyn_LogAnalyzeValue->Zone1FDWOFTestResult.NoFingerValue));
		ui.WOFZone1FDWithFingerLabel->setText(QString::number(pSyn_LogAnalyzeValue->Zone1FDWOFTestResult.WithFingerValue));
		ui.WOFZone1FDGainLabel->setText(QString::number(pSyn_LogAnalyzeValue->Zone1FDWOFTestResult.GainValue));
		ui.WOFZone1FDDeltaLabel->setText(QString::number(pSyn_LogAnalyzeValue->Zone1FDWOFTestResult.DeltaValue));
	}

	if (pSyn_LogAnalyzeValue->Zone1FUWOFTestResult.bExcuted)
	{
		ui.WOFZone1FUNoFingerLabel->setText(QString::number(pSyn_LogAnalyzeValue->Zone1FUWOFTestResult.NoFingerValue));
		ui.WOFZone1FUWithFingerLabel->setText(QString::number(pSyn_LogAnalyzeValue->Zone1FUWOFTestResult.WithFingerValue));
		ui.WOFZone1FUGainLabel->setText(QString::number(pSyn_LogAnalyzeValue->Zone1FUWOFTestResult.GainValue));
		ui.WOFZone1FUDeltaLabel->setText(QString::number(pSyn_LogAnalyzeValue->Zone1FUWOFTestResult.DeltaValue));
	}

	//SCM_WOF
	if (pSyn_LogAnalyzeValue->Zone0SCMWOFTestResult.bExcuted)
	{
		ui.SCMWOFZone0NoFingerLabel->setText(QString::number(pSyn_LogAnalyzeValue->Zone0SCMWOFTestResult.NoFingerValue));
		ui.SCMWOFZone0WithFingerLabel->setText(QString::number(pSyn_LogAnalyzeValue->Zone0SCMWOFTestResult.WithFingerValue));
		ui.SCMWOFZone0GainLabel->setText(QString::number(pSyn_LogAnalyzeValue->Zone0SCMWOFTestResult.GainValue));
		ui.SCMWOFZone0DeltaLabel->setText(QString::number(pSyn_LogAnalyzeValue->Zone0SCMWOFTestResult.DeltaValue));
	}

	if (pSyn_LogAnalyzeValue->Zone1SCMWOFTestResult.bExcuted)
	{
		ui.SCMWOFZone1NoFingerLabel->setText(QString::number(pSyn_LogAnalyzeValue->Zone1SCMWOFTestResult.NoFingerValue));
		ui.SCMWOFZone1WithFingerLabel->setText(QString::number(pSyn_LogAnalyzeValue->Zone1SCMWOFTestResult.WithFingerValue));
		ui.SCMWOFZone1GainLabel->setText(QString::number(pSyn_LogAnalyzeValue->Zone1SCMWOFTestResult.GainValue));
		ui.SCMWOFZone1DeltaLabel->setText(QString::number(pSyn_LogAnalyzeValue->Zone1SCMWOFTestResult.DeltaValue));
	}

	//NoFinger
	if (pSyn_LogAnalyzeValue->NoFingerResult.bExcuted)
	{
		int RowNumber = pSyn_LogAnalyzeValue->NoFingerResult.RowNumber;
		int ColumnNumber = pSyn_LogAnalyzeValue->NoFingerResult.ColumnNumber;
		QVector<QRgb> vcolorTable;
		for (int i = 0; i < 256; i++)
			vcolorTable.append(qRgb(i, i, i));
		QByteArray data;
		data.resize((RowNumber)*(ColumnNumber));
		int k(0);
		for (int m = 0; m < RowNumber; m++)
		{
			for (int n = 0; n < ColumnNumber; n++)
			{
				data[k] = pSyn_LogAnalyzeValue->NoFingerResult.arr_NoFinger[m][n];
				k++;
			}
		}
		QImage image((const uchar*)data.constData(), ColumnNumber, RowNumber, ColumnNumber, QImage::Format_Indexed8);
		image.setColorTable(vcolorTable);
		image = image.scaled(ColumnNumber * 2, RowNumber * 2);
		ui.NoFingerLabel->setPixmap(QPixmap::fromImage(image));
		ui.NoFingerLabel->setAlignment(Qt::AlignCenter);

		//Fill NoFinger TableWidget
		ui.NoFingerDataTableWidget->setRowCount(RowNumber);
		ui.NoFingerDataTableWidget->setColumnCount(ColumnNumber);
		for (int m = 0; m < RowNumber; m++)
		{
			for (int n = 0; n < ColumnNumber; n++)
			{
				QTableWidgetItem *itemNoFinger = new QTableWidgetItem(QString::number(pSyn_LogAnalyzeValue->NoFingerResult.arr_NoFinger[m][n]));
				if (NULL != itemNoFinger)
					ui.NoFingerDataTableWidget->setItem(m, n, itemNoFinger);
			}
		}
		for (int i = 0; i < ColumnNumber; i++)
		{
			ui.NoFingerDataTableWidget->resizeColumnToContents(i);
		}
	}

	//FakeFinger
	if (pSyn_LogAnalyzeValue->FakeFingerResult.bExcuted)
	{
		int RowNumber = pSyn_LogAnalyzeValue->FakeFingerResult.RowNumber;
		int ColumnNumber = pSyn_LogAnalyzeValue->FakeFingerResult.ColumnNumber;
		QVector<QRgb> vcolorTable;
		for (int i = 0; i < 256; i++)
			vcolorTable.append(qRgb(i, i, i));
		QByteArray data;
		data.resize((RowNumber)*(ColumnNumber));
		int k(0);
		for (int m = 0; m < RowNumber; m++)
		{
			for (int n = 0; n < ColumnNumber; n++)
			{
				data[k] = pSyn_LogAnalyzeValue->FakeFingerResult.arr_FakeFinger[m][n];
				k++;
			}
		}

		QImage image((const uchar*)data.constData(), ColumnNumber, RowNumber, ColumnNumber, QImage::Format_Indexed8);
		image.setColorTable(vcolorTable);
		image = image.scaled(ColumnNumber * 2, RowNumber * 2);
		ui.FakeFingerLabel->setPixmap(QPixmap::fromImage(image));
		ui.FakeFingerLabel->setAlignment(Qt::AlignCenter);

		//Fill FakeFinger TableWidget
		ui.FakeFingerDataTableWidget->setRowCount(RowNumber);
		ui.FakeFingerDataTableWidget->setColumnCount(ColumnNumber);
		for (int m = 0; m < RowNumber; m++)
		{
			for (int n = 0; n < ColumnNumber; n++)
			{
				QTableWidgetItem *itemFakeFinger = new QTableWidgetItem(QString::number(pSyn_LogAnalyzeValue->FakeFingerResult.arr_FakeFinger[m][n]));
				if (NULL != itemFakeFinger)
					ui.FakeFingerDataTableWidget->setItem(m, n, itemFakeFinger);
			}
		}
		for (int i = 0; i < ColumnNumber; i++)
		{
			ui.FakeFingerDataTableWidget->resizeColumnToContents(i);
		}
	}
}

void Yangpu::SaveExcel()
{
	unsigned int ListCounts = _ListOfLogAnalyze.size();
	if (0 == ListCounts)
		return;

	QString strExcelFilePath = QFileDialog::getSaveFileName(this, "Select Excel File", "", "Excel file(*.xlsx);;Excel file (*.xls)");
	if (QString("") == strExcelFilePath)
		return;

	QAxObject *excel = new QAxObject(this);
	if (NULL==excel)
		return;
	if (!excel->setControl("Excel.Application"))
	{
		delete excel;
		excel = NULL;
		return;
	}
	excel->dynamicCall("SetVisible (bool Visible)", "false");
	excel->setProperty("DisplayAlerts", false);

	QAxObject *workbooks = excel->querySubObject("WorkBooks"); 
	workbooks->dynamicCall("Add");
	QAxObject *workbook = excel->querySubObject("ActiveWorkBook"); 
	QAxObject *worksheets = workbook->querySubObject("Sheets");
	QAxObject *worksheet = worksheets->querySubObject("Item(int)", 1);

	//title
	QAxObject *SerialNuberTitleCell = worksheet->querySubObject("Range(QVariant, QVariant)", "A" + QString::number(1));
	if (NULL != SerialNuberTitleCell)
	{
		SerialNuberTitleCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("SensorSerialNumber")));

		QString merge_cell;
		merge_cell.append(QChar('A'));
		merge_cell.append(QString::number(1));
		merge_cell.append(":");
		merge_cell.append(QChar('A'));
		merge_cell.append(QString::number(2));
		QAxObject *merge_range = worksheet->querySubObject("Range(const QString&)", merge_cell);
		merge_range->setProperty("HorizontalAlignment", -4108);
		merge_range->setProperty("VerticalAlignment", -4108);
		merge_range->setProperty("WrapText", true);
		merge_range->setProperty("MergeCells", true);
	}
	QAxObject *ResultTitleCell = worksheet->querySubObject("Range(QVariant, QVariant)", "B" + QString::number(1));
	if (NULL != ResultTitleCell)
	{
		ResultTitleCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("Result")));

		QString merge_cell;
		merge_cell.append(QChar('B'));
		merge_cell.append(QString::number(1));
		merge_cell.append(":");
		merge_cell.append(QChar('B'));
		merge_cell.append(QString::number(2));
		QAxObject *merge_range = worksheet->querySubObject("Range(const QString&)", merge_cell);
		merge_range->setProperty("HorizontalAlignment", -4108);
		merge_range->setProperty("VerticalAlignment", -4108);
		merge_range->setProperty("WrapText", true);
		merge_range->setProperty("MergeCells", true);
	}
		
	QAxObject *SignalTitleCell = worksheet->querySubObject("Range(QVariant, QVariant)", "C" + QString::number(1));
	if (NULL != SignalTitleCell)
	{
		SignalTitleCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("Signal")));
		
		QString merge_cell;
		merge_cell.append(QChar('C'));
		merge_cell.append(QString::number(1));
		merge_cell.append(":");
		merge_cell.append(QChar('C'));
		merge_cell.append(QString::number(2));
		QAxObject *merge_range = worksheet->querySubObject("Range(const QString&)", merge_cell);
		merge_range->setProperty("HorizontalAlignment", -4108);
		merge_range->setProperty("VerticalAlignment", -4108);
		merge_range->setProperty("WrapText", true);
		merge_range->setProperty("MergeCells", true);
	}

	QAxObject *NoiseTitleCell = worksheet->querySubObject("Range(QVariant, QVariant)", "D" + QString::number(1));
	if (NULL != NoiseTitleCell)
	{
		NoiseTitleCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("Noise")));

		QString merge_cell;
		merge_cell.append(QChar('D'));
		merge_cell.append(QString::number(1));
		merge_cell.append(":");
		merge_cell.append(QChar('D'));
		merge_cell.append(QString::number(2));
		QAxObject *merge_range = worksheet->querySubObject("Range(const QString&)", merge_cell);
		merge_range->setProperty("HorizontalAlignment", -4108);
		merge_range->setProperty("VerticalAlignment", -4108);
		merge_range->setProperty("WrapText", true);
		merge_range->setProperty("MergeCells", true);
	}

	QAxObject *SNRTitleCell = worksheet->querySubObject("Range(QVariant, QVariant)", "E" + QString::number(1));
	if (NULL != SNRTitleCell)
	{
		SNRTitleCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("SNR")));

		QString merge_cell;
		merge_cell.append(QChar('E'));
		merge_cell.append(QString::number(1));
		merge_cell.append(":");
		merge_cell.append(QChar('E'));
		merge_cell.append(QString::number(2));
		QAxObject *merge_range = worksheet->querySubObject("Range(const QString&)", merge_cell);
		merge_range->setProperty("HorizontalAlignment", -4108);
		merge_range->setProperty("VerticalAlignment", -4108);
		merge_range->setProperty("WrapText", true);
		merge_range->setProperty("MergeCells", true);
	}
		
	QAxObject *SharpnessTitleCell = worksheet->querySubObject("Range(QVariant, QVariant)", "F" + QString::number(1));
	if (NULL != SharpnessTitleCell)
	{
		SharpnessTitleCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("Sharpness")));
		QString merge_cell;
		merge_cell.append(QChar('F'));
		merge_cell.append(QString::number(1));
		merge_cell.append(":");
		merge_cell.append(QChar('F'));
		merge_cell.append(QString::number(2));
		QAxObject *merge_range = worksheet->querySubObject("Range(const QString&)", merge_cell);
		merge_range->setProperty("HorizontalAlignment", -4108);
		merge_range->setProperty("VerticalAlignment", -4108);
		merge_range->setProperty("WrapText", true);
		merge_range->setProperty("MergeCells", true);
	}
		
	QAxObject *BinCodeTitleCell = worksheet->querySubObject("Range(QVariant, QVariant)", "G" + QString::number(1));
	if (NULL != BinCodeTitleCell)
	{
		BinCodeTitleCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("BinCodes")));

		QString merge_cell;
		merge_cell.append(QChar('G'));
		merge_cell.append(QString::number(1));
		merge_cell.append(":");
		merge_cell.append(QChar('G'));
		merge_cell.append(QString::number(2));
		QAxObject *merge_range = worksheet->querySubObject("Range(const QString&)", merge_cell);
		merge_range->setProperty("HorizontalAlignment", -4108);
		merge_range->setProperty("VerticalAlignment", -4108);
		merge_range->setProperty("WrapText", true);
		merge_range->setProperty("MergeCells", true);
	}
	
	QAxObject *WOFZone0FDTitleCell = worksheet->querySubObject("Range(QVariant, QVariant)", "H" + QString::number(1));
	if (NULL != WOFZone0FDTitleCell)
	{
		WOFZone0FDTitleCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("WOF Zone0 FingerDown")));

		QString merge_cell;
		merge_cell.append(QChar('H'));
		merge_cell.append(QString::number(1));
		merge_cell.append(":");
		merge_cell.append(QChar('K'));
		merge_cell.append(QString::number(1));
		QAxObject *merge_range = worksheet->querySubObject("Range(const QString&)", merge_cell);
		merge_range->setProperty("HorizontalAlignment", -4108);
		merge_range->setProperty("VerticalAlignment", -4108);
		merge_range->setProperty("WrapText", true);
		merge_range->setProperty("MergeCells", true);

		QAxObject *NoFingerCell = worksheet->querySubObject("Range(QVariant, QVariant)", "H" + QString::number(2));
		if (NULL != NoFingerCell)
			NoFingerCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("No Finger")));
		QAxObject *WithFingerCell = worksheet->querySubObject("Range(QVariant, QVariant)", "I" + QString::number(2));
		if (NULL != WithFingerCell)
			WithFingerCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("With Finger")));
		QAxObject *GainCell = worksheet->querySubObject("Range(QVariant, QVariant)", "J" + QString::number(2));
		if (NULL != GainCell)
			GainCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("Gain")));
		QAxObject *DeltaCell = worksheet->querySubObject("Range(QVariant, QVariant)", "K" + QString::number(2));
		if (NULL != DeltaCell)
			DeltaCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("Delta")));
	}
		
	QAxObject *WOFZone0FUTitleCell = worksheet->querySubObject("Range(QVariant, QVariant)", "L" + QString::number(1));
	if (NULL != WOFZone0FUTitleCell)
	{
		WOFZone0FUTitleCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("WOF Zone0 FingerUp")));

		QString merge_cell;
		merge_cell.append(QChar('L'));
		merge_cell.append(QString::number(1));
		merge_cell.append(":");
		merge_cell.append(QChar('O'));
		merge_cell.append(QString::number(1));
		QAxObject *merge_range = worksheet->querySubObject("Range(const QString&)", merge_cell);
		merge_range->setProperty("HorizontalAlignment", -4108);
		merge_range->setProperty("VerticalAlignment", -4108);
		merge_range->setProperty("WrapText", true);
		merge_range->setProperty("MergeCells", true);

		QAxObject *NoFingerCell = worksheet->querySubObject("Range(QVariant, QVariant)", "L" + QString::number(2));
		if (NULL != NoFingerCell)
			NoFingerCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("No Finger")));
		QAxObject *WithFingerCell = worksheet->querySubObject("Range(QVariant, QVariant)", "M" + QString::number(2));
		if (NULL != WithFingerCell)
			WithFingerCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("With Finger")));
		QAxObject *GainCell = worksheet->querySubObject("Range(QVariant, QVariant)", "N" + QString::number(2));
		if (NULL != GainCell)
			GainCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("Gain")));
		QAxObject *DeltaCell = worksheet->querySubObject("Range(QVariant, QVariant)", "O" + QString::number(2));
		if (NULL != DeltaCell)
			DeltaCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("Delta")));
	}
		
	QAxObject *WOFZone1FDTitleCell = worksheet->querySubObject("Range(QVariant, QVariant)", "P" + QString::number(1));
	if (NULL != WOFZone1FDTitleCell)
	{
		WOFZone1FDTitleCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("WOF Zone1 FingerDown")));

		QString merge_cell;
		merge_cell.append(QChar('P'));
		merge_cell.append(QString::number(1));
		merge_cell.append(":");
		merge_cell.append(QChar('S'));
		merge_cell.append(QString::number(1));
		QAxObject *merge_range = worksheet->querySubObject("Range(const QString&)", merge_cell);
		merge_range->setProperty("HorizontalAlignment", -4108);
		merge_range->setProperty("VerticalAlignment", -4108);
		merge_range->setProperty("WrapText", true);
		merge_range->setProperty("MergeCells", true);

		QAxObject *NoFingerCell = worksheet->querySubObject("Range(QVariant, QVariant)", "P" + QString::number(2));
		if (NULL != NoFingerCell)
			NoFingerCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("No Finger")));
		QAxObject *WithFingerCell = worksheet->querySubObject("Range(QVariant, QVariant)", "Q" + QString::number(2));
		if (NULL != WithFingerCell)
			WithFingerCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("With Finger")));
		QAxObject *GainCell = worksheet->querySubObject("Range(QVariant, QVariant)", "R" + QString::number(2));
		if (NULL != GainCell)
			GainCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("Gain")));
		QAxObject *DeltaCell = worksheet->querySubObject("Range(QVariant, QVariant)", "S" + QString::number(2));
		if (NULL != DeltaCell)
			DeltaCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("Delta")));
	}

	QAxObject *WOFZone1FUTitleCell = worksheet->querySubObject("Range(QVariant, QVariant)", "T" + QString::number(1));
	if (NULL != WOFZone1FUTitleCell)
	{
		WOFZone1FUTitleCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("WOF Zone1 FingerUp")));

		QString merge_cell;
		merge_cell.append(QChar('T'));
		merge_cell.append(QString::number(1));
		merge_cell.append(":");
		merge_cell.append(QChar('W'));
		merge_cell.append(QString::number(1));
		QAxObject *merge_range = worksheet->querySubObject("Range(const QString&)", merge_cell);
		merge_range->setProperty("HorizontalAlignment", -4108);
		merge_range->setProperty("VerticalAlignment", -4108);
		merge_range->setProperty("WrapText", true);
		merge_range->setProperty("MergeCells", true);

		QAxObject *NoFingerCell = worksheet->querySubObject("Range(QVariant, QVariant)", "T" + QString::number(2));
		if (NULL != NoFingerCell)
			NoFingerCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("No Finger")));
		QAxObject *WithFingerCell = worksheet->querySubObject("Range(QVariant, QVariant)", "U" + QString::number(2));
		if (NULL != WithFingerCell)
			WithFingerCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("With Finger")));
		QAxObject *GainCell = worksheet->querySubObject("Range(QVariant, QVariant)", "V" + QString::number(2));
		if (NULL != GainCell)
			GainCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("Gain")));
		QAxObject *DeltaCell = worksheet->querySubObject("Range(QVariant, QVariant)", "W" + QString::number(2));
		if (NULL != DeltaCell)
			DeltaCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("Delta")));
	}

	QAxObject *SCMWOFZone0TitleCell = worksheet->querySubObject("Range(QVariant, QVariant)", "X" + QString::number(1));
	if (NULL != SCMWOFZone0TitleCell)
	{
		SCMWOFZone0TitleCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("SCM WOF Zone0/Bottom")));

		QString merge_cell;
		merge_cell.append(QChar('X'));
		merge_cell.append(QString::number(1));
		merge_cell.append(":");
		merge_cell.append("AA");
		merge_cell.append(QString::number(1));
		QAxObject *merge_range = worksheet->querySubObject("Range(const QString&)", merge_cell);
		merge_range->setProperty("HorizontalAlignment", -4108);
		merge_range->setProperty("VerticalAlignment", -4108);
		merge_range->setProperty("WrapText", true);
		merge_range->setProperty("MergeCells", true);

		QAxObject *NoFingerCell = worksheet->querySubObject("Range(QVariant, QVariant)", "X" + QString::number(2));
		if (NULL != NoFingerCell)
			NoFingerCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("No Finger")));
		QAxObject *WithFingerCell = worksheet->querySubObject("Range(QVariant, QVariant)", "Y" + QString::number(2));
		if (NULL != WithFingerCell)
			WithFingerCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("With Finger")));
		QAxObject *GainCell = worksheet->querySubObject("Range(QVariant, QVariant)", "Z" + QString::number(2));
		if (NULL != GainCell)
			GainCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("Gain")));
		QAxObject *DeltaCell = worksheet->querySubObject("Range(QVariant, QVariant)", "AA" + QString::number(2));
		if (NULL != DeltaCell)
			DeltaCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("Delta")));
	}

	QAxObject *SCMWOFZone1TitleCell = worksheet->querySubObject("Range(QVariant, QVariant)", "AB" + QString::number(1));
	if (NULL != SCMWOFZone1TitleCell)
	{
		SCMWOFZone1TitleCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("SCM WOF Zone1/Top")));

		QString merge_cell;
		merge_cell.append("AB");
		merge_cell.append(QString::number(1));
		merge_cell.append(":");
		merge_cell.append("AE");
		merge_cell.append(QString::number(1));
		QAxObject *merge_range = worksheet->querySubObject("Range(const QString&)", merge_cell);
		merge_range->setProperty("HorizontalAlignment", -4108);
		merge_range->setProperty("VerticalAlignment", -4108);
		merge_range->setProperty("WrapText", true);
		merge_range->setProperty("MergeCells", true);

		QAxObject *NoFingerCell = worksheet->querySubObject("Range(QVariant, QVariant)", "AB" + QString::number(2));
		if (NULL != NoFingerCell)
			NoFingerCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("No Finger")));
		QAxObject *WithFingerCell = worksheet->querySubObject("Range(QVariant, QVariant)", "AC" + QString::number(2));
		if (NULL != WithFingerCell)
			WithFingerCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("With Finger")));
		QAxObject *GainCell = worksheet->querySubObject("Range(QVariant, QVariant)", "AD" + QString::number(2));
		if (NULL != GainCell)
			GainCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("Gain")));
		QAxObject *DeltaCell = worksheet->querySubObject("Range(QVariant, QVariant)", "AE" + QString::number(2));
		if (NULL != DeltaCell)
			DeltaCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("Delta")));
	}

	/*QAxObject *NoFingerTitleCell = worksheet->querySubObject("Range(QVariant, QVariant)", "AF" + QString::number(1));
	if (NULL != NoFingerTitleCell)
	{
		NoFingerTitleCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("NoFinger")));
		QString merge_cell;
		merge_cell.append("AF");
		merge_cell.append(QString::number(1));
		merge_cell.append(":");
		merge_cell.append("AF");
		merge_cell.append(QString::number(2));
		QAxObject *merge_range = worksheet->querySubObject("Range(const QString&)", merge_cell);
		merge_range->setProperty("HorizontalAlignment", -4108);
		merge_range->setProperty("VerticalAlignment", -4108);
		merge_range->setProperty("WrapText", true);
		merge_range->setProperty("MergeCells", true);
	}
	QAxObject *FakeFingerTitleCell = worksheet->querySubObject("Range(QVariant, QVariant)", "AG" + QString::number(1));
	if (NULL != FakeFingerTitleCell)
	{
		FakeFingerTitleCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString("FakeFinger")));
		QString merge_cell;
		merge_cell.append("AG");
		merge_cell.append(QString::number(1));
		merge_cell.append(":");
		merge_cell.append("AG");
		merge_cell.append(QString::number(2));
		QAxObject *merge_range = worksheet->querySubObject("Range(const QString&)", merge_cell);
		merge_range->setProperty("HorizontalAlignment", -4108);
		merge_range->setProperty("VerticalAlignment", -4108);
		merge_range->setProperty("WrapText", true);
		merge_range->setProperty("MergeCells", true);
	}*/
	
	//content
	for (unsigned i = 0; i<ListCounts; i++)
	{
		Syn_LogAnalyze *pSyn_LogAnalyze = _ListOfLogAnalyze[i];
		if (NULL == pSyn_LogAnalyze)
			continue;
		Syn_LogAnalyzeValue *pSyn_LogAnalyzeValue = NULL;
		pSyn_LogAnalyze->GetLogContent(pSyn_LogAnalyzeValue);
		if (NULL == pSyn_LogAnalyzeValue)
			continue;

		//Sensor SerialNumber
		if (0 != pSyn_LogAnalyzeValue->SensorSerialNumber.size())
		{
			QAxObject *itemSensorSerialNbCell = worksheet->querySubObject("Range(QVariant, QVariant)", "A" + QString::number(i + 3));
			if (NULL != itemSensorSerialNbCell)
			{
				itemSensorSerialNbCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::fromStdString(pSyn_LogAnalyzeValue->SensorSerialNumber)));
			}
		}

		//Result,BinCodes
		if (0 != pSyn_LogAnalyzeValue->listOfBinCode.size())
		{
			//Result
			QString qsResult("");
			QColor qColor;
			if (1 == pSyn_LogAnalyzeValue->listOfBinCode.size() && "1" == pSyn_LogAnalyzeValue->listOfBinCode[0])
			{
				qsResult = "Pass";
				qColor = QColor(0, 255, 0);
			}
			else
			{
				qsResult = "Fail";
				qColor = QColor(255, 0, 0);
			}

			QAxObject *itemResultCell = worksheet->querySubObject("Range(QVariant, QVariant)", "B" + QString::number(i + 3));
			if (NULL != itemResultCell)
			{
				itemResultCell->dynamicCall("SetValue(const QVariant&)", QVariant(qsResult));
				QAxObject * interior = itemResultCell->querySubObject("Interior");
				if (NULL != interior)
					interior->setProperty("Color", qColor);
			}

			//BinCodes
			std::string strBinCodesValue = pSyn_LogAnalyzeValue->listOfBinCode[0];
			if (1 != pSyn_LogAnalyzeValue->listOfBinCode.size())
			{
				for (size_t i = 1; i < pSyn_LogAnalyzeValue->listOfBinCode.size(); i++)
				{
					strBinCodesValue = strBinCodesValue + "  " + pSyn_LogAnalyzeValue->listOfBinCode[i];
				}
			}
			QAxObject *itemBinCodesCell = worksheet->querySubObject("Range(QVariant, QVariant)", "G" + QString::number(i + 3));
			if (NULL != itemBinCodesCell)
				itemBinCodesCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::fromStdString(strBinCodesValue)));
		}

		//Signal,Noise,SNR
		if (pSyn_LogAnalyzeValue->SNRTestResult.bExcuted)
		{
			QAxObject *itemSignalCell = worksheet->querySubObject("Range(QVariant, QVariant)", "C" + QString::number(i + 3));
			if (NULL != itemSignalCell)
				itemSignalCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->SNRTestResult.listOfSignalValue[pSyn_LogAnalyzeValue->SNRTestResult.listOfSignalValue.size() - 1])));
			
			QAxObject *itemNoiseCell = worksheet->querySubObject("Range(QVariant, QVariant)", "D" + QString::number(i + 3));
			if (NULL != itemNoiseCell)
				itemNoiseCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->SNRTestResult.listOfNoiseValue[pSyn_LogAnalyzeValue->SNRTestResult.listOfNoiseValue.size() - 1])));

			QAxObject *itemSNRCell = worksheet->querySubObject("Range(QVariant, QVariant)", "E" + QString::number(i + 3));
			if (NULL != itemSNRCell)
				itemSNRCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->SNRTestResult.listOfSNRlValue[pSyn_LogAnalyzeValue->SNRTestResult.listOfSNRlValue.size() - 1])));
		}

		//Sharpness
		if (pSyn_LogAnalyzeValue->SharpnessTestResult.bExcuted)
		{
			QAxObject *itemSharpnessCell = worksheet->querySubObject("Range(QVariant, QVariant)", "F" + QString::number(i + 3));
			if (NULL != itemSharpnessCell)
				itemSharpnessCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->SharpnessTestResult.OverallSharpness)));
		}

		//WOF Zone0 FingerDown
		if (pSyn_LogAnalyzeValue->Zone0FDWOFTestResult.bExcuted)
		{
			QAxObject *itemNoFingerCell = worksheet->querySubObject("Range(QVariant, QVariant)", "H" + QString::number(i + 3));
			if (NULL != itemNoFingerCell)
				itemNoFingerCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->Zone0FDWOFTestResult.NoFingerValue)));

			QAxObject *itemWithFingerCell = worksheet->querySubObject("Range(QVariant, QVariant)", "I" + QString::number(i + 3));
			if (NULL != itemWithFingerCell)
				itemWithFingerCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->Zone0FDWOFTestResult.WithFingerValue)));

			QAxObject *itemGainCell = worksheet->querySubObject("Range(QVariant, QVariant)", "J" + QString::number(i + 3));
			if (NULL != itemGainCell)
				itemGainCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->Zone0FDWOFTestResult.GainValue)));

			QAxObject *itemDeltaCell = worksheet->querySubObject("Range(QVariant, QVariant)", "K" + QString::number(i + 3));
			if (NULL != itemDeltaCell)
				itemDeltaCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->Zone0FDWOFTestResult.DeltaValue)));
		}

		//WOF Zone0 FingerUp
		if (pSyn_LogAnalyzeValue->Zone0FUWOFTestResult.bExcuted)
		{
			QAxObject *itemNoFingerCell = worksheet->querySubObject("Range(QVariant, QVariant)", "L" + QString::number(i + 3));
			if (NULL != itemNoFingerCell)
				itemNoFingerCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->Zone0FUWOFTestResult.NoFingerValue)));

			QAxObject *itemWithFingerCell = worksheet->querySubObject("Range(QVariant, QVariant)", "M" + QString::number(i + 3));
			if (NULL != itemWithFingerCell)
				itemWithFingerCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->Zone0FUWOFTestResult.WithFingerValue)));

			QAxObject *itemGainCell = worksheet->querySubObject("Range(QVariant, QVariant)", "N" + QString::number(i + 3));
			if (NULL != itemGainCell)
				itemGainCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->Zone0FUWOFTestResult.GainValue)));

			QAxObject *itemDeltaCell = worksheet->querySubObject("Range(QVariant, QVariant)", "O" + QString::number(i + 3));
			if (NULL != itemDeltaCell)
				itemDeltaCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->Zone0FUWOFTestResult.DeltaValue)));
		}

		//WOF Zone1 FingerDown
		if (pSyn_LogAnalyzeValue->Zone1FDWOFTestResult.bExcuted)
		{
			QAxObject *itemNoFingerCell = worksheet->querySubObject("Range(QVariant, QVariant)", "P" + QString::number(i + 3));
			if (NULL != itemNoFingerCell)
				itemNoFingerCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->Zone1FDWOFTestResult.NoFingerValue)));

			QAxObject *itemWithFingerCell = worksheet->querySubObject("Range(QVariant, QVariant)", "Q" + QString::number(i + 3));
			if (NULL != itemWithFingerCell)
				itemWithFingerCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->Zone1FDWOFTestResult.WithFingerValue)));

			QAxObject *itemGainCell = worksheet->querySubObject("Range(QVariant, QVariant)", "R" + QString::number(i + 3));
			if (NULL != itemGainCell)
				itemGainCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->Zone1FDWOFTestResult.GainValue)));

			QAxObject *itemDeltaCell = worksheet->querySubObject("Range(QVariant, QVariant)", "S" + QString::number(i + 3));
			if (NULL != itemDeltaCell)
				itemDeltaCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->Zone1FDWOFTestResult.DeltaValue)));
		}

		//WOF Zone1 FingerUp
		if (pSyn_LogAnalyzeValue->Zone1FUWOFTestResult.bExcuted)
		{
			QAxObject *itemNoFingerCell = worksheet->querySubObject("Range(QVariant, QVariant)", "T" + QString::number(i + 3));
			if (NULL != itemNoFingerCell)
				itemNoFingerCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->Zone1FUWOFTestResult.NoFingerValue)));

			QAxObject *itemWithFingerCell = worksheet->querySubObject("Range(QVariant, QVariant)", "U" + QString::number(i + 3));
			if (NULL != itemWithFingerCell)
				itemWithFingerCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->Zone1FUWOFTestResult.WithFingerValue)));

			QAxObject *itemGainCell = worksheet->querySubObject("Range(QVariant, QVariant)", "V" + QString::number(i + 3));
			if (NULL != itemGainCell)
				itemGainCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->Zone1FUWOFTestResult.GainValue)));

			QAxObject *itemDeltaCell = worksheet->querySubObject("Range(QVariant, QVariant)", "W" + QString::number(i + 3));
			if (NULL != itemDeltaCell)
				itemDeltaCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->Zone1FUWOFTestResult.DeltaValue)));
		}

		//SCM WOF Zone0/Bottom
		if (pSyn_LogAnalyzeValue->Zone0SCMWOFTestResult.bExcuted)
		{
			QAxObject *itemNoFingerCell = worksheet->querySubObject("Range(QVariant, QVariant)", "X" + QString::number(i + 3));
			if (NULL != itemNoFingerCell)
				itemNoFingerCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->Zone0SCMWOFTestResult.NoFingerValue)));

			QAxObject *itemWithFingerCell = worksheet->querySubObject("Range(QVariant, QVariant)", "Y" + QString::number(i + 3));
			if (NULL != itemWithFingerCell)
				itemWithFingerCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->Zone0SCMWOFTestResult.WithFingerValue)));

			QAxObject *itemGainCell = worksheet->querySubObject("Range(QVariant, QVariant)", "Z" + QString::number(i + 3));
			if (NULL != itemGainCell)
				itemGainCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->Zone0SCMWOFTestResult.GainValue)));

			QAxObject *itemDeltaCell = worksheet->querySubObject("Range(QVariant, QVariant)", "AA" + QString::number(i + 3));
			if (NULL != itemDeltaCell)
				itemDeltaCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->Zone0SCMWOFTestResult.DeltaValue)));
		}

		//SCM WOF Zone1/Top
		if (pSyn_LogAnalyzeValue->Zone1SCMWOFTestResult.bExcuted)
		{
			QAxObject *itemNoFingerCell = worksheet->querySubObject("Range(QVariant, QVariant)", "AB" + QString::number(i + 3));
			if (NULL != itemNoFingerCell)
				itemNoFingerCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->Zone1SCMWOFTestResult.NoFingerValue)));

			QAxObject *itemWithFingerCell = worksheet->querySubObject("Range(QVariant, QVariant)", "AC" + QString::number(i + 3));
			if (NULL != itemWithFingerCell)
				itemWithFingerCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->Zone1SCMWOFTestResult.WithFingerValue)));

			QAxObject *itemGainCell = worksheet->querySubObject("Range(QVariant, QVariant)", "AD" + QString::number(i + 3));
			if (NULL != itemGainCell)
				itemGainCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->Zone1SCMWOFTestResult.GainValue)));

			QAxObject *itemDeltaCell = worksheet->querySubObject("Range(QVariant, QVariant)", "AE" + QString::number(i + 3));
			if (NULL != itemDeltaCell)
				itemDeltaCell->dynamicCall("SetValue(const QVariant&)", QVariant(QString::number(pSyn_LogAnalyzeValue->Zone1SCMWOFTestResult.DeltaValue)));
		}

		//Pic
		/*if (pSyn_LogAnalyzeValue->NoFingerResult.bExcuted)
		{
			int RowNumber = pSyn_LogAnalyzeValue->NoFingerResult.RowNumber;
			int ColumnNumber = pSyn_LogAnalyzeValue->NoFingerResult.ColumnNumber;
			QVector<QRgb> vcolorTable;
			for (int a = 0; a < 256; a++)
				vcolorTable.append(qRgb(a, a, a));
			QByteArray data;
			data.resize((RowNumber)*(ColumnNumber));
			int k(0);
			for (int m = 0; m < RowNumber; m++)
			{
				for (int n = 0; n < ColumnNumber; n++)
				{
					data[k] = pSyn_LogAnalyzeValue->NoFingerResult.arr_NoFinger[m][n];
					k++;
				}
			}
			QImage image((const uchar*)data.constData(), ColumnNumber, RowNumber, ColumnNumber, QImage::Format_Indexed8);
			image.setColorTable(vcolorTable);
			QAxObject *itemNoFingerImageCell = worksheet->querySubObject("Range(QVariant, QVariant)", "AF" + QString::number(i + 3));
			QAxObject *shapes = worksheet->querySubObject("Shapes");
			if (!shapes->isNull())
			{
				image.save("./1.bmp");
				shapes->dynamicCall("AddPicture( QString&, bool, bool, double, double, double, double)", "./1.bmp", true, true, 14, i + 2, ColumnNumber, RowNumber);
			}
		}

		if (pSyn_LogAnalyzeValue->FakeFingerResult.bExcuted)
		{
			int RowNumber = pSyn_LogAnalyzeValue->FakeFingerResult.RowNumber;
			int ColumnNumber = pSyn_LogAnalyzeValue->FakeFingerResult.ColumnNumber;
			QVector<QRgb> vcolorTable;
			for (int a = 0; a < 256; a++)
				vcolorTable.append(qRgb(a, a, a));
			QByteArray data;
			data.resize((RowNumber)*(ColumnNumber));
			int k(0);
			for (int m = 0; m < RowNumber; m++)
			{
				for (int n = 0; n < ColumnNumber; n++)
				{
					data[k] = pSyn_LogAnalyzeValue->FakeFingerResult.arr_FakeFinger[m][n];
					k++;
				}
			}

			QImage image((const uchar*)data.constData(), ColumnNumber, RowNumber, ColumnNumber, QImage::Format_Indexed8);
			image.setColorTable(vcolorTable);
			QAxObject *itemFakeFingerImageCell = worksheet->querySubObject("Range(QVariant, QVariant)", "AG" + QString::number(i + 3));
			if (NULL != itemFakeFingerImageCell)
			{
				QAxObject *shapes = itemFakeFingerImageCell->querySubObject("Shapes");
				if (NULL!=shapes)
				{
					image.save("./1.bmp");
					shapes->dynamicCall("AddPicture( QString&, bool, bool, double, double, double, double)", "./1.bmp", true, true, 0, 0, ColumnNumber, RowNumber);
				}
			}
		}*/
	}

	QAxObject *used_range = worksheet->querySubObject("UsedRange");
	QAxObject *columns = used_range->querySubObject("Columns");
	columns->dynamicCall("AutoFit");
	QAxObject *rows = used_range->querySubObject("Rows");
	rows->dynamicCall("AutoFit");

	workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(strExcelFilePath));
	workbook->dynamicCall("Close()");
	excel->dynamicCall("Quit()");
	delete excel;
	excel = NULL;

	QMessageBox::information(this, QString("Info"), QString("Excel file has saved completed!"));
}

void Yangpu::SavePicSingalItem()
{
	int rowNumber = ui.tableWidget->rowCount();
	if (0 == rowNumber)
		return;

	QString strPicturePath = QFileDialog::getExistingDirectory(this, "Select Picture Path");
	if (strPicturePath.isNull())
		return;

	unsigned SelectRowNumber(0);
	SelectRowNumber = ui.tableWidget->currentRow();

	Syn_LogAnalyze *pSyn_LogAnalyze = _ListOfLogAnalyze[SelectRowNumber];
	if (NULL == pSyn_LogAnalyze)
		return;
	Syn_LogAnalyzeValue *pSyn_LogAnalyzeValue = NULL;
	int rc = pSyn_LogAnalyze->GetLogContent(pSyn_LogAnalyzeValue);
	if (0 != rc || NULL == pSyn_LogAnalyzeValue)
		return;

	//NoFinger
	if (pSyn_LogAnalyzeValue->NoFingerResult.bExcuted)
	{
		int RowNumber = pSyn_LogAnalyzeValue->NoFingerResult.RowNumber;
		int ColumnNumber = pSyn_LogAnalyzeValue->NoFingerResult.ColumnNumber;
		QVector<QRgb> vcolorTable;
		for (int i = 0; i < 256; i++)
			vcolorTable.append(qRgb(i, i, i));
		QByteArray data;
		data.resize((RowNumber)*(ColumnNumber));
		int k(0);
		for (int m = 0; m < RowNumber; m++)
		{
			for (int n = 0; n < ColumnNumber; n++)
			{
				data[k] = pSyn_LogAnalyzeValue->NoFingerResult.arr_NoFinger[m][n];
				k++;
			}
		}
		QImage image((const uchar*)data.constData(), ColumnNumber, RowNumber, ColumnNumber, QImage::Format_Indexed8);
		image.setColorTable(vcolorTable);
		image.save(strPicturePath + "/" + QString::fromStdString(pSyn_LogAnalyzeValue->SensorSerialNumber) + "_NoFinger_" + QString::number(SelectRowNumber + 1) + ".bmp");
	}

	//FakeFinger
	if (pSyn_LogAnalyzeValue->FakeFingerResult.bExcuted)
	{
		int RowNumber = pSyn_LogAnalyzeValue->FakeFingerResult.RowNumber;
		int ColumnNumber = pSyn_LogAnalyzeValue->FakeFingerResult.ColumnNumber;
		QVector<QRgb> vcolorTable;
		for (int i = 0; i < 256; i++)
			vcolorTable.append(qRgb(i, i, i));
		QByteArray data;
		data.resize((RowNumber)*(ColumnNumber));
		int k(0);
		for (int m = 0; m < RowNumber; m++)
		{
			for (int n = 0; n < ColumnNumber; n++)
			{
				data[k] = pSyn_LogAnalyzeValue->FakeFingerResult.arr_FakeFinger[m][n];
				k++;
			}
		}

		QImage image((const uchar*)data.constData(), ColumnNumber, RowNumber, ColumnNumber, QImage::Format_Indexed8);
		image.setColorTable(vcolorTable);
		//QPixmap::fromImage(image);
		image.save(strPicturePath + "/" + QString::fromStdString(pSyn_LogAnalyzeValue->SensorSerialNumber) + "_FakeFinger_" + QString::number(SelectRowNumber + 1) + ".bmp");
	}

	QMessageBox::information(this, QString("Info"), QString("Selected item's picture(bmp) has saved completed!"));
}

void Yangpu::SavePicAllItem()
{
	int rowNumber = ui.tableWidget->rowCount();
	if (0 == rowNumber)
		return;

	QString strPicturePath = QFileDialog::getExistingDirectory(this, "Select Picture Path");
	if (strPicturePath.isNull())
		return;

	for (int t = 0; t < rowNumber; t++)
	{
		Syn_LogAnalyze *pSyn_LogAnalyze = _ListOfLogAnalyze[t];
		if (NULL == pSyn_LogAnalyze)
			continue;
		Syn_LogAnalyzeValue *pSyn_LogAnalyzeValue = NULL;
		int rc = pSyn_LogAnalyze->GetLogContent(pSyn_LogAnalyzeValue);
		if (0 != rc || NULL == pSyn_LogAnalyzeValue)
			continue;

		//NoFinger
		if (pSyn_LogAnalyzeValue->NoFingerResult.bExcuted)
		{
			int RowNumber = pSyn_LogAnalyzeValue->NoFingerResult.RowNumber;
			int ColumnNumber = pSyn_LogAnalyzeValue->NoFingerResult.ColumnNumber;
			QVector<QRgb> vcolorTable;
			for (int i = 0; i < 256; i++)
				vcolorTable.append(qRgb(i, i, i));
			QByteArray data;
			data.resize((RowNumber)*(ColumnNumber));
			int k(0);
			for (int m = 0; m < RowNumber; m++)
			{
				for (int n = 0; n < ColumnNumber; n++)
				{
					data[k] = pSyn_LogAnalyzeValue->NoFingerResult.arr_NoFinger[m][n];
					k++;
				}
			}
			QImage image((const uchar*)data.constData(), ColumnNumber, RowNumber, ColumnNumber, QImage::Format_Indexed8);
			image.setColorTable(vcolorTable);
			image.save(strPicturePath + "/" + QString::fromStdString(pSyn_LogAnalyzeValue->SensorSerialNumber) + "_NoFinger_Item" + QString::number(t + 1) + ".bmp");
		}

		//FakeFinger
		if (pSyn_LogAnalyzeValue->FakeFingerResult.bExcuted)
		{
			int RowNumber = pSyn_LogAnalyzeValue->FakeFingerResult.RowNumber;
			int ColumnNumber = pSyn_LogAnalyzeValue->FakeFingerResult.ColumnNumber;
			QVector<QRgb> vcolorTable;
			for (int i = 0; i < 256; i++)
				vcolorTable.append(qRgb(i, i, i));
			QByteArray data;
			data.resize((RowNumber)*(ColumnNumber));
			int k(0);
			for (int m = 0; m < RowNumber; m++)
			{
				for (int n = 0; n < ColumnNumber; n++)
				{
					data[k] = pSyn_LogAnalyzeValue->FakeFingerResult.arr_FakeFinger[m][n];
					k++;
				}
			}

			QImage image((const uchar*)data.constData(), ColumnNumber, RowNumber, ColumnNumber, QImage::Format_Indexed8);
			image.setColorTable(vcolorTable);
			//QPixmap::fromImage(image);
			image.save(strPicturePath + "/" + QString::fromStdString(pSyn_LogAnalyzeValue->SensorSerialNumber) + "_FakeFinger_Item" + QString::number(t + 1) + ".bmp");
		}
	}

	QMessageBox::information(this, QString("Info"), QString("All items' pictures(bmp) has saved completed!"));
}