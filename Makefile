# NOTE !!! when adding a class, it must be added in one location.
# Place it in the correct list based on whether it is only a .h file
# and whether it is abstract or concrete.
#
ME = KWWidgets

srcdir        = .

ABSTRACT_H = 

CONCRETE_H = 

ABSTRACT = \
vtkKWComposite \
vtkKWView 

CONCRETE = \
vtkKWApplication \
vtkKWCheckButton \
vtkKWCompositeCollection \
vtkKWDialog \
vtkKWEntry \
vtkKWExtent \
vtkKWGenericComposite \
vtkKWLabeledFrame \
vtkKWMessageDialog \
vtkKWNotebook \
vtkKWObject \
vtkKWOptionMenu \
vtkKWRadioButton \
vtkKWSaveImageDialog \
vtkKWScale \
vtkKWSerializer \
vtkKWText \
vtkKWWidget \
vtkKWWidgetCollection \
vtkKWViewCollection \
vtkKWWindow \
vtkKWWindowCollection

#------------------------------------------------------------------------------
# Autoconfig defines that can be overridden in user.make

include ${VTKBIN}/system.make

#------------------------------------------------------------------------------
# Include user-editable defines.

include ${VTKBIN}/user.make

#------------------------------------------------------------------------------
# Include the generated targets

include targets.make

# add in any extra libraies here
KIT_LIBS =

# standard stuff here
KIT_OBJ = ${SRC_OBJ} 
KIT_TCL_OBJ = ${TCL_OBJ}
KIT_NEWS = ${TCL_NEWS}
KIT_FLAGS = 


VTK_LIB_FILE  = libVTK${ME}${VTK_LIB_EXT}
TCL_LIB_FILE  = libVTK${ME}Tcl${VTK_LIB_EXT}


#------------------------------------------------------------------------------
# Include the generic stuff here

include ../Kits.make


