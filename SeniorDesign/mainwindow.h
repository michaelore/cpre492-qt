#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSpinBox>
#include <QProcess>
#include <QFileDialog>
#include <QFile>
#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMenu>
#include <QLabel>
#include <QMenuBar>
#include <QPushButton>
#include <QLineEdit>
#include <QFuture>
#include <QtConcurrent>
#include <QProgressDialog>
#include "runningdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onProgramFinished();
    void onProgramCancelled();
    void onInputOpen();
    void onOutputOpen();
    void onClose();
    void onStart();
    void onSave();

private:
    Ui::MainWindow *ui;

    QTextEdit *outputLog;
    QWidget *mainWidget;
    QMenu *fileMenu;
    QAction *actInputOpen;
    QAction *actSave;
    QAction *actClose;
    QAction *actRun;

    QLabel *optionKLabel;
    QSpinBox *optionK;

    QLabel *optionNumCirclesLabel;
    QSpinBox *optionNumCircles;

    QHBoxLayout *layout;
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;
    QHBoxLayout *inputLayout;
    QHBoxLayout *outputLayout;

    QPushButton *startButton;
    QLineEdit *inputFileEdit;
    QPushButton *inputBrowseButton;
    QLineEdit *outputFileEdit;
    QPushButton *outputBrowseButton;
    QPushButton *saveButton;

    QProcess *process;

    RunningDialog *runDialog;

    void createLog();
    void createMenu();
    void createLayout();
    void createOptions();
};

#endif // MAINWINDOW_H
