 
/*
 * Copyright (C) 2007 Motorola Inc.
 *
 * Date         Author         Comment
 * 09/25/07     Motorola       Motorola customization.
*/

/****************************************************************************
** $Id: qt/src/kernel/qwindowsystem_qws.h   2.3.6   edited 2003-05-16 $
**
** Definition of Qt/FB central server classes
**
** Created : 991025
**
** Copyright (C) 1992-2000 Trolltech AS.  All rights reserved.
**
** This file is part of the kernel module of the Qt GUI Toolkit.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** Licensees holding valid Qt Enterprise Edition or Qt Professional Edition
** licenses for Qt/Embedded may use this file in accordance with the
** Qt Embedded Commercial License Agreement provided with the Software.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
**   information about Qt Commercial License Agreements.
** See http://www.trolltech.com/gpl/ for GPL licensing information.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
**********************************************************************/

#ifndef QTFB_H
#define QTFB_H

#ifndef QT_H
#include <qwssocket_qws.h>
#include <qmap.h>
#include <qdatetime.h>
#include <qlist.h>
#include <qvector.h>
#include <qimage.h>
#include <qintdict.h>
#include "qwidget.h"
#include "qwsproperty_qws.h"
#include "qwscommand_qws.h"
#include "qwsevent_qws.h"
#include "qkeyboard_qws.h"
#endif // QT_H

struct SWCursorData;
class QWSCursor;
class QWSClient;
class QWSRegionManager;
class QGfx;
class QWSServerData;

#ifndef QT_NO_QWS_FADEBACKGROUND
class QFadeBackground;
#endif

class QWSInternalWindowInfo
{

public:

    int winid;
    unsigned int clientid;
    QString name;   // Corresponds to QObject name of top-level widget

};

struct QWSWindowData;

class QWSScreenSaver
{
public:
    virtual ~QWSScreenSaver();
    virtual void restore()=0;
    virtual bool save(int level)=0;
};

class QWSWindow
{
    friend class QWSServer;
 public:
    QWSWindow(int i, QWSClient* client);
    ~QWSWindow();
    int winId() const { return id; }
    const QString &name() const { return rgnName; }
    const QString &caption() const { return rgnCaption; }
    QWSClient* client() const { return c; }

    int pageId() const { return page; } // page index in multi-page screen
    void setPageId(int id) { page = id; }

    QRegion requested() const { return requested_region; }
    QRegion allocation() const { return allocated_region; }
    bool isVisible() const { return !requested_region.isEmpty(); }
    bool isPartiallyObscured() const { return requested_region!=allocated_region; }
    bool isFullyObscured() const { return allocated_region.isEmpty(); }
    bool isFullScreen() const; // utility function to tell if window is fullscreen 

#ifndef QT_NO_QWS_FADEBACKGROUND
    bool isFadeBackground() const;
    int  fadeMode() const;
    void setFadeLevel(int l);
    int  fadeLevel() const ;
    bool isSkipFadeBackground() const;
#endif
    void raise();
    void lower();
    void show();
    void hide();
    void setActiveWindow();
    void setFocusPriority(int p);

private:
    bool hidden() const { return requested_region.isEmpty(); }
    bool forClient(const QWSClient* cl) const { return cl==c; }

    void setName( const QString &n );
    void setCaption( const QString &c );

    void addAllocation( QWSRegionManager *, const QRegion & );
    void removeAllocation( QWSRegionManager *, const QRegion & );
    void clearAllocation( QWSRegionManager * );

    int  allocationIndex() const { return alloc_region_idx; }
    void setAllocationIndex( int i ) { alloc_region_idx = i; modified = TRUE; }
    void updateAllocation();

    void setNeedAck( bool n ) { needAck = n; }

    void focus(bool get, bool updateFocusPri=TRUE);
    int focusPriority() const { return last_focus_time; }
    void operation( QWSWindowOperationEvent::Operation o );
    void shuttingDown() { last_focus_time=0; }

private:
    int id;
    QString rgnName;
    QString rgnCaption;
    int alloc_region_idx;
    int page;
    bool modified;
    bool needAck;
    bool onTop;
    QWSClient* c;
    QRegion requested_region;
    QRegion allocated_region;
    QRegion exposed;
    int last_focus_time;
    QWSWindowData *d;
};

