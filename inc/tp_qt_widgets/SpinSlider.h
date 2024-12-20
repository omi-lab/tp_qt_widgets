#ifndef tp_qt_widgets_SpinSlider_h
#define tp_qt_widgets_SpinSlider_h

#include "tp_qt_widgets/Globals.h"

#include <QWidget>

namespace tp_qt_widgets
{

//##################################################################################################
enum class SliderMode
{
  Linear,
  Exponential
};

//##################################################################################################
//! A spind box and a slider.
class TP_QT_WIDGETS_SHARED_EXPORT SpinSlider: public QWidget
{
  Q_OBJECT
  TP_DQ;
public:
  //################################################################################################
  SpinSlider(SliderMode mode=SliderMode::Linear, QWidget* parent=nullptr);

  //################################################################################################
  ~SpinSlider() override;

  //################################################################################################
  void setRange(float min, float max);

  //################################################################################################
  float minValue() const;

  //################################################################################################
  float maxValue() const;

  //################################################################################################
  void setSoftRange(float min, float max);

  //################################################################################################
  void setValue(float value);

  //################################################################################################
  float value() const;

  //################################################################################################
  tp_utils::CallbackCollection<void(float)> edited;
};

}

#endif