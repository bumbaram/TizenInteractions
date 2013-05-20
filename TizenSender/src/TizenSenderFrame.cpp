#include "TizenSenderFrame.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;

TizenSenderFrame::TizenSenderFrame(void)
{
}

TizenSenderFrame::~TizenSenderFrame(void)
{
}

result
TizenSenderFrame::OnInitializing(void)
{
	result r = E_SUCCESS;
	Views::MainForm* form = new (std::nothrow) Views::MainForm;
	AppAssert(form && form->Initialize());

	AddControl(*form);
	SetCurrentForm(*form);
	form->Invalidate(true);

	return r;
}

result
TizenSenderFrame::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}


