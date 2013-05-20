#ifndef _TIZENRECEIVERFRAME_H_
#define _TIZENRECEIVERFRAME_H_

#include <FBase.h>
#include <FUi.h>
#include <FApp.h>
#include "Views/MainForm.h"

class TizenReceiverFrame
	: public Tizen::Ui::Controls::Frame
{
public:
	TizenReceiverFrame(void);
	virtual ~TizenReceiverFrame(void);

public:
	result Initialize(Views::MainForm& form);

	result OnInitializing();
	result OnTerminating();

private:
};

#endif	//_TIZENRECEIVERFRAME_H_
