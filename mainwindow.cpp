#include "mainwindow.h"
#include <QGridLayout>
#include <QPushButton>
#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QMediaPlaylist>
#include <QStackedWidget>
#include <QFinalState>

QStackedWidget * stackW;
MainWindow::MainWindow(QWidget * parent ):
    QMainWindow(parent)
{
    setObjectName("Main Window");
        qDebug("Main Window Start");
    resize(500,500);
    stackW = new QStackedWidget(this);

    auto page1 = new QWidget(this);
    auto p1layout = new QVBoxLayout(page1);
    auto p1text = new QLabel(page1);
    p1text->setText("Test of QState Machine ");
    start = new QPushButton(page1);
    auto nextButton = new QPushButton(page1);
    start->setText("Start State");
    connect( start , &QPushButton::clicked, this, &MainWindow::startState );
    p1layout->addWidget(p1text);
    p1layout->addWidget(start);
    nextButton->setText("Next State");
    p1layout->addWidget(nextButton);

    stop = new QPushButton(page1);
    stop->setText("End State");
    connect( stop , &QPushButton::clicked, this, &MainWindow::endState );
    p1layout->addWidget(stop);

    auto exitApp = new QPushButton(page1);
    exitApp->setText("Exit App");
    connect( exitApp, &QPushButton::clicked, this, &QWidget::close );
    p1layout->addWidget(exitApp);

    auto checkMachine = new QPushButton(page1);
    checkMachine->setText("Status");
    connect( checkMachine, &QPushButton::clicked, [&]() { 
           qDebug(QString("Machine state is %1").arg( machine->isRunning() ? "Running": "Stopped").toUtf8());
            });
    p1layout->addWidget(checkMachine);

    stackW->addWidget(page1);
    setCentralWidget( stackW );

    machine = new QStateMachine();
    auto beginState = new QState();
    auto intermediateState1 = new QState();
    auto intermediateState2 = new QState();
    auto endState = new QFinalState();

    beginState->setProperty("stateName","begin");
    intermediateState1->setProperty("stateName","i1");
    intermediateState2->setProperty("stateName","i2");
    endState->setProperty("stateName","end");
    machine->addState( intermediateState1 );
    machine->addState(intermediateState2 );
    machine->addState(beginState );
    machine->addState( endState );
    machine->setInitialState( beginState );

    beginState->addTransition( nextButton, &QPushButton::clicked, intermediateState1 );
    intermediateState1->addTransition( nextButton, &QPushButton::clicked, intermediateState2 );
    intermediateState2->addTransition( nextButton, &QPushButton::clicked, endState );

    auto states = { beginState, intermediateState1, intermediateState2, (QState*)endState };
    for( auto s : states ) {
        connect( s, &QState::entered, this, &MainWindow::enterState );
        connect( s, &QState::exited, this, &MainWindow::exitState );
    }
#if 0 
    connect( beginState, &QState::entered, this, &MainWindow::enterState );
    connect( intermediateState1, &QState::entered, this, &MainWindow::enterState );
    connect( intermediateState2, &QState::entered, this, &MainWindow::enterState );
    connect( endState, &QState::entered, this, &MainWindow::enterState );
#endif
    stop->setEnabled(false);

    connect( machine, &QStateMachine::started, [](){ qDebug("Machine Started"); });
    // this doesn't get emitted when machine stops due to entering final state.
    // when stop called, states don't exit.
    connect( machine, &QStateMachine::stopped, [](){ qDebug("Machine Stopped"); });


}

MainWindow::~MainWindow()
{
        qDebug("Main Window Exit");
}

void MainWindow::startState()
{
    qDebug("User request Start State");
    machine->start();
    start->setEnabled(false);
    stop->setEnabled(true);
}

void MainWindow::endState()
{
    qDebug("End State");
    machine->stop();
}

void MainWindow::enterState()
{
    qDebug("============================");
    qDebug("Entered State");
    for( auto s : machine->configuration() )
    {
        qDebug(QString("State: %1").arg(s->property("stateName").toString()).toUtf8());
    }
    qDebug("============================");
}

void MainWindow::exitState()
{
    auto exitSender = sender();
    qDebug("============================");
    qDebug("Exited State");
    qDebug(QString("State: %1").arg(exitSender->property("stateName").toString()).toUtf8());
    qDebug("============================");
}
