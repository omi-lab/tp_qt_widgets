#include "tp_qt_widgets/ProgressBar.h"
#include "tp_qt_utils/Progress.h"

namespace tp_qt_widgets
{

//##################################################################################################
struct ProgressBar::Private
{
  TP_REF_COUNT_OBJECTS("tp_qt_widgets::ProgressBar::Private");
  TP_NONCOPYABLE(Private);

  tp_qt_utils::Progress* progress;

  Private(tp_qt_utils::Progress* progress_):
    progress(progress_)
  {

  }
};

//##################################################################################################
ProgressBar::ProgressBar(tp_qt_utils::Progress* progress, QWidget* parent):
  QProgressBar(parent),
  d(new Private(progress))
{
  setRange(0, 1000);
  connect(d->progress, &tp_qt_utils::Progress::changed, this, &ProgressBar::progressChanged);
}

//##################################################################################################
ProgressBar::~ProgressBar()
{
  delete d;
}

//##################################################################################################
void ProgressBar::progressChanged()
{
  setValue(int(d->progress->progress() * 10.0f));
}

}
