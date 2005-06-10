# Initialize Tcl

package require kwwidgets

# Create the application
# Restore the settings that have been saved to the registry, like
# the geometry of the user interface so far.

vtkKWApplication app
app RestoreApplicationSettingsFromRegistry
#app SetName "KWSimpleWindowWithPanelsExample"

# Set a help link. Can be a remote link (URL), or a local file

app SetHelpDialogStartingPage "http://www.kitware.com"

# Add a window to the application
# Set 'SupportHelp' to automatically add a menu entry for the help link

vtkKWWindow win
win SupportHelpOn
app AddWindow win
win Create app ""

[win GetViewFrame] SetBackgroundColor 0.92 0.87 0.69

# Add a label in the center, attach it to the view frame, and pack

vtkKWLabel hello_label
hello_label SetParent [win GetViewFrame]
hello_label Create app ""
hello_label SetWidth 50
hello_label SetForegroundColor 1.0 1.0 1.0
hello_label SetBackgroundColor 0.2 0.2 0.4

pack [hello_label GetWidgetName] -side left -anchor c -expand y -ipadx 60 -ipady 60

# Add a user interface panel to the secondary user interface manager
# Note how we do not interfere with the notebook, we just create
# a panel, hand it over to the manager, and ask the panel to return
# us where we should pack our widgets (i.e., the actually implementation
# is left to the window). 

vtkKWUserInterfacePanel label_panel
label_panel SetName "Label Interface"
label_panel SetUserInterfaceManager [win GetSecondaryUserInterfaceManager]
label_panel Create app

label_panel AddPage "Language" "Change the label language" ""
set page_widget [label_panel GetPageWidget "Language"]

# Add a set of radiobutton to modify the label text
# The set makes sure each radiobutton share the same 'variable name', 
# i.e. only one can be selected in the set because they reference
# the same Tcl variable internally and each radiobutton sets it to a
# different value (arbitrarily set to the ID of the button by default)

vtkKWRadioButtonSet rbs
rbs SetParent $page_widget
rbs Create app ""

pack [rbs GetWidgetName] -side top -anchor nw -expand y -padx 2 -pady 2

set texts { "Hello, World" "Bonjour, Monde" "Hallo, Welt" }
for {set id 0} {$id < [llength $texts]} {incr id} {
    set rb [rbs AddWidget $id]
    $rb SetText [lindex $texts $id]
    $rb SetCommand hello_label "SetText \"[lindex $texts $id]\""
    $rb SetBalloonHelpString "Set label text"
}

# Select the first label text in the set, and show/raise  the panel now
# that we have added our UI

hello_label SetText [lindex $texts 0]
[rbs GetWidget 0] StateOn
# or rb SetVariableValue 0

label_panel Raise

# Add a user interface panel to the main user interface manager

vtkKWUserInterfacePanel frame_panel
frame_panel SetName "View Interface"
frame_panel SetUserInterfaceManager [win GetMainUserInterfaceManager]
frame_panel Create app

frame_panel AddPage "View Colors" "Change the view colors" ""
set page_widget [frame_panel GetPageWidget "View Colors"]

# Add a HSV color selector to set the view frame color
# Put it inside a labeled frame for kicks

vtkKWFrameLabeled ccb_frame
ccb_frame SetParent $page_widget
ccb_frame Create app ""
ccb_frame SetLabelText "View Background Color"

pack [ccb_frame GetWidgetName] -side top -anchor nw -expand y -fill x -padx 2 -pady 2

vtkKWHSVColorSelector ccb
ccb SetParent [ccb_frame GetFrame]
ccb Create app ""
ccb SetSelectionChangingCommand [hello_label GetParent] "SetBackgroundColor"
ccb InvokeCommandsWithRGBOn
ccb SetBalloonHelpString "Set the view background color"

vtkMath math
eval ccb SetSelectedColor [eval math RGBToHSV [[hello_label GetParent] GetBackgroundColor]]

pack [ccb GetWidgetName] -side top -anchor w -expand y -padx 2 -pady 2

frame_panel Raise

# Create a main toolbar to control the label foreground color
# Set its name and it will be automatically added to the toolbars menu,
# and its visibility will be saved to the registry.

vtkKWToolbar fg_toolbar
fg_toolbar SetName "Label Foreground Color"
fg_toolbar SetParent [[win GetMainToolbarSet] GetToolbarsFrame]
fg_toolbar Create app
[win GetMainToolbarSet] AddToolbar fg_toolbar

# Add a simple explanatory label at the beginning of the toolbar 
# (most of the time, you should not really need that, icons should be
# self explanatory).

vtkKWLabel fg_toolbar_label
fg_toolbar_label SetParent [fg_toolbar GetFrame]
fg_toolbar_label Create app ""
fg_toolbar_label SetText "Label Foreground:"
fg_toolbar AddWidget fg_toolbar_label
fg_toolbar_label Delete

# Create a secondary toolbar to control the label background color
# Set its name and it will be automatically added to the toolbars menu,
# and its visibility will be saved to the registry.

vtkKWToolbar bg_toolbar
bg_toolbar SetName "Label Background Color"
bg_toolbar SetParent [[win GetSecondaryToolbarSet] GetToolbarsFrame]
bg_toolbar Create app
[win GetSecondaryToolbarSet] AddToolbar bg_toolbar

# Add a simple explanatory label at the beginning of the toolbar 
# (most of the time, you should not really need that, icons should be
# self explanatory).

vtkKWLabel bg_toolbar_label
bg_toolbar_label SetParent [bg_toolbar GetFrame]
bg_toolbar_label Create app ""
bg_toolbar_label SetText "Label Background:"
bg_toolbar AddWidget bg_toolbar_label
bg_toolbar_label Delete

# Add some color button to the toolbars
# Each button will set the label foreground or (a darker) background color

set nb_buttons 10
set buttons {}
for {set i 0} {$i < $nb_buttons} {incr i} {
    set hue [expr double($i) * (1.0 / double($nb_buttons))]

    set rgb [math HSVToRGB $hue 1.0 1.0]
    set fg_button "fg_button$i"
    vtkKWPushButton $fg_button
    $fg_button SetParent [fg_toolbar GetFrame]
    $fg_button Create app ""
    $fg_button SetCommand hello_label "SetForegroundColor $rgb"
    $fg_button SetWidth 2
    eval $fg_button SetBackgroundColor $rgb
    $fg_button SetBalloonHelpString "Set the label foreground color"
    fg_toolbar AddWidget $fg_button
    lappend buttons $fg_button

    set rgb [math HSVToRGB $hue 0.5 0.5]
    set bg_button "bg_button$i"
    vtkKWPushButton $bg_button
    $bg_button SetParent [bg_toolbar GetFrame]
    $bg_button Create app ""
    $bg_button SetCommand hello_label "SetBackgroundColor $rgb"
    $bg_button SetWidth 2
    eval $bg_button SetBackgroundColor $rgb
    $bg_button SetBalloonHelpString "Set the label background color"
    bg_toolbar AddWidget $bg_button
    lappend buttons $bg_button
}

# Start the application

app Start
set ret [app GetExitStatus]

# Deallocate and exit

math Delete
foreach abutton $buttons { $abutton Delete }
ccb Delete
bg_toolbar Delete
fg_toolbar Delete
ccb_frame Delete
label_panel Delete
frame_panel Delete
hello_label Delete
rbs Delete
win Delete
app Delete

exit $ret