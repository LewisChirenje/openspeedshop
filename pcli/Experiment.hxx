/*******************************************************************************
** Copyright (c) 2005 Silicon Graphics, Inc. All Rights Reserved.
**
** This library is free software; you can redistribute it and/or modify it under
** the terms of the GNU Lesser General Public License as published by the Free
** Software Foundation; either version 2.1 of the License, or (at your option)
** any later version.
**
** This library is distributed in the hope that it will be useful, but WITHOUT
** ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
** FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
** details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this library; if not, write to the Free Software Foundation, Inc.,
** 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*******************************************************************************/

// ApplicationGroupObject
class ApplicationGroupObject
{
 private:
  bool remote;
  CommandWindowID *RemoteFW;
  EXPID RemoteExp;
  std::string App_Name;
  Experiment   *App;

 public:
  ApplicationGroupObject ()
    { remote = false;
      RemoteFW = NULL;
      RemoteExp = 0;
      App = NULL;
    }
  ApplicationGroupObject (std::string name, Experiment  *Local_App)
    { *this = ApplicationGroupObject ();
      App_Name = name;
      App = Local_App;
    }
  ApplicationGroupObject (CommandWindowID *Rfw, EXPID Rexp)
    { *this = ApplicationGroupObject ();
      remote = true;
      RemoteFW = Rfw;
      RemoteExp = Rexp;
    }
  bool Application_Is_Remote() {return remote;}
  Experiment   *Application_App() {return App;}
  void Print(FILE *TFile) {
      fprintf(TFile," %s",App_Name.c_str());
    }
};

// ExperimentObject
// Note: ALL the instrumentation in the experiment's list is applied
//       to ALL of the executables in the experiment's list.
class ExperimentObject;
extern EXPID Experiment_Sequence_Number;
extern std::list<ExperimentObject *> ExperimentObject_list;

#define ExpStatus_NonExistant 0
#define ExpStatus_Paused      1
#define ExpStatus_Suspended   2
#define ExpStatus_Running     3
#define ExpStatus_Terminated  4
#define ExpStatus_InError     5

class ExperimentObject
{
 private:
  EXPID Exp_ID;
  int ExpStatus;
  bool Data_File_Has_A_Generated_Name;
  OpenSpeedShop::Framework::Experiment *FW_Experiment;

  std::string Suspended_Data_File_Name;

  std::list<ApplicationGroupObject *> ApplicationObjectList;
  std::list<Collector *> CollectorList;

 public:
  ExperimentObject (std::string data_base_name = std::string("")) {
    Exp_ID = ++Experiment_Sequence_Number;
    ExpStatus = ExpStatus_Paused;

   // Allocate a data base file for the information connected with the experiment.
    std::string Data_File_Name;
    if (data_base_name.length() == 0) {
      char base[20];
      snprintf(base, 20, "ssdb%lld.XXXXXX",Exp_ID);
      Data_File_Name = std::string(tempnam ("./", &base[0] ) ) + ".openss";
      Data_File_Has_A_Generated_Name = true;
      try {
        OpenSpeedShop::Framework::Experiment::create (Data_File_Name);
      }
      catch(const std::exception& error) {
        Exp_ID = 0;
        Data_File_Has_A_Generated_Name = false;
        FW_Experiment = NULL;
      }
    } else {
      Data_File_Name = data_base_name;
      Data_File_Has_A_Generated_Name = false;
    }

   // Create and open an experiment
    try {
      FW_Experiment = new OpenSpeedShop::Framework::Experiment (Data_File_Name);
      ExperimentObject_list.push_front(this);
    }
    catch(const std::exception& error) {
      Exp_ID = 0;
      Data_File_Has_A_Generated_Name = false;
      FW_Experiment = NULL;
    }

  }
  ~ExperimentObject () {
    ExperimentObject_list.remove (this);
    if (FW_Experiment != NULL) {
      if (Data_File_Has_A_Generated_Name) {
        int err = remove (FW_Experiment->getName().c_str());
        Data_File_Has_A_Generated_Name = false;
      }
      delete FW_Experiment;
      FW_Experiment = NULL;
    }
    Exp_ID = 0;
    ExpStatus = ExpStatus_NonExistant;
  }
  void ExperimentObject_Merge_Application(std::list<ApplicationGroupObject *> App_List)
    {
      ApplicationObjectList.merge(App_List);
    }
  void ExperimentObject_Merge_Instrumentation(std::list<Collector *> Collector_List)
    {
      CollectorList.merge(Collector_List);
    }
  void ExperimentObject_Add_Application(ApplicationGroupObject *App)
    {
      ApplicationObjectList.push_front(App);
    }
  void ExperimentObject_Add_Instrumention(Collector *Inst)
    {
      CollectorList.push_front(Inst);
    }

