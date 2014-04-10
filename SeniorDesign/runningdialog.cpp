#include "runningdialog.h"
#include <QFile>
#include <QMessageBox>
#include <QDebug>

RunningDialog::RunningDialog(QWidget *parent) :
    QProgressDialog(parent)
{
    proc = new QProcess;
    //QString cmd();
    QStringList sArgs;
    QFile file("C:\\dev\\in.txt");
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
        return;
    }
    sArgs << file.readAll();
    file.close();
    proc->setStandardOutputFile("C:\\dev\\out.txt");
    proc->start("C:\\dev\\longexample.exe", sArgs);
    connect(proc, SIGNAL(finished(int)), this, SLOT(onFinished(int)));
    setMinimum(0);
    setMaximum(0);
    setWindowTitle("Running");
    setWindowFlags(Qt::WindowTitleHint);
}

void RunningDialog::onFinished(int exitCode)
{
    if(exitCode == 0) {
        emit accepted();
    }
}

void RunningDialog::setProgramName(QString program)
{
    this->programName = program;
}

void RunningDialog::setOutputFilename(QString outputFile)
{
    this->outputFile = outputFile;
}

void RunningDialog::setInputFilename(QString inputFile)
{
    this->inputFile = inputFile;
}
