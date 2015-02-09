#include "geomitem.h"

#include <QPainter>
#include <QtMath>
#include <QDebug>

/**
 *
 * @brief GeomItem::GeomItem
 * @param xPos
 * @param yPos
 * @param radius
 * @param numberOfLines
 * @param linesColor
 */
GeomItem::GeomItem(float xPos, float yPos,
                   float radius, int numberOfLines, QColor linesColor)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->radius = radius;
    this->numberOfLines = numberOfLines;
    this->linesColor = linesColor;
}

/**
 * @brief GeomItem::~GeomItem
 */
GeomItem::~GeomItem()
{

}

QRectF GeomItem::boundingRect() const
{
    QRectF rect(QPointF(-3 * radius - 1 + xPos, -3 * radius - 1 + yPos), QSizeF(6 * radius + 1, 6 * radius + 1));
    return rect;
}

void GeomItem::iterPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget, float x, float y,
                         int nIter)
{
    for (int j = 0; j < 2 * numberOfLines; ++j)
    {
        float xLocal = x + radius * qSin((float)j * M_PI / (numberOfLines));
        float yLocal = y + radius * qCos((float)j * M_PI / (numberOfLines));

        if (nIter <= numberOfIterations)
        {
            iterPaint(painter, option, widget, xLocal, yLocal, nIter + 1);
        }

        QLineF line(QPointF(x, y), QPointF(xLocal, yLocal));
        painter->drawLine(line);
    }
}

void GeomItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush;
    brush.setColor(this->linesColor);
    painter->setBrush(brush);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(this->linesColor);
    painter->setPen(pen);

    for (int i = 0; i < 2 * numberOfLines; ++i)
    {
        float x = xPos + radius * qSin((float)i * M_PI / (numberOfLines));
        float y = yPos + radius * qCos((float)i * M_PI / (numberOfLines));

        QLineF line(QPointF(xPos, yPos), QPointF(x, y));
        painter->drawLine(line);
        float xTmp = x - xPos;
        float yTmp = y - yPos;
        for ( int j = 1; j <= numberOfIterations; ++j)
        {
            for (int k = 0; k < 2 * numberOfLines; ++k)
            {
                float xx = xPos + xTmp * j + radius * qSin((float)k * M_PI / (numberOfLines));
                float yy = yPos + yTmp * j + radius * qCos((float)k * M_PI / (numberOfLines));

                QLineF lineInternal(QPointF(xPos + xTmp * j, yPos + yTmp * j), QPointF(xx, yy));
                painter->drawLine(lineInternal);
            }
        }
    }
}

void GeomItem::changeParams(float radius, int numberOfLines, QColor linesColor, int numberOfIterations)
{   
    this->radius = radius;
    this->numberOfLines = numberOfLines;
    this->linesColor = linesColor;
    this->numberOfIterations = numberOfIterations;
}

void GeomItem::changePosition(float xPos, float yPos)
{
    this->xPos = xPos;
    this->yPos = yPos;
}