  EXPID ExperimentObject_ID() {return Exp_ID;}
  Experiment *FW() {return FW_Experiment;}
  int Status() {return ExpStatus;}
  void Determine_Status() {
    int S = ExpStatus;
    if (FW() == NULL) {
      if (ExpStatus != ExpStatus_Suspended) ExpStatus = ExpStatus_NonExistant;
    } else {
      ThreadGroup tgrp = FW()->getThreads();
      int A = ExpStatus_NonExistant;
      if (tgrp.empty()) A = ExpStatus_Paused;
      else if (tgrp.isAnyState(Thread::Running)) A = ExpStatus_Running;
      else if (tgrp.isAnyState(Thread::Suspended)) A = ExpStatus_Paused;
      else if (tgrp.areAllState(Thread::Terminated)) A = ExpStatus_Terminated;
      else A = ExpStatus_InError;
      ExpStatus = A;
    }
  }

  void setStatus (int S) {ExpStatus = S;}
  void ReStart () {
    if (ExpStatus == ExpStatus_Suspended) {
      try {
        FW_Experiment = new OpenSpeedShop::Framework::Experiment (Suspended_Data_File_Name);
        Determine_Status();
      }
      catch(const std::exception& error) {
        Exp_ID = 0;
        setStatus (ExpStatus_InError);
        Data_File_Has_A_Generated_Name = false;  // Save for later analysis
        FW_Experiment = NULL;
      }
    }
  }
  void Suspend () {
    if (FW_Experiment != NULL) {
      setStatus (ExpStatus_Suspended);
      Suspended_Data_File_Name = FW_Experiment->getName();
      delete FW_Experiment;
      FW_Experiment = NULL;
    }
  }

  void RenameDB (std::string New_DB) {
   // Determine the old DataBase Name.
    std::string Old_DB;
    if (Status() == ExpStatus_Suspended) {
      Old_DB = Suspended_Data_File_Name;
    } else {
      Old_DB = FW_Experiment->getName();
      delete FW_Experiment;
      FW_Experiment = NULL;
    }

   // Rename the Old DataBase.
    int len1 = Old_DB.length();
    int len2 = New_DB.length();
    char *scmd = (char *)malloc(6 + len1 + len2);
    sprintf(scmd,"mv %s %s\n\0",Old_DB.c_str(),New_DB.c_str());
    int ret = system(scmd);
    free (scmd);
    if (ret == 0) {
      if (Status() == ExpStatus_Suspended) {
        Suspended_Data_File_Name = New_DB;
      } else {
        FW_Experiment = new OpenSpeedShop::Framework::Experiment (New_DB);
        Data_File_Has_A_Generated_Name = false;
      }
    }
  }

  std::string ExpStatus_Name () {
    if ((this == NULL) || (ExpStatus == ExpStatus_NonExistant)) return std::string("NonExistant");
    if (ExpStatus == ExpStatus_Paused) return std::string("Paused");
    if (ExpStatus == ExpStatus_Suspended) return std::string("Disabled");
    if (ExpStatus == ExpStatus_Running) return std::string("Running");
    if (ExpStatus == ExpStatus_Terminated) return std::string("Terminated");
    if (ExpStatus == ExpStatus_InError) return std::string("Error");
    return std::string("Unknown");
  }

