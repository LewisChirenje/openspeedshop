/*! \class IntroWizardPanel
     This defines the starting point for entry level users.
     asks the highest level questions attempting to take 
     the user to a more specific wizard panel (i.e. pc sampline
     wizrard)

     This is only prototype code.   It was created using
     Qt Designer, then the code was pulled into this class.

     Autor: Al Stipek (stipek@sgi.com)
 */

#include "IntroWizardPanel.hxx"   // Change this to your new class header file name
#include "PanelContainer.hxx"   // Do not remove
#include "plugin_entry_point.hxx"   // Do not remove


#include <qvariant.h>
#include <qpushbutton.h>
#include <qframe.h>
#include <qwidgetstack.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qradiobutton.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include <qfile.h>   // For the file dialog box.
#include <qfiledialog.h>  // For the file dialog box.
#include <qmessagebox.h>
#include "qscrollview.h"



/*! The default constructor.   Unused. */
IntroWizardPanel::IntroWizardPanel()
{ // Unused... Here for completeness...
}


/*! Constructs a new UserPanel object */
/*! This is the most often used constructor call.
    \param pc    The panel container the panel will initially be attached.
    \param n     The initial name of the panel container
 */
IntroWizardPanel::IntroWizardPanel(PanelContainer *pc, const char *n) : Panel(pc, n)
{
  nprintf( DEBUG_CONST_DESTRUCT) ( "IntroWizardPanel::IntroWizardPanel() constructor called.\n");
// Cut-n-paste from here...
    if ( !getName() )
	setName( "IntroWizardForm" );

sv = new QScrollView(getBaseWidgetFrame(), "scrollview");
sv->setResizePolicy( QScrollView::Manual );
// int width = getPanelContainer()->parent->width();
// int height = getPanelContainer()->parent->height();
// int width = getPanelContainer()->width();
// int height = getPanelContainer()->height();
sv->resize(750,400);
sv->resizeContents(800,450);
// sv->resize(width(),height());
// sv->resizeContents(width(),height());

    IntroWizardFormLayout = new QVBoxLayout( sv->viewport(), 11, 6, "IntroWizardFormLayout"); 

    frame5 = new QFrame( sv->viewport(), "frame5" );
    frame5->setFrameShape( QFrame::StyledPanel );
    frame5->setFrameShadow( QFrame::Raised );
    frame5Layout = new QVBoxLayout( frame5, 11, 6, "frame5Layout"); 

    widgetStack5 = new QWidgetStack( frame5, "widgetStack5" );

    WStackPage = new QWidget( widgetStack5, "WStackPage" );
    WStackPageLayout = new QVBoxLayout( WStackPage, 11, 6, "WStackPageLayout"); 

    epage1Header_2 = new QLabel( WStackPage, "epage1Header_2" );
    epage1Header_2->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, epage1Header_2->sizePolicy().hasHeightForWidth() ) );
    epage1Header_2->setAlignment( int( QLabel::WordBreak | QLabel::AlignCenter ) );
    WStackPageLayout->addWidget( epage1Header_2 );

    layout21 = new QVBoxLayout( 0, 0, 6, "layout21"); 

    vpage1Label = new QLabel( WStackPage, "vpage1Label" );
    vpage1Label->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, vpage1Label->sizePolicy().hasHeightForWidth() ) );
    layout21->addWidget( vpage1Label );

    layout20 = new QHBoxLayout( 0, 0, 6, "layout20"); 
    spacer5_3 = new QSpacerItem( 20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum );
    layout20->addItem( spacer5_3 );

    vpage1LoadExperimentCheckBox = new QCheckBox( WStackPage, "vpage1LoadExperimentCheckBox" );
    layout20->addWidget( vpage1LoadExperimentCheckBox );
    layout21->addLayout( layout20 );

    line3 = new QFrame( WStackPage, "line3" );
    line3->setFrameShape( QFrame::HLine );
    line3->setFrameShadow( QFrame::Sunken );
    line3->setFrameShape( QFrame::HLine );
    layout21->addWidget( line3 );

    layout9 = new QHBoxLayout( 0, 0, 6, "layout9"); 
    spacer5 = new QSpacerItem( 20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum );
    layout9->addItem( spacer5 );

    vpage1pcSampleRB = new QRadioButton( WStackPage, "vpage1pcSampleRB" );
    vpage1pcSampleRB->setChecked( TRUE );
    layout9->addWidget( vpage1pcSampleRB );
    layout21->addLayout( layout9 );

    layout10 = new QHBoxLayout( 0, 0, 6, "layout10"); 
    spacer6 = new QSpacerItem( 20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum );
    layout10->addItem( spacer6 );

    vpage1UserTimeRB = new QRadioButton( WStackPage, "vpage1UserTimeRB" );
    layout10->addWidget( vpage1UserTimeRB );
    layout21->addLayout( layout10 );

    layout21_2 = new QHBoxLayout( 0, 0, 6, "layout21_2"); 
    spacer7 = new QSpacerItem( 20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum );
    layout21_2->addItem( spacer7 );

    vpage1HardwareCounterRB = new QRadioButton( WStackPage, "vpage1HardwareCounterRB" );
    layout21_2->addWidget( vpage1HardwareCounterRB );
    layout21->addLayout( layout21_2 );

    layout20_2 = new QHBoxLayout( 0, 0, 6, "layout20_2"); 
    spacer7_3 = new QSpacerItem( 20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum );
    layout20_2->addItem( spacer7_3 );

    vpage1FloatingPointRB = new QRadioButton( WStackPage, "vpage1FloatingPointRB" );
    layout20_2->addWidget( vpage1FloatingPointRB );
    layout21->addLayout( layout20_2 );

    layout19 = new QHBoxLayout( 0, 0, 6, "layout19"); 
    spacer7_4 = new QSpacerItem( 20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum );
    layout19->addItem( spacer7_4 );

    vpage1InputOutputRB = new QRadioButton( WStackPage, "vpage1InputOutputRB" );
    layout19->addWidget( vpage1InputOutputRB );
    layout21->addLayout( layout19 );

    WStackPageLayout->addLayout( layout21 );

    layout52 = new QHBoxLayout( 0, 0, 6, "layout52"); 
    spacer44 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout52->addItem( spacer44 );

    vpage1NextButton = new QPushButton( WStackPage, "vpage1NextButton" );
    vpage1NextButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, vpage1NextButton->sizePolicy().hasHeightForWidth() ) );
    layout52->addWidget( vpage1NextButton );
    WStackPageLayout->addLayout( layout52 );
    widgetStack5->addWidget( WStackPage, 0 );

    WStackPage_2 = new QWidget( widgetStack5, "WStackPage_2" );
    WStackPageLayout_2 = new QVBoxLayout( WStackPage_2, 11, 6, "WStackPageLayout_2"); 

    epage1Header = new QLabel( WStackPage_2, "epage1Header" );
    epage1Header->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, epage1Header->sizePolicy().hasHeightForWidth() ) );
    epage1Header->setAlignment( int( QLabel::WordBreak | QLabel::AlignCenter ) );
    WStackPageLayout_2->addWidget( epage1Header );

    layout20_3 = new QVBoxLayout( 0, 0, 6, "layout20_3"); 

    epage1Label = new QLabel( WStackPage_2, "epage1Label" );
    epage1Label->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, epage1Label->sizePolicy().hasHeightForWidth() ) );
    layout20_3->addWidget( epage1Label );

    layout19_2 = new QHBoxLayout( 0, 0, 6, "layout19_2"); 
    spacer5_2_2 = new QSpacerItem( 20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum );
    layout19_2->addItem( spacer5_2_2 );

    epage1LoadExperimentCheckBox = new QCheckBox( WStackPage_2, "epage1LoadExperimentCheckBox" );
    layout19_2->addWidget( epage1LoadExperimentCheckBox );
    layout20_3->addLayout( layout19_2 );

    line2 = new QFrame( WStackPage_2, "line2" );
    line2->setFrameShape( QFrame::HLine );
    line2->setFrameShadow( QFrame::Sunken );
    line2->setFrameShape( QFrame::HLine );
    layout20_3->addWidget( line2 );

    layout9_2 = new QHBoxLayout( 0, 0, 6, "layout9_2"); 
    spacer5_2 = new QSpacerItem( 20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum );
    layout9_2->addItem( spacer5_2 );

    epage1pcSampleRB = new QRadioButton( WStackPage_2, "epage1pcSampleRB" );
    epage1pcSampleRB->setChecked( TRUE );
    layout9_2->addWidget( epage1pcSampleRB );
    layout20_3->addLayout( layout9_2 );

    layout10_2 = new QHBoxLayout( 0, 0, 6, "layout10_2"); 
    spacer6_2 = new QSpacerItem( 20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum );
    layout10_2->addItem( spacer6_2 );

    epage1UserTimeRB = new QRadioButton( WStackPage_2, "epage1UserTimeRB" );
    layout10_2->addWidget( epage1UserTimeRB );
    layout20_3->addLayout( layout10_2 );

    layout21_2_2 = new QHBoxLayout( 0, 0, 6, "layout21_2_2"); 
    spacer7_2 = new QSpacerItem( 20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum );
    layout21_2_2->addItem( spacer7_2 );

    epage1HardwareCounterRB = new QRadioButton( WStackPage_2, "epage1HardwareCounterRB" );
    layout21_2_2->addWidget( epage1HardwareCounterRB );
    layout20_3->addLayout( layout21_2_2 );

    layout20_2_2 = new QHBoxLayout( 0, 0, 6, "layout20_2_2"); 
    spacer7_3_2 = new QSpacerItem( 20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum );
    layout20_2_2->addItem( spacer7_3_2 );

    epage1FloatingPointRB = new QRadioButton( WStackPage_2, "epage1FloatingPointRB" );
    layout20_2_2->addWidget( epage1FloatingPointRB );
    layout20_3->addLayout( layout20_2_2 );

    layout19_2_2 = new QHBoxLayout( 0, 0, 6, "layout19_2_2"); 
    spacer7_4_2 = new QSpacerItem( 20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum );
    layout19_2_2->addItem( spacer7_4_2 );

    epage1InputOutputRB = new QRadioButton( WStackPage_2, "epage1InputOutputRB" );
    layout19_2_2->addWidget( epage1InputOutputRB );
    layout20_3->addLayout( layout19_2_2 );

    WStackPageLayout_2->addLayout( layout20_3 );

    layout44 = new QHBoxLayout( 0, 0, 6, "layout44"); 
    spacer37 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout44->addItem( spacer37 );

    epage1NextButton = new QPushButton( WStackPage_2, "epage1NextButton" );
    epage1NextButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, epage1NextButton->sizePolicy().hasHeightForWidth() ) );
    layout44->addWidget( epage1NextButton );
    WStackPageLayout_2->addLayout( layout44 );
    widgetStack5->addWidget( WStackPage_2, 1 );
    frame5Layout->addWidget( widgetStack5 );
    IntroWizardFormLayout->addWidget( frame5 );

    layout5 = new QHBoxLayout( 0, 0, 6, "layout5"); 

    wizardMode = new QCheckBox( sv->viewport(), "wizardMode" );
    wizardMode->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, wizardMode->sizePolicy().hasHeightForWidth() ) );
    wizardMode->setChecked( TRUE );
    layout5->addWidget( wizardMode );
    spacer1 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout5->addItem( spacer1 );

    broughtToYouByLabel = new QLabel( sv->viewport(), "broughtToYouByLabel" );
    broughtToYouByLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, broughtToYouByLabel->sizePolicy().hasHeightForWidth() ) );
    layout5->addWidget( broughtToYouByLabel );
    IntroWizardFormLayout->addLayout( layout5 );
    languageChange();
