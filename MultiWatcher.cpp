#include "MultiWatcher.h"


void MultiWatcher::run()
{
	_sync.waitForFinished();
	emit allDone();
}
