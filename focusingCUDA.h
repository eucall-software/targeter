#pragma once

#include "globals.h"

class focusingCUDA 
{


public:
	focusingCUDA() {};
	~focusingCUDA() {};

public slots:

	void getFocusScore(FocusResult& res);

signals:

	void setFOCUS(FocusResult res);
};