//    resize( QSize(610, 480).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( wizardMode, SIGNAL( clicked() ), this, SLOT( wizardModeSelected() ) );
    connect( vpage1NextButton, SIGNAL( clicked() ), this, SLOT( vpage1NextButtonSelected() ) );
    connect( epage1NextButton, SIGNAL( clicked() ), this, SLOT( epage1NextButtonSelected() ) );

    connect( vpage1pcSampleRB, SIGNAL( clicked() ), this, SLOT(vpage1pcSampleRBChanged() ) );
    connect( vpage1UserTimeRB, SIGNAL( clicked() ), this, SLOT(vpage1UserTimeRBChanged() ) );
    connect( vpage1HardwareCounterRB, SIGNAL( clicked() ), this, SLOT(vpage1HardwareCounterRBChanged() ) );
    connect( vpage1FloatingPointRB, SIGNAL( clicked() ), this, SLOT(vpage1FloatingPointRBChanged() ) );
    connect( vpage1InputOutputRB, SIGNAL( clicked() ), this, SLOT(vpage1InputOutputRBChanged() ) );

    connect( epage1pcSampleRB, SIGNAL( clicked() ), this, SLOT(epage1pcSampleRBChanged() ) );
    connect( epage1UserTimeRB, SIGNAL( clicked() ), this, SLOT(epage1UserTimeRBChanged() ) );
    connect( epage1HardwareCounterRB, SIGNAL( clicked() ), this, SLOT(epage1HardwareCounterRBChanged() ) );
    connect( epage1FloatingPointRB, SIGNAL( clicked() ), this, SLOT(epage1FloatingPointRBChanged() ) );
    connect( epage1InputOutputRB, SIGNAL( clicked() ), this, SLOT(epage1InputOutputRBChanged() ) );

