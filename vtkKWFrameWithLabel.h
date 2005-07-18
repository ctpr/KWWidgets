/*=========================================================================

  Module:    $RCSfile: vtkKWFrameWithLabel.h,v $

  Copyright (c) Kitware, Inc.
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkKWFrameWithLabel - a frame with a grooved border and a label
// .SECTION Description
// The vtkKWFrameWithLabel creates a frame with a grooved border, and a label
// embedded in the upper left corner of the grooved border.


#ifndef __vtkKWFrameWithLabel_h
#define __vtkKWFrameWithLabel_h

#include "vtkKWCompositeWidget.h"

class vtkKWApplication;
class vtkKWFrame;
class vtkKWIcon;
class vtkKWLabel;
class vtkKWLabelWithLabel;

class KWWIDGETS_EXPORT vtkKWFrameWithLabel : public vtkKWCompositeWidget
{
public:
  static vtkKWFrameWithLabel* New();
  vtkTypeRevisionMacro(vtkKWFrameWithLabel,vtkKWCompositeWidget);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Create the widget.
  virtual void Create(vtkKWApplication *app);

  // Description:
  // Set the label for the frame.
  void SetLabelText(const char *);
  
  // Description:
  // Ask the frame to readjust its tops margin according to the content of
  // the LabelFrame. This method if bound to a Configure event, so
  // the widget should adjust itself automatically most of the time.
  void AdjustMargin();
 
  // Description:
  // Get the internal frame.
  vtkGetObjectMacro(Frame, vtkKWFrame);

  // Description:
  // Get the internal frame containing the label.
  vtkGetObjectMacro(LabelFrame, vtkKWFrame);

  // Description:
  // Get the label (frame title).
  virtual vtkKWLabel *GetLabel();

  // Description:
  // Show or hide the frame.
  void PerformShowHideFrame();

  // Description:
  // Globally enable or disable show/hide frame.
  // By default it is globally disabled.
  static void AllowShowHideOn();
  static void AllowShowHideOff();

  // Description:
  // Set/Get ShowHide for this object.
  vtkSetMacro(ShowHideFrame, int);
  vtkBooleanMacro(ShowHideFrame, int);
  vtkGetMacro(ShowHideFrame, int);

  // Description:
  // Globally override the case of the label to ensure GUI consistency.
  // This will change the label when SetLabelText() is called.
  // Defaults to LabelCaseUppercaseFirst.
  //BTX
  enum
  {
    LabelCaseUserSpecified = 0,
    LabelCaseUppercaseFirst,
    LabelCaseLowercaseFirst
  };
  //ETX
  static void SetLabelCase(int v);
  static int GetLabelCase();
  static void SetLabelCaseToUserSpecified() 
    { vtkKWFrameWithLabel::SetLabelCase(
      vtkKWFrameWithLabel::LabelCaseUserSpecified);};
  static void SetLabelCaseToUppercaseFirst() 
    {vtkKWFrameWithLabel::SetLabelCase(
      vtkKWFrameWithLabel::LabelCaseUppercaseFirst);};
  static void SetLabelCaseToLowercaseFirst() 
    {vtkKWFrameWithLabel::SetLabelCase(
      vtkKWFrameWithLabel::LabelCaseLowercaseFirst);};

  // Description:
  // Globally enable or disable bold label.
  // By default it is globally disabled.
  static void BoldLabelOn();
  static void BoldLabelOff();

  // Description:
  // Show a special icon (lock) when the application is in 
  // Limited Edition Mode and the label frame is disabled.
  virtual void SetShowIconInLimitedEditionMode(int);
  vtkBooleanMacro(ShowIconInLimitedEditionMode, int);
  vtkGetMacro(ShowIconInLimitedEditionMode, int);

  // Description:
  // Update the "enable" state of the object and its internal parts.
  // Depending on different Ivars (this->Enabled, the application's 
  // Limited Edition Mode, etc.), the "enable" state of the object is updated
  // and propagated to its internal parts/subwidgets. This will, for example,
  // enable/disable parts of the widget UI, enable/disable the visibility
  // of 3D widgets, etc.
  virtual void UpdateEnableState();

  // Description:
  // Get the drag and drop framework.
  // Override the superclass to allow the frame to be dragged using
  // the label.
  virtual vtkKWDragAndDropTargetSet* GetDragAndDropTargetSet();

protected:

  vtkKWFrameWithLabel();
  ~vtkKWFrameWithLabel();

  vtkKWFrame        *Frame;
  vtkKWFrame        *LabelFrame;
  vtkKWLabelWithLabel *Label;

  vtkKWFrame       *Border;
  vtkKWFrame       *Border2;
  vtkKWFrame       *Groove;
  vtkKWLabel        *Icon;
  vtkKWIcon         *IconData;

  int Displayed;
  int ShowHideFrame;
  int ShowIconInLimitedEditionMode;

  static int AllowShowHide;
  static int BoldLabel;
  static int LabelCase;

  virtual vtkKWLabel *GetLabelIcon();

private:
  vtkKWFrameWithLabel(const vtkKWFrameWithLabel&); // Not implemented
  void operator=(const vtkKWFrameWithLabel&); // Not implemented
};

#endif
