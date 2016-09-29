#ifndef YANGPU_H
#define YANGPU_H

#include <QtWidgets/QMainWindow>
#include "ui_yangpu.h"

#include <vector>
#include <string>

#include "Syn_LogAnalyze.h"

using namespace std;

typedef enum contune_bmp_status {
	CONTUNE_BMP_STATUS_OK,
	CONTUNE_BMP_STATUS_INVALID_ARG,
	CONTUNE_BMP_STATUS_CANT_OPEN_FILE,
	CONTUNE_BMP_STATUS_CANT_READ_HEADER,
	CONTUNE_BMP_STATUS_NOT_BMP,
	CONTUNE_BMP_STATUS_INCORRECT_DIMENSIONS,
	CONTUNE_BMP_STATUS_ONLY_SUPPORT_8_BIT,
	CONTUNE_BMP_STATUS_NO_MEMORY,
	CONTUNE_BMP_STATUS_CANT_READ_PIXEL_VALUES,
} contune_bmp_status;

typedef enum conTuneScoreStatus {
	CONTUNE_SCORE_STATUS_OK,
	CONTUNE_SCORE_STATUS_INVALID_ARGS,
	CONTUNE_SCORE_STATUS_INIT_FAILURE,
	CONTUNE_SCORE_STATUS_CANT_SET_VALUES,
	CONTUNE_SCORE_STATUS_CALCULATION_FAILURE,
} conTuneScoreStatus;

#define MAX_VALUES 500000

#define CONTUNE_BMP_HEADER_MINSIZE 54

class Yangpu : public QMainWindow
{
	Q_OBJECT

public:
	Yangpu(QWidget *parent = 0);
	~Yangpu();

	void GetLogInfo(vector<string> listOfLogFilePath);

public Q_SLOTS:

	void keyPressEvent(QKeyEvent * ev);

	void Exit();

	void OpenFile();
	
	void dragEnterEvent(QDragEnterEvent *event);

	void dropEvent(QDropEvent * event);

	void TableWidgetItemClicked();

	void TableWidgetCellClicked(int rowNumber, int columnNumber);

	void SaveExcel();

	void SavePicSingalItem();

	void SavePicAllItem();

	contune_bmp_status contune_test_read_bmp(char *filepath, int *pOutWidth, int *pOutHeight, unsigned int *values);

protected:

	void ClearLogAnalyze();

	void InitWidgetState();

private:
	Ui::YangpuClass ui;

	vector<Syn_LogAnalyze*> _ListOfLogAnalyze;
};

#endif // YANGPU_H