#ifdef DEBUG_WITH_COLOR
sv->viewport()->setPaletteBackgroundColor("red");
sv->viewport()->setPaletteForegroundColor("green");
#endif // DEBUG_WITH_COLOR

// sv->viewport()->setPaletteBackgroundColor(getBaseWidgetFrame()->paletteBackgroundColor() );
sv->viewport()->setBackgroundColor(getBaseWidgetFrame()->backgroundColor() );

}


//! Destroys the object and frees any allocated resources
/*! The only thing that needs to be cleaned up is the baseWidgetFrame.
 */
IntroWizardPanel::~IntroWizardPanel()
{
  nprintf( DEBUG_CONST_DESTRUCT) ( "  IntroWizardPanel::~IntroWizardPanel() destructor called.\n");
}

//! Add user panel specific menu items if they have any.
bool
IntroWizardPanel::menu(QPopupMenu* contextMenu)
{
  nprintf( DEBUG_PANELS ) ("IntroWizardPanel::menu() requested.\n");

  return( FALSE );
}

//! Save ascii version of this panel.
/*! If the user panel provides save to ascii functionality, their function
     should provide the saving.
 */
void 
IntroWizardPanel::save()
{
  nprintf( DEBUG_PANELS ) ("IntroWizardPanel::save() requested.\n");
}

