/*
 * Qt5-UKUI's Library
 *
 * Copyright (C) 2020, Tianjin KYLIN Information Technology Co., Ltd.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Authors: Yue Lan <lanyue@kylinos.cn>
 *
 */

#include "qt5-ukui-style.h"

#include "qt5-ukui-style-helper.h"

#include "ukui-style-settings.h"
#include "ukui-tabwidget-default-slide-animator.h"

#include <QStyleOption>
#include <QWidget>
#include <QPainter>

#include "tab-widget-animation-helper.h"
#include "scrollbar-animation-helper.h"

#include "animator-iface.h"

#include <QIcon>
#include <QStyleOptionViewItem>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QTreeView>
#include <QMenu>

#include <QtPlatformHeaders/QXcbWindowFunctions>

#include <QEvent>
#include <QDebug>

Qt5UKUIStyle::Qt5UKUIStyle(bool dark) : QFusionStyle ()
{
    m_use_dark_palette = dark;
    m_tab_animation_helper = new TabWidgetAnimationHelper(this);
    m_scrollbar_animation_helper = new ScrollBarAnimationHelper(this);
}

bool Qt5UKUIStyle::eventFilter(QObject *obj, QEvent *e)
{
    /*!
      \bug
      There is a bug when use fusion as base style when in qt5 assistant's
      HelperView. ScrollBar will not draw with our overrided function correctly,
      and then it will trigger QEvent::StyleAnimationUpdate. by some how it will let
      HelperView be hidden.
      I eat this event to aviod this bug, but the scrollbar in HelperView still
      display with old fusion style, and the animation will be ineffective.

      I don't know why HelperView didn't use our function drawing scrollbar but fusion, that
      makes me stranged.
      */
    if (e->type() == QEvent::StyleAnimationUpdate) {
        return true;
    }
    return false;
}

/*
 * Note there are some widgets can not be set as transparent one in polish.
 * Because it has been created as a rgb window.
 *
 * To reslove this problem, we have to let attribute be setted more ahead.
 * Some styleHint() methods are called in the early creation of a widget.
 * So we can real set them as alpha widgets.
 */
