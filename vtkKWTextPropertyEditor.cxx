/*=========================================================================

  Module:    $RCSfile: vtkKWTextPropertyEditor.cxx,v $

  Copyright (c) Kitware, Inc.
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkKWTextPropertyEditor.h"

#include "vtkActor2D.h"
#include "vtkKWChangeColorButton.h"
#include "vtkKWCheckButton.h"
#include "vtkKWCheckButtonSet.h"
#include "vtkKWLabel.h"
#include "vtkKWCheckButtonSetWithLabel.h"
#include "vtkKWMenuButtonWithLabel.h"
#include "vtkKWPushButtonSetWithLabel.h"
#include "vtkKWMenuButton.h"
#include "vtkKWPushButton.h"
#include "vtkKWPushButtonSet.h"
#include "vtkKWScaleWithEntry.h"
#include "vtkKWTkUtilities.h"
#include "vtkObjectFactory.h"
#include "vtkProperty2D.h"
#include "vtkTextProperty.h"

#define VTK_KW_TEXT_PROP_ARIAL   "Arial"
#define VTK_KW_TEXT_PROP_COURIER "Courier"
#define VTK_KW_TEXT_PROP_TIMES   "Times"

#define VTK_KW_TEXT_PROP_BOLD_ID   0
#define VTK_KW_TEXT_PROP_ITALIC_ID 1
#define VTK_KW_TEXT_PROP_SHADOW_ID 2

#define VTK_KW_TEXT_PROP_COPY_ID 0

/* 
 * This part was generated by ImageConvert from image:
 *    bold.png (zlib, base64)
 */
#define image_bold_width         12
#define image_bold_height        16
#define image_bold_pixel_size    4
#define image_bold_length 152

static unsigned char image_bold[] = 
  "eNr7//8/w38aYiBQAuI0IH4HxP+huByIZ0LFzkD56GA3knoYMEYzg5B6ZPF3NFCP7J40PO"
  "ph/gWx7wKxCxH+VULS846A+cgAOZxdSPAvepjiUn8Gh58Jhc8ZJH+hp4dVQNyBlh4EQYr/"
  "0zh9AgBC7tWi";

/* 
 * This part was generated by ImageConvert from image:
 *    italic.png (zlib, base64)
 */
#define image_italic_width         12
#define image_italic_height        16
#define image_italic_pixel_size    4
#define image_italic_length 140

static unsigned char image_italic[] = 
  "eNr7//8/w38aYyzABYjvAjFIsgOIlQioB4HdUD1gQIT6d0A8k0j1LlC3hBKpvgOqXpBI9W"
  "eg7mcgQr0S1OxyItWnQdUrEal+FXI4EqH+HdS/xKgPRQ9HHOoFoWrOIKcBXOppiQHpUhBU";

/* 
 * This part was generated by ImageConvert from image:
 *    shadow.png (zlib, base64)
 */
#define image_shadow_width         12
#define image_shadow_height        16
#define image_shadow_pixel_size    4
#define image_shadow_length 384

static unsigned char image_shadow[] = 
  "eNq10s8rRFEYxvFhRmZIzSATXSnNlR/JwsiMsiALyo+sxFqUmhVFdjaSBWv/go2VlY38Bf"
  "4DS6uJsrC8vk89i9PZO/Xpdmeec977vvdmWZbL/pnXOR58fcQN1nLBCvJHznShH8N4wz6q"
  "6EM+yL/gFgmaWMIFTl1jEqUgr7O//P8u5jCCA2xiQTWC/Dy+9Yh4Rl31Ucasz++N+t3Ah/"
  "f84EQZ7xlAd5RXT8t4wq/3XWMIRXQG+XHdYxAruMQn2tjBKApBXjPv8DxVfwZ3rnGFLT1T"
  "NE/NseLaBc/q1XNtIY3m+Y577OHYZ0z4Xr1PB3mdO4ZDnHlWZfe17R6SaD76Btb9vhruYR"
  "GrmIrer1bJ30OKmq+pf+vRPJT9A5tnxYs=";

