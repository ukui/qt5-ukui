#ifndef UKUITABWIDGETANIMATORIFACE_H
#define UKUITABWIDGETANIMATORIFACE_H

#include <QTabWidget>

/*!
 * \brief The UKUITabWidgetAnimatorIface class
 * \details
 * This class define the interface for doing a QTabWidget's animation.
 * a tabwidget animator should bind only one tabwidget with bindTabWidget(),
 * and can be unbounded with unboundTabWidget().
 *
 * Animator is created by AnimatorPlugin, which is another interface's implement
 * of UKUI style animation's frameworks.
 *
 * \see UKUITabWidgetAnimatorPluginIface
 */
class UKUITabWidgetAnimatorIface
{
public:
    virtual ~UKUITabWidgetAnimatorIface() {}

    virtual bool bindTabWidget(QTabWidget *w) = 0;

    virtual bool unboundTabWidget() = 0;
};

#endif // UKUITABWIDGETANIMATORIFACE_H
