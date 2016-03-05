#include <QGraphicsView>
#include <QTimer>

#include "constants.h"
#include "gamecontroller.h"
#include "mainwindow.h"

MainWindow::MainWindow (QWidget *parent)
    : QMainWindow (parent),
    scene (new QGraphicsScene (this)),
    view  (new QGraphicsView (scene, this)),
    game  (new GameController (*scene, this))
{
    setCentralWidget (view);

    //compare with screen mian window size
    //resize (600, 600);
    setFixedSize (600, 600);
    initScene ();
    initSceneBackground ();

    QTimer::singleShot ( 0, this
                       , SLOT (adjustViewSize ()));
}

MainWindow::~MainWindow ()
{

}

void MainWindow::adjustViewSize ()
{
    view->fitInView (scene->sceneRect ()
                    , Qt::KeepAspectRatioByExpanding);  //±£³Ö³¤¿í±È, Ëõ·ÅÖÁ³äÂúÊÓ¿Ú
}

void MainWindow::initScene ()
{
    scene->setSceneRect (-100, -100, 200, 200);
}

void MainWindow::initSceneBackground ()
{
    //single block size
    QPixmap bg (TILE_SIZE, TILE_SIZE);
    QPainter p (&bg);
    p.setBrush (QBrush (Qt::gray));
    p.drawRect (0, 0, TILE_SIZE, TILE_SIZE);

    view->setBackgroundBrush (std::move(static_cast<QBrush> (bg)));
}
