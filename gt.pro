
TEMPLATE = subdirs

SUBDIRS = GtCore GtLib GtGui Grepotool 

win32-msvc*{
    TEMPLATE = $$join(TEMPLATE,,"vc",)
} 
