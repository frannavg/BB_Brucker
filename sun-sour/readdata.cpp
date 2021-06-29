/* ************************************************************************* */
/*                            Filename: ReadData.c                           */
/*                                                                           */
/*     EXPORT: Procedure Read_Data: Read data from file 'FileName'           */
/* ************************************************************************* */
#include <cstdio>

#include "datastruct.hpp"
#include "table.hpp"
#include "list.hpp"
#include "readdata.hpp"

/* ************************************************************************* */
/*                           Procedure      Read_Data()                      */
/*                                                                           */
/*   INPUT:  FileName:    file which contains the data of the problem        */
/*                                                                           */
/*   FUNCTION: Reads data from file and stores it in global variables.       */
/*             If the file-read is correct Read_Data returns TRUE.           */
/* ************************************************************************* */
bool Read_Data(char *FileName) {
  int i, j, num_of_op_for_job, sum = 1;
  FILE * fp;

  // (1) open input file
  if ((fp = fopen(FileName, "r")) == NULL)
    return false;		/* Can't open input file */

  // (2) read instance size
  if (!fscanf(fp, "%d %d ", &NumOfMachines, &NumOfJobs))
    return false;

  // (3) read jobs
  for (i = 1; i <= NumOfJobs; ++i) {
    if (!fscanf(fp, "%d ", &num_of_op_for_job))
      return false;
    if (!fscanf(fp, "%d %d ", &OpData[sum].process_time, &OpData[sum].machine_nr))
      return false;
    if (num_of_op_for_job == 1) {
      OpsOnMachine[OpData[sum].machine_nr] = Insert(OpsOnMachine[OpData[sum].machine_nr], sum);
      ConjArcs->pred[sum] = Insert(ConjArcs->pred[sum], 0);
      ConjArcs->succ[0] = Insert(ConjArcs->succ[0], sum);
      ConjArcs->succ[sum] = Insert(ConjArcs->succ[sum], MaxNumOfOperations);
      ConjArcs->pred[MaxNumOfOperations] = Insert(ConjArcs->pred[MaxNumOfOperations], sum);
      sum++;
    } else {
      OpsOnMachine[OpData[sum].machine_nr] = Insert(OpsOnMachine[OpData[sum].machine_nr], sum);
      ConjArcs->pred[sum] = Insert(ConjArcs->pred[sum], 0);
      ConjArcs->succ[0] = Insert(ConjArcs->succ[0], sum);
      ConjArcs->succ[sum] = Insert(ConjArcs->succ[sum], sum + 1);
      sum++;
      for (j = 2; j < num_of_op_for_job; ++j) {
	if (!fscanf(fp, "%d %d ", &OpData[sum].process_time, &OpData[sum].machine_nr))
	  return false;
	OpsOnMachine[OpData[sum].machine_nr] = Insert(OpsOnMachine[OpData[sum].machine_nr], sum);
	ConjArcs->pred[sum] = Insert(ConjArcs->pred[sum], sum - 1);
	ConjArcs->succ[sum] = Insert(ConjArcs->succ[sum], sum + 1);
	sum++;
      }
      if (!fscanf(fp, "%d %d ", &OpData[sum].process_time, &OpData[sum].machine_nr))
	return false;
      OpsOnMachine[OpData[sum].machine_nr] = Insert(OpsOnMachine[OpData[sum].machine_nr], sum);
      ConjArcs->pred[sum] = Insert(ConjArcs->pred[sum], sum - 1);
      ConjArcs->succ[sum] = Insert(ConjArcs->succ[sum], MaxNumOfOperations);
      ConjArcs->pred[MaxNumOfOperations] = Insert(ConjArcs->pred[MaxNumOfOperations], sum);
      sum++;
    }
  }
  fclose(fp);
  NumOfOperations = --sum;
  return true;
}
