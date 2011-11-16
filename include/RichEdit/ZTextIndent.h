#ifndef ZTEXTINDENT_H
#define ZTEXTINDENT_H

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZTextIndent;
#else
class Q_EXPORT ZTextIndent
{
public:
    ZTextIndent();
    ~ZTextIndent();
};
#endif

#endif
