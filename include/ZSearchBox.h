

// Copyright (c) 06-Jul-07 - 2008 Motorola, Inc. All rights reserved.


#ifndef PUBLIC_API_WIDGET_ZSEARCHBOX_H
#define PUBLIC_API_WIDGET_ZSEARCHBOX_H

#ifndef __cplusplus
#error "This is a C++ header file; it requires C++ to compile."
#endif

#include "qpixmap.h"
#include "qstring.h"
#include "ZWidget.h"
#include "ZSkinService.h"

#include "ZLineEdit.h"

class ZLabel;
class ZImage;
class ZLineEdit;
class ZKbInputField;
class ZSearchBoxPrivate;
class ZLineEditSB ;

class Q_EXPORT ZSearchBox: public ZWidget
{
    Q_OBJECT

public:

    enum
    {
        LEFT,   
        UP,     
        RIGHT,  
        DOWN,   
        MID,    
        NUM     
    };

    ZSearchBox(QWidget * parent , const char * name = 0, WFlags f = 0,
            const ZSkinService::WidgetClsID clsId = ZSkinService::clsZSearchBox,bool mHasIMIcon = true);

    ~ZSearchBox();

    void setImagePixmap(QPixmap & pixmap);

    void setUpPixmap(QPixmap & pixmap) ;

    void setDownPixmap(QPixmap & pixmap) ;

    void  setLabelText(const QString & string);

    void  setLabelMatchText(const QString & string) ;

    ZKbInputField * getInputField();

    virtual bool eventFilter(QObject * o,QEvent * e);

     ZLineEdit * lineEdit();

     ZLabel * label();

     ZLabel * labelMatch() ;

     void setMaxLength(int nLimit);

     int  maxLength();

     QSize sizeHint() const;

    virtual void setGeometry(int x,int y, int w, int h);

    virtual void setGeometry(const QRect & r);

    virtual void resize(int w, int h);

    void setEnabled(bool enable);

    bool isZEnabled();

    bool isZDisabled();

    void activate(QKeyEvent *e);

    void setPalette(const QPalette & palette);

    void updateSkin(bool redraw);

signals:
    void sigTextChanged(const QString &str );

    void clearAllText();

    void keyPressed(int nIdx);

    void keyReleased(int nIdx);

    void SearchBoxResize() ;

protected:

    void paintEvent(QPaintEvent * e);

    void keyPressEvent(QKeyEvent * e);

    void customEvent(QCustomEvent * e);

    void resizeEvent( QResizeEvent * );

    QRect getContentRect() const;

    QSize getSearchBoxSize(int contentH);

    QSize getSearchBoxSize(const QSize&  szContent) const;

    void  layoutSearchBox();

    bool  createLabel();

    bool  createLabelMatch() ;

private:
    ZSearchBoxPrivate * d;
};

class  ZLineEditSB: public ZLineEdit
{
    Q_OBJECT

public:

    ZLineEditSB( QWidget *parent, const char *name=0,
                 const ZSkinService::WidgetClsID clsId = ZSkinService::clsZLineEdit);

    ZLineEditSB( const QString & contents, QWidget *parent, const char *name=0,
                 const ZSkinService::WidgetClsID clsId = ZSkinService::clsZLineEdit);

    ~ ZLineEditSB();

signals:
    void LEkeyPressed(int nIdx);

    void LEkeyReleased(int nIdx);

protected:

    void  keyPressEvent( QKeyEvent * );

    void emitKeySignal(QEvent * e ,int keyIndex) ;

} ;

#endif 