#ifndef QT_NO_SOUND
class QWSSoundServer;
#ifdef QT_USE_OLD_QWS_SOUND

class QWSSoundServer : public QObject {
    Q_OBJECT
public:
    QWSSoundServer(QObject* parent);
    ~QWSSoundServer();
    void playFile(const QString& filename);
private slots:
    void feedDevice(int fd);
private:
    QWSSoundServerData* d;
};
#endif
#endif







/*********************************************************************
 *
 * Class: QWSServer
 *
 *********************************************************************/

class QWSMouseHandler;
struct QWSCommandStruct;

#ifndef QT_NO_QWS_MULTIPROCESS
class QWSServer : public QWSServerSocket
#else
class QWSServer : public QObject
#endif
{
    friend class QCopChannel;
    friend class QWSMouseHandler;
    friend class QWSWindow;
    friend class QWSDisplay;
    friend class QWSInputMethod;
#ifndef QT_NO_QWS_FADEBACKGROUND    
    friend class QFadeBackground;
#endif
    Q_OBJECT

public:
    QWSServer( int flags = 0, QObject *parent=0, const char *name=0 );
    ~QWSServer();
    enum ServerFlags { DisableKeyboard = 0x01,
		       DisableMouse = 0x02 };


    enum GUIMode { NoGui = FALSE, NormalGUI = TRUE, Server };
#ifdef QT_QWS_MULTI_DISPLAY
    static void sendScreenSwitchEvents(int screen );
#endif    
    static void sendKeyEvent(int unicode, int keycode, int modifiers, bool isPress,
			     bool autoRepeat, int steps=0, int index=0);
    static void processKeyEvent(int unicode, int keycode, int modifiers, bool isPress,
				bool autoRepeat, int keyWeight=0, int index=0);

    // multi-display system
    //     // update active display: 
    //     1) focus transfer to active display 
    //     2) paintable display transfer to active display if single display paintable
    //     3) trigger displaySwitched signal
    //     4) send displaySwitchEvent to all toplevel widget
    static void setActiveDisplay(DisplayID id);

	//mason: begin, for to improve im's performance
    void lowerWindow( QWSWindow* changingw, QWSWindow* w);
	//mason: end

#ifndef QT_NO_QWS_IM
    enum IMState { Reserved, IMCompose, IMEnd, IMInternal = 42, IMMarkedText };
    enum IMMouse { MousePress, MouseRelease, MouseMove }; //MouseMove reserved but not used

    void sendIMEvent( IMState state, const QString& txt, int cpos, int selLen );
#endif

#ifndef QT_NO_QWS_MMI_TEST
    static QWSWindow* getKeyFocusw();
#endif /* added */

#ifndef QT_NO_QWS_KEYBOARD
    typedef struct KeyMap {
	int  key_code;
	ushort unicode;
	ushort shift_unicode;
	ushort ctrl_unicode;
    };

    static const KeyMap *keyMap();

    static void setOverrideKeys( QIntDict<QWSServer::KeyMap> *map );

    class KeyboardFilter
    {
    public:
	virtual bool filter(int unicode, int keycode, int modifiers, bool isPress,
		      bool autoRepeat)=0;
    };

    static void setKeyboardFilter( KeyboardFilter *f );
#endif
#ifndef QT_NO_QWS_IM
    static void setCurrentInputMethod( QWSInputMethod *im );
    static void resetInputMethod();
    static void setMicroFocus( int x, int y );
    static void requestMarkedText();
#endif


    static void setDefaultMouse( const char * );
    static void setDefaultKeyboard( const char * );
    static void setMaxWindowRect(const QRect&, int page=0);
    static void sendMouseEvent(const QPoint& pos, int state);

    static void setDesktopBackground( const QImage &img ); // !! thoretically there should be multiple background images
    static void setDesktopBackground( const QColor & );    //  and colors for each desktop
    static QWSMouseHandler *mouseHandler();
    static void setMouseHandler(QWSMouseHandler*);
#ifndef QT_NO_QWS_KEYBOARD
    static QWSKeyboardHandler* keyboardHandler();
    static void setKeyboardHandler(QWSKeyboardHandler* kh);
#endif
    QWSWindow *windowAt( const QPoint& pos, int page=0 );
    
    const QList<QWSWindow> &clientWindows() { return windows; }

    void openMouse();
    void closeMouse();
#ifndef QT_NO_QWS_KEYBOARD
    void openKeyboard();
    void closeKeyboard();
#endif

    static void setScreenSaver(QWSScreenSaver*); // maybe multiple
    static void setScreenSaverIntervals(int* ms);
    static void setScreenSaverInterval(int);
    static bool screenSaverActive();
    static void screenSaverActivate(bool);

    // the following are internal.
    void refresh();
    void enablePainting(bool);
    static void processEventQueue();
    static QList<QWSInternalWindowInfo> * windowList();

    void sendPropertyNotifyEvent( int property, int state );
#ifndef QT_NO_QWS_PROPERTIES
    QWSPropertyManager *manager() {
	return &propertyManager;
    }
#endif

    static QPoint mousePosition;

    static void startup( int flags );
    static void closedown();

    static void beginDisplayReconfigure();
    static void endDisplayReconfigure();

#ifndef QT_NO_QWS_CURSOR
    static void setCursorVisible( bool );
    static bool isCursorVisible();
#endif

#ifndef QT_NO_QWS_FADEBACKGROUND
    void enableFadeBackground( bool, int );  
#endif 

    // add Prehide and PaintEnd for FEAT_TAT_ANIMATION
    enum WindowEvent { Create=0x01, Destroy=0x02, Hide=0x04, Show=0x08,
		       Raise=0x10, Lower=0x20, Geometry=0x40, Active=0x80,
                       Move=0xb0, Name=0x0100, Prehide=0x0200, Migrate=0x0400, 
                       PaintEnd=0x0800 };

    // Morphing Feature
    void setMorphMode( const int morphMode );   // set morph mode of device
    int getMorphMode() const;   // get morph mode of device

signals:
    void windowEvent( QWSWindow *w, QWSServer::WindowEvent e );
    void requestedSetMorphMode( int modeId );
#ifndef QT_NO_COP
    void newChannel( const QString& channel);
    void removedChannel(const QString& channel);
#endif
#ifndef QT_NO_QWS_IM
    void markedText( const QString & );
#endif

    //Begin: added
    void NotifyClientClosed(QWSClient *c);
    //End: added

    void cursorSelected( QWSCursor* curs );
    void idleStatusChanged(bool inIdle);
    void idleAltitudeChanged(int altitude);

    void stopOmgRateMode(int stopStep, int index = 0);         //e6625c, called by need stop omega rate mode

private:
    
    static int  activeScreenPage(); 
#ifdef QT_QWS_MULTI_DISPLAY
    static void setActiveScreenPage(int p);
#endif

#ifndef QT_NO_COP
    static void sendQCopEvent( QWSClient *c, const QCString &ch,
			       const QCString &msg, const QByteArray &data,
			       bool response = FALSE );
#endif
    void move_region( const QWSRegionMoveCommand * );
    void set_altitude( const QWSChangeAltitudeCommand * );
    void request_focus( const QWSRequestFocusCommand * );
    void set_altitudeAndFocus( const QWSChangeAltitudeAndRequestFocusCommand * );
    void request_region( int, QRegion );
    void destroy_region( const QWSRegionDestroyCommand * );
    void name_region( const QWSRegionNameCommand * );
#ifdef QT_QWS_MULTI_DISPLAY
    void migrate_region( const QWSRegionMigrateCommand * );
#endif
    void set_region_priority( const QWSSetRegionPriorityCommand * );
    void reset_region_focus_priority( const QWSResetRegionFocusPriorityCommand * );
    void insertPrioritizedWindow(QWSWindow *, bool insertAtFront = TRUE);
    void set_identity( const QWSIdentifyCommand * );
#ifndef QT_NO_QWS_FADEBACKGROUND
    void set_fade_background(const QWSSetFadeBackgroundCommand *);
    void skip_fade_background(const QWSSkipFadeBackgroundCommand *);
#endif

#ifndef QT_NO_QWS_IM
    void set_im_info( const QWSSetIMInfoCommand * );
    void reset_im( const QWSResetIMCommand * );
    void set_im_font( const QWSSetIMFontCommand * );
    void send_im_mouse( const QWSIMMouseCommand * );
    static void sendKeyEventUnfiltered(int unicode, int keycode,
				       int modifiers, bool isPress,
				       bool autoRepeat, int keyWeight, int index);

#endif
    void simulate_mouse_event( const QWSSimulateMouseEventCommand * );
    static void emergency_cleanup();

    static QColor *bgColor; // multiple background image for multi-page screen
    static QImage *bgImage; // multiple background image for multi-page screen

    void sendMaxWindowRectEvents();
#ifndef QT_NO_QWS_MULTIPROCESS
    void newConnection( int socket );
#endif
    void invokeIdentify( const QWSIdentifyCommand *cmd, QWSClient *client );
    void invokeCreate( QWSCreateCommand *cmd, QWSClient *client );
    void invokeRegionName( const QWSRegionNameCommand *cmd, QWSClient *client );
    void invokeRegionPriority( const QWSSetRegionPriorityCommand *cmd, QWSClient *client );
    void invokeRegionFocusPriority( const QWSResetRegionFocusPriorityCommand *cmd, QWSClient *client );
    void invokeRegion( QWSRegionCommand *cmd, QWSClient *client );
    void invokeRegionMove( const QWSRegionMoveCommand *cmd, QWSClient *client );
    void invokeRegionDestroy( const QWSRegionDestroyCommand *cmd, QWSClient *client );
#ifdef QT_QWS_MULTI_DISPLAY
    void invokeRegionMigrate( const QWSRegionMigrateCommand *cmd, QWSClient *client );
#endif
    void invokeSetAltitude( const QWSChangeAltitudeCommand *cmd, QWSClient *client );
    // atomic opertions
    void invokeSetAltitudeAndSetFocus( const QWSChangeAltitudeAndRequestFocusCommand *cmd, QWSClient *client );
#ifndef QT_NO_QWS_PROPERTIES
    void invokeAddProperty( QWSAddPropertyCommand *cmd );
    void invokeSetProperty( QWSSetPropertyCommand *cmd );
    void invokeRemoveProperty( QWSRemovePropertyCommand *cmd );
    void invokeGetProperty( QWSGetPropertyCommand *cmd, QWSClient *client );
#endif //QT_NO_QWS_PROPERTIES
    void invokeSetSelectionOwner( QWSSetSelectionOwnerCommand *cmd );
    void invokeConvertSelection( QWSConvertSelectionCommand *cmd );
    void invokeSetFocus( const QWSRequestFocusCommand *cmd, QWSClient *client );

    void initIO();
    void setFocus( QWSWindow*, bool gain, bool causedByMigrate=FALSE );
#ifndef QT_NO_QWS_CURSOR
    void invokeDefineCursor( QWSDefineCursorCommand *cmd, QWSClient *client );
    void invokeSelectCursor( QWSSelectCursorCommand *cmd, QWSClient *client );
#endif
    void invokeGrabMouse( QWSGrabMouseCommand *cmd, QWSClient *client );
    void invokeGrabKeyboard( QWSGrabKeyboardCommand *cmd, QWSClient *client );
#ifndef QT_NO_SOUND
    void invokePlaySound( QWSPlaySoundCommand *cmd, QWSClient *client );
#endif
#ifndef QT_NO_COP
    void invokeRegisterChannel( QWSQCopRegisterChannelCommand *cmd,
				QWSClient *client );
    void invokeQCopSend( QWSQCopSendCommand *cmd, QWSClient *client );

#endif
#ifndef QT_NO_QWS_IM
        void invokeSetIMInfo( const QWSSetIMInfoCommand *cmd,
                                QWSClient *client );
        void invokeSetIMFont( const QWSSetIMFontCommand *cmd,
                                QWSClient *client );
#endif
    void invokeSimulateMouseEvent( const QWSSimulateMouseEventCommand*, QWSClient *client );

#ifndef QT_NO_QWS_FADEBACKGROUND
    void invokeFadeBackground(const QWSSetFadeBackgroundCommand* cmd, QWSClient *client);
    void invokeSkipFadeBackground(const QWSSkipFadeBackgroundCommand* cmd, QWSClient *client);
#endif
    // Morphing Feature
    void invokeSetMorphMode( const QWSSetMorphModeCommand *cmd, QWSClient*);

    QWSMouseHandler* newMouseHandler(const QString& spec);
#ifndef QT_NO_QWS_KEYBOARD
    QWSKeyboardHandler* newKeyboardHandler(const QString& spec);
#endif
    void openDisplay();
    void closeDisplay();
    void initRegions();

    void showCursor();
    void hideCursor();
    void initializeCursor();
    void paintServerRegion(int page=0);
    void paintBackground( const QRegion &r, int page=0);
    void clearRegion( const QRegion &r, const QColor &c, int page=0);
    void refreshBackground(int page=0);
    void resetGfx(); // reset all gfx for all pages

private slots:
#ifndef QT_NO_QWS_MULTIPROCESS
    void clientClosed();
    void doClient();
#endif
    void setMouse(const QPoint& pos,int bstate);

    void screenSaverWake();
    void screenSaverSleep();
    void screenSaverTimeout();

    void respondWindowEvent( QWSWindow *w, QWSServer::WindowEvent e );

private:
    void disconnectClient( QWSClient * );
    void screenSave(int level);
    void doClient( QWSClient * );
    typedef QMapIterator<int,QWSClient*> ClientIterator;
    typedef QMap<int,QWSClient*> ClientMap;
    void releaseMouse(QWSWindow* w);
    void releaseKeyboard(QWSWindow* w);

    void updateClientCursorPos();

    //uchar* sharedram; // no use currently, remove 
    //int ramlen;       // no use currently, remove

    //QGfx *gfx;
    // In order to support multi-page screen, most of single member variables must evolve to vectors
    QArray<QGfx*> gfxs;

    ClientMap client;
#ifndef QT_NO_QWS_PROPERTIES
    QWSPropertyManager propertyManager;
#endif
    struct SelectionOwner {
	int windowid;
	struct Time {
	    void set( int h, int m, int s, int s2 ) {
		hour = h; minute = m; sec = s; ms = s2;
	    }
	    int hour, minute, sec, ms;
	} time;
    } selectionOwner;
    QTime timer;
    QWSServerData* d;
    int* screensaverinterval;

    QWSWindow *focusw; // only one focus even with multi-page screen
    QWSWindow *mouseGrabber; // only one mouse grabber even with multi-page screen
    bool mouseGrabbing;
    //int swidth, sheight, sdepth;
    QArray<int> swidth;
    QArray<int> sheight;
    //QArray<int> sdepth; // no use currently

#ifndef QT_NO_QWS_CURSOR
    bool haveviscurs;
    QWSCursor *cursor;	    // cursor currently shown
    QWSCursor *nextCursor;  // cursor to show once grabbing is off
#endif
    //QRegion screenRegion;   // the entire display region
    //QRegion serverRegion;
    //QRegion dirtyBackground;
    QVector<QRegion> screenRegions;   // the entire display regions for multi-page screen
    QVector<QRegion> serverRegions;   // seems currently no use
    QVector<QRegion> dirtyBackgrounds;
    bool disablePainting;
    QList<QWSMouseHandler> mousehandlers;
#ifndef QT_NO_QWS_KEYBOARD
    QList<QWSKeyboardHandler> keyboardhandlers;
#endif

    QList<QWSCommandStruct> commandQueue;
    QWSRegionManager *rgnMan; // only one region manager, now it must manage all regions in different screen pages

    // Morphing Feature
    int morphMode;  // morph mode of device

    // Window management
    QList<QWSWindow> windows; // first=topmost
    QWSWindow* newWindow(int id, QWSClient* client);
    QWSWindow* findWindow(int windowid, QWSClient* client);
    void moveWindowRegion(QWSWindow*, int dx, int dy );
    QRegion setWindowRegion(QWSWindow*, QRegion r, bool isMigrate=FALSE );
    void raiseWindow( QWSWindow *, int = 0);
    void lowerWindow( QWSWindow *, int = -1);
    void exposeRegion( QRegion , int index = 0, int page=0 );
    void notifyModified( QWSWindow *active = 0 );
    void syncRegions( QWSWindow *active = 0 );

    void setCursor(QWSCursor *curs);

#ifndef QT_NO_QWS_FADEBACKGROUND
    QFadeBackground *fadeover;
#endif

    // multimedia
#ifndef QT_NO_SOUND
    QWSSoundServer *soundserver;
#endif
#ifndef QT_NO_COP
    QMap<QString, QList<QWSClient> > channels;
#endif
#ifndef QT_NO_QWS_IM
    bool microF;
    int microX;
    int microY;
#endif
    int idleAltitude;
    bool idleStatus;
#ifndef QT_NO_QWS_MMI_TEST
public:
   void sendCaptureEvent();
#endif
};

