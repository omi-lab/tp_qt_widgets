#include "tp_qt_widgets/ColorPickerWidget.h"
#include "tp_qt_widgets/ColorPickerDialog.h"
#include "tp_qt_widgets/detail/ColorPicker_HSVCircle.h"
#include "tp_qt_widgets/detail/ColorPicker_HSVSquare.h"
#include "tp_qt_widgets/detail/ColorPicker_RGBSlider.h"
#include "tp_qt_widgets/detail/ColorPicker_RGBSlider_Horizontal.h"

#include "tp_utils/RefCount.h"

#include <QBoxLayout>
#include <QMenu>

namespace tp_qt_widgets
{

//##################################################################################################
struct ColorPickerWidget::Private
{
  TP_REF_COUNT_OBJECTS("tp_qt_widgets::ColorPickerWidget::Private");
  TP_NONCOPYABLE(Private);

  Q* q;

  detail::ColorPicker* colorPicker;

  //################################################################################################
  Private(Q* q_):
    q(q_)
  {

  }
};

//##################################################################################################
ColorPickerWidget::ColorPickerWidget(Mode mode, bool editMenu, QWidget* parent):
  QWidget(parent),
  d(new Private(this))
{
  auto l = new QVBoxLayout(this);
  l->setContentsMargins(0,0,0,0);

  switch(mode)
  {
    case Mode::HSVCircle          : d->colorPicker = new detail::ColorPicker_HSVCircle(); break;
    case Mode::HSVSquare          : d->colorPicker = new detail::ColorPicker_HSVSquare(); break;
    case Mode::RGBSlider          : d->colorPicker = new detail::ColorPicker_RGBSlider(); break;
    case Mode::RGBSliderHorizontal: d->colorPicker = new detail::ColorPicker_RGBSlider_Horizontal(); break;
  }

  l->addWidget(d->colorPicker);
  connect(d->colorPicker, &detail::ColorPicker::colorChanged, this, &ColorPickerWidget::colorChanged);

  if(editMenu)
  {
    d->colorPicker->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(d->colorPicker, &QWidget::customContextMenuRequested, this, [&](const QPoint& pos)
    {
      QMenu menu(this);

      menu.addAction("Edit", this, [&]
      {
        auto c = ColorPickerDialog::getColor(qColor(), "Select Color", Mode::RGBSlider);
        if(!c.isValid())
          return;
        setColor(c);
        colorChanged();
      });

      menu.exec(d->colorPicker->mapToGlobal(pos));
    });
  }
}

//##################################################################################################
ColorPickerWidget::~ColorPickerWidget()
{
  delete d;
}

//##################################################################################################
void ColorPickerWidget::setColor(const QColor& color)
{
  d->colorPicker->set(color);
}

//##################################################################################################
void ColorPickerWidget::setColor(TPPixel color)
{
  d->colorPicker->set(tpPixelToQColor(color));
}

//##################################################################################################
QColor ColorPickerWidget::qColor() const
{
  return d->colorPicker->get();
}

//##################################################################################################
TPPixel ColorPickerWidget::tpPixel() const
{
  return tpPixelFromQColor(d->colorPicker->get());
}

//##################################################################################################
int ColorPickerWidget::targetHeight() const
{
  return d->colorPicker->targetHeight();
}

}