/* 
 * This part was generated by ImageConvert from image:
 *    copy.png (zlib, base64)
 */
#define image_copy_width         15
#define image_copy_height        16
#define image_copy_pixel_size    4
#define image_copy_length 124

static unsigned char image_copy[] = 
  "eNqlkwkKACAIBHu6P9+CLjNlpYSlCKZJJAAFj2kFL1nWVpaPWLVSVrnGXtwwb+fFPdO89e"
  "5IeN/kmffsxfaQ997vz3nN7Bfrh3vj2XEvY1+9LPj4Rz+pVM55tQ==";

// ----------------------------------------------------------------------------
vtkStandardNewMacro(vtkKWTextPropertyEditor);
vtkCxxRevisionMacro(vtkKWTextPropertyEditor, "$Revision: 1.19 $");

// ----------------------------------------------------------------------------
vtkKWTextPropertyEditor::vtkKWTextPropertyEditor()
{
  this->TextProperty = NULL;
  this->Actor2D = NULL;

  this->LongFormat = 0;
  this->LabelOnTop = 1;

  this->LabelVisibility = 0;
  this->Label = vtkKWLabel::New();

  this->ColorVisibility = 1;
  this->ChangeColorButton = vtkKWChangeColorButton::New();

  this->FontFamilyVisibility = 1;
  this->FontFamilyOptionMenu = vtkKWMenuButtonWithLabel::New();

  this->StylesVisibility = 1;
  this->StylesCheckButtonSet = vtkKWCheckButtonSetWithLabel::New();

  this->OpacityVisibility = 1;
  this->OpacityScale = vtkKWScaleWithEntry::New();

  this->ChangedCommand = NULL;
  this->ColorChangedCommand = NULL;

  this->CopyVisibility = 0;
  this->PushButtonSet = vtkKWPushButtonSetWithLabel::New();
}

