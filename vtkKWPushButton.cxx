/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkKWPushButton.cxx,v $
  Language:  C++
  Date:      $Date: 2002-05-27 19:26:20 $
  Version:   $Revision: 1.7 $

Copyright (c) 2000-2001 Kitware Inc. 469 Clifton Corporate Parkway,
Clifton Park, NY, 12065, USA.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * Neither the name of Kitware nor the names of any contributors may be used
   to endorse or promote products derived from this software without specific 
   prior written permission.

 * Modified source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/
#include "vtkKWApplication.h"
#include "vtkKWPushButton.h"
#include "vtkObjectFactory.h"



//------------------------------------------------------------------------------
vtkStandardNewMacro( vtkKWPushButton );


vtkKWPushButton::vtkKWPushButton()
{
  this->ButtonLabel = 0;
}

vtkKWPushButton::~vtkKWPushButton()
{
  this->SetButtonLabel(0);
}

void vtkKWPushButton::Create(vtkKWApplication *app, const char *args)
{
  const char *wname;

  // must set the application
  if (this->Application)
    {
    vtkErrorMacro("PushButton already created");
    return;
    }

  this->SetApplication(app);

  // create the top level
  wname = this->GetWidgetName();
  if (this->ButtonLabel)
    {
    this->Script("button %s %s -text {%s}", wname,args,this->ButtonLabel);
    }
  else
    {
    this->Script("button %s %s", wname,args);
    }
}

void vtkKWPushButton::SetLabel( const char *name )
{
  if ( this->Application )
    {
    this->Script("%s configure -text {%s}", this->GetWidgetName(), name );
    }
  this->SetButtonLabel(name);
}


void vtkKWPushButton::Disable()
{
  if (this->Application == NULL)
    {
    vtkErrorMacro("Widget not created yet.");
    return;
    }

  this->Script("%s configure -state disabled", this->GetWidgetName());
}

void vtkKWPushButton::Enable()
{
  if (this->Application == NULL)
    {
    vtkErrorMacro("Widget not created yet.");
    return;
    }

  this->Script("%s configure -state normal", this->GetWidgetName());
}

