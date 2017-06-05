# MMPADrawViewer
Program used to view raw data files from the 396x266 MMPAD (Cornell 3x2 tiled) (Mixed-Mode Pixel Array Detector).  
No waranty. I'm not reponsible for your data.  The program has mostly been used by me and it works.  I have not gone through rigorous debugging and exception handling is minimal thus far.
Also, note:  The code grew organically - I might rewrite and totally redo how I do everything.

All that being said - it is incredibly useful for MMPAD raw data (i.e. image stacks).
Two ways of loading file:
  file->load file :  Loads with typical fread type stuff.  Can be a drag for 16 GB files.
  file->load file (mem map): My preferred method.  It uses the Boost the mem-map routines.  This is super fast for these big files.  I do however only use this on copies of the orginial data. This is not because I have had any problems with it and not because I change the files knowling... it is more because I am paranoid.
  
  Once the data is loaded - left/right arrows flip through (backward/forward repectively) the the frames in increments of one. Up/Down arrows increment frames by the number in the field "major frame step."
  I am starting to write some help text in the program...
