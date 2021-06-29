/* ************************************************************************* */
/*                       Filename: table.h                                   */
/*                                                                           */
/*    Export: Global variables                                               */
/* ************************************************************************* */
#include "datastruct.hpp"

#pragma once

extern Operation OpData[MaxNumOfOperations + 1];
extern List *OpsOnMachine[MaxNumOfMachines + 1], *CriticalPath;
extern ArcList *ConjArcs, *DisjArcs;
extern int head[MaxNumOfOperations + 1],
    tail[MaxNumOfOperations + 1],
    CurrentBest[MaxNumOfOperations + 1],
    UpperBound,
    NumOfJobs, NumOfMachines, NumOfOperations,  SearchTreeNodes;
extern StackElement *FirstOfStack;
extern NodeType *ActualNode, *SonNode;
