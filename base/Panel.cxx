/*! \class Panel

    This class is the base class of all user Panels.    It's base functionality
    is to provide support for the user Panel and to interface with the 
    PanelControl class.

    A Panel consists of a baseWidget, and a suite of virtual member functions
    accessable by the user panel.

    A Panel may contain any sort of GUI display.   Panels may even be loaded
    that are instantiated, but never shown and provide background processing.
 
    A Panel is always parented to a PanelContainer, but may be reparented 
    (passed around) via a drag-n-drop request, or a splitting or collapsing
    (removing) of PanelContainers.

    Currently Panels are the only thing reparented in the base functionality.

    Author: Al Stipek   (stipek@sgi.com)
 */

#include "Panel.hxx"
#include "PanelContainer.hxx"
#include "InfoEventFilter.hxx"

#include <qtabwidget.h>

#include <qcursor.h>
#include <qpopupmenu.h>

class QTabWidget;

#include <qsplitter.h>

#include <qtimer.h>

#include <qpushbutton.h>  // For debug only ... 
 
#include "debug.hxx"  // This includes the definition of nprintf(DEBUG_PANELS) 

/*! This is the work constructor.
    It is called to create a Panel and attach it to a PanelContainer.
    \param pc    The panel container the panel will initially be attached.
    \param n     The initial name of the panel container
 */
Panel::Panel(PanelContainer *pc, const char *n) : QWidget(pc, n)
{
  nprintf(DEBUG_PANELS) ("Panel::Panel(...) entered.\n");

  expID = 0;

  topLevel = FALSE;   // 99.9 % of the time this is FALSE
  topPC = NULL;   // 99.9 % of the time this is NULL

  baseWidgetFrame = NULL;

  setName(n);

  setCaption(n);

  setPanelContainer(pc);

  QWidget *w = pc->dropSiteLayoutParent;

  baseWidgetFrame = new Frame(getPanelContainer(), w, "baseWidgetFrame");
// baseWidgetFrame->dragEnabled = TRUE;

  // Resize this to the right height right away...
  int width = pc->parent->width();
  int height = pc->parent->height();
// NOTE: 2 and 5 are numbers I pulled out of the blue.   They'll need to be
// calculated eventually.
  width-=2;
  height-=5;
  nprintf(DEBUG_PANELS) ("Panel::Panel() resize the widget to %dx%d\n", width, height );
  w->resize(width,height);

  baseWidgetFrame->resize(width,height);


if( getPanelContainer()->getMasterPC()->sleepTimer )
{
}
  getPanelContainer()->getMasterPC()->sleepTimer = NULL;
  getPanelContainer()->getMasterPC()->popupTimer = NULL;
}

/*!  Constructs a new Panel object.   (unused)
 */
Panel::Panel()
{
  // default constructor
  nprintf(DEBUG_PANELS) ("Panel::Panel() entered.\n");
  topLevel = FALSE;
  topPC = NULL;
}

/*! Destroys the object and frees any allocated resources.   None need to be
    destroyed in this class.
 */
Panel::~Panel()
{
  // no need to delete child widgets, Qt does it all for us
  nprintf(DEBUG_PANELS) ("Panel::~Panel(%s) destructor entered.\n", getName() );

  setPanelContainer(NULL);
// You should not need to delete this as the tutorials explain that qt will 
// take care of this delete.
//  delete baseWidgetFrame;
}

void
Panel::languageChange()
{
}

/*! Since we do so much management of PanelContainers, we also need to manage
    the size of the panel.   Resize the baseWidgetFrame to fit nicely into
    the size of the parent PanelContainer.
*/
void Panel::handleSizeEvent(QResizeEvent *)
{
  nprintf(DEBUG_PANELS) ("attempt to resize the panel baseWidgetFrame\n");
}

void Panel::setName(const char *n)
{
  setName(QString(n));
}

//! Set the name of the Panel.
void Panel::setName(QString n)
{
  name = n;
}

