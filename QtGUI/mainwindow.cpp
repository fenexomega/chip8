#include <QMessageBox>
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	m_interruptEmulator(false),
	m_emulator(*this, m_interruptEmulator)
{

	ui->setupUi(this);
	this->setFixedSize(defaultWindowWidth, defaultWindowHeight);
	this->setWindowTitle("Chip8-Emulator");


	QPixmap bkgnd(defaultBackgroundImage);
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);

	QPalette palette;
	palette.setBrush(QPalette::Background, bkgnd);

	this->setPalette(palette);
}



MainWindow::~MainWindow()
{
	if(m_emulator.isRunning())
	{
		m_interruptEmulator = true;
		while(m_emulator.isRunning())
			QThread::currentThread()->yieldCurrentThread();
	}

	delete ui;
}



void MainWindow::printErrorMessage(const QString errorMsg) const
{
	QMessageBox messageBox;
	messageBox.critical(nullptr,"Error", errorMsg);
	messageBox.setFixedSize(500,200);
}


void MainWindow::loadRom()

{
	QString romFile(QFileDialog::getOpenFileName());

	if(romFile.isEmpty())
		return;

	m_emulator.setRomFile(std::move(romFile));
	m_emulator.start();
}
