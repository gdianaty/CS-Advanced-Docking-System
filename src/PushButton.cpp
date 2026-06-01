//============================================================================
/// \file   PushButton.cpp
/// \author Uwe Kindler
/// \date   18.10.2022
/// \brief  Implementation of CPushButton
//============================================================================

//============================================================================
//                                   INCLUDES
//============================================================================
#include "PushButton.h"

#include <QPainter>
#include <QStyleOptionButton>
#include <QDebug>
#include <QStylePainter>

// hack because Copperspice does not have this.
inline QRect TransposedRect( const QRect& r )
{
    return QRect(r.x(), r.y(), r.height(), r.width());
}

namespace ads
{
QSize CPushButton::sizeHint() const
{
    QSize sh = QPushButton::sizeHint();

    if (m_Orientation != CPushButton::Horizontal)
    {
        sh.transpose();
    }

    return sh;
}

void CPushButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QStylePainter painter(this);
    QStyleOptionButton option;
    initStyleOption(&option);

    if (m_Orientation == CPushButton::VerticalTopToBottom)
    {
        painter.rotate(90);
        painter.translate(0, -1 * width());
        //option.rect = option.rect.transposed();
        option.rect = TransposedRect(option.rect);
    }
    else if (m_Orientation == CPushButton::VerticalBottomToTop)
    {
        painter.rotate(-90);
        painter.translate(-1 * height(), 0);
        option.rect = TransposedRect(option.rect);
    }

    painter.drawControl(QStyle::CE_PushButton, option);
}

CPushButton::Orientation CPushButton::buttonOrientation() const
{
    return m_Orientation;
}

void CPushButton::setButtonOrientation(Orientation orientation)
{
    m_Orientation = orientation;
    updateGeometry();
}
} // namespace ads

//---------------------------------------------------------------------------
// EOF PushButton.cpp
