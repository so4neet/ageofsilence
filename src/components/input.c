#include <stdio.h>
#include <kos.h>
#include <dc/maple.h>
#include <dc/maple/controller.h>

bool aPressed = false;
bool bPressed = false;
int padding = 0;
int menuChoice;
int GetStartState() {
    maple_device_t *controller_one = maple_enum_dev(0, 0);
    cont_state_t *status = maple_dev_status(controller_one);

    if(status->buttons & CONT_START){
        return 1;
    } else {
        return 0;
    }
}

void HandleMenuInput(int menuChoices) {
    if(padding > 0){
        padding--;
    }


    maple_device_t *controller_one = maple_enum_dev(0, 0);
    cont_state_t *status = maple_dev_status(controller_one);

    if(status->buttons & CONT_DPAD_DOWN){
        if(padding == 0){
            if(menuChoice < menuChoices-1) {
                menuChoice++;
                padding = 10;
            }
        }
    }
    if(status->buttons & CONT_DPAD_UP){
        if(padding == 0){
            if(menuChoice > 0) {
                menuChoice--;
                padding = 10;
            }
        }
    }

    if(status->buttons & CONT_A){
        if(padding == 0){
            aPressed = true;
            padding = 10;
        } else {
            aPressed = false;
        }

    }
    if(status->buttons & CONT_B){
        if(padding == 0){
            bPressed = true;
            padding = 10;
        } else {
            bPressed = false;
        }
    }
}

void HandleGameInput() {

}