//! Save ascii version of this panel (to a file).
/*! If the user panel provides save to ascii functionality, their function
     should provide the saving.  This callback will invoke a popup prompting
     for a file name.
 */
void 
IntroWizardPanel::saveAs()
{
  nprintf( DEBUG_PANELS ) ("IntroWizardPanel::saveAs() requested.\n");
}

//! This function listens for messages.
int 
IntroWizardPanel::listener(char *msg)
{
  nprintf( DEBUG_PANELS ) ("IntroWizardPanel::listener() requested.\n");
  return 0;  // 0 means, did not want this message and did not act on anything.
}


//! This function broadcasts messages.
int 
IntroWizardPanel::broadcast(char *msg)
{
  nprintf( DEBUG_PANELS ) ("IntroWizardPanel::broadcast() requested.\n");
  return 0;
}


void
IntroWizardPanel::languageChange()
{
    setCaption( tr( "IntroWizardForm" ) );
    epage1Header_2->setText( tr( "<h2>Welcome to Open/SpeedShop(tm)</h2>" ) );
    vpage1Label->setText( tr( "Please select which of the following are true for your application:" ) );
    vpage1LoadExperimentCheckBox->setText( tr( "I already have experiment data and would like to analyze it." ) );
    vpage1pcSampleRB->setText( tr( "I'm trying to find where my program is spending most of it's time." ) );
    vpage1UserTimeRB->setText( tr( "I'd like to find out how much time is system time vs. my program's time." ) );
    vpage1HardwareCounterRB->setText( tr( "I'd like to see what the internal Hardware Counters can show me.\n"
"(Hardware Counters are an advanced feature that utilizes machine \n"
"hardware to measure certain attributes of program execution.)" ) );
    vpage1FloatingPointRB->setText( tr( "I need to measure how many times I am causing Floating Point Exceptions." ) );
    vpage1InputOutputRB->setText( tr( "My program does a lot of Input and Output and I'd like to trace that work." ) );
    vpage1NextButton->setText( tr( "> Next" ) );
    epage1Header->setText( tr( "<h2>Welcome to Open/SpeedShop(tm)</h2>" ) );
    epage1Label->setText( tr( "Please select which of the following are true for your application:" ) );
    epage1LoadExperimentCheckBox->setText( tr( "Load experiment data" ) );
    epage1pcSampleRB->setText( tr( "pcSampling (profiling)" ) );
    epage1UserTimeRB->setText( tr( "User Time Experiment." ) );
    epage1HardwareCounterRB->setText( tr( "Hardware Counter Tracing." ) );
    epage1FloatingPointRB->setText( tr( "Floating Point Exceptions Tracing" ) );
    epage1InputOutputRB->setText( tr( "Input/Output Tracing" ) );
    epage1NextButton->setText( tr( "> Next" ) );
    wizardMode->setText( tr( "Verbose Wizard Mode" ) );
    broughtToYouByLabel->setText( tr( "Brought to you by SGI (SiliconGraphics)" ) );
}

