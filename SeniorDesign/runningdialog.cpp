#include "runningdialog.h"
#include <QDebug>

RunningDialog::RunningDialog(QWidget *parent) :
    QProgressDialog(parent)
{
    proc = new QProcess;
    proc->start(programName + " > " + outputFile);
    connect(proc, SIGNAL(finished(int)), this, SLOT(onFinished(int)));
    setMinimum(0);
    setMaximum(0);
    setWindowTitle("Running");
    setWindowFlags(Qt::WindowTitleHint);
}

void RunningDialog::onFinished(int exitCode)
{
    emit accepted();
}
