// Copyright (c) 2010, Lawrence Livermore National Security, LLC. Produced at
// the Lawrence Livermore National Laboratory. LLNL-CODE-443271. All Rights
// reserved. See file COPYRIGHT for details.
//
// This file is part of the GLVis visualization tool and library. For more
// information and source code availability see http://glvis.googlecode.com.
//
// GLVis is free software; you can redistribute it and/or modify it under the
// terms of the GNU Lesser General Public License (as published by the Free
// Software Foundation) version 2.1 dated February 1999.

#ifndef GLVIS_VSSOLUTION_3D
#define GLVIS_VSSOLUTION_3D

#include "mfem.hpp"
using namespace mfem;

class VisualizationSceneSolution3d : public VisualizationSceneScalarData
{
protected:

   int drawmesh, drawelems, shading;
   int displlist, linelist;
   int cplane, cplanelist, cplanelineslist, lsurflist;
   int cp_drawmesh, cp_drawelems, drawlsurf;

   double *node_pos;

   int nlevels;
   Array<double> levels;

   GridFunction *GridF;

   void Init();

   void GetFaceNormals(const int FaceNo, const int side,
                       const IntegrationRule &ir, DenseMatrix &normals);

   void DrawRefinedSurf (int n, double *points, int elem, int func,
                         int part = -1);
   void DrawRefinedSurf (int n, DenseMatrix &pointmat,
                         Vector &values, Array<int> &RefGeoms);
   void DrawRefinedSurfLevelLines (int n, DenseMatrix &pointmat,
                                   Vector &values, Array<int> &RefGeoms);
   void DrawRefinedSurfEdges (int n, DenseMatrix &pointmat,
                              Vector &values, Array<int> &RefEdges,
                              int part = -1);
   void LiftRefinedSurf (int n, DenseMatrix &pointmat,
                         Vector &values, int *RG);
   void DrawTetLevelSurf(const DenseMatrix &verts, const Vector &vals,
                         const int *ind, const Array<double> &levels,
                         const DenseMatrix *grad = NULL);

   int GetAutoRefineFactor();

public:
   int TimesToRefine;
   double FaceShiftScale;

   Array<int> bdr_attr_to_show;

   VisualizationSceneSolution3d();
   VisualizationSceneSolution3d(Mesh & m, Vector & s);

   void SetGridFunction (GridFunction *gf) { GridF = gf; };

   void NewMeshAndSolution(Mesh *new_m, Vector *new_sol,
                           GridFunction *new_u = NULL);

   virtual ~VisualizationSceneSolution3d();

   virtual void FindNewBox(bool prepare);
   virtual void FindNewValueRange(bool prepare);

   virtual void PrepareFlat();
   virtual void PrepareLines();
   virtual void Prepare();
   virtual void Draw();

   void ToggleDrawElems()
   { drawelems = !drawelems; Prepare(); }

   void ToggleDrawMesh();

   void ToggleShading();
   int GetShading() { return shading; };
   virtual void SetShading(int, bool);
   virtual void SetRefineFactors(int, int);
   virtual void AutoRefine();
   virtual void ToggleAttributes(Array<int> &attr_list);

   void FindNodePos();

   void CuttingPlaneFunc (int type);
   void CPPrepare();
   void CPMoved();
   void PrepareFlat2();
   void PrepareLines2();
   virtual void PrepareCuttingPlane();
   void PrepareCuttingPlane2();
   void PrepareCuttingPlaneLines();
   void PrepareCuttingPlaneLines2();
   void PrepareLevelSurf();
   void ToggleCuttingPlane();
   void ToggleCPDrawElems();
   void ToggleCPDrawMesh();
   void MoveLevelSurf(int);
   void NumberOfLevelSurf(int);
   virtual void EventUpdateColors();
   virtual void UpdateLevelLines()
   { PrepareLines(); PrepareCuttingPlaneLines(); }
   virtual void UpdateValueRange(bool prepare);
};

int Normalize(DenseMatrix &normals);

int Compute3DUnitNormal(const double p1[], const double p2[],
                        const double p3[], double nor[]);

int Compute3DUnitNormal (const double p1[], const double p2[],
                         const double p3[], const double p4[], double nor[]);

#endif
