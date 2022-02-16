#include <QMainWindow>
#include <QPushButton>
#include <QStateMachine>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        MainWindow(QWidget * parent = nullptr );
        ~MainWindow();

    public slots:
        void startState();
        void enterState();
        void exitState();
        void endState();

    private:
        QStateMachine * machine;
        QPushButton * start,*stop;
};
