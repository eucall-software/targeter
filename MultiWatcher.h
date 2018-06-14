#ifndef _MULTIWATCHER
#define _MULTIWATCHER

#include <QThread>
#include <QFutureSynchronizer>

#include "globals.h"

class MultiWatcher : public QThread
{
	Q_OBJECT

public:

signals:
	void MultiWatchDone();

public:
	void run() override 
	{
		_sync.waitForFinished();
		emit MultiWatchDone();
	};

	QFutureSynchronizer<FocusResult> _sync;
};

#endif