int Qt5UKUIStyle::styleHint(QStyle::StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const
{
    realSetWindowSurfaceFormatAlpha(widget);
    realSetMenuTypeToMenu(widget);

    switch (hint) {
    case SH_ScrollBar_Transient:
        return true;
    case SH_ItemView_ShowDecorationSelected:
        return true;
    default:
        break;
    }
    return QFusionStyle::styleHint(hint, option, widget, returnData);
}
void Qt5UKUIStyle::polish(QPalette &palette){
//ukui-white
    QColor  window_bg(231,231,231),
            window_no_bg(233,233,233),
            base_bg(255,255,255),
            base_no_bg(248, 248, 248),
            font_bg(0,0,0),
            font_br_bg(255,255,255),
            font_di_bg(191,191,191),
            button_bg(217,217,217),
            button_ac_bg(107,142,235),
            button_di_bg(233,233,233),
            tool_br_bg(61,107,229),
            tip_bg(248,248,248);

//ukui-black
//  QColor  window_bg(45,46,50),
//          window_no_bg(48,46,50),
//          base_bg(31,32,34),
//          base_no_bg(31,32,34),
//          font_bg(255,255,255),
//          font_br_bg(255,255,255),
//          font_di_bg(90,90,90),
//          button_bg(57,58,62),
//          button_ac_bg(61,107,229),
//          button_di_bg(57,58,62),
//          tool_br_bg(61,107,229),
//          tip_bg(90,90,90);


    palette.setBrush(QPalette::Window,window_bg);
    palette.setBrush(QPalette::Active,QPalette::Window,window_bg);
    palette.setBrush(QPalette::Inactive,QPalette::Window,window_no_bg);
    palette.setBrush(QPalette::Disabled,QPalette::Window,window_no_bg);
    palette.setBrush(QPalette::WindowText,font_bg);
    palette.setBrush(QPalette::Active,QPalette::WindowText,font_bg);
    palette.setBrush(QPalette::Inactive,QPalette::WindowText,font_bg);
    palette.setBrush(QPalette::Disabled,QPalette::WindowText,font_di_bg);

    palette.setBrush(QPalette::Base,base_bg);
    palette.setBrush(QPalette::Active,QPalette::Base,base_bg);
    palette.setBrush(QPalette::Inactive,QPalette::Base,base_no_bg);
    palette.setBrush(QPalette::Disabled,QPalette::Base,base_no_bg);
    palette.setBrush(QPalette::Text,font_bg);
    palette.setBrush(QPalette::Active,QPalette::Text,font_bg);
    palette.setBrush(QPalette::Disabled,QPalette::Text,font_di_bg);

     //Cursor placeholder
    palette.setBrush(QPalette::PlaceholderText,font_di_bg);

    palette.setBrush(QPalette::ToolTipBase,tip_bg);
    palette.setBrush(QPalette::ToolTipText,font_bg);

    palette.setBrush(QPalette::Highlight,tool_br_bg);
    palette.setBrush(QPalette::Active,QPalette::Highlight,tool_br_bg);
    palette.setBrush(QPalette::HighlightedText,font_br_bg);

    palette.setBrush(QPalette::BrightText,font_br_bg);
    palette.setBrush(QPalette::Active,QPalette::BrightText,font_br_bg);
    palette.setBrush(QPalette::Inactive,QPalette::BrightText,font_br_bg);
    palette.setBrush(QPalette::Disabled,QPalette::BrightText,font_di_bg);

    palette.setBrush(QPalette::Button,button_bg);
    palette.setBrush(QPalette::Active,QPalette::Button,button_bg);
    palette.setBrush(QPalette::Inactive,QPalette::Button,button_bg);
    palette.setBrush(QPalette::Disabled,QPalette::Button,button_di_bg);
    palette.setBrush(QPalette::ButtonText,font_bg);
    palette.setBrush(QPalette::Inactive,QPalette::ButtonText,font_bg);
    palette.setBrush(QPalette::Disabled,QPalette::ButtonText,font_di_bg);

    palette.setBrush(QPalette::AlternateBase,button_bg);
    palette.setBrush(QPalette::Inactive,QPalette::AlternateBase,button_ac_bg);
    palette.setBrush(QPalette::Disabled,QPalette::AlternateBase,button_di_bg);


//  palette.setBrush(QPalette::Link,QColor(255,0,0));
//  palette.setBrush(QPalette::LinkVisited,QColor(255,0,0));

   return QFusionStyle::polish(palette);
}

void Qt5UKUIStyle::polish(QWidget *widget)
{
    QFusionStyle::polish(widget);

    if (widget->inherits("QMenu")) {
        widget->setAttribute(Qt::WA_TranslucentBackground);
        //QRegion mask = getRoundedRectRegion(widget->rect(), 10, 10);

        //widget->setMask(mask);
        //do not polish widget with proxy style.
        return;
        //qDebug()<<mask<<"menu mask"<<widget->mask();
    }

    if (widget->inherits("QTabWidget")) {
        //FIXME: unpolish, extensiable.
        m_tab_animation_helper->registerWidget(widget);
    }

    if (widget->inherits("QScrollBar")) {
        widget->setAttribute(Qt::WA_Hover);
        m_scrollbar_animation_helper->registerWidget(widget);
    }

    if (auto v = qobject_cast<QAbstractItemView *>(widget)) {
        v->viewport()->setAttribute(Qt::WA_Hover);
    }

    widget->installEventFilter(this);
}

void Qt5UKUIStyle::unpolish(QWidget *widget)
{
    widget->removeEventFilter(this);

    if (widget->inherits("QMenu")) {
        widget->setAttribute(Qt::WA_TranslucentBackground, false);
        //widget->setMask(QRegion());
        return;
    }

    if (widget->inherits("QTabWidget")) {
        m_tab_animation_helper->unregisterWidget(widget);
    }

    if (widget->inherits("QScrollBar")) {
        widget->setAttribute(Qt::WA_Hover, false);
        m_scrollbar_animation_helper->unregisterWidget(widget);
    }

    if (auto v = qobject_cast<QAbstractItemView *>(widget)) {
        v->viewport()->setAttribute(Qt::WA_Hover);
    }

    QFusionStyle::unpolish(widget);
}

void Qt5UKUIStyle::drawPrimitive(QStyle::PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    //qDebug()<<"draw PE"<<element;
    switch (element) {
    case QStyle::PE_PanelMenu:
    case QStyle::PE_FrameMenu:
    {
        /*!
          \bug
          a "disabled" menu paint and blur in error, i have no idea about that.
          */
        if (widget->isEnabled()) {
            return drawMenuPrimitive(option, painter, widget);
        }

        return QFusionStyle::drawPrimitive(element, option, painter, widget);
    }
    case PE_FrameFocusRect: {
        if (qobject_cast<const QAbstractItemView *>(widget))
            return;
        break;
    }
    case PE_PanelItemViewRow: {
        return;
    }
    case PE_PanelItemViewItem: {
        /*!
         * \todo
         * deal with custom/altenative background items.
         */
        bool isHover = (option->state & State_MouseOver) && (option->state & ~State_Selected);
        bool isSelected = option->state & State_Selected;
        bool enable = option->state & State_Enabled;
        QColor color = option->palette.color(enable? QPalette::Active: QPalette::Disabled,
                                             QPalette::Highlight);
        color.setAlpha(0);
        if (isHover) {
            color.setAlpha(127);
        }
        if (isSelected) {
            color.setAlpha(255);
        }
        painter->fillRect(option->rect, color);
        return;
    }

    case PE_PanelButtonCommand://UKUI PushButton style
    {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing,true);

        if(option->state & State_HasFocus){
        painter->setPen(Qt::NoPen);
        painter->setBrush(option->palette.color(QPalette::Highlight));
        }
        else {
            painter->setPen(Qt::NoPen);
            painter->setBrush(option->palette.color(QPalette::Button));
        }

       if (option->state & State_MouseOver) {
           if (option->state & State_Sunken) {
               painter->setPen(Qt::NoPen);
               painter->setBrush(option->palette.color(QPalette::Mid));
           } else {
               painter->setPen(Qt::NoPen);
               painter->setBrush(option->palette.color(QPalette::Dark));
           }
        }
      painter->drawRoundedRect(option->rect,4,4);

      /*!
       * \todo
       * Judge whether it is OK or other buttons
       */

    return;
    }

    case PE_PanelTipLabel://UKUI Tip  style
   {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing,true);
        painter->setPen(option->palette.color(QPalette::ToolTipText));
        painter->setBrush(option->palette.color(QPalette::ToolTipBase));
        painter->drawRoundedRect(option->rect,4,4);
        painter->restore();
     return;
     }

    case PE_FrameStatusBar://UKUI Status style
   {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing,true);
        painter->setPen(Qt::NoPen);
        painter->setBrush(option->palette.color(QPalette::Dark));
        painter->drawRect(option->rect);
        painter->restore();
     return;
     }

    case PE_PanelButtonTool://UKUI ToolBar  item style
 {
       painter->save();
       painter->setRenderHint(QPainter::Antialiasing,true);
       painter->setPen(Qt::NoPen);
       painter->setBrush(Qt::NoBrush);
      if (option->state & State_MouseOver) {
         if (option->state & State_Sunken) {
             painter->setPen(option->palette.color(QPalette::Highlight));
             painter->setBrush(option->palette.color(QPalette::Highlight));
          } else {
             painter->setPen(option->palette.color(QPalette::Highlight));
             painter->setBrush(option->palette.color(QPalette::Highlight));
           }
      }
     painter->drawRoundedRect(option->rect,4,4);
     painter->restore();
   return;
   }

    case PE_FrameTabWidget://UKUI TabBar item style
   {
       painter->save();
       painter->setRenderHint(QPainter::Antialiasing,true);
       painter->setBrush(option->palette.color(QPalette::Base));
       painter->setPen(option->palette.color(QPalette::Base));
       painter->drawRect(option->rect.adjusted(+3,+2,+0,-10));
       painter->drawRoundedRect(option->rect.adjusted(+3,+10,+0,+0),5,5);
       painter->restore();
     return;
     }

    case PE_FrameTabBarBase://UKUI TabBar style
   {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing,true);
        painter->setPen(option->palette.color(QPalette::Button));
        painter->setBrush(option->palette.color(QPalette::Button));
        painter->drawRoundedRect(option->rect,0,0);
        painter->restore();
     return;
     }

    default:   break;
    }
    return QFusionStyle::drawPrimitive(element, option, painter, widget);
}

