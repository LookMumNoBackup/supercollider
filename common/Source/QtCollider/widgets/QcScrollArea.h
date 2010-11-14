/************************************************************************
*
* Copyright 2010 Jakob Leben (jakob.leben@gmail.com)
*
* This file is part of SuperCollider Qt GUI.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
************************************************************************/

#ifndef QC_SCROLL_AREA_H
#define QC_SCROLL_AREA_H

#include "QcCanvas.h"
#include "../QcHelper.h"

#include <QScrollArea>

class QcScrollWidget : public QcCanvas
{
public:
  QcScrollWidget( QWidget *parent = 0 );
  QSize sizeHint() const;
protected:
  virtual bool event ( QEvent * );
  virtual bool eventFilter ( QObject *, QEvent * );
};

class QcScrollArea : public QScrollArea, public QcHelper
{
  Q_OBJECT
  Q_PROPERTY( bool hasBorder READ dummyBool WRITE setHasBorder );
  Q_PROPERTY( QColor background READ dummyColor WRITE setBackground );
  Q_PROPERTY( bool paint READ dummyBool WRITE setPaint );
  Q_PROPERTY( QRectF innerBounds READ innerBounds );
  public:
    QcScrollArea();
    Q_INVOKABLE void addChild( QWidget* w ) { w->setParent( scrollWidget ); w->show(); }
    void setBackground ( const QColor &color );
    void setPaint( bool b ) { scrollWidget->setPaint( b ); }
    void setHasBorder( bool b );
    QRectF innerBounds() const {
      QSize vs = viewport()->size();
      QSize cs = scrollWidget->size();
      return QRectF(0, 0,
                    qMax( vs.width(), cs.width() ),
                    qMax( vs.height(), cs.height() ) );
    }
    Q_INVOKABLE void repaint() { scrollWidget->repaint(); }
  public Q_SLOTS:
    void doDrawFunc();
  private:
    QcScrollWidget *scrollWidget;
};

#endif //QC_SCROLL_AREA_H
