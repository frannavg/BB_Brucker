/* *********************************************************************** */
/*                               Filename: Heur.c                          */
/*                                                                         */
/*    Export: Procedure Heuristic_Schedule:                                */
/*                      Calculation of a heuristic solution for the        */
/*                      search tree node SonNode.                          */
/* *********************************************************************** */
#include <cstdio>
#include <limits>
using namespace std;

#include "datastruct.hpp"
#include "table.hpp"
#include "list.hpp"
#include "low.hpp"
#include "heur.hpp"

static int op_array[MaxOpProMachine + 1], temp_head[MaxNumOfOperations + 1];

/* Calculation of a lower bound, if Op is scheduled before all other
   operations on the machine which have not already been scheduled */
static int LowerBoundCalc(int machine_nr, int num_of_pred[], int local_head[], int Op) {
  List *help;
  int new_head,  lower_bound;
  register int i = 0;
  
  new_head = local_head[Op] + OpData[Op].process_time;
  help = OpsOnMachine[machine_nr];
  while (help != NIL) {
    if (num_of_pred[help->number] >= 0 && help->number != Op) {
      if (local_head[help->number] < new_head)
	temp_head[help->number] = new_head;
      else
	temp_head[help->number] = local_head[help->number];
      op_array[++i] = help->number;
    }
    help = help->next;
  }
  lower_bound = Preemptive_Schedule(op_array, i, temp_head);
  return (lower_bound > head[Op] + OpData[Op].process_time + tail[Op]) ? lower_bound : head[Op] + OpData[Op].process_time + tail[Op];
}


/* ************************************************************************* */
/*                         Procedure  Heuristic_Schedule()                   */
/*                                                                           */
/*  INPUT:  -/-                                                              */
/*                                                                           */
/*  FUNCTION: Calculation of a heuristic schedule. The critical path is      */
/*            stored in CriticalPath. If the makespan improves the actual    */
/*            upper bound, UB and CurrentBest are reset. Also the solution   */
/*            is stored in the file output.dat.                              */
/* ************************************************************************* */
static List *OutputList[MaxNumOfMachines];

static int num_of_pred[MaxNumOfOperations + 1],
  GenerateSet[MaxNumOfJobs + 1], GenSetPos,
  Selection[MaxNumOfOperations + 1], SelectPos,
  local_head[MaxNumOfOperations + 1],
  obtained[MaxNumOfOperations + 1],  Depth[MaxNumOfOperations + 1];

