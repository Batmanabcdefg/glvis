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

#ifndef GLVIS_THREADS
#define GLVIS_THREADS

#include <pthread.h>

class GLVisCommand
{
private:
   // Pointers to global GLVis data
   VisualizationSceneScalarData **vs;
   Mesh          **mesh;
   GridFunction  **grid_f;
   Vector         *sol;
   bool           *keep_attr;
   bool           *fix_elem_orient;

   pthread_mutex_t glvis_mutex;
   pthread_cond_t  glvis_cond;
   int num_waiting;
   bool terminating;
   int pfd[2];  // pfd[0] -- reading, pfd[1] -- writing

   enum
   {
      NO_COMMAND = 0,
      NEW_MESH_AND_SOLUTION = 1,
      SCREENSHOT = 2,
      KEY_COMMANDS = 3,
      WINDOW_SIZE = 4,
      WINDOW_TITLE = 5,
      PAUSE = 6,
      VIEW_ANGLES = 7,
      ZOOM = 8,
      SUBDIVISIONS = 9,
      VALUE_RANGE = 10,
      SHADING = 11,
      VIEW_CENTER = 12,
      AUTOSCALE = 13,
      PALETTE = 14,
      CAMERA = 15,
      AUTOPAUSE = 16
   };

   // command to be executed
   int command;

   // command arguments
   Mesh         *new_m;
   GridFunction *new_g;
   std::string   screenshot_filename;
   std::string   key_commands;
   int           window_w, window_h;
   std::string   window_title;
   double        view_ang_theta, view_ang_phi;
   double        zoom_factor;
   int           subdiv_tot, subdiv_bdr;
   double        val_min, val_max;
   std::string   shading;
   double        view_center_x, view_center_y;
   std::string   autoscale_mode;
   int           palette;
   double        camera[9];
   std::string   autopause_mode;

   // internal variables
   int autopause;

   int lock();
   int signal();
   void unlock();

public:
   // called by the main execution thread
   GLVisCommand(VisualizationSceneScalarData **_vs, Mesh **_mesh,
                GridFunction **_grid_f, Vector *_sol, bool *_keep_attr,
                bool *_fix_elem_orient);

   // to be used by the main execution (visualization) thread
   int ReadFD() { return pfd[0]; }

   // to be used worker threads
   bool KeepAttrib() { return *keep_attr; } // may need to sync this
   bool FixElementOrientations() { return *fix_elem_orient; }

   // called by worker threads
   int NewMeshAndSolution(Mesh *_new_m, GridFunction *_new_g);
   int Screenshot(const char *filename);
   int KeyCommands(const char *keys);
   int WindowSize(int w, int h);
   int WindowTitle(const char *title);
   int Pause();
   int ViewAngles(double theta, double phi);
   int Zoom(double factor);
   int Subdivisions(int tot, int bdr);
   int ValueRange(double minv, double maxv);
   int SetShading(const char *shd);
   int ViewCenter(double x, double y);
   int Autoscale(const char *mode);
   int Palette(int pal);
   int Camera(const double cam[]);
   int Autopause(const char *mode);

   // called by the main execution thread
   int Execute();

   // called by the main execution thread
   void Terminate();

   void ToggleAutopause();

   // called by the main execution thread
   ~GLVisCommand();
};

extern GLVisCommand *glvis_command;

class communication_thread
{
private:
   // streams to read data from
   Array<std::istream *> &is;

   // data that may be dynamically allocated by the thread
   Mesh *new_m;
   GridFunction *new_g;
   std::string ident;

   // thread id
   pthread_t tid;

   static void cancel_off()
   {
      pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
   }

   static void cancel_on()
   {
      pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
   }

   static void *execute(void *);

public:
   communication_thread(Array<std::istream *> &_is);

   ~communication_thread();
};

#endif