extern QWSServer *qwsServer; //there can be only one



#ifndef QT_NO_QWS_IM
class QWSInputMethod : public QObject
{
public:
    QWSInputMethod();
    virtual ~QWSInputMethod();
    virtual bool filter(int unicode, int keycode, int modifiers,
			bool isPress, bool autoRepeat)=0;
    virtual void reset();
    virtual void setMicroFocus( int x, int y );
    virtual void mouseHandler( int, int );
    QFont font() const;
    QRect inputRect() const;
protected:
    void sendIMEvent( QWSServer::IMState, const QString& txt, int cpos, int selLen = 0 );
};

inline void QWSInputMethod::sendIMEvent( QWSServer::IMState state, const QString &txt, int cpos, int selLen )
{
    qwsServer->sendIMEvent( state, txt, cpos, selLen );

}
#endif




/*********************************************************************
 *
 * Class: QWSClient
 *
 *********************************************************************/

struct QWSMouseEvent;

typedef QMap<int, QWSCursor*> QWSCursorMap;

class QWSClient : public QObject
{
    Q_OBJECT
public:
    QWSClient( QObject* parent, int socket, int id );
    ~QWSClient();

    int socket() const;

    void setIdentity(const QString&);
    QString identity() const { return id; }

    void sendEvent( QWSEvent* event );
    void sendConnectedEvent( const char *display_spec );
    void sendMaxWindowRectEvent(int page=0);
    void sendRegionModifyEvent( int winid, QRegion exposed, int page, bool ack );
    void sendFocusEvent( int winid, bool get );
    void sendPropertyNotifyEvent( int property, int state );
    void sendPropertyReplyEvent( int property, int len, char *data );
    void sendSelectionClearEvent( int windowid );
    void sendSelectionRequestEvent( QWSConvertSelectionCommand *cmd, int windowid );

    // 
    // Note: added so full-screen applications (like A780 camera) can send mouse
    // events to the application manager
    //
    
    void sendSimulateMouseEvent( const QPoint& pos, int state);

    QWSCommand* readMoreCommand();

    int clientId() const { return cid; }

    QWSCursorMap cursors;	// cursors defined by this client
signals:
    void connectionClosed();
    void readyRead();
private slots:
    void closeHandler();
    void errorHandler( int );
private:
    int s; // XXX csocket->d->socket->socket() is this value
#ifndef QT_NO_QWS_MULTIPROCESS
    QWSSocket *csocket;
#endif
    QWSCommand* command;
    uint isClosed : 1;
    QString id;
    int cid;
};

#endif
