#include "constants.h"
#include "gamecontroller.h"
#include "mainwindow.h"
#include <QGraphicsView>
#include <QTimer>

MainWindow::MainWindow (QWidget *parent)
    : QMainWindow (parent),
    scene (new QGraphicsScene (this)),
    view  (new QGraphicsView (scene, this)),
    game  (new GameController (*scene, this))
{
    setCentralWidget (view);

    //compare with screen main window size
    //resize (600, 600);
    setFixedSize (600, 600);
    initScene ();
    initSceneBackground ();

    // After 0 seconds, invoke this's asjustViewSize().
    // The advantage of this way is no need to override timerEvent()
    // or create a QTimer object.
    QTimer::singleShot ( 0, this, SLOT (adjustViewSize ()));
}

MainWindow::~MainWindow ()
{}

void MainWindow::adjustViewSize ()
{
    view->fitInView (scene->sceneRect (), Qt::KeepAspectRatioByExpanding);
}

void MainWindow::initScene ()
{
    scene->setSceneRect (-100, -100, 200, 200);
}

void MainWindow::initSceneBackground ()
{
    //single block size
    QPixmap background (TILE_SIZE, TILE_SIZE);
    QPainter p (&background);
    p.setBrush (QBrush (Qt::gray));
    p.drawRect (0, 0, TILE_SIZE, TILE_SIZE);
    // Let gray blocks covered background.
    view->setBackgroundBrush (std::move(QBrush(std::move(background))));
}
