// Copyright (c) 2010, Lawrence Livermore National Security, LLC. Produced at
// the Lawrence Livermore National Laboratory. LLNL-CODE-443271. All Rights
// reserved. See file COPYRIGHT for details.
//
// This file is part of the GLVis visualization tool and library. For more
// information and source code availability see http://glvis.org.
//
// GLVis is free software; you can redistribute it and/or modify it under the
// terms of the GNU Lesser General Public License (as published by the Free
// Software Foundation) version 2.1 dated February 1999.

#ifndef GLVIS_AUX_VIS
#define GLVIS_AUX_VIS

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>

#include "tk.h"
#include "aux_gl.hpp"

#include "openglvis.hpp"

extern float MatAlpha;
extern float MatAlphaCenter;

/// Initializes the visualization and some keys.
int InitVisualization(const char name[], int x, int y, int w, int h);

/// Start the infinite visualization loop.
void SetVisualizationScene(VisualizationScene * scene,
                           int view = 3, const char *keys = NULL);

void KillVisualization();

/// Send expose event. In our case MyReshape is executed and Draw after it.
void SendExposeEvent();

void MyExpose();

void MainLoop();
void AddIdleFunc(void (*Func)(void));
void RemoveIdleFunc(void (*Func)(void));

void LeftButtonDown  (AUX_EVENTREC *event);
void LeftButtonLoc   (AUX_EVENTREC *event);
void LeftButtonUp    (AUX_EVENTREC *event);
void MiddleButtonDown(AUX_EVENTREC *event);
void MiddleButtonLoc (AUX_EVENTREC *event);
void MiddleButtonUp  (AUX_EVENTREC *event);
void RightButtonDown (AUX_EVENTREC *event);
void RightButtonLoc  (AUX_EVENTREC *event);
void RightButtonUp   (AUX_EVENTREC *event);

void KeyCtrlP();
void KeyS();
void KeyQPressed();
void ToggleThreads();
void ThreadsPauseFunc(GLenum);
void ThreadsStop();
void ThreadsRun();

void Key1Pressed();
void Key2Pressed();
void Key3Pressed();
void Key4Pressed();
void Key5Pressed();
void Key6Pressed();
void Key7Pressed();
void Key8Pressed();
void Key9Pressed();

void Key0Pressed();
void KeyDeletePressed();
void KeyEnterPressed();

void KeyLeftPressed(GLenum);
void KeyRightPressed(GLenum);
void KeyUpPressed(GLenum);
void KeyDownPressed(GLenum);
void KeyJPressed();
void KeyMinusPressed();
void KeyPlusPressed();

void ZoomIn();
void ZoomOut();
void ScaleUp();
void ScaleDown();
void LookAt();
void ShrinkWindow();
void EnlargeWindow();
void MoveResizeWindow(int x, int y, int w, int h);
void ResizeWindow(int w, int h);
void SetWindowTitle(const char *title);

/// Take a screenshot using libtiff, libpng or xwd
int Screenshot(const char *fname, bool convert = false);

/// Send a sequence of keystrokes to the visualization window
void SendKeySequence(const char *seq);

// Directly call the functions assigned to the given keys. Unlike the above
// function, SendKeySequence(), this function does not send X events and
// actually disables the function SendExposeEvent() used by many of the
// functions assigned to keys. Call MyExpose() after calling this function to
// update the visualization window.
void CallKeySequence(const char *seq);

void Cone();

extern int MySetColorLogscale;
void MySetColor(double val, double min, double max);
void MySetColor(double val);
void SetUseTexture(int ut);
int GetUseTexture();
int GetMultisample();
void SetMultisample(int m);

#ifdef GLVIS_USE_FREETYPE
int RenderBitmapText(const char *text, int &width, int &heigth);
void DrawBitmapText(); // Draws the last rendered bitmap text
void DrawBitmapText(const char *text);
int SetFontFile(const char *font_file, int height);
int SetFont(const char *font_patterns[], int num_patterns, int height);
#endif

void SetFont(const char *fn);

#endif
