//Non class in EM35/VE66
//Create by Ant-ON

#ifdef FixByMAGX

#define ZScrollView ZScrollPanel

#include "ZScrollPanel.h"

#else

#include <qscrollview.h>

#define ZScrollView QScrollView

#endif
