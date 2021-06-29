/* ************************************************************************* */
/*                       Filename: table.c                                   */
/*                                                                           */
/*    Export: Global variables                                               */
/* ************************************************************************* */
#include "datastruct.hpp"

Operation OpData[MaxNumOfOperations + 1];
List *OpsOnMachine[MaxNumOfMachines + 1], *CriticalPath;
ArcList *ConjArcs, *DisjArcs;
int head[MaxNumOfOperations + 1],
    tail[MaxNumOfOperations + 1],
    CurrentBest[MaxNumOfOperations + 1],
    UpperBound,
    NumOfJobs, NumOfMachines, NumOfOperations,  SearchTreeNodes = 1;
StackElement *FirstOfStack;
NodeType *ActualNode, *SonNode;
