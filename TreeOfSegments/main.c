#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <crtdbg.h>
#include "TreeOfSegments.h"

int main(void){
  FILE *F;
  if ((F = fopen("input.txt", "r")) == NULL){
    return;
  }

  int numOfSegments;
   fscanf(F, "%i", &numOfSegments);

  Tree *tree = CreateTreeOfSegments();

  for (int i = 0; i < numOfSegments; i++){
    NodeData data;
    fscanf(F, "%i", &data.leftBoard);
    fscanf(F, "%i", &data.rightBoard);
    data.maxRightBoard = data.rightBoard;
    AddElement(tree, data);
  }

  //Tree *intesection = CreateTreeOfSegments();
  //intesection->head = Intersections(tree, -1, 8);
  DeleteTree(tree);
  fclose(F);
  _CrtDumpMemoryLeaks();
}