void Qt5UKUIStyle::drawComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const
{
    switch (control) {
    case CC_ScrollBar: {
        //auto animatorObj = widget->findChild<QObject*>("ukui_scrollbar_default_interaction_animator");
        auto animator = m_scrollbar_animation_helper->animator(widget);
        bool enable = option->state.testFlag(QStyle::State_Enabled);
        bool mouse_over = option->state.testFlag(QStyle::State_MouseOver);
        bool is_horizontal = option->state.testFlag(QStyle::State_Horizontal);
        if (!animator) {
            return QFusionStyle::drawComplexControl(control, option, painter, widget);
        }

        animator->setAnimatorDirectionForward("bg_opacity", mouse_over);
        animator->setAnimatorDirectionForward("groove_width", mouse_over);
        if (enable) {
            if (mouse_over) {
                if (!animator->isRunning("groove_width") && animator->currentAnimatorTime("groove_width") < animator->totalAnimationDuration("groove_width")) {
                    animator->startAnimator("bg_opacity");
                    animator->startAnimator("groove_width");
                }
            } else {
                if (!animator->isRunning("groove_width") && animator->currentAnimatorTime("groove_width") > 0) {
                    animator->startAnimator("groove_width");
                    animator->startAnimator("bg_opacity");
                }
            }
        }

        if (animator->isRunning("groove_width")) {
            const_cast<QWidget*>(widget)->update();
        }

        painter->save();
        painter->setPen(Qt::transparent);
        painter->setBrush(Qt::black);
        auto percent = animator->value("groove_width").toInt()*1.0/12;
        painter->setOpacity(0.1*percent);
        auto grooveRect = option->rect;
        auto currentWidth = animator->value("groove_width").toInt();
        if (is_horizontal) {
            grooveRect.setY(qMax(grooveRect.height() - currentWidth*2, 0));
        } else {
            grooveRect.setX(qMax(grooveRect.width() - currentWidth*2, 0));
        }
        painter->drawRect(grooveRect);
        painter->restore();

        return QCommonStyle::drawComplexControl(control, option, painter, widget);
    }
    default:
        return QFusionStyle::drawComplexControl(control, option, painter, widget);
    }
}

