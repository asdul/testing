// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 9.1.0
// Project name: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
lv_obj_t * ui_Screen1;
void ui_event_Switch1(lv_event_t * e);
lv_obj_t * ui_Switch1;
lv_obj_t * ui_Panel1;
lv_obj_t * ui_Label1;
// CUSTOM VARIABLES

// EVENTS
lv_obj_t * ui____initial_actions0;

// IMAGES AND IMAGE SETS

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 32bit to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_Switch1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);

    if(event_code == LV_EVENT_VALUE_CHANGED &&  !lv_obj_has_state(target, LV_STATE_CHECKED)) {
        _ui_label_set_property(ui_Label1, _UI_LABEL_PROPERTY_TEXT, "off");
    }
    if(event_code == LV_EVENT_VALUE_CHANGED &&  lv_obj_has_state(target, LV_STATE_CHECKED)) {
        _ui_label_set_property(ui_Label1, _UI_LABEL_PROPERTY_TEXT, "on");
    }
}

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t * dispp = lv_display_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_Screen1);
}