void IntroWizardPanel::wizardModeSelected()
{
  if( wizardMode->isOn() )
  {
    widgetStack5->raiseWidget(0);
  } else
  {
    widgetStack5->raiseWidget(1);
  }

  // Before we swith reposition to top...
  sv->verticalScrollBar()->setValue(0);
  sv->horizontalScrollBar()->setValue(0);

  handleSizeEvent(NULL);
}

void IntroWizardPanel::epage1NextButtonSelected()
{
  Panel *p = NULL;
  if( vpage1LoadExperimentCheckBox->isOn() )
  {
    QString fn = QString::null;
    char *cwd = get_current_dir_name();
    fn = QFileDialog::getOpenFileName( cwd, "Experiment Files (*.exp)", this, "open experiment dialog", "Choose an experiment file to open");
    free(cwd);
    if( !fn.isEmpty() )
    {
      printf("fn = %s\n", fn.ascii() );
      fprintf(stderr, "Determine which panel to bring up base on experiment file %s\n", fn.ascii() );
    } else
    {
      fprintf(stderr, "No experiment file name given.\n");
    }
    return;
  }
  if( epage1pcSampleRB->isOn() )
  {
    p = getPanelContainer()->raiseNamedPanel("&pc Sample Wizard");
    if( !p )
    {
      getPanelContainer()->getMasterPC()->dl_create_and_add_panel("pc Sample Wizard", getPanelContainer());
    }
  }
  if( epage1UserTimeRB->isOn() )
  {
    p = getPanelContainer()->raiseNamedPanel("&User Time Wizard");
    if( !p )
    {
      getPanelContainer()->getMasterPC()->dl_create_and_add_panel("User Time Wizard", getPanelContainer());
    }
  }
  if( epage1HardwareCounterRB->isOn() )
  {
    p = getPanelContainer()->raiseNamedPanel("&HW Counter Wizard");
    if( !p )
    {
      getPanelContainer()->getMasterPC()->dl_create_and_add_panel("HW Counter Wizard", getPanelContainer());
    }
  }
  if( epage1FloatingPointRB->isOn() )
  {
    p = getPanelContainer()->raiseNamedPanel("&FPE Tracing Wizard");
    if( !p )
    {
      getPanelContainer()->getMasterPC()->dl_create_and_add_panel("FPE Tracing Wizard", getPanelContainer());
    }
  }
  if( epage1InputOutputRB->isOn() )
  {
    p = getPanelContainer()->raiseNamedPanel("I&O Wizard");
    if( !p )
    {
      getPanelContainer()->getMasterPC()->dl_create_and_add_panel("IO Wizard", getPanelContainer());
    }
  }
}