void Heuristic_Schedule() {
  List *Cut, *help, *UpdateList;
  FILE * fp;
  int MinReadyTime,
    MinReadyTimeMachine,
    PriorityOp,
    C_max,
    LowerBoundForOp, LowerBoundForPriorityOp,
    Op, sum,  NewMinReadyTime;
  register int i;
  
  Cut = UpdateList = NIL;
  for (i = 1; i <= NumOfOperations; ++i) {
    num_of_pred[i] = SonNode->num_of_pred[i] + 1;
    local_head[i] = head[i];
    obtained[i] = 0;
    Depth[i] = numeric_limits<int>::max();
  }
  
  Depth[0] = 0;
  obtained[0] = 0;
  obtained[MaxNumOfOperations] = 0;
  Depth[MaxNumOfOperations] = numeric_limits<int>::max();
  local_head[MaxNumOfOperations] = head[MaxNumOfOperations];
  SelectPos = 1;
  
  help = ConjArcs->succ[0];
  while (help != NIL) {
    num_of_pred[help->number]--;
    if (num_of_pred[help->number] == 0) {
      Cut = Insert(Cut, help->number);
      Depth[help->number] = 0;
    }
    help = help->next;
  }
  
  while (Cut != NIL) {
    Op = Cut->number;
    MinReadyTime = local_head[Op] + OpData[Op].process_time;
    help = Cut->next;
    while (help != NIL) {
      NewMinReadyTime =
	local_head[help->number] + OpData[help->number].process_time;
      if (MinReadyTime >= NewMinReadyTime) {
	if (MinReadyTime > NewMinReadyTime || tail[Op] < tail[help->number]) {
	  MinReadyTime = NewMinReadyTime;
	  Op = help->number;
	}
      }
      help = help->next;
    }
    MinReadyTimeMachine = OpData[Op].machine_nr;
    GenSetPos = 1;
    help = Cut;
    while (help != NIL) {
      if (OpData[help->number].machine_nr == MinReadyTimeMachine &&local_head[help->number] < MinReadyTime)
	GenerateSet[GenSetPos++] = help->number;
      help = help->next;
    }
    PriorityOp = GenerateSet[1];
    if (GenSetPos > 2) {
      LowerBoundForPriorityOp =
	LowerBoundCalc(MinReadyTimeMachine, num_of_pred, local_head, PriorityOp);
      for (i = 2; i < GenSetPos; ++i) {
	LowerBoundForOp = LowerBoundCalc(MinReadyTimeMachine, num_of_pred, local_head, GenerateSet[i]);
	if (LowerBoundForOp < LowerBoundForPriorityOp) {
	  LowerBoundForPriorityOp = LowerBoundForOp;
	  PriorityOp = GenerateSet[i];
	} else {
	  if (LowerBoundForOp == LowerBoundForPriorityOp && tail[PriorityOp] < tail[GenerateSet[i]])
	    PriorityOp = GenerateSet[i];
	}
      }
    }
    Selection[SelectPos++] = PriorityOp;
    Cut = Delete(Cut, PriorityOp);
    num_of_pred[PriorityOp]--;
    sum = local_head[PriorityOp] + OpData[PriorityOp].process_time;
    Op = ConjArcs->succ[PriorityOp]->number;
    if (local_head[Op] <= sum)
      if (local_head[Op] < sum) {
	local_head[Op] = sum;
	UpdateList = Insert(UpdateList, Op);
	obtained[Op] = PriorityOp;
	Depth[Op] = Depth[PriorityOp] + 1;
      } else
	if (Depth[PriorityOp] + 1 < Depth[Op]) {
	  obtained[Op] = PriorityOp;
	  Depth[Op] = Depth[PriorityOp] + 1;
	}
    if (Op != MaxNumOfOperations) {
      num_of_pred[Op]--;
      if (num_of_pred[Op] == 0)
	Cut = Insert(Cut, Op);
    }
    help = OpsOnMachine[MinReadyTimeMachine];
    while (help != NIL) {
      if (num_of_pred[help->number] >= 0 && local_head[help->number] <= sum)
	if (local_head[help->number] < sum) {
	  local_head[help->number] = sum;
	  UpdateList = Insert(UpdateList, help->number);
	  obtained[help->number] = PriorityOp;
	  Depth[help->number] = Depth[PriorityOp];
	} else
	  if (Depth[PriorityOp] < Depth[help->number]) {
	    Depth[help->number] = Depth[PriorityOp];
	    obtained[help->number] = PriorityOp;
	  }
      help = help->next;
    }
    help = DisjArcs->succ[PriorityOp];
    while (help != NIL) {
      num_of_pred[help->number]--;
      if (num_of_pred[help->number] == 0)
	Cut = Insert(Cut, help->number);
      help = help->next;
    }
    while (UpdateList != NIL) {
      Op = UpdateList->number;
      UpdateList = Delete(UpdateList, Op);
      sum = local_head[Op] + OpData[Op].process_time;
      help = ConjArcs->succ[Op];
      while (help != NIL) {
	if (local_head[help->number] <= sum) {
	  if (local_head[help->number] < sum) {
	    local_head[help->number] = sum;
	    if (!Member(UpdateList, help->number))
	      UpdateList = Insert(UpdateList, help->number);
	    obtained[help->number] = Op;
	    Depth[help->number] = Depth[Op] + 1;
	  } else
	    if (Depth[Op] + 1 < Depth[help->number]) {
	      obtained[help->number] = Op;
	      Depth[help->number] = Depth[Op] + 1;
	    }
	}
	help = help->next;
      }
      help = DisjArcs->succ[Op];
      while (help != NIL) {
	if (local_head[help->number] <= sum) {
	  if (local_head[help->number] < sum) {
	    local_head[help->number] = sum;
	    if (!Member(UpdateList, help->number))
	      UpdateList = Insert(UpdateList, help->number);
	    obtained[help->number] = Op;
	    Depth[help->number] = Depth[Op];
	  } else
	    if (Depth[Op] < Depth[help->number]) {
	      obtained[help->number] = Op;
	      Depth[help->number] = Depth[Op];
	    }
	}
	help = help->next;
      }
    }				/* end  while (UpdateList != NIL) .. */
  }				/* end  while (Cut != NIL) .. */
  
  CriticalPath = NIL;
  Op = obtained[MaxNumOfOperations];
  CriticalPath = InsertBefore(CriticalPath, Op);
  C_max = OpData[Op].process_time;
  
  while (obtained[Op] != 0) {
    Op = obtained[Op];
    CriticalPath = InsertBefore(CriticalPath, Op);
    C_max = C_max + OpData[Op].process_time;
  }
  
  if (C_max < UpperBound) {
    UpperBound = C_max;
    printf("Upper Bound = %4d\n", C_max);
    for (i = 1; i <= NumOfOperations; ++i)
      CurrentBest[i] = Selection[i];
    fp = fopen("output.dat", "a");
    fprintf(fp, "\nUpper bound %d after %d search tree nodes\n", UpperBound, SearchTreeNodes);
    for (i = 0; i <= NumOfMachines; ++i)
      OutputList[i] = NIL;
    for (i = 1; i <= NumOfOperations; ++i)
      OutputList[OpData[CurrentBest[i]].machine_nr] = Insert(OutputList[OpData[CurrentBest[i]].machine_nr], CurrentBest[i]);
    for (i = 1; i <= NumOfMachines; ++i) {
      fprintf(fp, "MaschineNo %3d :  ", i);
      help = OutputList[i];
      while (help != NIL) {
	fprintf(fp, "%3d ", help->number);
	help = help->next;
      }
      fprintf(fp, "\n");
    }
    for (i = 0; i < NumOfMachines; ++i)
      OutputList[i] = Makeempty(OutputList[i]);
    fclose(fp);
  }
}
