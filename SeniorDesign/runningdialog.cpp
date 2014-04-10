#include "runningdialog.h"
#include <QFile>
#include <QMessageBox>
#include <QDebug>

RunningDialog::RunningDialog(QWidget *parent) :
    QProgressDialog(parent)
{
    proc = new QProcess;
    connect(proc, SIGNAL(finished(int)), this, SLOT(onFinished(int)));
    setMinimum(0);
    setMaximum(0);
    setWindowTitle("Running");
    setWindowFlags(Qt::WindowTitleHint);
}

void RunningDialog::process()
{
    QStringList sArgs;
    sArgs << QString::number(numCircles);
    sArgs << QString::number(kValues);
    if(inputFile != "") {
        QFile file(inputFile);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open input file"),
                file.errorString());
            return;
        }
        sArgs << file.readAll();
        file.close();
    }
    proc->setStandardOutputFile(outputFile);
    proc->start(programName, sArgs);

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

void RunningDialog::setInputArgs(QString inputFile, int numCircles, int kValues)
{
    this->inputFile = inputFile;
    this->numCircles = numCircles;
    this->kValues = kValues;
}
