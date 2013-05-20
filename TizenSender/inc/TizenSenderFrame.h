#ifndef _TIZENSENDERFRAME_H_
#define _TIZENSENDERFRAME_H_

#include <FBase.h>
#include <FUi.h>
#include "Views/MainForm.h"

class TizenSenderFrame
	: public Tizen::Ui::Controls::Frame
{
public:
	TizenSenderFrame(void);
	virtual ~TizenSenderFrame(void);

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
};

#endif	//_TIZENSENDERFRAME_H_