void IntroWizardPanel::vpage1NextButtonSelected()
{
  Panel *p = NULL;
  if( vpage1LoadExperimentCheckBox->isOn() )
  {
    QString fn = QString::null;
    char *cwd = get_current_dir_name();
    fn = QFileDialog::getOpenFileName( cwd, "Experiment Files (*.exp)", this, "open experiment dialog", "Choose an experiment file to open");
    free(cwd);
    if( !fn.isEmpty() )
    {
      printf("fn = %s\n", fn.ascii() );
      fprintf(stderr, "Determine which panel to bring up base on experiment file %s\n", fn.ascii() );
    } else
    {
      fprintf(stderr, "No experiment file name given.\n");
    }
    return;
  }
  if( vpage1pcSampleRB->isOn() )
  {
    p = getPanelContainer()->raiseNamedPanel("&pc Sample Wizard");
    if( !p )
    {
      getPanelContainer()->getMasterPC()->dl_create_and_add_panel("pc Sample Wizard", getPanelContainer());
    }
  }
  if( vpage1UserTimeRB->isOn() )
  {
    p = getPanelContainer()->raiseNamedPanel("&User Time Wizard");
    if( !p )
    {
      getPanelContainer()->getMasterPC()->dl_create_and_add_panel("User Time Wizard", getPanelContainer());
    }
  }
  if( vpage1HardwareCounterRB->isOn() )
  {
    p = getPanelContainer()->raiseNamedPanel("&HW Counter Wizard");
    if( !p )
    {
      getPanelContainer()->getMasterPC()->dl_create_and_add_panel("HW Counter Wizard", getPanelContainer());
    }
  }
  if( vpage1FloatingPointRB->isOn() )
  {
    p = getPanelContainer()->raiseNamedPanel("&FPE Tracing Wizard");
    if( !p )
    {
      getPanelContainer()->getMasterPC()->dl_create_and_add_panel("FPE Tracing Wizard", getPanelContainer());
    }
  }
  if( vpage1InputOutputRB->isOn() )
  {
    p = getPanelContainer()->raiseNamedPanel("I&O Wizard");
    if( !p )
    {
      getPanelContainer()->getMasterPC()->dl_create_and_add_panel("IO Wizard", getPanelContainer());
    }
  }
}

void IntroWizardPanel::vpage1pcSampleRBChanged()
{
  vSetStateChanged(vpage1pcSampleRB);
}

void IntroWizardPanel::vpage1UserTimeRBChanged()
{
  vSetStateChanged(vpage1UserTimeRB);
}

void IntroWizardPanel::vpage1HardwareCounterRBChanged()
{
  vSetStateChanged(vpage1HardwareCounterRB);
}

void IntroWizardPanel::vpage1FloatingPointRBChanged()
{
  vSetStateChanged(vpage1FloatingPointRB);
}

void IntroWizardPanel::vpage1InputOutputRBChanged()
{
  vSetStateChanged(vpage1InputOutputRB);
}

void IntroWizardPanel::vSetStateChanged(QRadioButton *rb)
{
  vpage1pcSampleRB->setChecked( FALSE );
  vpage1UserTimeRB->setChecked( FALSE );
  vpage1HardwareCounterRB->setChecked( FALSE );
  vpage1FloatingPointRB->setChecked( FALSE );
  vpage1InputOutputRB->setChecked( FALSE );
  rb->setChecked(TRUE);
}


void IntroWizardPanel::epage1pcSampleRBChanged()
{
  eSetStateChanged(epage1pcSampleRB);
}

void IntroWizardPanel::epage1UserTimeRBChanged()
{
  eSetStateChanged(epage1UserTimeRB);
}

void IntroWizardPanel::epage1HardwareCounterRBChanged()
{
  eSetStateChanged(epage1HardwareCounterRB);
}

void IntroWizardPanel::epage1FloatingPointRBChanged()
{
  eSetStateChanged(epage1FloatingPointRB);
}

void IntroWizardPanel::epage1InputOutputRBChanged()
{
  eSetStateChanged(epage1InputOutputRB);
}

void IntroWizardPanel::eSetStateChanged(QRadioButton *rb)
{
  epage1pcSampleRB->setChecked( FALSE );
  epage1UserTimeRB->setChecked( FALSE );
  epage1HardwareCounterRB->setChecked( FALSE );
  epage1FloatingPointRB->setChecked( FALSE );
  epage1InputOutputRB->setChecked( FALSE );
  rb->setChecked(TRUE);
}

void IntroWizardPanel::handleSizeEvent( QResizeEvent *e )
{

  int width=100;
  int height=100;



  width=getBaseWidgetFrame()->width();
  height=getBaseWidgetFrame()->height();


  sv->resize(width, height);
}
