#include <memory>
#include "../src/utility/log.h"
#include "../src/Chip8.h"
#include "chip8emulator.h"

static void exitHandler(QMainWindow &mainWin);



Chip8Emulator::Chip8Emulator(QMainWindow &win, std::atomic<bool> &interrupt) :
	m_mainWin(win),
	m_interrupt(interrupt)
{

}


void Chip8Emulator::run()
{
	QMetaObject::invokeMethod(&m_mainWin, "setVisible",
				  Qt::QueuedConnection, Q_ARG(bool,false));

	auto m_chip8 = std::make_unique<Chip8>();

	if(!m_chip8->initialize(WindowMode::BORDLESS))
		return exitHandler(m_mainWin);

	else if(!m_chip8->loadRom(m_currentRom.toStdString().c_str()))
		return exitHandler(m_mainWin);


	Chip8 *rawChip = m_chip8.get(); // get raw ptr to use in main loop

	while(!m_interrupt)
	{
		if(rawChip->wantToExit())
			return exitHandler(m_mainWin);

		rawChip->updateCpuState();
		rawChip->executeInstruction();
		if(rawChip->getDrawFlag())
			rawChip->drawGraphics();
	}

	return exitHandler(m_mainWin);


}




static
void exitHandler(QMainWindow &mainWin)
{
	QString possibleErrorMsg = GetEmulatorErrorMsg().c_str(); // check if there was an error

	if(!possibleErrorMsg.isEmpty())
		QMetaObject::invokeMethod(&mainWin, "printErrorMessage",
					  Qt::QueuedConnection, Q_ARG(QString, std::move(possibleErrorMsg)));

	// reset the main window to visible
	QMetaObject::invokeMethod(&mainWin, "setVisible",
				  Qt::QueuedConnection, Q_ARG(bool,true));

	return;
}
