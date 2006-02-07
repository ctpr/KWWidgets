from kwwidgets import vtkKWNotebook
from kwwidgets import vtkKWApplication
from kwwidgets import vtkKWWindow



def vtkKWNotebookEntryPoint(parent, win):

    app = parent.GetApplication()
    
    # -----------------------------------------------------------------------
    
    # Create a notebook
    
    notebook1 = vtkKWNotebook()
    notebook1.SetParent(parent)
    notebook1.SetMinimumWidth(400)
    notebook1.SetMinimumHeight(200)
    notebook1.Create()
    
    app.Script(
        "pack %s -side top -anchor nw -expand n -padx 2 -pady 2",
        notebook1.GetWidgetName())
    
    # Add some pages
    
    notebook1.AddPage("Page 1")
    
    notebook1.AddPage("Page Blue")
    notebook1.GetFrame("Page Blue").SetBackgroundColor(0.2, 0.2, 0.9)
    
    page_id = notebook1.AddPage("Page Red")
    notebook1.GetFrame(page_id).SetBackgroundColor(0.9, 0.2, 0.2)
    
    
    
    return "TypeComposite"