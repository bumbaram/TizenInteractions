#include "TizenReceiverFrame.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;

TizenReceiverFrame::TizenReceiverFrame(void) {
}

TizenReceiverFrame::~TizenReceiverFrame(void) {
}

result TizenReceiverFrame::OnInitializing() {
	return E_SUCCESS;
}


result TizenReceiverFrame::Initialize(Views::MainForm& form) {
	result r = E_SUCCESS;
	AppAssert(form.Initialize());
	AddControl(form);
	SetCurrentForm(form);
	form.Invalidate(true);

	return r;
}

result
TizenReceiverFrame::OnTerminating(void)
{
	result r = E_SUCCESS;
	return r;
}
