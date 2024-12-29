#include "check_button.h"

void CheckButton::on_click()
{
    emit send_sig();
    setEnabled(false);
}
