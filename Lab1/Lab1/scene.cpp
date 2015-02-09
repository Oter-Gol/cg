#include "scene.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QKeyEvent>

#include "geomitem.h"

Scene::Scene(QObject* parent) : QGraphicsScene(parent)
{
    numberOfIterations = 1;
}

Scene::~Scene()
{
    qDebug() << "destructor";
}

void Scene::changeParams(float radius, int numberOfLines, QColor linesColor)
{
    this->radius = radius;
    this->numberOfLines = numberOfLines;
    this->linesColor = linesColor;
    for (QGraphicsItem* item : this->items())
    {
        ((GeomItem*)item)->changeParams(radius, numberOfLines, linesColor, numberOfIterations);
    }
    update();
}



void Scene::keyPressEvent(QKeyEvent *event)
{
    qDebug() << event->key();

    switch (event->key()) {

    case Qt::Key_Plus:
        numberOfLines++;
        break;
    case Qt::Key_Minus:
        if (numberOfLines > 0)
        {
            numberOfLines--;
        }
        break;

    case Qt::Key_Up:
            radius++;
            break;

    case Qt::Key_Down:
        if(radius > 0){
            radius--;
        }
        break;
    case Qt::Key_Left:
        if (numberOfIterations > 0)
        {
            numberOfIterations--;
        }
        break;

    case Qt::Key_Right:
        numberOfIterations++;
        break;
    default:
        break;
    }

    for (QGraphicsItem* item : this->items())
    {
        ((GeomItem*)item)->changeParams(radius, numberOfLines, linesColor, numberOfIterations);
    }
    update();
}
float Scene::getRadius() const
{
    return radius;
}

int Scene::getNumberOfLines() const
{
    return numberOfLines;
}

int Scene::getNumberOfIterations() const
{
    return numberOfIterations;
}

