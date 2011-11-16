#ifndef ZRICHEDIT_INPUTFIELD_H
#define ZRICHEDIT_INPUTFIELD_H

#include <ZInputField.h>

class ZTextParagraph;
class ZTextEdit;

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
class ZRichEditInputField;
#else
class ZRichEditInputField : public ZInputField
{
    Q_OBJECT	
public:
    ZRichEditInputField(ZTextEdit * edit); 
    virtual ~ZRichEditInputField();

    virtual int editType();
    virtual QString getText(QPoint pos , bool forward);
    virtual QPoint getCursorPos(); 
    virtual void setText(QString text);
    virtual QPoint setCursorPos(QPoint pos, int len, bool update=true);
    virtual void setReverse(QPoint pos, int len, bool update=true );
    virtual void clearReverse(bool update=true);
    virtual void setUnderline(QPoint pos, int len, bool alternateAvailable,  bool update=true);
    virtual void clearUnderline(bool update=true);
    virtual void deleteString(QPoint pos, int len , bool autoUpdate);
    virtual void insertString(QPoint pos, QString text, bool update=true );
    virtual void insertString(QPoint start_pos , QString text , int reverse_start , int reverse_len , int underline_start , int underline_len , bool alternateAvailable, int cursorPos );
    virtual void insertImage(QPoint start_pos, QString text);
    virtual QString format(QString text);
    virtual QRect getFieldBounds();
    virtual QRect getCharBounds(QPoint pos);
    QRect getUnderlineBounds(QPoint pos);
    
    void setCursorDirection(int);
    void setCursorFlag(int);
    void setMaxLength(int);

public slots:
    void slotTextChanged();
    void slotCursorChanged( int cursorX , int cursorY );	

private:
    void setCursorPosition( int para, int index, bool refreshUi = true );
    ZTextParagraph *setUnderlineValue( QPoint pos, int len, bool alternateAvailable );
    ZTextParagraph *setReverseValue( QPoint pos, int len );
    bool clearReverseInternal(bool update);
    void updateInvalidate();

private:
    uint fix[10];
};
#endif

#endif