void Qt5UKUIStyle::drawControl(QStyle::ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    switch (element) {
    case CE_ScrollBarSlider: {
        //qDebug()<<"draw slider";
        //auto animatorObj = widget->findChild<QObject*>("ukui_scrollbar_default_interaction_animator");
        auto animator = m_scrollbar_animation_helper->animator(widget);
        if (!animator) {
            return QFusionStyle::drawControl(element, option, painter, widget);
        }

        bool enable = option->state.testFlag(QStyle::State_Enabled);
        bool mouse_over = option->state.testFlag(QStyle::State_MouseOver);
        bool is_horizontal = option->state.testFlag(QStyle::State_Horizontal);

        //draw slider
        if (!enable) {
            painter->save();
            painter->setRenderHint(QPainter::Antialiasing);
            painter->setPen(Qt::transparent);
            painter->setBrush(Qt::black);
            painter->setOpacity(0.2);
            auto sliderRect = option->rect;
            if (is_horizontal) {
                sliderRect.translate(0, sliderRect.height() - 3);
                sliderRect.setHeight(2);
            } else {
                sliderRect.translate(sliderRect.width() - 3, 0);
                sliderRect.setWidth(2);
            }
            painter->drawRoundedRect(sliderRect, 1, 1);
            painter->restore();
        } else {
            auto sliderWidth = 0;
            if (is_horizontal) {
                sliderWidth = qMin(animator->value("groove_width").toInt() + 2, option->rect.height());
            } else {
                sliderWidth = qMin(animator->value("groove_width").toInt() + 2, option->rect.width());
            }

            animator->setAnimatorDirectionForward("slider_opacity", mouse_over);
            if (mouse_over) {
                if (!animator->isRunning("slider_opacity") && animator->currentAnimatorTime("slider_opacity") == 0) {
                    animator->startAnimator("slider_opacity");
                }
            } else {
                if (!animator->isRunning("slider_opacity") && animator->currentAnimatorTime("slider_opacity") > 0) {
                    animator->startAnimator("slider_opacity");
                }
            }

            if (animator->isRunning("slider_opacity")) {
                const_cast<QWidget *>(widget)->update();
            }

            painter->save();
            painter->setRenderHint(QPainter::Antialiasing);
            painter->setPen(Qt::transparent);
            painter->setBrush(Qt::black);
            painter->setOpacity(animator->value("slider_opacity").toDouble());
            auto sliderRect = option->rect;
            if (is_horizontal) {
                sliderRect.setY(sliderRect.height() - sliderWidth);
            } else {
                sliderRect.setX(sliderRect.width() - sliderWidth);
            }
            if (sliderWidth > 3) {
                if (is_horizontal) {
                    sliderRect.adjust(0, 1, 0, -1);
                } else {
                    sliderRect.adjust(1, 0, -1, 0);
                }
            } else {
                if (is_horizontal) {
                    sliderRect.adjust(0, -2, 0, -2);
                } else {
                    sliderRect.adjust(-2, 0, -2, 0);
                }
            }
            painter->drawRoundedRect(sliderRect, 6, 6);
            painter->restore();
        }
        return;
    }
    case CE_ScrollBarAddLine: {
        //auto animatorObj = widget->findChild<QObject*>("ukui_scrollbar_default_interaction_animator");
        auto animator = m_scrollbar_animation_helper->animator(widget);
        if (!animator) {
            return QFusionStyle::drawControl(element, option, painter, widget);
        }

        painter->save();
        auto percent = animator->value("groove_width").toInt()*1.0/12;
        painter->setOpacity(percent);
        QFusionStyle::drawControl(element, option, painter, widget);
        painter->restore();
        return;
    }
    case CE_ScrollBarSubLine: {
        //auto animatorObj = widget->findChild<QObject*>("ukui_scrollbar_default_interaction_animator");
        auto animator = m_scrollbar_animation_helper->animator(widget);
        if (!animator) {
            return QFusionStyle::drawControl(element, option, painter, widget);
        }

        painter->save();
        auto percent = animator->value("groove_width").toInt()*1.0/12;
        painter->setOpacity(percent);
        QFusionStyle::drawControl(element, option, painter, widget);
        painter->restore();
        return;
    }

    case CE_PushButtonLabel:
    {
       auto pushbutton = qstyleoption_cast<const QStyleOptionButton*>(option);
       painter->save();
       painter->setRenderHint(QPainter::Antialiasing,true);

       if(option->state & State_HasFocus){
         painter->setPen(option->palette.color(QPalette::HighlightedText));
       }
       else {
         painter->setPen(option->palette.color(QPalette::ButtonText));
       }

        if (option->state & State_MouseOver) {
            if (option->state & State_Sunken) {
                painter->setPen(option->palette.color(QPalette::HighlightedText));
            } else {
                painter->setPen(option->palette.color(QPalette::HighlightedText));
            }
         }
     painter->drawText(option->rect,pushbutton->text, QTextOption(Qt::AlignCenter));
     painter->restore();
    return;
    }

    case CE_TabBarTabShape://UKUI TabBar item style
    {
       painter->save();
       painter->setRenderHint(QPainter::Antialiasing,true);
       painter->setPen(option->palette.color(QPalette::Button));
       painter->setBrush(option->palette.color(QPalette::Button));
       if (option->state & State_Selected) {
           if (option->state & State_Sunken) {
              painter->setPen(option->palette.color(QPalette::Base));
               painter->setBrush(option->palette.color(QPalette::Base));
           } else {
               painter->setPen(option->palette.color(QPalette::Base));
               painter->setBrush(option->palette.color(QPalette::Base));
           }
        }
     painter->drawRoundedRect(option->rect.adjusted(+3,+0,+0,-option->rect.height()/2),4,4);
     painter->drawRect(option->rect.adjusted(+3,+option->rect.height()/2-4,+0,+0));
     painter->restore();
     return;
     }

    default:
        return QFusionStyle::drawControl(element, option, painter, widget);
    }
}

