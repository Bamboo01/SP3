#include "GL/glew.h"
#include <string>
#pragma once

struct CanvasImageUpdate
{
    enum ClickType
    {
        START,
        CLICKABLE,
        NONCLICKABLE,
        END
    };

    enum ButtonType
    {
        START2 = 0,
        GENERATOR1BUTTON,
        GENERATOR2BUTTON,
        LABBUTTON,
        LABNORMALUNIT,
        LABTANKUNIT,
        LABRANGEUNIT,
        NEXUSCREATEUNITBUTTON,
        NEXUSCREATEBUILDINGBUTTON,
        NEXUSNORMALUNIT,
        NEXUSTANKUNIT,
        NEXUSRANGEUNIT,
        NEXUSBUILDING,
        NEXUSWALL,
        NEXUSGENERATOR1,
        NEXUSGENERATOR2,
        END2
    };

    enum PopUpType
    {
        START3,
        POPUP,
        NONPOPUP,
        END3
    };

    enum UniqueUI
    {
        START4,
        LABUI,
        NEXUSUNITUI,
        NEXUSBUILDINGUI,
        PICUI
    };

    ClickType clicktype;
    ButtonType buttontype;
    PopUpType popuptype;
    UniqueUI uniquetype;

    CanvasImageUpdate()
    {
        clicktype = START;
        buttontype = START2;
        popuptype = START3;
        uniquetype = START4;
    }

    CanvasImageUpdate(ClickType clicktype, ButtonType buttontype, PopUpType popuptype, UniqueUI uniquetype)
    {
        this->clicktype = clicktype;
        this->buttontype = buttontype;
        this->popuptype = popuptype;
        this->uniquetype = uniquetype;
    }
};