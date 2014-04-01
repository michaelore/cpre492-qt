#ifndef RUNNINGDIALOG_H
#define RUNNINGDIALOG_H

#include <QProcess>
#include <QProgressDialog>

class RunningDialog : public QProgressDialog
{
    Q_OBJECT
public:
    explicit RunningDialog(QWidget *parent = 0);
    void setProgramName(QString program) {this->programName = program;}
    void setOutputFilename(QString outputFile) {this->outputFile = outputFile;}
    QProcess *getProc() {return proc;}
signals:

public slots:

protected slots:
    void onFinished(int exitCode);

protected:
    QProcess *proc;

    QString programName;
    QString outputFile;
};

#endif // RUNNINGDIALOG_H
