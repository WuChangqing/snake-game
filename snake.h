#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsItem>
#include <QRectF>

class GameController;

class Snake : public QGraphicsItem
{
public:
    enum Direction
    {
          MoveDown = -2
        , MoveLeft
        , NoMove
        , MoveRight
        , MoveUp
    };
    Snake (GameController & controller);

    QRectF boundingRect () const;
    QPainterPath shape () const;
    void paint (QPainter *painter
               , const QStyleOptionGraphicsItem *
               , QWidget *);

    void setMoveDirection (Direction direction);

protected:
    //Will be invoke 30 times per second.
    //Set by GameController's contructor.
    void advance (int step);

private:
    void moveLeft ();
    void moveRight ();
    void moveUp ();
    void moveDown ();

    void handleCollisions ();

    //Change snake's length
    int            growing;
    int            speed;
    int            tickCounter;
    Direction      moveDirection;
    QPointF        head;
    QList<QPointF> tail;
    GameController &controller;
};

#endif // SNAKE_H
