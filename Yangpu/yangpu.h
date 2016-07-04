#ifndef YANGPU_H
#define YANGPU_H

#include <QtWidgets/QMainWindow>
#include "ui_yangpu.h"

#include <vector>
#include <string>

#include "Syn_LogAnalyze.h"

using namespace std;

class Yangpu : public QMainWindow
{
	Q_OBJECT

public:
	Yangpu(QWidget *parent = 0);
	~Yangpu();

	void GetLogInfo(vector<string> listOfLogFilePath);

public Q_SLOTS:

	void Exit();

	void OpenFile();
	
	void dragEnterEvent(QDragEnterEvent *event);

	void dropEvent(QDropEvent * event);

	void TableWidgetCellClicked(int rowNumber, int columnNumber);

protected:

	void ClearLogAnalyze();

	void InitWidgetState();

private:
	Ui::YangpuClass ui;

	vector<Syn_LogAnalyze*> _ListOfLogAnalyze;
};

#endif // YANGPU_H