int Qt5UKUIStyle::pixelMetric(QStyle::PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
    switch (metric) {
    case PM_ScrollBarExtent: {
        return 12;
    }
    case PM_ScrollView_ScrollBarOverlap: {
        return -12;
    }
    default:
        break;
    }
    return QFusionStyle::pixelMetric(metric, option, widget);
}

QRect Qt5UKUIStyle::subControlRect(QStyle::ComplexControl control, const QStyleOptionComplex *option, QStyle::SubControl subControl, const QWidget *widget) const
{
    switch (control) {
    case CC_ScrollBar: {
        return scrollBarSubControlRect(control, option, subControl, widget);
    }
    default:
        break;
    }
    return QFusionStyle::subControlRect(control, option, subControl, widget);
}

// This fuction is copied from fusion style.
// The only different is it not hide add/sub line rect
// when style hint SH_ScrollBar_Transient is true.
QRect Qt5UKUIStyle::scrollBarSubControlRect(QStyle::ComplexControl control, const QStyleOptionComplex *option, QStyle::SubControl subControl, const QWidget *widget) const
{
    QRect ret;
    if (const QStyleOptionSlider *scrollbar = qstyleoption_cast<const QStyleOptionSlider *>(option)) {
        const QRect scrollBarRect = scrollbar->rect;
        int sbextent = 0;
        sbextent = proxy()->pixelMetric(PM_ScrollBarExtent, scrollbar, widget);

        int maxlen = ((scrollbar->orientation == Qt::Horizontal) ?
                      scrollBarRect.width() : scrollBarRect.height()) - (sbextent * 2);
        int sliderlen;

        // calculate slider length
        if (scrollbar->maximum != scrollbar->minimum) {
            uint range = scrollbar->maximum - scrollbar->minimum;
            sliderlen = (qint64(scrollbar->pageStep) * maxlen) / (range + scrollbar->pageStep);

            int slidermin = proxy()->pixelMetric(PM_ScrollBarSliderMin, scrollbar, widget);
            if (sliderlen < slidermin || range > INT_MAX / 2)
                sliderlen = slidermin;
            if (sliderlen > maxlen)
                sliderlen = maxlen;
        } else {
            sliderlen = maxlen;
        }

        int sliderstart = sbextent + sliderPositionFromValue(scrollbar->minimum,
                          scrollbar->maximum,
                          scrollbar->sliderPosition,
                          maxlen - sliderlen,
                          scrollbar->upsideDown);

        switch (subControl) {
        case SC_ScrollBarSubLine:            // top/left button
            if (scrollbar->orientation == Qt::Horizontal) {
                int buttonWidth = qMin(scrollBarRect.width() / 2, sbextent);
                ret.setRect(0, 0, buttonWidth, scrollBarRect.height());
            } else {
                int buttonHeight = qMin(scrollBarRect.height() / 2, sbextent);
                ret.setRect(0, 0, scrollBarRect.width(), buttonHeight);
            }
            break;
        case SC_ScrollBarAddLine:            // bottom/right button
            if (scrollbar->orientation == Qt::Horizontal) {
                int buttonWidth = qMin(scrollBarRect.width()/2, sbextent);
                ret.setRect(scrollBarRect.width() - buttonWidth, 0, buttonWidth, scrollBarRect.height());
            } else {
                int buttonHeight = qMin(scrollBarRect.height()/2, sbextent);
                ret.setRect(0, scrollBarRect.height() - buttonHeight, scrollBarRect.width(), buttonHeight);
            }
            break;
        case SC_ScrollBarSubPage:            // between top/left button and slider
            if (scrollbar->orientation == Qt::Horizontal)
                ret.setRect(sbextent, 0, sliderstart - sbextent, scrollBarRect.height());
            else
                ret.setRect(0, sbextent, scrollBarRect.width(), sliderstart - sbextent);
            break;
        case SC_ScrollBarAddPage:            // between bottom/right button and slider
            if (scrollbar->orientation == Qt::Horizontal)
                ret.setRect(sliderstart + sliderlen, 0,
                            maxlen - sliderstart - sliderlen + sbextent, scrollBarRect.height());
            else
                ret.setRect(0, sliderstart + sliderlen, scrollBarRect.width(),
                            maxlen - sliderstart - sliderlen + sbextent);
            break;
        case SC_ScrollBarGroove:
            if (scrollbar->orientation == Qt::Horizontal)
                ret.setRect(sbextent, 0, scrollBarRect.width() - sbextent * 2,
                            scrollBarRect.height());
            else
                ret.setRect(0, sbextent, scrollBarRect.width(),
                            scrollBarRect.height() - sbextent * 2);
            break;
        case SC_ScrollBarSlider:
            if (scrollbar->orientation == Qt::Horizontal)
                ret.setRect(sliderstart, 0, sliderlen, scrollBarRect.height());
            else
                ret.setRect(0, sliderstart, scrollBarRect.width(), sliderlen);
            break;
        default:
            break;
        }
        ret = visualRect(scrollbar->direction, scrollBarRect, ret);
    }
    return ret;
}