/*! Add user panel specific menu items if they have any.
    This calls the user 'menu()' function
    if the user provides one.   The user can attach any specific panel
    menus to the passed argument and they will be displayed on a right
    mouse down in the panel.
    /param  contextMenu is the QPopupMenu * that use menus can be attached.
 */
bool Panel::menu(QPopupMenu* contextMenu)
{
  nprintf(DEBUG_PANELS) ("Panel::menu() entered\n");

  return( FALSE );
}

/*! If the user panel provides save, their function should provide the saving.
 */
void Panel::save()
{
  nprintf(DEBUG_PANELS) ("Panel::save() entered\n");
}

/*! If the user panel provides save as functionality, their function
     should provide the saving.  This callback will invoke a popup prompting
     for a file name.
 */
void Panel::saveAs()
{
  nprintf(DEBUG_PANELS) ("Panel::saveAs() entered\n");
}

/*! When a message 
    has been sent (from anyone) and the message broker is notifying 
    panels that they may want to know about the message, this is the
    function the broker notifies.   The listener then needs to determine
    if it wants to handle the message.
    \param msg is the incoming message.
    \return 0 means you didn't do anything with the message.
    \return 1 means you handled the message.
 */
int Panel::listener(void *msg)
{
  nprintf(DEBUG_PANELS) ("Panel::listener() entered\n");

  return(0); // 0 means didn't handle and didn't want this message.
}

/*! Based on the broadcast type, send out the message.
 */
int
Panel::broadcast(char *msg, BROADCAST_TYPE bt, PanelContainer *startPC)
{
  // Set a global flag that we're broadcasting.... 
  // Warn and do not allow anothe message to be sent until this message 
  // is handled.
  nprintf(DEBUG_PANELS) ("Panel::broadcast(msg) entered\n");

  // Clear the global flag....

  switch( bt )
  {
    case PC_T:
      return( getPanelContainer()->notifyPC(msg) );
    case NEAREST_T:
      return( (int)getPanelContainer()->notifyNearest(msg) );
    case ALL_DECENDANTS_T:
      return( getPanelContainer()->notifyAllDecendants(msg, startPC) );
    case GROUP_T:
      return( getPanelContainer()->notifyGroup(msg) );
    case ALL_T:
    default:
      return( getPanelContainer()->notifyAll(msg) );
  }
}

void
Panel::addWhatsThis(QObject *o, Panel *p)
{
  getPanelContainer()->getMasterPC()->whatsThisEventFilter = new InfoEventFilter(o, p);
  o->installEventFilter( getPanelContainer()->getMasterPC()->whatsThisEventFilter );
}

/*! Called when mouse hover in panel.   The panel developers can overload
    this virtual function if they're interested in field the event.
 */
void
Panel::info(QPoint, QObject *  )
{
  nprintf(DEBUG_PANELS) ("Panel::info() entered\n");
}

void
Panel::wakeupFromSleep()
{
  nprintf(DEBUG_PANELS) ("wakeupFromSleep() called\n");
  getPanelContainer()->getMasterPC()->popupTimer->start(250, TRUE);
}

void
Panel::popupInfoAtLine()
{
  nprintf(DEBUG_PANELS) ("popupInfoAtLine() called\n");
  info(getPanelContainer()->getMasterPC()->last_pos);
}

void
Panel::displayWhatsThis(QString msg)
{
  nprintf(DEBUG_PANELS) ("Panel::displayWhatsThis() called.  Put the wit here.\n");

  getPanelContainer()->getMasterPC()->whatsThisActive = TRUE;
  getPanelContainer()->getMasterPC()->whatsThis = new WhatsThis( this );
  getPanelContainer()->getMasterPC()->whatsThis->display( msg, QCursor::pos() );
//  getPanelContainer()->getMasterPC()->whatsThis->display( msg, mapToGlobal( QCursor::pos() ) );
//  getPanelContainer()->getMasterPC()->whatsThis->display( msg, mapFromGlobal( QCursor::pos() ) );
}

