#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <qwidget.h>
#include <qtabwidget.h>

//! This overloads QTabWidget so the tabbar can accept mouse down events.
class TabWidget : public QTabWidget
{
    Q_OBJECT
  public:
    //! default constructor.
    TabWidget( );

    //! Constructor to overload QTabWiget
    TabWidget( QWidget *parent=0, const char *name=0 );

    //! The default destructor
    ~TabWidget( );

    //! Sets the tabbar
    void setTabBar( QTabBar *tb );

    //! Gets the tabbar.
    QTabBar *tabBar();

  protected slots:
    //! The standard Qt slot to change language information.
    virtual void languageChange();

  private:

};
#endif // TABWIDGET_H