void Qt5UKUIStyle::realSetWindowSurfaceFormatAlpha(const QWidget *widget) const
{
    if (!widget)
        return;

    if (widget->testAttribute(Qt::WA_WState_Created))
        return;

    if (auto menu = qobject_cast<const QMenu *>(widget)) {
        const_cast<QWidget *>(widget)->setAttribute(Qt::WA_TranslucentBackground);
    }
}

void Qt5UKUIStyle::realSetMenuTypeToMenu(const QWidget *widget) const
{
    if (auto menu = qobject_cast<const QMenu *>(widget)) {
        if (!qobject_cast<const QMenu*>(widget)
                || widget->testAttribute(Qt::WA_X11NetWmWindowTypeMenu)
                || !widget->windowHandle())
            return;

        int wmWindowType = 0;
        if (widget->testAttribute(Qt::WA_X11NetWmWindowTypeDropDownMenu))
            wmWindowType |= QXcbWindowFunctions::DropDownMenu;
        if (widget->testAttribute(Qt::WA_X11NetWmWindowTypePopupMenu))
            wmWindowType |= QXcbWindowFunctions::PopupMenu;
        if (wmWindowType == 0) return;
        QXcbWindowFunctions::setWmWindowType(widget->windowHandle(),
                                             static_cast<QXcbWindowFunctions::WmWindowType>(wmWindowType));
    }
}
