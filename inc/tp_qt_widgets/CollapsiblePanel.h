#ifndef tp_qt_widgets_CollapsiblePanel_h
#define tp_qt_widgets_CollapsiblePanel_h

#include "tp_qt_widgets/Globals.h"

#include <QWidget>

namespace tp_qt_widgets
{

//##################################################################################################
class TP_QT_WIDGETS_SHARED_EXPORT CollapsiblePanel: public QWidget
{
  Q_OBJECT
  TP_DQ;
public:
  //################################################################################################
  CollapsiblePanel(QWidget* parent=nullptr);

  //################################################################################################
  ~CollapsiblePanel() override;

  //################################################################################################
  void setContentLayout(QLayout* layout);

  //################################################################################################
  QLayout* contentLayout() const;

  //################################################################################################
  void expand();

  //################################################################################################
  void collapse();

  //################################################################################################
  void collapseNow();

  //################################################################################################
  float expansionFactor() const;

  //################################################################################################
  void recalculateGeometry();

  //################################################################################################
  Q_SIGNAL void expansionFactorChanged();

protected:  
  //################################################################################################
   void showEvent(QShowEvent* event) override;

  //################################################################################################
  bool eventFilter(QObject* watched, QEvent* event) override;
};

}

#endif
