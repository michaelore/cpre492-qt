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
    void setInputFilename(QString inputFile);
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
};

#endif // RUNNINGDIALOG_H
