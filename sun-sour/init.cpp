/* ************************************************************************* */
/*                             Filename: Init.c                              */
/*                                                                           */
/*    EXPORT: Procedure Initialize:                                          */
/*                      Initialization of global variables                   */
/* ************************************************************************* */
#include <cstdio>
#include <cstdlib>
#include <limits>
using namespace std;

#include "datastruct.hpp"
#include "table.hpp"
#include "init.hpp"

/* ************************************************************************* */
/*                           Procedure  Initialize()                         */
/*                                                                           */
/*  INPUT : -/-                                                              */
/*                                                                           */
/*  FUNCTION: Initialization of global variables;                            */
/*            Initialization of the file "output.dat"                        */
/* ************************************************************************* */
void Initialize() {
  int i;
  FILE * fp;
  fp = fopen("output.dat", "w");
  fclose(fp);
  UpperBound = numeric_limits<int>::max();
  FirstOfStack = NIL;
  SonNode = (NodeType *) malloc(sizeof(NodeType));

  /* Speicherplatz fuer SonNode; SonNode stellt
     zunaechst die Wurzel des Suchbaumes dar */
  ConjArcs = (ArcList *) malloc(sizeof(ArcList));
  DisjArcs = (ArcList *) malloc(sizeof(ArcList));
  for (i = 0; i <= MaxNumOfOperations; ++i) {
    ConjArcs->pred[i] = ConjArcs->succ[i] = NIL;
    DisjArcs->pred[i] = DisjArcs->succ[i] = NIL;
    SonNode->num_of_succ[i] = SonNode->num_of_pred[i] = 0;
    OpData[i].process_time = 0;
    OpData[i].machine_nr = 0;
  }
  for (i = 0; i <= MaxNumOfMachines; ++i)
    OpsOnMachine[i] = NIL;
}