  void Print(FILE *TFile)
    { fprintf(TFile,"Experiment %lld %s data->%s\n",ExperimentObject_ID(), ExpStatus_Name().c_str(),
              (FW_Experiment != NULL) ? FW_Experiment->getName().c_str() :
                 (ExpStatus == ExpStatus_Suspended) ? Suspended_Data_File_Name.c_str() : "(null)");
      if (FW_Experiment != NULL) {
        ThreadGroup tgrp = FW_Experiment->getThreads();
        ThreadGroup::iterator ti;
        bool atleastone = false;
        for (ti = tgrp.begin(); ti != tgrp.end(); ti++) {
          Thread t = *ti;
          std::string host = t.getHost();
          pid_t pid = t.getProcessId();
          if (!atleastone) {
            atleastone = true;
          }
          fprintf(TFile,"    -h %s -p %lld",host.c_str(),pid);
          Optional<pthread_t> pthread = t.getPosixThreadId();
          if (pthread.hasValue()) {
            fprintf(TFile," -t %lld",pthread.getValue());
          }
#ifdef HAVE_MPI
          Optional<int> rank = t.getMpiRank();
          if (rank.hasValue()) {
            fprintf(TFile," -r %lld",rank.getValue());
          }
#endif
          CollectorGroup cgrp = t.getCollectors();
          CollectorGroup::iterator ci;
          int collector_count = 0;
          for (ci = cgrp.begin(); ci != cgrp.end(); ci++) {
            Collector c = *ci;
            Metadata m = c.getMetadata();
            if (collector_count) {
              fprintf(TFile,",");
            } else {
              fprintf(TFile," ");
              collector_count = 1;
            }
            fprintf(TFile," %s", m.getUniqueId().c_str() );
          }
          fprintf(TFile,"\n");
        }

        CollectorGroup cgrp = FW_Experiment->getCollectors();
        CollectorGroup::iterator ci;
        atleastone = false;
        for (ci = cgrp.begin(); ci != cgrp.end(); ci++) {
          Collector c = *ci;
          ThreadGroup tgrp = c.getThreads();
          if (tgrp.empty()) {
            Metadata m = c.getMetadata();
            if (atleastone) {
              fprintf(TFile,",");
            } else {
              fprintf(TFile,"   ");
              atleastone = true;
            }
            fprintf(TFile," %s", m.getUniqueId().c_str() );
          }
        }
        if (atleastone) {
          fprintf(TFile,"\n");
        }
      }
    }
  void Dump(FILE *TFile)
    { std::list<ExperimentObject *>::reverse_iterator expi;
      for (expi = ExperimentObject_list.rbegin(); expi != ExperimentObject_list.rend(); expi++)
      {
        (*expi)->Print(TFile);
      }
    }
};

// Make sure all experiments are closed and associated files freed.
void Experiment_Termination ();

// Experiment Utilities
ExperimentObject *Find_Experiment_Object (EXPID ExperimentID);

// Experiment level commands
bool SS_expAttach (CommandObject *cmd);
bool SS_expClose (CommandObject *cmd);
bool SS_expCreate (CommandObject *cmd);
bool SS_expDetach (CommandObject *cmd);
bool SS_expDisable (CommandObject *cmd);
bool SS_expEnable (CommandObject *cmd);
bool SS_expFocus  (CommandObject *cmd);
bool SS_expGo (CommandObject *cmd);
bool SS_expPause (CommandObject *cmd);
bool SS_expRestore (CommandObject *cmd);
bool SS_expSave (CommandObject *cmd);
bool SS_expSetParam (CommandObject *cmd);
bool SS_expView (CommandObject *cmd);

// Information level commands
bool SS_ListBreaks (CommandObject *cmd);
bool SS_ListExp (CommandObject *cmd);
bool SS_ListHosts (CommandObject *cmd);
bool SS_ListObj (CommandObject *cmd);
bool SS_ListPids (CommandObject *cmd);
bool SS_ListMetrics (CommandObject *cmd);
bool SS_ListParams (CommandObject *cmd);
bool SS_ListReports (CommandObject *cmd);
bool SS_ListSrc (CommandObject *cmd);
bool SS_ListTypes (CommandObject *cmd);

// Session level commands
bool SS_ClearBreaks (CommandObject *cmd);
bool SS_Exit (CommandObject *cmd);
bool SS_Help (CommandObject *cmd);
bool SS_History (CommandObject *cmd);
bool SS_Log (CommandObject *cmd);
bool SS_OpenGui (CommandObject *cmd);
bool SS_Playback (CommandObject *cmd);
bool SS_Record (CommandObject *cmd);
bool SS_SetBreak (CommandObject *cmd);

// Place holders for comands that are not yet implemented
bool SS_no_value    	(CommandObject *cmd);
bool SS_string_value    (CommandObject *cmd);
bool SS_int_value   	(CommandObject *cmd);
