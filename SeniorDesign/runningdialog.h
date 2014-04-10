#ifndef RUNNINGDIALOG_H
#define RUNNINGDIALOG_H

#include <QProcess>
#include <QProgressDialog>

class RunningDialog : public QProgressDialog
{
    Q_OBJECT
public:
    explicit RunningDialog(QWidget *parent = 0);
    void setProgramName(QString program);
    void setOutputFilename(QString outputFile);
    void setInputArgs(QString inputFile, int numCircles, int kValues);
    void process();
    QProcess *getProc() {return proc;}
signals:

public slots:

protected slots:
    void onFinished(int exitCode);

protected:
    QProcess *proc;

    QString programName;
    QString outputFile;
    QString inputFile;
    int numCircles;
    int kValues;
};

#endif // RUNNINGDIALOG_H
