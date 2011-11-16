// Writed by Ant-ON <prozanton@gmal.com>, 2010
// Based on QCopChannel header file.

#ifndef ESCOPCHENEL_H
#define ESCOPCHENEL_H

#include <qobject.h>
#include <qstring.h>

#include <ES_API.h>

class ESCopChannel: public QObject
{
	int fix[30];
	
	public:
		ESCopChannel(char const* channel, bool, char const*, char const*, char const*, QObject* parent, char const*, bool);
		ESCopChannel(char const* channel, bool, QObject* parent=0, char const* name=0);
		ESCopChannel(const QCString& channel, QObject* parent=0, char const* name=0);
		~ESCopChannel();	
		
		static bool send(const QCString &channel, const QCString &msg, bool local = false);
		static bool send(const QCString &channel, const QCString &msg, const QByteArray &data, bool local = false);		
		static bool sendEx(ES_Event const&, bool local = false);
		
		static bool isRegistered(QCString const&, int = 0xFFFFFFFF);
		
		QString channel() const;
		
		void bPrefix() const;
		void filter() const;
		
		void defaultFilterConstraint() const;
		void filterConstraint() const;
		int getSubscriptionResult() const;
		
		void setSubscriptionResult(int);
		
		void registerStartup(char const*, void const*, int, char const*, bool, char const*, char const*, char const*, bool, bool);
		void unregisterStartup(char const*, char const*);
		
		virtual void receiveEx(ES_Event const&);
		virtual void receive(QCString const&, QArray<char> const&);		
signals:
		void receivedEx(ES_Event const&);
		void received(QCString const&, QArray<char> const&);
};

#endif
