/*=========================================================================

  Module:    $RCSfile: vtkKWWidgetWithScrollbars.h,v $

  Copyright (c) Kitware, Inc.
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkKWWidgetWithScrollbars - an abstract class for composite widgets associated to two vtkKWScrollbar's
// .SECTION Description
// This provide a boilerplate for a composite widget associated to a horizontal
// and vertical scrollbars.
// Be aware that most subclasses of vtkKWWidgetWithScrollbars are 
// generated automatically out of the vtkKWWidgetWithScrollbarsSubclass 
// template located in the Templates directory: therefore, even though the
// source code for those vtkKWWidgetWithScrollbars subclasses does not exist 
// in the KWWidgets repository, they are still generated automatically and 
// documented in the API online: check the vtkKWWidgetWithScrollbars API 
// online for its subclasses, as well as the \subpage 
// kwwidgets_autogenerated_page "Auto-Generated Classes" page. Classes related
// to the same template can be found in the 
// \ref kwwidgets_autogenerated_widget_with_scrollbars_group section.
// .SECTION See Also
// vtkKWCanvasWithScrollbars vtkKWListBoxWithScrollbars vtkKWMultiColumnListWithScrollbars vtkKWTextWithScrollbars vtkKWTreeWithScrollbars

#ifndef __vtkKWWidgetWithScrollbars_h
#define __vtkKWWidgetWithScrollbars_h

#include "vtkKWCompositeWidget.h"

class vtkKWScrollbar;

class KWWidgets_EXPORT vtkKWWidgetWithScrollbars : public vtkKWCompositeWidget
{
public:
  vtkTypeRevisionMacro(vtkKWWidgetWithScrollbars,vtkKWCompositeWidget);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Set/Get the vertical scrollbar visibility (default to On).
  virtual void SetVerticalScrollbarVisibility(int val);
  vtkGetMacro(VerticalScrollbarVisibility, int);
  vtkBooleanMacro(VerticalScrollbarVisibility, int);

  // Description:
  // Set/Get the horizontal scrollbar visibility (default to On).
  virtual void SetHorizontalScrollbarVisibility(int val);
  vtkGetMacro(HorizontalScrollbarVisibility, int);
  vtkBooleanMacro(HorizontalScrollbarVisibility, int);

  // Description:
  // Access the internal scrollbars.
  vtkGetObjectMacro(VerticalScrollbar, vtkKWScrollbar);
  vtkGetObjectMacro(HorizontalScrollbar, vtkKWScrollbar);

  // Description:
  // Update the "enable" state of the object and its internal parts.
  // Depending on different Ivars (this->Enabled, the application's 
  // Limited Edition Mode, etc.), the "enable" state of the object is updated
  // and propagated to its internal parts/subwidgets. This will, for example,
  // enable/disable parts of the widget UI, enable/disable the visibility
  // of 3D widgets, etc.
  virtual void UpdateEnableState();

protected:
  vtkKWWidgetWithScrollbars();
  ~vtkKWWidgetWithScrollbars();

  // Description:
  // Create the widget.
  virtual void CreateWidget();

  // Description:
  // Scrollbar visibility flags
  int VerticalScrollbarVisibility;
  int HorizontalScrollbarVisibility;

  // Description:
  // Scrollbars
  vtkKWScrollbar *VerticalScrollbar;
  vtkKWScrollbar *HorizontalScrollbar;

  // Description:
  // Create scrollbars and associate the scrollbars to a widget by
  // setting up the callbacks between both instances.
  // The associated *has* to be made for this class to work, but
  // since we do not know the internal widget at that point, it is up
  // to the subclass to reimplement both Create*Scrollbar() methods
  // and have them simply call the super and the Associate*Scrollbar() 
  // methods with the internal argument as parameter.
  virtual void CreateHorizontalScrollbar();
  virtual void CreateVerticalScrollbar();
  virtual void AssociateHorizontalScrollbarToWidget(vtkKWCoreWidget *widget);
  virtual void AssociateVerticalScrollbarToWidget(vtkKWCoreWidget *widget);

  // Description:
  // Pack or repack the widget. This should be implemented by subclasses,
  // but a convenience function PackScrollbarsWithWidget() can be
  // called from the subclass just as easily.
  virtual void Pack() = 0;
  virtual void PackScrollbarsWithWidget(vtkKWWidget *widget);

private:

  vtkKWWidgetWithScrollbars(const vtkKWWidgetWithScrollbars&); // Not implemented
  void operator=(const vtkKWWidgetWithScrollbars&); // Not implemented
};

#endif
