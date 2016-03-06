#include <QEvent>
#include <QGraphicsScene>
#include <QKeyEvent>

#include "gamecontroller.h"
#include "food.h"
#include "snake.h"

GameController::GameController (QGraphicsScene &scene, QObject *parent)
    : QObject       (parent)
    , gameIsRunning (true)
    , scene         (scene)
    , snake         (new Snake (*this))
{
    // Will emit the timeout() signal repeatly every 1000 / 40 per millisecond.
    timer.start (1000 / 40);

    Food *food = new Food (0, -50);
    scene.addItem (food);

    scene.addItem (snake);
    scene.installEventFilter (this);

    resume ();
}

GameController::~GameController ()
{}

//void GameController::snakeAteFood (Snake *snake, Food *food)
//{
//    scene.removeItem (food);
//    //delete food;

//    addNewFood ();
//}

void GameController::snakeAteFood (Snake *snake, Food *food)
{
        int x, y;

        do {
            x = (int)(qrand () % 100) / 10;
            y = (int)(qrand () % 100) / 10;

            x *= 10;
            y *= 10;
        }
        while (snake->shape ().contains (snake->mapFromScene (
                                                 QPointF (x + 5, y + 5))));

        //food = new Food (x, y);
        food->setPos (x, y);
}

//void GameController::snakeHitWall (Snake *snake, Wall *wall)
//{}

void GameController::snakeAteItself (Snake *snake)
{
    QTimer::singleShot (0, this, SLOT (gameOver ()));
}

void GameController::pause ()
{
    disconnect (&timer, SIGNAL (timeout ()),
                &scene, SLOT (advance ()));
}

void GameController::resume ()
{
    connect (&timer, SIGNAL (timeout ()),
             &scene, SLOT (advance ()));
}

void GameController::handleKeyPressed (QKeyEvent *event)
{
    if (gameIsRunning) {
        switch (event->key ()) {
        case Qt::Key_Left:
            snake->setMoveDirection (Snake::MoveLeft);
            break;
        case Qt::Key_Right:
            snake->setMoveDirection (Snake::MoveRight);
            break;
        case Qt::Key_Up:
            snake->setMoveDirection (Snake::MoveUp);
            break;
        case Qt::Key_Down:
            snake->setMoveDirection (Snake::MoveDown);
            break;
        case Qt::Key_Space:
            pause ();
            gameIsRunning = false;
        }
    }
    else {
        if (event->key() == Qt::Key_Space) {
            resume ();
            gameIsRunning = true;
        }
    }
}

void GameController::addNewFood ()
{
    int x, y;

    do {
        x = (int)(qrand () % 100) / 10;
        y = (int)(qrand () % 100) / 10;

        x *= 10;
        y *= 10;
    }
    while (snake->shape ().contains (snake->mapFromScene (
                                             QPointF (x + 5, y + 5))));

    Food *food = new Food (x, y);
    scene.addItem (food);
}

void GameController::gameOver ()
{
    scene.clear ();

    snake = new Snake (*this);
    scene.addItem (snake);
    addNewFood ();
}

bool GameController::eventFilter (QObject *object, QEvent *event)
{
    if (event->type () == QEvent::KeyPress) {
        handleKeyPressed ((QKeyEvent *)event);
        return true;
    }
    else {
        return QObject::eventFilter (object, event);
    }
}