// ----------------------------------------------------------------------------
vtkKWTextPropertyEditor::~vtkKWTextPropertyEditor()
{
  this->SetTextProperty(NULL);
  this->SetActor2D(NULL);

  if (this->ChangedCommand)
    {
    delete [] this->ChangedCommand;
    this->ChangedCommand = NULL;
    }

  if (this->ColorChangedCommand)
    {
    delete [] this->ColorChangedCommand;
    this->ColorChangedCommand = NULL;
    }

  if (this->Label)
    {
    this->Label->Delete();
    this->Label = NULL;
    }

  if (this->ChangeColorButton)
    {
    this->ChangeColorButton->Delete();
    this->ChangeColorButton = NULL;
    }

  if (this->FontFamilyOptionMenu)
    {
    this->FontFamilyOptionMenu->Delete();
    this->FontFamilyOptionMenu = NULL;
    }

  if (this->StylesCheckButtonSet)
    {
    this->StylesCheckButtonSet->Delete();
    this->StylesCheckButtonSet = NULL;
    }

  if (this->OpacityScale)
    {
    this->OpacityScale->Delete();
    this->OpacityScale = NULL;
    }

  if (this->PushButtonSet)
    {
    this->PushButtonSet->Delete();
    this->PushButtonSet = NULL;
    }
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::Create()
{
  // Check if already created

  if (this->IsCreated())
    {
    vtkErrorMacro(<< this->GetClassName() << " already created");
    return;
    }

  // Call the superclass to create the whole widget

  this->Superclass::Create();

  // Label

  this->Label->SetParent(this);
  this->Label->Create();

  // Color

  this->ChangeColorButton->SetParent(this);
  this->ChangeColorButton->LabelOutsideButtonOn();
  this->ChangeColorButton->Create();
  this->ChangeColorButton->SetCommand(this, "ChangeColorButtonCallback");
  this->ChangeColorButton->SetBalloonHelpString("Select the text color.");
  this->ChangeColorButton->SetDialogTitle("Text Color");

  // Font Family

  this->FontFamilyOptionMenu->SetParent(this);
  this->FontFamilyOptionMenu->Create();
  this->FontFamilyOptionMenu->ExpandWidgetOff();
  this->FontFamilyOptionMenu->SetBalloonHelpString("Select the font.");

  vtkKWMenuButton *omenu = this->FontFamilyOptionMenu->GetWidget();
  omenu->SetWidth(7);
  omenu->SetPadX(0);
  omenu->SetPadY(2);

  omenu->AddRadioButton(VTK_KW_TEXT_PROP_ARIAL, this, "FontFamilyCallback");
  omenu->AddRadioButton(VTK_KW_TEXT_PROP_COURIER, this, "FontFamilyCallback");
  omenu->AddRadioButton(VTK_KW_TEXT_PROP_TIMES, this, "FontFamilyCallback");

  // Styles (bold, italic, shadow)

  this->StylesCheckButtonSet->SetParent(this);
  this->StylesCheckButtonSet->Create();
  this->StylesCheckButtonSet->SetBalloonHelpString("Select the font style.");

  vtkKWCheckButtonSet *cbs = this->StylesCheckButtonSet->GetWidget();
  cbs->PackHorizontallyOn();

  vtkKWCheckButton *cb;

  cb = cbs->AddWidget(VTK_KW_TEXT_PROP_BOLD_ID);
  cb->SetCommand(this, "BoldCallback");
  cb->SetBalloonHelpString("Select bold style.");
  cb->IndicatorVisibilityOff();
  cb->SetPadX(0);
  cb->SetPadY(0);

  cb->SetImageToPixels(image_bold, 
                       image_bold_width, 
                       image_bold_height, 
                       image_bold_pixel_size,
                       image_bold_length);

  cb = cbs->AddWidget(VTK_KW_TEXT_PROP_ITALIC_ID);
  cb->SetCommand(this, "ItalicCallback");
  cb->SetBalloonHelpString("Select italic style.");
  cb->IndicatorVisibilityOff();
  cb->SetPadX(0);
  cb->SetPadY(0);

  cb->SetImageToPixels(image_italic, 
                       image_italic_width, 
                       image_italic_height, 
                       image_italic_pixel_size,
                       image_italic_length);

  cb = cbs->AddWidget(VTK_KW_TEXT_PROP_SHADOW_ID);
  cb->SetCommand(this, "ShadowCallback");
  cb->SetBalloonHelpString("Select shadow style.");
  cb->IndicatorVisibilityOff();
  cb->SetPadX(0);
  cb->SetPadY(0);

  cb->SetImageToPixels(image_shadow, 
                       image_shadow_width, 
                       image_shadow_height, 
                       image_shadow_pixel_size,
                       image_shadow_length);

  // Opacity

  this->OpacityScale->SetParent(this);
  this->OpacityScale->PopupModeOn();
  this->OpacityScale->Create();
  this->OpacityScale->SetResolution(0.01);
  this->OpacityScale->SetRange(0.0, 1.0);
  this->OpacityScale->SetLabelText("");
  this->OpacityScale->SetEntryWidth(4);
  this->OpacityScale->SetCommand(this, "OpacityCallback");
  this->OpacityScale->SetEndCommand(this, "OpacityEndCallback");
  this->OpacityScale->SetEntryCommand(this, "OpacityEndCallback");
  this->OpacityScale->SetBalloonHelpString("Select the text opacity.");

  // Buttons

  this->PushButtonSet->SetParent(this);
  this->PushButtonSet->SetLabelPositionToLeft();
  this->PushButtonSet->Create();
  this->PushButtonSet->ExpandWidgetOff();

  vtkKWPushButtonSet *pbs = this->PushButtonSet->GetWidget();
  pbs->PackHorizontallyOn();

  vtkKWPushButton *pb;

  // Buttons : copy button

  pb = pbs->AddWidget(VTK_KW_TEXT_PROP_COPY_ID);
  pb->SetImageToPixels(image_copy, 
                       image_copy_width, 
                       image_copy_height, 
                       image_copy_pixel_size,
                       image_copy_length);

  // Pack

  this->Pack();

  // Update

  this->UpdateInterface();
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::Pack()
{
  if (!this->IsCreated())
    {
    return;
    }

  ostrstream tk_cmd;

  this->ChangeColorButton->UnpackSiblings();

  if (this->LongFormat)
    {
    this->ChangeColorButton->GetLabel()->SetText("Color:");
    this->ChangeColorButton->LabelVisibilityOn();

    this->FontFamilyOptionMenu->GetWidget()->IndicatorVisibilityOn();
    this->FontFamilyOptionMenu->GetLabel()->SetText("Font:");
    this->FontFamilyOptionMenu->LabelVisibilityOn();

    this->StylesCheckButtonSet->GetLabel()->SetText("Style:");
    this->StylesCheckButtonSet->LabelVisibilityOn();

    this->OpacityScale->SetLabelText("Opacity:");

    this->PushButtonSet->GetLabel()->SetText("Functions:");
    this->PushButtonSet->LabelVisibilityOn();

    int row = 0, col = 0;

    tk_cmd << "grid " 
           << this->Label->GetWidgetName() 
           << " -sticky nsw -column " << col << " -row " << row << endl;

    if (this->LabelOnTop)
      {
      row++;
      }
    else
      {
      col = 1;
      }

    const char *options = " -sticky nsw -pady 1 -padx 10";
    
    tk_cmd << "grid " << this->ChangeColorButton->GetWidgetName() << options 
           << " -column " << col << " -row " << row++ << endl;
    tk_cmd << "grid " << this->FontFamilyOptionMenu->GetWidgetName() << options 
           << " -column " << col << " -row " << row++ << endl;
    tk_cmd << "grid " << this->StylesCheckButtonSet->GetWidgetName() << options 
           << " -column " << col << " -row " << row++ << endl;
    tk_cmd << "grid " << this->OpacityScale->GetWidgetName() << options 
             << " -column " << col << " -row " << row++ << endl;
    tk_cmd  << "grid " << this->PushButtonSet->GetWidgetName() << options 
           << " -column " << col << " -row " << row++ << endl;
    }
  else
    {
    this->ChangeColorButton->LabelVisibilityOff();

    this->FontFamilyOptionMenu->GetWidget()->IndicatorVisibilityOff();
    this->FontFamilyOptionMenu->LabelVisibilityOff();

    this->StylesCheckButtonSet->LabelVisibilityOff();

    this->OpacityScale->SetLabelText("");

    this->PushButtonSet->LabelVisibilityOff();

    tk_cmd << "grid "
           << this->Label->GetWidgetName() << " "
           << this->ChangeColorButton->GetWidgetName() << " "
           << this->FontFamilyOptionMenu->GetWidgetName() << " "
           << this->StylesCheckButtonSet->GetWidgetName() << " "
           << this->OpacityScale->GetWidgetName() << " "
           << this->PushButtonSet->GetWidgetName()
           << " -row 0 -sticky news -padx 1" << endl;
    }

  tk_cmd << ends;
  this->Script(tk_cmd.str());
  tk_cmd.rdbuf()->freeze(0);

  // Synchronize the label width to align everything

  if (this->LongFormat)
    {
    int nb = 0;
    const char *labels[10];
    labels[nb++] = this->ChangeColorButton->GetLabel()->GetWidgetName();
    labels[nb++] = this->FontFamilyOptionMenu->GetLabel()->GetWidgetName();
    labels[nb++] = this->StylesCheckButtonSet->GetLabel()->GetWidgetName();
    labels[nb++] = this->OpacityScale->GetLabel()->GetWidgetName();
    labels[nb++] = this->PushButtonSet->GetLabel()->GetWidgetName();
    vtkKWTkUtilities::SynchroniseLabelsMaximumWidth(
      this->GetApplication(), nb, labels, "-anchor w");
    }
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::Update()
{
  this->UpdateInterface();
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::UpdateInterface()
{
  // Update enable state

  this->UpdateEnableState();

  // Update all components

  this->UpdateLabel();
  this->UpdateColorButton();
  this->UpdateFontFamilyOptionMenu();
  this->UpdateStylesCheckButtonSet();
  this->UpdateOpacityScale();
  this->UpdatePushButtonSet();
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::SetTextProperty(vtkTextProperty *_arg)
{
  if (this->TextProperty == _arg)
    {
    return;
    }

  this->TextProperty = _arg;
  
  if (this->TextProperty)
    {
    this->UpdateInterface();
    }

  this->Modified();
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::SetActor2D(vtkActor2D *_arg)
{
  if (this->Actor2D == _arg)
    {
    return;
    }

  this->Actor2D = _arg;
  
  if (this->Actor2D)
    {
    this->UpdateInterface();
    }

  this->Modified();
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::SetLongFormat(int _arg)
{
  if (this->LongFormat == _arg)
    {
    return;
    }
  this->LongFormat = _arg;
  this->Modified();

  this->Pack();
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::SetLabelVisibility(int _arg)
{
  if (this->LabelVisibility == _arg)
    {
    return;
    }
  this->LabelVisibility = _arg;
  this->Modified();

  this->UpdateLabel();
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::SetLabelOnTop(int _arg)
{
  if (this->LabelOnTop == _arg)
    {
    return;
    }
  this->LabelOnTop = _arg;
  this->Modified();

  this->Pack();
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::UpdateLabel()
{
  if (this->IsCreated() && this->Label)
    {
    this->Script("grid %s %s",
                 (this->LabelVisibility ? "" : "remove"), 
                 this->Label->GetWidgetName());
    }
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::SetColorVisibility(int _arg)
{
  if (this->ColorVisibility == _arg)
    {
    return;
    }
  this->ColorVisibility = _arg;
  this->Modified();

  this->UpdateColorButton();
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::SetColor(double r, double g, double b) 
{
  double *rgb = this->GetColor();
  if (rgb[0] == r && rgb[1] == g && rgb[2] == b)
    {
    return;
    }

  if (this->TextProperty)
    {
    this->TextProperty->SetColor(r, g, b);
    }
  else if (this->Actor2D && this->Actor2D->GetProperty())
    {
    this->Actor2D->GetProperty()->SetColor(r, g, b);
    }

  this->UpdateColorButton();

  this->InvokeColorChangedCommand(r, g, b);
  this->InvokeChangedCommand();
}

// ----------------------------------------------------------------------------
double* vtkKWTextPropertyEditor::GetColor() 
{
  int use_actor_color = 0;
  if (!this->TextProperty)
    {
    use_actor_color = 1;
    }
  else
    {
    // This test is done to maintain backward compatibility (see
    // vtkOpenGL...TextMapper). The default vtkTextProperty color is
    // -1, -1, -1 so that the mappers know that they have to use
    // the actor's color instead.
    double *rgb = this->TextProperty->GetColor();
    if (rgb[0] < 0.0 && rgb[1] < 0.0 && rgb[2] < 0.0)
      {
      use_actor_color = 1;
      }
    }

  if (use_actor_color && this->Actor2D && this->Actor2D->GetProperty())
    {
    return this->Actor2D->GetProperty()->GetColor();
    }
  else if (this->TextProperty)
    {
    return this->TextProperty->GetColor();
    }
  return 0;
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::UpdateColorButton()
{
  if (this->IsCreated() && this->ChangeColorButton)
    {
    if (this->GetColor())
      {
      this->ChangeColorButton->SetColor(this->GetColor());
      }

    this->Script("grid %s %s",
                 (this->ColorVisibility ? "" : "remove"), 
                 this->ChangeColorButton->GetWidgetName());
    }
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::ChangeColorButtonCallback(double r, double g, double b) 
{
  this->SetColor(r, g, b);
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::SetFontFamilyVisibility(int _arg)
{
  if (this->FontFamilyVisibility == _arg)
    {
    return;
    }
  this->FontFamilyVisibility = _arg;
  this->Modified();

  this->UpdateFontFamilyOptionMenu();
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::SetFontFamily(int v) 
{
  if (this->TextProperty)
    {
    if (this->TextProperty->GetFontFamily() == v)
      {
      return;
      }
    this->TextProperty->SetFontFamily(v);
    }

  this->UpdateFontFamilyOptionMenu();

  this->InvokeChangedCommand();
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::UpdateFontFamilyOptionMenu()
{
  if (this->IsCreated() &&
      this->FontFamilyOptionMenu &&
      this->TextProperty)
    {
    switch (this->TextProperty->GetFontFamily())
      {
      case VTK_ARIAL:
        this->FontFamilyOptionMenu->GetWidget()->SetValue(
          VTK_KW_TEXT_PROP_ARIAL);
        break;
      case VTK_COURIER:
        this->FontFamilyOptionMenu->GetWidget()->SetValue(
          VTK_KW_TEXT_PROP_COURIER);
        break;
      case VTK_TIMES:
        this->FontFamilyOptionMenu->GetWidget()->SetValue(
          VTK_KW_TEXT_PROP_TIMES);
        break;
      }
    this->Script("grid %s %s",
                 (this->FontFamilyVisibility ? "" : "remove"), 
                 this->FontFamilyOptionMenu->GetWidgetName());
    }
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::FontFamilyCallback() 
{
  if (this->FontFamilyOptionMenu->IsCreated())
    {
    const char *value = this->FontFamilyOptionMenu->GetWidget()->GetValue();
    if (!strcmp(value, VTK_KW_TEXT_PROP_ARIAL))
      {
      this->SetFontFamily(VTK_ARIAL);
      }
    else if (!strcmp(value, VTK_KW_TEXT_PROP_COURIER))
      {
      this->SetFontFamily(VTK_COURIER);
      }
    else if (!strcmp(value, VTK_KW_TEXT_PROP_TIMES))
      {
      this->SetFontFamily(VTK_TIMES);
      }
    }
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::SetStylesVisibility(int _arg)
{
  if (this->StylesVisibility == _arg)
    {
    return;
    }
  this->StylesVisibility = _arg;
  this->Modified();

  this->UpdateStylesCheckButtonSet();
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::UpdateStylesCheckButtonSet()
{
  if (this->IsCreated() && this->StylesCheckButtonSet)
    {
    this->Script("grid %s %s",
                 (this->StylesVisibility ? "" : "remove"), 
                 this->StylesCheckButtonSet->GetWidgetName());
    }

  this->UpdateBoldCheckButton();
  this->UpdateItalicCheckButton();
  this->UpdateShadowCheckButton();
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::SetBold(int v) 
{
  if (this->TextProperty)
    {
    if (this->TextProperty->GetBold() == v)
      {
      return;
      }
    this->TextProperty->SetBold(v);
    }

  this->UpdateBoldCheckButton();

  this->InvokeChangedCommand();
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::UpdateBoldCheckButton()
{
  if (this->IsCreated() && 
      this->StylesCheckButtonSet &&
      this->TextProperty)
    {
    this->StylesCheckButtonSet->GetWidget()->GetWidget(VTK_KW_TEXT_PROP_BOLD_ID)->SetSelectedState(this->TextProperty->GetBold());
    }
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::BoldCallback(int state) 
{
  this->SetBold(state);
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::SetItalic(int v) 
{
  if (this->TextProperty)
    {
    if (this->TextProperty->GetItalic() == v)
      {
      return;
      }
    this->TextProperty->SetItalic(v);
    }

  this->UpdateItalicCheckButton();

  this->InvokeChangedCommand();
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::UpdateItalicCheckButton()
{
  if (this->IsCreated() && 
      this->StylesCheckButtonSet &&
      this->TextProperty)
    {
    this->StylesCheckButtonSet->GetWidget()->GetWidget(VTK_KW_TEXT_PROP_ITALIC_ID)->SetSelectedState(this->TextProperty->GetItalic());
    }
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::ItalicCallback(int state) 
{
  this->SetItalic(state);
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::SetShadow(int v) 
{
  if (this->TextProperty)
    {
    if (this->TextProperty->GetShadow() == v)
      {
      return;
      }
    this->TextProperty->SetShadow(v);
    }

  this->UpdateShadowCheckButton();

  this->InvokeChangedCommand();
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::UpdateShadowCheckButton()
{
  if (this->IsCreated() && 
      this->StylesCheckButtonSet &&
      this->TextProperty)
    {
    this->StylesCheckButtonSet->GetWidget()->GetWidget(VTK_KW_TEXT_PROP_SHADOW_ID)->SetSelectedState(this->TextProperty->GetShadow());
    }
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::ShadowCallback(int state) 
{
  this->SetShadow(state);
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::SetOpacityVisibility(int _arg)
{
  if (this->OpacityVisibility == _arg)
    {
    return;
    }
  this->OpacityVisibility = _arg;
  this->Modified();

  this->UpdateOpacityScale();
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::SetOpacity(float v) 
{
  if (this->GetOpacity() == v)
    {
    return;
    }

  if (this->TextProperty)
    {
    this->TextProperty->SetOpacity(v);
    }
  else if (this->Actor2D && this->Actor2D->GetProperty())
    {
    this->Actor2D->GetProperty()->SetOpacity(v);
    }

  this->UpdateOpacityScale();

  this->InvokeChangedCommand();
}

// ----------------------------------------------------------------------------
float vtkKWTextPropertyEditor::GetOpacity() 
{
  int use_actor_opacity = 0;
  if (!this->TextProperty)
    {
    use_actor_opacity = 1;
    }
  else
    {
    // This test is done to maintain backward compatibility (see
    // vtkOpenGL...TextMapper). The default vtkTextProperty opacity is
    // -1 so that the mappers know that they have to use
    // the actor's opacity instead.
    if (this->TextProperty->GetOpacity() < 0.0)
      {
      use_actor_opacity = 1;
      }
    }

  if (use_actor_opacity && this->Actor2D && this->Actor2D->GetProperty())
    {
    return this->Actor2D->GetProperty()->GetOpacity();
    }
  else if (this->TextProperty)
    {
    return this->TextProperty->GetOpacity();
    }
  return 0.0;
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::UpdateOpacityScale()
{
  if (this->IsCreated() && 
      this->OpacityScale &&
      this->TextProperty)
    {
    this->OpacityScale->SetValue(this->GetOpacity());
    this->Script("grid %s %s",
                 (this->OpacityVisibility ? "" : "remove"), 
                 this->OpacityScale->GetWidgetName());
    }
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::OpacityCallback(double value) 
{
  this->SetOpacity(value);
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::OpacityEndCallback(double value) 
{
  this->SetOpacity(value);
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::SetCopyVisibility(int _arg)
{
  if (this->CopyVisibility == _arg)
    {
    return;
    }
  this->CopyVisibility = _arg;
  this->Modified();

  this->UpdatePushButtonSet();
}

// ----------------------------------------------------------------------------
vtkKWPushButton* vtkKWTextPropertyEditor::GetCopyButton()
{
  if (this->IsCreated())
    {
    return this->PushButtonSet->GetWidget()->GetWidget(
      VTK_KW_TEXT_PROP_COPY_ID);
    }
  return NULL;
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::UpdatePushButtonSet()
{
  if (this->IsCreated() && this->PushButtonSet)
    {
    this->PushButtonSet->GetWidget()->SetWidgetVisibility(
      VTK_KW_TEXT_PROP_COPY_ID, this->CopyVisibility);

    this->Script("grid %s %s",
                 (this->PushButtonSet->GetWidget()
                  ->GetNumberOfVisibleWidgets() ? "" : "remove"), 
                 this->PushButtonSet->GetWidgetName());
    }
}

// ----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::CopyValuesFrom(vtkKWTextPropertyEditor *widget)
{
  if (widget)
    {
    vtkTextProperty *tprop = widget->GetTextProperty();
    if (tprop)
      {
      this->SetColor(widget->GetColor());
      this->SetFontFamily(tprop->GetFontFamily());
      this->SetBold(tprop->GetBold());
      this->SetItalic(tprop->GetItalic());
      this->SetShadow(tprop->GetShadow());
      this->SetOpacity(widget->GetOpacity());
      }
    }
}

//----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::SaveInTclScript(ofstream *file, 
                                        const char *tcl_name, int tabify)
{
  static int instance_count = 0;

  const char *name;
  char buffer[128];
  if (tcl_name)
    {
    name = tcl_name;
    }
  else
    {
    sprintf(buffer, "TextProperty%d", instance_count++);
    name = buffer;
    *file << "vtkTextProperty " << name << endl;
    }

  vtkTextProperty *tprop = this->TextProperty;

  if (tprop)
    {
    double *rgb = this->GetColor();
    if (tabify)
      {
      *file << "\t";
      }
    *file << name << " SetColor " << rgb[0] << " "  << rgb[1] << " "  << rgb[2]
          << endl;
    if (tabify)
      {
      *file << "\t";
      }
    *file << name << " SetFontFamily " << tprop->GetFontFamily() << endl;
    if (tabify)
      {
      *file << "\t";
      }
    *file << name << " SetBold " << tprop->GetBold() << endl;
    if (tabify)
      {
      *file << "\t";
      }
    *file << name << " SetItalic " << tprop->GetItalic() << endl;
    if (tabify)
      {
      *file << "\t";
      }
    *file << name << " SetShadow " << tprop->GetShadow() << endl;
    if (tabify)
      {
      *file << "\t";
      }
    *file << name << " SetOpacity " << this->GetOpacity() << endl;
    }
}

//----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::UpdateEnableState()
{
  this->Superclass::UpdateEnableState();


  this->PropagateEnableState(this->Label);
  this->PropagateEnableState(this->ChangeColorButton);
  this->PropagateEnableState(this->FontFamilyOptionMenu);
  this->PropagateEnableState(this->StylesCheckButtonSet);
  this->PropagateEnableState(this->OpacityScale);
  this->PropagateEnableState(this->PushButtonSet);
}

//----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::SetChangedCommand(
  vtkObject *object, const char *method)
{
  this->SetObjectMethodCommand(&this->ChangedCommand, object, method);
}

//----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::InvokeChangedCommand()
{
  this->InvokeObjectMethodCommand(this->ChangedCommand);
}

//----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::SetColorChangedCommand(
  vtkObject *object, const char *method)
{
  this->SetObjectMethodCommand(&this->ColorChangedCommand, object, method);
}

//----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::InvokeColorChangedCommand(
  double r, double g, double b)
{
  if (this->GetApplication() &&
      this->ColorChangedCommand && *this->ColorChangedCommand)
    {
    this->Script("%s %lf %lf %lf", this->ColorChangedCommand, r, g, b);
    }
}

//----------------------------------------------------------------------------
void vtkKWTextPropertyEditor::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
  if (this->TextProperty)
    {
    os << indent << "TextProperty:\n";
    this->TextProperty->PrintSelf(os, indent.GetNextIndent());
    }
  else
    {
    os << indent << "TextProperty: None" << endl;
    }
  if (this->Actor2D)
    {
    os << indent << "Actor2D:\n";
    this->Actor2D->PrintSelf(os, indent.GetNextIndent());
    }
  else
    {
    os << indent << "Actor2D: None" << endl;
    }
  os << indent << "LongFormat: " << (this->LongFormat ? "On" : "Off") << endl;
  os << indent << "LabelVisibility: " << (this->LabelVisibility ? "On" : "Off") << endl;
  os << indent << "LabelOnTop: " << (this->LabelOnTop ? "On" : "Off") << endl;
  os << indent << "ColorVisibility: " << (this->ColorVisibility ? "On" : "Off") << endl;
  os << indent << "FontFamilyVisibility: " 
     << (this->FontFamilyVisibility ? "On" : "Off") << endl;
  os << indent << "StylesVisibility: " 
     << (this->StylesVisibility ? "On" : "Off") << endl;
  os << indent << "OpacityVisibility: " 
     << (this->OpacityVisibility ? "On" : "Off") << endl;
  os << indent << "CopyVisibility: " << (this->CopyVisibility ? "On" : "Off") << endl;
  os << indent << "ChangedCommand: " 
     << (this->ChangedCommand ? this->ChangedCommand : "None") << endl;
  os << indent << "ColorChangedCommand: " 
     << (this->ColorChangedCommand ? this->ColorChangedCommand : "None") << endl;
  os << indent << "Label: " << this->Label << endl;
}

